#include <qmessagebox.h>
#include <qsharedmemory.h>

#include <QtWidgets/QApplication>

#include "neko_blocker.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  // 避免程式重複開啟
  QSharedMemory sharedMemory("neko-blocker-unique-key");
  if (!sharedMemory.create(1)) {
    QMessageBox::warning(nullptr, "Neko Blocker",
                         "Another instance is already running.");
    return 0;
  }

  NekoBlocker window;

  return app.exec();
}
