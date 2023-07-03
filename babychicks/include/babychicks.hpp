#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <eosio/system.hpp>
#include "atomicassets.hpp"
using namespace eosio;

namespace babychick_constants {
static constexpr symbol CORE_TOKEN_SYMBOL = symbol("WAX", 8);
// Convert 2000 WAXP to asset precision
static constexpr uint64_t EGG_PRICE_IN_WAX = 200000000;
static constexpr name COLLECTION_NAME = name("babychicknft");
static constexpr name EGG_SCHEMA_NAME = name("chickegg");
static constexpr uint32_t EGG_TEMPLATE_ID = 629366;
} // namespace babychick_constants

CONTRACT babychicks : public contract {
  public:
    using contract::contract;

    [[eosio::on_notify("eosio.token::transfer")]] void receive_token_transfer(
        name from, name to, asset quantity, std::string memo
    );

    ACTION airdropegg(name receiver);
    using airdropegg_action =
        action_wrapper<"airdropegg"_n, &babychicks::airdropegg>;

  private:
    void mint_egg_check(name receiver, asset quantity);
    void mint_egg(name receiver);
};