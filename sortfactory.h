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
    static SortAlgorithms * selectionSort(){
        SelectionSort * sort = new SelectionSort;
        return sort ;
    }
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
    static SortAlgorithms * simpleHeadCount(){
        HeadCount *sort = new CompositeHeadCount(new SimplAlgHeadCount);
        return sort;
    }
    static SortAlgorithms * robustHeadCount(){
        HeadCount *sort = new CompositeHeadCount(new RobustAlgHeadCount);
        return sort;
    }


};

#endif // SORTFACTORY_H
