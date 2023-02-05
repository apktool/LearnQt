#include "button.h"

namespace ch {
Button::Button(const QString& text, QWidget* parent) : QPushButton(parent) {
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  setText(text);
}

QSize ch::Button::sizeHint() const {
  QSize hint = QPushButton::sizeHint();
  hint.rheight() += 20;
  hint.rwidth() = qMax(hint.width(), hint.height());
  return hint;
}
}// namespace ch
