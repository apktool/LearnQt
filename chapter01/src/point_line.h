#include <QWidget>

class PointLine : public QWidget {
  Q_OBJECT

 public:
  PointLine(QWidget *parent = nullptr);

 protected:
  void paintEvent(QPaintEvent *event) override;
};
