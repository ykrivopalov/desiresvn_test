import DesireVPN 1.0
import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

ApplicationWindow {
  visible: true
  title: "Integrator"

  Integrator {
    id: integrator
    onIntegrated: answerView.text = answer
  }

  Column {
    Row {
      Text { text: "Integrate:" }
      TextField {
        text: "sin(x)"
        readOnly: true
      }
    }

    Row {
      Row {
        Text { text: "From:" }
        TextField {
          id: fromInput
          text: "0"
        }
      }

      Row {
        Text { text: "To:" }
        TextField {
          id: toInput
          text: "10"
        }
      }

      Row {
        Text { text: "With step:" }
        TextField {
          id: stepInput
          text: "1"
        }
      }
    }

    Row {
      Text { text: "Result:"}
      Text {
        id: answerView
      }

      Button {
        text: "Evaluate"
        onClicked: {
          integrator.from = fromInput.text
          integrator.to = toInput.text
          integrator.step = stepInput.text
          integrator.integrate()
        }
      }
    }
  }
}
