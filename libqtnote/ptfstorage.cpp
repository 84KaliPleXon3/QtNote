/*
QtNote - Simple note-taking application
Copyright (C) 2010 Ili'nykh Sergey

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Contacts:
E-Mail: rion4ik@gmail.com XMPP: rion@jabber.ru
*/

#include <QDesktopServices>
#include <QDir>
#include <QApplication>
#include <QStyle>
#include <QSettings>

#ifdef Q_OS_WIN
#include <QLibrary>
#include <ShlObj.h>
#endif // Q_OS_WIN

#include "ptfstorage.h"
#include "ptfdata.h"
#include "utils.h"
#include "humanfilenameprovider.h"

namespace QtNote {

PTFStorage::PTFStorage(QObject *parent) :
    FileStorage(parent)
{
    fileExt = "txt";
    QSettings s;
    notesDir = s.value("storage.ptf.path").toString();
    if (notesDir.isEmpty()) {
        notesDir = findStorageDir();
    }
    initNotesDir();
}

void PTFStorage::initNotesDir()
{
    QDir d(notesDir);
    if (!d.exists()) {
        if (!QDir::root().mkpath(notesDir)) {
            qWarning("can't create storage dir: %s", qPrintable(notesDir));
        }
    }
    if (!nameProvder) {
        nameProvder = new HumanFileNameProvider(notesDir, fileExt);
    } else {
        nameProvder->setPath(notesDir);
    }
}

bool PTFStorage::isAccessible() const
{
    return QDir(notesDir).isReadable();
}

const QString PTFStorage::systemName() const
{
    return "ptf";
}

const QString PTFStorage::name() const
{
    return tr("Plain Text Storage");
}

QIcon PTFStorage::storageIcon() const
{
    return QIcon(":/icons/trayicon");
}

QIcon PTFStorage::noteIcon() const
{
    return QIcon(":/icons/trayicon");
}

QList<NoteListItem> PTFStorage::noteListFromInfoList(const QFileInfoList &files)
{
    QList<NoteListItem> ret;
    foreach (QFileInfo fi, files) {
        PTFData note;
        if (note.fromFile(fi.canonicalFilePath())) {
            NoteListItem li(note.uid(), systemName(), note.title(),
                            note.modifyTime());
            ret.append(li);
        }
    }
    return ret;
}

Note PTFStorage::note(const QString &noteId)
{
    if (!noteId.isEmpty()) {
        QString fileName = QDir(notesDir).absoluteFilePath(
                QString("%1.%2").arg(noteId).arg(fileExt) );
        QFileInfo fi(fileName);
        if (fi.isWritable()) {
            PTFData *noteData = new PTFData;
            noteData->fromFile(fileName);
            return Note(noteData);
        }
        handleFSError();
    }
    return Note();
}

bool PTFStorage::internalSave(const QString &text, QString &noteId)
{
    PTFData note;
    QDir d(notesDir);
    QString fileName = QString("%1.%2").arg(noteId).arg(fileExt);
    note.setText(text);

    QString title = note.title();
    QRegExp r("[<>:\"/\\\\|?*]");
    title.replace(r, QChar('_'));
    if (title != noteId) {
        d.remove(fileName);

        QString suf;
        int ind = 0;

        while (d.exists((fileName = QString("%1%2.%3").arg(title, suf, fileExt)))) {
            ind++;
            suf = QString::number(ind);
        }
        noteId = title + suf;
    }

    return saveNoteToFile(note, d.absoluteFilePath(fileName));
}

QString PTFStorage::createNote(const QString &text)
{
    QString noteId;
    if (internalSave(text, noteId)) {
        return noteId;
    }
    return QString();
}

bool PTFStorage::saveNote(const QString &noteId, const QString & text)
{
    QString idCopy = noteId;
    return internalSave(text, idCopy);
}

bool PTFStorage::isRichTextAllowed() const
{
    return false;
}

QString PTFStorage::findStorageDir() const
{
    return Utils::qtnoteDataDir() + QLatin1Char('/') + systemName();
}

} // namespace QtNote
