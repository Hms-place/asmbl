#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "asmlib.h"

int main(int argc, char *argv[]) {
	if (argc < 2){
		puts(" sup, 'm workin fine\r\n" \
		" use me to debug .exe assembly files\r\n" \
		" dsm -help if you need help");
		return 0;
	}

	if(!endsWith(argv[1], ".exe")) {
		puts("error this file is not supported, use *.exe");
		return 1;
	}

	char * toPrint = malloc(strlen(argv[1]) + 31 + 1);

	sprintf(toPrint, "gdb -x C:/amb_GAS/GAS/deb_com %s", argv[1]);
	system(toPrint);

	free(toPrint);

    return 0;
}
