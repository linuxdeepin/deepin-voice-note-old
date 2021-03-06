#ifndef PLAYINGBUTTON_H
#define PLAYINGBUTTON_H

#include <QWidget>
#include <DImageButton>
#include <QVBoxLayout>
#include <DFloatingButton>
#include "myrecodebuttons.h"

DWIDGET_USE_NAMESPACE

//录音回放按钮
class PlayingButton : public QWidget
{
    Q_OBJECT

public:
    PlayingButton(QWidget *parent = 0);
    void onlySetResumeForButton();
    void setPlayDisable();
    void setPlayEnable();
    void VoicePlayOrPause(); //Add bug 2587
signals:
    void pause();
    void resume();
    void stop();

public slots:
    void handlePause();
    void handleResume();
    void handleStop();
    void changeTheme();

private:
    MyRecodeButtons *pauseButton;
    MyRecodeButtons *resumeButton;
    QVBoxLayout *layout;
};

#endif // PLAYINGBUTTON_H
