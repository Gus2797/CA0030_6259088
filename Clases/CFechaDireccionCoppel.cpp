#include "CFECHADIRECCIONCOPPEL.HPP"
CFechaDireccionCoppel::CFechaDireccionCoppel(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=3;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_VARCHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
 
    nLongitud[0] = 107;
    nLongitud[1] = 202;
    nLongitud[2] = 52;
    pVar[0] = &fecha;
    pVar[1] =  domiciliocompleto;
    pVar[2] =  expedicion;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CFechaDireccionCoppel::~CFechaDireccionCoppel()
{
    Commit();
}
    
void CFechaDireccionCoppel::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CFechaDireccionCoppel::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("gndominio");
    return (retorno);
}
BOOL CFechaDireccionCoppel::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (fecha, domiciliocompleto, expedicion) VALUES (?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
