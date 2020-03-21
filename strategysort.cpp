#include "strategysort.h"

void insertionSort::sort(std::vector<int> &vec){
    int key;
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

void quickSort::swapVec (int * a, int * b) {
    int tmp;
    tmp = * a;
    * a = * b;
    * b= tmp;
}

int quickSort::partitionVec (std::vector<int> &vec, int l, int h) {
    int line = vec[h];
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

void quickSort::quickSVec(std::vector<int> &vec, int l, int h) {
    if (l < h) {
        int line = partitionVec(vec, l, h);
        quickSVec(vec, l, line - 1);
        quickSVec(vec, line + 1, h);
    }
}

void quickSort::sort(std::vector<int> &vec) {
    quickSVec(vec, 0, vec.size()-1);
}

void mergeSort::mergeVec(std::vector<int> &vec, int l, int c, int r) {
    int i, j, k;
    int n1 = c - l + 1;
    int n2 =  r - c;
    int L[n1], R[n2];
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

void recMerge::mergeRecVec(std::vector<int> &vec, int left, int right) {
    if (left < right) {
        int center = left+(right-left)/2;
        mergeRecVec(vec, left, center);
        mergeRecVec(vec, center+1, right);
        mergeVec(vec, left, center, right);
    }
}

void recMerge::sort(std::vector<int> &vec) {
    mergeRecVec(vec, 0, vec.size()-1);
}

void iterationMerge::sort(std::vector<int> &vec) {
    int n = vec.size();
    int currSize;
    int lStart;
       for (currSize = 1; currSize <= n-1; currSize = 2 * currSize) {
           for (lStart = 0; lStart < n-1; lStart += 2 * currSize) {
               int mid = min(lStart + currSize - 1, n - 1);
               int rEnd = min(lStart + 2 * currSize - 1, n - 1);
               mergeVec(vec, lStart, mid, rEnd);
           }
       }
}








