/*
 *  This file is part of Pack n' Roll project
 *	name of file: PRDialog.hpp
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

#ifndef PRDIALOG_HPP
#define PRDIALOG_HPP

#include <QDialog>

namespace Ui {
class PRDialog;
}

class PRDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PRDialog(QWidget *parent = 0);
    ~PRDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PRDialog *ui;
};

#endif // PRDIALOG_HPP
