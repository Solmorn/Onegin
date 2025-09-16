
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "sorting.h"


StrPar** merge_sort(StrPar** arr, size_t size) {
    if (size == 1) {
        return arr;

    } else  {
        StrPar** arr1 = arr;
        StrPar** arr2 = arr + size/2;

        size_t size1 = size/2;
        size_t size2 = size - size/2;

        return my_merge(merge_sort(arr1, size1), merge_sort(arr2, size2), size1, size2, arr);
    }
}


StrPar** my_merge(StrPar** arr1, StrPar** arr2, size_t size1, size_t size2, StrPar** arr0) {

    StrPar** res = (StrPar**)calloc(size1+size2, sizeof(StrPar*));

    size_t added_elements1 = 0;
    size_t added_elements2 = 0;
    size_t index = 0;

    while(index < size1+size2) {// cmp true esly 1 >= 2

        if (added_elements1 == size1 || added_elements2 == size2) {
            break;
        }

        if (rcmp(*arr1, *arr2)) {
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

    for(size_t index = 0; index < size1+size2; index++) {
        arr0[index] = res[index];
    }

    free(res);

    return arr0;
}


bool rcmp(StrPar* el1, StrPar* el2) {
    char* str1 = el1->str;
    char* str2 = el2->str;

    size_t len1 = el1->len;
    size_t len2 = el2->len;



    while(len1 > 0 && !isalpha(str1[len1-1])) len1--;
    while(len2 > 1 && !isalpha(str2[len2-1])) len2--;
    size_t bound = len1;
    if (len2 < len1) bound = len2;


    for (size_t index = 0; index < bound; index++) {

        if (str1[len1-index-1] > str2[len2-index-1]) return true;
        else if (str1[len1-index-1] < str2[len2-index-1]) return false;
    }

    if (len1 > len2) return true;

    return false;

}





