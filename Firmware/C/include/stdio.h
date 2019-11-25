/*
** stdio.h
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

#ifndef STDIO_H
#define STDIO_H

#define STDIO_VERSION_STRING "2.0.2"

#include "vos.h"
#include "config.h"
#include "errno.h"
#include "FAT.h"

#define SEEK_SET	 2
#define SEEK_CUR	 0
#define SEEK_END	 1

// 8.3 filenames
#define FILENAME_MAX 11

typedef file_context_t FILE;

#define stdin		 ((FILE *) 0)
#define stdout		 ((FILE *) 1)
#define stderr		 ((FILE *) 2)

// attach stdin, stdout, stderr to a device handle
// it is not possible to attach file systems to stdio
int stdioAttach(VOS_HANDLE);
// attach individual streams to separate handles
int stdinAttach(VOS_HANDLE);
int stdoutAttach(VOS_HANDLE);
int stderrAttach(VOS_HANDLE);
// attach file system to a
int fsAttach(VOS_HANDLE);

// write to stdout
int printf(const char *fmt, ...);

// file input/output
FILE *fopen(const char *, const char *);
int fclose(FILE *);
int feof(FILE *);
int ftell(FILE *);
int fseek(FILE *, long offset, int whence);
int fflush(FILE *);
// in the following functions FILE pointers may be stdin, stdout and stderr
int fprintf(FILE *, const char *fmt, ...);
size_t fread(void *, size_t, size_t, FILE *);
size_t fwrite(const void *, size_t, size_t, FILE *);
int remove(const char *);
int rename(const char *, const char *);
void rewind(FILE *);

// character based file input/output
int getchar();
int putchar(int);
int fgetc(FILE *);
int fputc(int, FILE *);
// macros for putc and getc to map to stdin and stdout
#define putc(A) fputc(A, stdout)
#define getc()	fgetc(stdin)

// string functions
int sprintf(char *, const char *fmt, ...);

// to be added
char *fgets(char *, int, FILE *);
int fputs(const char *, FILE *);
int fgetpos(FILE *, long *);
int fsetpos(FILE *, const long *);
#endif
