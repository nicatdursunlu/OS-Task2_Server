#include <Windows.h>
#include <iostream>

using namespace std;
#define buf_size 1024

int main() {

	HANDLE pipe1;
	char buffer[buf_size];
	DWORD num_byte;

	pipe1 = CreateNamedPipe(
		"\\\\.\\pipe\\pipe1",
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_BYTE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		buf_size,
		buf_size,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL
	);

	cout << "pipe created" << endl;

	ConnectNamedPipe(
		pipe1,
		NULL
	);

	BOOL read1 = ReadFile(
		pipe1,
		buffer,
		sizeof(buffer),
		&num_byte,
		NULL
	);

	cout << "Message: " << buffer << endl;

	strcpy(buffer, "   comp_eng   ");

	BOOL write1 = WriteFile(
		pipe1,
		buffer,
		sizeof(buffer),
		&num_byte,
		NULL
	);

	CloseHandle(pipe1);

}