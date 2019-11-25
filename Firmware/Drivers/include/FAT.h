/*
** FAT.h
**
** Copyright © 2009-2011 Future Technology Devices International Limited
**
** Header file containing definitions for Vinculum II FAT File System Drivers
**
** Author: FTDI
** Project: Vinculum II Layered Drivers
** Module: Vinculum II FAT File System Driver
** Requires: vos.h boms.h usb.h usbhost.h
** Comments:
**
** History:
**  1 – Initial version
**
*/

#ifndef FAT_H
#define FAT_H

#define FAT_VERSION_STRING "2.0.2"

#define NULL			   0

#define FAT_ROOT_DIR	   0

enum FAT_STATUS {
    FAT_OK = 0,
    FAT_NOT_FOUND,
    FAT_READ_ONLY,
    FAT_PENDING,
    FAT_INVALID_PARAMETER,
    FAT_INVALID_BUFFER,
    FAT_INVALID_FILE_TYPE,
    FAT_EXISTS,
    FAT_BPB_INVALID,
    FAT_NOT_OPEN,
    FAT_EOF,
    FAT_DIRECTORY_TABLE_FULL,
    FAT_DISK_FULL,
    FAT_ERROR,
    FAT_MSI_ERROR = 0x80,
    FAT_FATAL_ERROR = 0xff,
};

// context pointer for instance of FAT file system
typedef void *fat_context;

// context pointer for file instance
typedef struct _file_context_t
{
    // copy of the directory entry for the file
    unsigned char dirEntry[32];

    // open mode (read/write/append/overwrite)
    unsigned char mode;

    unsigned char context[34];
} file_context_t;

// File attributes:
#define FAT_ATTR_READ_ONLY		0x01
#define FAT_ATTR_HIDDEN			0x02
#define FAT_ATTR_SYSTEM			0x04
#define FAT_ATTR_VOLUME_ID		0x08
#define FAT_ATTR_DIRECTORY		0x10
#define FAT_ATTR_ARCHIVE		0x20
#define FAT_ATTR_LONG_NAME		(FAT_ATTR_READ_ONLY | FAT_ATTR_HIDDEN | FAT_ATTR_SYSTEM | FAT_ATTR_VOLUME_ID)
#define FAT_ATTR_LONG_NAME_MASK (FAT_ATTR_LONG_NAME | FAT_ATTR_DIRECTORY | FAT_ATTR_ARCHIVE)

// file handle type to obtain
// obtain handle for file only (returned for a directory table find)
#define FILE_MODE_HANDLE		0x00
// update mode
#define FILE_MODE_PLUS			0x10
// r	(file pointer at SOF, read only)
#define FILE_MODE_READ			0x01
// w	(file pointer at SOF, write only, truncate to zero length)
#define FILE_MODE_WRITE			0x02
// a	(file pointer at EOF, write only)
#define FILE_MODE_APPEND		0x04
// r+	(file pointer at SOF, read or write)
#define FILE_MODE_READ_PLUS		(FILE_MODE_READ | FILE_MODE_PLUS)
// w+	(file pointer at SOF, read or write, truncate to zero length)
#define FILE_MODE_WRITE_PLUS	(FILE_MODE_WRITE | FILE_MODE_PLUS)
// a+	(file pointer at EOF, read or write)
#define FILE_MODE_APPEND_PLUS	(FILE_MODE_APPEND | FILE_MODE_PLUS)

// File system types
#define FAT12					0x12
#define FAT16					0x16
#define FAT32					0x32

// ---------------------------------------------------------------------------
// FAT Driver definitions

unsigned char fatdrv_init(unsigned char vos_dev_num);

typedef struct _fat_ioctl_cb_t {
    unsigned char  ioctl_code;
    // file context
    file_context_t *file_ctx;
    // read buffer
    unsigned char  *get;
    // write butter
    unsigned char  *set;
} fat_ioctl_cb_t;

typedef struct _fatdrv_ioctl_cb_attach_t
{
    // handle to initialised MSI device
    VOS_HANDLE	  msi_handle;
    // partition on BOMS device to use
    unsigned char partition;
} fatdrv_ioctl_cb_attach_t;

typedef struct _fatdrv_ioctl_cb_fs_t
{
    // file system type
    char		   fsType;
    // free space on disk in bytes
    unsigned int   freeSpaceH;
    unsigned int   freeSpaceL;
    // capacity of disk in bytes
    unsigned int   capacityH;
    unsigned int   capacityL;
    // number of bytes in a cluster
    unsigned int   bytesPerCluster;
    // number of bytes in a sector
    unsigned short bytesPerSector;
    // volume id
    unsigned long  volID;
} fatdrv_ioctl_cb_fs_t;

typedef struct _fatdrv_ioctl_cb_file_t
{
    // filename
    char *filename;
    // offset within file or size of file
    int	 offset;
    // access mode of file, seek mode or file attribute
    char mode;
} fatdrv_ioctl_cb_file_t;

typedef struct _fatdrv_ioctl_cb_dir_t
{
    char *filename;
} fatdrv_ioctl_cb_dir_t;

typedef struct _fatdrv_ioctl_cb_time_t
{
    // crtDate and crtTime used for set time and get time methods
    unsigned short crtDate;
    unsigned short crtTime;
    // wrtDate, wrtTime and accDate used for get time method only
    unsigned short wrtDate;
    unsigned short wrtTime;
    unsigned short accDate;
} fatdrv_ioctl_cb_time_t;

typedef struct _fat_stream_t {
    // file context
    file_context_t *file_ctx;
    // read/write buffer
    unsigned char  *buf;
    // length of buffer
    // maximum size of data to read or write
    unsigned long  len;
    unsigned long  actual;
} fat_stream_t;

#define FAT_IOCTL_FS_ATTACH			0x01
#define FAT_IOCTL_FS_DETACH			0x02
#define FAT_IOCTL_FS_INFO			0x03

#define FAT_IOCTL_FILE_OPEN			0x10
#define FAT_IOCTL_FILE_CLOSE		0x11
#define FAT_IOCTL_FILE_SEEK			0x12
#define FAT_IOCTL_FILE_SETPOS		0x13
#define FAT_IOCTL_FILE_TELL			0x14
#define FAT_IOCTL_FILE_REWIND		0x15
#define FAT_IOCTL_FILE_TRUNCATE		0x16
#define FAT_IOCTL_FILE_DELETE		0x17
#define FAT_IOCTL_FILE_RENAME		0x18
#define FAT_IOCTL_FILE_MOD			0x19
#define FAT_IOCTL_FILE_FLUSH		0x1A

#define FAT_IOCTL_DIR_CD			0x20
#define FAT_IOCTL_DIR_MK			0x21
#define FAT_IOCTL_DIR_FIND			0x22
#define FAT_IOCTL_DIR_FIND_FIRST	0x23
#define FAT_IOCTL_DIR_FIND_NEXT		0x24
#define FAT_IOCTL_DIR_SIZE			0x25
#define FAT_IOCTL_DIR_GETTIME		0x26
#define FAT_IOCTL_DIR_SETTIME		0x27
#define FAT_IOCTL_DIR_ISEMPTY		0x28
#define FAT_IOCTL_DIR_ISVALID		0x29
#define FAT_IOCTL_DIR_ISVOLUMELABEL 0x2a
#define FAT_IOCTL_DIR_ISREADONLY	0x2b
#define FAT_IOCTL_DIR_ISFILE		0x2c
#define FAT_IOCTL_DIR_ISDIRECTORY	0x2d
#define FAT_IOCTL_DIR_ISROOT		0x2e

// ---------------------------------------------------------------------------
// FAT API Definitions

void fat_init(void);
fat_context *fat_open(VOS_HANDLE hMsi, unsigned char partition, unsigned char *status);
void fat_close(fat_context *fat_ctx);
#define FAT_FREESPACE_NO_SCAN	 0
#define FAT_FREESPACE_SCAN		 1
#define FAT_FREESPACE_FORCE_SCAN 2
unsigned char fat_freeSpace(fat_context *fat_ctx, unsigned long *bytes_h, unsigned long *bytes_l, unsigned char scan);
VOS_HANDLE fat_getDevHandle(fat_context *fat_ctx);
unsigned char fat_capacity(fat_context *fat_ctx, unsigned long *bytes_h, unsigned long *bytes_l);
unsigned char fat_bytesPerCluster(fat_context *fat_ctx, unsigned long *bytes);
unsigned char fat_bytesPerSector(fat_context *fat_ctx, unsigned short *bytes);
unsigned char fat_getFSType(fat_context *fat_ctx);
unsigned char fat_getVolumeID(fat_context *fat_ctx, unsigned long *volID);
unsigned char fat_getVolumeLabel(fat_context *fat_ctx, char *volLabel);

// file IO
unsigned char fat_fileOpen(fat_context *fat_ctx, file_context_t *file_ctx, char *name, unsigned char mode);
unsigned char fat_fileClose(file_context_t *file_ctx);
#define FAT_SEEK_CUR 0
#define FAT_SEEK_END 1
#define FAT_SEEK_SET 2
unsigned char fat_fileSeek(file_context_t *file_ctx, long offset, unsigned char mode);
unsigned char fat_fileSetPos(file_context_t *file_ctx, unsigned long offset);
unsigned char fat_fileTell(file_context_t *file_ctx, unsigned long *offset);
unsigned char fat_fileRewind(file_context_t *file_ctx);
unsigned char fat_fileTruncate(file_context_t *file_ctx);
unsigned char fat_fileFlush(file_context_t *file_ctx);

unsigned char fat_fileRead(file_context_t *file_ctx, unsigned long length, char *buffer, VOS_HANDLE hOutput, unsigned long *bytes_read);
unsigned char fat_fileWrite(file_context_t *file_ctx, unsigned long length, char *buffer, VOS_HANDLE hOutput, unsigned long *bytes_written);

// delete file
// obtain file handle first with fat_fileOpen and FILE_MODE_HANDLE
unsigned char fat_fileDelete(file_context_t *source_file_ctx);

// copy file from source_file_ctx to current directory in fat_ctx - new name is dest_name if supplied
// obtain file handles first source file with FILE_MODE_READ and destinaiton with FILE_MODE_WRITE
unsigned char fat_fileCopy(file_context_t *source_file_ctx, file_context_t *dest_file_ctx);

// move file from source_file_ctx to current directory in fat_ctx - new name is dest_name if supplied
// obtain file handles first with fat_fileOpen and FILE_MODE_HANDLE
// Not yet implemented
// unsigned char fat_fileMove(file_context_t *source_file_ctx, file_context_t *dest_file_ctx);
unsigned char fat_fileRename(file_context_t *file_ctx, char *name);

// change attributes of a file
unsigned char fat_fileMod(file_context_t *file_ctx, unsigned char attr);

// change current time stamp - used for new/open/read/write etc
unsigned char fat_time(unsigned long time);

// directory table functions
unsigned char fat_dirTableFind(fat_context *fat_ctx, file_context_t *file_ctx, char *name);
unsigned char fat_dirTableFindFirst(fat_context *fat_ctx, file_context_t *file_ctx);
unsigned char fat_dirTableFindNext(fat_context *fat_ctx, file_context_t *file_ctx);

unsigned char fat_dirDirIsEmpty(file_context_t *file_ctx);
unsigned char fat_dirEntryIsValid(file_context_t *file_ctx);
unsigned char fat_dirEntryIsVolumeLabel(file_context_t *file_ctx);
unsigned char fat_dirEntryIsReadOnly(file_context_t *file_ctx);
unsigned char fat_dirEntryIsFile(file_context_t *file_ctx);
unsigned char fat_dirEntryIsDirectory(file_context_t *file_ctx);
unsigned long fat_dirEntrySize(file_context_t *file_ctx);
#define FAT_DIRENTRYTIME_CREATE_DATE 1
#define FAT_DIRENTRYTIME_CREATE_TIME 2
#define FAT_DIRENTRYTIME_MODIFY_DATE 3
#define FAT_DIRENTRYTIME_MODIFY_TIME 4
#define FAT_DIRENTRYTIME_ACCESS_DATE 5
unsigned short fat_dirEntryTime(file_context_t *file_ctx, unsigned char offset);
unsigned char fat_dirEntryName(file_context_t *file_ctx, char *fileName);

unsigned char fat_dirChangeDir(fat_context *fat_ctx, unsigned char *name);
unsigned char fat_dirCreateDir(fat_context *fat_ctx, unsigned char *name);
unsigned char fat_dirIsRoot(fat_context *fat_ctx);

#endif                                 /* FAT_H */
