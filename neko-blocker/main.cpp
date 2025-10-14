#include <QtWidgets/QApplication>

#include "neko_blocker.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  NekoBlocker window;

  return app.exec();
}
