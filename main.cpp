#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

#include "sorting.h"

const size_t STRNUM = 5520;

size_t FileSize(const char* filename);
char* CreateAndFillBuffer(const char* filename, size_t* result_length, size_t filesize);
StrPar** CreateAndFillText(char* buffer, size_t length);
StrPar** CreateTextCopy(StrPar** text);





int main() {

    const char* filename = "onegin.txt";
    const char* result = "processed_text.txt";
    size_t filesize = FileSize(filename);
    size_t length = 0;

    char* buffer = CreateAndFillBuffer(filename, &length, filesize);

    StrPar** text = CreateAndFillText(buffer, length);
    StrPar** text_for_rs = CreateTextCopy(text);
    StrPar** text_for_ls = CreateTextCopy(text);


    merge_sort(text, STRNUM);
    FILE* result_f = fopen(result, "w");

    for (size_t i = 0; i < STRNUM; i++) {
        for (size_t j = 0; j < text[i]->len; j++){
            fputc((text[i]->str)[j], result_f);
        }
    }



    free(buffer);
    for (size_t i = 0; i < STRNUM; i++) {
        free(text[i]);
        free(text_for_rs[i]);
        free(text_for_ls[i]);
    }
    free(text);
    free(text_for_rs);
    free(text_for_ls);
    return 0;
}






size_t FileSize(const char* filename) {
    struct stat st;

    if (stat(filename, &st) == 0) {
        size_t filesize = st.st_size;
        return filesize;

    }

    return 0;
}


char* CreateAndFillBuffer(const char* filename, size_t* result_length, size_t filesize) {

    char* buffer = (char*)calloc(filesize+1, sizeof(char));
    int descriptor = open(filename, O_RDONLY);

    ssize_t length = read(descriptor, buffer, filesize+1);

    if (length == -1) {
        return nullptr;
    }

    buffer[length] = '\0';

    *result_length = (size_t)length + 1; //Нужно ли?

    close(descriptor);

    return buffer;

}


StrPar** CreateAndFillText(char* buffer, size_t length) {
    StrPar** text = (StrPar**)calloc(STRNUM, sizeof(StrPar*));
    for (size_t i = 0; i < STRNUM; i++) {
        text[i] = (StrPar*)calloc(STRNUM, sizeof(StrPar));
    }


    size_t strings_added = 0;
    char* prev_pointer_to_string = buffer;
    for(char* pointer = buffer; pointer < buffer + length; pointer++) {

        if (*pointer == '\n') {

            text[strings_added]->str = prev_pointer_to_string;
            text[strings_added]->len = (size_t)(pointer + 1 - prev_pointer_to_string);

            strings_added++;
            prev_pointer_to_string = pointer + 1;
        }
    }

    return text;

}


StrPar** CreateTextCopy(StrPar** text) {
    StrPar** text_copy = (StrPar**)calloc(STRNUM, sizeof(StrPar*));
    for (size_t i = 0; i < STRNUM; i++) {
        text_copy[i] = (StrPar*)calloc(STRNUM, sizeof(StrPar));
        text_copy[i]->len = text[i]->len;
        text_copy[i]->str = text[i]->str;
    }
    return text_copy;
}




