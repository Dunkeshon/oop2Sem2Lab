#ifndef STRATEGYSORTNAVIGATION_H
#define STRATEGYSORTNAVIGATION_H

#include <iostream>
#include "sortfactory.h"
#include "strategysort.h"
#include "randomize.h"
#include <QObject>
#include <QTimer>

using std::vector ;
class StrategySortNavigation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double timePassed READ timePassed WRITE setTimePassed NOTIFY timePassedChanged)
private:
    SortAlgorithms* m_strategy;
    double m_timePassed;

public:
    StrategySortNavigation(QObject *parent = nullptr);
    ~StrategySortNavigation(){delete m_strategy;}
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
    double timePassed() const
    {
        return m_timePassed;
    }
public slots:
    void setTimePassed(double timePassed)
    {
        qWarning("Floating point comparison needs context sanity check");
        if (qFuzzyCompare(m_timePassed, timePassed))
            return;
        m_timePassed = timePassed;
        emit timePassedChanged(m_timePassed);
    }
signals:
    void timePassedChanged(double timePassed);
};

#endif // STRATEGYSORTNAVIGATION_H
