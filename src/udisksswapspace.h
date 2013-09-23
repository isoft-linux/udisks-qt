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

#ifndef UDISKSSWAPSPACE_H
#define UDISKSSWAPSPACE_H

#include <QObject>

#include "dbus-types.h"

class UDisksSwapspacePrivate;
class UDisksSwapspace : public QObject
{
    Q_OBJECT
public:
    explicit UDisksSwapspace(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties, QObject *parent = 0);

    Q_PROPERTY(bool active READ active)
    bool active() const;

protected:
    UDisksSwapspacePrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(UDisksSwapspace)
};

#endif // UDISKSSWAPSPACE_H
