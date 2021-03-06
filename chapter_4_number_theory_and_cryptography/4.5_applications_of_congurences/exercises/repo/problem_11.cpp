#include "power_random.h"
#include <cstdio>

int main() {
    int p = 7;
    int d = 3;
    int x = 2;
    discrete_mathematics::chapter_4::PowerRandom random;
    const std::vector<int> numbers = random.generate(p, d, x);

    printf("----------------------------------------------\n");
    for (std::size_t i = 0; i < numbers.size(); ++i)
        printf("%d ", numbers[i]);
    printf("\n----------------------------------------------\n");

    return 0;
}
