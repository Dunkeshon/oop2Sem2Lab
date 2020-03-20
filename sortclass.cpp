#include "sortclass.h"

template <typename V>
sortClass<V>::sortClass()
{

}

template <typename V>
void sortClass<V>::insertionSortVec(std::vector<V> &vec){
    V key;
    int j;
    for(int i = 1; i < vec.size(); i++){
        key = vec[i];
        j = i - 1;
        while((j>=0) && (vec[j]>key)){
            vec[j+1] = vec[j];
            j--;
        }
        vec[j+1] = key;
    }
}
