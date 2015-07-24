#
#       This file is part of Pack n' Roll project
#	name of file: packnroll.pro
#
#	Copyright (C) 2015 Filipe Marques <eagle.software3@gmail.com>
#
#	This program is free software; you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation; either version 3 of the License, or
#	any later version.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You received a copy of the GNU General Public License
#	along with this program in License folder; if not, write to the Free Software
#	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#	MA 02110-1301, USA.
#

QT       += core gui widgets

TARGET = PacknRoll
TEMPLATE = app
CONFIG += c++11
CONFIG += release

VERSION += 1.0.0

SOURCES +=  src/main.cpp\
            src/PRMainWindow.cpp \
            src/PRDialog.cpp

HEADERS +=  inc/PRMainWindow.hpp \
            inc/PRDialog.hpp

FORMS   +=  ui/prmainwindow.ui \
            ui/prdialog.ui

RESOURCES += resources/pnrresources.qrc

# Installation on Linux
#unix {
#    target.path = /usr/bin/packnroll
#
#    desk.path = /usr/share/applications/packnroll
#    desk.files = packnroll.desktop
#
#    icon128.path = /usr/share/icons/hicolor/128x128/apps/packnroll
#    icon128.files = resource/icons/packnroll128.png
#
#    license.path = /usr/share/licenses/packnroll/LICENSE
#    license.files = LICENSE
#
#    INSTALLS += target desk icon24 icon24_2 icon128 license
#}
