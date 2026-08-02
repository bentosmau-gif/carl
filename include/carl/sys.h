
#ifndef CARL_SYS_H
#define CARL_SYS_H

#include <stdint.h>
#include <stddef.h>

typedef int32_t   BOOL;
typedef int32_t   HANDLE;
typedef uint32_t  DWORD;
typedef void*     LPVOID;
typedef const char* LPCSTR;

#define TRUE  1
#define FALSE 0
#define INVALID_HANDLE (-1)


HANDLE c_OpenFile(LPCSTR path, DWORD flags);
DWORD  c_ReadFile(HANDLE file, LPVOID buffer, DWORD size);
DWORD  c_WriteFile(HANDLE file, const void* buffer, DWORD size);
BOOL   c_CloseHandle(HANDLE h);

LPVOID c_VirtualAlloc(size_t size);
BOOL   c_VirtualFree(LPVOID addr);

HANDLE c_CreateProcess(LPCSTR path, LPCSTR args);
BOOL   c_TerminateProcess(HANDLE process, DWORD exitCode);
DWORD  c_GetProcessId(HANDLE process);

typedef void (*c_ThreadFunc)(LPVOID param);

HANDLE c_CreateThread(c_ThreadFunc func, LPVOID param);
BOOL   c_TerminateThread(HANDLE thread, DWORD exitCode);
void   c_Sleep(DWORD ms);

DWORD c_GetTickCount(void);

HANDLE c_CreateMutex(void);
BOOL   c_LockMutex(HANDLE mutex);
BOOL   c_UnlockMutex(HANDLE mutex);

void c_DebugPrint(LPCSTR msg);

#endif // CARL_SYS_H
