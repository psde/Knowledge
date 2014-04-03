#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    ui.setupUi(this);

    // Connect slots
    connect(this->ui.dingeButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::buttonClicked()
{
    this->close();
}