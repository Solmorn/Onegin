#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sorting.h"


int main() {

    StrPar** poem[14] = {nullptr};


    for (size_t i = 0; i < 14; i++) {
        poem[i] = (StrPar**)calloc(50, sizeof(StrPar*));
        for (size_t j = 0; j < 50; j++) {
            poem[i][j] = (StrPar*)calloc(1, sizeof(StrPar));
            poem[i][j]->len = 0;
            poem[i][j]->str = nullptr;
        }
    }

    FILE* input_file = nullptr;
    FILE* output_file = nullptr;

    size_t lines_added[14] = {0};

    input_file  = fopen("raww_text.txt", "r");
    output_file = fopen("processed_text.txt", "w");

    signed char letter = '\n';
    char* string = (char*)calloc(100, sizeof(char));
    bool is_not_eof = true;
    size_t line_in_block = 0;
    ssize_t length = 0;
    size_t count = 0;
    size_t fg = 0;

    while(is_not_eof) {

        if (length == 1) {
            line_in_block = 0;
        }

        length = 0;


        if ((length = getline(&string, &fg, input_file)) == -1) is_not_eof = 0;



        if (is_not_eof && length > 1) {
            printf("l %zu, lib %zu", length, line_in_block);


            assert(line_in_block < 14);
            assert(lines_added[line_in_block] < 50);

            StrPar* curr_str = poem[line_in_block][lines_added[line_in_block]];

            curr_str->len = length + 1;
            curr_str->str = (char*)calloc(length + 1, sizeof(char));


            for (size_t i = 0; i < length; i++) {
                (curr_str->str)[i] = string[i];
            }



            lines_added[line_in_block]++;
        }

        printf("count %zu\n", count);
        printf("lnb %zu\n", line_in_block);
        printf("%s\n", string);
        for (size_t i = 0; i < 14; i++) {
            printf("[%zu]->%zu ", i, lines_added[i]);
        }
        printf("\n\n");

        line_in_block++;
        count++;
    }


    fclose(input_file);
    fclose(output_file);

    for (size_t i = 0; i < 14; i++) {
        printf("%zu lines\n\n", i);

        StrPar** res = merge_sort(poem[i], 50);

        for (size_t j = 0; poem[i][j]->str != nullptr; j++) {
            printf("%s\n", poem[i][j]->str);

            free(poem[i][j]->str);
        }

        free(poem[i]);
    }

}


