#include "COBTENERFECHASALDACONCRCROPA.HPP"
CObtenerFechaSaldaConCrCropa::CObtenerFechaSaldaConCrCropa(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=8;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_VARCHAR;
    nSqlTipo[2] = SQL_VARCHAR;
    nSqlTipo[3] = SQL_VARCHAR;
    nSqlTipo[4] = SQL_VARCHAR;
    nSqlTipo[5] = SQL_VARCHAR;
    nSqlTipo[6] = SQL_VARCHAR;
    nSqlTipo[7] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_CHAR;
    nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_CHAR;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_SLONG;
 
    nLongitud[0] = 5;
    nLongitud[1] = 107;
    nLongitud[2] = 107;
    nLongitud[3] = 107;
    nLongitud[4] = 107;
    nLongitud[5] = 107;
    nLongitud[6] = 107;
    nLongitud[7] = 5;
    pVar[0] = &cliente;
    pVar[1] = &fechaultcompra;
    pVar[2] = &fechaultimacomprames1;
    pVar[3] = &fechaultimacomprames2;
    pVar[4] = &fechaultimacomprames3;
    pVar[5] = &fechaultimacomprames4;
    pVar[6] = &fechaultimacomprames5;
    pVar[7] = &interessobrecompra;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CObtenerFechaSaldaConCrCropa::~CObtenerFechaSaldaConCrCropa()
{
    Commit();
}
    
void CObtenerFechaSaldaConCrCropa::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CObtenerFechaSaldaConCrCropa::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("CrCropa");
    return (retorno);
}
BOOL CObtenerFechaSaldaConCrCropa::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cliente, fechaultcompra, fechaultimacomprames1, fechaultimacomprames2, fechaultimacomprames3, fechaultimacomprames4, fechaultimacomprames5, interessobrecompra) VALUES (?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
