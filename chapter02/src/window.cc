#include "window.h"
#include <QGridLayout>

namespace ch {
Window::Window(QWidget* parent) : QWidget(parent) {
  display = new QLineEdit(0);
  display->setReadOnly(true);
  display->setAlignment(Qt::AlignRight);

  QGridLayout* layout = new QGridLayout();
  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->addWidget(display, 0, 0, 1, 6);
  layout->addWidget(createButton(tr("Backspace"), SLOT(backspaceClicked())), 1, 0, 1, 2);
  layout->addWidget(createButton(tr("Clear"), SLOT(clear())), 1, 2, 1, 2);

  Button* digitButtons[10];
  for (int i = 0; i < 10; i++) {
    digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
  }

  for (int i = 1; i <= 10; i++) {
    int row = ((9 - i) / 3 + 2);
    int col = ((i - 1) % 3) + 1;
    layout->addWidget(digitButtons[i], row, col);
  }

  layout->addWidget(createButton("Click", SLOT(digitClicked())), 3, 4);
  layout->addWidget(createButton(tr("."), SLOT(pointClicked())), 4, 4);

  setLayout(layout);
}

Button* Window::createButton(const QString& text, const char* mem) {
  Button* button = new Button(text);
  connect(button, SIGNAL(clicked()), this, mem);
  return button;
}

void Window::digitClicked() {
  Button* button = qobject_cast<Button*>(sender());
  int digit = button->text().toInt();
  display->setText(display->text() + QString::number(digit));
}

void Window::pointClicked() {
  if (!display->text().contains(".")) {
    display->setText(display->text() + tr("."));
  }
}

void Window::backspaceClicked() {
  QString text = display->text();
  if (text.isEmpty()) {
    return;
  }
  text.chop(1);
  display->setText(text);
}

void Window::clear() {
  display->setText("0");
}
}// namespace ch