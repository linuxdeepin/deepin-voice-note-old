#include "addtextbtn.h"
#include "consts.h"
#include <DApplicationHelper>
#include <DFontSizeManager>

#include <QDebug>

#include "uiutil.h"

AddTextBtn::AddTextBtn(QWidget *parent) : DWidget(parent)
{
    this->setFixedHeight(ADDBUTTON_HEIGHT_HEIGHT);
//    DPalette pe = DApplicationHelper::instance()->palette(this);
//    pe.setBrush(DPalette::Base, QColor(255,255,0,255));
//    this->setAutoFillBackground(true);
//    this->setPalette(pe);
    m_addBtn = new DPushButton(this);
    m_addBtn->setFixedHeight(64);
    //m_addBtn->setFixedSize(QSize(548,64));
    //m_addBtn->setFixedSize(QSize(539,64));
    //m_addBtn->move(0,0);
    //m_addBtn->setFixedHeight(64);

//    QSizePolicy sp = m_addBtn->sizePolicy();
//    sp.setHorizontalStretch(1);
//    m_addBtn->setSizePolicy(sp);

    connect(m_addBtn, SIGNAL(clicked()), this, SIGNAL(addTextItem()));

    m_itemLayout = new QHBoxLayout(this);
    m_itemLayout->setContentsMargins(0, 0, 0, 0);

    QSpacerItem *phorizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    //m_itemLayout->addItem(phorizontalSpacer1);
    m_itemLayout->addWidget(m_addBtn);
    QSpacerItem *phorizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    //m_itemLayout->addItem(phorizontalSpacer2);

    //m_itemLayout->setSizeConstraint(QLayout::SetNoConstraint);

    this->setLayout(m_itemLayout);

    //3653
    //connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &AddTextBtn::changeTheme);

}

AddTextBtn::~AddTextBtn()
{
    if(nullptr != m_addBtn)
    {
        delete m_addBtn;
        m_addBtn = nullptr;
    }
}

void AddTextBtn::init()
{
    if(nullptr != m_addBtn)
    {
        DFontSizeManager::instance()->bind(m_addBtn,DFontSizeManager::T5);
        //m_addBtn->setFont(DFontSizeManager::instance()->get(DFontSizeManager::T5));
        m_addBtn->setText(tr("Add Text Note"));

//        DPalette pb = DApplicationHelper::instance()->palette(m_addBtn);
//        pb.setBrush(DPalette::ButtonText, pb.color(DPalette::TextTips));

//        pb.setBrush(DPalette::Button, QColor(0,0,0,0));
//        pb.setBrush(DPalette::Light, QColor(0,0,0,0));
//        pb.setBrush(DPalette::Dark, QColor(0,0,0,0));
//        pb.setBrush(DPalette::Shadow, pb.color(DPalette::FrameBorder));
//        m_addBtn->setPalette(pb);
    }
}

void AddTextBtn::setDisableBtn(bool flag)
{
    if(nullptr != m_addBtn)
    {
        m_addBtn->setDisabled(flag);
    }
}

//3653
//void AddTextBtn::changeTheme()
//{
//    DPalette pb = DApplicationHelper::instance()->palette(m_addBtn);
//    pb.setBrush(DPalette::ButtonText, pb.color(DPalette::TextTips));

//    pb.setBrush(DPalette::Button, QColor(0,0,0,0));
//    pb.setBrush(DPalette::Light, QColor(0,0,0,0));
//    pb.setBrush(DPalette::Dark, QColor(0,0,0,0));
//    pb.setBrush(DPalette::Shadow, pb.color(DPalette::FrameBorder));
//    m_addBtn->setPalette(pb);
//}

void AddTextBtn::resizeEvent(QResizeEvent * event)
{
    DWidget::resizeEvent(event);
    //m_addBtn->setFixedWidth(this->width() - 2);

    //qDebug()<<"addBtnWidth:"<<this->width();
    //qDebug()<<"btnwidth:"<<m_addBtn->width();
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("addBtnWidth:"), QString::number(this->width(),10));
    UiUtil::writeLog(1, __FILE__, __LINE__, Q_FUNC_INFO, QString("btnwidth:"), QString::number(m_addBtn->width(),10));
}
