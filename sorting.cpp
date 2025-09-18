#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "sorting.h"


LineParams** MergeSort(LineParams** arr, size_t size, Comparator cmp) {

    assert(arr != nullptr);

    if (size == 1) {
        return arr;

    } else  {
        LineParams** arr1 = arr;
        LineParams** arr2 = arr + size/2;

        size_t size1 = size/2;
        size_t size2 = size - size/2;

        return MergeLines(MergeSort(arr1, size1, cmp), MergeSort(arr2, size2, cmp), size1, size2, arr, cmp);
    }
}


LineParams** MergeLines(LineParams** arr1, LineParams** arr2,
                        size_t      size1, size_t      size2, LineParams** arr0, Comparator cmp) {

    assert(arr1 != nullptr);
    assert(arr2 != nullptr);
    assert(arr0 != nullptr);

    LineParams** res = (LineParams**)calloc(size1+size2, sizeof(LineParams*));

    size_t added_elements1 = 0;
    size_t added_elements2 = 0;
    size_t index           = 0;
    size_t all_size        = size1 + size2;

    while (index < all_size) {// cmp true if 1 >= 2

        if (added_elements1 == size1 || added_elements2 == size2) {
            break;
        }

        if (cmp(arr1, arr2) < 0) {
            res[index] = *arr1;
            arr1++;
            added_elements1++;
        } else {
            res[index] = *arr2;
            arr2++;
            added_elements2++;
        }
        index++;
    }


    if (added_elements1 == size1) {

        while (added_elements2 < size2) {
            res[index] = *arr2;
            arr2++;
            index++;
            added_elements2++;
        }


    } else if (added_elements2 == size2) {

        while (added_elements1 < size1) {

            res[index] = *arr1;
            arr1++;
            index++;
            added_elements1++;
        }
    }

    index = 0;
    while (index < all_size) {
        arr0[index] = res[index];
        index++;
    }

    free(res);

    return arr0;
}

void BubbleSort(void* arr0, size_t number_of_elements, size_t size, Comparator cmp) {

    assert(arr0 != nullptr);

    char* arr  = (char*)arr0;
    char* temp = (char*)calloc(1, size);

    for (size_t first_check_index = 0; first_check_index < number_of_elements - 1; first_check_index++) {

        for (size_t second_check_index = 0; second_check_index < number_of_elements - 1 - first_check_index; second_check_index++) {

            void* elem1 = arr + second_check_index * size;
            void* elem2 = elem1 + size;

            if (cmp(elem1, elem2) > 0) {
                memcpy(temp, elem1, size);
                memcpy(elem1, elem2, size);
                memcpy(elem2, temp, size);
            }
        }
    }
    free(temp);
}


char ConvertToLower(char c) {
    if (c >= 'A' && c <= 'Z') return c + 'a' - 'A';
    return c;
}


int ReversedAlphabetLineComparator(const void* v_el1, const void* v_el2) {

    assert(v_el1 != nullptr);
    assert(v_el2 != nullptr);

    const LineParams* el1 = *((const LineParams**)v_el1);
    const LineParams* el2 = *((const LineParams**)v_el2);

    char* str1 = el1->str;
    char* str2 = el2->str;


    size_t len1 = el1->len;
    size_t len2 = el2->len;

    size_t bound = len1;
    if (len2 < len1) bound = len2;

    char c1 = 0;
    char c2 = 0;

    for (size_t index = 0; index < bound; index++) {

        while(len1 > 0 && !isalpha(str1[len1-1])) len1--;
        while(len2 > 0 && !isalpha(str2[len2-1])) len2--;

        c1 = ConvertToLower(str1[len1-index-1]);
        c2 = ConvertToLower(str2[len2-index-1]);

        if (c1 > c2) return 1;
        else if (c1 < c2) return -1;

        bound = len1;
        if (len2 < len1) bound = len2;

    }

    if (len1 > len2) return 1;

    return -1;
}

int AlphabetLineComparator(const void* v_el1, const void* v_el2) {

    assert(v_el1 != nullptr);
    assert(v_el2 != nullptr);

    const LineParams* el1 = *((const LineParams**)v_el1);
    const LineParams* el2 = *((const LineParams**)v_el2);

    char* str1 = el1->str;
    char* str2 = el2->str;


    size_t len1 = el1->len;
    size_t len2 = el2->len;
    size_t bound = len1;
    if (len2 < len1) bound = len2;

    char c1 = 0;
    char c2 = 0;

    size_t index1 = 0;
    size_t index2 = 0;


    while (index1 < bound && index2 < bound) {

        if (str1[index1] == '\n') return -1;
        if (str2[index2] == '\n') return 1;

        while(index1 < bound && !isalpha(str1[index1])) {
            index1++;
        }
        while(index2 < bound && !isalpha(str2[index2])) {
            index2++;
        }

        c1 = ConvertToLower(str1[index1]);
        c2 = ConvertToLower(str2[index2]);

        if (c1 > c2) return 1;
        else if (c1 < c2) return -1;

        index1++;
        index2++;
    }

    if (len1 > len2) return 1;

    return -1;
}

int PointerLineComparator(const void* v_el1, const void* v_el2) {

    assert(v_el1 != nullptr);
    assert(v_el2 != nullptr);

    const LineParams* el1 = *((const LineParams**)v_el1);
    const LineParams* el2 = *((const LineParams**)v_el2);

    char* str1 = el1->str;
    char* str2 = el2->str;

    if (str1 > str2) return 1;
    return -1;
}

