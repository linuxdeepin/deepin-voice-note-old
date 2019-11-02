#ifndef LEFTVIEW_H
#define LEFTVIEW_H
#include "leftfolderlist.h"

#include <DWidgetUtil>
#include <QFrame>
#include <foldercontroller.h>
//#include <DImageButton>
#include <dimagebutton.h>
//#include <DIconButton>
#include <QObject>
#include "consts.h"
#include <DtkGuis>
#include <QVBoxLayout>
#include <DBlurEffectWidget>
#include <DFloatingButton>
#include "addfolderbutton.h"

DWIDGET_USE_NAMESPACE
#define LEFTVIEW_MAX_WIDTH 250

//左侧View
class LeftView : public DBlurEffectWidget
//class LeftView : public QFrame
{
    Q_OBJECT
public:
    LeftView();
    ~LeftView();

    void sendSelectCurFolder();
    int getCurrSelectFolderId();
    void searchFolder(QString searchKey);
    void selectTheFirstFolderByCode();

signals:
    void selFolderIdChg(int folderId);
    void searchNote(int folderId, QString searchKey);
    void noResult();
    void clearNoteListSignal();
    void sigBoardPress();
    void sigAllFolderDeleted();
    void sigAddFolder();

protected:
    void resizeEvent(QResizeEvent * event);

public slots:
    void addFolder();
    void handleSelFolderChg(QListWidgetItem *item);
    void itemSelectedChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void viewDisabled();
    void viewEnabled();
    //void handlePressFolderChg(QListWidgetItem *item);

private:
    QVBoxLayout *m_leftViewLayout;
    //QListWidget *folderList;
    LeftFolderList *m_leftFolderView;
    AddFolderButton *m_addFolderBtn;
    //DWidget *m_LeftListBoard;

    FolderController *m_folderCtr;
    QString m_currSearchKey;
    DWidget *m_greyboard;

    void initUI();
    void initController();
    void initConnection();
    void updateFolderView();
    void clearNoteList();
};

#endif // LEFTVIEW_H
