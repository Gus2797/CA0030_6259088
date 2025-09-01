#ifndef CSYSFOLIOGLOBAL
#define CSYSFOLIOGLOBAL
#include <RecordSet.HPP>
class CSysFolioGlobal : public CRecordSet
{
public:
    CSysFolioGlobal(C_ODBC *odbc_ext,bool bFlagCommit = true, const char *select=NULL);
    ~CSysFolioGlobal();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);

    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[2];
    int nCTipo[2];
    long nLongitud[2];
    long nLongResp[2];
    void *pVar[2];
        bool bFlagCommit;

    _int64              folio;
};
#endif CSYSFOLIOGLOBAL
