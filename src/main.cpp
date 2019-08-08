#include <QApplication>
#include <QNetworkProxyFactory>

#include "mainwindow.h"

#include "palette.h"

QByteArray readTextFile(const QString& file_path) {
  QFile input_file(file_path);
  QByteArray input_data;

  if (input_file.open(QIODevice::Text | QIODevice::Unbuffered |
                      QIODevice::ReadOnly)) {
    input_data = input_file.readAll();
    input_file.close();
    return input_data;
  } else {
    return QByteArray();
  }
}

int main(int argc, char* argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QNetworkProxyFactory::setUseSystemConfiguration(true);

  QString stylesheet = MPalette::generateStyleSheet(readTextFile(":/assets/stylesheet/base.qss"));

  QApplication app(argc, argv);

  QApplication::setStyle("macintosh");

  app.setOrganizationName("ENCOM");
  app.setOrganizationDomain("encom.eu.org");
  app.setApplicationName("Spectral");
  app.setWindowIcon(QIcon(":/assets/img/icon.png"));

  app.setStyleSheet(stylesheet);

  MainWindow w;

  w.show();

  return app.exec();
}
