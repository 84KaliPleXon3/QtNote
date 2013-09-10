#include "notestorage.h"

class QWidget;

class TrayHandlerInterface
{
public:
	void setNoteList(QList<NoteListItem>) = 0;
	void notify(const QString &message) = 0;
};

class DEIntegrationInterface
{
public:
    virtual void activateNote(QWidget *w) = 0;
};

Q_DECLARE_INTERFACE(DEIntegrationInterface,
                     "com.rion-soft.QtNote.TrayIconInterface/1.0")