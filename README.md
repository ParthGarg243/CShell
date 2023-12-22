# CShell

This C program implements a simple interactive shell with both internal and external commands. It consists of three files: `q2_main.c`, `q2_dir.c`, and `q2_date.c`.

## Files and Commands

- **q2_main.c**: Implements the interactive shell with support for commands such as 'word', 'date', 'dir', 'help', and 'exit'. Handles errors like "Command Doesn't Exist" and "Fork Failed".

- **q2_dir.c**: Contains the external command 'dir'. Handles various error messages, including "Directory Already Exists" and "Memory Allocation Failed".

- **q2_date.c**: Implements the external command 'date'. Supports options like '-d' and '-R' for different date formats. Handles errors like "No Arguments Passed" and "Invalid Number of Arguments".

## Functions

- `wordCount`: Compares word counts if the '-d' argument is passed. Handles errors like "File not Found" and "Invalid Argument Passed".

- `wordCountIgnoreNewLine`: Similar to `wordCount` but ignores newline characters.

## Libraries Used

- string.h
- stdlib.h
- stdio.h
- sys/stat.h
- time.h
- unistd.h
- dirent.h

## Error Messages

### Common Errors

- "Command Doesn't Exist"
- "Fork Failed"

### wordCount and wordCountIgnoreNewLine

- "File not Found"
- "Invalid Argument Passed"
- "No Arguments Passed"
- "Invalid Number of Arguments"

### q2_date.c

- "No Arguments Passed"
- "File not Found"
- "Invalid Arguments"
- "Invalid Number of Arguments"

### q2_dir.c

- "Directory Already Exists"
- "Memory Allocation Failed"
- "Couldn't change directory"
- "Couldn't create directory"
- "Couldn't remove directory"
- "Invalid Arguments"
- "Invalid Number of Arguments"

## Additional Information

- The program supports various options for 'date' and 'dir' commands, including '-d', '-R', '-r', and '-v'.
- The 'help' command provides information about available commands.

## Specific Commands

### 1. word

It is a built-in (internal) command that reads the number of words in a text file. Throws an error if the file does not exist.

#### Syntax:

```sh
word [-n | -d] [file_name]
```

Options:
-n: Ignores newline characters.
-d: Compares word sizes of two text files.
Note: Only one of the options (-n or -d) can be used at a time with the word command.

### 2. dir

It creates a directory, changes the path to that directory, and throws an error if the directory already exists.

### Syntax:

```sh
dir [-r | -v] [dir_name]
```

Options:
-r: Removes the directory if it already exists and creates a new directory instead of throwing an error.
-v: Prints a message for each step in the running of this command.

### 3. date

Returns the last modified date and time of a particular file. It is an external command.

### Syntax:

```sh
date [-d | -R] [file_name]
```

Options:
-d: Displays time described by STRING.
-R: Outputs date and time in RFC 5322 format.
