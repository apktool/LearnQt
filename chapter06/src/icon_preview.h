#pragma once

#include <QLabel>
#include <QWidget>

namespace ch {
static const QList<QIcon::Mode> IconMode = {QIcon::Normal, QIcon::Active, QIcon::Disabled, QIcon::Selected};
static const QList<QIcon::State> IconState = {QIcon::Off, QIcon::On};
static const QStringList IconModeName = {"Normal", "Active", "Disabled", "Selected"};
static const QStringList IconStateName = {"Off", "On"};

class IconPreviewArea : public QWidget {
  Q_OBJECT
 public:
  explicit IconPreviewArea(QWidget* parent = nullptr);

  void SetIcon(const QIcon& icon);
  void SetSize(const QSize& size);
  void UpdatePixmapLabels();

 private:
  enum { NumModes = 4, NumStates = 2 };

  QLabel* createHeaderLabel(const QString& text);
  QLabel* createPixmapLabel();

  QLabel* stateLabels[NumStates];
  QLabel* modeLabels[NumModes];
  QLabel* pixmapLabels[NumModes][NumStates];

 private:
  QIcon icon;
  QSize size;
};
}  // namespace ch