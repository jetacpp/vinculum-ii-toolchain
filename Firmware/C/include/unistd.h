/*
** unistd.h
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

#ifndef UNISTD_H
#define UNISTD_H

#define UNISTD_VERSION_STRING "2.0.2"

#include "vos.h"
#include "config.h"
#include "errno.h"
#include "FAT.h"

int chdir(const char *);

#endif
