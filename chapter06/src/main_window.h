#include <QAbstractButton>
#include <QGroupBox>
#include <QMainWindow>
#include <QTableWidget>

#include "icon_preview.h"
#include "menu_bar.h"

namespace ch {
class MainWindow : public QMainWindow {
 public:
  explicit MainWindow(QWidget* parent = nullptr);
  void show();

 private:
  void initMenu();
  QGroupBox* initPreview();
  QGroupBox* initImage();
  QGroupBox* initSize();
  QGroupBox* initDpiSize();

  void updateImage();

 protected slots:
  void changeSize(QAbstractButton* button, bool);
  void changeIcon();
  void addDefaultImage(bool check);
  void addOtherImage(bool check);
  void removeAllImage(bool check);
  void screenChanged();

 private:
  MenuBar* menu;
  IconPreviewArea* previewArea;
  QTableWidget* imagesTable;
  QButtonGroup* sizeButtonGroup;
  QLabel* screenNameLabel;
  QLabel* devicePixelRatioLabel;
};
}  // namespace ch