#include "code_editor.h"

#include <QPainter>
#include <QTextBlock>

namespace ch {

CodeEditor::CodeEditor(QWidget* parent) : QPlainTextEdit(parent) {
  margin_ = new LeftMargin(this);

  // set cursor position only
  connect(this, &CodeEditor::blockCountChanged, this,
          [&](int newBlockCnt) -> void { setViewportMargins(calSpace(newBlockCnt), 0, 0, 0); });

  // indirectly call margin's **paintEvent()**
  connect(this, &CodeEditor::updateRequest, this, [&](const QRect& rect, int dy) -> void {
    if (dy) {
      margin_->scroll(0, dy);
    } else {
      margin_->update(0, rect.y(), margin_->width(), rect.height());
    }
  });

  // set highlight line
  connect(this, &CodeEditor::cursorPositionChanged, this, [&]() -> void {
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
      QTextEdit::ExtraSelection selection;

      QColor lineColor = QColor(Qt::blue).lighter(160);

      selection.format.setBackground(lineColor);
      selection.format.setProperty(QTextFormat::FullWidthSelection, true);
      selection.cursor = textCursor();
      selection.cursor.clearSelection();
      extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
  });
}

void CodeEditor::resizeEvent(QResizeEvent* event) {
  QPlainTextEdit::resizeEvent(event);

  QRect cr = contentsRect();
  margin_->setGeometry(QRect(cr.left(), cr.top(), calSpace(blockCount()), cr.height()));
};

// set line number
void CodeEditor::UpdateMarginNo(QPaintEvent* event) {
  QPainter painter(margin_);
  painter.fillRect(event->rect(), Qt::red);

  QTextBlock block = firstVisibleBlock();
  int blockNumber = block.blockNumber();
  int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
  int bottom = top + qRound(blockBoundingRect(block).height());

  while (block.isValid() && top <= event->rect().bottom()) {
    if (block.isVisible() && bottom >= event->rect().top()) {
      QString number = QString::number(blockNumber + 1);
      painter.setPen(Qt::green);
      painter.drawText(0, top, margin_->width(), fontMetrics().height(), Qt::AlignRight, number);
    }

    block = block.next();
    top = bottom;
    bottom = top + qRound(blockBoundingRect(block).height());
    blockNumber++;
  }
}

int CodeEditor::calSpace(int num) {
  int cnt = 1;
  while (num >= 10) {
    num = num / 10;
    cnt++;
  }

  int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * cnt;
  return space;
}
}  // namespace ch