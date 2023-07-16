#include <babychicks.hpp>
#include "random.cpp"

uint32_t now() { return current_time_point().sec_since_epoch(); }

/**
 * @brief Listen for WAX transfers to this contract
 *
 * @param from
 * @param to
 * @param quantity
 * @param memo
 */
void babychicks::receive_token_transfer(
    name from, name to, asset quantity, std::string memo
) {
    // Ignore EOSIO system account transfers
    const std::set<name> ignore = std::set<name>{
        name("eosio.stake"),
        name("eosio.names"),
        name("eosio.ram"),
        name("eosio.rex"),
        name("eosio")};

    // Ignore transfers not to this contract
    if (to != get_self() || ignore.find(from) != ignore.end()) {
        return;
    }

    if (memo == "egg") {
        mint_egg_check(from, quantity);
    } else {
        check(false, "invalid memo");
    }
}

/**
 * @brief Check if the quantity is valid and mint an egg
 * If the quantity is valid, mint an egg and send it to the sender
 *
 * @param receiver
 * @param quantity
 */
void babychicks::mint_egg_check(name receiver, asset quantity) {
    // Check if the quantity is valid
    if (quantity.symbol != babychick_constants::CORE_TOKEN_SYMBOL ||
        quantity.amount != babychick_constants::EGG_PRICE_IN_WAX) {
        check(false, "invalid quantity");
    }

    // Mint an egg and send it to the sender
    mint_egg(receiver);
}

/**
 * @brief Mint an egg and send it to the sender
 *
 * @param receiver
 */
void babychicks::mint_egg(name receiver) {
    action(
        permission_level{get_self(), name("active")},
        atomicassets::ATOMICASSETS_ACCOUNT,
        name("mintasset"),
        std::make_tuple(
            get_self(),
            babychick_constants::COLLECTION_NAME.value,
            babychick_constants::EGG_SCHEMA_NAME.value,
            babychick_constants::EGG_TEMPLATE_ID,
            receiver,
            // immutable data
            (atomicassets::ATTRIBUTE_MAP){{"created_at", (uint64_t)now()}},
            // mutable data
            (atomicassets::ATTRIBUTE_MAP){},
            // backing assets
            (std::vector<asset>){}
        )
    )
        .send();
}

/**
 * @brief Let the owner of the contract airdrop Egg NFTs to wallets
 *
 * @param receiver
 */
ACTION babychicks::airdropegg(name receiver) {
    require_auth(get_self());

    // Make sure the receiver is valid
    check(is_account(receiver), "invalid receiver");

    mint_egg(receiver);
}

/**
 * @brief Listen for NFT transfers to this contract
 *
 * @param from
 * @param to
 * @param asset_ids
 * @param memo
 */
void babychicks::receive_asset_transfer(
    name from, name to, std::vector<uint64_t> asset_ids, std::string memo
) {
    // Ignore EOSIO system account transfers
    const std::set<name> ignore = std::set<name>{
        atomicassets::ATOMICASSETS_ACCOUNT,
        // EOSIO system accounts
        name("eosio.stake"),
        name("eosio.names"),
        name("eosio.ram"),
        name("eosio.rex"),
        name("eosio")};

    if (to != get_self() || ignore.find(from) != ignore.end()) {
        return;
    }

    if (asset_ids.size() != 1) {
        check(false, "Only one asset can be transferred at a time");
    }

    if (memo == "hatch") {
        check_unbox_egg(from, asset_ids[0]);
    } else {
        check(false, "invalid memo");
    }
}

/**
 * @brief Check if the asset is a ChickEgg and unbox it
 * 
 * @param from 
 * @param asset_id 
 */
void babychicks::check_unbox_egg(name from, uint64_t asset_id) {
    atomicassets::assets_t own_assets = atomicassets::get_assets(get_self());

    // Verify that the asset the user sent us is a ChickEgg
    auto pack_asset_iter =
        own_assets.require_find(asset_id, "Asset could not be found");

    check(
        pack_asset_iter->template_id == babychick_constants::EGG_TEMPLATE_ID,
        "Asset is not a ChickEgg"
    );

    unbox_egg(from, asset_id);
}

/**
 * @brief Unbox an egg
 * 
 * @param from 
 * @param asset_id 
 */
void babychicks::unbox_egg(name from, uint64_t asset_id) {
    uint64_t signing_value = create_signing_value();

    rngqueue.emplace(get_self(), [&](auto &_queue) {
        _queue.assoc_id = asset_id;
        _queue.from = from;
        _queue.timestamp = now();
        _queue.memo = "hatch";
    });

    action(
        permission_level{get_self(), name("active")},
        orng::ORNG_CONTRACT,
        name("requestrand"),
        std::make_tuple(asset_id, signing_value, get_self())
    )
        .send();
}

/**
 * @brief Determine how to handle the Oracle response
 * 
 * @param assoc_id 
 * @param random_value 
 * @return ACTION 
 */
ACTION babychicks::receiverand(uint64_t assoc_id, checksum256 random_value) {
    // ensure that only the WAX RNG oracle can call this function
    check(
        has_auth(orng::ORNG_CONTRACT) || has_auth(get_self()),
        "Caller must be WAX RNG oracle"
    );

    auto randomqueue_itr = rngqueue.require_find(
        assoc_id, "Could not find associated randomness id"
    );

    if (randomqueue_itr->memo == "hatch") {
        rng_response_unbox_egg(assoc_id, random_value);
    } else {
        check(false, "invalid memo");
    }
}

/**
 * @brief determine a random number and mint a BabyChick
 * with a random template id
 * 
 * @param assoc_id 
 * @param random_value 
 */
void babychicks::rng_response_unbox_egg(
    uint64_t assoc_id, checksum256 random_value
) {
    auto randomqueue_itr = rngqueue.require_find(
        assoc_id, "Could not find the associated randomness id"
    );

    RandomnessProvider randomness_provider(random_value);
    uint16_t random_range = randomness_provider.get_rand(10);

    // Mint BabyChick
    if (random_range >= 9) {
        mint_baby_chick(
            randomqueue_itr->from, babychick_constants::EPIC_TEMPLATE_ID
        );
    } else if (random_range > 5) {
        mint_baby_chick(
            randomqueue_itr->from, babychick_constants::RARE_TEMPLATE_ID
        );
    } else {
        mint_baby_chick(
            randomqueue_itr->from, babychick_constants::COMMON_TEMPLATE_ID
        );
    }

    // Burn the ChickEgg
    action(
        permission_level{get_self(), name("active")},
        atomicassets::ATOMICASSETS_ACCOUNT,
        name("burnasset"),
        std::make_tuple(get_self(), assoc_id)
    )
        .send();
    
    // Delete table entry
    rngqueue.erase(randomqueue_itr);
}

/**
 * @brief Mint a BabyChick NFT
 * 
 * @param receiver 
 * @param template_id 
 */
void babychicks::mint_baby_chick(name receiver, uint32_t template_id) {
    action(
        permission_level{get_self(), name("active")},
        atomicassets::ATOMICASSETS_ACCOUNT,
        name("mintasset"),
        std::make_tuple(
            get_self(),
            babychick_constants::COLLECTION_NAME.value,
            babychick_constants::BABY_CHICK_SCHEMA_NAME.value,
            template_id,
            receiver,
            // immutable data
            (atomicassets::ATTRIBUTE_MAP){{"created_at", (uint64_t)now()}},
            // mutable data
            (atomicassets::ATTRIBUTE_MAP){},
            // backing assets
            (std::vector<asset>){}
        )
    )
        .send();
}

/**
 * @brief Create a signing value to use with the oracle request
 * 
 * @return uint64_t 
 */
uint64_t babychicks::create_signing_value() {
    // Create a signing key for the pack
    size_t size = eosio::transaction_size();
    char buf[size];
    uint32_t read = eosio::read_transaction(buf, size);

    check(
        size == read, "Signing value generation: read_transaction() has failed."
    );
    checksum256 tx_id = eosio::sha256(buf, read);
    uint64_t signing_value;
    memcpy(&signing_value, tx_id.data(), sizeof(signing_value));

    // Check if the signing_value was already used.
    // If that is the case, increment the signing_value until a non-used
    // value is found
    while (orng::signvals.find(signing_value) != orng::signvals.end()) {
        signing_value++;
    }

    return signing_value;
}