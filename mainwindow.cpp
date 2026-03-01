#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QToolButton>
#include <QMessageBox>

#include <QDir>
#include <QSettings>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect buttons to functions.
    connect(ui->BrowseDecrypt, &QPushButton::clicked, this, &MainWindow::onBrowseDecrypt);
    connect(ui->DecryptButton, &QPushButton::clicked, this, &MainWindow::Decrypt);
    connect(ui->BrowseEncrypt, &QPushButton::clicked,this, &MainWindow::OnBrowseEncrypt);
    connect(ui->EncryptButton, &QPushButton::clicked, this, &MainWindow::Encrypt);
    connect(ui->actionAbout_Qt, &QAction::triggered, this, &MainWindow::AboutQt);
    connect(ui->actionInfo,&QAction::triggered,this,&MainWindow::About);

    WD_CreateNewSave(&loadedData);
}


MainWindow::~MainWindow()
{
    delete ui;
};


void MainWindow::About() {
    QMessageBox about;
    about.setTextFormat(Qt::RichText);
    about.setText("<p><a href=https://github.com/taxicat1/wappysav>WappySav 0.3.2</a><br>By <a href=https://github.com/taxicat1>Mow</a> and <a href=https://github.com/pliplupp>Pliplupp</a>.</p>");
    about.setStandardButtons(QMessageBox::Ok);
    about.setWindowTitle("About WappySav");
    about.setIcon(QMessageBox::Information);
    about.exec();
}


void MainWindow::AboutQt() {
    QMessageBox::information(this, tr("About Qt"), tr("Made with Qt 6.10.2.\nAll rights to Qt belong to the Qt Company."));
}


// Select file to decrypt
void MainWindow::onBrowseDecrypt() {
    // Select file and set textbox to file path
    decryptSelectedFile = QFileDialog::getOpenFileName(this, tr("Open Encrypted Save"), m_currentDir.absolutePath());
    ui->DecryptFile->setText(decryptSelectedFile);
}


// Function for decrypt button
void MainWindow::Decrypt() {
    // Check for selected file
    if (decryptSelectedFile == "") {
        QMessageBox::warning(this, tr("WappySav Error"), tr("Select a file to decrypt."));
        return;
    }

    // Import file with C code in save_proc.c
    switch (WD_ImportSaveFile(&loadedData, decryptSelectedFile.toLocal8Bit())) { // Use result from WD_ImportSaveFile to display a message box
        case SAVE_STATUS_OK: {
            // File was imported OK
            // Prompt for new file to create
            QString output_fname = QFileDialog::getSaveFileName(this, tr("Save Decrypted File"), m_currentDir.absolutePath());
            if (output_fname == "") {
                // User cancelled
                return;
            }

            // Create file
            if (WD_ExportDataFile(output_fname.toLocal8Bit(), &loadedData) != SAVE_STATUS_OK){
                QMessageBox::warning(this, tr("WappySav Error"), tr("Unable to write file ").append(output_fname.toLocal8Bit()));
            } else {
                QMessageBox::information(this, tr("WappySav"), tr("Successfully decrypted file."));
            }
            break;
        }

        case SAVE_STATUS_SIGNATURE_MISMATCH: {
            QMessageBox::warning(this, tr("WappySav Error"), tr("Could not convert save file:\nSignature mismatch (file must begin 47 2D 47 2D)"));
            break;
        }

        case SAVE_STATUS_CHECKSUM_MISMATCH: {
            QMessageBox::warning(this, tr("WappySav Error"), tr("Could not convert save file:\nChecksum mismatch (file is considered corrupt)"));
            break;
        }

        default:
        case SAVE_STATUS_FILE_FAILURE: {
            QMessageBox::warning(this, tr("WappySav Error"), tr("Could not convert save file:\nUnable to read ").append(decryptSelectedFile.toLocal8Bit()));
            break;
        }
    }
}


void MainWindow::OnBrowseEncrypt() {
    // Select file for reading and set textbox.
    encryptSelectedFile = QFileDialog::getOpenFileName(this, tr("Open Decrypted Save"), m_currentDir.absolutePath());
    ui->EncryptFile->setText(encryptSelectedFile);
}


void MainWindow::Encrypt() {
    // Check for selected file
    if (encryptSelectedFile == "") {
        QMessageBox::warning(this, tr("WappySav Error"), tr("Select a file to encrypt."));
        return;
    }

    // Import file with C code in save_proc.c
    switch (WD_ImportDataFile(&loadedData, encryptSelectedFile.toLocal8Bit())) { // Use result from WD_ImportDataFile to display a message box
        case SAVE_STATUS_OK: {
            // Data file was read OK
            // Prompt for new file to create
            QString output_fname = QFileDialog::getSaveFileName(this, tr("Save Encrypted File"), m_currentDir.absolutePath());
            if (output_fname == "") {
                // User cancelled
                return;
            }

            // Create file
            if (WD_ExportSaveFile(output_fname.toLocal8Bit(), &loadedData) != SAVE_STATUS_OK) {
                QMessageBox::warning(this, tr("WappySav Error"), tr("Unable to write file ").append(output_fname.toLocal8Bit()));
            } else {
                // Export file and show infobox if save status is good
                QMessageBox::information(this, tr("WappySav"), tr("Successfully encrypted file.") );
            }
            break;
        }

        default:
        case SAVE_STATUS_FILE_FAILURE: {
            QMessageBox::warning(this, tr("WappySav Error"), tr("Could not import data file:\nUnable to read ").append(encryptSelectedFile.toLocal8Bit()));
            break;
        }
    }
}
