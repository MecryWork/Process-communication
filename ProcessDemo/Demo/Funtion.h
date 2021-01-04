#ifndef FUNTION_H
#define FUNTION_H

#include"CallBackHelper.h"

class CFunc:public ICallBackReport
{
public:
    CFunc()
    {
        m_shm_p = 0;
    }
    void GetProcess();
    void DoFuncMan();
    void ClallBackProcess();
    void ClallBackResult();
private:
    void* m_shm_p;
};

#endif // FUNTION_H
