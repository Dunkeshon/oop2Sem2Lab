#ifndef STRATEGYSORT_H
#define STRATEGYSORT_H

#include <ctime>
#include <random>
#include <string>
#include <vector>
#include <cstring>

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
  strategySort* p = new strategySort(new mergeSort);
  p->sort({2, 1, 7, 4});
  delete p;
  return 0;
}
*/
#endif // STRATEGYSORT_H
