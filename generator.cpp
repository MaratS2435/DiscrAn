#include <iostream>
#include <cstring>
#include <unistd.h>
#include <climits>

const int MAX_SIZE = 2048;
const unsigned long DISTANCE = ULONG_MAX;

unsigned long generateRandomULong() {
    unsigned long randomValue = 0;
    constexpr int numIntsInULong = sizeof(unsigned long) / sizeof(int);
    
    for (int i = 0; i < numIntsInULong; ++i) {
        randomValue <<= (sizeof(int) * 8); // Сдвигаем на количество бит в типе int
        randomValue |= rand(); // Заполняем младшие биты случайными значениями типа int
    }

    return randomValue;
}

int main(void) {
    srand(time(NULL));

    for (int i = 0; i < 10; ++i) {
        std::string s {"aabbbb"};
        std::cout << generateRandomULong() << '\t' << s << std::endl;
    }
}