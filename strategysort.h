#ifndef STRATEGYSORT_H
#define STRATEGYSORT_H

#include <ctime>
#include <random>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using std::string;
using std::vector;

class sortAlgorithms
{
  public:
    virtual ~sortAlgorithms() {}
    virtual void sort(std::vector<int> &vec) {}
};

class insertionSort : public sortAlgorithms
{
  public:
    void sort(std::vector<int> &vec);
};

class quickSort : public sortAlgorithms
{
  public:
    void sort(std::vector<int> &vec);
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
    const int bit; // bit position [0..31] to examine
public:
    radix_test(int offset) : bit(offset) {
    }

    bool operator()(int value) const // function call operator
    {
        //std::cout << value << " " << bit << std::endl;
        if (bit == 31) // sign bit
            return value < 0; // negative int to left partition
        else {
            //if (!(value & (1 << bit)) == true) std::cout << "bitch";
            //else std::cout << "no bitch";
            //std::cout << " -" << (1<<bit) << "- ";
            return !(value & (1 << bit)); // 0 bit to left partition
        }
    }
};




//Component pattern
//Component
class headCount : public sortAlgorithms
{
  public:
    virtual void sort(std::vector<int> &vec, std::vector<int> vecHelp) = 0;
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
        for (int i = 1; i < vec.size(); i++) {
            if (maxim < vec[i]) maxim = vec[i];
        }
        //std::vector<int> c(maxim);
        for (int i = 0; i <= maxim; i++) {
            c[i] = 0;
        }
        for (int i = 0; i < vec.size(); i++) {
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
  public:
    strategySort( sortAlgorithms* comp): strategy(comp) {}
   ~strategySort() { delete strategy; }
    void sort(std::vector<int> &vec) {
      strategy->sort(vec);
    }
  private:
    sortAlgorithms* strategy;
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
