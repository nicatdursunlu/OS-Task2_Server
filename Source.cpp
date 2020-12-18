#include <Windows.h>
#include <iostream>

using namespace std;
#define buf_size 1024

int main() {

	HANDLE FileMap;
	BOOL Result;
	PCHAR lpBuffer = NULL;
	char Buffer[buf_size] = "Hello from Computer Engineering Server";
	size_t bufferSize = sizeof(Buffer);

	// Create File Mapping 
	FileMap = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		256,
		L"Local\\MyFileMap"
	);

	if (FileMap == FALSE) {
		cout << "CreateFileMapping Failed  " << GetLastError() << endl;
	}

	cout << "CreateFileMapping Success  " << endl;

	// MapViewOfFile
	lpBuffer = (PCHAR)MapViewOfFile(
		FileMap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		256
	);

	if (lpBuffer == NULL) {
		cout << "MapViewOfFile Failed  " << GetLastError() << endl;
	}

	cout << "MapViewOfFile Success  " << endl;


	// CopyMemory
	CopyMemory(lpBuffer, Buffer, bufferSize);

	// UnmapViewOfFile
	Result = UnmapViewOfFile(lpBuffer);
	if (Result == FALSE) {
		cout << "UnmapViewOfFile Failed" << GetLastError() << endl;
	}

	cout << "UnmapViewOfFile Success" << endl;


}
