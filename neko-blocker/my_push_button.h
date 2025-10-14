#pragma once

#include <qcoreevent.h>
#include <qevent.h>
#include <qpushbutton.h>
#include <qwidget.h>

class MyPushButton : public QPushButton {
  Q_OBJECT

 public:
  explicit MyPushButton(QWidget* parent = nullptr);

 protected:
  // 重寫繪製事件
  void paintEvent(QPaintEvent* event) override;
  // 鼠標進入事件
  void enterEvent(QEvent* event) override;
  // 鼠標離開事件
  void leaveEvent(QEvent* event) override;
  // 鼠標按下事件
  void mousePressEvent(QMouseEvent* event) override;
  // 鼠標釋放事件
  void mouseReleaseEvent(QMouseEvent* event) override;

 signals:
  void onClicked();

 public:
  bool Checkable = false;
  bool Checked = false;
  bool Enabled = true;

 private:
  bool isHovered;
  bool pressed;
};