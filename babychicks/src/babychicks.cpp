#include <babychicks.hpp>

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