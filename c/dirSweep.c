#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#define PATH_SIZE 256

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char directory[PATH_SIZE];
    char tempFileName[256];

    strncpy(tempFileName, argv[1], sizeof(tempFileName) - 1);
    tempFileName[sizeof(tempFileName) - 1] = '\0';

    printf("Using filename: %s\n", tempFileName);

    if (getcwd(directory, sizeof(directory)) == NULL) {
        perror("getcwd");
        return 1;
    }

    printf("Current directory: %s\n", directory);

    DIR *dir = opendir(".");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    int found = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, tempFileName) == 0) {
            printf("Exact match found: %s\n", entry->d_name);
            FILE* ptr;
            ptr = fopen(tempFileName, "r");
            if (ptr == NULL){
                return 1;
            }
            char buff[100]; //manually create a buffer to fill from reading out
            size_t n;
            while ((n = fread(buff, sizeof(char), sizeof(buff) - 1, ptr)) > 0) {
                buff[n] = '\0';
                printf("%s", buff);
            }
            fclose(ptr);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("File not found in current directory\n");
    }

    closedir(dir);
    return 0;
}