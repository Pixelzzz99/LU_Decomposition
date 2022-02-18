#include "lss_09_08.h"
#include <stdio.h>
#include <time.h>

void help()
{
    printf("Usage: lss [input_file_name] [output_file_name] [options]\n"
           "OPTIONS\n"
           "-d\t"
           "debug mode [default OFF]\n"
           "-e\t"
           "errors [default OFF]\n"
           "-p\t"
           "print matrix [default OFF]\n"
           "-t\t"
           "print execution time [default OFF]\n"
           "-h -?\t"
           "print this help\n"
           "Default input file name \"lss_09_07_in.txt\"\n"
           "Default output file name \"lss_09_07_out.txt\"\n");
}

int len(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

int word_eq(const char *word1, const char *word2)
{
    int len_word1 = len(word1);
    int len_word2 = len(word2);
    if (len_word1 != len_word2)
        return -1;
    for (int i = 0; i < len_word1; i++)
        if (word1[i] != word2[i])
            return -1;

    return 0;
}

int main(int argc, char **argv)
{
    FILE *fin;
    FILE *fout;
    int debug = 0;
    int errors = 0;
    int print = 0;
    int time = 0;
    int err = 0;
    int count_files = 0;

    for (int i = 1; i < argc; i++)
    {
        if (!word_eq(argv[i], "-h") || !word_eq(argv[i], "-?"))
        {
            help();
            return 0;
        }
        else if (!word_eq(argv[i], "-d"))
        {
            debug = 1;
        }
        else if (!word_eq(argv[i], "-e"))
        {
            errors = 1;
        }
        else if (!word_eq(argv[i], "-p"))
        {
            print = 1;
        }
        else if (!word_eq(argv[i], "-t"))
        {
            time = 1;
        }
        else if (argv[i][0] != '-')
        {
            if (i == 1)
            {
                fin = fopen(argv[i], "r");
                count_files++;
            }
            else if (i == 2)
            {
                fout = fopen(argv[i], "w");
                count_files++;
            }
            else if (errors == 1)
            {
                fprintf(stderr, "No such command");
                exit(-3);
            }
        }
        else
        {
            if (errors == 1)
            {
                fprintf(stderr, "No such command");
                exit(-3);
            }
        }
    }

    if(count_files == 0)
    {
        if((fin = fopen("lss_09_08_in.txt", "r")) == NULL)
        {
            fprintf(stderr, "Failed to open input file \n");
        }
        if((fout = fopen("lss_09_08_out.txt", "w")) == NULL)
        {
            fprintf(stderr, "Failed to open output file");
        }
    }
    else if(count_files == 1)
    {
        if(errors == 1)
        {
            fprintf(stderr, "You have added 1 file");
        }
        exit(-6);
    }




    clock_t start = clock();
    int status_code = lss_09_08(fin, fout, debug, print);
    clock_t end = clock();

    if (status_code == -1)
    {
        err = -1;
    }

    if (time)
        printf("Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    if (errors)
    {
        if (err == -1)
        {
            printf("Can't Open file \n");
        }
        if (err == 2)
        {
            printf("Can't open file \n");
        }
    }
    return 0;
}
