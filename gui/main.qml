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

  function idleMode() {
    integrateButton.visible = true
    cancelButton.visible = false
  }

  function integrationMode() {
    integrateButton.visible = false
    cancelButton.visible = true
  }

  function showError(msg) {
    answerView.text = qsTr("Error") + ": " + msg
  }

  function checkInputFields() {
    if (fromInput.text.length == 0 || toInput.text.length == 0 ||
        stepInput.text.length == 0 || threadCountInput.text.length == 0) {
      showError(qsTr("you must fill all fields"))
      return false
    }

    if (threadCountInput.text < 1) {
      showError(qsTr("thread count must be greater then 0"))
      return false
    }

    if (stepInput.text <= 0) {
      showError(qsTr("integration step must be greater then 0"))
      return false
    }

    return true
  }

  Integrator {
    id: integrator
    onIntegrated: {
      answerView.text = result
      idleMode()
    }
    onError: {
      showError(error)
      idleMode()
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
        Layout.fillWidth: true
      }
    }

    GridLayout {
      columns: 4
        Text { text: qsTr("From:") }
        TextField {
          id: fromInput
          text: "0"
          validator: DoubleValidator { locale: "C" }
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
          validator: DoubleValidator { locale: "C"; bottom: 0 }
          Layout.fillWidth: true
        }

        Text { text: qsTr("Threads:") }
        TextField {
          id: threadCountInput
          text: "1"
          validator: IntValidator { bottom: 1 }
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
          if (checkInputFields()) {
            integrationMode()
            answerView.text = qsTr("Integration in process")

            integrator.from = fromInput.text
            integrator.to = toInput.text
            integrator.step = stepInput.text
            integrator.thread_count = threadCountInput.text
            integrator.integrate()
          }
        }
      }

      Button {
        id: cancelButton
        text: qsTr("Cancel")
        visible: false
        onClicked: {
          integrator.cancel()
          answerView.text = qsTr("Integration interrupted")
          idleMode()
        }
      }
    }
  }
}
