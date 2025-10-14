#include "neko_blocker.h"

#include <Windows.h>
#include <qaction.h>
#include <qapplication.h>
#include <qicon.h>
#include <qmenu.h>
#include <qobject.h>
#include <qsystemtrayicon.h>
#include <qwidget.h>

bool NekoBlocker::isLocked = false;
HHOOK NekoBlocker::keyboardHook = NULL;

/// <summary>
/// �غc�l
/// </summary>
/// <param name="parent"></param>
NekoBlocker::NekoBlocker() {
  // �]�wicon
  trayIcon = new QSystemTrayIcon(QIcon(":/NekoBlocker/keyboard.png"), this);

  // �إߨt�ΧX���
  QMenu* menu = new QMenu();
  QAction* lockAction = new QAction(tr("Lock"), this);
  QAction* exitAction = new QAction(tr("Exit"), this);
  lockAction->setCheckable(true);

  QObject::connect(lockAction, &QAction::toggled, this, [=](bool checked) {
    if (checked) {
      lockKeyboard();
      trayIcon->setIcon(QIcon(":/NekoBlocker/keyboard_off.png"));
    } else {
      unlockKeyboard();
      trayIcon->setIcon(QIcon(":/NekoBlocker/keyboard.png"));
    }
  });
  QObject::connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);

  menu->addAction(lockAction);
  menu->addSeparator();
  menu->addAction(exitAction);

  trayIcon->setContextMenu(menu);
  trayIcon->show();
}

/// <summary>
/// �Ѻc�l
/// </summary>
NekoBlocker::~NekoBlocker() { uninstallHook(); }

/// <summary>
/// ��L���_�B�z���
/// </summary>
/// <param name="nCode"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
LRESULT CALLBACK NekoBlocker::keyboardProc(int nCode, WPARAM wParam,
                                           LPARAM lParam) {
  if (nCode >= 0 && isLocked) {
    return 1;
  }

  return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

/// <summary>
/// ��L�W��
/// </summary>
void NekoBlocker::lockKeyboard() {
  if (!keyboardHook) {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc,
                                    GetModuleHandle(NULL), 0);
  }

  isLocked = true;
}

/// <summary>
/// ��L����
/// </summary>
void NekoBlocker::unlockKeyboard() { isLocked = false; }

/// <summary>
/// ������L���_
/// </summary>
void NekoBlocker::uninstallHook() {
  if (isLocked) {
    UnhookWindowsHookEx(keyboardHook);
    keyboardHook = NULL;
  }
}
