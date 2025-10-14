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
  // ���gø�s�ƥ�
  void paintEvent(QPaintEvent* event) override;
  // ���жi�J�ƥ�
  void enterEvent(QEvent* event) override;
  // �������}�ƥ�
  void leaveEvent(QEvent* event) override;
  // ���Ы��U�ƥ�
  void mousePressEvent(QMouseEvent* event) override;
  // ��������ƥ�
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