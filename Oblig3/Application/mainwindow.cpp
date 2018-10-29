#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sortbase.h"
#include <QtDebug>
#include <QDialog>
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    selectionEnabled_{false}, insertionEnabled_{false}, mergeEnabled_{false}, bogoEnabled_{false},
    quickEnabled_{false}, stlSort_Enabled{false}, binarytreeEnabled_{false}, stlHeapEnabled_{false},
    numberOfWorkingThreads_{0}
{
    srand(time(NULL));
    ui->setupUi(this);

    // Remove bottom right corner grip, because resizing is disabled (min / max window size are equal)
    ui->statusBar->setSizeGripEnabled(false);

    elapsedTimer_ = new QElapsedTimer();
}

MainWindow::~MainWindow()
{ 
    delete ui;
}

void MainWindow::updateTimeTakenList(std::string s, double d)
{
    std::lock_guard<std::mutex> lock(mutex_);

    ui->timeTakenList->addItem(QString::fromStdString(s) + QString().setNum(d, 'g', 6) + " seconds");
}

void MainWindow::onThreadExit(Algorithm algorithm)
{
    std::lock_guard<std::mutex> lock(mutex_);

    updateLabelStatus(algorithm, FINISHED);
    numberOfWorkingThreads_--;
}

template<typename T>
std::vector<T> MainWindow::generateRandomData(int length)
{
    std::vector<T> randomData;
    randomData.reserve(length);

    for(int i = 0; i < length; ++i)
    {
        randomData.push_back(T(rand() % 100 + 1));
    }

    return randomData;
}

void MainWindow::on_sortButton_clicked()
{
    if(data_.size())
    {
        for(auto& data : data_)
        {
            data.clear();
        }
        data_.clear();

        ui->timeTakenList->clear();
    }

    data_.reserve(ui->numOfDataSetSpinBox->value());
    for(int i = 0; i < ui->numOfDataSetSpinBox->value(); ++i)
    {
        data_.push_back(generateRandomData<int>(ui->sizeOfDataSetSpinBox->value()));
    }

    if(stlSort_Enabled)
    {
        updateLabelStatus(STL_SORT, IN_PROGRESS);
        t1_ = std::thread(&MainWindow::sort, this, STL_SORT);
        t1_.detach();
        numberOfWorkingThreads_++;
    }
    else
    {
        updateLabelStatus(STL_SORT, NOT_STARTED);
    }

    if(quickEnabled_)
    {
        updateLabelStatus(QUICK, IN_PROGRESS);
        t2_ = std::thread(&MainWindow::sort, this, QUICK);
        t2_.detach();
        numberOfWorkingThreads_++;
    }
    else
    {
        updateLabelStatus(QUICK, NOT_STARTED);
    }

    if(insertionEnabled_)
    {
        updateLabelStatus(INSERTION, IN_PROGRESS);
        t3_ = std::thread(&MainWindow::sort, this, INSERTION);
        t3_.detach();
        numberOfWorkingThreads_++;
    }
    else
    {
        updateLabelStatus(INSERTION, NOT_STARTED);
    }

    if(selectionEnabled_)
    {
        updateLabelStatus(SELECTION, IN_PROGRESS);
        t4_ = std::thread(&MainWindow::sort, this, SELECTION);
        t4_.detach();
        numberOfWorkingThreads_++;
    }
    else
    {
        updateLabelStatus(SELECTION, NOT_STARTED);
    }

    if(mergeEnabled_)
    {
        updateLabelStatus(MERGE, IN_PROGRESS);
        t5_ = std::thread(&MainWindow::sort, this, MERGE);
        t5_.detach();
        numberOfWorkingThreads_++;
    }
    else
    {
        updateLabelStatus(MERGE, NOT_STARTED);
    }

    if(binarytreeEnabled_)
    {
        updateLabelStatus(BINARY_TREE, IN_PROGRESS);
        t6_ = std::thread(&MainWindow::sort, this, BINARY_TREE);
        t6_.detach();
        numberOfWorkingThreads_++;
    }
    else
    {
        updateLabelStatus(BINARY_TREE, NOT_STARTED);
    }

    if(stlHeapEnabled_)
    {
        updateLabelStatus(STL_HEAP, IN_PROGRESS);
        t7_ = std::thread(&MainWindow::sort, this, STL_HEAP);
        t7_.detach();
        numberOfWorkingThreads_++;
    }
    else
    {
        updateLabelStatus(STL_HEAP, NOT_STARTED);
    }

    if(bogoEnabled_)
    {
        updateLabelStatus(BOGO, IN_PROGRESS);
        t8_ = std::thread(&MainWindow::sort, this, BOGO);
        t8_.detach();
        numberOfWorkingThreads_++;
    }
    else
    {
        updateLabelStatus(BOGO, NOT_STARTED);
    }

    elapsedTimer_->start();
    t9_ = std::thread(&MainWindow::updateElapsedTime, this);
}

void MainWindow::updateLabelStatus(Algorithm algorithm, Status status)
{

    std::string statusText;
    switch (status) {
    case NOT_STARTED:
        statusText = STATUS_NOT_STARTED;
        break;
    case IN_PROGRESS:
        statusText = STATUS_IN_PROGRESS;
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
    case STL_SORT:
        ui->plabel_stdSort->setText("std::Sort: " + QString::fromStdString(statusText));
        break;
    case BINARY_TREE:
        ui->plabel_BT->setText("Binary Tree: " + QString::fromStdString(statusText));
        break;
    case STL_HEAP:
        ui->plabel_Heap->setText("Heap Sort: " + QString::fromStdString(statusText));
        break;
    case BOGO:
        ui->plabel_Bogo->setText("Bogo Sort: " + QString::fromStdString(statusText));
        break;
    default:
        break;
    }
}

void MainWindow::updateElapsedTime()
{
    while(numberOfWorkingThreads_ > 0)
    {
        auto time = elapsedTimer_->elapsed();
        ui->label_TimeElapsed->setText("Elapsed time: " + QString::number(time/1000) + " seconds");
    }

    t9_.detach();
}

void MainWindow::on_quickCheckBox_stateChanged(int arg1)
{
    quickEnabled_ = arg1;
}

void MainWindow::on_insertionCheckBox_stateChanged(int arg1)
{
    insertionEnabled_ = arg1;
}

void MainWindow::on_mergeCheckBox_stateChanged(int arg1)
{
    mergeEnabled_ = arg1;
}

void MainWindow::on_stlHeapCheckBox_stateChanged(int arg1)
{
    stlHeapEnabled_ = arg1;
}

void MainWindow::on_stlSortCheckBox_stateChanged(int arg1)
{
    stlSort_Enabled = arg1;
}

void MainWindow::on_binaryTreeCheckBox_stateChanged(int arg1)
{
    binarytreeEnabled_ = arg1;
}

void MainWindow::on_selectionCheckBox_stateChanged(int arg1)
{
    selectionEnabled_ = arg1;
}

void MainWindow::on_bogoCheckBox_stateChanged(int arg1)
{
    bogoEnabled_ = arg1;
}

void MainWindow::sort(Algorithm algorithm)
{
    SortBase sb(this);
    sb.Sort(data_, algorithm);
}


