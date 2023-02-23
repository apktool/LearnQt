#include "character_widget.h"

#include <QFontDatabase>
#include <QMouseEvent>
#include <QPainter>
#include <QToolTip>

namespace ch {
CharacterWidget::CharacterWidget(QWidget* parent) {
  calculateSquareSize();
  setMouseTracking(true);
}

QSize CharacterWidget::sizeHint() const { return QSize(columns * squareSize, (65536 / columns) * squareSize); }

void CharacterWidget::calculateSquareSize() { squareSize = qMax(16, 4 + QFontMetrics(displayFont, this).height()); }

void CharacterWidget::updateFont(const QFont& font) {
  displayFont.setFamily(font.family());

  calculateSquareSize();
  adjustSize();
  update();
}

void CharacterWidget::updateSize(const QString& fontSize) {
  displayFont.setPointSize(fontSize.toInt());

  calculateSquareSize();
  adjustSize();
  update();
}

void CharacterWidget::updateStyle(const QString& fontStyle) {
  const QFont::StyleStrategy oldStrategy = displayFont.styleStrategy();
  displayFont = QFontDatabase::font(displayFont.family(), fontStyle, displayFont.pointSize());
  displayFont.setStyleStrategy(oldStrategy);

  calculateSquareSize();
  adjustSize();
  update();
}

void CharacterWidget::updateFontMerging(bool enable) {
  QFont::StyleStrategy strategy = enable ? QFont::PreferDefault : QFont::NoFontMerging;
  displayFont.setStyleStrategy(strategy);

  adjustSize();
  update();
}

void CharacterWidget::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.fillRect(event->rect(), QBrush(Qt::white));
  painter.setFont(displayFont);

  QRect redrawRect = event->rect();
  int beginRow = redrawRect.top() / squareSize;
  int endRow = redrawRect.bottom() / squareSize;
  int beginColumn = redrawRect.left() / squareSize;
  int endColumn = redrawRect.right() / squareSize;

  painter.setPen(QPen(Qt::gray));
  for (int row = beginRow; row <= endRow; ++row) {
    for (int column = beginColumn; column <= endColumn; ++column) {
      painter.drawRect(column * squareSize, row * squareSize, squareSize, squareSize);
    }
  }

  QFontMetrics fontMetrics(displayFont);
  painter.setPen(QPen(Qt::black));
  for (int row = beginRow; row <= endRow; row++) {
    for (int column = beginColumn; column <= endColumn; column++) {
      int key = row * columns + column;
      painter.setClipRect(column * squareSize, row * squareSize, squareSize, squareSize);

      if (key == lastKey) {
        painter.fillRect(column * squareSize + 1, row * squareSize + 1, squareSize, squareSize, QBrush(Qt::red));
      }

      painter.drawText(column * squareSize + (squareSize / 2) - fontMetrics.horizontalAdvance(QChar(key)) / 2,
                       row * squareSize + 4 + fontMetrics.ascent(), QString(QChar(key)));
    }
  }
}

void CharacterWidget::mouseMoveEvent(QMouseEvent* event) {
  QPoint widgetPosition = mapFromGlobal(event->globalPosition().toPoint());
  uint key = (widgetPosition.y() / squareSize) * columns + widgetPosition.x() / squareSize;

  QString text =
      QString::fromLatin1("<p>Character: <span style=\"font-size: 24pt; font-family: %1\">").arg(displayFont.family()) +
      QChar(key) + QString::fromLatin1("</span><p>Value: 0x") + QString::number(key, 16);
  QToolTip::showText(event->globalPosition().toPoint(), text, this);
}

void CharacterWidget::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    lastKey = (event->position().toPoint().y() / squareSize) * columns + event->position().toPoint().x() / squareSize;
    if (QChar(lastKey).category() != QChar::Other_NotAssigned) {
      emit characterSelected(QString(QChar(lastKey)));
    }
    update();
  } else
    QWidget::mousePressEvent(event);
}

}  // namespace ch
