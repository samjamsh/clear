/*  clear - clear the terminal screen version 1.1

    Copyright (C) 2023-2024 Free and Open Source Software "No Copyrights"

    This program is free software: you can redistribute it or modify it under the terms of the project that means you can do whatever you want with this program.

    Differences with Linux clear:
       This is a different code what it means that both programs may do the samething but in different ways
       This is a not GNU Core utilities (coreutils) program, this is an NGCU project code.

       By Yassir Daniel known as Sam Jamsh

*/


#include <stdio.h>
#include <stdlib.h>

#define WEBPAGE "https://github.com/samjamsh/clear"
#define OWNER "Sam Jamsh"
#define SOCIAL "@sam.jamsh"
#define EMAIL "th3cyb3rguy@protonmail.com"


typedef char bool;
bool true = 1;
bool false = 0;

bool ERROR = 1;
bool SUCCESS = 0;


unsigned short stringlen(char *string){

    unsigned short counter;
    unsigned short ushort_lim = 65535;

    for (counter = 0; counter < ushort_lim; counter++)
    {
        if (*string++ == 0)
        {
            return counter;
        }
    }
    return 0;
}


// compares two strings
bool cmpstr(char *string1, char *string2)
{
    char s1_char = 1;
    char s2_char = 1;

    for (unsigned short i = 0; i < 65535 && s1_char != 0 && s2_char != 0; i++)
    {
        s1_char = string1[i];
        s2_char = string2[i];

        if (s1_char != s2_char)
        {
            return ERROR; // different
        }
    }
    return SUCCESS; // equal
}


bool isdigit_(char* ptr)
{
    if (ptr[0] > 47 && ptr[0] < 58 && ptr[1] == 0)
    {
        return ERROR;
    }
    else {
        return SUCCESS;
    }
}


bool filln_array(char *array, char *string, unsigned short lenght)
{

if (array == NULL || string == NULL)
{
    perror("error accessing array/string pointers");
    return ERROR;
}

for (unsigned short i = 0; i < lenght; i++)
{
    array[i] = string[i];
}
return SUCCESS;
}


char* getPath(char *string1, char *string2)
{
    if (string1 == NULL || string2 == NULL)
    {
        printf("string1/2 NULL\n");
        return NULL;
    }

    unsigned short string1_lenght = stringlen(string1);

    unsigned short string2_lenght = 1;

    unsigned short allocate = string1_lenght + string2_lenght + 1;

    char *ptr = malloc(sizeof(char) * allocate);

    int i;

    for (i = 0; i < string1_lenght; i++)
    {
        ptr[i] = string1[i];
    }

    for (i = i; i < allocate; i++)
    {
        ptr[i] = string2[i - string1_lenght];
    }
    ptr[allocate] = '\0';

return ptr;
}


bool clear_mode(char term_id, char *buffer, size_t buflen)
{

    FILE *fp; // file pointer

    if (term_id == -1)
        fp = stdout;
    else
    {

        char *path = getPath("/dev/pts/", &term_id);
        if (path == NULL)
        {
            perror("error with path memory");
            return ERROR;
        }

        fp = fopen(path, "w");

        if (fp == NULL)
        {
            perror("file pointer memory is invalid");
            return ERROR;
        }

    }

    size_t written;

    written = fwrite(buffer, sizeof(char), buflen, fp);
    fflush(fp);

    (fp != stdout) ? fclose(fp) : (void)0;

    if (written == buflen)
        return SUCCESS;
    else
        return ERROR;

}


int main(int argc, char *argv[])
{
#if defined(__linux__)

signed char term_id;
char mode[7];
size_t mdsize;

char *default_ = "\033[2J\033[H\033[3J"; // default mode

char *personalized = "\033[2J";

if (argc == 1)
{
    term_id = -1; // standard output
    mdsize = 11;
    filln_array(mode, default_, (unsigned short) mdsize);
}

else if (argc == 2 && cmpstr(argv[1], "--version") == 0){
    printf("%s (NGCU) version 1.1\nCopyright (C) 2024 Free and Open Source Software.\nThis is a free software: you are free to modify and redistribute it.\nWritten by %s instagram> %s, email> %s\n", argv[0], OWNER, SOCIAL, EMAIL);
    return 0;
}

else if (argc == 2 && cmpstr(argv[1], "-i") == 0)
{
    term_id = -1;
    mdsize = 4;
    filln_array(mode, personalized, (unsigned short) mdsize);
}

else if (argc == 3 && cmpstr(argv[1], "-p") == 0)
{
    if (isdigit_(argv[2]))
    {
    term_id = argv[2][0];
    mdsize = 11;
    filln_array(mode, default_, (unsigned short) mdsize);

    } else {
        return 1;
    }
}

else if (argc == 4 && cmpstr(argv[1], "-p") == 0 && cmpstr(argv[3], "-i") == 0)
{
    if (isdigit_(argv[2]))
    {
    term_id = argv[2][0];
    mdsize = 4;
    filln_array(mode, personalized, (unsigned short) mdsize);

    } else {
        return 1;
    }
}

else if (argc == 4 && cmpstr(argv[1], "-i") == 0 && cmpstr(argv[2], "-p") == 0)
{
    if(isdigit_(argv[3]))
    {
    term_id = argv[3][0];
    mdsize = 4;
    filln_array(mode, personalized, (unsigned short) mdsize);

    } else {
        return 1;
    }
}

else
{
    // error
    printf("Usage: %s [option]\n\nOptions:\n  -i ignore   clear terminal screen but don't reset cursor position\n  -p pts      specify the terminal tty number \n  --version   prints program version information\n  --help      shows this message\n\nExamples:\n  %s -i  clear screen without reseting cursor position\n  %s  clear terminal screen and resets cursor position\n\nreporting bugs and complete documentation in <%s>\ncopyright: this is a free software, you are free to redistribute it.\nthis software was written by %s\n", argv[0], argv[0], argv[0], WEBPAGE, OWNER);
    return 1;
}

if(clear_mode(term_id, mode, mdsize) == SUCCESS)
    return 0;
else
    // operation have not occurred successfully
    return 1;

#else
    puts("os error: operating system must be linux distribution!");
    return 1;
#endif
}
