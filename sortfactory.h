#ifndef SORTFACTORY_H
#define SORTFACTORY_H
#include "strategysort.h"

// brief is used to create choosen sort strategy
class SortFactory
{
private:
    SortFactory();
    SortFactory(SortFactory &other) = delete;
    SortFactory(const SortFactory &) = delete;

public:
    static SortAlgorithms * insertionSort(){
        InsertionSort * sort = new InsertionSort;
        return sort ;
    }
    static SortAlgorithms * quickSort(){
        QuickSort * sort = new QuickSort;
        return sort ;
    }
    static SortAlgorithms * iterationMerge(){
        IterationMerge * sort = new IterationMerge;
        return sort ;
    }
    static SortAlgorithms * recursiveMerge(){
        RecMerge * sort = new RecMerge;
        return sort ;
    }
    static SortAlgorithms * msdRadix(){
        MsdRadix * sort = new MsdRadix;
        return sort ;
    }
    static SortAlgorithms * lsdRadix(){
        LsdRadix * sort = new LsdRadix;
        return sort ;
    }
    // TO DO



};

#endif // SORTFACTORY_H
