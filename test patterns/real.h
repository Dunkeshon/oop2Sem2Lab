#include <vector>
#ifndef TEST_PATTERNS_REAL_H
#define TEST_PATTERNS_REAL_H


class SortAlgorithms
{
public:

    virtual ~SortAlgorithms() = default;
    virtual void sort(std::vector<int> &vec) = 0;

};

//****************************************************************************************

class SelectionSort : public SortAlgorithms
{
public:
    void sort(std::vector<int> &vec) override;
};

//****************************************************************************************

class InsertionSort : public SortAlgorithms
{
public:
    void sort(std::vector<int> &vec) override;
};

//***************************************************************************************

class strategySort
{
public:
    explicit strategySort( SortAlgorithms* comp): strategy(comp) {}
    ~strategySort() { delete strategy; }
    void sort(std::vector<int> &vec) {
        strategy->sort(vec);
    }
private:
    SortAlgorithms* strategy;
};



#endif //TEST_PATTERNS_REAL_H
