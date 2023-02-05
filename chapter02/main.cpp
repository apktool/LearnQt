#include "src/window.h"
#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  ch::Window window;
  window.show();

  return app.exec();
}
