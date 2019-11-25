/*
** string.h
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

#ifndef _STRING_H
#define _STRING_H

#define STRING_VERSION_STRING "2.0.2"

#include "config.h"
#include "errno.h"

extern void *memcpy(void *destination, const void *source, size_t num);
extern void *memset(void *dstptr, int value, size_t num);
extern int strcmp(const char *str1, const char *str2);
extern int strncmp(const char *str1, const char *str2, size_t num);
extern char *strcpy(char *destination, const char *source);
extern char *strncpy(char *destination, const char *source, size_t num);
extern char *strcat(char *destination, const char *source);
extern size_t strlen(const char *str);

#endif                                 /* _STRING_H */

