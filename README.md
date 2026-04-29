![cableguard logo banner](./banner.png)

# NEAR implicit account generator
This repository is focused on generating NEAR protocol implicit account JSON files with the account ID and key pair, stored in the `~/.near-credentials/$BLOCKCHAIN_ENV` directory.

## License
This project is released under the [GPLv2](COPYING).
More information may be found at [WireGuard.com](https://www.wireguard.com/).**

## How to Install from Source
You may need to install libssl-dev with: sudo apt-get install libssl-dev

From the cgtools directory where the source code is downloaded
- make -C ./src -j$(nproc)
- sudo make -C ./src install

With the command
- nearaccountgenerator --help
you should get
- the account generator usage and `genaccount` command

##How to install form Deb package
wget https://cableguard.fra1.digitaloceanspaces.com/cgtools_00.90.53_amd64.deb
sudo apt install ./cgtools_00.90.53_amd64.deb

## How to Use
Set the blockchain network first:
`export BLOCKCHAIN_ENV=testnet` (or `mainnet`)

Then run:
`nearaccountgenerator genaccount`

If you run `nearaccountgenerator` with no arguments, it defaults to generating an account.

# Cableguard Ecosystem
    Cableguard RODITVPN: RODiT and VPN manager
    Cableguard TOOLS: local VPN tunnel configuration
    Cableguard TUN: VPN tunnels
    Cableguard FORGE: RODiT minter


---
<sub><sub><sub><sub>WireGuard is a registered trademark of Jason A. Donenfeld. Cableguard is not sponsored or endorsed by Jason A. Donenfeld.</sub></sub></sub></sub>