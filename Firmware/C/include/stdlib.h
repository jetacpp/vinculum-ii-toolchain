/*
** stdlib.h
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

#ifndef STDLIB_H
#define STDLIB_H

#define STDLIB_VERSION_STRING "2.0.2"

#include "vos.h"
#include "config.h"
#include "errno.h"
#define NULL 0

int initHeap();
int abs(int);
long strtol(const char *nptr, char **endptr, int base);
int atoi(const char *nptr);
long atol(const char *nptr);
void *malloc(size_t size);
void *calloc(size_t nmem, size_t size);
void free(void *);
char *itoa(int value, char *string, int radix);
char *ltoa(long value, char *string, int radix);

#endif                                 /* STDLIB_H */
