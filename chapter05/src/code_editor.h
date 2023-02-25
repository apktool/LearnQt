#include <QPlainTextEdit>

namespace ch {
class CodeEditor : public QPlainTextEdit {
  Q_OBJECT

 public:
  CodeEditor(QWidget* parent = nullptr);

  void UpdateMarginNo(QPaintEvent* event);

 protected:
  void resizeEvent(QResizeEvent* event) override;

 private:
  int calSpace(int num);

  QWidget* margin_;
};

class LeftMargin : public QWidget {
 public:
  LeftMargin(CodeEditor* code_editor) : QWidget(code_editor), code_editor_(code_editor) {}

 protected:
  void paintEvent(QPaintEvent* event) override { code_editor_->UpdateMarginNo(event); }

 private:
  CodeEditor* code_editor_;
};
}  // namespace ch