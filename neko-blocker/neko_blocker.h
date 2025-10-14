#pragma once

#include <Windows.h>
#include <qwidget.h>

#include <QtWidgets/QMainWindow>

#include "ui_neko_blocker.h"

class NekoBlocker : public QMainWindow {
  Q_OBJECT

 public:
  // �غc�l
  NekoBlocker(QWidget *parent = nullptr);
  // �Ѻc�l
  ~NekoBlocker();

 private slots:
  // Ĳ�o���s�ҥ�/���Ψƥ�
  void onEnableButtonToggled();

 private:
  // ��L���_�B�z���
  static LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
  // ��L�W��
  void lock();
  // ��L����
  void unlock();
  // ������L���_
  void uninstallHook();

 private:
  Ui::NekoBlockerClass ui;
  static bool isLocked;
  static HHOOK keyboardHook;
};
