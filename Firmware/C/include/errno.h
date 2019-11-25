/*
** errno.h
**
** Copyright (C) 2009 Future Technolgy Devices International Limited
**
**
** Project: Tool Chain
** Module: VII Library
** Requires:
** Comments:
**
** History:
**  1  initial version
*/

#ifndef ERRNO_H
#define ERRNO_H

#define ERRNO_VERSION_STRING "2.0.2"

#define errno				 _errno()

#define ERANGE				 1         /* Math result not representable */

#endif /* ERRNO_H */
