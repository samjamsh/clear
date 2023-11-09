#include <stdio.h>
#include <unistd.h>
#include <string.h>

int writin_output(char *bytes, size_t bytes_lenght){

    ssize_t writed_bytes;

    size_t byte_lenght = 1;

    int writen_successfully;

    writed_bytes = fwrite(bytes, byte_lenght, bytes_lenght, stdout);

    writen_successfully = fflush(stdout);

    if (writen_successfully == 0 && (writed_bytes == bytes_lenght)){
        return 0;
    }
    else{
        perror("it was not possible to write the bytes to stdout");
        return 1;
    }
}

int main(int argc, char *argv[]){
#if defined(__linux__)
    char *clean;
    size_t sizeofValue;

    if (argc == 1){
        clean = "\033[2J\033[H"; // default mode
        sizeofValue = 7;
    }
    else if (argc == 2 && strcmp(argv[1], "-i\0") == 0){
        clean = "\033[2J"; // personalized mode
        sizeofValue = 4;
    }
    else if (argc == 2 && strcmp(argv[1], "--help\0") == 0){
        printf("This is help message of WCP (Windows Cls Program) version 1.0\nusage: %s {option}\n\n[option]\n       -i  ignore: this options cleans the terminal screen but don't reset cursor position, it just cleans without reseting cursor position to line 0 and column 0\n\nexample: %s\n", argv[0], argv[0]);
        return 0;
    }
    else if (argc == 2 && strcmp(argv[1], "--version\0") == 0){
        puts("Windows Cls command for linux similar to linux Clear command version 1.0\nThis is a free and open source software you can do whatever you want\nContacts: instagram> @sam.jamsh, github> samjamsh\n\nThis software was created by sam jamsh 09/11/2023");
        return 0;

    } else {
        puts("parameter error: invalid arguments!");
        return 1;
    }

    if (writin_output(clean, sizeofValue) != 0){
        // error
        return 1;
    } else {
        // success
        return 0;
    }
#else
    puts("os error: operating system must be linux!");
    return 1;
#endif
}
