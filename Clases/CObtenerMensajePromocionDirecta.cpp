#include "COBTENERMENSAJEPROMOCIONDIRECTA.HPP"
CObtenerMensajePromocionDirecta::CObtenerMensajePromocionDirecta(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=5;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_CHAR;
    nSqlTipo[3] = SQL_CHAR;
    nSqlTipo[4] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_CHAR;
    nCTipo[4] = SQL_C_CHAR;
 
    nLongitud[0] = 84;
    nLongitud[1] = 257;
    nLongitud[2] = 208;
    nLongitud[3] = 154;
    nLongitud[4] = 38;
    pVar[0] =  cencabezado;
    pVar[1] =  cparrafo1;
    pVar[2] =  cparrafo2;
    pVar[3] =  cparrafo3;
    pVar[4] =  cparrafo4;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CObtenerMensajePromocionDirecta::~CObtenerMensajePromocionDirecta()
{
    Commit();
}
    
void CObtenerMensajePromocionDirecta::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CObtenerMensajePromocionDirecta::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("gndominio");
    return (retorno);
}
BOOL CObtenerMensajePromocionDirecta::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cencabezado, cparrafo1, cparrafo2, cparrafo3, cparrafo4) VALUES (?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
