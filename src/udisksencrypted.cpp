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

#include "udisksencrypted.h"
#include "udisksencrypted_p.h"

#include "common.h"

#include <QDebug>

UDisksEncrypted::UDisksEncrypted(const QDBusObjectPath &objectPath, const QVariantMap &properties, UDisksObject *parent) :
    UDisksInterface(parent),
    d_ptr(new UDisksEncryptedPrivate(objectPath.path()))
{
    Q_D(UDisksEncrypted);

    d->properties = properties;
}

UDisksEncrypted::~UDisksEncrypted()
{
    delete d_ptr;
}

QDBusPendingReply<> UDisksEncrypted::changePassphrase(const QString &passphrase, const QString &newPassphrase, const QVariantMap &options)
{
    Q_D(UDisksEncrypted);
    return d->interface.ChangePassphrase(passphrase, newPassphrase, options);
}

QDBusPendingReply<> UDisksEncrypted::lock(const QVariantMap &options)
{
    Q_D(UDisksEncrypted);
    return d->interface.Lock(options);
}

QDBusPendingReply<QDBusObjectPath> UDisksEncrypted::unlock(const QString &passphrase, const QVariantMap &options)
{
    Q_D(UDisksEncrypted);
    return d->interface.Unlock(passphrase, options);
}

void UDisksEncrypted::propertiesChanged(const QVariantMap &properties, const QStringList &invalidProperties)
{
    Q_D(UDisksEncrypted);
    changeProperties(d->properties, properties, invalidProperties);
}

UDisksEncryptedPrivate::UDisksEncryptedPrivate(const QString &path) :
    interface(QLatin1String(UD2_SERVICE), path, QDBusConnection::systemBus())
{
}
