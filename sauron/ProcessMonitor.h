#include <windows.h>

// LOG_IMAGE_TTL_MS en ms (3600000 = 1h)
#define LOG_IMAGE_TTL_MS 3600000

// LOG_IMAGE_TIMEOUT_MS en ms (3600000 = 1h)
#define LOG_IMAGE_TIMEOUT_MS 3600000

#define PROCESS_MONITOR_NAME "ProcessMonitor"
#define PROCESS_MONITOR_DEVICE_NAME  "\\\\.\\ProcessMonitor"

#define FILE_DEVICE_EVENT  0x8000

#define IOCTL_PROCESS_PASSEVENT \
    CTL_CODE(FILE_DEVICE_EVENT, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_PROCESS_PASSBUF \
    CTL_CODE(FILE_DEVICE_EVENT, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_IMAGE_PASSEVENT \
    CTL_CODE(FILE_DEVICE_EVENT, 0x804, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_IMAGE_PASSBUF \
    CTL_CODE(FILE_DEVICE_EVENT, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_CAPTURE_GET_PROCINFO	CTL_CODE(0x00000022, 0x0802, METHOD_NEITHER, FILE_READ_DATA | FILE_WRITE_DATA)
#define IOCTL_CAPTURE_PROC_LIST    CTL_CODE(0x00000022, 0x0807, METHOD_NEITHER, FILE_READ_DATA | FILE_WRITE_DATA)

void InitializeProcessMonitor(void);
DWORD WINAPI ProcessMonitorThread(LPVOID);

typedef struct _ProcessInfo
{
	//TIME_FIELDS time;
	LARGE_INTEGER time;
	HANDLE  ParentId;
	HANDLE  ProcessId;
	BOOLEAN bCreate;
	UINT processPathLength;
	WCHAR processPath[1024];
	UCHAR ParentSID[SECURITY_MAX_SID_SIZE];
	UCHAR ProcessSID[SECURITY_MAX_SID_SIZE];
	struct _ProcessInfo *next;
} ProcessInfo;
