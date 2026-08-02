#ifndef CARL_FS_H
#define CARL_FS_H

/* File Operations */

int OpenFile(const char* path);
int CreateFile(const char* path);
int DeleteFile(const char* path);
int CloseFile(int handle);

/* Directory Operations */
int CreateDirectory(const char* path);
int RemoveDirectory(const char* path);

/* File Information */
int GetFileSize(const char* path);
int FileExists(const char* path);