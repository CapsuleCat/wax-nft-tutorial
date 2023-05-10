#include <eosio/eosio.hpp>
#include <eosio/system.hpp>
#include <guestbook.hpp>
using namespace eosio;
using namespace std;

ACTION guestbook::sign( name nm, string memo ) {
   require_auth(nm);

   guestbook_t guestbook(get_self(), get_self().value);
   guestbook.emplace(nm, [&](auto &row) {
     row.id = guestbook.available_primary_key();
     row.user = nm;
     row.memo = memo;
     row.timestamp = current_time_point().sec_since_epoch();
   });
}