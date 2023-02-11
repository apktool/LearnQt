#include "windows.h"

#include <QCalendarWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QTextCharFormat>

namespace ch {
Windows::Windows(QWidget* parent, const Qt::WindowFlags& f) : QWidget(parent, f) {
  QGroupBox* previewLayout = createPreviewGroupBox();
  QGroupBox* generalLayout = createGeneralOptionsGroupBox();

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(previewLayout, 0, 0);
  layout->addWidget(generalLayout, 0, 1);
  setLayout(layout);
}

QGroupBox* Windows::createPreviewGroupBox() {
  calendar = new QCalendarWidget;
  calendar->setMinimumDate(QDate(1900, 1, 1));
  calendar->setMaximumDate(QDate(3000, 1, 1));
  calendar->setGridVisible(true);

  connect(calendar, &QCalendarWidget::currentPageChanged, calendar, [this]() -> void {
    QTextCharFormat firstFridayFormat;
    firstFridayFormat.setForeground(Qt::red);

    const QDate firstFriday(calendar->yearShown(), calendar->monthShown(), 11);
    calendar->setDateTextFormat(firstFriday, firstFridayFormat);
  });

  QGridLayout* layout = new QGridLayout();
  layout->addWidget(calendar, 0, 0, Qt::AlignCenter);

  QGroupBox* groupBox = new QGroupBox(tr("Preview"));
  groupBox->setLayout(layout);

  return groupBox;
}

QGroupBox* Windows::createGeneralOptionsGroupBox() {
  firstDayCombo = new QComboBox();
  firstDayCombo->addItem(tr("Sunday"), Qt::Sunday);
  firstDayCombo->addItem(tr("Monday"), Qt::Monday);
  firstDayCombo->addItem(tr("Tuesday"), Qt::Tuesday);
  firstDayCombo->addItem(tr("Wednesday"), Qt::Wednesday);
  firstDayCombo->addItem(tr("Thursday"), Qt::Thursday);
  firstDayCombo->addItem(tr("Friday"), Qt::Friday);
  firstDayCombo->addItem(tr("Saturday"), Qt::Saturday);

  // week
  QLabel* weekLabel = new QLabel(tr("Wee&k starts on: "));
  weekLabel->setBuddy(firstDayCombo);

  // grid
  QCheckBox* gridCheckBox = new QCheckBox(tr("&Grid"));
  gridCheckBox->setChecked(calendar->isGridVisible());

  // navigation
  QCheckBox* navigationCheckBox = new QCheckBox(tr("&Navigation bar"));
  navigationCheckBox->setChecked(true);

  // horizontal header
  horizontalHeaderCombo = new QComboBox();
  horizontalHeaderCombo->addItem(tr("Single letter day names"), QCalendarWidget::SingleLetterDayNames);
  horizontalHeaderCombo->addItem(tr("Short day names"), QCalendarWidget::ShortDayNames);
  horizontalHeaderCombo->addItem(tr("None"), QCalendarWidget::NoHorizontalHeader);
  horizontalHeaderCombo->setCurrentIndex(1);

  QLabel* horizontalHeaderLabel = new QLabel(tr("&Horizontal header:"));
  horizontalHeaderLabel->setBuddy(horizontalHeaderCombo);

  // vertical header
  verticalHeaderCombo = new QComboBox();
  verticalHeaderCombo->addItem(tr("ISO week numbers"), QCalendarWidget::ISOWeekNumbers);
  verticalHeaderCombo->addItem(tr("None"), QCalendarWidget::NoVerticalHeader);

  QLabel* verticalHeaderLabel = new QLabel(tr("&Vertical header:"));
  verticalHeaderLabel->setBuddy(verticalHeaderCombo);

  // layout
  QGridLayout* layout = new QGridLayout();
  layout->addWidget(weekLabel, 0, 0);
  layout->addWidget(firstDayCombo, 0, 1);
  layout->addWidget(gridCheckBox, 1, 0);
  layout->addWidget(navigationCheckBox, 1, 1);
  layout->addWidget(horizontalHeaderLabel, 2, 0);
  layout->addWidget(horizontalHeaderCombo, 2, 1);
  layout->addWidget(verticalHeaderLabel, 3, 0);
  layout->addWidget(verticalHeaderCombo, 3, 1);

  // group box
  QGroupBox* groupBox = new QGroupBox(tr("General Options"));
  groupBox->setLayout(layout);

  // signal and slot
  connect(firstDayCombo, &QComboBox::currentIndexChanged, this, [this](int index) -> void {
    calendar->setFirstDayOfWeek(Qt::DayOfWeek(firstDayCombo->itemData(index).toInt()));
  });
  connect(gridCheckBox, &QCheckBox::toggled, calendar, &QCalendarWidget::setGridVisible);
  connect(navigationCheckBox, &QCheckBox::toggled, calendar, &QCalendarWidget::setNavigationBarVisible);
  connect(horizontalHeaderCombo, &QComboBox::currentIndexChanged, this, [this](int index) -> void {
    calendar->setHorizontalHeaderFormat(
        QCalendarWidget::HorizontalHeaderFormat(horizontalHeaderCombo->itemData(index).toInt()));
  });
  connect(verticalHeaderCombo, &QComboBox::currentIndexChanged, this, [this](int index) -> void {
    calendar->setVerticalHeaderFormat(
        QCalendarWidget::VerticalHeaderFormat(verticalHeaderCombo->itemData(index).toInt()));
  });

  return groupBox;
}
}  // namespace ch