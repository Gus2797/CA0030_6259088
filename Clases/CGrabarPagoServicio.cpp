#include "CGRABARPAGOSERVICIO.HPP"
CGrabarPagoServicio::CGrabarPagoServicio(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=9;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_CHAR;
    nSqlTipo[5] = SQL_CHAR;
    nSqlTipo[6] = SQL_SMALLINT;
    nSqlTipo[7] = SQL_SMALLINT;
    nSqlTipo[8] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_CHAR;
    nCTipo[6] = SQL_C_SSHORT;
    nCTipo[7] = SQL_C_SSHORT;
    nCTipo[8] = SQL_C_SSHORT;
 
    nLongitud[0] = 257;
    nLongitud[1] = 257;
    nLongitud[2] = 3;
    nLongitud[3] = 3;
    nLongitud[4] = 257;
    nLongitud[5] = 257;
    nLongitud[6] = 3;
    nLongitud[7] = 3;
    nLongitud[8] = 3;
    pVar[0] =  ccontratocfe;
    pVar[1] =  cimportecfe;
    pVar[2] = &iflagcfe;
    pVar[3] = &iregistroscfe;
    pVar[4] =  ccontratotelmex;
    pVar[5] =  cimportetelmex;
    pVar[6] = &iflagtelmex;
    pVar[7] = &iregistrostelmex;
    pVar[8] = &irespuesta;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarPagoServicio::~CGrabarPagoServicio()
{
    Commit();
}
    
void CGrabarPagoServicio::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarPagoServicio::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("Cagrabarpagoservicio");
    return (retorno);
}
BOOL CGrabarPagoServicio::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (ccontratocfe, cimportecfe, iflagcfe, iregistroscfe, ccontratotelmex, cimportetelmex, iflagtelmex, iregistrostelmex, irespuesta) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
