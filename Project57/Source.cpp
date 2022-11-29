#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
HANDLE hPipe;
HANDLE hThread;
const int BUFFER_SIZE = 1024;
HANDLE hMutex;
DWORD WINAPI ThreadFunc(LPVOID param)
{
	while (true) {
		char buffer[BUFFER_SIZE];
		DWORD bytesRead;
		WaitForSingleObject(hMutex, INFINITE);
		if (ReadFile(hPipe, buffer, BUFFER_SIZE, &bytesRead, NULL)) {
			std::cout << "The number of read bytes = " << bytesRead << '\n';
			std::cout << "Received: " << buffer << std::endl;
			return 1;
		}
		else {
			std::cout << "ReadFile failed. Error: " << GetLastError() <<
				std::endl;
		}
		ReleaseMutex(hMutex);
	}
	std::cout << "End of thread func!\n";
	return 0;
}
int main() {
	hMutex = CreateMutex(NULL, FALSE, NULL);
	hPipe = CreateFile(L"\\\\.\\pipe\\MyPipe", GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, 0, NULL);
	if (hPipe == INVALID_HANDLE_VALUE) {
		std::cout << "CreateFile failed. Error: " << GetLastError() << endl;
		return 1;
	}
	hThread = CreateThread(NULL, 0, ThreadFunc, (LPVOID)NULL, 0, NULL);
	while (true) {
		WaitForSingleObject(hMutex, INFINITE);
		string message;
		std::cout << "Enter message: ";
		getline(cin, message);
		DWORD nWrittenBytes;
		if (!WriteFile(hPipe, message.c_str(), message.length() + 1,
			&nWrittenBytes, NULL)) {
			std::cout << "WriteFile failed. Error: " << GetLastError() << endl;
		}
		else {
			std::cout << "The number of written bytes = " << nWrittenBytes
				<< '\n';
		}
		ReleaseMutex(hMutex);
	}
	CloseHandle(hPipe);
	return 0;
}