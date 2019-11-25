/*
** stdarg.h
**
** Copyright (C) 2009 Future Technolgy Devices International Limited
**
** Project: Tool Chain
** Module: VII Library
** Requires:
** Comments:
**
** History:
**  1  initial version
*/

#ifndef STDARG_H
#define STDARG_H

typedef short va_list;

#define va_start(ap, v) (ap = (va_list) & v + sizeof(v))
#define va_arg(ap, t)	(*(t *) ((ap += sizeof(int)) - sizeof(int)))
#define va_end(ap)		(ap = (va_list) 0)

#endif                                 /* STDARG_H */

