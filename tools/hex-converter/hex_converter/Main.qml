/**
  * @file Main.qml
  * @brief Main QML file for hex converter application
  * @author Edwin Mwiti
  * @date Oct 5 2025
*/

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Basic

Window {
    id: app_window
    width: 730
    height: 300

    //minimumHeight: app_window.height /* cannot be resized lower than this*/
    //minimumWidth: app_window.width

    visible: true
    title: qsTr("Hex Converter")
    color: "#353535"

    ColumnLayout {
        anchors.fill: parent
        spacing: 20

        /**
          * Major upper row - INPUT AREA
        */
        RowLayout {
            id: input_area_row
            //anchors.fill: parent
            spacing: 6

            /* Holds the input field label and the input field itself */
            RowLayout {
                Text { /* input field label */
                    text: "Input chars"
                    color: "white"
                    font.family: "ubuntu"
                    font.pixelSize: 20
                    leftPadding: 10
                }

                /* input text area */
                Rectangle {
                    width: 500
                    height: 100
                    color: "#f3f3f3"
                    border.color: "black"
                    border.width: 2
                    radius: 2

                    ScrollView {
                        id: input_text_view
                        anchors.fill: parent

                        TextArea {
                            id: input_chars_field
                            width: parent.width
                            wrapMode: Text.WordWrap
                            color: "black"
                            font.family: "ubuntu"
                            font.pixelSize: 23
                            placeholderText: "Input characters...\n\n\n\n\n\n"
                        }
                    }
                }

                ColumnLayout {
                    /* clear button */
                    Button{
                        id: clear_button
                        text: qsTr("Clear")
                        font.family: "ubuntu"
                        font.pixelSize: 23

                        contentItem: Text {
                            text: clear_button.text
                            font: clear_button.font
                            opacity: enabled ? 1.0 : 0.3
                            color: "#ffffff"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        onClicked: {
                            input_chars_field.text = ""
                        }

                        background: Rectangle {
                            implicitWidth: 100
                            implicitHeight: 40
                            opacity: enabled ? 1: 0.3
                            border.color: clear_button.down ? "#1c4d4d" : "#4d4d4d"
                            color: "#636363"
                            border.width: 2
                            radius: 2
                        }
                    }
                    /* end of clear button */

                    /* Convert button */
                    Button{
                        id: convert_button
                        text: qsTr("Convert")
                        font.family: "ubuntu"
                        font.pixelSize: 23

                        onClicked: {
                            console.log(input_chars_field.text)

                            let input_str = input_chars_field.text
                            let str_len = input_str.length
                            let output_str = ""

                            for(let i=0; i < str_len; i++) {
                                let ch = input_str[i]
                                if(ch !== 'string' || ch !== 1) {
                                    console.log("Input must be a single character or string")
                                }

                                let unicode_value = ch.charCodeAt(0)
                                let hex_string = unicode_value.toString(16)

                                /* append to output string */
                                output_str += hex_string
                            }

                            console.log("HEX OUT: " + output_str)

                            /* display the text */
                            output_chars_field.text = output_str

                        }

                        contentItem: Text {
                            text: convert_button.text
                            font: convert_button.font
                            opacity: enabled ? 1.0 : 0.3
                            color: "#ffffff"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            implicitWidth: 100
                            implicitHeight: 40
                            opacity: enabled ? 1: 0.3
                            border.color: convert_button.down ? "#1c4d4d" : "#4d4d4d"
                            color: "#636363"
                            border.width: 2
                            radius: 2
                        }
                    }
                    /* end of convert button */

                }
            }

        }

        /* holds the output area field label, output field and output control buttons */
        RowLayout {
            id: output_area_row
            //anchors.fill: parent
            spacing: 6

            /* Holds the input field label and the input field itself */
            RowLayout {
                Text { /* output field label */
                    horizontalAlignment: Text.AlignHCenter
                    rightPadding: 35 // crude way to alight with the top field
                    leftPadding: 10
                    text: "Output"
                    color: "white"
                    font.family: "ubuntu"
                    font.pixelSize: 20
                }

                /* output text area */
                Rectangle {
                    width: 500
                    height: 100
                    color: "black"
                    border.color: "black"
                    border.width: 2
                    radius: 2

                    ScrollView {
                        id: output_text_view
                        clip: true
                        anchors.fill: parent

                        TextArea {
                            id: output_chars_field
                            width: parent.width
                            wrapMode: Text.WordWrap
                            color: "#00d900"
                            font.family: "ubuntu"
                            font.pixelSize: 23
                            placeholderText: "\n\n\n\n\n\n"
                        }
                    }
                }

                ColumnLayout {
                    /* clear button */
                    Button{
                        id: copy_button
                        text: qsTr("Copy")
                        font.family: "ubuntu"
                        font.pixelSize: 23

                        onClicked: {
                            output_chars_field.selectAll()
                            output_chars_field.copy()

                            copy_button.text = "Copied"
                            copy_button_text.color = "#00d55f"
                        }

                        onFocusChanged: {
                            copy_button.text = "Copy"
                            copy_button_text.color = "#ffffff"
                        }

                        contentItem: Text {
                            id: copy_button_text
                            text: copy_button.text
                            font: copy_button.font
                            opacity: enabled ? 1.0 : 0.3
                            color: "#ffffff"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            implicitWidth: 100
                            implicitHeight: 40
                            opacity: enabled ? 1: 0.3
                            border.color: copy_button.down ? "#1c4d4d" : "#4d4d4d"
                            color: "#636363"
                            border.width: 2
                            radius: 2
                        }
                    }
                    /* end of clear button */

                    /* Save to file button */
                    // Button{
                    //     id: save_button
                    //     text: qsTr("Save")
                    //     font.family: "ubuntu"
                    //     font.pixelSize: 23

                    //     contentItem: Text {
                    //         text: save_button.text
                    //         font: save_button.font
                    //         opacity: enabled ? 1.0 : 0.3
                    //         color: "#ffffff"
                    //         horizontalAlignment: Text.AlignHCenter
                    //         verticalAlignment: Text.AlignVCenter
                    //         elide: Text.ElideRight
                    //     }

                    //     background: Rectangle {
                    //         implicitWidth: 100
                    //         implicitHeight: 40
                    //         opacity: enabled ? 1: 0.3
                    //         border.color: save_button.down ? "#1c4d4d" : "#4d4d4d"
                    //         color: "#636363"
                    //         border.width: 2
                    //         radius: 2
                    //     }
                    // }
                    /* end of convert button */

                }
            }

        }

    }
}
