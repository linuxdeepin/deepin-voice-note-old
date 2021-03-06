#include "aiservicecontroller.h"
#include "intancer.h"
#include "uiutil.h"
#include <QDebug>
#include <QDBusConnection>
#include <QDBusError>
#include <QDebug>
#include <QObject>

AiServiceController::AiServiceController()
{
    m_session = nullptr;
    m_asrInterface = nullptr;
};
AiServiceController::~AiServiceController()
{
    //4256
    if (m_status == "3" || m_status == "0")
    {
        this->stopAsr();
    }
    if(m_asrInterface) delete m_asrInterface;
    if(m_session) delete m_session;
};

QString AiServiceController::createSession(QString ability)
{
    if (m_session == nullptr)
    {
        m_session = new com::iflytek::aiservice::session("com.iflytek.aiservice","/",QDBusConnection::sessionBus(),this);
        int errorcode = -1;
        QString a = Intancer::get_Intancer()->getApplicationName();
        QDBusObjectPath qdPath = m_session->createSession(Intancer::get_Intancer()->getApplicationName(),ability,errorcode);
        //qDebug() << "ObjectPath : " << qdPath.path() << " errorcode: " << errorcode;
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("ObjectPath : "), qdPath.path());
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString(" errorcode: "), QString::number(errorcode,10));
        return qdPath.path();
    }
    return "";
}

void AiServiceController::freeSession(QString ability)
{
    //qDebug() << "freeSession ret :" << m_session->freeSession(Intancer::get_Intancer()->getApplicationName(),ability);
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("freeSession ret :"), QString::number(m_session->freeSession(Intancer::get_Intancer()->getApplicationName(),ability),10));
}

QString AiServiceController::startAsr(QString filePath, int fileDuration, QString srcLanguage, QString targetLanguage)
{
    ability = "asr";
    QString path = createSession(ability);
    if (m_asrInterface == nullptr)
    {
        m_asrInterface = new com::iflytek::aiservice::asr("com.iflytek.aiservice",path,QDBusConnection::sessionBus(),this );
        connect(m_asrInterface,SIGNAL(onNotify(QString)),this,SLOT(notifySlot(QString)));
    }


    QVariantMap param;
    param.insert("filePath",filePath);
    param.insert("fileDuration",fileDuration);
    if (!srcLanguage.isEmpty())
    {
        param.insert("fileDuration",srcLanguage);
    }
    if (!targetLanguage.isEmpty())
    {
        param.insert("fileDuration",targetLanguage);

    }
    QString ret = m_asrInterface->startAsr(param);
    m_status = "0";  //4256
    //Add start 3858
    if (ret != "000000")
    {
        class AsrResult clsResult;
        clsResult.code = ret;
        if(m_asrInterface) delete m_asrInterface;
        if(m_session) delete m_session;
        m_session = nullptr;
        m_asrInterface = nullptr;
        //qDebug()<< "clsResult.code:"<<clsResult.code;
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("clsResult.code:"), clsResult.code);
        emit AsrResultReq(clsResult);
    }
    //Add end 3858
    //qDebug()<< "start:"<<ret;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("start:"), ret);
    return ret;
}
void AiServiceController::stopAsr()
{
    if(m_asrInterface != nullptr){
        m_asrInterface->stopAsr();
        this->freeSession(ability);
    }
}

void AiServiceController::notifySlot(const QString &msg)
{
    //qDebug() << msg;
    UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("msg: "), msg);
    class AsrResult clsResult;
    asrJsonParse(msg,clsResult);
    m_status = clsResult.status;
    if (clsResult.code == "000000" && clsResult.status == "4")
    {
        //this->freeSession(ability);
        if(m_asrInterface) delete m_asrInterface;
        if(m_session) delete m_session;
        m_session = nullptr;
        m_asrInterface = nullptr;
        emit AsrResultReq(clsResult);
    }
    else if ((clsResult.code == "000000" && clsResult.status == "-1") || clsResult.code != "000000")
    {
        //this->freeSession(ability);
        ErrorCodeToMsg(clsResult,clsResult.ErrorMsg);
        if(m_asrInterface) delete m_asrInterface;
        if(m_session) delete m_session;
        m_session = nullptr;
        m_asrInterface = nullptr;
        emit AsrResultReq(clsResult);
    }
}
void AiServiceController::asrJsonParse(const QString &msg, class AsrResult &Result)
{
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(msg.toUtf8(), &error);
    if(QJsonParseError::NoError == error.error)
    {
        //map
        QVariantMap map = document.toVariant().toMap();
        if(map.contains("code"))
        {
            Result.code = map["code"].toString();
        }
        if(map.contains("descInfo"))
        {
            Result.descInfo = map["descInfo"].toString();
        }
        if(map.contains("failType"))
        {
            Result.failType = map["failType"].toString();
        }
        if(map.contains("status"))
        {
            Result.status = map["status"].toString();
        }
        if(map.contains("text"))
        {
            Result.txt = map["text"].toString();
        }
    }

}
void AiServiceController::ErrorCodeToMsg(const class AsrResult &clsResult, QString &ErrorMsg)
{
  if (clsResult.code == "900003")
  {
      ErrorMsg = "⽹络状态差，语⾳已转写失败，是否重新转写？";
      return;
  }
  if (clsResult.code == "000000" && clsResult.status =="-1")
  {
      if (clsResult.failType == "6")
      {
         ErrorMsg = "静音文件";
         return;
      }
  }
}


