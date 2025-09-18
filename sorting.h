#ifndef SORTING
#define SORTING

struct LineParams {
    size_t len;
    char* str;
};


typedef int (*Comparator) (const void*, const void*);



LineParams** MergeSort(LineParams** arr, size_t size, Comparator);
LineParams** MergeLines(LineParams** arr1, LineParams** arr2, size_t size1, size_t size2, LineParams** arr0, Comparator);
char ConvertToLower(char c);
int ReversedAlphabetLineComparator(const void* el1, const void* el2);
int AlphabetLineComparator(const void* v_el1, const void* v_el2);
int PointerLineComparator(const void* v_el1, const void* v_el2);


#endif
