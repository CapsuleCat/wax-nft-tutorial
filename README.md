# WAX NFT Smart Contract Tutorials

This repository contains a collection of tutorials for creating NFTs on the WAX blockchain.

You can read the full documentation at [our Dev.to collection](https://dev.to/idmontie/series/23860).

## Getting Started

### Prerequisites

Get the WAX Docker image:

```bash
docker pull waxteam/dev
docker run -it --name wax-tutorial --publish 8888:8888 -v $(pwd):/wax waxteam/dev bash
```

## Compiling

You can compile any contract with:

```bash
cd <dir>/build
cmake ..
make
```

## License

See [License](LICENSE.md) for license information.
