/*
** USBPrinter.h
**
** Copyright © 2010-2011 Future Technology Devices International Limited
**
** THIS SOFTWARE IS PROVIDED BY FUTURE TECHNOLOGY DEVICES INTERNATIONAL LIMITED
** ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL FUTURE TECHNOLOGY DEVICES
** INTERNATIONAL LIMITED BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
** OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
** STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
** OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
** DAMAGE.
**
** Header file containing definitions for Vinculum II Host Printer Driver
** Used internally by the Printer driver only
**
** Author: FTDI
** Project: Vinculum II
** Module: Vinculum II USB Host Printer Driver
** Requires: VOS
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef __USBHOSTPRINTER_H__
#define __USBHOSTPRINTER_H__

#define USBHOSTPRINTER_VERSION_STRING "2.0.2"

enum USBHOSTPRINTER_STATUS
{
    USBHOSTPRINTER_OK = 0,
    USBHOSTPRINTER_INVALID_PARAMETER,
    USBHOSTPRINTER_ERROR,
    USBHOSTPRINTER_NOT_FOUND,
    USBHOSTPRINTER_USBHOST_ERROR = 0x80,
    USBHOSTPRINTER_FATAL_ERROR = 0xFF
};

#define VOS_IOCTL_USBHOSTPRINTER_ATTACH		   1
#define VOS_IOCTL_USBHOSTPRINTER_DETACH		   2
#define VOS_IOCTL_USBHOSTPRINTER_GET_DEVICE_ID 3
#define VOS_IOCTL_USBHOSTPRINTER_PORT_STATUS   4
#define VOS_IOCTL_USBHOSTPRINTER_SOFT_RESET	   5

// USBPrinter IOCTL attach structure
typedef struct _usbHostPrinter_ioctl_cb_attach_t
{
    VOS_HANDLE				 hc_handle;
    usbhost_device_handle_ex ifDev;
} usbHostPrinter_ioctl_cb_attach_t;

// USBPrinter IOCTL structure
typedef struct _usbHostPrinter_ioctl_t
{
    unsigned char ioctl_code;
    union
    {
        unsigned char					 *data;
        usbHostPrinter_ioctl_cb_attach_t *att;
    } set;
    union
    {
        unsigned char *data;
    } get;
} usbHostPrinter_ioctl_t;

unsigned char usbHostPrinter_init(unsigned char vos_dev_num);

#endif                                 /* __USBHOSTPRINTER_H__ */
