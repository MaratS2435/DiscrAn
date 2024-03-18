#include "function.hpp"

unsigned long TElem::GetKey() const {
    return key;
}

const char* TElem::GetVal() const {
    return val;
}

void TElem::SetKey(unsigned long &newkey) {
    key = newkey;
}

void TElem::SetVal(char newval[]) {
    for (int i = 0; i < MAX_SIZE; ++i) {
        val[i] = newval[i];
    }
}

bool Inputing(TElem *&data, size_t num) {
    unsigned long newkey {0};
    char newval[MAX_SIZE] {'\0'};
    bool fail = false;

    char temp;
    if (read(STDIN_FILENO, &temp, 1) == 0) {
        return 0;
    }
    while (temp != '\t' && temp != ' ' && temp != EOF) {
        newkey = newkey * 10 + (temp - '0');
        read(STDIN_FILENO, &temp, 1);
    }

    if (temp == EOF) {
        return temp != EOF;
    }

    read(STDIN_FILENO, &temp, 1);
    int i {0};
    while (temp != EOF && temp != '\0' && temp != '\n') {
        newval[i++] = temp;
        if (read(STDIN_FILENO, &temp, 1) == 0) {
            fail = true;
            break;
        }
    }
    data[num].SetKey(newkey);
    data[num].SetVal(newval);

    if (fail == true) {
        return 0;
    }

    return temp != EOF;
}

bool TBucket::AddItem(TElem &item) {
    TElem* newContent = new TElem[count + 1];
    if (newContent == nullptr) {
        fprintf(stderr, "Memory allocation error: AddItem\n");
        if (count != 0) {
            delete[] content;
        }

        return false;
    }
    for (size_t i = 0; i < count; ++i) {
        newContent[i] = content[i];
    }
    newContent[count] = item;
    if (count != 0) {
        delete[] content;
    }
    content = newContent;
    ++count;
    return true;
}

void TBucket::Sort() {
    size_t i {0};
    size_t j {0};
    TElem tmp;
    for (i = 0; i < count; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (content[j].GetKey() > content[j + 1].GetKey()) {
                tmp = content[j];
                content[j] = content[j + 1];
                content[j + 1] = tmp;
            }
        }
    }
}

bool BucketSort(TElem *&data, size_t num) {
    TBucket* bucket = new TBucket[num];
    if (bucket == nullptr) {
        fprintf(stderr, "Memory allocation error: bucket\n");
        return false;
    }
    size_t bucketLenght = DISTANCE / num;
    for (size_t i = 0; i < num; ++i) {
        size_t bucketIndex = data[i].GetKey() / bucketLenght;
        if (!bucket[bucketIndex].AddItem(data[i])) {
            for (size_t j = 0; j < num; ++j) {
                if (bucket[j].count > 0) {
                    delete[] bucket[j].content;
                }
            }
            delete[] bucket;

            return false;
        }
    }

    size_t k = 0;
    for (size_t i = 0; i < num; ++i) {
        if (bucket[i].count > 1) {
            bucket[i].Sort();
            for (size_t j = 0; j < bucket[i].count; ++j) {
                data[k++] = bucket[i].content[j];
            }
        }
        if (bucket[i].count == 1) {
            data[k++] = bucket[i].content[0];
        }  
    }

    return true;
}

