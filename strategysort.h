#ifndef STRATEGYSORT_H
#define STRATEGYSORT_H


#include <string>
#include <vector>
#include <algorithm>
#include <QObject>

using std::string;
using std::vector;

class SortsEnums : public QObject{
    Q_GADGET
public:
    enum SortChoice{
        INSERTION_SORT,
        QUICK_SORT,
        MERGE_RECURSIVE_SORT,
        MERGE_ITERATIVE_SORT,
        LSD_RADIX,
        MSD_RADIX
    };
    Q_ENUM(SortChoice)
};

/*!
 * \brief Pattern strategy
 * \details Main pattern of the project that includes all sorting
 */
class SortAlgorithms
{
public:

    virtual ~SortAlgorithms() {}
    /*!
     * \brief sort is virtual function (all sortings have different realization of this function)
     * \param vec - vector of variables that is needed to sort
     */
    virtual void sort(std::vector<int> &vec) = 0;

};

//****************************************************************************************

class SelectionSort : public SortAlgorithms
{
public:
    void sort(std::vector<int> &vec) override;
};

//****************************************************************************************

/*!
 * \brief The insertionSort class - represent the insertion sort algorithm
 * inheritor of class sortAlgorithm
 */
class InsertionSort : public SortAlgorithms
{
public:   
    void sort(std::vector<int> &vec) override;
};

//***************************************************************************************

/*!
 * \brief The quickSort class - represent the quick sort algorithm
 */
class QuickSort : public SortAlgorithms
{
public:
    void sort(std::vector<int> &vec) override;

    void quickSVec(std::vector<int> &vec, int l, int h);
    int partitionVec (std::vector<int> &vec, int l, int h);
    void swapVec (int * a, int * b);
};

//***************************************************************************************

/*!
 * \brief pattern Template Method
 * \details have class MergeSort      - main class of the pattern
 *                     RecMerge       - inheritor of class MergeSort that represent recursive merge sort
 *                     IterationMerge - inheritor of class MergeSort that represent iteration merge sort
 */
class MergeSort : public SortAlgorithms
{
public:
    virtual void sort(std::vector<int> &vec) = 0;

    //make a constructor maybe
    void mergeVec(std::vector<int> &vec, int l, int c, int r);
};

/*!
 * \brief The RecMerge class - recursive merge sort algorithm
 */
class RecMerge : public MergeSort
{
public:
    void sort(std::vector<int> &vec);

    void mergeRecVec(std::vector<int> &vec, int left, int right);
};

/*!
 * \brief The IterationMerge class - iterative merge sort algorithm
 */
class IterationMerge : public MergeSort
{
public:
     void sort(std::vector<int> &vec);

    int min(int x, int y) { return (x<y)? x :y; }
};

//***************************************************************************************

/*!
 * \brief The MsdRadix class - msd radix sort algorithm
 * \details radix sort that go from first rank to the last (from hundreds to tenths)
 */
class MsdRadix : public SortAlgorithms
{
public:
    void sort(std::vector<int> &vec);

    void msd_radix_sort(int *first, int *last, int msb = 31);
};
/*!
 * \brief The Radix_test class - it is supporting class for MsdRadix::sort
 * (I recommend you don`t take\change\breathe on it)
 */
class Radix_test : public MsdRadix
{
    const int bit;
public:
    Radix_test(int offset) : bit(offset) {
    }

    bool operator()(int value) const
    {
        if (bit == 31)
            return value < 0;
        else return !(value & (1 << bit));
    }
};

//***************************************************************************************

/*!
 * \brief The LsdRadix class - lsd radix sort algorithm
 * \details radix sort that go from last rank to the first (from tenths to hundreds)
 */
class LsdRadix : public SortAlgorithms
{
public:
    void sort(std::vector<int> &vec);

    void countSort(std::vector<int> &vec, int exp);
    int getMax(std::vector<int> &vec);
};

//***************************************************************************************

/*!
 * \brief Component pattern
 * \details have class HeadCount          - Component abstract base class with behavior common
 *  to primitive and composite objects
 *                     SimplAlgHeadCount  - primitive class that represent simple headcount sort
 *                     RobustAlgHeadCount - primitive class that represent robust headcount sort
 *                     CompositeHeadCount - Composite class stores primitives of the abstract type Component
 */

//! Component class
class HeadCount : public SortAlgorithms
{
public:
    virtual void sorts(std::vector<int> &vec, std::vector<int> vecHelp) = 0 ;

    virtual ~HeadCount() {}
};

//! Primitive class
class SimplAlgHeadCount: public HeadCount
{
public:
    virtual void sorts(std::vector<int> &vec, std::vector<int> vecHelp);
};
//! Primitive class
class RobustAlgHeadCount: public HeadCount
{
public:
    virtual void sorts(std::vector<int> &vec, std::vector<int> vecHelp);
};

//! Composite class
/*!
 * \brief The CompositeHeadCount class - main class of this kind of sorting
 * (we will create objects of this class when use it)
 * \details classic function "sort" will call function "sorts" that will make some algorithm
 * and than call one of the primitive "sort"(function from classses SimplAlgHeadCount or RobustAlgHeadCount)
 */
class CompositeHeadCount: public HeadCount
{
public:
    void sort(std::vector<int> &vec) override;

    CompositeHeadCount( HeadCount* comp): headCountStrategy(comp) {}
    ~CompositeHeadCount() { delete headCountStrategy; }

    void sorts(std::vector<int> &vec, std::vector<int> c = {0}) override;


private:
    HeadCount* headCountStrategy;
};

//***************************************************************************************

/*
 Если бы был бы меин то он выглядел бы как то так:
int main()
{
  strategySort* p = new strategySort(new quickSort);
  p->sort({2, 1, 7, 4});
  delete p;
  return 0;
}
*/
#endif // STRATEGYSORT_H
