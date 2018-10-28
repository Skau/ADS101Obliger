#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <conio.h>
#include <ctime>
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

void MainWindow::updateTimeTakenList(std::vector<std::pair<double, std::string> > times)
{
    ui->timeTakenList->clear();

    QStringList list;

    for(auto itr = times.begin(); itr != times.end(); ++itr)
    {
        list.push_back(QString::fromStdString(itr->second) + QString().setNum(itr->first, 'g', 6));
    }

    ui->timeTakenList->addItems(list);
}

template<typename T>
std::vector<T> MainWindow::generateRandomData(int length)
{
    std::vector<T> randomData;
    randomData.reserve(length);

    for(int i = 0; i < length; ++i)
    {
        randomData.push_back(rand() % 100 + 1);
    }

    return randomData;
}

void MainWindow::on_sortButton_clicked()
{
    auto data = generateRandomData<int>(ui->sizeSpinBox->value());
    qDebug() << data.size();
    std::vector<std::pair<double, std::string>> times;

    ui->timeTakenList->clear();

    if(quick)
    {
        SortBase sb;
        clock_t startTime = clock();
        sb.Sort(data, QUICK);
        clock_t endTime = clock();
        double duration = ( endTime - startTime ) / (double) CLOCKS_PER_SEC;
        times.emplace_back(std::make_pair(duration, "Quick Sort: "));
    }

    if(selection)
    {
        SortBase sb;
        clock_t startTime = clock();
        sb.Sort(data, SELECTION);
        clock_t endTime = clock();
        double duration = ( endTime - startTime ) / (double) CLOCKS_PER_SEC;
        times.emplace_back(std::make_pair(duration, "Selection Sort: "));
    }

    if(insertion)
    {
        SortBase sb;
        clock_t startTime = clock();
        sb.Sort(data, INSERTION);
        clock_t endTime = clock();
        double duration = ( endTime - startTime ) / (double) CLOCKS_PER_SEC;
        times.emplace_back(std::make_pair(duration, "Insertion Sort: "));
    }

    if(merge)
    {
        SortBase sb;
        clock_t startTime = clock();
        sb.Sort(data, MERGE);
        clock_t endTime = clock();
        double duration = ( endTime - startTime ) / (double) CLOCKS_PER_SEC;
        times.emplace_back(std::make_pair(duration, "Merge Sort: "));
    }

    if(stl)
    {
        SortBase sb;
        clock_t startTime = clock();
        sb.Sort(data, STL);
        clock_t endTime = clock();
        double duration = ( endTime - startTime ) / (double) CLOCKS_PER_SEC;
        times.emplace_back(std::make_pair(duration, "std::Sort: "));
    }

//    if(binarytree)
//    {
//        SortBase sb;
//        clock_t startTime = clock();
//        sb.Sort(data, BINARY_TREE);
//        clock_t endTime = clock();
//        double duration = ( endTime - startTime ) / (double) CLOCKS_PER_SEC;
//        times.emplace_back(std::make_pair(duration, "Binary Search Tree Sort: "));
//    }

//    if(heap)
//    {
//        SortBase sb;
//        clock_t startTime = clock();
//        sb.Sort(data, HEAP);
//        clock_t endTime = clock();
//        double duration = ( endTime - startTime ) / (double) CLOCKS_PER_SEC;
//        times.emplace_back(std::make_pair(duration, "Heap Sort: "));
//    }

    std::sort(times.begin(), times.end());
    updateTimeTakenList(times);
}

void MainWindow::on_quickCheckBox_stateChanged(int arg1)
{
    quick = arg1;
}

void MainWindow::on_insertionCheckBox_stateChanged(int arg1)
{
    insertion = arg1;
}

void MainWindow::on_mergeCheckBox_stateChanged(int arg1)
{
    merge = arg1;
}

void MainWindow::on_heapCheckBox_stateChanged(int arg1)
{
    heap = arg1;
}

void MainWindow::on_stlCheckBox_stateChanged(int arg1)
{
    stl = arg1;
}

void MainWindow::on_binaryTreeCheckBox_stateChanged(int arg1)
{
    binarytree = arg1;
}

void MainWindow::on_selectionCheckBox_stateChanged(int arg1)
{
    selection = arg1;
}
