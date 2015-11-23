#ifndef QTNOTE_RICHTEXTADAPTER_H
#define QTNOTE_RICHTEXTADAPTER_H

#include <QObject>

class QTextDocument;

namespace QtNote {

class RichTextAdapter : public QObject
{
    Q_OBJECT

    enum Cap {
        Nothing = 0,
        FontSize = 0x1,
        FontColor = 0x2,
        BackgroundColor = 0x4,
        BulletList = 0x8,
        NumericList = 0x10,
        TaskList = 0x20,
        CustomObject = 0x40000000,
        Reserved = 0x80000000
    };
    Q_DECLARE_FLAGS(Caps, Cap)

public:
    explicit RichTextAdapter(QObject *parent = 0);
    virtual Caps caps() const = 0;

    virtual void populateDocumentFromData(QTextDocument *doc, const QByteArray &srcData) = 0;
    virtual QByteArray dumpDocument(QTextDocument *doc) = 0; // FIXME tomboy we need to return QDocumentFragment


signals:

public slots:
};

} // namespace QtNote

#endif // QTNOTE_RICHTEXTADAPTER_H
