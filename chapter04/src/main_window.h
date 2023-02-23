#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QFontComboBox>
#include <QMainWindow>
#include <QPushButton>

namespace ch {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);

 private slots:
  void findStyles(const QFont& font);
  void findSizes(const QFont& font);
  void insertCharacter(const QString &character);
  void updateClipboard();

 private:
  QFontComboBox* fontCombo{nullptr};
  QComboBox* sizeCombo{nullptr};
  QComboBox* styleCombo{nullptr};
  QLineEdit* lineEdit{nullptr};
  QCheckBox* fontMerging{nullptr};

  QPushButton* clipboardButton{nullptr};
};
}  // namespace ch