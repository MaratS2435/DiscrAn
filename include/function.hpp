#include <iostream>
#include <cstring>

const int MAX_SIZE = 2048;

int Expansion(unsigned long int *&keys, char **&values, size_t &capacity) {
    size_t old_cap = capacity;
    capacity *= 2;
    unsigned long int* temp_keys = (unsigned long int*)realloc(keys, sizeof(unsigned long int) * capacity);
    if (temp_keys == nullptr) {
        fprintf(stderr, "Memory allocation error: keys.\n");
        free(keys);
        return 1;
    } else {
        keys = temp_keys;
    }
    char** temp_values = (char**)realloc(values, sizeof(char*) * capacity);
    if (temp_values == nullptr) {
        fprintf(stderr, "Memory allocation error: values\n");
        // Освобождение ранее выделенной памяти перед выходом
        for (int i = 0; i < old_cap; ++i) {
            free(values[i]);
        }
        free(values);
        return 1;
    }
    for (size_t i = old_cap; i < capacity; ++i) {
        values[i] = (char*)malloc(sizeof(char) * MAX_SIZE);
        if (values[i] == nullptr) {
        fprintf(stderr, "Memory allocation error: strings\n");
        // Освобождение ранее выделенной памяти перед выходом
        for (int j = 0; j < i; ++j) {
            free(values[j]);
        }
        free(values);
        return 1;
        }
        memset(values[i], '\0', MAX_SIZE);
    }
    return 0;
}

int Inputing()