#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openGLWidget = ui->openGLWidget;
	connect(ui->colorPickerButton, &QPushButton::clicked, this, &MainWindow::onColorPickerButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onColorPickerButtonClicked()
{
    // Open QColorDialog to select the color
    QColorDialog colorDialog(this);
    if (colorDialog.exec() == QColorDialog::Accepted) {
        QColor color = colorDialog.currentColor();
        openGLWidget->changeTriangleColor(color);
    }
}



