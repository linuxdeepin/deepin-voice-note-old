#ifndef VOICENOTEBOOKAPP_H
#define VOICENOTEBOOKAPP_H

#include <src/views/mainwindow.h>

#include <DApplication>

DWIDGET_USE_NAMESPACE

class VoiceNotebookApp
{
public:
    VoiceNotebookApp(DApplication &a);
    ~VoiceNotebookApp();
    //int exec();
private:
    MyMainWindow *m_mainWindow;
    DApplication *m_app;
    void initApp();
    void initMainWindow();
    void initController();
    void initConnection();

};

#endif // VOICENOTEBOOKAPP_H