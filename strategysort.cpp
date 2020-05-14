#include "strategysort.h"

void insertionSort::sort(std::vector<int> &vec){
    int key;
    int j;
    for(unsigned int i = 1; i < vec.size(); i++){
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

void SimplAlg::sort(std::vector<int> &vec, std::vector<int> vecHelp) {
    int b = 0;
        for (unsigned int i = 0; i < vecHelp.size(); i++){
            for (int j = 0; j < vecHelp[i]; j++) {
                vec[b] = i;
                b = b + 1;
            }
        }
}

void RobustAlg::sort(std::vector<int> &vec, std::vector<int> vecHelp) {
    std::vector<int> finalVec;
    for (unsigned int i = 1; i < vecHelp.size(); i++){
        vecHelp[i] = vecHelp[i - 1];
    }
    for (unsigned int j = vec.size() - 1; j >= 0; j--) {
        vecHelp[vec[j]] = vecHelp[vec[j]] - 1;
        finalVec[vecHelp[vec[j]]] = vec[j];
    }
    for (unsigned int i = 0; i < vec.size(); i++) {
        vec[i] = finalVec[i];
    }
}

void msdRadix::msd_radix_sort(int *first, int *last, int msb)
{
    if (first != last && msb >= 0)
    {
        //std::cout << " lal" << std::endl;
        int *mid = std::partition(first, last, radix_test(msb));
        //std::cout << " lol" << std::endl;
        msb--; // decrement most-significant-bit
        msd_radix_sort(first, mid, msb); // sort left partition

        msd_radix_sort(mid, last, msb); // sort right partition
    }
}
void msdRadix::sort(std::vector<int> &vec) {
    int num[vec.size()];
    std::copy( vec.begin(), vec.end(), num );
    msd_radix_sort(num, num + vec.size());
    for (unsigned int i = 0; i < vec.size(); i++) {
        vec[i] = num[i];
   }
}

void lsdRadix::sort(std::vector<int> &vec) {
    int m = getMax(vec);
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(vec, exp);
}
void lsdRadix::countSort(std::vector<int> &vec, int exp) {
    int n = vec.size();
    std::vector<int> output;
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[ (vec[i]/exp)%10 ]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[ (vec[i]/exp)%10 ] - 1] = vec[i];
        count[ (vec[i]/exp)%10 ]--;
    }
    for (i = 0; i < n; i++)
        vec[i] = output[i];
}
int lsdRadix::getMax(std::vector<int> &vec) {
    int n = vec.size();
    int mx = vec[0];
    for (int i = 1; i < n; i++)
        if (vec[i] > mx)
            mx = vec[i];
    return mx;
}






