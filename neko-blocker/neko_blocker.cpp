#include "neko_blocker.h"

#include <Windows.h>
#include <qobject.h>

#include "my_push_button.h"
#include "ui_neko_blocker.h"

bool NekoBlocker::isLocked = false;
HHOOK NekoBlocker::keyboardHook = NULL;

/// <summary>
/// 建構子
/// </summary>
/// <param name="parent"></param>
NekoBlocker::NekoBlocker(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  QObject::connect(ui.enableButton, &MyPushButton::toggled, this,
                   &NekoBlocker::onEnableButtonToggled);
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
void NekoBlocker::lock() {
  if (!keyboardHook) {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc,
                                    GetModuleHandle(NULL), 0);
  }

  isLocked = true;
}

/// <summary>
/// 鍵盤解鎖
/// </summary>
void NekoBlocker::unlock() { isLocked = false; }

/// <summary>
/// 移除鍵盤掛鉤
/// </summary>
void NekoBlocker::uninstallHook() {
  if (isLocked) {
    UnhookWindowsHookEx(keyboardHook);
    keyboardHook = NULL;
  }
}

/// <summary>
/// 觸發按鈕啟用/停用事件
/// </summary>
void NekoBlocker::onEnableButtonToggled() {
  if (ui.enableButton->isChecked()) {
    lock();
  } else {
    unlock();
  }

  ui.enableButton->setText(isLocked ? tr("Disable") : tr("Enable"));
}
