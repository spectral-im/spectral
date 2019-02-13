import QtQuick 2.12
import QtQuick.Controls 2.12 as Controls
import QtQuick.Layouts 1.12
import Qt.labs.settings 1.0
import Qt.labs.platform 1.0 as Platform
import org.kde.kirigami 2.4 as Kirigami

import Spectral 0.1

Kirigami.ApplicationWindow {
    property var user: controller.connection ? controller.connection.localUser : null

    id: root

    Controller {
        id: controller

        quitOnLastWindowClosed: true
    }

    globalDrawer: Kirigami.GlobalDrawer {
        title: "Spectral"
        titleIcon: "applications-graphics"

        actions: [
            Kirigami.Action {
                text: "Account"
                iconName: "view-list-icons"
            }
        ]

        Controls.CheckBox {
            checked: true
            text: "Settings"
        }
    }

    pageStack.initialPage: RoomList {}

    Component {
        id: chatPage

        Chat {

        }
    }

    Binding {
        target: imageProvider
        property: "connection"
        value: controller.connection
    }

    Component.onCompleted: {
        controller.initiated.connect(function() {
            if (controller.accountCount == 0) console.log("Login")
        })
    }
}
