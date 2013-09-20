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

#ifndef UDISKS_MANAGER_H
#define UDISKS_MANAGER_H

#include <QtCore/QObject>
#include <QtCore/QMetaEnum>
#include <QtDBus/QDBusError>
#include <QtDBus/QDBusObjectPath>

#include "dbus-types.h"

/**
 * \class Manager Manager.h Manager
 * \author Daniel Nicoletti \e <dantti12@gmail.com>
 *
 * \brief Base class used to interact with the UDisks daemon
 *
 * This class holds all the functions enabling the user to interact with the UDisks daemon.
 *
 * This class is a singleton, its constructor is private. Call UDisksManager::global() to get
 * an instance of the UDisksManager object, you only need UDisksManager::global()
 * when connecting to the signals of this class.
 */
class QDBusPendingCallWatcher;
class UDisksManagerPrivate;
class UDisksManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString version READ version NOTIFY versionChanged)
public:
    /**
     * \brief Returns an instance of the Manager
     *
     * The UDisksManager class is a singleton, you can call this method several times,
     * a single UDisksManager object will exist.
     * Use this only when connecting to this class signals
     */
    static UDisksManager* global();

    /**
     * Destructor
     */
    ~UDisksManager();

    /**
     * The daemon version
     */
    QString version() const;

    /**
     * Creates a block device for the file represented by \p fd.
     *
     * Returns a Block::Ptr
     */
//    Block::Ptr loopSetup(int fileDescriptor);

    /**
     * Creates a new RAID array on the block devices specified by
     * @blocks. Each element in this array must be an object path to
     * an object implementing the #org.freedesktop.UDisks2.Block
     * interface.
     *
     * \p blocks: An array of object paths to objects implementing the #org.freedesktop.UDisks2.Block interface.
     * \p level: The RAID level for the array.
     * \p name: The name for the array.
     * \p chunk: The chunk size (in bytes) or 0 if @level is <quote>raid1</quote>.
     * \p options: Options (currently unused except for <link linkend="udisks-std-options">standard options</link>).
     * returns an MDRaid object
     */
//    MDRaid::Ptr MDRaidCreate(const QStringList &blocks, const QString &level, const QString &name, qulonglong chunk, const QVariantMap &options);

Q_SIGNALS:
    /**
     * This signal is emitted when a version of the daemon changes.
     */
    void versionChanged();

private Q_SLOTS:
    void serviceOwnerChanged(const QString &service, const QString &oldOwner, const QString &newOwner);
    void callFinishedSlot(QDBusPendingCallWatcher *call);
    void proccessObject(const QDBusObjectPath &objectPath, UDVariantMapMap interfacesAndProperties);

private:
    UDisksManagerPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(UDisksManager)
//    Q_PRIVATE_SLOT(d_ptr, void _q_proccessObject())

    UDisksManager(QObject *parent = 0);
    static UDisksManager *m_global;
};

#endif // UDISKS_MANAGER_H
