#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

char *weekDay(int week_Day)
{
    switch (week_Day)
    {
    case 0:
        return "Sun";
    case 1:
        return "Mon";
    case 2:
        return "Tue";
    case 3:
        return "Wed";
    case 4:
        return "Thur";
    case 5:
        return "Fri";
    case 6:
        return "Sat";
    case 7:
        return "Sun";
    case 8:
        return "Mon";
    }
}

char *month(int month)
{
    switch (month)
    {
    case 1:
        return "Jan";
    case 2:
        return "Feb";
    case 3:
        return "Mar";
    case 4:
        return "Apr";
    case 5:
        return "May";
    case 6:
        return "Jun";
    case 7:
        return "Jul";
    case 8:
        return "Aug";
    case 9:
        return "Sep";
    case 10:
        return "Oct";
    case 11:
        return "Nov";
    case 12:
        return "Dec";
    }
}

int main(int argc, char *argv[])
{
    FILE *file = NULL;
    char *file_name = NULL;
    struct stat file_stats;
    struct tm *file_time;

    if (argc == 1)
    {
        fprintf(stderr, "Error: No Arguments Passed\n");
    }
    else if (argc == 2)
    {
        file_name = argv[1];
        file = fopen(file_name, "r");
        if (file == NULL)
        {
            fprintf(stderr, "Error: File not Found\n");
        }
        else
        {
            stat(file_name, &file_stats);
            file_time = gmtime(&(file_stats.st_mtime));
            fprintf(stdout, "Last Modified: %s %s %d %d:%d:%d IST %d\n", weekDay(file_time->tm_wday), month(file_time->tm_mon + 1), file_time->tm_mday, file_time->tm_hour, file_time->tm_min, file_time->tm_sec, file_time->tm_year + 1900);
        }
    }
    else if (argc == 3)
    {
        file_name = argv[2];
        file = fopen(file_name, "r");
        if (file == NULL)
        {
            fprintf(stderr, "Error: File not Found\n");
        }
        else
        {
            if (!strcmp(argv[1], "-d"))
            {
                stat(file_name, &file_stats);
                file_time = gmtime(&(file_stats.st_mtime));
                fprintf(stdout, "Last Modified (STRING Format): %s %s %d %d:%d:%d IST %d\n", weekDay(file_time->tm_wday), month(file_time->tm_mon + 1), file_time->tm_mday, file_time->tm_hour, file_time->tm_min, file_time->tm_sec, file_time->tm_year + 1900);
            }
            else if (!strcmp(argv[1], "-R"))
            {
                stat(file_name, &file_stats);
                file_time = gmtime(&(file_stats.st_mtime));
                fprintf(stdout, "Last Modified (RFC 5322 Format): %s, %d %s %d %d:%d:%d +0530\n", weekDay(file_time->tm_wday), file_time->tm_mday, month(file_time->tm_mon + 1), file_time->tm_year + 1900, file_time->tm_hour, file_time->tm_min, file_time->tm_sec);
            }
            else
            {
                fprintf(stderr, "Error: Invalid Argument\n");
            }
        }
    }
    else if (argc == 4)
    {
        file_name = argv[2];
        file = fopen(file_name, "r");
        if (file == NULL)
        {
            fprintf(stderr, "Error: File not Found\n");
        }
        else
        {
            if (!strcmp(argv[1], "-d"))
            {
                if (!strcmp(argv[2], "yesterday"))
                {
                    stat(file_name, &file_stats);
                    file_time = gmtime(&(file_stats.st_mtime));
                    fprintf(stdout, "Last Modified (STRING Format): %s %s %d %d:%d:%d IST %d\n", weekDay(file_time->tm_wday - 1), month(file_time->tm_mon + 1), file_time->tm_mday, file_time->tm_hour, file_time->tm_min, file_time->tm_sec, file_time->tm_year + 1900);
                }
                if (!strcmp(argv[2], "tomorrow"))
                {
                    stat(file_name, &file_stats);
                    file_time = gmtime(&(file_stats.st_mtime));
                    fprintf(stdout, "Last Modified (STRING Format): %s %s %d %d:%d:%d IST %d\n", weekDay(file_time->tm_wday + 1), month(file_time->tm_mon + 1), file_time->tm_mday, file_time->tm_hour, file_time->tm_min, file_time->tm_sec, file_time->tm_year + 1900);
                }
            }
        }
    }

    else
    {
        fprintf(stderr, "Error: Invalid Number of Arguments\n");
    }
    return 0;
}
