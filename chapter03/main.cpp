#include <QApplication>

#include "src/windows.h"

int main(int argv, char *args[]) {
  try {
    QApplication app(argv, args);
    ch::Windows window;
    window.show();
    return app.exec();
  } catch (...) {
    qDebug() << "ERROR";
  }
}