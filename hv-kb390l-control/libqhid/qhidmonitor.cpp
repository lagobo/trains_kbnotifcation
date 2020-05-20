/*
 *      Copyright 2018 Pavel Bludov <pbludov@gmail.com>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License along
 *      with this program; if not, write to the Free Software Foundation, Inc.,
 *      51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "qhidmonitor.h"
#if defined(WITH_LIBUSB_1_0)
#include "qhidmonitor_libusb.h"
#elif defined(WITH_LIBUDEV)
#include "qhidmonitor_udev.h"
#elif defined(Q_OS_WIN32)
#include "qhidmonitor_win32.h"
#endif

QHIDMonitor::QHIDMonitor(int vendorId, int deviceId, QObject *parent)
    : QObject(parent)
    , d_ptr(new QHIDMonitorPrivate(this, vendorId, deviceId))
{
}

QHIDMonitor::~QHIDMonitor()
{
    d_ptr->q_ptr = nullptr;
    delete d_ptr;
    d_ptr = nullptr;
}
