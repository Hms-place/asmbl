#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char * getBaseName(const char* myStr) {
    if (!myStr) //check for null
		return NULL;

	char *retStr = (char*) malloc(strlen(myStr) + 1);

    if (retStr == NULL) //malloc and check errors
		return NULL;

    strcpy (retStr, myStr);

	int i = strlen (retStr);
	for (; i >= 0; i--){
		if(retStr[i] == '.'){
			retStr[i] = '\0';
			return retStr;
		}
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

int baseNameLen(const char* myStr){
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

char toLower(char character){
	if(character >= 'A' && character <= 'Z')
		return character | 0x20;

	return character;
}

int endsWith(const char* string, const char* pattern){
	if(!string || !pattern)
		return 0;

	int stringLength = strlen(string);
	int patternLength = strlen(pattern);
	int	i;

	if(patternLength > stringLength)
		return 0;

	for(i = 0; i < patternLength; i++)
		if(toLower(string[stringLength - i]) != toLower(pattern[patternLength - i]))
			return 0;

	return 1;
}
