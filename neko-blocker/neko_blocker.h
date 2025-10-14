#pragma once

#include <Windows.h>
#include <qwidget.h>

#include <QtWidgets/QMainWindow>

#include "ui_neko_blocker.h"

class NekoBlocker : public QMainWindow {
  Q_OBJECT

 public:
  // 建構子
  NekoBlocker(QWidget *parent = nullptr);
  // 解構子
  ~NekoBlocker();

 private slots:
  // 觸發按鈕啟用/停用事件
  void onEnableButtonToggled();

 private:
  // 鍵盤掛鉤處理函數
  static LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
  // 鍵盤上鎖
  void lock();
  // 鍵盤解鎖
  void unlock();
  // 移除鍵盤掛鉤
  void uninstallHook();

 private:
  Ui::NekoBlockerClass ui;
  static bool isLocked;
  static HHOOK keyboardHook;
};
