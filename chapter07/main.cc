#include <QApplication>

#include "login.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  LoginWidget login_widget;
  login_widget.show();

  int res = app.exec();
  return res;
}
