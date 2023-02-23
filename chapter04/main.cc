#include <QApplication>

#include "src/main_window.h"

int main(int argc, char* argv[]) {
  try {
    QApplication app(argc, argv);

    ch::MainWindow window;
    window.show();

    app.exec();
  } catch (...) {
    qDebug() << "Error";
  }

  return 0;
}