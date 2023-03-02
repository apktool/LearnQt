#include <QFileInfo>
#include <QImage>
#include <QString>
#include <QStringList>

namespace ch {
class FileUtil {
 public:
  FileUtil(QWidget* parent) : parent(parent) {}

  void GetAll(QVector<QFileInfo>* images);
  void AddImages(const QString& directory);
  void ClearAll();

 public:
  QWidget* parent{nullptr};

 private:
  void loadImages(const QStringList& files);

  QVector<QFileInfo> images;
};
}  // namespace ch