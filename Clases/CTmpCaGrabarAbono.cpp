#include "CTMPCAGRABARABONO.HPP"
CTmpCaGrabarAbono::CTmpCaGrabarAbono(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=42;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_INTEGER;
    nSqlTipo[4] = SQL_VARCHAR;
    nSqlTipo[5] = SQL_INTEGER;
    nSqlTipo[6] = SQL_SMALLINT;
    nSqlTipo[7] = SQL_VARCHAR;
    nSqlTipo[8] = SQL_VARCHAR;
    nSqlTipo[9] = SQL_VARCHAR;
    nSqlTipo[10] = SQL_VARCHAR;
    nSqlTipo[11] = SQL_INTEGER;
    nSqlTipo[12] = SQL_SMALLINT;
    nSqlTipo[13] = SQL_INTEGER;
    nSqlTipo[14] = SQL_INTEGER;
    nSqlTipo[15] = SQL_INTEGER;
    nSqlTipo[16] = SQL_INTEGER;
    nSqlTipo[17] = SQL_INTEGER;
    nSqlTipo[18] = SQL_INTEGER;
    nSqlTipo[19] = SQL_INTEGER;
    nSqlTipo[20] = SQL_INTEGER;
    nSqlTipo[21] = SQL_INTEGER;
    nSqlTipo[22] = SQL_SMALLINT;
    nSqlTipo[23] = SQL_SMALLINT;
    nSqlTipo[24] = SQL_SMALLINT;
    nSqlTipo[25] = SQL_VARCHAR;
    nSqlTipo[26] = SQL_INTEGER;
    nSqlTipo[27] = SQL_SMALLINT;
    nSqlTipo[28] = SQL_SMALLINT;
    nSqlTipo[29] = SQL_CHAR;
    nSqlTipo[30] = SQL_SMALLINT;
    nSqlTipo[31] = SQL_SMALLINT;
    nSqlTipo[32] = SQL_INTEGER;
    nSqlTipo[33] = SQL_SMALLINT;
    nSqlTipo[34] = SQL_INTEGER;
    nSqlTipo[35] = SQL_INTEGER;
    nSqlTipo[36] = SQL_INTEGER;
    nSqlTipo[37] = SQL_INTEGER;
    nSqlTipo[38] = SQL_INTEGER;
    nSqlTipo[39] = SQL_INTEGER;
	nSqlTipo[40] = SQL_SMALLINT;
	nSqlTipo[41] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_SLONG;
    nCTipo[6] = SQL_C_SSHORT;
    nCTipo[7] = SQL_C_CHAR;
    nCTipo[8] = SQL_C_CHAR;
    nCTipo[9] = SQL_C_CHAR;
    nCTipo[10] = SQL_C_CHAR;
    nCTipo[11] = SQL_C_SLONG;
    nCTipo[12] = SQL_C_SSHORT;
    nCTipo[13] = SQL_C_SLONG;
    nCTipo[14] = SQL_C_SLONG;
    nCTipo[15] = SQL_C_SLONG;
    nCTipo[16] = SQL_C_SLONG;
    nCTipo[17] = SQL_C_SLONG;
    nCTipo[18] = SQL_C_SLONG;
    nCTipo[19] = SQL_C_SLONG;
    nCTipo[20] = SQL_C_SLONG;
    nCTipo[21] = SQL_C_SLONG;
    nCTipo[22] = SQL_C_SSHORT;
    nCTipo[23] = SQL_C_SSHORT;
    nCTipo[24] = SQL_C_SSHORT;
    nCTipo[25] = SQL_C_CHAR;
    nCTipo[26] = SQL_C_SLONG;
    nCTipo[27] = SQL_C_SSHORT;
    nCTipo[28] = SQL_C_SSHORT;
    nCTipo[29] = SQL_C_CHAR;
    nCTipo[30] = SQL_C_SSHORT;
    nCTipo[31] = SQL_C_SSHORT;
    nCTipo[32] = SQL_C_SLONG;
    nCTipo[33] = SQL_C_SSHORT;
    nCTipo[34] = SQL_C_SLONG;
    nCTipo[35] = SQL_C_SLONG;
    nCTipo[36] = SQL_C_SLONG;
    nCTipo[37] = SQL_C_SLONG;
    nCTipo[38] = SQL_C_SLONG;
    nCTipo[39] = SQL_C_SLONG;
	nCTipo[40] = SQL_C_SSHORT;
	nCTipo[41] = SQL_C_SLONG;
 
    nLongitud[0] = 3;
    nLongitud[1] = 12;
    nLongitud[2] = 3;
    nLongitud[3] = 5;
    nLongitud[4] = 107;
    nLongitud[5] = 5;
    nLongitud[6] = 3;
    nLongitud[7] = 107;
    nLongitud[8] = 107;
    nLongitud[9] = 107;
    nLongitud[10] = 107;
    nLongitud[11] = 5;
    nLongitud[12] = 3;
    nLongitud[13] = 5;
    nLongitud[14] = 5;
    nLongitud[15] = 5;
    nLongitud[16] = 5;
    nLongitud[17] = 5;
    nLongitud[18] = 5;
    nLongitud[19] = 5;
    nLongitud[20] = 5;
    nLongitud[21] = 5;
    nLongitud[22] = 3;
    nLongitud[23] = 3;
    nLongitud[24] = 3;
    nLongitud[25] = 107;
    nLongitud[26] = 5;
    nLongitud[27] = 3;
    nLongitud[28] = 3;
    nLongitud[29] = 3;
    nLongitud[30] = 3;
    nLongitud[31] = 3;
    nLongitud[32] = 5;
    nLongitud[33] = 3;
    nLongitud[34] = 5;
    nLongitud[35] = 5;
    nLongitud[36] = 5;
    nLongitud[37] = 5;
    nLongitud[38] = 5;
    nLongitud[39] = 5;
	nLongitud[40] = 3;
	nLongitud[41] = 5;

    pVar[0] =  clave;
    pVar[1] =  conceptocuenta;
    pVar[2] = &tienda;
    pVar[3] = &factura;
    pVar[4] = &fechacompra;
    pVar[5] = &importe;
    pVar[6] = &diapago;
    pVar[7] = &fechavencimiento;
    pVar[8] = &fechaultimomovimiento;
    pVar[9] = &fechasaldacon;
    pVar[10] = &fechaconvenio;
    pVar[11] = &empleadoconvenio;
    pVar[12] = &plazoconvenio;
    pVar[13] = &importeconvenio;
    pVar[14] = &saldo;
    pVar[15] = &interesadicional;
    pVar[16] = &base;
    pVar[17] = &vencido;
    pVar[18] = &minimo;
    pVar[19] = &saldacon;
    pVar[20] = &bonificacion;
    pVar[21] = &supago;
    pVar[22] = &numeroseguros;
    pVar[23] = &numeromeses;
    pVar[24] = &flagconyugal;
    pVar[25] = &fechavencimientoanterior;
    pVar[26] = &saldaconanteriormuebles;
    pVar[27] = &tipoconvenio;
    pVar[28] = &flagcapturoconvenio;
    pVar[29] =  status;
    pVar[30] = &cantidadanteriorseguros;
    pVar[31] = &subtipoconvenio;
    pVar[32] = &interesprimermes;
    pVar[33] = &tipoproducto;
    pVar[34] = &minimototal;
    pVar[35] = &saldototal;
    pVar[36] = &vencidototal;
    pVar[37] = &minimototalfinal;
    pVar[38] = &saldototalfinal;
    pVar[39] = &vencidototalfinal;
	pVar[40] = &flagcuentaperdida;
	pVar[41] = &descuento;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CTmpCaGrabarAbono::~CTmpCaGrabarAbono()
{
    Commit();
}
    
void CTmpCaGrabarAbono::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CTmpCaGrabarAbono::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmpCaGrabarAbono");
    return (retorno);
}
BOOL CTmpCaGrabarAbono::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, conceptocuenta, tienda, factura, fechacompra, importe, diapago, fechavencimiento, fechaultimomovimiento, fechasaldacon, fechaconvenio, empleadoconvenio, plazoconvenio, importeconvenio, saldo, interesadicional, base, vencido, minimo, saldacon, bonificacion, supago, numeroseguros, numeromeses, flagconyugal, fechavencimientoanterior, saldaconanteriormuebles, tipoconvenio, flagcapturoconvenio, status, cantidadanteriorseguros, subtipoconvenio, interesprimermes, tipoproducto, minimototal, saldototal, vencidototal, minimototalfinal, saldototalfinal, vencidototalfinal, flagcuentaperdida, descuento) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
