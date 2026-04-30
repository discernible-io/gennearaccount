# NEAR implicit account generator

The `gennearaccount` tool creates a NEAR implicit account: it writes a JSON key file and prints the new account id on standard output.

## License

This project is released under the [GPLv2](COPYING).

## How to install from source

From this repository’s root (the `gennearaccount` directory):

- `make -C ./src -j$(nproc)`
- `sudo make -C ./src install` (installs `gennearaccount` under `$(PREFIX)/bin`, default `/usr/bin`)

The build only needs a C compiler and standard headers; no extra crypto libraries are required.

### Debian package

From the same root:

```bash
dpkg-buildpackage -us -uc -b
```

The binary package is written to the parent directory (e.g. `../gennearaccount_1.0_amd64.deb`).

## Usage
### Top-level

| Command | Behavior |
|--------|----------|
| `gennearaccount --help` (or `-h`, `help`) | Lists subcommands. |
| `gennearaccount --version` (or `-v`, `version`) | Prints version string. |
- **Optional `DIRECTORY`**: where to write `<implicit_account_id>.json`. If omitted, the current directory (`.`) is used.
- **Directory creation**: if `DIRECTORY` does not exist, a single directory is created (`mkdir` with mode `0755`). Parent directories are not created for you (not a full `mkdir -p`).
- **Aside from `--help` / `-h`**, the only optional argument is `DIRECTORY`.

### Output
- **Standard output**: one line after success, for example:  
  `NEAR implicit account created: f6cf27149c92207d46a9fd9b3ddf67e62367f180a583af0ab5211f6ec3e9cf47`  
  The hex string is the implicit account id (64 hex characters, same as in the JSON file).

- **File**: `DIRECTORY/<implicit_account_id>.json` containing a single JSON object with:
  - `implicit_account_id` — hex-encoded public key (implicit account id)
  - `public_key` — `ed25519:` + Base58-encoded public key
  - `private_key` — `ed25519:` + Base58-encoded extended secret key

Errors and usage messages go to **stderr**.