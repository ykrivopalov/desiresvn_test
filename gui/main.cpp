#include <QGuiApplication>
#include <QtQml>

#include "integrator.h"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);
  qmlRegisterType<gui::Integrator>("DesireVPN", 1, 0, "Integrator");
  QQmlApplicationEngine engine(QUrl("qrc:/main.qml"));
  return app.exec();
}

