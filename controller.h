#ifndef STRATEGYSORTNAVIGATION_H
#define STRATEGYSORTNAVIGATION_H

#include <iostream>
#include "sortfactory.h"
#include "strategysort.h"
#include "randomize.h"
#include <QObject>
#include <QVector>
#include <QThread>
#include "sortRealization.h"
/*
 * brief this class is responsible for the conversation between ui and the thread,
 * where the sort happens
 * contains singnals and slots connections inside the constructor
 */

using std::vector ;
class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<int> vectorWeSort READ vectorWeSort WRITE setVectorWeSort NOTIFY vectorWeSortChanged)
private:
    SortAlgorithms* m_strategy;

    QVector<int> m_vectorWeSort;

    QThread sortThread; // thread, where we will move sortRealization

    SortRealization *sortRealization;

public:
    Controller(QObject *parent = nullptr);
    ~Controller(){delete m_strategy;}


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

    QVector<int> vectorWeSort() const;

public slots:
    void setVectorWeSort(QVector<int> vectorWeSort)
    {
        if (m_vectorWeSort == vectorWeSort)
            return;

        m_vectorWeSort = vectorWeSort;
        emit vectorWeSortChanged(m_vectorWeSort);
    }

signals:
    // to call functions of sortRealization
    void selectSortInThread(SortsEnums::SortChoice choosenSort);
    void randomizeVectorInThread(int howManyNumbers , int from , int to );
    void sortInThread();

    //to notify Qml
    void vectorWeSortChanged(QVector<int> vectorWeSort);
};

#endif // STRATEGYSORTNAVIGATION_H
