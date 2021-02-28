#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fstream>
#include <iostream>


char * getDosBoxCompatiblePath(const char * myStr){
	if(!myStr)
		return NULL;	

	int shift = 0;
	int spaceshift = 0;

	int strl = strlen(myStr);
	int folderLength = 1;
    int spaces = 0;
	char * compPath = new char[strl + 1];

    int shifted = 0;
	
	for (int i = 0; i <= strl; i++){
		

		shifted = i - shift - spaceshift;
		
        //folder end
		if(i == strl || myStr[i] == '\\' || myStr[i] == '/' ){
            if(i == strl - 1)
                folderLength++;
            
            //if the folderLength reaches 10 set the last 2 chars to be ~1 
            if(folderLength - spaces >= 10 || folderLength - spaces>= 9 && spaces > 0){
                compPath[shifted] = '\\'; 
                compPath[shifted - 1] = '1';
                compPath[shifted - 2] = '~';
            }else if (folderLength >= 10 && folderLength - spaces == 8 ||  folderLength - spaces == 7){
                if(folderLength - spaces == 7){
                    shift -= 2;
                    shifted += 2;
                }else {
                    shift -= 1;
                    shifted += 1;
                }

                compPath[shifted] = '\\';
                compPath[shifted - 1] = '1';
                compPath[shifted - 2] = '~';
            }else
                compPath[shifted] = '\\';
            folderLength = 1;
            spaces = 0;
            continue;
        }

		//if the folderLength is currently fine set the char to be as myStr
		if(folderLength - spaces < 10)
			compPath[shifted] = myStr[i];
		else
			shift++;
		//every cicle add 1 to folderLength
		folderLength++;

		//every time you find a space inc i, folderLength and spaceShift
		while(i < strl - 1 && myStr[i + 1] == ' '){
			i++;
			folderLength++;
            spaces++;
			spaceshift++; 
		}
	}

	//set the last char to end string
	compPath[shifted] = '\0';
	
	return compPath;
}

inline bool exists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void install(){
	if(!exists("C:\\amb_GAS\\ASMBL\\source\\asm.c") || !exists("C:\\amb_GAS\\ASMBL\\source\\dsm.c") || !exists("C:\\amb_GAS\\ASMBL\\source\\asmlib.h")){
		puts("error: cannot find source files");
		return;
	}
	system(
		"C:\\amb_GAS\\DOSBox\\dosbox.exe -noconsole " 
		"-c \"cls\" "
		"-c \"MOUNT C C:\\\" " 
		"-c \"C:\\ \""
		"-c \"set DJGPP=C:\\amb_GAS\\GAS\\DJGPP.ENV \""
		"-c \"set PATH=C:\\amb_GAS\\GAS\\BIN\" "
		"-c \"gcc C:\\amb_GAS\\ASMBL\\source\\asm.c C:\\amb_GAS\\ASMBL\\source\\asmlib.h -o C:\\amb_GAS\\ASMBL\\execs\\asm.exe\" "
		"-c \"gcc C:\\amb_GAS\\ASMBL\\source\\dsm.c C:\\amb_GAS\\ASMBL\\source\\asmlib.h -o C:\\amb_GAS\\ASMBL\\execs\\dsm.exe\" "
		"-c \"exit\""
	);
}
void Help(){
	puts("write rsm to launch dosbox");
	puts("-install to install asm and dsm");
	puts("-help to get this message");
	puts("-nocls to not clear the dosbox terminal (use it to see what i'm doing)");
}

int main(int argc, char *argv[]) {

	char curDirectory [PATH_MAX];
   	if (getcwd(curDirectory, sizeof(curDirectory)) == NULL){
		   puts("something went wrong");
		   return 1;
	}

	if(!exists("C:\\amb_GAS\\DOSBox\\dosbox.exe")){
		puts("error: install dosbox to use this software (C:\\amb_GAS\\DOSBox\\dosbox.exe not found)");
		return 1;
	}
	char clear [] = "-c \"cls\"";

	if(argc > 1){
		if(strcmp("-help",argv[1]) == 0){
			Help();
			return 0;
		}else if(strcmp("-nocls",argv[1]) == 0){
			// clear the string
			clear[0] = '\0';
		}else if(strcmp("-install",argv[1]) == 0){
			install();
			return 0;
		}else{
			puts("wrong input");
			return 0;
		}
	}

	//if asm and dsm are not compiled give error
	if(!exists("C:\\amb_GAS\\ASMBL\\execs\\asm.exe") || !exists("C:\\amb_GAS\\ASMBL\\execs\\dsm.exe")){
		puts("error: asm and dsm aren't installed");
		puts("do you want to install them? [Y/N]");
		char * resp;
		std::cin >> resp;
		if(strcmp(resp, "Y") == 0 || strcmp(resp, "y") == 0)
			install();
		return 0;
	}
	
	//set 500 to the correct value
	char * command = (char *) malloc(strlen(curDirectory) + 500 + 1);
	char * compatiblePath = getDosBoxCompatiblePath(curDirectory);
	char * toMount = (char *) malloc(15);
	char disc = compatiblePath[0];

	if(disc != 'C')
		sprintf(
			toMount,
			"-c \"MOUNT %c %c:\\ \" "
			"-c \" %c:\\ \"", 
			disc, 
			disc,
			disc
		);
	else
		toMount[0] = '\0';
	
	sprintf(command,"echo v 1.1 running dosBox in %s",curDirectory);
	system(command);

	sprintf(
		command,
		"C:\\amb_GAS\\DOSBox\\dosbox.exe -noconsole " 
		"-c \"cls\""
		"-c \" MOUNT C C:\\ \""
		"-c \" C:\\ \"" 
		
		"-c \"set PATH=C:\\amb_GAS\\GAS\\BIN;C:\\amb_GAS\\ASMBL\\execs;Z:\\ \""
		"-c \"set DJGPP=C:\\amb_GAS\\GAS\\DJGPP.ENV \""

		"%s"
		
		"-c \"CD %s\""
		"%s",

		toMount,
		compatiblePath, 
		clear
	);
	
	system(command);
	puts(command);
	free(command);
	free(compatiblePath);
	free(toMount);
}
