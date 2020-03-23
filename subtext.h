#ifndef SUBTEXT_H
#define SUBTEXT_H

#include <QWidget>
#include <QTextEdit>
#include <QString>

class SubText : public QTextEdit
{
    Q_OBJECT
public:
    explicit SubText(QWidget *parent = nullptr);
    explicit SubText(QString path,QWidget *parent = nullptr);
    void SetFilePath(QString path){this->filepath=path;}    //设置文件路径
    void CloseFile(QString filename);   //关闭文件
    void SaveFile();    //保存文件
    void SaveFileAs();  //文件另存为
    void SetSaveFlg(bool flg){this->issave=flg;}
signals:

public slots:

private:
    bool issave;
    QString filepath;
};

#endif // SUBTEXT_H
