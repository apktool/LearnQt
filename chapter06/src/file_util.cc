#include "file_util.h"

#include <QFileDialog>
#include <QImageReader>

namespace ch {
void FileUtil::AddImages(const QString& directory) {
  QFileDialog fileDialog(parent, QString::fromStdString("Open Images"), directory);
  QStringList mimeTypeFilters;
  const QList<QByteArray> mimeTypes = QImageReader::supportedMimeTypes();
  for (const QByteArray& mimeTypeName : mimeTypes) {
    mimeTypeFilters.append(mimeTypeName);
  }
  mimeTypeFilters.sort();
  fileDialog.setMimeTypeFilters(mimeTypeFilters);
  fileDialog.selectMimeTypeFilter(QString("image/png"));
  fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
  fileDialog.setFileMode(QFileDialog::ExistingFiles);

  if (fileDialog.exec() == QDialog::Accepted) {
    loadImages(fileDialog.selectedFiles());
  }
}

void FileUtil::loadImages(const QStringList& files) {
  for (const QString& file : files) {
    const QFileInfo fileInfo(file);
    const QString imageName = fileInfo.baseName();
    const QString fileName2x =
        fileInfo.absolutePath() + QLatin1Char('/') + imageName + QLatin1String("@2x.") + fileInfo.suffix();
    const QFileInfo fileInfo2x(fileName2x);
    images.push_back(std::move(fileInfo));
  }
}

void FileUtil::ClearAll() { images.clear(); }

void FileUtil::GetAll(QVector<QFileInfo>* images) { *images = this->images; }
}  // namespace ch
