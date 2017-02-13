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
#include <QVBoxLayout>

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

void TestUDisksClientGui::comboTextChanged(QComboBox *combo, QString text, QTableWidget *table) 
{
    table->clearContents();

    QDBusObjectPath tblPath = QDBusObjectPath("/org/freedesktop/UDisks2/block_devices/" + text.mid(5));
    qDebug() << tblPath.path();
    int row = 0;
    for (const UDisksObject::Ptr partPtr : m_UDisksClient->getPartitions(tblPath)) {
        UDisksPartition *part = partPtr->partition();
        qDebug() << text + QString::number(part->number()) << part->size() / 1073741824.0 << part->type();
        table->insertRow(row);
        auto *item = new QTableWidgetItem(text + QString::number(part->number()));
        table->setItem(row, 0, item);
        item = new QTableWidgetItem(QString::number(part->size() / 1073741824.0));
        table->setItem(row, 1, item);
        row++;
    }

    UDisksObject::Ptr blkPtr = m_UDisksClient->getObject(tblPath);
    Q_ASSERT(blkPtr != nullptr);
    
    UDisksBlock *blk = blkPtr->block();
    Q_ASSERT(blk != nullptr);

    UDisksObject::Ptr drvPtr = blk->driveObjectPtr();
    Q_ASSERT(drvPtr != nullptr);

    UDisksDrive *drv = drvPtr->drive();
    Q_ASSERT(drv != nullptr);
    combo->setToolTip(drv->id());
}

void TestUDisksClientGui::getDriveObjects(QComboBox *combo, QTableWidget *table) 
{
    combo->clear();
    for (const UDisksObject::Ptr drvPtr : m_UDisksClient->getObjects(UDisksObject::Drive)) {
        qDebug() << drvPtr->path().path();
        UDisksDrive *drv = drvPtr->drive();
        if (drv == nullptr)
            continue;
        qDebug() << "drv:--->" << drv->id() << drv->size() << 
            drv->opticalNumAudioTracks() << drv->opticalNumDataTracks() << 
            drv->opticalNumSessions() << drv->opticalNumTracks() << 
            drv->revision() << drv->seat() << drv->serial();
        UDisksBlock *blk = drv->getBlock();
        if (blk == nullptr)
            continue;
        qDebug() << "blk:------>" << blk->device() << blk->deviceNumber() << 
            blk->id() << blk->preferredDevice() << blk->symlinks();
        combo->addItem(blk->preferredDevice());
    }
    connect(combo, &QComboBox::currentTextChanged, [=](const QString &text) {
        comboTextChanged(combo, text, table);
    });
    comboTextChanged(combo, combo->currentText(), table);
}

void TestUDisksClientGui::testGetDriveObjects() 
{
    m_UDisksClient->init();

    auto *dlg = new QDialog;
    auto *vbox = new QVBoxLayout(dlg);
    auto *combo = new QComboBox;
    auto *table = new QTableWidget;
    table->setColumnCount(2);
    vbox->addWidget(combo);
    vbox->addWidget(table);

    connect(m_UDisksClient, &UDisksClient::objectAdded, [=](const UDisksObject::Ptr &object) {
        getDriveObjects(combo, table);
    });

    connect(m_UDisksClient, &UDisksClient::objectRemoved, [=](const UDisksObject::Ptr &object) {
        getDriveObjects(combo, table);
    });

    connect(m_UDisksClient, &UDisksClient::objectsAvailable, [=]() {
        getDriveObjects(combo, table);
    });

    dlg->exec();
}
