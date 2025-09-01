// stdafx.cpp : source file that includes just the standard includes
// CapturarAbono.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "afxwin.h"

int AFXAPI AfxMessageBox(LPCTSTR lpszText, UINT nType, UINT /*nIDHelp*/)
{
    return MessageBox(GetActiveWindow(), lpszText, "COPPEL", nType == NULL ? MB_ICONEXCLAMATION : nType);
}