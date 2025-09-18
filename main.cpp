#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <cstdlib>
#include <ctime>

#include "sorting.h"


struct TextParams {
    size_t length;
    size_t number_of_strings;
    char* buffer;
    LineParams** text;

};


size_t GetFileSize(const char* filename);
void FillTextInfo(TextParams* text_info, const char* filename, size_t filesize);
char* CreateAndFillBuffer(const char* filename, size_t* result_length, size_t filesize);
LineParams** AllocateText(size_t number_of_strings);
LineParams** CreateAndFillText(char* buffer, size_t length, size_t number_of_strings);
void AddVariantsOfSortedTextInFile(const char* result_filename, TextParams* text_info);
void WriteDichInFile(FILE* result_file, TextParams* text_info);
void WriteResultInFile(FILE* result_f, TextParams* text_info);
void PrintLine(LineParams* str_params, FILE* result_file);
void Destruct(TextParams* text_info);


int main() {

    const char* filename = "onegin.txt";
    const char* result = "processed_text.txt";

    size_t filesize = GetFileSize(filename);

    TextParams text_info = {0, 5520, nullptr, nullptr};
    FillTextInfo(&text_info, filename, filesize);

    AddVariantsOfSortedTextInFile(result, &text_info);

    Destruct(&text_info);
    return 0;
}


size_t GetFileSize(const char* filename) {

    assert(filename != nullptr);

    struct stat st;//////off_t

    if (stat(filename, &st) == 0) {
        size_t filesize = st.st_size;
        return filesize;

    }

    return 0;
}

void FillTextInfo(TextParams* text_info, const char* filename, size_t filesize) {

    assert(filename  != nullptr);
    assert(text_info != nullptr);

    size_t* length_ptr = &(text_info->length);

    text_info->buffer = CreateAndFillBuffer(filename, length_ptr, filesize);
    text_info->text   = CreateAndFillText(text_info->buffer, *length_ptr, text_info->number_of_strings);
}

char* CreateAndFillBuffer(const char* filename, size_t* result_length, size_t filesize) {

    assert(filename      != nullptr);
    assert(result_length != nullptr);

    char* buffer = (char*)calloc(filesize+1, sizeof(char));
    int descriptor = open(filename, O_RDONLY);

    ssize_t length = read(descriptor, buffer, filesize+1);

    if (length == -1) {
        return nullptr;
    }

    buffer[length] = '\0';

    *result_length = (size_t)length + 1;

    close(descriptor);

    return buffer;
}

LineParams** AllocateText(size_t number_of_strings) {

    LineParams** text = (LineParams**)calloc(number_of_strings, sizeof(LineParams*));

    for (size_t i = 0; i < number_of_strings; i++) {
        text[i] = (LineParams*)calloc(number_of_strings, sizeof(LineParams));
    }

    return text;
}

LineParams** CreateAndFillText(char* buffer, size_t length, size_t number_of_strings) {

    assert(buffer != nullptr);

    LineParams** text = AllocateText(number_of_strings);

    size_t strings_added = 0;

    char* prev_pointer_to_string = buffer;
    char* destination_pointer    = buffer + length;

    for (char* pointer = buffer; pointer < destination_pointer; pointer++) {

        if (*pointer == '\n') {

            text[strings_added]->str = prev_pointer_to_string;
            text[strings_added]->len = (size_t)(pointer + 1 - prev_pointer_to_string);

            strings_added++;
            prev_pointer_to_string = pointer + 1; //offset caused by pointer's position on '\n'(L3 английский имеет свой эффект)
        }
    }

    return text;
}

void AddVariantsOfSortedTextInFile(const char* result_filename, TextParams* text_info) {

    assert(result_filename != nullptr);
    assert(text_info       != nullptr);

    FILE* result_file = fopen(result_filename, "w");

    size_t text_strings = text_info->number_of_strings;
    LineParams** text_ptr = text_info->text;

    MergeSort(text_ptr, text_strings, AlphabetLineComparator);
    fputs("----------------------STRAIGHT_SORTING---------------------------------------\n\n", result_file);
    WriteResultInFile(result_file, text_info);

    qsort(text_ptr, text_strings, sizeof(LineParams*), ReversedAlphabetLineComparator);
    fputs("----------------------WAYBACK_SORTING----------------------------------------\n\n", result_file);
    WriteResultInFile(result_file, text_info);

    qsort(text_ptr, text_strings, sizeof(LineParams*), PointerLineComparator);
    fputs("----------------------ORIGINAL_ONEGIN----------------------------------------\n\n", result_file);
    WriteResultInFile(result_file, text_info);

    qsort(text_ptr, text_strings, sizeof(LineParams*), ReversedAlphabetLineComparator);
    fputs("----------------------BREEEEEEEEEEEED----------------------------------------\n\n", result_file);
    WriteDichInFile(result_file, text_info);


    fclose(result_file);
}

void WriteResultInFile(FILE* result_file, TextParams* text_info) {

    assert(result_file != nullptr);
    assert(text_info   != nullptr);

    size_t text_strings = text_info->number_of_strings;

    for (size_t i = 0; i < text_strings; i++) {
        PrintLine((text_info->text)[i], result_file);
    }
}

void WriteDichInFile(FILE* result_file, TextParams* text_info) {// reading this is dangerous

    assert(result_file != nullptr);
    assert(text_info   != nullptr);

    LineParams* block[14] = {nullptr};

    srand(time(NULL));

    size_t lines_num = text_info->number_of_strings;
    LineParams** lines = text_info->text;

    size_t a = 0;
    size_t b = 0;
    size_t c = 0;
    size_t d = 0;
    size_t e = 0;
    size_t f = 0;
    size_t g = 0;

    for (size_t count = 0; count < 5; count++) {
        a = rand() % lines_num;
        b = rand() % lines_num;
        c = rand() % lines_num;
        d = rand() % lines_num;
        e = rand() % lines_num;
        f = rand() % lines_num;
        g = rand() % lines_num;

        block[0] = lines[a];
        block[1] = lines[b];
        block[2] = lines[a+1];
        block[3] = lines[b+1];

        block[4] = lines[c];
        block[5] = lines[c+1];
        block[6] = lines[d];
        block[7] = lines[d+1];

        block[8]  = lines[e];
        block[9]  = lines[f];
        block[10] = lines[f+1];
        block[11] = lines[e+1];

        block[12] = lines[g];
        block[13] = lines[g+1];

        for (size_t i = 0; i < 14; i++) {
            PrintLine(block[i], result_file);
        }
        fputs("\n", result_file);
    }
}

void PrintLine(LineParams* str_params, FILE* result_file) {

    assert(result_file != nullptr);
    assert(str_params  != nullptr);

    size_t string_length = str_params->len;

    for (size_t j = 0; j < string_length; j++){
        fputc((str_params->str)[j], result_file);
    }
}

void Destruct(TextParams* text_info) {

    assert(text_info != nullptr);

    free(text_info->buffer);
    free(text_info->text);

    LineParams** lines = text_info->text;
    size_t lines_num = text_info->number_of_strings;

    for (size_t index = 0; index < lines_num; index++) {
        free(lines[index]);
    }

    free(lines);
}

