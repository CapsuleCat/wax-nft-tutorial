# simplenft Project

This is a simple NFT contract that implements its own table and does not use the eosio.token contract.

This is an example of how to create a simple NFT and should not be used in production.

## Build

How to Build:

- cd to 'build' directory
- run the command 'cmake ..'
- run the command 'make'

After building:

- The built smart contract is under the 'simplenft' directory in the 'build' directory
- You can then do a 'set contract' action with 'cleos' and point in to the './build/simplenft' directory

Additions to CMake should be done to the CMakeLists.txt in the './src' directory and not in the top level CMakeLists.txt.
