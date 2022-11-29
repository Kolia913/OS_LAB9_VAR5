#ifndef IBASESWOP_H
#define IBASESWOP_H

class iBaseSwop
{
public:
    virtual void HostInit(void) = 0;
    virtual void ClientInit(void) = 0;
    virtual void Send(char *) = 0;
    virtual int GetCount(void) = 0;
    virtual char * Get(int) = 0;
    virtual const char * GetName(void) = 0;
};

#endif // IBASESWOP_H
