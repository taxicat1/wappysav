#include "mainwindow.h"
#include "./ui_mainwindow.h"


#include <QFileDialog>
#include <QToolButton>
#include <QMessageBox>

#include <QDir>
#include <QSettings>

extern "C"{
#include "save_proc.c"
#include "nitro_types.h" // Doesn't actually need to be included, but if more functions are added, it might be useful.
#include "save_proc.h"
}

void* encoded_data_buf = malloc(SAVE_ENCODED_SIZE);
void* decoded_data_buf = malloc(SAVE_DECODED_SIZE);

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
}

MainWindow::~MainWindow()
{
    delete ui;
};


void MainWindow::About(){
    QMessageBox about;
    about.setTextFormat(Qt::RichText);   //this is what makes the links clickable
    about.setText("<p><a href=https://github.com/taxicat1/wappysav>WappySav 0.2.0.</a><br>By <a href=https://github.com/taxicat1>Mow</a> and <a href=https://github.com/pliplupp>Pliplupp</a>.</p>");
    about.setStandardButtons(QMessageBox::Ok);
    about.setWindowTitle("About WappySav");
    about.setIcon(QMessageBox::Information);
    about.exec();
}

void MainWindow::AboutQt(){
    QMessageBox::information(this,tr("About Qt"),tr("Made with Qt 6.10.2.\nAll rights to Qt belong to the Qt Company."));
}


// Select file to decrypt
void MainWindow::onBrowseDecrypt(){
    // Select file and set textbox to file path
    filename =  QFileDialog::getOpenFileName(this, tr("Open Encrypted Save"), m_currentDir.absolutePath());
    ui->DecryptFile->setText(filename);
};

// Function for decrypt button
void MainWindow::Decrypt(){
    // Get name and location for output file
    QString output_fname = QFileDialog::getSaveFileName(this, tr("Save Decrypted File"), m_currentDir.absolutePath());
    // Get actual file from filename stored earlier
    QFile *decryptfile = new QFile(filename);

    // Convert QFile to FILE
    decryptfile->open(QIODevice::ReadOnly);
    int fileHandle = decryptfile->handle();
    FILE* inputdecrypt = fdopen(fileHandle, "rb");

    // Import file with Mow's original C code in save_proc.c
    WD_ImportSaveFile(encoded_data_buf, inputdecrypt);
    decryptfile->close();
    fclose(inputdecrypt);

    int decode_result = WD_DecodeSaveData(decoded_data_buf, encoded_data_buf);
    switch (decode_result) { // Use result from WD_DecodeSaveData to display a message box
    case SAVE_STATUS_OK: {
        // Create file
        QByteArray outtemp = output_fname.toLocal8Bit();
        char* finaloutput = outtemp.data();
        FILE* decryptout = fopen(finaloutput, "wb");
        if (decryptout == NULL) {
            QMessageBox::critical(this,tr("WappySav Error"),tr("Could not write."));
        }
        else {

        WD_ExportDataFile(decryptout, decoded_data_buf);

        fclose(decryptout);

        QMessageBox::information(this,tr("WappySav"),tr("Conversion successful"));
        break;
        };
    }

    case SAVE_STATUS_SIGNATURE_MISMATCH: {
        QMessageBox::warning(this,tr("WappySav Error"),tr("Signature mismatch (file must begin 47 2D 47 2D)"));
        break;
    }

    case SAVE_STATUS_CHECKSUM_MISMATCH: {
        QMessageBox::warning(this,tr("WappySav Error"),tr("Checksum mismatch (file is considered corrupt)"));
        break;
    }
    };
}

void MainWindow::OnBrowseEncrypt(){
    // Select file for reading and set textbox.
    filenameopen =  QFileDialog::getOpenFileName(this, tr("Open Decrypted Save"), m_currentDir.absolutePath());
    ui->EncryptFile->setText(filenameopen);
};

void MainWindow::Encrypt(){
    // Get name and location of file for exporting
    QString output_fname = QFileDialog::getSaveFileName(this, tr("Save Encrypted File"), m_currentDir.absolutePath());
    // Get an actual file from the path to the one selected earlier
    QFile *encryptfile = new QFile(filenameopen);
    // Convert QFile to FILE
    encryptfile->open(QIODevice::ReadOnly);
    int fileHandle2 = encryptfile->handle();
    FILE* inencrypt = fdopen(fileHandle2, "rb");

    // Run functions from Mow's C code.
    WD_ImportDataFile(decoded_data_buf, inencrypt);
    fclose(inencrypt);
    encryptfile->close();

    // Store result of save reading in result
    int result = WD_EncodeSaveData(encoded_data_buf, decoded_data_buf);

    // Create FILE from the QString stored earlier
    QByteArray outtemp2 = output_fname.toLocal8Bit();
    char* finaloutput2 = outtemp2.data();
    FILE* output_file2 = fopen(finaloutput2, "wb");

    // Show popup if file returns NULL
    if (output_file2 == NULL) {
        QMessageBox::critical(this,tr("WappySav Error"),tr("Could not write file."));
    }
    // Export file and show infobox if save status is good
    else if (result == SAVE_STATUS_OK){
        WD_ExportSaveFile(output_file2, encoded_data_buf);
        fclose(output_file2);
        QMessageBox::information(this, tr("WappySav"), tr("Successfully encrypted file.") );
    }

};
