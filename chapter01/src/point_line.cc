#include "point_line.h"

#include <QPainter>

PointLine::PointLine(QWidget *parent) : QWidget(parent) {
  setWindowTitle(tr("point and line"));
  resize(512, 512);
}

void PointLine::paintEvent(QPaintEvent *) {
  QPainter painter(this);

  QPen pen;
  pen.setBrush(Qt::blue);
  pen.setCapStyle(Qt::RoundCap);
  pen.setWidth(10);

  painter.setPen(pen);
  painter.drawLine(QLine(100, 100, 400, 400));
  painter.drawLine(QLine(400, 100, 100, 400));

  painter.drawText(QWidget::width() / 2, 50, "Hello Qt");
}
