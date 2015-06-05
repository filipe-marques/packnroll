/*
 *  This file is part of Pack n' Roll project
 *	name of file: PRMainWindow.cpp
 *
 *	Copyright (C) 2015 Filipe Marques <eagle.software3@gmail.com>
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 3 of the License, or
 *	any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You received a copy of the GNU General Public License
 *	along with this program in License folder; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *	MA 02110-1301, USA.
*/

#include "inc/PRMainWindow.hpp"
#include "ui_prmainwindow.h"

PRMainWindow::PRMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::PRMainWindow)
{
    ui->setupUi(this);
    pro = new QProcess(this);
    setWindowState(Qt::WindowMaximized);
    setWindowTitle("Pack n' Roll");
    setCentralWidget(ui->tabWidget);

    // readyRead() update itself automatically - a kind of recursion
    connect(pro, SIGNAL(readyRead()), this, SLOT(readyRead()));

    //connect(pro, SIGNAL(started()), this, SLOT(processStarted_on_pushButton_clicked()));
    //connect(pro, SIGNAL(started()), this, SLOT(processStarted_on_pushButton_2_clicked()));
    //connect(pro, SIGNAL(started()), this, SLOT(processStarted_on_pushButton_3_clicked()));
    //connect(pro, SIGNAL(started()), this, SLOT(processStarted_on_pushButton_4_clicked()));

    setTab1();
    setTab2();
    setstatusBar();

    ui->action_Close->setDisabled(true);
    ui->action_Save->setDisabled(true);
    ui->action_Update->setDisabled(true);
    ui->action_SAVE_as->setDisabled(true);
}

PRMainWindow::~PRMainWindow()
{
    delete ui;
}

void PRMainWindow::setTab1()
{
    ui->tabWidget->setTabText(0, tr("Editing PKGBUILD file"));
    ui->label->setOpenExternalLinks(true);
    ui->label->setText(tr("<h3><a href=\"https://wiki.archlinux.org/index.php/Creating_packages\">Need help</a> in inserting the <a href=\"https://wiki.archlinux.org/index.php/Arch_packaging_standards\">package</a> information on <a href=\"https://wiki.archlinux.org/index.php/PKGBUILD\">PKGBUILD</a> file ?</h3>"));
    ui->tab->setLayout(ui->gridLayout_4);
    ui->textEdit->setStyleSheet("QTextEdit {font: 16pt \"Monospace\";}");
    ui->textEdit->setAcceptRichText(false);
    ui->textEdit->setDisabled(true);
    ui->textEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->label_2->setText("Open a PKGBUILD file: Ctrl+O or Create a new PKGBUILD file: Ctrl+N - After create: File - Save as PKGBUILD");
}

void PRMainWindow::setTab2()
{
    ui->tabWidget->setTabText(1, tr("Building Package ..."));
    ui->tab_2->setLayout(ui->gridLayout_3);
    ui->pushButton->setText(tr("Verify Package"));
    ui->pushButton_2->setText(tr("Update Sums"));
    ui->pushButton_3->setText(tr("Build Tarball"));
    ui->pushButton_4->setText(tr("Build Package"));
    ui->pushButton_5->setText(tr("Clear Text"));
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->textEdit_2->setStyleSheet("QTextEdit {font: 12pt \"Monospace\";}");
    ui->textEdit_2->setAcceptRichText(false);
    ui->textEdit_2->setReadOnly(true);
    ui->textEdit_2->setWordWrapMode(QTextOption::NoWrap);
}

void PRMainWindow::setstatusBar()
{
    statusBar()->showMessage(tr("Ready to Roll !"), 5000);
}

// tools - options
void PRMainWindow::on_action_Options_triggered()
{
    // dialog for set size of font in textEdit's and select text highlight
}

// about - packnroll
void PRMainWindow::on_action_Packnroll_triggered()
{
    PRDialog *prd = new PRDialog;
    prd->setModal(true);
    prd->exec();
}

// file - open
void PRMainWindow::on_action_Open_triggered()
{
    fn = QFileDialog::getOpenFileName(this, tr("Open File..."), QString(), tr("PKGBUILD (PKGBUILD)"));
    if (!fn.isEmpty())
    {
        loadFile(fn);
        fn_temp.clear();
        fn_temp = fn;
        fn_temp.chop(8);
        fn_copy.clear();
        fn_copy.append(fn_temp);
        ui->textEdit->setDisabled(false);
        ui->action_Close->setDisabled(false);
        ui->action_Save->setDisabled(false);
        ui->action_Update->setDisabled(false);
        ui->action_Open->setDisabled(true);
        ui->action_New->setDisabled(true);
        ui->pushButton->setDisabled(false);
        ui->pushButton_2->setDisabled(false);
        ui->pushButton_3->setDisabled(false);
        ui->pushButton_4->setDisabled(false);
        ui->pushButton_5->setDisabled(false);
    }
}

// file - save
void PRMainWindow::on_action_Save_triggered()
{
    QFile file;
    if(fn.isEmpty())
        file.setFileName(save_as_file);
    else
        file.setFileName(fn);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Pack n' Roll"), tr("Cannot write file %1:\n%2.").arg(fn).arg(file.errorString()));
        return;
    }
    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << ui->textEdit->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    statusBar()->showMessage(tr("PKGBUILD Saved !"), 2000);
}

// file - exit
void PRMainWindow::on_action_Exit_triggered()
{
    this->close();
}

void PRMainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Pack n' Roll"), tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return;
    }
    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    ui->textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    ui->label_2->setText(fn);
    statusBar()->showMessage(tr("PKGBUILD Loaded !"), 2000);
}

void PRMainWindow::on_action_Close_triggered()
{
    ui->textEdit->document()->setModified(false);
    setWindowModified(false);
    ui->textEdit->setPlainText("");
    ui->textEdit_2->setPlainText("");
    fn.clear();
    fn_copy.clear();
    fn_temp.clear();
    ui->label_2->setText("Open a PKGBUILD file by pressing: Ctrl+O");
    ui->textEdit->setDisabled(true);
    ui->action_Close->setDisabled(true);
    ui->action_Save->setDisabled(true);
    ui->action_New->setDisabled(false);
    ui->action_Open->setDisabled(false);
    ui->action_SAVE_as->setDisabled(true);
    ui->action_Update->setDisabled(true);
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
}

void PRMainWindow::on_action_New_triggered()
{
    QString new_PKGBUILD = "# Maintainer: Your Name <youremail@domain.com>\n\npkgname=NAME\npkgver=VERSION\npkgrel=1\npkgdesc=""\narch=()\nurl=""\nlicense=('GPL')\ngroups=()\ndepends=()\nmakedepends=()\noptdepends=()\nprovides=()\nconflicts=()\nreplaces=()\nbackup=()\noptions=()\ninstall=\nchangelog=\nsource=($pkgname-$pkgver.tar.gz)\nnoextract=()\nsha256sums=()\nmd5sums=() #autofill using updpkgsums\n\nbuild() {\n\tcd \"$pkgname-$pkgver\"\n\t./configure --prefix=/usr\n\tmake\n}\n\npackage() {\n\tcd \"$pkgname-$pkgver\"\n\tmake DESTDIR=\"$pkgdir/\" install\n}\n";
    ui->textEdit->setPlainText(new_PKGBUILD);
    ui->textEdit->setDisabled(false);
    ui->action_SAVE_as->setDisabled(false);
    ui->action_Save->setDisabled(true);
    ui->action_Close->setDisabled(false);
    ui->action_New->setDisabled(true);
    ui->action_Open->setDisabled(true);
    ui->action_Update->setDisabled(false);
    ui->pushButton->setDisabled(false);
    ui->pushButton_2->setDisabled(false);
    ui->pushButton_3->setDisabled(false);
    ui->pushButton_4->setDisabled(false);
    ui->pushButton_5->setDisabled(false);
}

void PRMainWindow::on_action_SAVE_as_triggered()
{
    QFile file;
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec())
    {
        file.setFileName(dialog.directory().absoluteFilePath("PKGBUILD"));
        fn = dialog.directory().absoluteFilePath("PKGBUILD");
        fn_temp.clear();
        fn_temp = fn;
        fn_temp.chop(8);
        fn_copy.clear();
        fn_copy.append(fn_temp);
        if (!file.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this, tr("Pack n' Roll"), tr("Cannot write file %1:\n%2.").arg(save_as_file).arg(file.errorString()));
            return;
        }
        QTextStream out(&file);
    #ifndef QT_NO_CURSOR
        QApplication::setOverrideCursor(Qt::WaitCursor);
    #endif
        out << ui->textEdit->toPlainText();
    #ifndef QT_NO_CURSOR
        QApplication::restoreOverrideCursor();
    #endif
        statusBar()->showMessage(tr("PKGBUILD Saved !"), 2000);
        ui->action_SAVE_as->setDisabled(true);
        ui->action_Save->setDisabled(false);
        ui->label_2->setText(dialog.directory().absoluteFilePath("PKGBUILD"));
    }
}

void PRMainWindow::on_action_Update_triggered()
{
    loadFile(fn);
}

// readyRead method
void PRMainWindow::readyRead()
{
    /*
     *  QByteArray QProcess::readAllStandardOutput()
     *  Regardless of the current read channel,
     *  this function returns all data available from
     *  the standard output of the process as a QByteArray.
    */
    string_output.append(pro->readAllStandardOutput());
    ui->textEdit_2->setPlainText(string_output);
    // sets a vertical scroll bar in the textEdit
    ui->textEdit_2->verticalScrollBar()->setSliderPosition(ui->textEdit_2->verticalScrollBar()->maximum());
}

/*
// Debuging
void PRMainWindow::processStarted_on_pushButton_clicked()
{
    qDebug() << "on_pushButton_clicked()";
}

// Debuging
void PRMainWindow::processStarted_on_pushButton_2_clicked()
{
    qDebug() << "on_pushButton_2_clicked()";
}

// Debuging
void PRMainWindow::processStarted_on_pushButton_3_clicked()
{
    qDebug() << "on_pushButton_3_clicked()";
}

// Debuging
void PRMainWindow::processStarted_on_pushButton_4_clicked()
{
    qDebug() << "on_pushButton_4_clicked()";
}
*/

// verify package button
void PRMainWindow::on_pushButton_clicked()
{
    ui->textEdit_2->clear();
    QString program = "namcap";
    QStringList arguments;
    QDir::setCurrent(fn_copy);
    arguments << "PKGBUILD";
    //qDebug() << "on_pushButton_clicked" << "fn " << fn << "\n" << "fn_copy " << fn_copy << "\n";
    /*
     * QProcess merges the output of the running process into the standard output channel (stdout).
     * The standard error channel (stderr) will not receive any data.
     * The standard output and standard error data of the running process are interleaved.
    */
    pro->setProcessChannelMode(QProcess::MergedChannels);
    pro->start(program, arguments);
}

// update sums button
void PRMainWindow::on_pushButton_2_clicked()
{
    ui->textEdit_2->clear();
    QString program = "updpkgsums";
    QStringList arguments;
    QDir::setCurrent(fn_copy);
    arguments << "PKGBUILD";
    //qDebug() << "on_pushButton_2_clicked" << "fn " << fn << "\n" << "fn_copy " << fn_copy << "\n";
    /*
     * QProcess merges the output of the running process into the standard output channel (stdout).
     * The standard error channel (stderr) will not receive any data.
     * The standard output and standard error data of the running process are interleaved.
    */
    pro->setProcessChannelMode(QProcess::MergedChannels);
    pro->start(program, arguments);
}

// build tarball button
void PRMainWindow::on_pushButton_3_clicked()
{
    ui->textEdit_2->clear();
    QString program = "makepkg";
    QStringList arguments;
    QDir::setCurrent(fn_copy);
    arguments << "--source";
    //qDebug() << "on_pushButton_3_clicked" << "fn " << fn << "\n" << "fn_copy " << fn_copy << "\n";
    /*
     * QProcess merges the output of the running process into the standard output channel (stdout).
     * The standard error channel (stderr) will not receive any data.
     * The standard output and standard error data of the running process are interleaved.
    */
    pro->setProcessChannelMode(QProcess::MergedChannels);
    pro->start(program, arguments);
}

// build package button
void PRMainWindow::on_pushButton_4_clicked()
{
    ui->textEdit_2->clear();
    QString program = "makepkg";
    QDir::setCurrent(fn_copy);
    //qDebug() << "on_pushButton_4_clicked" << "fn " << fn << "\n" << "fn_copy " << fn_copy << "\n";
    /*
     * QProcess merges the output of the running process into the standard output channel (stdout).
     * The standard error channel (stderr) will not receive any data.
     * The standard output and standard error data of the running process are interleaved.
    */
    pro->setProcessChannelMode(QProcess::MergedChannels);
    pro->start(program);
}

void PRMainWindow::on_pushButton_5_clicked()
{
    ui->textEdit_2->setPlainText("");
}
