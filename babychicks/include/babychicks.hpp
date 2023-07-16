#include "atomicassets.hpp"
#include "orng.hpp"
#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <eosio/system.hpp>
using namespace eosio;

namespace babychick_constants {
static constexpr symbol CORE_TOKEN_SYMBOL = symbol("WAX", 8);
// Convert 2000 WAXP to asset precision
static constexpr uint64_t EGG_PRICE_IN_WAX = 200000000;
static constexpr name COLLECTION_NAME = name("babychicknft");
static constexpr name EGG_SCHEMA_NAME = name("chickegg");
static constexpr name BABY_CHICK_SCHEMA_NAME = name("babychick");
static constexpr uint32_t EGG_TEMPLATE_ID = 629366;
static constexpr uint32_t EPIC_TEMPLATE_ID = 629367;
static constexpr uint32_t RARE_TEMPLATE_ID = 629368;
static constexpr uint32_t COMMON_TEMPLATE_ID = 629369;
} // namespace babychick_constants

CONTRACT babychicks : public contract {
  public:
    using contract::contract;

    [[eosio::on_notify("eosio.token::transfer")]] void receive_token_transfer(
        name from, name to, asset quantity, std::string memo
    );

    [[eosio::on_notify("atomicassets::transfer")]] void receive_asset_transfer(
        name from, name to, std::vector<uint64_t> asset_ids, std::string memo
    );

    ACTION receiverand(uint64_t assoc_id, checksum256 random_value);
    using receiverand_action =
        action_wrapper<"receiverand"_n, &babychicks::receiverand>;

    ACTION airdropegg(name receiver);
    using airdropegg_action =
        action_wrapper<"airdropegg"_n, &babychicks::airdropegg>;

  private:
    void mint_egg_check(name receiver, asset quantity);
    void mint_egg(name receiver);
    void mint_baby_chick(name receiver, uint32_t template_id);

    void check_unbox_egg(name from, uint64_t asset_id);
    void unbox_egg(name from, uint64_t asset_id);
    void rng_response_unbox_egg(uint64_t assoc_id, checksum256 random_value);

    uint64_t create_signing_value();

    TABLE rngqueue_s {
        uint64_t assoc_id;
        name from;
        uint32_t timestamp;
        std::string memo;

        uint64_t primary_key() const { return assoc_id; }
        uint64_t by_from() const { return from.value; }
    };
    typedef multi_index<name("rngqueue"), rngqueue_s> rngqueue_t;
    rngqueue_t rngqueue = rngqueue_t(get_self(), get_self().value);
};