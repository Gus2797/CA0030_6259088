#include "CGRABARCERTIFICACIONABONO.HPP"
CGrabarCertificacionAbono::CGrabarCertificacionAbono(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=2;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_LONGVARCHAR;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_CHAR;
 
    nLongitud[0] = 5;
    nLongitud[1] = 20000;
    pVar[0] = &estado;
    pVar[1] =  mensaje;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarCertificacionAbono::~CGrabarCertificacionAbono()
{
}
    
void CGrabarCertificacionAbono::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
