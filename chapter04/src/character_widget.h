#pragma once

#include <QWidget>

namespace ch {
class CharacterWidget : public QWidget {
  Q_OBJECT

 public:
  CharacterWidget(QWidget* parent = nullptr);
  QSize sizeHint() const override;

 protected:
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

 public slots:
  void updateFont(const QFont& font);
  void updateSize(const QString& fontSize);
  void updateStyle(const QString& fontStyle);
  void updateFontMerging(bool enable);

 signals:
  void characterSelected(const QString& character);

 private:
  void calculateSquareSize();

 private:
  QFont displayFont;
  int squareSize = 0;
  int columns = 16;
  int lastKey = -1;
};
}  // namespace ch