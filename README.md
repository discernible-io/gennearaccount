# NEAR implicit account generator

![banner](banner.png)

[![Get a Passport](https://img.shields.io/badge/Get%20a%20Passport-purchase.identyclaw.com-FF4500)](https://purchase.identyclaw.com)

**Step 1 of [IdentyClaw](https://www.discernible.io/#get-started) enrollment:** create a NEAR implicit account with this CLI, then mint a Passport once at [purchase.identyclaw.com](https://purchase.identyclaw.com) (buy once — no subscription). Enrollment summary: [api.identyclaw.com/.well-known/enrollment](https://api.identyclaw.com/.well-known/enrollment).

The `gennearaccount` tool writes a JSON key file and prints the new implicit account id on standard output.

> **OpenClaw alternative:** OpenClaw operators can use [`openclaw-identyclaw-plugin`](https://github.com/discernible-io/openclaw-identyclaw-plugin) `generate-near-account` instead — same JSON credential layout.

> **Production deploy:** [`identyclaw-agents`](https://github.com/discernible-io/identyclaw-agents) runs account generation inside the container via `./identyclaw.sh generate-near-account`.

## Install

### From GitHub Releases

Download the `.deb` package from [GitHub Releases](https://github.com/discernible-io/gennearaccount/releases) (asset name `gennearaccount_*_amd64.deb`), then install:

```bash
sudo dpkg -i gennearaccount_*_amd64.deb
```

### From source

From this repository’s root (the `gennearaccount` directory):

- `make -C ./src -j$(nproc)`
- `sudo make -C ./src install` (installs `gennearaccount` under `$(PREFIX)/bin`, default `/usr/bin`)

The build only needs a C compiler and standard headers; no extra crypto libraries are required.

#### Debian package (build your own)

```bash
dpkg-buildpackage -us -uc -b
```

The binary package is written to the parent directory (e.g. `../gennearaccount_2026.05.17_amd64.deb`).

## Usage

| Command | Behavior |
|--------|----------|
| `gennearaccount --help` (or `-h`, `help`) | Lists subcommands. |
| `gennearaccount --version` (or `-v`, `version`) | Prints version string. |
| `gennearaccount [DIRECTORY]` | Writes `<implicit_account_id>.json` under `DIRECTORY`. |

- **Optional `DIRECTORY`**: where to write `<implicit_account_id>.json`. If omitted, the current directory (`.`) is used.
- **Directory creation**: if `DIRECTORY` does not exist, a single directory is created (`mkdir` with mode `0755`). Parent directories are not created for you (not a full `mkdir -p`).

### Output

- **Standard output**: one line after success, for example:

  `NEAR implicit account created: f6cf27149c92207d46a9fd9b3ddf67e62367f180a583af0ab5211f6ec3e9cf47`

  The hex string is the implicit account id (64 hex characters, same as in the JSON file). The private key is never printed.

- **File**: `DIRECTORY/<implicit_account_id>.json` — see [JSON compatibility](#json-compatibility) below.

Errors and usage messages go to **stderr**.

## JSON compatibility

The credential file is a single JSON object with these fields — the same layout used by [`openclaw-identyclaw-plugin`](https://github.com/discernible-io/openclaw-identyclaw-plugin) `generate-near-account`:

| Field | Description |
|-------|-------------|
| `implicit_account_id` | Hex-encoded public key (64 characters); NEAR implicit account id |
| `public_key` | `ed25519:` + Base58-encoded public key |
| `private_key` | `ed25519:` + Base58-encoded extended secret key |

Example filename: `f6cf27149c92207d46a9fd9b3ddf67e62367f180a583af0ab5211f6ec3e9cf47.json`.

## Security

- **File permissions:** restrict credential JSON to the owning user — `chmod 0600` on each file (and `umask 077` before running if you want new files created that way). Never leave keys world- or group-readable.
- **Git and backups:** never commit `*.json` credential files or paste private keys into chat, tickets, or CI logs. Add credential directories to `.gitignore`.
- **Private key on disk only:** stdout reports the implicit account id; the extended secret key exists only in the JSON file on disk.

## License

This project is released under the [GPLv2](COPYING).

---

[discernible.io](https://www.discernible.io) · [sdk/verify-hola](https://github.com/discernible-io/sdk/tree/main/verify-hola) · [enrollment guide](https://www.discernible.io/#enroll)
