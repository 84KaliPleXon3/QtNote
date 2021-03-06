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

#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include <QFileInfoList>
#include <QHash>

#include "qtnote_export.h"
#include "storage/notestorage.h"

namespace QtNote {

class FileNoteData;
class FileNameProvider;

class QTNOTE_EXPORT FileStorage : public NoteStorage
{
    Q_OBJECT
public:
    FileStorage(QObject *parent);
    QString createNote(const QString &text);
    void deleteNote(const QString &noteId);
    virtual void putToCache(const Note &note, const QString &oldNoteId);
    virtual QString findStorageDir() const = 0;
    QWidget *settingsWidget();
    QString tooltip();
    QList<Note> noteList(int limit = 0);
    virtual QList<Note> noteListFromInfoList(const QFileInfoList &) = 0;

protected:
    QString saveNoteToFile(FileNoteData &note, const QString &text, const QString &noteId = QString::null);
    void handleFSError();
    void ensureChachePopulated();

protected slots:
    void settingsApplied();

protected:
    friend class FileNoteData;
    QString fileExt;
    QHash<QString, Note> cache;
    bool _cacheValid; /* last limit passed to noteList() */
    QString notesDir;
    FileNameProvider *nameProvider;
};

}

#endif // FILESTORAGE_H
