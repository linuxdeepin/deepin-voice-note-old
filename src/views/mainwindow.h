#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainpage.h"
#include "textnoteedit.h"


#include <DMainWindow>
#include <QFrame>
#include <QObject>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#define DEFAULT_WINDOWS_WIDTH 960
#define DEFAULT_WINDOWS_HEIGHT 540
#define TITLE_FIXED_HEIGHT 40


DWIDGET_USE_NAMESPACE

class MyMainWindow : public DMainWindow
{
    Q_OBJECT
public:
    MyMainWindow();

public slots:
    void showNoteDetail(NOTE note);
    void showListPage();

private:
     QFrame *m_centralWidget;
//     DFMSplitter *m_splitter;
//     QFrame *m_leftView;

//     RightView *m_rightView;
    MainPage * m_mainPage;
    QStackedWidget * m_stackedWidget;
    TextNoteEdit * m_textNoteEdit;
    QWidget *m_detailPage;
    QVBoxLayout *m_detailPageLayout;
    QLabel *m_logo;
    DImageButton *m_returnBtn;
    QFrame *m_titleFrame;

    void initUI();
    void initConnection();

    void initTitleBar();
    void initTitleFrame();

    void initStackedWidget();
//    void initSplitter();

//    void initLeftView();

//    void initRightView();

    void initCentralWidget();
};

#endif // MAINWINDOW_H