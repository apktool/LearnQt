#pragma once

#include "button.h"
#include <QLineEdit>
#include <QWidget>

namespace ch {
class Window : public QWidget {
  Q_OBJECT

 public:
  Window(QWidget* parent = nullptr);

 protected:
  Button* createButton(const QString& text, const char* mem);

 private:
  QLineEdit* display;

 private slots:
  void digitClicked();
  void pointClicked();
  void backspaceClicked();
  void clear();
};
}// namespace ch