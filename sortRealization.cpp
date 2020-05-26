#include "sortRealization.h"

SortRealization::SortRealization(QObject *parent) : QObject(parent)
{

}

vector<int> &SortRealization::getVectorToSort(){
    return m_vectorToSort;
}

SortAlgorithms &SortRealization::getStrategyOfSort(){
    return *m_strategy;
}
/*
  * @param howManyNumbers - size of array we want to create
  * @param from - begin of randomizing range
  * @param to - end of randomizing range
*/
void SortRealization::randomizeVector(int howManyNumbers, int from, int to){
    for( int i = 0; i < howManyNumbers;i++){
        m_vectorToSort.push_back(Randomizing::generateRandomInt(from,to));
    }
    emit vectorToSortChanged(m_vectorToSort);
}

/*
  *brief creates m_strategy of needed sort, based on enums
*/

void SortRealization::selectSort(SortsEnums::SortChoice choosenSort){

    // factory switch case based on enum
    // m_strategy = classCreatedByFactory
    switch (choosenSort) {
    case SortsEnums::SortChoice ::INSERTION_SORT : m_strategy = SortFactory::insertionSort();
        break;
    case SortsEnums::SortChoice ::QUICK_SORT : m_strategy = SortFactory::quickSort();
        break;
    case SortsEnums::SortChoice ::MERGE_RECURSIVE_SORT : m_strategy = SortFactory::recursiveMerge();
        break;
    case SortsEnums::SortChoice ::MERGE_ITERATIVE_SORT : m_strategy = SortFactory::iterationMerge();
        break;
    case SortsEnums::SortChoice ::MSD_RADIX : m_strategy = SortFactory::msdRadix();
        break;
    case SortsEnums::SortChoice ::LSD_RADIX : m_strategy = SortFactory::lsdRadix();
        break;
    case SortsEnums::SortChoice ::SIMPLE_HEAD_COUNT : m_strategy = SortFactory::simpleHeadCount();
        break;
    case SortsEnums::SortChoice ::ROBUST_HEAD_COUNT : m_strategy = SortFactory::robustHeadCount();
        break;
    default:
        qDebug("Wrong enum");
        break;
    }
}
