#include "CCONSULTARDATOSGNDOMINIO3.HPP"
CConsultarDatosGnDominio3::CConsultarDatosGnDominio3(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=14;
    odbcRet=TRUE;
    flagInsertar = 0;

    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_VARCHAR;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_CHAR;
    nSqlTipo[7] = SQL_CHAR;
    nSqlTipo[8] = SQL_CHAR;
    nSqlTipo[9] = SQL_INTEGER;
    nSqlTipo[10] = SQL_CHAR;
    nSqlTipo[11] = SQL_CHAR;
	nSqlTipo[12] = SQL_CHAR;
	nSqlTipo[13] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_CHAR;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_CHAR;
    nCTipo[8] = SQL_C_CHAR;
    nCTipo[9] = SQL_C_SLONG;
    nCTipo[10] = SQL_C_CHAR;
    nCTipo[11] = SQL_C_CHAR;
	nCTipo[12] = SQL_C_CHAR;
	nCTipo[13] = SQL_C_CHAR;
 
    nLongitud[0] = 22;
    nLongitud[1] = 22;
    nLongitud[2] = 5;
    nLongitud[3] = 107;
    nLongitud[4] = 5;
    nLongitud[5] = 3;
    nLongitud[6] = 22;
    nLongitud[7] = 12;
    nLongitud[8] = 37;
    nLongitud[9] = 5;
    nLongitud[10] = 202;
    nLongitud[11] = 52;
	nLongitud[12] = 22;
	nLongitud[13] = 27;

    pVar[0] =  nombresucursal;
    pVar[1] =  domicilio;
    pVar[2] = &numempgerentecajas;
    pVar[3] = &fecha;
    pVar[4] = &clientemaximo;
    pVar[5] = &ciudad;
    pVar[6] =  nombreciudad;
    pVar[7] =  telefono;
    pVar[8] =  permisogobernacion;
    pVar[9] = &salariominimo;
    pVar[10] =  domiciliocompleto;
    pVar[11] =  expedicion;
	pVar[12] =  foliopoliza;
	pVar[13] =  fechavigencia;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarDatosGnDominio3::~CConsultarDatosGnDominio3()
{
    Commit();
}
    
void CConsultarDatosGnDominio3::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarDatosGnDominio3::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("gndominio");
    return (retorno);
}
BOOL CConsultarDatosGnDominio3::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (nombresucursal, domicilio, numempgerentecajas, fecha, clientemaximo, ciudad, nombreciudad, telefono, permisogobernacion, salariominimo, domiciliocompleto, expedicion) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
