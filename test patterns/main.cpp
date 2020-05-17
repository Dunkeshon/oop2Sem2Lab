#include <iostream>
#include <vector>
#include "real.h"

int main() {
    auto* p = new strategySort(new SelectionSort);
    std::vector<int> exampl = {1, -23, -7, 4};
    for (auto &data:exampl) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    p->sort(exampl);
    for (auto &data:exampl) {
        std::cout << data << " ";
    }
    delete p;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
