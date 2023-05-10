project(guestbook)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( guestbook guestbook guestbook.cpp )
target_include_directories( guestbook PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( guestbook ${CMAKE_SOURCE_DIR}/../ricardian )