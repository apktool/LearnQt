#include "main_window.h"

#include <QApplication>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QClipboard>

#include "character_widget.h"

namespace ch {
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(tr("Quit"), this, &QWidget::close);

  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
  helpMenu->addAction(tr("Show Font Info"), this, []() -> void { qDebug() << "Hello world"; });

  // ------------------

  QHBoxLayout* controlsLayout = new QHBoxLayout();

  QLabel* filterLabel = new QLabel(tr("Filter:"));
  QComboBox* filterCombo = new QComboBox();
  filterCombo->addItem(tr("All"), QVariant::fromValue(QFontComboBox::AllFonts));
  filterCombo->addItem(tr("Scalable"), QVariant::fromValue(QFontComboBox::ScalableFonts));
  filterCombo->addItem(tr("Monospaced"), QVariant::fromValue(QFontComboBox::MonospacedFonts));
  filterCombo->addItem(tr("Proportional"), QVariant::fromValue(QFontComboBox::ProportionalFonts));
  filterCombo->setCurrentIndex(0);
  controlsLayout->addWidget(filterLabel);
  controlsLayout->addWidget(filterCombo);

  QLabel* fontLabel = new QLabel(tr("Font:"));
  fontCombo = new QFontComboBox();
  controlsLayout->addWidget(fontLabel);
  controlsLayout->addWidget(fontCombo);

  QLabel* sizeLabel = new QLabel(tr("Size:"));
  sizeCombo = new QComboBox();
  controlsLayout->addWidget(sizeLabel);
  controlsLayout->addWidget(sizeCombo);

  QLabel* styleLabel = new QLabel(tr("Style:"));
  styleCombo = new QComboBox();
  controlsLayout->addWidget(styleLabel);
  controlsLayout->addWidget(styleCombo);

  QLabel* fontMergingLabel = new QLabel(tr("Automatic Font Merging:"));
  fontMerging = new QCheckBox();
  controlsLayout->addWidget(fontMergingLabel);
  controlsLayout->addWidget(fontMerging);

  // ------------------

  QScrollArea* scrollArea = new QScrollArea();
  CharacterWidget* characterWidget = new CharacterWidget();
  scrollArea->setWidget(characterWidget);

  // ------------------

  lineEdit = new QLineEdit;
  lineEdit->setClearButtonEnabled(true);

  clipboardButton = new QPushButton(tr("&To Clipboard"));

  QHBoxLayout* lineLayout = new QHBoxLayout();
  lineLayout->addWidget(lineEdit, 1);
  lineLayout->addSpacing(10);
  lineLayout->addWidget(clipboardButton, 2);

  // ------------------

  QVBoxLayout* main = new QVBoxLayout();
  main->addLayout(controlsLayout);
  main->addWidget(scrollArea);
  main->addLayout(lineLayout);

  // ------------------

  QWidget* widget = new QWidget();
  widget->setLayout(main);

  findStyles(fontCombo->currentFont());
  findSizes(fontCombo->currentFont());

  connect(fontCombo, &QFontComboBox::currentFontChanged, this, &MainWindow::findStyles);
  connect(fontCombo, &QFontComboBox::currentFontChanged, this, &MainWindow::findSizes);
  connect(fontCombo, &QFontComboBox::currentFontChanged, characterWidget, &CharacterWidget::updateFont);
  connect(sizeCombo, &QComboBox::currentTextChanged, characterWidget, &CharacterWidget::updateSize);
  connect(styleCombo, &QComboBox::currentTextChanged, characterWidget, &CharacterWidget::updateStyle);
  connect(characterWidget, &CharacterWidget::characterSelected, this, &MainWindow::insertCharacter);
  connect(fontMerging, &QCheckBox::clicked, characterWidget, &CharacterWidget::updateFontMerging);
  connect(clipboardButton, &QAbstractButton::clicked, this, &MainWindow::updateClipboard);

  // ------------------

  setCentralWidget(widget);
  setWindowTitle(tr("Character Map"));
}

void MainWindow::findStyles(const QFont& font) {
  QString currentItem = styleCombo->currentText();
  styleCombo->clear();

  const QStringList styles = QFontDatabase::styles(font.family());
  for (const QString& style : styles) {
    styleCombo->addItem(style);
  }

  int styleIndex = styleCombo->findText(currentItem);

  if (styleIndex == -1) {
    styleCombo->setCurrentIndex(0);
  } else {
    styleCombo->setCurrentIndex(styleIndex);
  }
}

void MainWindow::findSizes(const QFont& font) {
  QString currentSize = sizeCombo->currentText();

  const QSignalBlocker blocker(sizeCombo);
  sizeCombo->clear();

  if (QFontDatabase::isSmoothlyScalable(font.family(), QFontDatabase::styleString(font))) {
    const QList<int> sizes = QFontDatabase::standardSizes();
    for (const int size : sizes) {
      sizeCombo->addItem(QVariant(size).toString());
      sizeCombo->setEditable(true);
    }
  } else {
    const QList<int> sizes = QFontDatabase::smoothSizes(font.family(), QFontDatabase::styleString(font));
    for (const int size : sizes) {
      sizeCombo->addItem(QVariant(size).toString());
      sizeCombo->setEditable(false);
    }
  }

  int sizeIndex = sizeCombo->findText(currentSize);

  if (sizeIndex == -1) {
    sizeCombo->setCurrentIndex(qMax(0, sizeCombo->count() / 3));
  } else {
    sizeCombo->setCurrentIndex(sizeIndex);
  }
}

void MainWindow::insertCharacter(const QString& character) { lineEdit->insert(character); }

void MainWindow::updateClipboard() {
  QGuiApplication::clipboard()->setText(lineEdit->text(), QClipboard::Clipboard);
  QGuiApplication::clipboard()->setText(lineEdit->text(), QClipboard::Selection);
}
}  // namespace ch