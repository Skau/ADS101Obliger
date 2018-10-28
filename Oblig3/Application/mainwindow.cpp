#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include "sortbase.h"
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

void MainWindow::on_mergeSortButton_clicked()
{
    SortBase sort;

    auto data = sort.generateRandomData<int>(20);

    sort.Sort(data, Quick);

    for(auto& a : data)
        qDebug() << a << " ";
}
