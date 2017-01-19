/*
 * Copyright (C) 2017 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * See the file "COPYING" for the exact licensing terms.
 */

#include "test-udisksclient.h"

#include <QtTest/QTest>
#include <QDebug>

QTEST_GUILESS_MAIN(TestUDisksClient)

TestUDisksClient::TestUDisksClient()
{
    m_UDisksClient = new UDisksClient;
    m_UDisksClient->init(false);
}

TestUDisksClient::~TestUDisksClient() 
{
    if (m_UDisksClient) {
        delete m_UDisksClient;
        m_UDisksClient = nullptr;
    }
}

void TestUDisksClient::testGetObjects()
{
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << m_UDisksClient->getObjects();
}
