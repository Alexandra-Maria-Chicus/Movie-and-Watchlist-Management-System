#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_A10.h"

class A10 : public QMainWindow
{
    Q_OBJECT

public:
    A10(QWidget* parent = nullptr);
    ~A10();

private:
    Ui::A10Class ui;
};
