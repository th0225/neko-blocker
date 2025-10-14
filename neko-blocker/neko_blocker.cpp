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
/// 建構子
/// </summary>
/// <param name="parent"></param>
NekoBlocker::NekoBlocker() {
  // 設定icon
  trayIcon = new QSystemTrayIcon(QIcon(":/NekoBlocker/keyboard.png"), this);

  // 建立系統匣選單
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
/// 解構子
/// </summary>
NekoBlocker::~NekoBlocker() { uninstallHook(); }

/// <summary>
/// 鍵盤掛鉤處理函數
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
/// 鍵盤上鎖
/// </summary>
void NekoBlocker::lockKeyboard() {
  if (!keyboardHook) {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc,
                                    GetModuleHandle(NULL), 0);
  }

  isLocked = true;
}

/// <summary>
/// 鍵盤解鎖
/// </summary>
void NekoBlocker::unlockKeyboard() { isLocked = false; }

/// <summary>
/// 移除鍵盤掛鉤
/// </summary>
void NekoBlocker::uninstallHook() {
  if (isLocked) {
    UnhookWindowsHookEx(keyboardHook);
    keyboardHook = NULL;
  }
}
