#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_neko_blocker.h"

class NekoBlocker : public QMainWindow
{
    Q_OBJECT

public:
    NekoBlocker(QWidget *parent = nullptr);
    ~NekoBlocker();

private:
    Ui::NekoBlockerClass ui;
};

