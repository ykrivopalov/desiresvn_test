import DesireVPN 1.0
import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

ApplicationWindow {
  visible: true
  title: qsTr("Integrator")
  width: mainLayout.implicitWidth
  height: mainLayout.implicitHeight
  minimumWidth: mainLayout.implicitWidth
  minimumHeight: mainLayout.implicitHeight

  Integrator {
    id: integrator
    onIntegrated: {
      answerView.text = answer
      cancelButton.visible = false
      integrateButton.visible = true
    }
  }

  ColumnLayout {
    id: mainLayout
    anchors.fill: parent

    RowLayout {
      Text { text: qsTr("Integrate:");  }
      TextField {
        text: "sin(x)"
        readOnly: true
        validator: DoubleValidator { locale: "C" }
        Layout.fillWidth: true
      }
    }

    GridLayout {
      columns: 4
        Text { text: qsTr("From:") }
        TextField {
          id: fromInput
          text: "0"
          Layout.fillWidth: true
        }

        Text { text: qsTr("To:") }
        TextField {
          id: toInput
          text: "10"
          validator: DoubleValidator { locale: "C" }
          Layout.fillWidth: true
        }

        Text { text: qsTr("With step:") }
        TextField {
          id: stepInput
          text: "1"
          validator: DoubleValidator { locale: "C" }
          Layout.fillWidth: true
        }

        Text { text: qsTr("Threads:") }
        TextField {
          id: threadCountInput
          text: "1"
          validator: IntValidator {}
          Layout.fillWidth: true
        }
    }

    RowLayout {
      Text { text: qsTr("Result:")}
      Text {
        id: answerView
        text: "0"
        Layout.fillWidth: true
      }

      Button {
        id: integrateButton
        text: qsTr("Integrate")
        onClicked: {
          visible = false
          answerView.text = qsTr("Integration in process")
          cancelButton.visible = true
          integrator.from = fromInput.text
          integrator.to = toInput.text
          integrator.step = stepInput.text
          integrator.thread_count = threadCountInput.text
          integrator.integrate()
        }
      }

      Button {
        id: cancelButton
        text: qsTr("Cancel")
        visible: false
        onClicked: {
          integrator.cancel()
          answerView.text = qsTr("Integration interrupted")
          cancelButton.visible = false
          integrateButton.visible = true
        }
      }
    }
  }
}
