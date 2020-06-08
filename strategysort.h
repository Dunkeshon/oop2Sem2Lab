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
        SELECTION_SORT,
        INSERTION_SORT,
        QUICK_SORT,
        MERGE_RECURSIVE_SORT,
        MERGE_ITERATIVE_SORT,
        LSD_RADIX,
        MSD_RADIX,
        SIMPLE_HEAD_COUNT,
        ROBUST_HEAD_COUNT
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

/*!
 * \brief The SelectionSort class - represent the selection sort algorithm
 * inheritor of class sortAlgorithm
 */
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
 * \brief pattern Chain of Responsibility
 * \details have class Radix       - main class of pattern
 *                                   next - pointer to the class of choosen sort
 * make object of class Radix and give to the pointer "next" object of choosen class
 */
class Radix : public SortAlgorithms
{
    Radix *next;
public:
    Radix() {}
    Radix(Radix *n) {
        next = n;
    }
    void sort(std::vector<int> &vec) override;
    virtual void sorts(std::vector<int> &vec);
};

/*!
 * \brief The MsdRadix class - msd radix sort algorithm
 * \details radix sort that go from first rank to the last (from hundreds to tenths)
 */
class MsdRadix : public Radix
{
public:
    void sorts(std::vector<int> &vec);

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

/*!
 * \brief The LsdRadix class - lsd radix sort algorithm
 * \details radix sort that go from last rank to the first (from tenths to hundreds)
 */
class LsdRadix : public Radix
{
public:
    void sorts(std::vector<int> &vec);

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

//! Composite class
/*!
 * \brief The CompositeHeadCount class - main class of this kind of sorting
 * (we will create objects of this class when use it)
 * \details classic function "sort" that will make some algorithm
 * and than call one of the primitive "sort"(function from classses SimplAlgHeadCount or RobustAlgHeadCount)
 */
class CompositeHeadCount: public HeadCount
{
public:
    void sort(std::vector<int> &vec) override;

        CompositeHeadCount( HeadCount* comp) { headCountStrategy = comp;}
        ~CompositeHeadCount() { delete headCountStrategy; }
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
