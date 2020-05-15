#ifndef STRATEGYSORTNAVIGATION_H
#define STRATEGYSORTNAVIGATION_H

#include <iostream>
#include "sortfactory.h"
#include "strategysort.h"
#include "randomize.h"
#include <QObject>

using std::vector ;
class StrategySortNavigation : public QObject
{
    Q_OBJECT
private:
    sortAlgorithms* m_strategy;
public:
    StrategySortNavigation(QObject *parent = nullptr);

    vector<int> vectorToSort;

    /*
     * @brief sort your array, based on what sort you have selected earlier
     * @details you need to randomizeVector and selectSort firstly
    */
    void sort() ;
    /*
      * @param howManyNumbers - size of array we want to create
      * @param from - begin of randomizing range
      * @param to - end of randomizing range
    */
   Q_INVOKABLE void randomizeVector(int howManyNumbers , int from , int to );
    /*
      *brief creates m_strategy of needed sort, based on enums
    */
   Q_INVOKABLE void selectSort(SortsEnums::SortChoice choosenSort);
};

#endif // STRATEGYSORTNAVIGATION_H
