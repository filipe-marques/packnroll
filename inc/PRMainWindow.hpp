/*
 *  This file is part of Pack n' Roll project
 *	name of file: PRMainWindow.hpp
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

#ifndef PRMAINWINDOW_HPP
#define PRMAINWINDOW_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QScrollBar>
#include <QDebug>
#include <QDir>

#include "PRDialog.hpp"

namespace Ui {
class PRMainWindow;
}

class PRMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PRMainWindow(QWidget *parent = 0);
    ~PRMainWindow();

private slots:

    void on_action_Options_triggered();
    void on_action_Packnroll_triggered();
    void on_action_Open_triggered();
    void on_action_Save_triggered();
    void on_action_Exit_triggered();
    void on_action_Close_triggered();
    void on_action_New_triggered();
    void on_action_SAVE_as_triggered();
    void on_action_Update_triggered();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

    // readyRead member function
    void readyRead();

    /*
    // Debuging
    void processStarted_on_pushButton_clicked();
    void processStarted_on_pushButton_2_clicked();
    void processStarted_on_pushButton_3_clicked();
    void processStarted_on_pushButton_4_clicked();
    */

private:
    Ui::PRMainWindow *ui;
    QProcess *pro;
    QString string_output, fn, fn_copy, fn_temp, save_as_file{"PKGBUILD"};

    void setTab1();
    void setTab2();
    void setstatusBar();
    void loadFile(const QString &fileName);
};

#endif // PRMAINWINDOW_HPP
