#include "sortclass.h"


bool operator< (std::string str1, std::string str2) {
    //bool res;
    char cstr1[str1.size() + 1];
    strcpy(cstr1, str1.c_str());
    char cstr2[str2.size() + 1];
    strcpy(cstr2, str2.c_str());
    return strcmp(cstr1, cstr2) < 0;
}
bool operator> (std::string str1, std::string str2) {
    return str2 < str1;
}

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

template <typename V>
void sortClass<V>::swapVec (V * a, V * b) {
    V tmp;
    tmp = * a;
    * a = * b;
    * b= tmp;
}

template <typename V>
int sortClass<V>::partitionVec (std::vector<V> &vec, int l, int h) {
    V line = vec[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++) {
        if (vec[j] < line) {
            i++;
            swapVec (&vec[i], &vec[j]);
        }
    }
    swapVec (&vec[i + 1], &vec[h]);
    return (i + 1);
}

template <typename V>
void sortClass<V>::quickSVec(std::vector<V> &vec, int l, int h) {
    if (l < h) {
        int line = partitionVec(vec, l, h);
        quickSVec(vec, l, line - 1);
        quickSVec(vec, line + 1, h);
    }
}

template <typename V>
void sortClass<V>::quickSortVec (std::vector<V> &vec) {
    quickSVec(vec, 0, vec.size()-1);
}

template <typename V>
void sortClass<V>::mergeVec(std::vector<V> &vec, int l, int c, int r) {
    int i, j, k;
    int n1 = c - l + 1;
    int n2 =  r - c;
    V L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = vec[l + i];
    for (j = 0; j < n2; j++)
        R[j] = vec[c + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] < R[j]) {
            vec[k] = L[i];
            i++;
        }
        else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        vec[k] = R[j];
        j++;
        k++;
    }
}

template <typename V>
void sortClass<V>::mergeSVec(std::vector<V> &vec, int left, int right) {
    if (left < right) {
        int center = left+(right-left)/2;
        mergeSVec(vec, left, center);
        mergeSVec(vec, center+1, right);
        mergeVec(vec, left, center, right);
    }
}

template <typename V>
void sortClass<V>::mergeSortVec(std::vector<V> &vec) {
    mergeSVec(vec, 0, vec.size()-1);
}
