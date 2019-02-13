import QtQuick 2.12
import QtQuick.Controls 2.12 as Controls
import QtQuick.Layouts 1.12
import Qt.labs.settings 1.0
import Qt.labs.platform 1.0 as Platform
import org.kde.kirigami 2.4 as Kirigami

import Spectral 0.1

Kirigami.ScrollablePage {
    id: pageRoot

    implicitWidth: Kirigami.Units.gridUnit * 20
    background: Rectangle {
        color: Kirigami.Theme.backgroundColor
    }

    title: user ? user.displayName : "Nil"

    ListView {
        id: mainListView
        currentIndex: -1
        activeFocusOnTab: true
        focus: true

        model: RoomListModel {
            connection: controller.connection
        }

        delegate: Kirigami.AbstractListItem {
            property string subtitleColor: "#5B7480"

            id: listItem

            width: mainListView.width
            height: 64

            textColor: "#1D333E"

            contentItem: RowLayout {
                property bool indicateActiveFocus: listItem.pressed || Kirigami.Settings.tabletMode || listItem.activeFocus || (listItem.ListView.view ? listItem.ListView.view.activeFocus : false)

                anchors.fill: parent
                anchors.margins: 12

                id: layout

                spacing: 12

                Avatar {
                    Layout.preferredWidth: height
                    Layout.fillHeight: true

                    source: avatar
                    hint: name || "No Name"
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignHCenter

                    Controls.Label {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        text: name || "No Name"
                        color: layout.indicateActiveFocus && (listItem.highlighted || listItem.checked || (listItem.pressed && listItem.supportsMouseEvents)) ? listItem.activeTextColor : listItem.textColor
                        font.family: listItem.font.family
                        font.pixelSize: 16
                        elide: Text.ElideRight
                        wrapMode: Text.NoWrap
                    }

                    Controls.Label {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        text: (lastEvent == "" ? topic : lastEvent).replace(/(\r\n\t|\n|\r\t)/gm,"")
                        color: layout.indicateActiveFocus && (listItem.highlighted || listItem.checked || (listItem.pressed && listItem.supportsMouseEvents)) ? listItem.activeTextColor : listItem.subtitleColor
                        font.family: listItem.font.family
                        font.pixelSize: 13
                        elide: Text.ElideRight
                        wrapMode: Text.NoWrap
                    }
                }
            }

            Accessible.role: Accessible.MenuItem
            onClicked: {
                mainListView.currentIndex = index;
                root.pageStack.pop(pageRoot);
                root.pageStack.push(chatPage, {"room": currentRoom});
            }
            highlighted: focus && ListView.isCurrentItem
        }
    }
}
