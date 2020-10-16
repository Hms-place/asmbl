#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h>
#include <string.h>
#include <limits.h>

char * getDosBoxCompPath(const char * myStr){
	if(!myStr)
		return NULL;
	int count = 1;
	char * ret = new char[strlen(myStr) + 1];
	int shift = 0;
	int spaceshift = 0;
	for (int i = 0; i < strlen(myStr); i++){
		int shifted = i - shift;
		if(myStr[i] == '\\' || myStr[i] == '/')
			count = 1;
		if(count == 10){
			ret[shifted - 1] = '1';
			ret[shifted - 2] = '~';
		}
		if(count < 10)
			ret[shifted - spaceshift] = myStr[i];
		else
			shift++;
		count++;
		while(i < strlen(myStr) - 1 && myStr[i + 1] == ' '){
			i++;
			count++;
			spaceshift++;
		}
	}
	ret[strlen(myStr)-shift] = '\0';
	return ret;
}
void Help(){
	// rsm -nocls -help
	puts(" asm filename.s [-help] [-nocls] \r\n -help");
	puts(" -nocls to not clear the dosbox terminal (used to check errors)");
}
int main(int argc, char *argv[]) {
	char cwd [PATH_MAX];
   	if (getcwd(cwd, sizeof(cwd)) == NULL){
		   puts("something went wrong");
		   return 1;
	}
	char clear[50];
	strcpy(clear,"-c \"cls\"");
	if(argc > 1){
		if(strcmp("-help",argv[1]) == 0){
			Help();
			return 0;
		}else if(strcmp("-nocls",argv[1]) == 0)
			clear[0] = 0;
		else{
			puts("wrong input");
			return 0;
		}
	}
	char toprint[500];
	char * cur = getDosBoxCompPath(cwd);
	if(cur[0] != 'C'){
		puts("sorry you can use dosBox only in C subdirectories");
		return 0;
	}
	sprintf(toprint,"echo running dosBox in %s",cwd);
	system(toprint);
	//back to root to have permissions and dosbox shit
	sprintf(toprint,"CD\\ && C:\\amb_GAS\\DOSBox\\dosbox.exe -noconsole -c \"MOUNT C .\"  -c \"C:\" -c \"CD %s\" -c \"set PATH=C:\\amb_GAS\\GAS\\BIN;C:\\amb_GAS\\ASMBL;Z:\\ \" -c \"set DJGPP=C:\\amb_GAS\\GAS\\DJGPP.ENV \" %s",cur, clear);
	system(toprint);
}
