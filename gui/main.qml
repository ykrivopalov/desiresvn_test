import DesireVPN 1.0
import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

ApplicationWindow {
  visible: true
  title: qsTr("Integrator")

  Integrator {
    id: integrator
    onIntegrated: {
      answerView.text = answer
      cancelButton.visible = false
      evaluateButton.visible = true
    }
  }

  Column {
    Row {
      Text { text: qsTr("Integrate:");  }
      TextField {
        text: "sin(x)"
        readOnly: true
      }
    }

    Row {
      Row {
        Text { text: qsTr("From:") }
        TextField {
          id: fromInput
          text: "0"
        }
      }

      Row {
        Text { text: qsTr("To:") }
        TextField {
          id: toInput
          text: "10"
        }
      }

      Row {
        Text { text: qsTr("With step:") }
        TextField {
          id: stepInput
          text: "1"
        }
      }

      Row {
        Text { text: qsTr("Thread count:") }
        TextField {
          id: threadCountInput
          text: "1"
        }
      }
    }

    Row {
      Text { text: qsTr("Result:")}
      Text {
        id: answerView
      }

      Button {
        id: evaluateButton
        text: qsTr("Evaluate")
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
          evaluateButton.visible = true
        }
      }
    }
  }
}
