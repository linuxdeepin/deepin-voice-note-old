#ifndef CONSTS_H
#define CONSTS_H

#include <QDateTime>
#include <QString>

#define TABLE_FOLDER "folder"
#define TABLE_NOTE "note"

static QString DB_PATH = "./voiceNoteDB.db";
//static QString DB_PATH = "/mnt/hgfs/D/voiceNoteDB1.db";
static QString DEFAULT_FOLDER_IMG_PATH = ":/image/default_folder_img.png";
static const char * DEFAULT_FOLDER_NAME = "新记事";
static const char * FOLDER_MENU_RENAME = "重命名";
static const char * FOLDER_MENU_DELETE = "删除";
static const char * NOTE_MENU_SAVE_AS_TXT = "保存为TXT";
static const char * NOTE_MENU_SAVE_AS_MP3 = "保存为MP3";

enum NOTE_TYPE {VOICE=0, TEXT=1};

typedef struct
{
    int id;
    QString imgPath;
    QString folderName;
    QDateTime createTime;
}FOLDER;



typedef struct
{
    int id;
    NOTE_TYPE noteType;
    QString contentText;
    QString contentPath;
    int voiceTime;
    QString voiceSampleData;
    int folderId;
    QDateTime createTime;
}NOTE;

typedef struct
{
    NOTE note;
    QString windowTitle;
    QString fileExtension;
}SAVE_INFO;

typedef struct
{
    QString voicePath;
    int voiceLength;
    QString voiceSampleData;
}VOICE_INFO;
#endif // CONSTS_H
