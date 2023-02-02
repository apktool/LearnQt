#include <QApplication>

#include "src/point_line.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  PointLine demo;
  demo.show();

  app.exec();
  return 0;
}