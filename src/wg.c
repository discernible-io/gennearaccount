// SPDX-License-Identifier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2020 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "subcommands.h"
#include "version.h"

const char *PROG_NAME;

static const struct {
	const char *subcommand;
	int (*function)(int, const char**);
	const char *description;
} subcommands[] = {
	{ "genaccount", genaccount_main, "Generates a new private key and accountID and writes it to a file with the name accountID.json in the ~/.near-credential directory" }
};

static void show_usage(FILE *file)
{
	fprintf(file, "Usage: %s <cmd> [<args>]\n\n", PROG_NAME);
	fprintf(file, "Available subcommands:\n");
	for (size_t i = 0; i < sizeof(subcommands) / sizeof(subcommands[0]); ++i)
		fprintf(file, "  %s: %s\n", subcommands[i].subcommand, subcommands[i].description);
	fprintf(file, "You may pass `--help' to any of these subcommands to view usage.\n");
}

int main(int argc, const char *argv[])
{
	PROG_NAME = argv[0];

	if (argc == 2 && (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version") || !strcmp(argv[1], "version"))) {
		printf("wireguard-tools v %s - https://github.com/alanesmizi/cableguard-wgtools\n", WIREGUARD_TOOLS_VERSION);
		return 0;
	}
	if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help") || !strcmp(argv[1], "help"))) {
		show_usage(stdout);
		return 0;
	}

	if (argc == 1)
		return genaccount_main(1, (const char *[]){ "genaccount", NULL });

	for (size_t i = 0; i < sizeof(subcommands) / sizeof(subcommands[0]); ++i) {
		if (!strcmp(argv[1], subcommands[i].subcommand))
			return subcommands[i].function(argc - 1, argv + 1);
	}

	fprintf(stderr, "Invalid subcommand: `%s'\n", argv[1]);
	show_usage(stderr);
	return 1;
}