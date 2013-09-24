/*
 * Copyright (C) 2013 Daniel Nicoletti <dantti12@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "udiskspartitiontable.h"
#include "udiskspartitiontable_p.h"

#include "common.h"

#include <QDebug>

UDisksPartitionTable::UDisksPartitionTable(const QDBusObjectPath &objectPath, const QVariantMap &properties, QObject *parent) :
    QObject(parent),
    d_ptr(new UDisksPartitionTablePrivate(objectPath.path()))
{
    Q_D(UDisksPartitionTable);

    d->properties = properties;
}

UDisksPartitionTable::~UDisksPartitionTable()
{
    delete d_ptr;
}

QString UDisksPartitionTable::type() const
{
    Q_D(const UDisksPartitionTable);
    return d->properties[QLatin1String("Type")].toString();
}

UDisksPartitionTablePrivate::UDisksPartitionTablePrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}
