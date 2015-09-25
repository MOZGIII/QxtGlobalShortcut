#include "Widget.h"

#include <QKeySequence>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    m_globalShortcut(new QxtGlobalShortcut(QKeySequence("Shift+F1"), this))
{
    QObject::connect(m_globalShortcut, SIGNAL(activated()), this, SLOT(shortcutActivated()));

    setWindowTitle(QString("Press %1").arg(m_globalShortcut->shortcut().toString()));
}

Widget::~Widget()
{
    if(m_globalShortcut) {
        m_globalShortcut->deleteLater();
    }
}

void Widget::shortcutActivated()
{
    activateWindow();
    QMessageBox::critical(this, "Shortcut activated!", QString("You pressed %1").arg(m_globalShortcut->shortcut().toString()));
}
