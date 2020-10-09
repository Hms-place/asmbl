#include<stdlib.h> 
#include<stdio.h> 
#include<unistd.h>
#include <string.h>
#include <limits.h>

char * getDosBoxCompPath(const char * myStr){
	if(!myStr)
		return NULL;
	int count = 1;
	char * ret = new char[strlen(myStr) + 1];
	int shift = 0;
	for (int i = 0; i < strlen(myStr); i++){
		if(myStr[i] == '\\' || myStr[i] == '/')
			count = 1;
		if(count == 10){
			ret[i - 1 - shift] = '1';
			ret[i - 2 - shift] = '~';
		}
		if(count < 10)
			ret[i - shift] = myStr[i];
		else
			shift++;
		count++;
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
	char toprint[PATH_MAX];
	sprintf(toprint,"echo running dosBox in %s",cwd);
	system(toprint);
	char * cur = getDosBoxCompPath(cwd);
	//back to root to have permissions and dosbox shit
	sprintf(toprint," CD\\ && C:\\amb_GAS\\DOSBox\\dosbox.exe -noconsole -c \"MOUNT C .\"  -c \"C:\"  -c \"CD %s\" -c \"set PATH=C:\\amb_GAS\\GAS\\BIN;C:\\amb_GAS\\ASMBL;Z:\\ \" -c \"set DJGPP=C:\\amb_GAS\\GAS\\DJGPP.ENV \" %s",cur,clear);
	system(toprint);
}
