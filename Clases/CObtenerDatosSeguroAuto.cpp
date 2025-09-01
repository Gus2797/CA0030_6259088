#include "COBTENERDATOSSEGUROAUTO.HPP"
CObtenerDatosSeguroAuto::CObtenerDatosSeguroAuto(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=38;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_VARCHAR;
    nSqlTipo[1] = SQL_VARCHAR;
    nSqlTipo[2] = SQL_VARCHAR;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_CHAR;
    nSqlTipo[5] = SQL_CHAR;
    nSqlTipo[6] = SQL_SMALLINT;
    nSqlTipo[7] = SQL_SMALLINT;
    nSqlTipo[8] = SQL_SMALLINT;
    nSqlTipo[9] = SQL_INTEGER;
    nSqlTipo[10] = SQL_INTEGER;
    nSqlTipo[11] = SQL_INTEGER;
    nSqlTipo[12] = SQL_INTEGER;
    nSqlTipo[13] = SQL_INTEGER;
    nSqlTipo[14] = SQL_INTEGER;
    nSqlTipo[15] = SQL_INTEGER;
    nSqlTipo[16] = SQL_INTEGER;
    nSqlTipo[17] = SQL_INTEGER;
    nSqlTipo[18] = SQL_INTEGER;
    nSqlTipo[19] = SQL_INTEGER;
    nSqlTipo[20] = SQL_VARCHAR;
    nSqlTipo[21] = SQL_INTEGER;
    nSqlTipo[22] = SQL_INTEGER;
    nSqlTipo[23] = SQL_INTEGER;
    nSqlTipo[24] = SQL_INTEGER;
    nSqlTipo[25] = SQL_INTEGER;
    nSqlTipo[26] = SQL_INTEGER;
    nSqlTipo[27] = SQL_INTEGER;
    nSqlTipo[28] = SQL_CHAR;
    nSqlTipo[29] = SQL_BIGINT;
    nSqlTipo[30] = SQL_BIGINT;
    nSqlTipo[31] = SQL_BIGINT;
    nSqlTipo[32] = SQL_CHAR;
    nSqlTipo[33] = SQL_SMALLINT;
    nSqlTipo[34] = SQL_SMALLINT;
    nSqlTipo[35] = SQL_SMALLINT;
    nSqlTipo[36] = SQL_CHAR;
    nSqlTipo[37] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_CHAR;
    nCTipo[6] = SQL_C_SSHORT;
    nCTipo[7] = SQL_C_SSHORT;
    nCTipo[8] = SQL_C_SSHORT;
    nCTipo[9] = SQL_C_SLONG;
    nCTipo[10] = SQL_C_SLONG;
    nCTipo[11] = SQL_C_SLONG;
    nCTipo[12] = SQL_C_SLONG;
    nCTipo[13] = SQL_C_SLONG;
    nCTipo[14] = SQL_C_SLONG;
    nCTipo[15] = SQL_C_SLONG;
    nCTipo[16] = SQL_C_SLONG;
    nCTipo[17] = SQL_C_SLONG;
    nCTipo[18] = SQL_C_SLONG;
    nCTipo[19] = SQL_C_SLONG;
    nCTipo[20] = SQL_C_CHAR;
    nCTipo[21] = SQL_C_SLONG;
    nCTipo[22] = SQL_C_SLONG;
    nCTipo[23] = SQL_C_SLONG;
    nCTipo[24] = SQL_C_SLONG;
    nCTipo[25] = SQL_C_SLONG;
    nCTipo[26] = SQL_C_SLONG;
    nCTipo[27] = SQL_C_SLONG;
    nCTipo[28] = SQL_C_CHAR;
    nCTipo[29] = SQL_C_SBIGINT;
    nCTipo[30] = SQL_C_SBIGINT;
    nCTipo[31] = SQL_C_SBIGINT;
    nCTipo[32] = SQL_C_CHAR;
    nCTipo[33] = SQL_C_SSHORT;
    nCTipo[34] = SQL_C_SSHORT;
    nCTipo[35] = SQL_C_SSHORT;
    nCTipo[36] = SQL_C_CHAR;
    nCTipo[37] = SQL_C_CHAR;
 
    nLongitud[0] = 107;
    nLongitud[1] = 107;
    nLongitud[2] = 107;
    nLongitud[3] = 3;
    nLongitud[4] = 12;
    nLongitud[5] = 22;
    nLongitud[6] = 3;
    nLongitud[7] = 3;
    nLongitud[8] = 3;
    nLongitud[9] = 5;
    nLongitud[10] = 5;
    nLongitud[11] = 5;
    nLongitud[12] = 5;
    nLongitud[13] = 5;
    nLongitud[14] = 5;
    nLongitud[15] = 5;
    nLongitud[16] = 5;
    nLongitud[17] = 5;
    nLongitud[18] = 5;
    nLongitud[19] = 5;
    nLongitud[20] = 107;
    nLongitud[21] = 5;
    nLongitud[22] = 5;
    nLongitud[23] = 5;
    nLongitud[24] = 5;
    nLongitud[25] = 5;
    nLongitud[26] = 5;
    nLongitud[27] = 5;
    nLongitud[28] = 8;
    nLongitud[29] = 9;
    nLongitud[30] = 9;
    nLongitud[31] = 9;
    nLongitud[32] = 17;
    nLongitud[33] = 3;
    nLongitud[34] = 3;
    nLongitud[35] = 3;
    nLongitud[36] = 22;
    nLongitud[37] = 32;
    pVar[0] = &fechaventa;
    pVar[1] = &fechaactivacion;
    pVar[2] = &fechavencimiento;
    pVar[3] = &tipocobertura;
    pVar[4] =  placas;
    pVar[5] =  numerodeserie;
    pVar[6] = &modelo;
    pVar[7] = &tipovehiculo;
    pVar[8] = &tipouso;
    pVar[9] = &primaneta;
    pVar[10] = &udi;
    pVar[11] = &excedente;
    pVar[12] = &derechodepoliza;
    pVar[13] = &primaantesdeiva;
    pVar[14] = &primatotal;
    pVar[15] = &primanetaanual;
    pVar[16] = &excedenteanual;
    pVar[17] = &derechopolizaanual;
    pVar[18] = &primaantesdeivaanual;
    pVar[19] = &primatotalanual;
    pVar[20] = &fechaalta;
    pVar[21] = &udidespuesdeiva;
    pVar[22] = &excedentedespuesdeiva;
    pVar[23] = &derechodepolizadespuesdeiva;
    pVar[24] = &udianual;
    pVar[25] = &udidespuesdeivaanual;
    pVar[26] = &excedentedespuesdeivaanual;
    pVar[27] = &derechodepolizadespuesdeivaanual;
    pVar[28] =  claveamis;
    pVar[29] = &danosaterceros;
    pVar[30] = &gastosmedicosauto;
    pVar[31] = &gastosmedicoscamioneta;
    pVar[32] =  asistencialegal;
    pVar[33] = &gastosdeasistencialegal;
    pVar[34] = &marca;
    pVar[35] = &submarca;
    pVar[36] =  descripcionmarca;
    pVar[37] =  descripcionlinea;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CObtenerDatosSeguroAuto::~CObtenerDatosSeguroAuto()
{
}
    
void CObtenerDatosSeguroAuto::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
