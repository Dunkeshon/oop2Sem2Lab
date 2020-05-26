#pragma once
#include <QObject>
#include "strategysort.h"
#include "randomize.h"
#include "sortfactory.h"
#include <vector>
#include <QDebug>

using std::vector;

class SortRealization : public QObject
{
    Q_OBJECT
private:
    SortAlgorithms* m_strategy;
    vector<int> m_vectorToSort;
public:
    explicit SortRealization(QObject *parent = nullptr);


    //getters
    vector<int>& getVectorToSort();
    SortAlgorithms& getStrategyOfSort();

public slots:
    void sort()
    {
        if(!m_strategy){
            qDebug("m_strategy == nullptr .You need to select sort firstly");
            //send signal
        }
        else if(m_vectorToSort.empty()){
            qDebug("Your vector is empty.You need to create it firstly");
            //send signal
          }
        else{
            m_strategy->sort(m_vectorToSort);
        }
    }
    /*
      * @param howManyNumbers - size of array we want to create
      * @param from - begin of randomizing range
      * @param to - end of randomizing range
    */
    void randomizeVector(int howManyNumbers, int from, int to);

    /*
      *brief creates m_strategy of needed sort, based on enums
    */
    void selectSort(SortsEnums::SortChoice choosenSort);

signals:
    void vectorToSortChanged(const vector<int>& newVector);

    // void strategyChanged(); maybe to test later

    // void sortEnded(); clear the screen in qml ( снять выделения )




};

