#ifndef CSHAREMEMORYSWOP_H
#define CSHAREMEMORYSWOP_H
#include "ibaseswop.h"
#include <QSharedMemory>
#include "windows.h"

class cShareMemorySwop:public iBaseSwop
{
private:
    QSharedMemory * ptrMem = NULL;
public:
    cShareMemorySwop();
    ~cShareMemorySwop();
    virtual void HostInit(void);
    virtual void ClientInit(void);
    virtual void Send(char *);
    virtual int GetCount(void);
    virtual char * Get(int);
    virtual const char * GetName(void);
};

#endif // CSHAREMEMORYSWOP_H
