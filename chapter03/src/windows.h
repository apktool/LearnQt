#pragma once

#include <QCalendarWidget>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QWidget>

namespace ch {

class Windows : public QWidget {
  Q_OBJECT

 public:
  Windows(QWidget* parent = nullptr, const Qt::WindowFlags& f = Qt::Widget);

 private:
  QGroupBox* createPreviewGroupBox();
  QGroupBox* createGeneralOptionsGroupBox();

 private:
  QCalendarWidget* calendar;

  QComboBox* firstDayCombo;
  QComboBox* horizontalHeaderCombo;
  QComboBox* verticalHeaderCombo;
};

}  // namespace ch
