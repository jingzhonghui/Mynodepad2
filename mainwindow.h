#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ConnectAll();
protected slots:
    void NewFile();     //新建文件
    void OpenFile();    //打开文件
    void CloseFile();   //关闭文件
    void SaveFile();    //保存文件
    void SaveFileAs();  //文件另存为
    void CloseWindow(); //关闭

private:
    Ui::MainWindow *ui;
    int indexnum;
};

#endif // MAINWINDOW_H
