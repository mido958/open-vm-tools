/*********************************************************
 * Copyright (C) 2009 VMware, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2 and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
 *********************************************************/

/*
 * vmci_sockets_int.h --
 *
 *    VMCI sockets private constants and types.
 *
 *    This file is internal only, we do not ship the kernel interface yet.
 *    You need to include this file *before* vmci_sockets.h in your kernel
 *    module.
 */

#ifndef _VMCI_SOCKETS_INT_H_
#define _VMCI_SOCKETS_INT_H_

#include "vm_basic_types.h"

#if defined(_WIN32)
#  if defined(_DDK_DRIVER_)
      /*
       * WinSockKernel is targetted at Vista and later.  We want to allow
       * drivers built from W2K onwards to work with the interface.  Until we
       * find a better way, these hacks are necessary.
       */
      typedef unsigned short u_short;
#     include <windef.h>
#     include <ws2def.h>
      typedef WSACMSGHDR CMSGHDR, *PCMSGHDR;
#     include <wsk.h>
      NTSTATUS VMCISock_WskRegister(PWSK_CLIENT_NPI wskClientNpi,
                                    PWSK_REGISTRATION wskRegistration);
      NTSTATUS VMCISock_WskDeregister(PWSK_REGISTRATION wskRegistration);
      NTSTATUS VMCISock_WskCaptureProviderNPI(PWSK_REGISTRATION wskRegistration,
                                              ULONG waitTimeout,
                                              PWSK_PROVIDER_NPI wskProviderNpi);
      NTSTATUS VMCISock_WskReleaseProviderNPI(PWSK_REGISTRATION wskRegistration);
      NTSTATUS VMCISock_WskGetAFValue(PWSK_CLIENT wskClient, PIRP irp);
      NTSTATUS VMCISock_WskGetLocalCID(PWSK_CLIENT wskClient, PIRP irp);
#  endif // _DDK_DRIVER_
#endif // _WIN32


#if defined(__APPLE__) && !defined(KERNEL)
#  include <sys/socket.h>
#endif // __APPLE__ && !KERNEL
#define VMCISock_socket(_domain, _type, _protocol) socket(_domain, _type, _protocol)
#define VMCISock_bind(_socket, _address, _address_len) bind(_socket, _address, _address_len)
#define VMCISock_listen(_socket, _backlog) listen(_socket, _backlog)
#define VMCISock_accept(_socket, _address, _address_len) accept(_socket, _address, _address_len)
#define VMCISock_getsockname(_socket, _address, _address_len) getsockname(_socket, _address, _address_len)
#define VMCISock_connect(_socket, _address, _address_len) connect(_socket, _address, _address_len)
#define VMCISock_send(_socket, _buffer, _length, _flags) send(_socket, _buffer, _length, _flags)
#define VMCISock_recv(_socket, _buffer, _length, _flags) recv(_socket, _buffer, _length, _flags)
#define VMCISock_sendto(_socket, _buffer, _length, _flags, _dest_addr, _dest_len) sendto(_socket, _buffer, _length, _flags, _dest_addr, _dest_len)
#define VMCISock_recvfrom(_socket, _buffer, _length, _flags, _address, _address_len) recvfrom(_socket, _buffer, _length, _flags, _address, _address_len)
#define VMCISock_getpeername(_socket, _address, _address_len) getpeername(_socket, _address, _address_len)
#define VMCISock_writev(_socket, _iov, _iovcount) writev(_socket, _iov, _iovcount)
#define VMCISock_close(_socket) close(_socket)


#endif // _VMCI_SOCKETS_INT_H_

