#pragma once

#include <QMainWindow>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui_MainWindow ui;

private slots:
    void buttonClicked();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};
