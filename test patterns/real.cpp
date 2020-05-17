
#include <vector>
#include "real.h"

void swapVec (int * a, int * b) {
    int tmp;
    tmp = * a;
    * a = * b;
    * b= tmp;
}

void SelectionSort::sort(std::vector<int> &vec)  {
    unsigned int i, j, min_idx;

    //! One by one move boundary of unsorted subarray
    for (i = 0; i < vec.size() - 1; i++)  {

        //! Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < vec.size(); j++)
            if (vec[j] < vec[min_idx])
                min_idx = j;

        //! Swap the found minimum element with the first element
        swapVec(&vec[min_idx], &vec[i]);            //!
    }
}

//******************************************************************************************

void InsertionSort::sort(std::vector<int> &vec){
    int key;
    int j;
    for(int i = 1; i < vec.size(); i++){
        key = vec[i];
        j = i - 1;
        //! if previous element is bigger than current
        //! current = value of previous
        while((j >= 0) && (vec[j] > key)){
            vec[j+1] = vec[j];  //!
            j--;
        }
        vec[j+1] = key;         //!
    }
}
