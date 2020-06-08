
function startSort() {

    switch(sorts.currentIndex) {
    case 0: navigationSort.selectSort(SortChoice.INSERTION_SORT);
        break;
    case 1: navigationSort.selectSort(SortChoice.QUICK_SORT);
        break;
    case 2: navigationSort.selectSort(SortChoice.MERGE_RECURSIVE_SORT);
        break;
    case 3: navigationSort.selectSort(SortChoice.MERGE_ITERATIVE_SORT);
        break;
    case 4: navigationSort.selectSort(SortChoice.LSD_RADIX);
        break;
    case 5: navigationSort.selectSort(SortChoice.MSD_RADIX);
        break;
    case 6: navigationSort.selectSort(SortChoice.SIMPLE_HEAD_COUNT);
        break;
    case 7: navigationSort.selectSort(SortChoice.ROBUST_HEAD_COUNT);
        break;
    case 8: navigationSort.selectSort(SortChoice.SELECTION_SORT);
        break;
    default: console.debug("WRONG ENUM")
        break;
    }

}

function checkFields() {
    if(vecGen.count.text==="" || vecGen.from.text==="" || vecGen.to.text==="")
        return false
    return true
}

function clearAllFields() {
    vecGen.count.text = ""
    vecGen.from.text = ""
    vecGen.to.text = ""
}

function rebVectorClicked() {
    vecGen.visible = true
}
