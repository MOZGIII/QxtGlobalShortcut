#ifndef WIDGET_H
#define WIDGET_H

#include <QObject>
#include <QWidget>
#include "qxtglobalshortcut.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void shortcutActivated();

private:
    QxtGlobalShortcut *m_globalShortcut;
};

#endif // WIDGET_H
