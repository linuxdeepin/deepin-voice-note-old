#include "menubutton.h"
#include <DStyleOptionButton>
#include <DApplicationHelper>
#include <QDebug>
DWIDGET_USE_NAMESPACE

MenuButton::MenuButton(QWidget *parent) : DFloatingButton(parent)
{

}

MenuButton::MenuButton(QStyle::StandardPixmap iconType , QWidget *parent): DFloatingButton(iconType , parent)
{

}

MenuButton::MenuButton(DStyle::StandardPixmap iconType, QWidget *parent ):DFloatingButton(iconType , parent)
{

}

MenuButton::MenuButton(const QString &text, QWidget *parent):DFloatingButton(text , parent)
{

}

void MenuButton::initStyleOption(DStyleOptionButton *option) const
{
    DFloatingButton::initStyleOption(option);
    DPalette pa;
    DApplicationHelper::instance()->palette(this);
    //pa.setBrush(DPalette::Highlight, pa.color(DPalette::Base));
    //pa.setBrush(DPalette::Highlight, QColor(255,0,0,255));
    pa.setBrush(DPalette::Highlight, pa.color(DPalette::TextWarning));
    option->palette = pa;
}
