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

#ifndef PTFNOTE_H
#define PTFNOTE_H

#include <QFile>
#include <QPointer>
#include <QDateTime>
#include "note.h"

class PTFNote : public Note
{
	Q_OBJECT
	Q_DISABLE_COPY(PTFNote)
private:
	QString sFile;
	QString sUid;
	QString sTitle;
	QString sText;
	QDateTime dtLastChange;
	QDateTime dtCreate;
	int iCursor;
	int iWidth;
	int iHeight;

public:
	PTFNote(QObject *parent = 0);
	~PTFNote();
	bool fromFile(QString);
	void setFile(QString fn);
	void saveToFile(const QString &fileName);
	QString title() const;
	QString uid() const;
	QString text() const;
	void setText(const QString &text);
	QDateTime modifyTime() const;
	void toTrash();
};

#endif // TOMBOYNOTE_H