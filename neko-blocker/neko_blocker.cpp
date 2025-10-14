#include "neko_blocker.h"

#include <Windows.h>
#include <qobject.h>

#include "my_push_button.h"
#include "ui_neko_blocker.h"

bool NekoBlocker::isLocked = false;
HHOOK NekoBlocker::keyboardHook = NULL;

/// <summary>
/// �غc�l
/// </summary>
/// <param name="parent"></param>
NekoBlocker::NekoBlocker(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  QObject::connect(ui.enableButton, &MyPushButton::toggled, this,
                   &NekoBlocker::onEnableButtonToggled);
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
void NekoBlocker::lock() {
  if (!keyboardHook) {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc,
                                    GetModuleHandle(NULL), 0);
  }

  isLocked = true;
}

/// <summary>
/// ��L����
/// </summary>
void NekoBlocker::unlock() { isLocked = false; }

/// <summary>
/// ������L���_
/// </summary>
void NekoBlocker::uninstallHook() {
  if (isLocked) {
    UnhookWindowsHookEx(keyboardHook);
    keyboardHook = NULL;
  }
}

/// <summary>
/// Ĳ�o���s�ҥ�/���Ψƥ�
/// </summary>
void NekoBlocker::onEnableButtonToggled() {
  if (ui.enableButton->isChecked()) {
    lock();
  } else {
    unlock();
  }

  ui.enableButton->setText(isLocked ? tr("Disable") : tr("Enable"));
}
