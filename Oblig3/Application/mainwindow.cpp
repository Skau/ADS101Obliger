#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include "sortbase.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    selection{false}, insertion{false}, merge{false},
    quick{false}, stl{false}, binarytree{false}, heap{false}
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{ 
    delete ui;
}

void MainWindow::updateTimeTakenList(std::vector<std::pair<double, std::string>> times)
{
    ui->timeTakenList->clear();

    QStringList list;

    for(auto itr = times.begin(); itr != times.end(); ++itr)
    {
        list.push_back(QString::fromStdString(itr->second) + QString().setNum(itr->first, 'g', 6) + " seconds");
    }

    ui->timeTakenList->addItems(list);
}

template<typename T>
std::vector<T*> MainWindow::generateRandomData(int length)
{
    std::vector<T*> randomData;
    randomData.reserve(length);

    for(int i = 0; i < length; ++i)
    {
        randomData.push_back(new T(rand() % 100 + 1));
    }

    return randomData;
}

void MainWindow::on_sortButton_clicked()
{
    SortBase sb;
    auto data = generateRandomData<int>(ui->sizeSpinBox->value());
    std::vector<std::pair<double, std::string>> times;
    double duration = 0.0f;

    if(stl)
    {
        duration = sb.Sort(data, STL);
        times.emplace_back(std::make_pair(duration, "std::Sort: "));
    }

    if(quick)
    {
        duration = sb.Sort(data, QUICK);
        times.emplace_back(std::make_pair(duration, "Quick Sort: "));
    }

    if(selection)
    {
        duration = sb.Sort(data, SELECTION);
        times.emplace_back(std::make_pair(duration, "Selection Sort: "));
    }

    if(insertion)
    {
        duration = sb.Sort(data, INSERTION);
        times.emplace_back(std::make_pair(duration, "Insertion Sort: "));
    }

    if(merge)
    {
        duration = sb.Sort(data, MERGE);
        times.emplace_back(std::make_pair(duration, "Merge Sort: "));
    }

    if(binarytree)
    {
        duration = sb.Sort(data, BINARY_TREE);
        times.emplace_back(std::make_pair(duration, "Binary Search Tree Sort: "));
    }

    if(heap)
    {
        duration = sb.Sort(data, HEAP);
        times.emplace_back(std::make_pair(duration, "(STL)Heap Sort: "));
    }

    std::sort(times.begin(), times.end());
    updateTimeTakenList(times);

    for(auto& d : data)
    {
        delete d;
        d = nullptr;
    }
    data.clear();
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
