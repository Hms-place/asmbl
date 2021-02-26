#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fstream>

char * getDosBoxCompatiblePath(const char * myStr){
	if(!myStr)
		return NULL;
	
	char * compPath = new char[strlen(myStr) + 1];
	
	//used to skip every char that is not shown in dosBox
	int shift = 0;
	
	//used to skip every char that is a space
	int spaceshift = 0;

	int folderLength = 1;
	
	for (int i = 0; i < strlen(myStr); i++){
		
		int shifted = i - shift;
		
		//if you find a new folder reset the folderLength
		if(myStr[i] == '\\' || myStr[i] == '/')
			folderLength = 1;
		
		//if the folderLength reaches 10 set the last 2 chars to be ~1 
		if(folderLength == 10){
			compPath[shifted - 1] = '1';
			compPath[shifted - 2] = '~';
		}

		//if the folderLength is currently fine set the char to be as myStr
		if(folderLength < 10)
			compPath[shifted - spaceshift] = myStr[i];
		else
			shift++;
		
		//every cicle add 1 to folderLength
		folderLength++;

		//every time you find a space inc i, folderLength and spaceShift
		while(i < strlen(myStr) - 1 && myStr[i + 1] == ' '){
			i++;
			folderLength++;
			spaceshift++;
		}
	}

	//set the last char to end string
	compPath[strlen(myStr)-shift] = '\0';
	
	return compPath;
}
inline bool exists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}
void install(){
	system(
		" \"C:\\amb_GAS\\DOSBox\\dosbox.exe -noconsole\" " 
		"-c \"MOUNT C C:\\\" " 
		"-c \"C:\\ \""
		"-c \"set DJGPP=C:\\amb_GAS\\GAS\\DJGPP.ENV \""
		"-c \"set PATH=C:\\amb_GAS\\GAS\\BIN\" "
		"-c \"cd github\\asmbl\\source\" "
		"-c \"gcc -o C:\\amb_GAS\\ASMBL\\execs\\asm.exe C:\\amb_GAS\\ASMBL\\source\\asm.c C:\\amb_GAS\\ASMBL\\source\\asmlib.h\" "
		"-c \"gcc -o C:\\amb_GAS\\ASMBL\\execs\\dsm.exe C:\\amb_GAS\\ASMBL\\source\\dsm.c C:\\amb_GAS\\ASMBL\\source\\asmlib.h\" "
		"-c \"exit\""
	);
}
void Help(){
	puts("write rsm to launch dosbox");
	puts("-check to check if asm and dsm are installed");
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
			if(exists("C:\\amb_GAS\\ASMBL\\execs\\asm.exe") && exists("C:\\amb_GAS\\ASMBL\\execs\\dsm.exe")){
				puts("asm and dsm seem to be correctly installed");
				return 0;
			}
			install();
			return 0;

		}else if(strcmp("-check",argv[1]) == 0){
			if(exists("C:\\amb_GAS\\ASMBL\\execs\\asm.exe") && exists("C:\\amb_GAS\\ASMBL\\execs\\dsm.exe")){
				puts("asm and dsm seem to be correctly installed");
				return 0;
			}else{
				puts("asm and dsm aren't installed");
				return 0;
			}
		}else{
			puts("wrong input");
			return 0;
		}
	}

	//if asm and dsm are not compiled compile them
	if(!exists("C:\\amb_GAS\\ASMBL\\execs\\asm.exe") || !exists("C:\\amb_GAS\\ASMBL\\execs\\dsm.exe"))
		install();
	
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
	
	sprintf(command,"echo running dosBox in %s",curDirectory);
	system(command);

	//back to root to have permissions and dosbox stuff
	sprintf(
		command,
		" \"C:\\amb_GAS\\DOSBox\\dosbox.exe -noconsole\" " 
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
	
	free(command);
	free(compatiblePath);
	free(toMount);
}
