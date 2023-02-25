#include <QApplication>

#include "src/code_editor.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  ch::CodeEditor editor;
  editor.show();

  app.exec();
}
