#include "main_window.h"

#include <QApplication>
#include <QButtonGroup>
#include <QFormLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QMenuBar>
#include <QRadioButton>
#include <QScreen>
#include <QStandardPaths>
#include <QStyleFactory>
#include <QWindow>

#include "icon_preview.h"
#include "menu_bar.h"

namespace ch {
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  QWidget* centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  QGridLayout* mainLayout = new QGridLayout(centralWidget);
  centralWidget->setLayout(mainLayout);

  initMenu();

  QVBoxLayout* previewLayout = new QVBoxLayout();
  previewLayout->addWidget(initPreview());
  mainLayout->addLayout(previewLayout, 0, 0, 1, 2);

  QHBoxLayout* imageLayout = new QHBoxLayout();
  imageLayout->addWidget(initImage());
  mainLayout->addLayout(imageLayout, 1, 0);

  QVBoxLayout* vBox = new QVBoxLayout();
  vBox->addWidget(initSize());
  vBox->addWidget(initDpiSize());
  mainLayout->addLayout(vBox, 1, 1);
}

void MainWindow::initMenu() {
  menu = new MenuBar(this);

  // add file
  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

  QAction* sampleAction = new QAction(tr("Add &Sample Images ..."), this);
  sampleAction->setShortcut(tr("Ctrl+A"));
  fileMenu->addAction(sampleAction);
  connect(sampleAction, &QAction::triggered, this, &MainWindow::addDefaultImage);

  QAction* commonAction = new QAction(tr("&Add Images ..."), this);
  commonAction->setShortcut(QKeySequence::Open);
  fileMenu->addAction(commonAction);
  connect(commonAction, &QAction::triggered, this, &MainWindow::addOtherImage);

  QAction* removeAction = new QAction(tr("&Remove All Images ..."), this);
  removeAction->setShortcut(tr("Ctrl+R"));
  fileMenu->addAction(removeAction);
  connect(removeAction, &QAction::triggered, this, &MainWindow::removeAllImage);

  fileMenu->addSeparator();

  QAction* quitAction = new QAction(tr("&Quit"), this);
  quitAction->setShortcut(QKeySequence::Quit);
  fileMenu->addAction(quitAction);
  connect(quitAction, &QAction::triggered, this, &QWidget::close);

  // add help
  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));

  QAction* aboutAction = new QAction(tr("&About ..."), this);
  aboutAction->setShortcut(tr("F1"));
  helpMenu->addAction(aboutAction);
  connect(aboutAction, &QAction::triggered, menu, &MenuBar::About);
}

QGroupBox* MainWindow::initPreview() {
  QGroupBox* box = new QGroupBox(tr("Preview"));
  QVBoxLayout* layout = new QVBoxLayout(box);
  previewArea = new IconPreviewArea(box);
  layout->addWidget(previewArea);

  return box;
}

QGroupBox* MainWindow::initImage() {
  imagesTable = new QTableWidget();
  imagesTable->setSelectionMode(QAbstractItemView::NoSelection);

  const QStringList labels({tr("Image"), tr("Mode"), tr("State")});

  imagesTable->horizontalHeader()->setDefaultSectionSize(90);
  imagesTable->setColumnCount(labels.size());
  imagesTable->setHorizontalHeaderLabels(labels);
  imagesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
  imagesTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
  imagesTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
  imagesTable->verticalHeader()->hide();

  connect(imagesTable, &QTableWidget::itemChanged, this, &MainWindow::changeIcon);

  // layout

  QGroupBox* box = new QGroupBox(tr("Images"));
  QVBoxLayout* layout = new QVBoxLayout(box);
  layout->addWidget(imagesTable);
  return box;
}

QGroupBox* MainWindow::initSize() {
  QGroupBox* box = new QGroupBox(tr("Icon size"));
  QGridLayout* layout = new QGridLayout(box);

  sizeButtonGroup = new QButtonGroup(box);
  sizeButtonGroup->setExclusive(true);

  QRadioButton* smallRadioButton = new QRadioButton(tr("Small (16 x 16)"));
  sizeButtonGroup->addButton(smallRadioButton, QStyle::PM_SmallIconSize);
  QRadioButton* largeRadioButton = new QRadioButton(tr("Large (32 x 32)"));
  sizeButtonGroup->addButton(largeRadioButton, QStyle::PM_LargeIconSize);
  QRadioButton* toolBarRadioButton = new QRadioButton(tr("Toolbars (24 x 24)"));
  sizeButtonGroup->addButton(toolBarRadioButton, QStyle::PM_ToolBarIconSize);
  QRadioButton* listViewRadioButton = new QRadioButton(tr("List views (24 x 24)"));
  sizeButtonGroup->addButton(listViewRadioButton, QStyle::PM_ListViewIconSize);
  QRadioButton* iconViewRadioButton = new QRadioButton(tr("Icon views (32 x 32)"));
  sizeButtonGroup->addButton(iconViewRadioButton, QStyle::PM_IconViewIconSize);
  QRadioButton* tabBarRadioButton = new QRadioButton(tr("Tab bars (16 x 16)"));
  sizeButtonGroup->addButton(tabBarRadioButton, QStyle::PM_TabBarIconSize);
  QRadioButton* otherRadioButton = new QRadioButton(tr("Other:"));
  sizeButtonGroup->addButton(otherRadioButton, QStyle::PM_CustomBase);

  layout->addWidget(smallRadioButton, 0, 0);
  layout->addWidget(largeRadioButton, 1, 0);
  layout->addWidget(toolBarRadioButton, 2, 0);
  layout->addWidget(listViewRadioButton, 0, 1);
  layout->addWidget(iconViewRadioButton, 1, 1);
  layout->addWidget(tabBarRadioButton, 2, 1);
  layout->setRowStretch(4, 1);

  connect(sizeButtonGroup, &QButtonGroup::buttonToggled, this, &MainWindow::changeSize);

  return box;
}

QGroupBox* MainWindow::initDpiSize() {
  QGroupBox* box = new QGroupBox(tr("High DPI Scaling"));
  QFormLayout* layout = new QFormLayout(box);

  screenNameLabel = new QLabel(box);
  layout->addRow(tr("Screen:"), screenNameLabel);

  devicePixelRatioLabel = new QLabel(box);
  layout->addRow(tr("Device pixel ratio:"), devicePixelRatioLabel);

  return box;
}

void MainWindow::show() {
  QMainWindow::show();

  connect(windowHandle(), &QWindow::screenChanged, this, &MainWindow::screenChanged);
  screenChanged();
}

void MainWindow::screenChanged() {
  devicePixelRatioLabel->setText(QString::number(devicePixelRatio()));
  if (const QWindow* window = windowHandle()) {
    const QScreen* screen = window->screen();
    const QString screenDescription =
        tr("\"%1\" (%2x%3)").arg(screen->name()).arg(screen->geometry().width()).arg(screen->geometry().height());
    screenNameLabel->setText(screenDescription);
  }
  changeIcon();
}

void MainWindow::changeIcon() {
  QIcon icon;

  for (int row = 0; row < imagesTable->rowCount(); row++) {
    const QTableWidgetItem* fileItem = imagesTable->item(row, 0);
    const QTableWidgetItem* modeItem = imagesTable->item(row, 1);
    const QTableWidgetItem* stateItem = imagesTable->item(row, 2);

    if (fileItem->checkState() == Qt::Checked) {
      const QIcon::Mode mode = IconMode.at(IconModeName.indexOf(modeItem->text()));
      const QIcon::State state = IconState.at(IconStateName.indexOf(stateItem->text()));

      const QString file = fileItem->data(Qt::UserRole).toString();
      QImage image(fileItem->data(Qt::UserRole).toString());
      if (!image.isNull()) {
        icon.addPixmap(QPixmap::fromImage(image), mode, state);
      }
    }
  }

  previewArea->SetSize(QSize(128, 128));
  previewArea->SetIcon(icon);
}

void MainWindow::changeSize(QAbstractButton* button, bool checked) {
  if (!checked) {
    return;
  }

  const int index = sizeButtonGroup->id(button);
  const int extent = QApplication::style()->pixelMetric(static_cast<QStyle::PixelMetric>(index));
  previewArea->SetSize(QSize(extent, extent));
}

void MainWindow::addDefaultImage(bool check) {
  QString dir = QLatin1String("/home/li/Pictures");
  menu->AddImages(dir);
  updateImage();
  menu->RemoveImages();
}

void MainWindow::addOtherImage(bool check) {
  QString dir = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).value(0, QString());
  menu->AddImages(dir);
  updateImage();
  menu->RemoveImages();
}

void MainWindow::removeAllImage(bool check) {
  imagesTable->clear();
  imagesTable->setRowCount(0);
  updateImage();
  menu->RemoveImages();
}

void MainWindow::updateImage() {
  QVector<QFileInfo> images;
  menu->GetAllImages(&images);

  for (const QFileInfo& image : images) {
    const int row = imagesTable->rowCount();
    imagesTable->setRowCount(row + 1);

    QString fileName = image.baseName();

    QTableWidgetItem* fileItem = new QTableWidgetItem(fileName);
    fileItem->setData(Qt::UserRole, image.absoluteFilePath());
    fileItem->setIcon(QPixmap::fromImage(QImage(image.baseName())));
    fileItem->setFlags((fileItem->flags() | Qt::ItemIsUserCheckable) & ~Qt::ItemIsEditable);

    QIcon::Mode mode = QIcon::Normal;
    QIcon::State state = QIcon::Off;

    imagesTable->setItem(row, 0, fileItem);
    QTableWidgetItem* modeItem = new QTableWidgetItem(IconModeName.at(IconMode.indexOf(mode)));
    imagesTable->setItem(row, 1, modeItem);
    QTableWidgetItem* stateItem = new QTableWidgetItem(IconStateName.at(IconState.indexOf(state)));
    imagesTable->setItem(row, 2, stateItem);
    imagesTable->openPersistentEditor(modeItem);
    imagesTable->openPersistentEditor(stateItem);

    fileItem->setCheckState(Qt::Checked);
  }
}
}  // namespace ch