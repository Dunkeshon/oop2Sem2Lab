
function startSort() {

    switch(sorts.currentIndex) {
    case 0: navigationClass.selectSort(Sortchoice.INSERTION_SORT);
        break;
    case 1: navigationClass.selectSort(Sortchoice.QUICK_SORT);
        break;
    case 2: navigationClass.selectSort(Sortchoice.MERGE_RECURSIVE_SORT);
        break;
    case 3: navigationClass.selectSort(Sortchoice.MERGE_ITERATIVE_SORT);
        break;
    case 4: navigationClass.selectSort(Sortchoice.LSD_RADIX);
        break;
    case 5: navigationClass.selectSort(Sortchoice.MSD_RADIX);
        break;
    case 6: navigationClass.selectSort(Sortchoice.SIMPLE_HEAD_COUNT);
        break;
    case 7: navigationClass.selectSort(Sortchoice.ROBUST_HEAD_COUNT);
        break;
    case 8: navigationClass.selectSort(Sortchoice.SELECTION_SORT);
        break;
    default: console.debug("WRONG ENUM")
        break;
    }

}

function checkFields() {
    if(vecGen.count.text==="" || vecGen.from.text==="" || vecGen.to.text==="")
        return false
//    if(vecGen.from.text < vecGen.to.text)
//        return false
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
