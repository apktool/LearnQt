#pragma once

#include <QPushButton>
#include <iostream>

namespace ch {
class Button : public QPushButton {
  Q_OBJECT

 public:
  explicit Button(const QString& text, QWidget* parent = nullptr);

  QSize sizeHint() const override;
};
}// namespace ch
