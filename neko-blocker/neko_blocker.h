#pragma once

#include <Windows.h>
#include <qobject.h>
#include <qsystemtrayicon.h>

class NekoBlocker : public QObject {
  Q_OBJECT

 public:
  // �غc�l
  NekoBlocker();
  // �Ѻc�l
  ~NekoBlocker();

 private slots:
  // ��L�W��
  void lockKeyboard();
  // ��L����
  void unlockKeyboard();

 private:
  // ��L���_�B�z���
  static LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
  // ������L���_
  void uninstallHook();

 private:
  QSystemTrayIcon* trayIcon;
  static bool isLocked;
  static HHOOK keyboardHook;
};
