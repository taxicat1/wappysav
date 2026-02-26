#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QToolButton>
#include <QMessageBox>

#include <QDir>
#include <QSettings>

extern "C" {
#include "save_proc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QString encryptSelectedFile;
    QString decryptSelectedFile;
    WDSave loadedData;
    QDir m_currentDir;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void onBrowseDecrypt();
    void Decrypt();
    void OnBrowseEncrypt();
    void Encrypt();
    void About();
    void AboutQt();

    ;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
