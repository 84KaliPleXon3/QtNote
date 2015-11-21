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

#QMAKE_CXXFLAGS += -Winvalid-pch

greaterThan(QT_MAJOR_VERSION, 4) {
    QT *= printsupport
    QT *= widgets
    greaterThan(QT_MAJOR_VERSION, 5)|greaterThan(QT_MINOR_VERSION, 0) {
        unix:!mac:QT += x11extras
    }
    win32:CONFIG += skip_target_version_ext
}

unix {
    target.path = $$LIBDIR
    INSTALLS += target
}

win32 {
    target.path = $$WININST_PREFIX
    target.files = $$OUT_PWD$${DBG_SUBDIR}/qtnote.dll
    INSTALLS += target
}

SOURCES += \
    storage/note.cpp \
    storage/notemanager.cpp \
    storage/notestorage.cpp \
    storage/ptfstorage.cpp \
    storage/ptfdata.cpp \
    storage/notedata.cpp \
	storage/filenotedata.cpp \
	storage/filestorage.cpp \
	storage/filestoragesettingswidget.cpp \
	storage/filenameprovider.cpp \
	storage/humanfilenameprovider.cpp \
	storage/uuidfilenameprovider.cpp \
	widgets/noteedit.cpp \
	widgets/typeaheadfind.cpp \
	widgets/shortcutedit.cpp \
	widgets/colorbutton.cpp \
	notedialog.cpp \
	aboutdlg.cpp \
    optionsdlg.cpp \
    utils.cpp \
    notesmodel.cpp \
    notemanagerdlg.cpp \
    notemanagerview.cpp \
	qtnote.cpp \
    shortcutsmanager.cpp \
    notewidget.cpp \
    pluginmanager.cpp \
    optionsplugins.cpp \
    notehighlighter.cpp \
    notessearchmodel.cpp \
    richtextadapter.cpp

HEADERS += qtnote_export.h \
    storage/note.h \
    storage/notemanager.h \
    storage/notestorage.h \
    storage/ptfstorage.h \
    storage/ptfdata.h \
    storage/notedata.h \
	storage/filenotedata.h \
    storage/filestoragesettingswidget.h \
	storage/filestorage.h \
	storage/filenameprovider.h \
	storage/humanfilenameprovider.h \
	storage/uuidfilenameprovider.h \
	widgets/noteedit.h \
	widgets/typeaheadfind.h \
	widgets/shortcutedit.h \
	widgets/colorbutton.h \
	notedialog.h \
	aboutdlg.h \
    optionsdlg.h \
    utils.h \
    notesmodel.h \
    notemanagerdlg.h \
    notemanagerview.h \
	qtnote.h \
    shortcutsmanager.h \
    notewidget.h \
    pluginmanager.h \
    optionsplugins.h \
    highlighterext.h \
    notehighlighter.h \
    defaults.h \
    notessearchmodel.h \
    richtextadapter.h

FORMS += notedialog.ui \
    aboutdlg.ui \
    optionsdlg.ui \
    notemanagerdlg.ui \
    storage/filestoragesettingswidget.ui \
    notewidget.ui \
    optionsplugins.ui

INCLUDEPATH += $$PWD $$PWD/../plugins

# required for shortcuts
unix:!macx:LIBS += -L$$QMAKE_LIBDIR_X11 -lX11

macx {
    LIBS = -framework ApplicationServices
}

win32-ms*:LIBS *= -lUser32
win32:DEFINES += QTNOTE_EXPORT

RESOURCES += main.qrc

unix {
    incinstall.path = $$PREFIX/include/$$APPNAME
    incinstall.files = $$HEADERS
    INSTALLS += incinstall
}
