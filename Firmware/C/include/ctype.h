/*
** ctype.h
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

#ifndef _is_ctype__
#define _is_ctype__

#define CTYPE_VERSION_STRING "2.0.2"

#define CTYPE_ASM

int isalnum(int c);
int isalpha(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);

#endif
