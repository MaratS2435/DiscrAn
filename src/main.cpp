#include <iostream>
#include "function.hpp"

int main(void) {
    unsigned long int* keys = (unsigned long int*)malloc(sizeof(unsigned long int));
    char** values = (char**)malloc(sizeof(char*));
    size_t capacity = 1;
    size_t num = 0;

    values[0] = (char*)malloc(sizeof(char) * MAX_SIZE);
    memset(values[0], '\0', MAX_SIZE);

    unsigned long key;
    char value[MAX_SIZE];
    while(std::cin >> key >> value) {
        if (capacity == num) {
            if (Expansion(keys, values, capacity)) {
                return 1;
            }
        }
        keys[num] = key;

    }
}