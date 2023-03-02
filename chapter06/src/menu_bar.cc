#include "menu_bar.h"

#include <QImageReader>
#include <QMessageBox>
#include <QStandardPaths>

namespace ch {
MenuBar::MenuBar(QWidget* parent) : QMenu(parent) { file_util_ = new FileUtil(this); }

void MenuBar::AddImages(const QString& image) { file_util_->AddImages(image); }

void MenuBar::RemoveImages() { file_util_->ClearAll(); }

void MenuBar::About(bool) {
  QMessageBox::about(this, tr("About Icons"),
                     tr("The <b>Icons</b> example illustrates how Qt renders an icon in "
                        "different modes (active, normal, disabled, and selected) and "
                        "states (on and off) based on a set of images."));
}

void MenuBar::GetAllImages(QVector<QFileInfo>* images) { file_util_->GetAll(images); }
}  // namespace ch