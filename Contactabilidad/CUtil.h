#pragma once
#include "stdafx.h"
#include "C_Archiv.hpp"
#include "CExcepcion.h"

#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip> // Para std::setfill y std::setw

class CUtil
{
private:

public:
    CUtil();
    ~CUtil(void);
    //void GrabarLog(char *cLog);
    void GrabarLog(const char* cLog);
    void GrabarLog(CString sLog);
    void Click(int iLeft, int iRight);
    void ClickCenter();
    void SendAltTab();
};