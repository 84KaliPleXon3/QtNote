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

#include <QFile>
#include <QTextDocument>

#include "storage/filenotedata.h"
#include "richtextadapter.h"
#include "filestorage.h"
#include "filenameprovider.h"

namespace QtNote {

QDateTime FileNoteData::modifyTime() const
{
    return _lastChange;
}

qint64 FileNoteData::lastChangeElapsed() const
{
    return _lastChange.msecsTo(QDateTime::currentDateTime());
}

void FileNoteData::remove()
{
    auto np = dynamic_cast<FileStorage*>(storage())->nameProvider;
    QFile f(np->fileNameForUid(_id));
    f.remove();
}

QVariant FileNoteData::uiCmpValue() const
{
    return _lastChange;
}

bool FileNoteData::open(QFile &f, QIODevice::OpenMode flags)
{
    auto np = dynamic_cast<FileStorage*>(storage())->nameProvider;
    if (_id.isEmpty()) {
        if (! (flags & (QIODevice::WriteOnly))) {
            return false;
        }
        QString id;
        f.setFileName(np->newName(*this, id));
        if (f.open(flags)) {
            _id = id;
            return true;
        }
        return false;
    }
    if (flags & QIODevice::WriteOnly) {
        f.setFileName(np->updateName(*this, id));
    } else {
        f.setFileName(np->fileNameForUid(_id));
    }
    return f.open(flags);
}

bool FileNoteData::load()
{
    QFile f;
    if (open(f, QIODevice::ReadOnly | QIODevice::Text)) {
        _text = new QTextDocument;
        _storage->richTextAdapter()->populateDocumentFromData(_text, f.readAll());
        return true;
    }
    return false;
}

bool FileNoteData::saveData(const QByteArray &data)
{
    QFile file;
    if (!open(file, QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Failed to write: %s\n", qPrintable(file.errorString()));
        return false;
    }
    file.write(data);
    file.close();
    _lastChange = QFileInfo(file).lastModified();
    return true;
}

} // namespace QtNote
