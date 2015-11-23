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

#include <QString>
#include <QVariant>
#include <QHash>
#include <QTextDocument>

#include "storage/note.h"
#include "storage/notedata.h"

namespace QtNote {

Note::Note()
{

}

Note::Note(NoteData *data)
{
    d = QSharedPointer<NoteData>(data);
}

QString Note::id() const
{
    return d->id();
}

NoteStorage *Note::storage() const
{
    return d->storage();
}

bool Note::isNull()
{
	return !d;
}

void Note::remove()
{
    d->remove();
}

QString Note::plainText() const
{
    return d->plainText();
}

void Note::setPlainText(const QString &text)
{
    d->setPlainText(text);
}

QTextDocument* Note::document() const
{
    return d->document();
}

void Note::setDocument(QTextDocument *doc)
{
    d->setDocument(doc);
}

QString Note::title() const
{
	return d->title();
}

NoteData* Note::data() const
{
    return d.data();
}

typedef bool (*uiNotesComparer)(const QVariant &a, const QVariant &b);
static QHash<QVariant::Type,uiNotesComparer> uiComparers;
static QVariant::Type uiCmpPrevType = QVariant::Invalid;
static uiNotesComparer uiCmpPrev;

bool Note::uiCmp(const Note &other) const
{
    QVariant v = d->uiCmpValue();
    QVariant ov = other.d->uiCmpValue();
    if (v.type() == ov.type()) {
        if (v.type() != uiCmpPrevType) {
            uiCmpPrevType = v.type();
            uiCmpPrev = uiComparers.value(uiCmpPrevType);
        }
        if (uiCmpPrev) {
            return uiCmpPrev(v, ov);
        }
    }
    return title().compare(other.title(), Qt::CaseInsensitive) > 0;
}

} // namespace QtNote
