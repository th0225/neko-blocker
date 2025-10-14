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
/// ���gø�s�ƥ�
/// </summary>
/// <param name="event"></param>
void MyPushButton::paintEvent(QPaintEvent* event) {
  // ��r�C��
  QColor color;
  // �I���C��
  QBrush backgroundColor;
  // ����C��
  QColor borderColor;

  // Disabled���A
  if (!isEnabled()) {
    color = QColor("#757575");
    backgroundColor = QColor("#BDBDBD");
    borderColor = QColor("#757575");
    // Checked���A
  } else if (isChecked()) {
    color = QColor("#1976D2");
    backgroundColor = QColor("#BBDEFB");
    borderColor = QColor("#1976D2");
    // Pressed���A
  } else if (pressed) {
    color = QColor("#1976D2");

    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0.0, QColor("#DADBDE"));
    gradient.setColorAt(1.0, QColor("#F6F7FA"));
    backgroundColor = QBrush(gradient);

    borderColor = QColor("#1976D2");
    // Hover���A
  } else if (isHovered) {
    color = QColor("#1976D2");
    backgroundColor = QColor("#E3F2FD");
    borderColor = QColor("#1976D2");
    // �@�몬�A
  } else {
    color = QColor("#1976D2");
    backgroundColor = QColor("#00FFFFFF");
    borderColor = QColor("#1976D2");
  }

  // �]�wPainter
  QPainter painter(this);
  // �Ͽ���
  painter.setRenderHints(QPainter::Antialiasing, true);
  // ���ƳB�z
  painter.setRenderHints(QPainter::SmoothPixmapTransform, true);

  // ø�s�I��
  painter.setBrush(backgroundColor);
  painter.setPen(QPen(borderColor, 2));
  painter.drawRoundedRect(rect().adjusted(1, 1, -1, -1), 10, 10);

  // ø�s��r
  QFont font;
  font.setPointSize(16);
  painter.setPen(color);
  painter.setFont(font);
  painter.drawText(rect(), Qt::AlignCenter, text());
}

/// <summary>
/// ���жi�J�ƥ�
/// </summary>
/// <param name="event"></param>
void MyPushButton::enterEvent(QEvent* event) {
  isHovered = true;
  update();
  QPushButton::enterEvent(event);
}

/// <summary>
/// �������}�ƥ�
/// </summary>
/// <param name="event"></param>
void MyPushButton::leaveEvent(QEvent* event) {
  isHovered = false;
  update();
  QPushButton::leaveEvent(event);
}

/// <summary>
/// ���Ы��U�ƥ�
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
/// ��������ƥ�
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
