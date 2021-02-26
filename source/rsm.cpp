#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h>
#include <string.h>
#include <limits.h>

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
	folderLength[strlen(myStr)-shift] = '\0';
	
	return compPath;
}

void Help(){
	puts(" write rsm to launch dosbox");
	puts(" -help to get this message");
	puts(" -nocls to not clear the dosbox terminal (use it to see what i'm doing)");
}

int main(int argc, char *argv[]) {

	char curDirectory [PATH_MAX];
   	if (getcwd(curDirectory, sizeof(curDirectory)) == NULL){
		   puts("something went wrong");
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
		}
		else{
			puts("wrong input");
			return 0;
		}
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
	
	sprintf(command,"echo running dosBox in %s",curDirectory);
	system(command);

	//back to root to have permissions and dosbox stuff
	sprintf(
		command,
		" \"C:\\amb_GAS\\DOSBox\\dosbox.exe -noconsole\" "
		"-c \"set PATH=C:\\amb_GAS\\GAS\\BIN;C:\\amb_GAS\\ASMBL;Z:\\ \""
		"-c \"set DJGPP=C:\\amb_GAS\\GAS\\DJGPP.ENV \""

		"-c \" MOUNT C C:\\ \""
		"-c \" C:\\ \"" 
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
