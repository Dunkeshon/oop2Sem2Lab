#include "controller.h"



Controller::Controller(QObject *parent):
    QObject(parent),
    m_strategy(nullptr)
{
    sortRealization = new SortRealization();
    sortRealization->moveToThread(&sortThread);
    connect(&sortThread, &QThread::finished, sortRealization, &QObject::deleteLater);
    // call sort
    connect(this, &Controller::sortInThread, sortRealization, &SortRealization::sort);
    //call randomize vector
    connect(this, &Controller::randomizeVectorInThread, sortRealization, &SortRealization::randomizeVector);
    //call select sort
    connect(this, &Controller::selectSortInThread, sortRealization, &SortRealization::selectSort);
    // update QVector's state, that can be used in qml
    connect(sortRealization,&SortRealization::vectorToSortChanged,this,[&](const vector<int>& newVector){
        setVectorWeSort(QVector<int>::fromStdVector(newVector));
    });
    // pause thread implement
    // resume thread implement
    // think about giving 100% info about array or just changes to qml
    // connect(sortRealization, &SortRealization::resultReady, this, &Controller::handleResults);
    sortThread.start();
}


/*
 * @brief sort your array, based on what sort you have selected earlier
 * @details you need to randomizeVector and selectSort firstly
*/

void Controller::sort()
{
    emit sortInThread();
}

/*
  * @param howManyNumbers - size of array we want to create
  * @param from - begin of randomizing range
  * @param to - end of randomizing range
*/
void Controller::randomizeVector(int howManyNumbers, int from, int to){
    emit randomizeVectorInThread(howManyNumbers,from,to);
}

/*
  *brief creates m_strategy of needed sort, based on enums
*/
void Controller::selectSort(SortsEnums::SortChoice choosenSort){
    emit selectSortInThread(choosenSort);
}

QVector<int> Controller::vectorWeSort() const
{
    return m_vectorWeSort;
}
