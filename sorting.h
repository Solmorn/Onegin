#ifndef SORTING
#define SORTING

struct StrPar {
    size_t len;
    char* str;
};



StrPar** merge_sort(StrPar** arr, size_t size);
StrPar** my_merge(StrPar** arr1, StrPar** arr2, size_t size1, size_t size2, StrPar** arr0);
bool rcmp(StrPar* el1, StrPar* el2);


#endif
