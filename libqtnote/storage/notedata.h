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

#ifndef NOTEDATA_H
#define NOTEDATA_H

#include <QSharedData>
#include <QString>
#include <QDateTime>
#include <QVariant>

#include "qtnote_export.h"

class QTextDocument;

namespace QtNote {

class NoteStorage;

class QTNOTE_EXPORT NoteData : public QSharedData
{
public:
	static const int TitleLength = 256;

    NoteData(NoteStorage *storage);
    NoteData(NoteStorage *storage, const QString &noteId);

    virtual ~NoteData();
    inline const QString &id() const { return _id; }
    inline NoteStorage* storage() const { return _storage; }

    virtual QString plainText();
    virtual void setPlainText(const QString &text);
    QTextDocument* document();
    void setDocument(QTextDocument *doc);

    inline const QDateTime &lastModify() const { return _lastModify; }

    virtual void  remove() = 0;
    virtual QString title() const;
    virtual QVariant uiCmpValue() const;

protected:
    virtual bool load() = 0;
    virtual bool save() = 0;

protected:
    QString _id;
    NoteStorage *_storage;
    QString _title;
    QTextDocument *_text;
    QDateTime _lastModify; // that's bad to use it only for sorting. actually each storage sould provide its way for best sorting
};

} // namespace QtNote

#endif // NOTEDATA_H
