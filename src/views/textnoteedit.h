#ifndef TEXTNOTEEDIT_H
#define TEXTNOTEEDIT_H
#include <DTextEdit>
//#include <dtextedit.h>
#include <notecontroller.h>
#include <QObject>
#include <QTextEdit>
DWIDGET_USE_NAMESPACE

//文字编辑框(Detal和非Deltal都在使用)
class TextNoteEdit : public DTextEdit
//class TextNoteEdit : public QTextEdit
{
    Q_OBJECT
public:
    TextNoteEdit(NOTE textNote, QWidget *parent = nullptr, NoteController *noteCtr = nullptr);
    TextNoteEdit(QWidget *parent = nullptr, NoteController *noteCtr = nullptr);
    ~TextNoteEdit();

    QString getText();
    void setTextNote(NOTE textNote, QString searchKey);
    int getID();
    int getFolderID();
    void searchText(QString searchKey);
    void readFromDatabase();
    QString onlyreadFromDatabase();
signals:
    void clicked();
    void focusOutSignal();
    void sigTextChanged(QString str);
    void sigTextHeightChanged(int newHeight); //Add 20191111
    void sigDelMyself();

public slots:
    void updateNote();
    void textAreaChanged(); //Add 20191111

protected:
    void mousePressEvent(QMouseEvent *event);
    void focusOutEvent(QFocusEvent *e);

private:
    NOTE m_textNote;
    NoteController *m_noteCtr;
    QString m_searchKey;

    void initConnection();

};

#endif // TEXTNOTEEDIT_H
