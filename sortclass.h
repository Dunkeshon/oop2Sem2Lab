#ifndef SORTCLASS_H
#define SORTCLASS_H

#include <ctime>
#include <random>
#include <string>
#include <vector>

using std::string;
using std::vector;

template <typename V>
class sortClass
{
public:
    sortClass();

    void insertionSortVec(std::vector<V> &vec);

    void quickSortVec (std::vector<V> &vec);
    void quickSVec(std::vector<V> &vec, int l, int h);
    int partitionVec (std::vector<V> &vec, int l, int h);
    void swapVec (V * a, V * b);

    void mergeSortVec(std::vector<V> &vec);
    void mergeSVec(std::vector<V> &vec, int left, int right);
    void mergeVec(std::vector<V> &vec, int l, int c, int r);

};

#endif // SORTCLASS_H
