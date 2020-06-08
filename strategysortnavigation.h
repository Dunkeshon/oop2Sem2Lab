#ifndef STRATEGYSORTNAVIGATION_H
#define STRATEGYSORTNAVIGATION_H

#include <iostream>
#include "sortfactory.h"
#include "strategysort.h"
#include "randomize.h"
#include <QObject>
#include <QTime>

using std::vector ;
class StrategySortNavigation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int timePassed READ timePassed WRITE setTimePassed NOTIFY timePassedChanged)
    Q_PROPERTY(QString vectorBefore READ vectorBefore WRITE setVectorBefore NOTIFY vectorBeforeChanged)
    Q_PROPERTY(QString vectorAfter READ vectorAfter WRITE setVectorAfter NOTIFY vectorAfterChanged)
private:
    SortAlgorithms* m_strategy;


    QString m_vectorBefore;

    QString m_vectorAfter;

    QString makeString(const vector<int>& fromVector){
        QString newString;
        for(size_t i=0;i<fromVector.size();i++){
            if((i+1)!=fromVector.size()){
                newString.push_back(QString::number(i)+QString(", "));
            }
            else{
                newString.push_back(QString::number(i));
            }
        }
        return newString;
    }

    int m_timePassed;

public:
    StrategySortNavigation(QObject *parent = nullptr);
    ~StrategySortNavigation(){delete m_strategy;}
    vector<int> vectorToSort;

    /*
     * @brief sort your array, based on what sort you have selected earlier
     * @details you need to randomizeVector and selectSort firstly
    */
    Q_INVOKABLE void sort() ;
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

    QString vectorBefore() const
    {
        return m_vectorBefore;
    }

    QString vectorAfter() const
    {
        return m_vectorAfter;
    }

    int timePassed() const
    {
        return m_timePassed;
    }

public slots:

    void setVectorBefore(QString vectorBefore)
    {
        if (m_vectorBefore == vectorBefore)
            return;

        m_vectorBefore = vectorBefore;
        emit vectorBeforeChanged(m_vectorBefore);
    }

    void setVectorAfter(QString vectorAfter)
    {
        if (m_vectorAfter == vectorAfter)
            return;

        m_vectorAfter = vectorAfter;
        emit vectorAfterChanged(m_vectorAfter);
    }

    void setTimePassed(int timePassed)
    {
        if (m_timePassed == timePassed)
            return;

        m_timePassed = timePassed;
        emit timePassedChanged(m_timePassed);
    }

signals:
    void vectorBeforeChanged(QString vectorBefore);
    void vectorAfterChanged(QString vectorAfter);
    void timePassedChanged(int timePassed);
};

#endif // STRATEGYSORTNAVIGATION_H
