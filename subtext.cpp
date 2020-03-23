#include "subtext.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

SubText::SubText(QWidget *parent) : QTextEdit(parent)
{
    this->issave=true;
}
SubText::SubText(QString path,QWidget *parent) : QTextEdit(parent)
{
    this->issave=true;
    this->filepath=path;
}

//关闭文件
void SubText::CloseFile(QString filename)
{
    if(!this->issave)   //文件未保存
    {
       QMessageBox::StandardButton button= QMessageBox::information(this,"保存","保存文件 "+filename+"?",
                                 QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
       if  (button==QMessageBox::Yes)
       {
           SaveFile();
       }
    }
    this->close();
}

//保存文件
void SubText::SaveFile()
{
    bool saveflag=false;
    if(filepath.isEmpty())
    {
        filepath=QFileDialog::getSaveFileName(this,"保存文件","./new.txt","Text (*.txt)");
        QFile file(filepath);
        if(file.open(QIODevice::Text | QIODevice::WriteOnly))
        {
            file.write(this->toPlainText().toUtf8());
            file.close();
            saveflag=true;
            this->issave=true;  //保存成功记录
        }
    }
    else
    {
        QFile file(filepath);
        if(file.open(QIODevice::Text | QIODevice::WriteOnly))
        {
            file.write(this->toPlainText().toUtf8());
            file.close();
            saveflag=true;
            this->issave=true;
        }
    }
    if(!saveflag)
    {
         QMessageBox::information(this,"提示","文件保存失败，可能是文件路径获取失败!");
    }
}

//文件另存为
void SubText::SaveFileAs()
{
    QString path=QFileDialog::getSaveFileName(this,"文件另存为","new.txt","Text (*.txt)");
    QFile file(path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write(this->toPlainText().toUtf8());
        file.close();
        this->issave=true;
    }
    else
    {
        QMessageBox::information(this,"提示","文件保存失败，可能是文件路径获取失败!");
    }
}





