#include <iostream>
#include "function.hpp"

int main(void) {
    TElem* data = new TElem;
    size_t num = 0;

    while (Inputing(data, num++)) {
        TElem* newdata = new TElem[num + 1];
        if (newdata == nullptr) {
            fprintf(stderr, "Memory allocation error: data\n");
            delete[] data;
            return 1;
        }
        for (size_t i = 0; i < num; ++i) {
            newdata[i] = data[i];
        }
        delete[] data;
        data = newdata;
    }

    if (!BucketSort(data, num)) {
        delete[] data;
        return 1;
    }

    for (size_t i = 0; i < num; ++i) {
        std::cout << data[i].GetKey() << '\t' << data[i].GetVal() << std::endl;
    }

    return 0;
    
}