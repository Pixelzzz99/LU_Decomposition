#include "lss_09_08.h"
#include <stdio.h>
#include <time.h>

void help()
{
    printf("Usage: lss [input_file_name] [output_file_name] [options]\n"
            "OPTIONS\n"
            "-d\t" "debug mode [default OFF]\n"
            "-e\t" "errors [default OFF]\n"
            "-p\t" "print matrix [default OFF]\n"
            "-t\t" "print execution time [default OFF]\n"
            "-h -?\t" "print this help\n"
            "Default input file name \"lss_09_07_in.txt\"\n"
            "Default output file name \"lss_09_07_out.txt\"\n");
}

int len(const char* str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

int word_eq(const char* word1, const char* word2)
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

FILE* open_file(const char* filename, const char* mode)
{
    FILE* file = fopen(filename, mode);
    if (file == NULL)
    {
        printf("Error: can't open file \"%s\"\n", filename);
        return NULL;
    }
    return file;
}

int main(int argc, char **argv)
{
    FILE* fin;
    FILE* fout;
    int debug = 0;
    int errors = 0;
    int print = 0;
    int time = 0;
    int err = 0;

    for(int i = 1; i < argc; i++)
    {
        if(!word_eq(argv[i], "-h") || !word_eq(argv[i], "-?"))
        {
            help();
            return 0;
        }
        else if(!word_eq(argv[i], "-d"))
        {
            debug = 1;
            printf("Dubug Mode ON\n");
        }
        else if(!word_eq(argv[i], "-e"))
        {
            errors = 1;
            printf("Errors ON\n");
        }
        else if(!word_eq(argv[i], "-p"))
        {
            print = 1;
            printf("Print matrix ON\n");
        }
        else if(!word_eq(argv[i], "-t"))
        {
            time = 1;
            printf("Print time ON\n");
        }
        else if(argv[i][0] != '-')
        {
            if(i == 1) {
                fin = open_file(argv[i], "r");
            }
            if(i == 2) {
                fout = open_file(argv[i], "w");
            }
        }
    }

    if(fin == NULL || fout == NULL){
        printf("Error: can't open file \n");
        err = 2;
    }
    
    clock_t start = clock();
    if(lss_09_08(fin, fout, debug, print) == -1) {
        err = -1;
    }
    clock_t end = clock();

    if (time)
        printf("Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    if(errors)
    {
        if(err == -1)
        {
            printf("Can't Open file \n");
        }
        if(err == 2)
        {
            printf("Can't open file \n");
        }

    }
    return 0;
}
