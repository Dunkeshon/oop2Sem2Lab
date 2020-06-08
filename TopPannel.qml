import QtQuick 2.0
import QtQuick.Controls 1.0
import "functions.js" as F
import SortVisualizer 1.0

Item {
    id: mainItem



    Rectangle {
        id: pannel
        anchors.fill: parent
        color: "lightsteelblue"

        Rectangle {
            id: bottomSeparator
            height: 1
            color: "black"
            anchors.left: pannel.left
            anchors.right: pannel.right
            anchors.bottom: pannel.bottom
        }

        ComboBox {
            id: sorts
            anchors.left: pannel.left
            anchors.leftMargin: 10
            anchors.verticalCenter: pannel.verticalCenter
            width: 150
            model: [
                "Insertion Sort",
                "Quick Sort",
                "Merge Recursive Sort",
                "Merge Interative Sort",
                "LSD Radix",
                "MSD Radix",
                "Simple Head Count",
                "Robust Head Count",
                "Selection Sort"
            ]

            onCurrentIndexChanged: {
                results.text = "BEFORE: " + navigationClass.vectorBefore + "\n\n"
            }
        }

        Button {
            id: rebuildVector
            text: "Rebuild Vector"
            anchors.verticalCenter: pannel.verticalCenter
            anchors.left: sorts.right
            anchors.leftMargin: 10
            onClicked:  {
                F.rebVectorClicked()
            }
        }

        Button {
            id: startSort
            text: "Start"
            anchors.verticalCenter: pannel.verticalCenter
            anchors.right: pannel.right
            anchors.rightMargin: 10
            onClicked: {
                //SORT AND PRINT AFTER VECTOR AND SET ENUM
                F.startSort()
                navigationClass.sort()
                results.text += "AFTER: " + navigationClass.vectorAfter + "\n\n" + "TIME: " + navigationClass.timePassed
            }
        }
    }
}
