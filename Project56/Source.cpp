#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
std::vector<HANDLE> myPipeVector;
HANDLE hPipe;
std::vector<HANDLE> myThreadVector;
HANDLE hTempThread;
const int BUFFER_SIZE = 1024;
DWORD WINAPI ThreadFunc(LPVOID param)
{
	std::cout << "Thread func\n";
	int nPipeIndex = (int)param;
	while (true) {
		char buffer[BUFFER_SIZE];
		DWORD bytesRead, bytesWrite;
		if (ReadFile(myPipeVector[nPipeIndex], buffer, BUFFER_SIZE, &bytesRead,
			NULL))
		{
			std::cout << "Received: " << buffer << std::endl;
		}
		else
		{
			std::cout << "Read file error" << std::endl;
		}
		for (int i = 0; i < myPipeVector.size() - 1; i++)
		{
			std::cout << "Sending message to pipe " << nPipeIndex << std::endl;
			if (!WriteFile(myPipeVector[i], buffer, bytesRead, &bytesWrite,
				NULL))
			{
				std::cout << "WriteFile failed. Error: " << GetLastError() <<
					std::endl;
				return 1;
			}
			std::cout << "Sending message to pipe " << nPipeIndex << "complete" << std::endl;
		}
	}
	std::cout << "End of thread func!\n";
	return 0;
}

int main() {
	int nPipesCounter = 0;
	while (true) {
		hPipe = CreateNamedPipe(L"\\\\.\\pipe\\MyPipe", PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES, BUFFER_SIZE * 16, BUFFER_SIZE * 16, 0, NULL);
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			std::cout << "CreateNamedPipe failed. Error: " << GetLastError() <<
				std::endl;
			break;
		}
		//Pipe was successfully created
		myPipeVector.push_back(hPipe);
		std::cout << "Waiting for client connection..." << std::endl;
		if (!ConnectNamedPipe(myPipeVector[nPipesCounter], NULL))
		{
			std::cout << "ConnectNamedPipe failed. Error: " << GetLastError()
				<< std::endl;
			break;
		}
		std::cout << "Client connected." << std::endl;
		hTempThread = CreateThread(NULL, 0, ThreadFunc, (LPVOID)nPipesCounter,
			0, NULL);
		myThreadVector.push_back(hTempThread);
		nPipesCounter++;
	}
	int nNumOfThreads = myThreadVector.size();
	for (int i = 0; i < nNumOfThreads; i++)
	{
		WaitForSingleObject(myThreadVector[i], INFINITE);
	}
	//free system resources
	for (int i = 0; i < nNumOfThreads; i++)
	{
		CloseHandle(myThreadVector[i]);
	}
	int nNumOfPipes = myPipeVector.size();
	for (int i = 0; i < nNumOfThreads; i++)
	{
		DisconnectNamedPipe(myPipeVector[i]);
		CloseHandle(myPipeVector[i]);
	}
	return 0;
}