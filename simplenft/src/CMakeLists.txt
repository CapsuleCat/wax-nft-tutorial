project(simplenft)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( simplenft simplenft simplenft.cpp )
target_include_directories( simplenft PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( simplenft ${CMAKE_SOURCE_DIR}/../ricardian )