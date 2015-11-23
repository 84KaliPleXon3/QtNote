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

#ifndef NOTE_H
#define NOTE_H

#include <QSharedPointer>

//class NoteData;
//#include "storage/notedata.h"
#include "qtnote_export.h"

class QTextDocument;

namespace QtNote {

class NoteData;
class NoteStorage;

class QTNOTE_EXPORT Note
{
public:
	Note();
	Note(NoteData *data);

    QString id() const;
    NoteStorage* storage() const;
	bool isNull();
    void remove();
    QString plainText() const;
    void setPlainText(const QString &text);
    QTextDocument *document() const;
    void setDocument(QTextDocument* doc);
	QString title() const;
	NoteData* data() const;
    bool uiCmp(const Note &other) const;

private:
	QSharedPointer<NoteData> d;
};

} // namespace QtNote

#endif // NOTE_H
