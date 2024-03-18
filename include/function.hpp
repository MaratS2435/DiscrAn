#include <iostream>
#include <cstring>
#include <unistd.h>
#include <climits>

const int MAX_SIZE = 2048;
const unsigned long DISTANCE = ULONG_MAX;

class TElem {
    private:
        unsigned long key;
        char val[MAX_SIZE] {'\0'};
    public:
        TElem() = default;
        ~TElem() = default;

        unsigned long GetKey() const;
        const char* GetVal() const;
        void SetKey(unsigned long &newkey);
        void SetVal(char newval[]);
        void PrintVal();
};

bool Inputing(TElem *&data, size_t num);

class TBucket {
public:
    TElem* content {nullptr};
    size_t count {0};

    bool AddItem(TElem& item);
    void Sort();
};

bool BucketSort(TElem *&data, size_t num);
