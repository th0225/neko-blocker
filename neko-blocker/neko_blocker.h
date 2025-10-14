#pragma once

#include <Windows.h>
#include <qobject.h>
#include <qsystemtrayicon.h>

class NekoBlocker : public QObject {
  Q_OBJECT

 public:
  // 建構子
  NekoBlocker();
  // 解構子
  ~NekoBlocker();

 private slots:
  // 鍵盤上鎖
  void lockKeyboard();
  // 鍵盤解鎖
  void unlockKeyboard();

 private:
  // 鍵盤掛鉤處理函數
  static LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
  // 移除鍵盤掛鉤
  void uninstallHook();

 private:
  QSystemTrayIcon* trayIcon;
  static bool isLocked;
  static HHOOK keyboardHook;
};
