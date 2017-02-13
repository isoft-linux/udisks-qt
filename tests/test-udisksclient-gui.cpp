/*
 * Copyright (C) 2017 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * See the file "COPYING" for the exact licensing terms.
 */

#include <QtTest/QTest>
#include <QDebug>
#include <QDialog>

#include "test-udisksclient-gui.h"
#include "udisksobject.h"
#include "udisksdrive.h"
#include "udisksblock.h"
#include "udiskspartition.h"

QTEST_MAIN(TestUDisksClientGui)

TestUDisksClientGui::TestUDisksClientGui()
{
    m_UDisksClient = new UDisksClient;
}

TestUDisksClientGui::~TestUDisksClientGui() 
{
    if (m_UDisksClient) {
        delete m_UDisksClient;
        m_UDisksClient = nullptr;
    }
}

void TestUDisksClientGui::testGetDriveObjects() 
{
    m_UDisksClient->init();

    auto *dlg = new QDialog;

    connect(m_UDisksClient, &UDisksClient::objectsAvailable, [this](){
    for (const UDisksObject::Ptr drvPtr : m_UDisksClient->getObjects(UDisksObject::Drive)) {
        qDebug() << drvPtr->path().path();
        UDisksDrive *drv = drvPtr->drive();
        if (drv == nullptr)
            continue;
        qDebug() << drv->id() << drv->size() << drv->opticalNumAudioTracks() << 
            drv->opticalNumDataTracks() << drv->opticalNumSessions() << 
            drv->opticalNumTracks() << drv->revision() << drv->seat() << 
            drv->serial();
        UDisksBlock *blk = drv->getBlock();
        if (blk == nullptr)
            continue;
        qDebug() << blk->device() << blk->deviceNumber() << blk->id() << 
            blk->preferredDevice() << blk->symlinks();
        QDBusObjectPath tblPath = QDBusObjectPath("/org/freedesktop/UDisks2/block_devices/" + QString(blk->device()).mid(5)); // /dev
        qDebug() << tblPath.path();
        for (const UDisksObject::Ptr partPtr : m_UDisksClient->getPartitions(tblPath)) {
            UDisksPartition *part = partPtr->partition();
            qDebug() << part->number() << part->size() << part->type();
        }
    }
    });

    dlg->exec();
}
