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

#ifndef FILENOTEDATA_H
#define FILENOTEDATA_H

#include <QDateTime>
#include <QIODevice>

#include "storage/notedata.h"

namespace QtNote {

class QTNOTE_EXPORT FileNoteData : public NoteData
{
public:
    inline FileNoteData(NoteStorage *storage)
        : NoteData(storage) {}
    inline FileNoteData(NoteStorage *storage, const QString &noteId)
        : NoteData(storage, noteId) {}

#if 0
    inline void setFile(const QString &fn) { sFileName = fn; }
    virtual bool saveToFile(const QString &fileName) = 0;
#endif
    QDateTime modifyTime() const;
	qint64 lastChangeElapsed() const;
	void remove();
    QVariant uiCmpValue() const;

protected:
    bool open(QFile &f, QIODevice::OpenMode flags);
    bool load();
    bool saveData(const QByteArray &data);

protected:
    QDateTime _lastChange;
};

} // namespace QtNote

#endif // FILENOTEDATA_H
