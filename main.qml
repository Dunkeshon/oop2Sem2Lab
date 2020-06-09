import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import "functions.js" as F

Window {
    id: mainw
    visible: true
    width: 640
    height: 480
    minimumHeight: 480
    minimumWidth: 480
    title: qsTr("Hello World")

    Rectangle {
        id: vecGen
        color: "lightsteelblue"
        anchors.fill: parent
        property alias count: countV
        property alias from: fromV
        property alias to: toV

        property alias confirmB: confirm

        Item {
            anchors.centerIn: parent
            width: 200
            height: textV.height + countV.height + fromV.height + confirm.height + 30
            Text {
                id: textV
                text: qsTr("<strong>Generate Vector</strong>")
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
            }
            TextField {
                id: countV
                height: 40
                width: 200
                placeholderText: "AMOUNT OF ELEMENTS"
                anchors.top: textV.bottom
                anchors.margins: 10
                validator: IntValidator { bottom: 0; top: 10000 }
                anchors.horizontalCenter: parent.horizontalCenter
            }
            TextField {
                id: fromV
                height: 40
                width: 95
                placeholderText: "FROM"
                anchors.top: countV.bottom
                anchors.topMargin: 10
                validator: IntValidator { bottom: 0; top: 1000000 }
                anchors.left: countV.left
            }
            TextField {
                id: toV
                height: 40
                width: 95
                placeholderText: "TO"
                anchors.top: countV.bottom
                anchors.topMargin: 10
                validator: IntValidator { bottom: 0; top: 1000000 }
                anchors.right: countV.right
            }
            Button {
                id: confirm
                width: 200
                height: 40
                text: "Confirm"
                anchors.top: fromV.bottom
                anchors.topMargin: 20
                visible: F.checkFields() ? true : false
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    navigationClass.randomizeVector(parseInt(countV.text), parseInt(fromV.text), parseInt(toV.text))
                    results.text = "BEFORE: " + navigationClass.vectorBefore + "\n\n"

                    F.clearAllFields()
                    vecGen.visible = false
                }
            }
        }
    }

    TopPannel {
        id:topPannel
        visible: vecGen.visible ? false : true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 40
    }
    ScrollView {
        anchors.top: topPannel.bottom
        visible: vecGen.visible ? false : true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        TextArea {
            id: results
            readOnly: true
            wrapMode: TextArea.WordWrap
        }
    }
}
