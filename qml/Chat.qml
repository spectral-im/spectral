import QtQuick 2.12
import QtQuick.Controls 2.5 as Controls
import org.kde.kirigami 2.4 as Kirigami
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3

import Spectral 0.1

Kirigami.ScrollablePage {
    property var room: null
    readonly property var user: controller.connection ? controller.connection.localUser : null

    id: chat

    title: room ? room.displayName : ""

    ListView {
        id: timeline

        model: MessageEventModel {
            room: chat.room

            onModelReset: {
                if (room) {
                    if (timeline.contentY < timeline.originY + 10 || room.timelineSize < 20)
                        room.getPreviousContent(50)
                }
            }
        }

        spacing: 4

        verticalLayoutDirection: ListView.BottomToTop

        delegate: RowLayout {
            width: parent.width

            Avatar {
                Layout.preferredWidth: Kirigami.Units.gridUnit * 2
                Layout.preferredHeight: Kirigami.Units.gridUnit * 2
                Layout.leftMargin: Kirigami.Units.largeSpacing

                hint: author.displayName
                source: author.avatarMediaId
            }

            Controls.Label {
                Layout.fillWidth: true
                Layout.rightMargin: Kirigami.Units.largeSpacing

                text: display

                wrapMode: Text.Wrap
                textFormat: Text.RichText
            }
        }

        onContentYChanged: {
            if(room && contentY  - 5000 < originY)
                room.getPreviousContent(20);
        }
    }

    footer: Controls.Pane {
        horizontalPadding: Kirigami.Units.largeSpacing
        verticalPadding: Kirigami.Units.smallSpacing

        Material.elevation: 8

        contentItem: RowLayout {
            spacing: Kirigami.Units.largeSpacing

            Avatar {
                Layout.preferredWidth: Kirigami.Units.gridUnit * 2
                Layout.preferredHeight: Kirigami.Units.gridUnit * 2

                source: chat.user ? chat.user.avatarMediaId : null
                hint: chat.user ? chat.user.displayName : "?"
            }

            Controls.TextArea {
                Layout.fillWidth: true
                Layout.minimumHeight: Kirigami.Units.gridUnit * 3

                wrapMode: Text.Wrap
                placeholderText: "Send a Message"
                topPadding: 0
                bottomPadding: 0
                selectByMouse: true
                verticalAlignment: TextEdit.AlignVCenter

                background: Item {}

                Keys.onReturnPressed: {
                    if (event.modifiers & Qt.ShiftModifier) {
                        insert(cursorPosition, "\n")
                    } else if (text) {
                        postMessage(text)
                        text = ""
                    }
                }

                function postMessage(text) {
                    if (text.trim().length === 0) { return }
                    if(!room) { return }

                    var PREFIX_ME = '/me '
                    var PREFIX_NOTICE = '/notice '
                    var PREFIX_RAINBOW = '/rainbow '
                    var PREFIX_HTML = '/html '
                    var PREFIX_MARKDOWN = '/md '

                    if (text.indexOf(PREFIX_ME) === 0) {
                        text = text.substr(PREFIX_ME.length)
                        room.postMessage(text, RoomMessageEvent.Emote)
                        return
                    }
                    if (text.indexOf(PREFIX_NOTICE) === 0) {
                        text = text.substr(PREFIX_NOTICE.length)
                        room.postMessage(text, RoomMessageEvent.Notice)
                        return
                    }
                    if (text.indexOf(PREFIX_RAINBOW) === 0) {
                        text = text.substr(PREFIX_RAINBOW.length)

                        var parsedText = ""
                        var rainbowColor = ["#ff2b00", "#ff5500", "#ff8000", "#ffaa00", "#ffd500", "#ffff00", "#d4ff00", "#aaff00", "#80ff00", "#55ff00", "#2bff00", "#00ff00", "#00ff2b", "#00ff55", "#00ff80", "#00ffaa", "#00ffd5", "#00ffff", "#00d4ff", "#00aaff", "#007fff", "#0055ff", "#002bff", "#0000ff", "#2a00ff", "#5500ff", "#7f00ff", "#aa00ff", "#d400ff", "#ff00ff", "#ff00d4", "#ff00aa", "#ff0080", "#ff0055", "#ff002b", "#ff0000"]
                        for (var i = 0; i < text.length; i++) {
                            parsedText = parsedText + "<font color='" + rainbowColor[i % rainbowColor.length] + "'>" + text.charAt(i) + "</font>"
                        }
                        room.postHtmlMessage(text, parsedText, RoomMessageEvent.Text)
                        return
                    }
                    if (text.indexOf(PREFIX_HTML) === 0) {
                        text = text.substr(PREFIX_HTML.length)
                        var re = new RegExp("<.*?>")
                        var plainText = text.replace(re, "")
                        room.postHtmlMessage(plainText, text, RoomMessageEvent.Text)
                        return
                    }
                    if (text.indexOf(PREFIX_MARKDOWN) === 0) {
                        text = text.substr(PREFIX_MARKDOWN.length)
                        room.postMarkdownText(text)
                        return
                    }

                    room.postPlainText(text)
                }
            }
        }
    }
}
