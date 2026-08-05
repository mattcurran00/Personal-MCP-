#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 256

/**
 * Program to do a sweep of directories in order to find a file just based on name 
 */

int main (int argc, char *argv[]){

    char directory[PATH_MAX];
    char tempFileName[256]; 
    strncpy(tempFileName, argv[1], sizeof(tempFileName) - 1);
    tempFileName[sizeof(tempFileName) - 1] = '\0';

    if(argc < 2) {
        printf("\nUsing filename: %s", argv[1]);
    }

    //FILE *tmp = popen("ls", "r");  //open a file, command ls and read result. 

    if(getcwd(directory, sizeof(directory)) == NULL){
        perror("getcwd");
        return 1;
    }

    printf("\nCurrent Directory: %s", directory);
    return 0;
}