#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include "sort.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sortButton_clicked()
{
    std::vector<int> data = {8, 3, 2, 7, 6, 1, 9, 5, 4};

    Sort sort;

    sort.Merge(data);
}
