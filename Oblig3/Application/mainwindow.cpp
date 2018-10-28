#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sortbase.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    selection_{false}, insertion_{false}, merge_{false},
    quick_{false}, stl_{false}, binarytree_{false}, heap_{false}
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Hello");
}

MainWindow::~MainWindow()
{ 
    delete ui;
}

void MainWindow::updateTimeTakenList(std::string s, double d)
{
    QStringList list;

    list.push_back(QString::fromStdString(s) + QString().setNum(d, 'g', 6) + " seconds");

    ui->timeTakenList->addItems(list);
}

void MainWindow::onThreadExit(std::thread::id id, Algorithm algorithm)
{
    std::lock_guard<std::mutex> lk(mutex_);
    updateLabelStatus(algorithm, FINISHED);
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
    if(data_.size())
    {
        for(auto& d : data_)
        {
            delete d;
            d = nullptr;
        }
        data_.clear();

        ui->timeTakenList->clear();
    }

    data_ = generateRandomData<int>(ui->sizeSpinBox->value());

    if(stl_)
    {
        updateLabelStatus(STL, IN_PROGRESS);
        t1_ = std::thread(&MainWindow::sort, this, STL);
        t1_.detach();
    }
    else
    {
        updateLabelStatus(STL, NOT_STARTED);
    }

    if(quick_)
    {
        updateLabelStatus(QUICK, IN_PROGRESS);
        t2_ = std::thread(&MainWindow::sort, this, QUICK);
        t2_.detach();
    }
    else
    {
        updateLabelStatus(QUICK, NOT_STARTED);
    }

    if(selection_)
    {
        updateLabelStatus(SELECTION, IN_PROGRESS);
        t3_ = std::thread(&MainWindow::sort, this, SELECTION);
        t3_.detach();
    }
    else
    {
        updateLabelStatus(SELECTION, NOT_STARTED);
    }

    if(insertion_)
    {
        updateLabelStatus(INSERTION, IN_PROGRESS);
        t4_ = std::thread(&MainWindow::sort, this, INSERTION);
        t4_.detach();
    }
    else
    {
        updateLabelStatus(INSERTION, NOT_STARTED);
    }

    if(merge_)
    {
        updateLabelStatus(MERGE, IN_PROGRESS);
        t5_ = std::thread(&MainWindow::sort, this, MERGE);
        t5_.detach();
    }
    else
    {
        updateLabelStatus(MERGE, NOT_STARTED);
    }

    if(binarytree_)
    {
        updateLabelStatus(BINARY_TREE, IN_PROGRESS);
        t6_ = std::thread(&MainWindow::sort, this, BINARY_TREE);
        t6_.detach();
    }
    else
    {
        updateLabelStatus(BINARY_TREE, NOT_STARTED);
    }

    if(heap_)
    {
        updateLabelStatus(HEAP, IN_PROGRESS);
        t7_ = std::thread(&MainWindow::sort, this, HEAP);
        t7_.detach();
    }
    else
    {
        updateLabelStatus(HEAP, NOT_STARTED);
    }
}

void MainWindow::on_quickCheckBox_stateChanged(int arg1)
{
    quick_ = arg1;
}

void MainWindow::on_insertionCheckBox_stateChanged(int arg1)
{
    insertion_ = arg1;
}

void MainWindow::on_mergeCheckBox_stateChanged(int arg1)
{
    merge_ = arg1;
}

void MainWindow::on_heapCheckBox_stateChanged(int arg1)
{
    heap_ = arg1;
}

void MainWindow::on_stlCheckBox_stateChanged(int arg1)
{
    stl_ = arg1;
}

void MainWindow::on_binaryTreeCheckBox_stateChanged(int arg1)
{
    binarytree_ = arg1;
}

void MainWindow::on_selectionCheckBox_stateChanged(int arg1)
{
    selection_ = arg1;
}

void MainWindow::sort(Algorithm algorithm)
{
    SortBase sb(this);
    sb.Sort(data_, algorithm);
}

void MainWindow::updateLabelStatus(Algorithm algorithm, Status status)
{

    std::string statusText;

    switch (status) {
    case NOT_STARTED:
        statusText = STATUS_NOTSTARTED;
        break;
    case IN_PROGRESS:
        statusText = STATUS_PROGRESS;
        break;
    case FINISHED:
        statusText = STATUS_FINISHED;
        break;
    default:
        break;
    }

    switch (algorithm) {
    case SELECTION:
        ui->plabel_Selection->setText("Selection Sort: " + QString::fromStdString(statusText));
        break;
    case INSERTION:
        ui->plabel_Insertion->setText("Insertion Sort: " + QString::fromStdString(statusText));
        break;
    case MERGE:
        ui->plabel_Merge->setText("Merge Sort: " + QString::fromStdString(statusText));
        break;
    case QUICK:
        ui->plabel_Quick->setText("Quick Sort: " + QString::fromStdString(statusText));
        break;
    case STL:
        ui->plabel_stdSort->setText("std::Sort: " + QString::fromStdString(statusText));
        break;
    case BINARY_TREE:
        ui->plabel_BT->setText("Binary Tree: " + QString::fromStdString(statusText));
        break;
    case HEAP:
        ui->plabel_Heap->setText("Heap Sort: " + QString::fromStdString(statusText));
        break;
    default:
        break;
    }


}
