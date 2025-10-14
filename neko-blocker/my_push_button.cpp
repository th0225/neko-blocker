#include "my_push_button.h"

#include <qbrush.h>
#include <qcolor.h>
#include <qevent.h>
#include <qfont.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpen.h>
#include <qpushbutton.h>
#include <qwidget.h>

MyPushButton::MyPushButton(QWidget* parent)
    : QPushButton(parent), isHovered(false), pressed(false) {
  setCheckable(Checkable);
  setChecked(Checked);
  setEnabled(Enabled);
}

/// <summary>
/// 重寫繪製事件
/// </summary>
/// <param name="event"></param>
void MyPushButton::paintEvent(QPaintEvent* event) {
  // 文字顏色
  QColor color;
  // 背景顏色
  QBrush backgroundColor;
  // 邊框顏色
  QColor borderColor;

  // Disabled狀態
  if (!isEnabled()) {
    color = QColor("#757575");
    backgroundColor = QColor("#BDBDBD");
    borderColor = QColor("#757575");
    // Checked狀態
  } else if (isChecked()) {
    color = QColor("#1976D2");
    backgroundColor = QColor("#BBDEFB");
    borderColor = QColor("#1976D2");
    // Pressed狀態
  } else if (pressed) {
    color = QColor("#1976D2");

    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0.0, QColor("#DADBDE"));
    gradient.setColorAt(1.0, QColor("#F6F7FA"));
    backgroundColor = QBrush(gradient);

    borderColor = QColor("#1976D2");
    // Hover狀態
  } else if (isHovered) {
    color = QColor("#1976D2");
    backgroundColor = QColor("#E3F2FD");
    borderColor = QColor("#1976D2");
    // 一般狀態
  } else {
    color = QColor("#1976D2");
    backgroundColor = QColor("#00FFFFFF");
    borderColor = QColor("#1976D2");
  }

  // 設定Painter
  QPainter painter(this);
  // 反鋸齒
  painter.setRenderHints(QPainter::Antialiasing, true);
  // 平滑處理
  painter.setRenderHints(QPainter::SmoothPixmapTransform, true);

  // 繪製背景
  painter.setBrush(backgroundColor);
  painter.setPen(QPen(borderColor, 2));
  painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), 10, 10);

  // 繪製文字
  QFont font;
  font.setPointSize(16);
  painter.setPen(color);
  painter.setFont(font);
  painter.drawText(rect(), Qt::AlignCenter, text());
}

/// <summary>
/// 鼠標進入事件
/// </summary>
/// <param name="event"></param>
void MyPushButton::enterEvent(QEvent* event) {
  isHovered = true;
  update();
  QPushButton::enterEvent(event);
}

/// <summary>
/// 鼠標離開事件
/// </summary>
/// <param name="event"></param>
void MyPushButton::leaveEvent(QEvent* event) {
  isHovered = false;
  update();
  QPushButton::leaveEvent(event);
}

/// <summary>
/// 鼠標按下事件
/// </summary>
/// <param name="event"></param>
void MyPushButton::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    pressed = true;
    update();
  }

  QPushButton::mousePressEvent(event);
}

/// <summary>
/// 鼠標釋放事件
/// </summary>
/// <param name="event"></param>
void MyPushButton::mouseReleaseEvent(QMouseEvent* event) {
  if (pressed) {
    pressed = false;
    update();
    emit onClicked();
  }
  QPushButton::mouseReleaseEvent(event);
}
