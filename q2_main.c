#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int wordCount(FILE* file_name);
int wordCountIgnoreNewline(FILE* file_name);
int argumentCount(char input[100]);
void wordFunction(char **argument_array, int argument_count);

int argumentCount(char input[100]) {    // function to calculate the number of arguments in input
    int count = 0;
    for (int i = 0; i < 100; i++) {
        if (input[i] == ' ') {
            count++;
        }
        else if (input[i] == '\0') {
            count++;
            return count;
        }
        else {
            continue;
        }
    }
}

int wordCount(FILE* file_name) {    // function to calculate the words in a file
    int word = 0;   // pointer inside/outside word
    int word_count = 0;
    while (1) {
        char character = fgetc(file_name);
        if (character == ' ') {
            word = 0;
        }
        else if (character == EOF) {
            if(word == 0) {
                return word_count;
            }
            else {
                word_count++;
                return word_count;
            }
        }
        else if (word == 0) {
            word = 1;
            word_count++;
        }
    }
}

int wordCountIgnoreNewline(FILE* file_name) {
    int word = 0;   // pointer inside/outside word
    int word_count = 0;
    int newline = 0; // flag to track newline characters

    while (1) {
        char character = fgetc(file_name);
        
        if (character == '\n') {
            if (newline) {
                word_count++;
                newline = 0;
            }
            else {
                newline = 1;
            }
        }
        else if (character == ' ') {
            word = 0;
            newline = 0;
        }
        else if (character == EOF) {
            if (word == 0 && !newline) {
                return word_count;
            }
            else {
                return word_count + 1; // Account for the last word
            }
        }
        else if (word == 0) {
            word = 1;
            word_count++;
            newline = 0;
        }
    }
}

void wordFunction(char **argument_array, int argument_count) {
    int word_count1 = 0;
    int word_count2 = 0;
    FILE* file1 = NULL;
    FILE* file2 = NULL;

    if (argument_count == 1) {
        fprintf(stderr, "Error: No Arguments Passed\n");
    }
    else if (argument_count == 2) {
        file1 = fopen(argument_array[1], "r");
        if (file1 == NULL) {
            fprintf(stderr, "Error: File not found\n");
        }
        word_count1 = wordCount(file1);
        printf("Number of words: %d\n", word_count1);
        fclose(file1);
    }
    else if (argument_count == 3) {
        if (!strcmp(argument_array[1], "-n")) {
            file1 = fopen(argument_array[2], "r");
            if (file1 == NULL) {
                fprintf(stderr, "Error: File not found\n");
            }
            word_count1 = wordCountIgnoreNewline(file1);
            printf("Number of Words: %d\n", word_count1);
            fclose(file1);
        }
        else {
            fprintf(stderr, "Error: Invalid Argument Passed\n");
        }
    }
    else if (argument_count == 4) {
        if (!strcmp(argument_array[1], "-d")) {
            file1 = fopen(argument_array[2], "r");
            file2 = fopen(argument_array[3], "r");
            if (file1 == NULL) {
                fprintf(stderr, "Error: File not found\n");
            }
            if (file2 == NULL) {
                fprintf(stderr, "Error: File not found\n");
            }
            word_count1 = wordCount(file1);
            word_count2 = wordCount(file2);
            printf("Word Difference: %d\n", abs(word_count1 - word_count2));
            fclose(file1);
            fclose(file2);
        }
        else {
            fprintf(stderr, "Error: Invalid Argument\n");
        }
    }
    else if (argument_count == 5) {
        if ((!strcmp(argument_array[1], "-n") && !strcmp(argument_array[2], "-d")) || (!strcmp(argument_array[1], "-d") && !strcmp(argument_array[2], "-n"))) {
            file1 = fopen(argument_array[3], "r");
            file2 = fopen(argument_array[4], "r");
            if (file1 == NULL) {
                fprintf(stderr, "Error: File not found\n");
            }
            if (file2 == NULL) {
                fprintf(stderr, "Error: File not found\n");
            }
            word_count1 = wordCountIgnoreNewline(file1);
            word_count2 = wordCountIgnoreNewline(file2);
            printf("Word Difference: %d\n", abs(word_count1 - word_count2));
            fclose(file1);
            fclose(file2);
        }
        else {
            fprintf(stderr, "Error: Invalid Argument Passed");
        }
    }
    else {
        fprintf(stderr, "Error: Invalid Number of Arguments\n");
    }
}

int main(int argc, char* argv[]) {
    char input[100];
    char *argument_array[6];
    int argument_count;
    char *word;
    char cwd_path[250];

    while (1) {
        argument_count = 0;
        printf("$ ");   // prefix really...
        fgets(input, 100, stdin);

        for (int i = 0; i < 100; i++) {
            if (input[i] == '\n') {
                input[i] = '\0';
                break;
            }
        }

        argument_count = argumentCount(input);
        word = strtok(input, " ");

        int i = 0;
        while (word != NULL) {
            argument_array[i] = strdup(word);
            i++;
            word = strtok(NULL, " ");
        }

        argument_array[argument_count] = NULL;

        if (!strcmp(argument_array[0], "word")) {
            wordFunction(argument_array, argument_count);
        }

        else if (!strcmp(argument_array[0], "dir")) {
            int rc = fork();
            if (rc < 0) {       // fork failed, ignore this- i will do it later
                fprintf(stderr, "fork failed\n");
                exit(1);
            }
            else if (rc == 0) {     // child process, execvp here
                argument_array[argument_count] = NULL;
                execvp("./dir", argument_array);
            }
            int rc_wait = wait(NULL);
            //child ends above, starting parent here, yet again
        }

        else if (!strcmp(argument_array[0], "date")) {
            int rc = fork();
            if (rc < 0) {       // fork failed, ignore this- i will do it later
                fprintf(stderr, "fork failed\n");
                exit(1);
            }
            else if (rc == 0) {     // child process, execvp/exec here
                argument_array[argument_count] = NULL;
                execvp("./date", argument_array);
            }
            int rc_wait = wait(NULL);
            //child ends above, starting parent here, yet again
        }

        else if (!strcmp(argument_array[0], "help")) {
            printf("1) word\n2) dir\n3) date\n4) help\n5) exit\n");
        }

        else if (!strcmp(argument_array[0], "exit")) {
            return 0;
        }

        else {
            fprintf(stderr, "Error: Command doesn't exist\n");
        }

        for (int j = 0; j < argument_count; j++) {
            if (argument_array[j] != NULL) {
                free(argument_array[j]);
            }
        }
    }
}
