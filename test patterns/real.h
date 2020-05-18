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

class QuickSort : public SortAlgorithms
{
public:
    void sort(std::vector<int> &vec) override;

    static void quickSVec(std::vector<int> &vec, int l, int h);
    static int partitionVec (std::vector<int> &vec, int l, int h);
};

//***************************************************************************************

class MergeSort : public SortAlgorithms
{
public:
    void sort(std::vector<int> &vec) override = 0;

    //make a constructor maybe
    static void mergeVec(std::vector<int> &vec, int l, int c, int r);
};

/*!
 * \brief The RecMerge class - recursive merge sort algorithm
 */
class RecMerge : public MergeSort
{
public:
    void sort(std::vector<int> &vec) override;

    static void mergeRecVec(std::vector<int> &vec, int left, int right);
};

/*!
 * \brief The IterationMerge class - iterative merge sort algorithm
 */
class IterationMerge : public MergeSort
{
public:
    void sort(std::vector<int> &vec) override;

    static int min(int x, int y) { return (x<y)? x :y; }
};

//***************************************************************************************

class Radix : public SortAlgorithms
{
    Radix *next;
public:
    Radix() {next = nullptr;}
    explicit Radix(Radix *n) {next = n;}
    void sort(std::vector<int> &vec) override;
    virtual void sorts(std::vector<int> &vec);
};

class MsdRadix : public Radix
{
public:
    void sorts(std::vector<int> &vec) override;

    static void msd_radix_sort(int *first, int *last, int msb = 31);
};

class Radix_test : public MsdRadix
{
    const int bit;
public:
    explicit Radix_test(int offset) : bit(offset) {
    }

    bool operator()(int value) const
    {
        if (bit == 31)
            return value < 0;
        else return !(value & (1 << bit));
    }
};

class LsdRadix : public Radix
{
public:
    void sorts(std::vector<int> &vec) override;

    static void countSort(std::vector<int> &vec, int exp);
    static int getMax(std::vector<int> &vec);
};



class HeadCount : public SortAlgorithms
{
public:
    virtual ~HeadCount() {}
};

//! Primitive class
class SimplAlgHeadCount: public HeadCount
{
public:
    virtual void sort(std::vector<int> &vec);
};
//! Primitive class
class RobustAlgHeadCount: public HeadCount
{
public:
    virtual void sort(std::vector<int> &vec);
};

class CompositeHeadCount: public HeadCount
{
public:
    void sort(std::vector<int> &vec) override;

    CompositeHeadCount( HeadCount* comp) { headCountStrategy = comp;}
    ~CompositeHeadCount() { delete headCountStrategy; }
private:
    HeadCount* headCountStrategy;
};

//// Component
//class Unit: public SortAlgorithms
//{
//public:
//    virtual int getStrength() = 0;
//    virtual ~Unit() {}
//};
//
//// Primitives
//class Archer: public Unit
//{
//public:
//    virtual int getStrength() {
//        return 1;
//    }
//};
//class Infantryman: public Unit
//{
//public:
//    virtual int getStrength() {
//        return 2;
//    }
//};
//
//class Horseman: public Unit
//{
//public:
//    virtual void sort(std::vector<int> &vec);
//    virtual int getStrength() {
//        return 3;
//    }
//};
//
//// Composite
//class CompositeUnit: public Unit
//{
//public:
//    void sort(std::vector<int> &vec) override;
//    int getStrength() {
//        int total = 0;
//        total = c->getStrength();
//        return total;
//    }
//    CompositeUnit(Unit* p) {
//        c = p;
//    }
//    ~CompositeUnit() {
//        delete c;
//    }
//private:
//    Unit* c;
//};



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
