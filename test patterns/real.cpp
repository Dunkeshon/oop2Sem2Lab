#include "iostream"
#include "algorithm"
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
    //std::cout << "HELLO" << std::endl;
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

//******************************************************************************************

int QuickSort::partitionVec (std::vector<int> &vec, int l, int h) {
    int line = vec[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++) {
        if (vec[j] < line) {
            i++;
            swapVec (&vec[i], &vec[j]);    //!
        }
    }
    swapVec (&vec[i + 1], &vec[h]);        //!
    return (i + 1);
}

void QuickSort::quickSVec(std::vector<int> &vec, int l, int h) {
    if (l < h) {
        int line = partitionVec(vec, l, h);
        quickSVec(vec, l, line - 1);
        quickSVec(vec, line + 1, h);
    }
}

void QuickSort::sort(std::vector<int> &vec) {
    int n = vec.size();
    quickSVec(vec, 0,  n- 1);
}

void MergeSort::mergeVec(std::vector<int> &vec, int l, int c, int r) {
    //std::cout << "step 3" << std::endl;
    int i, j, k;
    int n1 = c - l + 1;
    int n2 =  r - c;

    //!create temp arrays
    int L[n1], R[n2];

    //!Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = vec[l + i];
    for (j = 0; j < n2; j++)
        R[j] = vec[c + 1+ j];

    i = 0;   //!Initial index of first subarray
    j = 0;   //!Initial index of second subarray
    k = l;   //!Initial index of merged subarray

    //!Merge the temp arrays back into vec[l..r]
    while (i < n1 && j < n2) {
        if (L[i] < R[j]) {
            vec[k] = L[i];          //!
            i++;
        }
        else {
            vec[k] = R[j];          //!
            j++;
        }
        k++;
    }

    //!Copy the remaining elements of L[], if there are any
    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }

    //!Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        vec[k] = R[j];
        j++;
        k++;
    }
}

void RecMerge::mergeRecVec(std::vector<int> &vec, int left, int right) {
    //std::cout << "step 2" << std::endl;
    if (left < right) {
        int center = left+(right-left)/2;

        //! Sort first and second halves
        mergeRecVec(vec, left, center);
        mergeRecVec(vec, center+1, right);

        mergeVec(vec, left, center, right);
    }
}

void RecMerge::sort(std::vector<int> &vec) {
    int n = vec.size();
    //std::cout << "step 1" << std::endl;
    mergeRecVec(vec, 0, n-1);
}

void IterationMerge::sort(std::vector<int> &vec) {
    int n = vec.size();
    int currSize;
    int lStart;
    for (currSize = 1; currSize <= n-1; currSize = 2 * currSize) {

        //! Pick starting point of different subarrays of current size
        for (lStart = 0; lStart < n-1; lStart += 2 * currSize) {

            //!Find ending point of left subarray. mid+1 is starting
            int mid = min(lStart + currSize - 1, n - 1);
            int rEnd = min(lStart + 2 * currSize - 1, n - 1);

            //! Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
            mergeVec(vec, lStart, mid, rEnd);
        }
    }
}

//******************************************************************************************

void Radix::sort(std::vector<int> &vec) {
    sorts(vec);
}

void Radix::sorts(std::vector<int> &vec) {
    next->sorts(vec);
}

void MsdRadix::msd_radix_sort(int *first, int *last, int msb)
{
    if (first != last && msb >= 0)
    {

        int *mid = std::partition(first, last, Radix_test(msb));

        //! decrement most-significant-bit
        msb--;

        //!sort left partition
        msd_radix_sort(first, mid, msb);

        //!sort right partition
        msd_radix_sort(mid, last, msb);
    }
}

void MsdRadix::sorts(std::vector<int> &vec) {
    int num[vec.size()];
    std::copy( vec.begin(), vec.end(), num );

    msd_radix_sort(num, num + vec.size());

    for (unsigned int i = 0; i < vec.size(); i++) {
        vec[i] = num[i];
    }
}

//******************************************************************************************

void LsdRadix::sorts(std::vector<int> &vec) {
    std::cout << "step_1" << std::endl;
    int m = getMax(vec);
    std::cout << "step_1.5" << std::endl;
    int test = m;
    for (int exp = 1; m/exp > 0; exp = exp*10) {
        std::cout << "step_newwwwwwwwwwwwwwww" << m/exp << std::endl;
        countSort(vec, exp);
    }
}

void LsdRadix::countSort(std::vector<int> &vec, int exp) {
    std::cout << "step_2" << std::endl;
    int n = vec.size();
    std::vector<int> output = {0}; //--------------------------------------------------------------
    int i, count[10] = {0};
    std::cout << "step_3" << std::endl;
    //!Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (vec[i]/exp)%10 ]++;
    std::cout << "step_4" << std::endl;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        //std::cout << output[count[(vec[i]/exp)%10] - 1] << std::endl;
        std::cout << vec[i] << std::endl;
        output[count[ (vec[i]/exp)%10 ] - 1] = vec[i];  //!
        std::cout << "step_5" << std::endl;
        count[ (vec[i]/exp)%10 ]--;
    }
    std::cout << "step_6" << std::endl;
    for (i = 0; i < n; i++)
        vec[i] = output[i];
    std::cout << "step_7" << std::endl;
}

int LsdRadix::getMax(std::vector<int> &vec) {
    int n = vec.size();
    int mx = vec[0];
    for (int i = 1; i < n; i++)
        if (vec[i] > mx)
            mx = vec[i];
    return mx;
}


//void HeadCount::setHelper(std::vector<int> helping) {
//    for (int i = 0; i < helping.size(); i++) {
//        helper.push_back(helping[i]);
//    }
//    std::cout << "suka " << helper.size() << std::endl;
//}
//
//std::vector<int> HeadCount::getHelper() {
//    std::cout << "zaebal " << helper.size() << std::endl;
//    return helper;
//}
std::vector<int> helper; ///////////////////////////

void CompositeHeadCount::sort(std::vector<int> &vec) {
    helper.clear(); /////////////////////////////////
    int maxim = vec[0];
    for (unsigned int i = 1; i < vec.size(); i++) {
        if (maxim < vec[i]) maxim = vec[i];
    }
    for (int i = 0; i <= maxim; i++) {///////////////////////////////////
        helper.push_back(0);
    }
    for (unsigned int i = 0; i < vec.size(); i++) {
        helper[vec[i]] = helper[vec[i]] + 1;
    }
    headCountStrategy->sort(vec);
}

void SimplAlgHeadCount::sort(std::vector<int> &vec) {
    int b = 0;
    for (unsigned int i = 0; i < helper.size(); i++){
        for (int j = 0; j < helper[i]; j++) {

            vec[b] = i;         //!
            b = b + 1;
        }
    }
}

void RobustAlgHeadCount::sort(std::vector<int> &vec) {
    std::vector<int> finalVec;
    for (unsigned int i = 0; i < vec.size(); i++){ ////////////////////////////////
        finalVec.push_back(0);
    }
    for (unsigned int i = 0; i < helper.size(); i++){
        std::cout << i << " " << helper[i] << std::endl;
    }
    for (unsigned int i = 1; i < helper.size(); i++){
        helper[i] = helper[i] + helper[i - 1];////////////////////////////////////////////
    }
    for (int j = vec.size() - 1; j >= 0; j--) {
        helper[vec[j]] = helper[vec[j]] - 1;
        finalVec[helper[vec[j]]] = vec[j];
    }
    for (unsigned int i = 0; i < vec.size(); i++) {
        vec[i] = finalVec[i];
    }
}