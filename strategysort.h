#ifndef STRATEGYSORT_H
#define STRATEGYSORT_H


#include <ctime>
#include <random>
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
        MERGE_ITERATIVE_SORT
    };
    Q_ENUM(SortChoice)
};


class sortAlgorithms
{

public:

    virtual ~sortAlgorithms() {}
    virtual void sort(std::vector<int> &vec) = 0;
    //    sortAlgorithms(sortAlgorithms &other) = delete;
    //    sortAlgorithms(const sortAlgorithms &) = delete; 

};

class insertionSort : public sortAlgorithms
{
public:
    void sort(std::vector<int> &vec);
};

class quickSort : public sortAlgorithms
{
public:
    void sort(std::vector<int> &vec) override;
    void quickSVec(std::vector<int> &vec, int l, int h);
    int partitionVec (std::vector<int> &vec, int l, int h);
    void swapVec (int * a, int * b);
};

//Realization of pattern Template Method
class mergeSort : public sortAlgorithms
{
public:
    //make a constructor maybe
    virtual void sort(std::vector<int> &vec) = 0;
    //virtual void mergeSVec(std::vector<int> &vec, int left, int right) = 0;
    void mergeVec(std::vector<int> &vec, int l, int c, int r);//
};

class recMerge : public mergeSort
{
public:
    void sort(std::vector<int> &vec);
    void mergeRecVec(std::vector<int> &vec, int left, int right);
};
class iterationMerge : public mergeSort
{
public:
    int min(int x, int y) { return (x<y)? x :y; }
    void sort(std::vector<int> &vec);
};
//end of pattern Template Method

class msdRadix : public sortAlgorithms
{
public:
    void sort(std::vector<int> &vec);
    void msd_radix_sort(int *first, int *last, int msb = 31);
};
class radix_test : public msdRadix
{
    const int bit;
public:
    radix_test(int offset) : bit(offset) {
    }

    bool operator()(int value) const
    {
        if (bit == 31)
            return value < 0;
        else return !(value & (1 << bit));
    }
};
class lsdRadix : public sortAlgorithms
{
public:
    void sort(std::vector<int> &vec);
    void countSort(std::vector<int> &vec, int exp);
    int getMax(std::vector<int> &vec);
};

//Component pattern
//Component
class headCount : public sortAlgorithms
{
public:
    virtual void sort(std::vector<int> &vec, std::vector<int> vecHelp) = 0 ;
    virtual ~headCount() {}
};

//Primitives
class SimplAlg: public headCount
{
public:
    virtual void sort(std::vector<int> &vec, std::vector<int> vecHelp);
};

class RobustAlg: public headCount
{
public:
    virtual void sort(std::vector<int> &vec, std::vector<int> vecHelp);
};

// Composite
class CompositeHeadCount: public headCount
{
public:
    CompositeHeadCount( headCount* comp): headCountStrategy(comp) {}
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
    headCount* headCountStrategy;
};
//end of composite Pattern

// Класс для использования
class strategySort
{
private:
    sortAlgorithms* m_strategy;

    // generates random integer from given range
    // @param from begin of randomizing range
    // @param to end of randomizing range
    int generate_random_int(int from,int to){
        std::random_device rd;   // non-deterministic generator
        std::mt19937 gen(rd());  // to seed mersenne twister.
        std::uniform_int_distribution<> dist(from,to);
        return dist(gen); // returns generated item
    }

public:
    strategySort( sortAlgorithms* comp): m_strategy(comp) {}
    ~strategySort() { delete m_strategy; }

    std::vector<int> vectorToSort;
    void sort() {
        m_strategy->sort(vectorToSort);
    }

    // @param howManyNumbers
    void randomizeVector(int howManyNumbers , int from , int to ){
        for( int i = 0; i < howManyNumbers;i++){
            vectorToSort.push_back(generate_random_int(from,to));
        }
    }
};


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
