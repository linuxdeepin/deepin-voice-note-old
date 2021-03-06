#include "initemptypage.h"
#include "uiutil.h"
#include "intancer.h"
#include <DApplicationHelper>
#include <DFontSizeManager>

InitEmptyPage::InitEmptyPage(QWidget *parent) : DFrame(parent)
{
    init();
    initConnect();
}

void InitEmptyPage::onChangeColor()
{
    DGuiApplicationHelper::ColorType themeType = DGuiApplicationHelper::instance()->themeType();

    DPalette pb = DApplicationHelper::instance()->palette(this);
    //pb.setBrush(DPalette::Background, pb.color(DPalette::Window));
    pb.setBrush(DPalette::Base, pb.color(DPalette::Window));
    this->setPalette(pb);

    if (nullptr != m_PushButton) {

    }
    if (nullptr != m_Text) {
        DPalette pa = DApplicationHelper::instance()->palette(m_Text);
        pa.setBrush(DPalette::WindowText, pa.color(DPalette::TextTips));
        m_Text->setPalette(pa);
    }
    if (nullptr != m_Image) {
        switch (themeType) {
        case DGuiApplicationHelper::LightType:
            m_Image->setPixmap(UiUtil::renderSVG(":/image/icon/icon_import_note.svg", QSize(m_Image->width(), m_Image->height()), Intancer::get_Intancer()->getApp()));
            break;
        case DGuiApplicationHelper::DarkType:
            m_Image->setPixmap(UiUtil::renderSVG(":/image/icon_dark/icon_import_note.svg", QSize(m_Image->width(), m_Image->height()), Intancer::get_Intancer()->getApp()));
            break;
        }
    }

}

void InitEmptyPage::resizeEvent(QResizeEvent *event)
{
    DFrame::resizeEvent(event);
    checkPos();
}

void InitEmptyPage::init()
{
    m_PushButton = new DSuggestButton(QString(tr("Create Notebook")), this);
    //m_PushButton = new DSuggestButton(QString(tr("新建记事本")),this);
    m_PushButton->setFixedSize(QSize(302, 36));
//    m_PushButton->setFont(DFontSizeManager::instance()->get(DFontSizeManager::T6));
    DFontSizeManager::instance()->bind(m_PushButton, DFontSizeManager::T6);
    m_Image = new DLabel(this);
    m_Image->setFixedSize(QSize(128, 128));


    m_Text = new DLabel(this);
    //m_Text->resize(QSize(240,18));
    //m_Text->setFixedSize(QSize(240,18));
    m_Text->setFixedSize(QSize(500, 18));
    m_Text->setText(QString(tr("Create a notebook to start recording voice and making notes")));
    m_Text->setAlignment(Qt::AlignCenter);
    //m_Text->setFont(DFontSizeManager::instance()->get(DFontSizeManager::T8));
    DFontSizeManager::instance()->bind(m_Text, DFontSizeManager::T8);
    m_Text->setForegroundRole(DPalette::TextTips);
    this->setLineWidth(0);
    onChangeColor();
    checkPos();
}

void InitEmptyPage::initConnect()
{
    connect(m_PushButton, SIGNAL(clicked()), this, SIGNAL(sigAddFolderByInitPage()));
    connect(DApplicationHelper::instance(), &DApplicationHelper::themeTypeChanged, this, &InitEmptyPage::onChangeColor);
}

void InitEmptyPage::checkPos()
{
    m_PushButton->move((this->width() - m_PushButton->width()) / 2, (this->height() - m_PushButton->height()) / 2 + 5);
    m_Image->move((this->width() - m_Image->width()) / 2, m_PushButton->y() - m_Image->height() - 15);
    m_Text->move((this->width() - m_Text->width()) / 2, m_PushButton->y() + m_PushButton->height() + 20);
}
