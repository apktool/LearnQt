#include <QWidget>

#include "ui_login.h"

class LoginWidget: public QWidget {
  Q_OBJECT

 public:
  LoginWidget(QWidget* parent = nullptr);

 private:
  Ui::LoginWidget ui;
};
