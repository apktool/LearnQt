#include "icon_preview.h"

#include <QGridLayout>

namespace ch {
IconPreviewArea::IconPreviewArea(QWidget* parent) : QWidget(parent) {
  QGridLayout* mainLayout = new QGridLayout(this);

  for (int row = 0; row < NumStates; ++row) {
    stateLabels[row] = createHeaderLabel(IconStateName[row]);
    mainLayout->addWidget(stateLabels[row], row + 1, 0);
  }
  Q_ASSERT(NumStates == 2);

  for (int column = 0; column < NumModes; ++column) {
    modeLabels[column] = createHeaderLabel(IconModeName.at(column));
    mainLayout->addWidget(modeLabels[column], 0, column + 1);
  }
  Q_ASSERT(NumModes == 4);

  for (int column = 0; column < NumModes; ++column) {
    for (int row = 0; row < NumStates; ++row) {
      pixmapLabels[column][row] = createPixmapLabel();
      mainLayout->addWidget(pixmapLabels[column][row], row + 1, column + 1);
    }
  }
}

QLabel* IconPreviewArea::createHeaderLabel(const QString& text) {
  QLabel* label = new QLabel(tr("<b>%1</b>").arg(text));
  label->setAlignment(Qt::AlignCenter);
  return label;
}

QLabel* IconPreviewArea::createPixmapLabel() {
  QLabel* label = new QLabel();
  label->setEnabled(false);
  label->setAlignment(Qt::AlignCenter);
  label->setFrameShape(QFrame::Box);
  label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  label->setBackgroundRole(QPalette::Base);
  label->setAutoFillBackground(true);
  label->setMinimumSize(132, 132);
  return label;
}

void IconPreviewArea::SetSize(const QSize& size) {
  if (size != this->size) {
    this->size = size;
    UpdatePixmapLabels();
  }
}

void IconPreviewArea::SetIcon(const QIcon& icon) {
  this->icon = icon;
  UpdatePixmapLabels();
}

void IconPreviewArea::UpdatePixmapLabels() {
  for (int column = 0; column < NumModes; ++column) {
    for (int row = 0; row < NumStates; ++row) {
      QLabel* pixmapLabel = pixmapLabels[column][row];
      const QPixmap pixmap = icon.pixmap(size, devicePixelRatio(), IconMode.at(column), IconState.at(row));
      pixmapLabel->setPixmap(pixmap);
      pixmapLabel->setEnabled(!pixmap.isNull());
      QString toolTip;
      if (!pixmap.isNull()) {
        const QSize actualSize = icon.actualSize(size);
        toolTip = tr("Size: %1x%2\nActual size: %3x%4\nDevice pixel ratio: %5")
                      .arg(size.width())
                      .arg(size.height())
                      .arg(actualSize.width())
                      .arg(actualSize.height())
                      .arg(pixmap.devicePixelRatio());
      }
      pixmapLabel->setToolTip(toolTip);
    }
  }
}

}  // namespace ch
