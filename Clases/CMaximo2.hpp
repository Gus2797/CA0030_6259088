#ifndef CMAXIMO2
#define CMAXIMO2
#include <RecordSet.hpp>
class CMaximo2 : public CRecordSet
{
public:
    CMaximo2(C_ODBC *odbc_ext, bool bFlagCommit = true,const char *select=NULL);
    ~CMaximo2();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);

    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];
    bool bFlagCommit;

    long                Total;
	long                Total2;
};
#endif CMAXIMO2
