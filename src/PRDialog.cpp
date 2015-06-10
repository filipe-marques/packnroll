/*
 *  This file is part of Pack n' Roll project
 *	name of file: PRDialog.cpp
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

#include "inc/PRDialog.hpp"
#include "ui_prdialog.h"

PRDialog::PRDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::PRDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("About Pack n' Roll");
    this->setMaximumSize(560,287);
    this->setMinimumSize(560,287);
}

PRDialog::~PRDialog()
{
    delete ui;
}

// ok button
void PRDialog::on_pushButton_clicked()
{
    this->close();
}
