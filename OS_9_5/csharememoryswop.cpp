#include "csharememoryswop.h"
#define MEM_SIZE 1045

struct MemStruct {
    int MessCount = 0;
    char asMessages[300][50];
};

cShareMemorySwop::cShareMemorySwop()
{

}

cShareMemorySwop::~cShareMemorySwop()
{

}

void cShareMemorySwop::HostInit() {
    //окремо виносити інціалізацію першого процесу не потрібно
}

void cShareMemorySwop::ClientInit() {

    ptrMem = new QSharedMemory("myMem_os9");
    CRITICAL_SECTION cs;
    InitializeCriticalSection (&cs);
    EnterCriticalSection(&cs);
    if(!ptrMem->attach()) {
        ptrMem->create(sizeof(MemStruct));
        MemStruct * ptr = (MemStruct *)ptrMem->data();
        ptr->MessCount = 0;
    }
    LeaveCriticalSection(&cs);
    DeleteCriticalSection(&cs);
}

void cShareMemorySwop::Send(char * caMessage) {
    MemStruct * ptr = (MemStruct *)ptrMem->data();
    strcpy_s(ptr->asMessages[ptr->MessCount],caMessage);
    ptr->MessCount++;
}
int cShareMemorySwop::GetCount(void) {
    MemStruct * ptr = (MemStruct *)ptrMem->data();
    return ptr->MessCount;
}
char * cShareMemorySwop::Get(int num) {
    MemStruct * ptr = (MemStruct *)ptrMem->data();
    return ptr->asMessages[num];
}

const char * cShareMemorySwop::GetName(void) {
    return "QSharedMemory";
}
