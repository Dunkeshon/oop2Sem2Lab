#include "strategysortnavigation.h"



StrategySortNavigation::StrategySortNavigation(QObject *parent): QObject(parent)
{
    m_strategy=nullptr;
}


/*
 * @brief sort your array, based on what sort you have selected earlier
 * @details you need to randomizeVector and selectSort firstly
*/

void StrategySortNavigation::sort()
{
    if(!m_strategy){
        throw("m_strategy == nullptr .You need to select sort firstly");
    }
    else if(vectorToSort.empty()){
        throw("Your vector is empty.You need to create it firstly");
    }
    else{
        m_strategy->sort(vectorToSort);
    }
}

/*
  * @param howManyNumbers - size of array we want to create
  * @param from - begin of randomizing range
  * @param to - end of randomizing range
*/
void StrategySortNavigation::randomizeVector(int howManyNumbers, int from, int to){
    for( int i = 0; i < howManyNumbers;i++){
        vectorToSort.push_back(Randomizing::generateRandomInt(from,to));
    }
}

/*
  *brief creates m_strategy of needed sort, based on enums
*/
void StrategySortNavigation::selectSort(SortsEnums::SortChoice choosenSort){
    // TO DO
    // factory switch case based on enum
    // m_strategy = classCreatedByFactory
    switch (choosenSort) {
    case SortsEnums::SortChoice ::INSERTION_SORT : std::cout<< "you choosed INSERTION_SORT"<<std::endl;
        break;
    case SortsEnums::SortChoice ::QUICK_SORT : std::cout<< "you choosed QUICK_SORT"<<std::endl;
        break;
    case SortsEnums::SortChoice ::MERGE_RECURSIVE_SORT : std::cout<< "you choosed MERGE_RECURSIVE_SORT"<<std::endl;
        break;
    case SortsEnums::SortChoice ::MERGE_ITERATIVE_SORT : std::cout<< "you choosed MERGE_ITERATIVE_SORT"<<std::endl;
        break;
        // TO DO
    default:
        throw ("Wrong enum ");
        break;

    }

}
