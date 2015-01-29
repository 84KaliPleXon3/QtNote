#ifndef QTNOTE_SPELLCHECKER_H
#define QTNOTE_SPELLCHECKER_H

#include <QObject>
#include <QSyntaxHighlighter>

#include "noteedit.h"

namespace QtNote {

class SpellEngineInterface;

class SpellCheckHighlighter : public QSyntaxHighlighter
{
	Q_OBJECT

	SpellEngineInterface *sei;
public:

	SpellCheckHighlighter(SpellEngineInterface *sei, NoteEdit *nde);
	void highlightBlock(const QString &text);
};

} // namespace QtNote

#endif // QTNOTE_SPELLCHECKER_H
