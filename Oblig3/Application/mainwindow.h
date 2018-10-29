#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include <map>
#include <thread>
#include <mutex>

class QElapsedTimer;

enum Algorithm
{
    SELECTION,
    INSERTION,
    MERGE,
    QUICK,
    STL_SORT,
    BINARY_TREE,
    STL_HEAP,
    BOGO
};

enum Status
{
    NOT_STARTED,
    IN_PROGRESS,
    FINISHED
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateTimeTakenList(std::string s, double d);

    void onThreadExit(Algorithm algorithm);

private slots:
    void on_sortButton_clicked();

    void on_quickCheckBox_stateChanged(int arg1);

    void on_insertionCheckBox_stateChanged(int arg1);

    void on_mergeCheckBox_stateChanged(int arg1);

    void on_stlHeapCheckBox_stateChanged(int arg1);

    void on_stlSortCheckBox_stateChanged(int arg1);

    void on_binaryTreeCheckBox_stateChanged(int arg1);

    void on_selectionCheckBox_stateChanged(int arg1);

    void on_bogoCheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    template <typename T>
    std::vector<T> generateRandomData(int length);

    void sort(Algorithm algorithm);

    void updateLabelStatus(Algorithm algorithm, Status status);

    std::vector<std::vector<int>> data_;

    std::thread t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_;
    std::mutex mutex_;

    int numberOfWorkingThreads_;

    void updateElapsedTime();

    bool selectionEnabled_, insertionEnabled_, mergeEnabled_, bogoEnabled_,
    quickEnabled_, stlSort_Enabled, binarytreeEnabled_, stlHeapEnabled_;

    const std::string STATUS_NOT_STARTED = "Not started";
    const std::string STATUS_IN_PROGRESS = "In progress";
    const std::string STATUS_FINISHED = "Finished";

    QElapsedTimer* elapsedTimer_;
};

#endif // MAINWINDOW_H
