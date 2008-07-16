/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtDesigner module of the Qxt library.
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of the Common Public License, version 1.0, as published by
** IBM.
**
** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
** FITNESS FOR A PARTICULAR PURPOSE.
**
** You should have received a copy of the CPL along with this file.
** See the LICENSE file and the cpl1.0.txt file included with the source
** distribution for more information. If you did not receive a copy of the
** license, contact the Qxt Foundation.
**
** <http://libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/

#ifndef QXTCOUNTRYCOMBOBOX_P_H
#define QXTCOUNTRYCOMBOBOX_P_H

#include "qxtcountrycombobox.h"
#include "qxtpimpl.h"
#include <QComboBox>

class QxtCountryComboBoxPrivate : public QObject, public QxtPrivate<QxtCountryComboBox>
{
    Q_OBJECT
public:
    QXT_DECLARE_PUBLIC(QxtCountryComboBox);

public:
    explicit QxtCountryComboBoxPrivate();

    QLocale::Country currentCountry() const;
    QString currentCountryName() const;

public slots:
    void setCurrentCountry(QLocale::Country country);
    void comboBoxCurrentIndexChanged(int index);
};


#endif  // QXTCOUNTRYCOMBOBOX_P_H
