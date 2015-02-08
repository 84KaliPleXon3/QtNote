# -------------------------------------------------
# Project created by QtCreator 2009-02-10T13:06:32
# QtNote - Simple note-taking application
# Copyright (C) 2010 Ili'nykh Sergey
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# Contacts:
# E-Mail: rion4ik@gmail.com XMPP: rion@jabber.ru
# -------------------------------------------------

include(../common.pri)

TARGET = $$APPNAME
TEMPLATE = lib

greaterThan(QT_MAJOR_VERSION, 4) {
    QT *= printsupport
    QT *= widgets
    greaterThan(QT_MAJOR_VERSION, 5)|greaterThan(QT_MINOR_VERSION, 0) {
	unix:!mac:QT += x11extras
    }
}

unix {
    target.path = $$LIBDIR
    INSTALLS += target
}

SOURCES += notedialog.cpp \
	note.cpp \
	notemanager.cpp \
	notestorage.cpp \
	ptfstorage.cpp \
	ptfdata.cpp \
	notedata.cpp \
	filenotedata.cpp \
	aboutdlg.cpp \
	optionsdlg.cpp \
	filestorage.cpp \
	utils.cpp \
	notesmodel.cpp \
	notemanagerdlg.cpp \
	notemanagerview.cpp \
	noteedit.cpp \
	ptfstoragesettingswidget.cpp \
	qtnote.cpp \
	typeaheadfind.cpp \
	shortcutedit.cpp \
	shortcutsmanager.cpp \
	notewidget.cpp \
	pluginmanager.cpp \
    optionsplugins.cpp \
    notehighlighter.cpp \
    colorbutton.cpp

HEADERS += notedialog.h \
	note.h \
	notemanager.h \
	notestorage.h \
	ptfstorage.h \
	ptfdata.h \
	notedata.h \
	filenotedata.h \
	aboutdlg.h \
	optionsdlg.h \
	filestorage.h \
	utils.h \
	notesmodel.h \
	notemanagerdlg.h \
	notemanagerview.h \
	noteedit.h \
	ptfstoragesettingswidget.h \
	qtnote.h \
	typeaheadfind.h \
	shortcutedit.h \
	shortcutsmanager.h \
	notewidget.h \
	pluginmanager.h \
    optionsplugins.h \
    highlighterext.h \
    notehighlighter.h \
    colorbutton.h \
    defaults.h

FORMS += notedialog.ui \
	aboutdlg.ui \
	optionsdlg.ui \
	notemanagerdlg.ui \
	ptfstoragesettingswidget.ui \
	notewidget.ui \
    optionsplugins.ui

INCLUDEPATH += $$PWD $$PWD/../plugins

# required for shortcuts
unix:!macx:LIBS += -L$$QMAKE_LIBDIR_X11 -lX11

macx {
    LIBS = -framework ApplicationServices
}

RESOURCES += main.qrc
