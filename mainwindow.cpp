#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include "subtext.h"
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    indexnum=1;
    ConnectAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConnectAll()

{
    connect(ui->action_N,&QAction::triggered,this,&MainWindow::NewFile);
    connect(ui->action_O,&QAction::triggered,this,&MainWindow::OpenFile);
    connect(ui->action_C,&QAction::triggered,this,&MainWindow::CloseFile);
    connect(ui->action_S,&QAction::triggered,this,&MainWindow::SaveFile);
    connect(ui->action_A,&QAction::triggered,this,&MainWindow::SaveFileAs);
    connect(ui->action_E,&QAction::triggered,this,&MainWindow::CloseWindow);
    //////////////////////////////////////////////////////////////////////////
}

//新建文件
void MainWindow::NewFile()
{
   SubText *subtext=new SubText;
   QString tabname="new_"+QString::number(indexnum++);
   ui->tabWidget->addTab(subtext,tabname);
   ui->tabWidget->setCurrentWidget(subtext);
   connect(subtext,&SubText::textChanged,[=] {subtext->SetSaveFlg(false);});
}
//打开文件
void MainWindow::OpenFile()
{
    QString path=QFileDialog::getOpenFileName(this,"打开文件",".","Text (*.txt)");
    if(path.isEmpty())  //获取路径失败直接退出
    {
        return;
    }
    QFile file(path);
    //获取文件名
    QFileInfo fileinfo(file);
    QString filename=fileinfo.fileName();

    bool isread=false;  //是否成功读取到内容
    QWidget *widget=ui->tabWidget->currentWidget();
    //在已经打开的界面内打开文件
    if(widget)
    {
        SubText *subtext=qobject_cast<SubText *>(widget);
        subtext->SetFilePath(path);
        if(file.open(QIODevice::Text | QIODevice::ReadOnly))
        {

            subtext->setText(file.readAll());
            file.close();
            isread=true;
            connect(subtext,&SubText::textChanged,[=] {subtext->SetSaveFlg(false);});
        }
    }
    else
    {   //在新窗口中打开文件
        SubText *subtext=new SubText(path);
        QString tabname="new_"+QString::number(indexnum++);
        ui->tabWidget->addTab(subtext,tabname);
        ui->tabWidget->setCurrentWidget(subtext);
        if(file.open(QIODevice::Text | QIODevice::ReadOnly))
        {
            subtext->setText(file.readAll());
            file.close();
            isread=true;
            connect(subtext,&SubText::textChanged,[=] {subtext->SetSaveFlg(false);});
        }
    }
    //将文件名设置成标签页名称
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),filename);
    if(!isread)
    {
        QMessageBox::information(this,"提示","文件保存失败，可能是文件路径获取失败!");
    }
}


//关闭文件
void MainWindow::CloseFile()
{
    SubText *subtext=qobject_cast<SubText *>(ui->tabWidget->currentWidget());
    if(subtext)
    {
        int currindex=ui->tabWidget->currentIndex();
        subtext->CloseFile(ui->tabWidget->tabText(currindex));
        ui->tabWidget->removeTab(currindex);
    }
}

//保存文件
void MainWindow::SaveFile()
{
    SubText *subtext=qobject_cast<SubText *>(ui->tabWidget->currentWidget());
    subtext->SaveFile();
}

//文件另存为
void MainWindow::SaveFileAs()
{
    SubText *subtext=qobject_cast<SubText *>(ui->tabWidget->currentWidget());
    subtext->SaveFileAs();
}


void MainWindow::CloseWindow()
{
    this->close();
}


