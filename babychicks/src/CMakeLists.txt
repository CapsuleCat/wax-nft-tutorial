project(babychicks)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( babychicks babychicks babychicks.cpp )
target_include_directories( babychicks PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( babychicks ${CMAKE_SOURCE_DIR}/../ricardian )