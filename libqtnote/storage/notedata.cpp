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

#include <QTextDocument>

#include "storage/notedata.h"

namespace QtNote {

NoteData::NoteData(NoteStorage *storage)
	: QSharedData()
    , _storage(storage)
    , _text(0)
{
}

NoteData::NoteData(NoteStorage *storage, const QString &noteId)
    : QSharedData()
    , _id(noteId)
    , _storage(storage)
    , _text(0)
{

}

QString NoteData::plainText()
{
    return document()->toPlainText();
}

QTextDocument *NoteData::document()
{
    if (!_text) {
        load();
    }
    return _text;
}

void NoteData::setDocument(QTextDocument *doc)
{
    delete _text;
    _text = doc;
    if (doc) {
        _title = doc->toPlainText().trimmed().section('\n', 0, 0).trimmed().left(NoteData::TitleLength);
    }
    save();
}

NoteData::~NoteData()
{
    delete _text;
}

QString NoteData::title() const
{
    return _title;
}

void NoteData::setPlainText(const QString &text)
{
    QString trimmed = text.trimmed();
    document()->setPlainText(trimmed);
    _title = trimmed.section('\n', 0, 0).trimmed().left(NoteData::TitleLength);
}

QVariant NoteData::uiCmpValue() const
{
    return _title;
}

}
