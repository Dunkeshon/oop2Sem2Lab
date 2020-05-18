#include <iostream>
#include <vector>
#include "real.h"

int main() {
    auto* p = new strategySort(new SelectionSort);
    std::vector<int> exampl = {1, -23, -7, 4};
    p->sort(exampl);
    for (auto &data:exampl) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    delete p;

    p = new strategySort(new InsertionSort);
    std::vector<int> exampl_2 = {45, -23, -7, 4};
    p->sort(exampl_2);
    for (auto &data:exampl_2) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    delete p;

    p = new strategySort(new QuickSort);
    std::vector<int> exampl_3 = {45, -2, -7, 4, -10, 10, 10};
    p->sort(exampl_3);
    for (auto &data:exampl_3) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    delete p;

    p = new strategySort((new RecMerge));
    std::vector<int> exampl_4 = {45, -1, -7, 8, -10, 10, 10};
    p->sort(exampl_4);
    for (auto &data:exampl_4) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    delete p;

    p = new strategySort((new IterationMerge));
    std::vector<int> exampl_5 = {45, -1, -7, 8, 4, -10, -10, 0, 10};
    p->sort(exampl_5);
    for (auto &data:exampl_5) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    delete p;

    p = new strategySort(new Radix(new MsdRadix));
    std::vector<int> exampl_6 = {45, -1, -7, 8, 4, -10, -10, 0, 123, 12};
    p->sort(exampl_6);
    for (auto &data:exampl_6) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    delete p;

    //ATENTION PLES: IT IS NOT WORK FOR NEGATIVES and sometimes with another shit
//    p = new strategySort((new Radix(new LsdRadix)));
//    std::vector<int> exampl_7 = {1, 54, 48, 89};
//    p->sort(exampl_7);
//    std::cout << "step_00" << std::endl;
//    for (auto &data:exampl_7) {
//        std::cout << data << " ";
//    }
//    std::cout << std::endl;
//    std::cout << "step_000" << std::endl;
//    delete p;

//    CompositeUnit* army = new CompositeUnit(new Horseman);
//
//    std::cout << "Roman army damaging strength is " << army->getStrength() << std::endl;
//    delete army;


    auto* g = new strategySort(new CompositeHeadCount(new RobustAlgHeadCount));
    std::vector<int> exampl_8 = {1, 35, 0, 34, 16, 0, 35};
    g->sort(exampl_8);
    for (auto &data:exampl_8) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    delete g;

    auto* q = new strategySort(new CompositeHeadCount(new SimplAlgHeadCount));
    std::vector<int> exampl_9 = {34, 34, 0, 0, 35};
    q->sort(exampl_9);
    for (auto &data:exampl_9) {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    delete q;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
