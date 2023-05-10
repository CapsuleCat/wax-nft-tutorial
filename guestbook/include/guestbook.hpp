#include <eosio/eosio.hpp>
using namespace eosio;
using namespace std;

CONTRACT guestbook : public contract {
   public:
      using contract::contract;

      ACTION sign( name nm, string memo );

      TABLE guestbook_s {
        uint64_t id;
        name user;
        string memo;
        uint64_t timestamp;

        uint64_t primary_key() const { return id; }
      };
      typedef multi_index<name("guestbook"), guestbook_s> guestbook_t;
      guestbook_t guestbook = guestbook_t(get_self(), get_self().value);
};