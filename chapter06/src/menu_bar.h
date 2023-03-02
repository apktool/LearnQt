#pragma once

#include <QMenu>

#include "file_util.h"

namespace ch {
class MenuBar : public QMenu {
  Q_OBJECT
 public:
  explicit MenuBar(QWidget* parent = nullptr);

  // File
  void AddImages(const QString& image);
  void RemoveImages();

  // Help
  void About(bool check);

 public:
  void GetAllImages(QVector<QFileInfo>* images);

 private:
  FileUtil* file_util_;
};
};  // namespace ch
