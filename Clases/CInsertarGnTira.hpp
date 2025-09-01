#ifndef CINSERTARGNTIRA
#define CINSERTARGNTIRA
#include <RecordSet.HPP>
class CInsertarGnTira : public CRecordSet 
{
public:
    CInsertarGnTira(C_ODBC *odbc_ext, bool bFlagCommit = true, const char *select=NULL);
    ~CInsertarGnTira();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[12];
    int nCTipo[12];
    long nLongitud[12];
    long nLongResp[12];
    void *pVar[12];
    
    short int           status;
    char                area[3];
    short int           tipo;
    short int           caja;
    long                folio;
    short int           tipoimpresora;
    char                documento[100000];
    long                tamanio;
    long                empleadoefectuo;
    long                empleadocancelo;
    SqlTimeStamp        fecha;
	bool				bFlagCommit;
};
#endif CINSERTARGNTIRA
