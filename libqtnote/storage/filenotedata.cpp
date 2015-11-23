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
	QFile f(sFileName);
    f.remove();
}

QVariant FileNoteData::uiCmpValue() const
{
    return _lastChange;
}

bool FileNoteData::load()
{
    QFile f(sFileName);
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        _text = new QTextDocument;
        _storage->richTextAdapter()->populateDocumentFromData(_text, f.readAll());
        return true;
    }
    return false;
}

void FileNoteData::saveData(const QByteArray &data)
{
    auto np = dynamic_cast<FileStorage*>(storage())->nameProvider;
    QString filename, id;
    if (_id.isEmpty()) {
        filename = np->newName(*this, id);
    } else {
        filename = np->updateName(*this, id);
    }

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Failed to write: %s\n", qPrintable(file.errorString()));
        return false;
    }
    file.write(data);
    file.close();
    _lastChange = QFileInfo(file).lastModified();
    _id = id;
    return true;
}

} // namespace QtNote
