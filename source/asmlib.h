#include<stdlib.h> 
#include <string.h>
#include <unistd.h>

char *getName(const char* myStr) {
    if (!myStr) //check for null
		return NULL;
	char *retStr;
    if ((retStr = (char*) malloc (strlen (myStr) + 1)) == NULL) //malloc and check errors
		return NULL;
    strcpy (retStr, myStr);
	int i = 0;
	for (i = strlen (retStr); i >= 0; i--){
		if(retStr[i] == '.')
			retStr[i] = '\0';
	}
    return retStr;
}
char *getFolder(const char* myStr) {
    if (!myStr) //check for null
		return NULL;
	char *retStr;
    if ((retStr = (char*) malloc (strlen (myStr) + 1)) == NULL) //malloc and check errors
		return NULL;
    strcpy (retStr, myStr);
	int i = 0;
	for (i = strlen (retStr); i >= 0; i--){
		if(retStr[i] == '\\' || retStr[i] == '/' || i == 0){
            retStr[i] = '\0';
        }
	}
    return retStr;
}
int Len(const char* myStr){
	if(!myStr)
		return -1;
	int i = 0;
	int count = 0;
	for (i = strlen(myStr); i >= 0; i--){
		if(myStr[i] == '/' || myStr[i] == '\\' )
			break;
		count++;
	}
	return count;
}
int checkExtExe(const char* myStr){
	if(!myStr)
		return 0;
	int strl = strlen(myStr);
	if (strl < 4)
		return 0;
	int last = myStr[strl - 1]=='e' || myStr[strl - 1]=='E';
	int lastt = myStr[strl - 2]=='x' || myStr[strl - 2]=='X';
	int lasttt = myStr[strl - 3]=='e' || myStr[strl - 3]=='E';
	return last && lastt && lasttt && myStr[strl - 4]=='.';
}
int checkExtS(const char* myStr){
	if (!myStr) //check for null
		return 0;
	int strl = strlen(myStr);
	return (myStr[strl - 1]=='s' || myStr[strl - 1]=='S') && myStr[strl - 2]=='.';
}
