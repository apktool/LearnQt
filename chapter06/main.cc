#include <QApplication>
#include <QScreen>

#include "src/main_window.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  ch::MainWindow mainWin;

  const QRect availableGeometry = mainWin.screen()->availableGeometry();
  mainWin.resize(availableGeometry.width() / 2, availableGeometry.height() * 2 / 3);
  mainWin.move((availableGeometry.width() - mainWin.width()) / 2, (availableGeometry.height() - mainWin.height()) / 2);

  mainWin.show();

  int res = QApplication::exec();
  return res;
}
