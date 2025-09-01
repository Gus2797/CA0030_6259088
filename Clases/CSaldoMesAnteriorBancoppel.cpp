#include "CSALDOMESANTERIORBANCOPPEL.HPP"
CSaldoMesAnteriorBancoppel::CSaldoMesAnteriorBancoppel(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=30;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_VARCHAR;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_INTEGER;
    nSqlTipo[6] = SQL_INTEGER;
    nSqlTipo[7] = SQL_SMALLINT;
    nSqlTipo[8] = SQL_INTEGER;
    nSqlTipo[9] = SQL_INTEGER;
    nSqlTipo[10] = SQL_INTEGER;
    nSqlTipo[11] = SQL_INTEGER;
    nSqlTipo[12] = SQL_INTEGER;
    nSqlTipo[13] = SQL_INTEGER;
    nSqlTipo[14] = SQL_INTEGER;
    nSqlTipo[15] = SQL_INTEGER;
    nSqlTipo[16] = SQL_CHAR;
    nSqlTipo[17] = SQL_VARCHAR;
    nSqlTipo[18] = SQL_INTEGER;
    nSqlTipo[19] = SQL_VARCHAR;
    nSqlTipo[20] = SQL_CHAR;
    nSqlTipo[21] = SQL_CHAR;
    nSqlTipo[22] = SQL_SMALLINT;
    nSqlTipo[23] = SQL_INTEGER;
    nSqlTipo[24] = SQL_SMALLINT;
    nSqlTipo[25] = SQL_INTEGER;
    nSqlTipo[26] = SQL_INTEGER;
    nSqlTipo[27] = SQL_VARCHAR;
    nSqlTipo[28] = SQL_INTEGER;
    nSqlTipo[29] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_CHAR;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SLONG;
    nCTipo[6] = SQL_C_SLONG;
    nCTipo[7] = SQL_C_SSHORT;
    nCTipo[8] = SQL_C_SLONG;
    nCTipo[9] = SQL_C_SLONG;
    nCTipo[10] = SQL_C_SLONG;
    nCTipo[11] = SQL_C_SLONG;
    nCTipo[12] = SQL_C_SLONG;
    nCTipo[13] = SQL_C_SLONG;
    nCTipo[14] = SQL_C_SLONG;
    nCTipo[15] = SQL_C_SLONG;
    nCTipo[16] = SQL_C_CHAR;
    nCTipo[17] = SQL_C_CHAR;
    nCTipo[18] = SQL_C_SLONG;
    nCTipo[19] = SQL_C_CHAR;
    nCTipo[20] = SQL_C_CHAR;
    nCTipo[21] = SQL_C_CHAR;
    nCTipo[22] = SQL_C_SSHORT;
    nCTipo[23] = SQL_C_SLONG;
    nCTipo[24] = SQL_C_SSHORT;
    nCTipo[25] = SQL_C_SLONG;
    nCTipo[26] = SQL_C_SLONG;
    nCTipo[27] = SQL_C_CHAR;
    nCTipo[28] = SQL_C_SLONG;
    nCTipo[29] = SQL_C_CHAR;
 
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    nLongitud[2] = 3;
    nLongitud[3] = 107;
    nLongitud[4] = 5;
    nLongitud[5] = 5;
    nLongitud[6] = 5;
    nLongitud[7] = 3;
    nLongitud[8] = 5;
    nLongitud[9] = 5;
    nLongitud[10] = 5;
    nLongitud[11] = 5;
    nLongitud[12] = 5;
    nLongitud[13] = 5;
    nLongitud[14] = 5;
    nLongitud[15] = 5;
    nLongitud[16] = 3;
    nLongitud[17] = 107;
    nLongitud[18] = 5;
    nLongitud[19] = 107;
    nLongitud[20] = 3;
    nLongitud[21] = 3;
    nLongitud[22] = 3;
    nLongitud[23] = 5;
    nLongitud[24] = 3;
    nLongitud[25] = 5;
    nLongitud[26] = 5;
    nLongitud[27] = 107;
    nLongitud[28] = 5;
    nLongitud[29] = 32;
    pVar[0] = &numerocliente;
    pVar[1] = &numerofactura;
    pVar[2] = &numerotienda;
    pVar[3] = &fechaprestamo;
    pVar[4] = &importeprestamo;
    pVar[5] = &interesfinanciamiento;
    pVar[6] = &comision;
    pVar[7] = &plazo;
    pVar[8] = &abonomensual;
    pVar[9] = &saldoprestamoanterior;
    pVar[10] = &saldomesanterior;
    pVar[11] = &saldoalafecha;
    pVar[12] = &interesadicional;
    pVar[13] = &abonosdelmes;
    pVar[14] = &prestamosdelmes;
    pVar[15] = &ajustes;
    pVar[16] =  tipoultimomovimiento;
    pVar[17] = &fechaultimomovimiento;
    pVar[18] = &importeultimomovimiento;
    pVar[19] = &fechadelconvenio;
    pVar[20] =  tipodeconvenio;
    pVar[21] =  subtipodeconvenio;
    pVar[22] = &plazodelconvenio;
    pVar[23] = &importedelconvenio;
    pVar[24] = &vecesrealizoconvenio;
    pVar[25] = &efectuoconvenio;
    pVar[26] = &interesadicionalmes;
    pVar[27] = &fechacuentasperdidas;
    pVar[28] = &tipoproducto;
    pVar[29] =  vistaentienda;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CSaldoMesAnteriorBancoppel::~CSaldoMesAnteriorBancoppel()
{
    Commit();
}
    
void CSaldoMesAnteriorBancoppel::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CSaldoMesAnteriorBancoppel::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crctasperdidasdeudabancoppel");
    return (retorno);
}
BOOL CSaldoMesAnteriorBancoppel::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (numerocliente, numerofactura, numerotienda, fechaprestamo, importeprestamo, interesfinanciamiento, comision, plazo, abonomensual, saldoprestamoanterior, saldomesanterior, saldoalafecha, interesadicional, abonosdelmes, prestamosdelmes, ajustes, tipoultimomovimiento, fechaultimomovimiento, importeultimomovimiento, fechadelconvenio, tipodeconvenio, subtipodeconvenio, plazodelconvenio, importedelconvenio, vecesrealizoconvenio, efectuoconvenio, interesadicionalmes, fechacuentasperdidas, tipoproducto, vistaentienda) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
