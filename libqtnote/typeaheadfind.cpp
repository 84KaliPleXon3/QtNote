/*
 * typeaheadfind.cpp - Typeahead find toolbar
 * Copyright (C) 2006  Maciej Niedzielski
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "typeaheadfind.h"

#include <QAction>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QTextEdit>
#include <QApplication>
#include <QStyle>
#include <QLayout>
#include <QTextDocumentFragment>

/*#include "iconaction.h"
#include "stretchwidget.h"
#include "shortcutmanager.h"
#include "psioptions.h"*/

/**
 * \class TypeAheadFindBar
 * \brief The TypeAheadFindBar class provides a toolbar for typeahead finding.
 */

class TypeAheadFindBar::Private
{
public:
	// setup search and react to search results
	void doFind(bool backward = false)
	{
		QTextDocument::FindFlags options;

		if (caseSensitive)
			options |= QTextDocument::FindCaseSensitively;

		if (backward) {
			options |= QTextDocument::FindBackward;

			// move cursor before currect selection
			// to prevent finding the same occurence again
			QTextCursor cursor = te->textCursor();
			cursor.setPosition(cursor.selectionStart());
			cursor.movePosition(QTextCursor::Left);
			te->setTextCursor(cursor);
		}

		if (find(options)) {
			le_find->setStyleSheet("");
		}
		else {
			le_find->setStyleSheet("QLineEdit { background: #ff6666; color: #ffffff }");
		}
	}

	// real search code

	bool find(QTextDocument::FindFlags options, QTextCursor::MoveOperation start = QTextCursor::NoMove)
	{
		if (start != QTextCursor::NoMove) {
			QTextCursor cursor = te->textCursor();
			cursor.movePosition(start);
			te->setTextCursor(cursor);
		}

		bool found = te->find(text, options);
		if (!found) {
			if (start == QTextCursor::NoMove)
				return find(options, options & QTextDocument::FindBackward ? QTextCursor::End : QTextCursor::Start);

			return false;
		}

		return true;
	}

	void doReplace()
	{
		if (te->textCursor().selection().isEmpty()) {
			return;
		}
		te->textCursor().removeSelectedText();
		te->textCursor().insertText(le_replace->text());
	}

	QString text;
	bool caseSensitive;
	TypeAheadFindBar::Mode mode;

	QTextEdit *te;
	QLineEdit *le_find;
	QLineEdit *le_replace;
	QAction *act_next;
	QAction *act_prev;
	QAction *act_replace;
	QAction *act_le_replace;
	QCheckBox *cb_case;
};

/**
 * \brief Creates new find toolbar, hidden by default.
 * \param textedit, QTextEdit that this toolbar will operate on.
 * \param title, toolbar's title
 * \param parent, toolbar's parent
 */
TypeAheadFindBar::TypeAheadFindBar(QTextEdit *textedit, const QString &title, QWidget *parent)
: QToolBar(title, parent)
{
	d = new Private();
	d->te = textedit;
	init();
}

void TypeAheadFindBar::init()
{
	setIconSize(QSize(16,16));
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

	d->caseSensitive = false;
	d->text = "";

	d->le_find = new QLineEdit(this);
	d->le_find->setMaximumWidth(200);
	d->le_find->setToolTip(tr("Search"));
	connect(d->le_find, SIGNAL(textEdited(const QString &)), SLOT(textChanged(const QString &)));
	addWidget(d->le_find);

	d->le_replace = new QLineEdit(this);
	d->le_replace->setMaximumWidth(200);
	d->le_replace->setToolTip(tr("Replace"));
	d->act_le_replace = addWidget(d->le_replace);

	d->act_next = new QAction(QApplication::style()->standardIcon(QStyle::SP_ArrowDown), tr("Find next"), this);
	d->act_next->setEnabled(false);
	d->act_next->setToolTip(tr("Find next"));
	connect(d->act_next, SIGNAL(triggered()), SLOT(findNext()));
	addAction(d->act_next);

	d->act_prev = new QAction(QApplication::style()->standardIcon(QStyle::SP_ArrowUp), tr("Find previous"), this);
	d->act_prev->setEnabled(false);
	d->act_prev->setToolTip(tr("Find previous"));
	connect(d->act_prev, SIGNAL(triggered()), SLOT(findPrevious()));
	addAction(d->act_prev);

	d->act_replace = new QAction(QIcon(":/icons/replace-text"), tr("Replace"), this); // TODO find an icon for button
	d->act_replace->setToolTip(tr("Replace text"));
	connect(d->act_replace, SIGNAL(triggered()), SLOT(replaceText()));
	addAction(d->act_replace);

	d->cb_case = new QCheckBox(tr("&Case sensitive"), this);
	connect(d->cb_case, SIGNAL(stateChanged(int)), SLOT(caseToggled(int)));
	addWidget(d->cb_case);

	optionsUpdate();

	setMode(Find);
	hide();
}

void TypeAheadFindBar::setMode(TypeAheadFindBar::Mode mode)
{
	d->act_replace->setVisible(mode == Replace);
	d->act_le_replace->setVisible(mode == Replace);
	d->mode = mode;
}

TypeAheadFindBar::Mode TypeAheadFindBar::mode() const
{
	return d->mode;
}

/**
 * \brief Destroys the toolbar.
 */
TypeAheadFindBar::~TypeAheadFindBar()
{
	delete d;
	d = 0;
}

/**
 * \brief Should be called when application options are changed.
 * This slot updates toolbar's shortcuts.
 */
void TypeAheadFindBar::optionsUpdate()
{
	//d->act_next->setShortcuts(ShortcutManager::instance()->shortcuts("chat.find-next"));
	//d->act_prev->setShortcuts(ShortcutManager::instance()->shortcuts("chat.find-prev"));
}

/**
 * \brief Opens (shows) the toolbar.
 */
void TypeAheadFindBar::open()
{
	show();
	d->le_find->setFocus();
	d->le_find->selectAll();
	emit visibilityChanged(true);
}

/**
 * \brief Closes (hides) the toolbar.
 */
void TypeAheadFindBar::close()
{
	hide();
	emit visibilityChanged(false);
}

/**
 * \brief Switched between visible and hidden state.
 */
void TypeAheadFindBar::toggleVisibility()
{
	if (isVisible())
		hide();
	else
		//show();
		open();
}

/**
 * \brief Private slot activated when find text chagnes.
 */
void TypeAheadFindBar::textChanged(const QString &str)
{
	QTextCursor cursor;
	cursor = d->te->textCursor();

	if (str.isEmpty()) {
		d->act_next->setEnabled(false);
		d->act_prev->setEnabled(false);
		d->le_find->setStyleSheet("");
		cursor.clearSelection();
		d->te->setTextCursor(cursor);
		d->le_find->setStyleSheet("");
	}
	else {
		d->act_next->setEnabled(true);
		d->act_prev->setEnabled(true);

		// don't jump to next word occurence after appending new charater
		cursor.setPosition(cursor.selectionStart());
		d->te->setTextCursor(cursor);

		d->text = str;
		d->doFind();
	}
}

/**
 * \brief Private slot activated when find-next is requested.
 */
void TypeAheadFindBar::findNext()
{
	d->doFind();
}

/**
 * \brief Private slot activated when find-prev is requested.
 */
void TypeAheadFindBar::findPrevious()
{
	d->doFind(true);
}

void TypeAheadFindBar::replaceText()
{
	d->doReplace();
}

/**
 * \brief Private slot activated when case-sensitive box is toggled.
 */
void TypeAheadFindBar::caseToggled(int state)
{
	d->caseSensitive = (state == Qt::Checked);
}
