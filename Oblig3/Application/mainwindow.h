#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include <map>
#include <thread>
#include <mutex>

enum Algorithm
{
    SELECTION,
    INSERTION,
    MERGE,
    QUICK,
    STL,
    BINARY_TREE,
    HEAP
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

    void onThreadExit(std::thread::id id, Algorithm algorithm);

private slots:
    void on_sortButton_clicked();

    void on_quickCheckBox_stateChanged(int arg1);

    void on_insertionCheckBox_stateChanged(int arg1);

    void on_mergeCheckBox_stateChanged(int arg1);

    void on_heapCheckBox_stateChanged(int arg1);

    void on_stlCheckBox_stateChanged(int arg1);

    void on_binaryTreeCheckBox_stateChanged(int arg1);

    void on_selectionCheckBox_stateChanged(int arg1);


private:
    Ui::MainWindow *ui;

    template <typename T>
    std::vector<T*> generateRandomData(int length);

    void sort(Algorithm algorithm);

    void updateLabelStatus(Algorithm algorithm, Status status);

    std::vector<int*> data_;

    std::thread t1_, t2_, t3_, t4_, t5_, t6_, t7_;

    std::mutex mutex_;

    bool selection_, insertion_, merge_, quick_, stl_, binarytree_, heap_;

    const std::string STATUS_NOTSTARTED = "not started";
    const std::string STATUS_PROGRESS = "in progress";
    const std::string STATUS_FINISHED = "finished";
};

#endif // MAINWINDOW_H
