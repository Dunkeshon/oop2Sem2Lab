#include "strategysort.h"
#include <algorithm>

/*!
 * \brief swapVec change values of two elements
 * \details it is used several times so it is here
 */
void swapVec (int * a, int * b) {
    int tmp;
    tmp = * a;
    * a = * b;
    * b= tmp;
}

//******************************************************************************************

/*!
 * \brief SelectionSort::sort - algorith of selection sort
 * \param vec - vector that is needed to be sort
 */
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

/*!
 * \brief InsertionSort::sort - algorithm of insertion sort
 * \param vec - vector that is needed to be sorted
 */
void InsertionSort::sort(std::vector<int> &vec){
    int key;
    int j;
    for(unsigned int i = 1; i < vec.size(); i++){
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

/*!
 * \brief QuickSort::partitionVec
 * \param vec - vector that is needed to be sort
 * \param l - index of the firt element of the current vec
 * \param h - index of the last element of the current vec
 * \return index of element from which we divide the vector by 2 parts
 */
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

/*!
 * \brief QuickSort::quickSVec
 * \param l - index of the firt element of the current vec
 * \param h - index of the last element of the current vec
 */
void QuickSort::quickSVec(std::vector<int> &vec, int l, int h) {
    if (l < h) {
        int line = partitionVec(vec, l, h);
        quickSVec(vec, l, line - 1);
        quickSVec(vec, line + 1, h);
    }
}

/*!
 * \brief QuickSort::sort main function that will call quickSVec
 */
void QuickSort::sort(std::vector<int> &vec) {
    quickSVec(vec, 0, vec.size()-1);
}

//******************************************************************************************

/*!
 * \brief MergeSort::mergeVec - Merges two subarrays of vec[]
 * \details first subarray is vec[l..c]
 *          second subarray is vec[c+1..r]
 * \param vec
 * \param l - left index of first subarray
 * \param c - right index of first subarray
 * \param r - right index of second subarray
 */
void MergeSort::mergeVec(std::vector<int> &vec, int l, int c, int r) {
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

/*!
 * \brief RecMerge::mergeRecVec - recursive merge vector
 * \param left is for left index of the sub-array of vec to be sorted
 * \param right is right index of the sub-array of vec to be sorted
 */
void RecMerge::mergeRecVec(std::vector<int> &vec, int left, int right) {
    if (left < right) {
        int center = left+(right-left)/2;

        //! Sort first and second halves
        mergeRecVec(vec, left, center);
        mergeRecVec(vec, center+1, right);

        mergeVec(vec, left, center, right);
    }
}

/*!
 * \brief RecMerge::sort main function that will call mergeRecVec
 */
void RecMerge::sort(std::vector<int> &vec) {
    mergeRecVec(vec, 0, vec.size()-1);
}

/*!
 * \brief IterationMerge::sort Merge subarrays in bottom up manner.
 * \details  First merge subarrays of size 1 to create sorted subarrays of size 2,
 *  then merge subarrays of size 2 to create sorted subarrays of size 4, and so on.
 */
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

/*!
 * \brief CompositeHeadCount::sort main function that will cal sorts of CompositeHeadCount class
 */
void CompositeHeadCount::sort(std::vector<int> &vec) {
    sorts(vec);
}

/*!
 * \brief CompositeHeadCount::sorts Composite sort that will call SimplAlgHeadCount::sorts or RobustAlgHeadCount::sorts
 * (it depends on object that will headCountStrategy consits)
 * \param vec - vector that is needed to be sort
 * \param c - supporting vector
 */
void CompositeHeadCount::sorts(std::vector<int> &vec, std::vector<int> c) {
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
    headCountStrategy->sorts(vec, c);
}

/*!
 * \brief SimplAlgHeadCount::sorts simplest algorithm of headCount
 * \details it just go in vecHelp and gives indexes of it to  our vec (go to wiki for details)
 * \param vec - vector that is needed to be sort
 * \param vecHelp - supporting vector
 */
void SimplAlgHeadCount::sorts(std::vector<int> &vec, std::vector<int> vecHelp) {
    int b = 0;
        for (unsigned int i = 0; i < vecHelp.size(); i++){
            for (int j = 0; j < vecHelp[i]; j++) {

                vec[b] = i;         //!
                b = b + 1;
            }
        }
}

/*!
 * \brief RobustAlgHeadCount::sorts "strong" algorithm
 * \details make sorted "finalvec" from elements of vector "vec"
 */
void RobustAlgHeadCount::sorts(std::vector<int> &vec, std::vector<int> vecHelp) {
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

//******************************************************************************************

/*!
 * \brief Radix::sort main function of class Radix
 */
void Radix::sort(std::vector<int> &vec) {
   sorts(vec);
}

/*!
 * \brief Radix::sorts variable next(object of class of needed algorithm) call class MsdRadix or LsdRadix
 *  that represents needed algorithm
 */
void Radix::sorts(std::vector<int> &vec) {
    next->sorts(vec);
}

/*!
 * \brief MsdRadix::msd_radix_sort - msd radix
 * \param first - first element of sub-array
 * \param last - last element of sub-array
 * \param msb - number of current bit
 */
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

/*!
 * \brief MsdRadix::sort - main function of msd radix sort
 */
void MsdRadix::sorts(std::vector<int> &vec) {
    int num[vec.size()];
    std::copy( vec.begin(), vec.end(), num );

    msd_radix_sort(num, num + vec.size());

    for (unsigned int i = 0; i < vec.size(); i++) {
        vec[i] = num[i];
   }
}

//******************************************************************************************

/*!
 * \brief LsdRadix::sort - main function of lsd radix sort
 * \param vec - vector that is needed to be sort
 */
void LsdRadix::sorts(std::vector<int> &vec) {
    int m = getMax(vec);
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(vec, exp);
}

/*!
 * \brief LsdRadix::countSort - a function to do counting sort of vec
 *  according to the digit represented by exp
 * \param exp - grade of number (tenth/hundreds)
 */
void LsdRadix::countSort(std::vector<int> &vec, int exp) {
    int n = vec.size();
    std::vector<int> output = {0};
    int i, count[10] = {0};

    //!Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (vec[i]/exp)%10 ]++;

    //!Change count[i] so that count[i] now contains actual position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    //! Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[ (vec[i]/exp)%10 ] - 1] = vec[i];  //!
        count[ (vec[i]/exp)%10 ]--;
    }
    for (i = 0; i < n; i++)
        vec[i] = output[i];
}

/*!
 * \brief LsdRadix::getMax - function that return maximum of vector
 * \return maximum of the vector
 */
int LsdRadix::getMax(std::vector<int> &vec) {
    int n = vec.size();
    int mx = vec[0];
    for (int i = 1; i < n; i++)
        if (vec[i] > mx)
            mx = vec[i];
    return mx;
}






