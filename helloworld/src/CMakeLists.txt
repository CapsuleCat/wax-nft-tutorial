project(helloworld)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( helloworld helloworld helloworld.cpp )
target_include_directories( helloworld PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( helloworld ${CMAKE_SOURCE_DIR}/../ricardian )