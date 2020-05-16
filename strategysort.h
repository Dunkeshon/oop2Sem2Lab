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

/*!
 * \brief The insertionSort class - realisation of insertion sort algorithm
 * inheritor of class sortAlgorithm
 */
class InsertionSort : public SortAlgorithms
{
public:
    void sort(std::vector<int> &vec) override;
};

/*!
 * \brief The quickSort class
 */
class QuickSort : public SortAlgorithms
{
public:
    void sort(std::vector<int> &vec) override;
    void quickSVec(std::vector<int> &vec, int l, int h);
    int partitionVec (std::vector<int> &vec, int l, int h);
    void swapVec (int * a, int * b);
};

//Realization of pattern Template Method
class MergeSort : public SortAlgorithms
{
public:
    //make a constructor maybe
    virtual void sort(std::vector<int> &vec) = 0;
    //virtual void mergeSVec(std::vector<int> &vec, int left, int right) = 0;
    void mergeVec(std::vector<int> &vec, int l, int c, int r);//
};

class RecMerge : public MergeSort
{
public:
    void sort(std::vector<int> &vec);
    void mergeRecVec(std::vector<int> &vec, int left, int right);
};
class IterationMerge : public MergeSort
{
public:
    int min(int x, int y) { return (x<y)? x :y; }
    void sort(std::vector<int> &vec);
};
//end of pattern Template Method

class MsdRadix : public SortAlgorithms
{
public:
    void sort(std::vector<int> &vec);
    void msd_radix_sort(int *first, int *last, int msb = 31);
};
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
class LsdRadix : public SortAlgorithms
{
public:
    void sort(std::vector<int> &vec);
    void countSort(std::vector<int> &vec, int exp);
    int getMax(std::vector<int> &vec);
};

//Component pattern
//Component
class HeadCount : public SortAlgorithms
{
public:
    virtual void sort(std::vector<int> &vec, std::vector<int> vecHelp) = 0 ;
    virtual ~HeadCount() {}
};

//Primitives
class SimplAlgHeadCount: public HeadCount
{
public:
    virtual void sort(std::vector<int> &vec, std::vector<int> vecHelp);
};

class RobustAlgHeadCount: public HeadCount
{
public:
    virtual void sort(std::vector<int> &vec, std::vector<int> vecHelp);
};

// Composite
class CompositeHeadCount: public HeadCount
{
public:
    CompositeHeadCount( HeadCount* comp): headCountStrategy(comp) {}
    void sort(std::vector<int> &vec, std::vector<int> c = {0}) {
        int maxim = vec[0];
        for (unsigned int i = 1; i < vec.size(); i++) {
            if (maxim < vec[i]) maxim = vec[i];
        }
        //std::vector<int> c(maxim);
        for (int i = 0; i <= maxim; i++) {
            c[i] = 0;
        }
        for (unsigned int i = 0; i < vec.size(); i++) {
            c[vec[i]] = c[vec[i]] + 1;
        }
        headCountStrategy->sort(vec, c);
    }
    ~CompositeHeadCount() { delete headCountStrategy; }
private:
    HeadCount* headCountStrategy;
};
//end of composite Pattern



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
