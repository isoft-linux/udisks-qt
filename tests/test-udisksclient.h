/*
 * Copyright (C) 2017 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * See the file "COPYING" for the exact licensing terms.
 */

#ifndef TEST_UDISKSCLIENT_H
#define TEST_UDISKSCLIENT_H

#include <QtCore/QObject>

#include "udisksclient.h"

class TestUDisksClient : public QObject
{
    Q_OBJECT

public:
    TestUDisksClient();
    ~TestUDisksClient();

private slots:
    void testGetObjects();

private:
    UDisksClient *m_UDisksClient = nullptr;
};

#endif // TEST_UDISKSCLIENT_H
