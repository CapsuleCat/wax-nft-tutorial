#include <simplenft.hpp>

using namespace std;

ACTION simplenft::create(string cat_name) {
   require_auth(get_self());

   // Check that the cat name doesn't already exist
   auto idx = cats.get_index<name("bycatname")>();
   auto cat_itr = idx.find(std::hash<string>{}(cat_name));
   check(cat_itr == idx.end(), "Cat name already exists");

   // Create the new cat
   cats.emplace(get_self(), [&](auto &cat) {
      cat.token_id = cats.available_primary_key();
      cat.issuer = get_self();
      cat.cat_name = cat_name;
   });
}

ACTION simplenft::transfer(uint64_t token_id, name to) {
   // Check that the token exists
   auto cat_itr = cats.find(token_id);
   check(cat_itr != cats.end(), "Cat does not exist");

   // Check that the sender owns the token
   check(cat_itr->issuer == get_self(), "You do not own this cat");

   // Check that the recipient exists
   check(is_account(to), "Recipient account does not exist");

   // Transfer the token to the recipient
   cats.modify(cat_itr, get_self(), [&](auto &cat) {
      cat.issuer = to;
   });
}