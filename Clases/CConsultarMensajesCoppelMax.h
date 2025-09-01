#ifndef CCONSULTARMENSAJESCOPPELMAX
#define CCONSULTARMENSAJESCOPPELMAX
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarMensajesCoppelMax : public CRecordSet
{
public:
	CConsultarMensajesCoppelMax(C_ODBC *odbc_ext, const char *select=NULL);
	~CConsultarMensajesCoppelMax();
	void activarCols();

	C_ODBC *odbc;
	int odbcRet;
	int nCols;
	int nSqlTipo[2];
	int nCTipo[2];
	long nLongitud[2];
	long nLongResp[2];
	void *pVar[2];

	char mensaje[1024];
};
#endif CCONSULTARMENSAJESCOPPELMAX
