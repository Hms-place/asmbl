#include <stdlib.h>
#include <stdio.h>
#include "asmlib.h"

void Help(){
	// asm erjh.s -o name.exe -l -help
	puts("asm filename.s [-o outputname.exe] [-l]");
	puts("-help");
	puts("-o lets you decide the output name");
	puts("-l gets you an outputname.lis file with infos");
}

int main(int argc, char *argv[]) {
	char * toCompile = argv[1];
	char toPrint [500];

	if (argc < 2){
		puts("hello i'm your assembly assembler");
		puts("use me to compile .s files");
		puts("asm -help if you need help");
		return 0;
	}

	if(strncmp(toCompile, "-help", 10) == 0){
		Help();
		return 0;
	}

	char * outputFileName = NULL;			//output name
	int makeListato = 0;    				//write assembled code
	int isOutputFileSpecified = 0;			//tells you if you've found -o
	int i;

	for (i = 2; i < argc; i++){
		int isParameter = argv[i][0] == '-';
		if(isOutputFileSpecified){
			if(isParameter){
				puts("you must specify a filename after -o");
				return 1;
			}
			else{
				outputFileName = (char *) malloc(strlen(argv[i]) + 1);
				strcpy(outputFileName, argv[i]);
			}
		}

		if(isParameter || isOutputFileSpecified){ //is a parameter
			makeListato = strncmp(argv[i], "-l", 5) == 0 || makeListato;
			isOutputFileSpecified = strncmp(argv[i], "-o", 5) == 0;
		}
		else{
			sprintf(toPrint,"%s is not a valid parameter", argv[i]);
			puts(toPrint);
		}
	}

	// if the last thing that you find is a -o there are some probs
	if(isOutputFileSpecified){
		puts("you must specify a filename after -o");
		return 2;
	}

	//files check
	if(!endsWith(toCompile, ".s")) {
		puts("error: this file is not supported, use *.s");
		return 3;
	}

	char * targetBaseName = getBaseName(toCompile);
	char * outputBaseName = (outputFileName) ? getBaseName(outputFileName) : targetBaseName;

	if(outputFileName && baseNameLen(outputBaseName) > 8){
		puts("error: the output name is too long");
		return 4;
	}

	//Add .exe to output basename
	outputFileName = realloc(outputFileName, strlen(outputBaseName) + 4 + 1);
	sprintf(outputFileName, "%s.exe", outputBaseName);

	char * listatoFileName = (char *) malloc(strlen(outputBaseName) + 10);
	if(makeListato)
		sprintf(listatoFileName, ">>%s.lis", outputBaseName);
	else
		strcpy(listatoFileName, ">NUL");

	sprintf(toPrint, "gcc %s -o %s -Wa,-a -g %s", toCompile, outputFileName, listatoFileName);
	puts(toPrint);
	system(toPrint);
	
	free(targetBaseName);
	free(outputBaseName);
	
	free(listatoFileName);
	free(outputFileName);
    
	return 0;
}
