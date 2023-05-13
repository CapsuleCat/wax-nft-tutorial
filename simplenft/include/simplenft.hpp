#include <eosio/eosio.hpp>

using namespace eosio;
using namespace std;

CONTRACT simplenft : public contract {
   public:
      using contract::contract;

      ACTION create(string cat_name);
      ACTION transfer(uint64_t token_id, name to);

      TABLE cat_nft_s {
        uint64_t token_id;
        name issuer;
        string cat_name;

        uint64_t primary_key() const { return token_id; }
        uint64_t by_cat_name() const { return std::hash<string>{}(cat_name); }
      };

      typedef eosio::multi_index<
          name("cats"), cat_nft_s,
          indexed_by<name("bycatname"), const_mem_fun<cat_nft_s, uint64_t,
                                                      &cat_nft_s::by_cat_name>>>
          cat_nft_t;
      cat_nft_t cats = cat_nft_t(get_self(), get_self().value);
};