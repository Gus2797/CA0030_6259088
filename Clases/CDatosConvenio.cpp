#include "CDATOSCONVENIO.HPP"
CDatosConvenio::CDatosConvenio(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=6;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_SMALLINT;
    nSqlTipo[1] = SQL_SMALLINT;
    nSqlTipo[2] = SQL_VARCHAR;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SSHORT;
    nCTipo[1] = SQL_C_SSHORT;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SLONG;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 107;
    nLongitud[3] = 3;
    nLongitud[4] = 5;
    nLongitud[5] = 5;
    pVar[0] = &tipoconvenio;
    pVar[1] = &subtipoconvenio;
    pVar[2] = &fechaconvenio;
    pVar[3] = &plazoconvenio;
    pVar[4] = &importeconvenio;
    pVar[5] = &efectuoconvenio;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CDatosConvenio::~CDatosConvenio()
{
    Commit();
}
    
void CDatosConvenio::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CDatosConvenio::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crCropa");
    return (retorno);
}
BOOL CDatosConvenio::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (tipoconvenio, subtipoconvenio, fechaconvenio, plazoconvenio, importeconvenio, efectuoconvenio) VALUES (?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
