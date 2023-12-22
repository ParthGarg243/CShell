#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    char *directory_name;
    int created;
    char cwd_path[250];

    if (argc == 2) {
        directory_name = malloc(strlen(argv[1]) + 3);
        if (directory_name == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            return 1;
        }
        strcpy(directory_name, "./");
        strcat(directory_name, argv[1]);
        DIR* directory = opendir(directory_name);
        if (directory) {
            fprintf(stderr, "Error: Directory already exists\n");
            closedir(directory);
        }
        else {
            created = mkdir(directory_name, 0755);
            if (!created) {
                if (!chdir(directory_name)) {
                    ;
                }
                else {
                    fprintf(stderr, "Error: Couldn't change directory\n"); 
                }
            }
            else {
                fprintf(stderr, "Error: Couldn't create directory\n");
            }
        }
    }
    else if (argc == 3) {
        directory_name = malloc(strlen(argv[2]) + 3); // Add space for "./" and null-terminator
        if (directory_name == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            return 1;
        }
        strcpy(directory_name, "./");
        strcat(directory_name, argv[2]);
        DIR* directory = opendir(directory_name);
        if (!strcmp(argv[1], "-r")) {
            if (directory) {
                closedir(directory);
                if (rmdir(directory_name) == 0) {
                } 
                else {
                    fprintf(stderr, "Error: Couldn't remove directory\n");
                }
            }
            created = mkdir(directory_name, 0755);
            if (!created) {
                if (!chdir(directory_name)) {
                    ;
                }
                else {
                    fprintf(stderr, "Error: Couldn't change directory\n");
                }
            }
            else {
                fprintf(stderr, "Error: Couldn't create directory\n");
            }
        } 
        else if (!strcmp(argv[1], "-v")) {
            if (directory) {
                fprintf(stderr, "Error: Directory already exists\n");
                closedir(directory);
            }
            else {
                created = mkdir(directory_name, 0755);
                if (!created) {
                    fprintf(stdout, "Directory created\n");
                    if (!chdir(directory_name)) {
                        fprintf(stdout, "Changed current working directory\n");
                        fprintf(stdout, "Current Working Directory: %s\n", getcwd(cwd_path, sizeof(cwd_path)));
                    }
                    else {
                        fprintf(stderr, "Error: Couldn't change directory\n");
                    }
                }
                else {
                    fprintf(stderr, "Error: Couldn't create directory\n");
                }
            }
        }
        else {
            fprintf(stderr, "Error: Invalid Arguments\n");
        }
    }
    else if (argc == 4) {
        directory_name = malloc(strlen(argv[2]) + 3); // Add space for "./" and null-terminator
        if (directory_name == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            return 1;
        }
        strcpy(directory_name, "./");
        strcat(directory_name, argv[3]);
        DIR* directory = opendir(directory_name);
        if ((!strcmp(argv[1], "-r") && !strcmp(argv[2], "-v")) || (!strcmp(argv[1], "-v") && !strcmp(argv[2], "-r"))) {
            if (directory) {
                closedir(directory);
                if (rmdir(directory_name) == 0) {
                    fprintf(stdout, "Removed Directory\n");
                } 
                else {
                    fprintf(stderr, "Error: Couldn't remove directory\n");
                }
            }
            created = mkdir(directory_name, 0755);
            if (!created) {
                fprintf(stdout, "Directory created\n");
                if (!chdir(directory_name)) {
                    fprintf(stdout, "Changed current working directory\n");
                    fprintf(stdout, "Current Working Directory: %s\n", getcwd(cwd_path, sizeof(cwd_path)));
                }
                else {
                    fprintf(stderr, "Error: Couldn't change directory\n");
                }
            }
            else {
                fprintf(stderr, "Error: Couldn't create directory\n");
            }
        }
    }
    else {
        fprintf(stdout, "Error: Invalid Number of Arguments\n");
    }
    return 0;
}
