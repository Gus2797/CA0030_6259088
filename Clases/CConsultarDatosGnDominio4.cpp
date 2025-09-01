#include "CCONSULTARDATOSGNDOMINIO4.HPP"
CConsultarDatosGnDominio4::CConsultarDatosGnDominio4(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=10;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_VARCHAR;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_CHAR;
    nSqlTipo[7] = SQL_CHAR;
    nSqlTipo[8] = SQL_CHAR;
    nSqlTipo[9] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_CHAR;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_CHAR;
    nCTipo[8] = SQL_C_CHAR;
    nCTipo[9] = SQL_C_CHAR;
 
    nLongitud[0] = 22;
    nLongitud[1] = 22;
    nLongitud[2] = 5;
    nLongitud[3] = 107;
    nLongitud[4] = 5;
    nLongitud[5] = 3;
    nLongitud[6] = 22;
    nLongitud[7] = 12;
    nLongitud[8] = 202;
    nLongitud[9] = 52;
	
    pVar[0] =  nombresucursal;
    pVar[1] =  domicilio;
    pVar[2] = &numempgerentecajas;
    pVar[3] = &fecha;
    pVar[4] = &clientemaximo;
    pVar[5] = &ciudad;
    pVar[6] =  nombreciudad;
    pVar[7] =  telefono;
    pVar[8] =  domiciliocompleto;
    pVar[9] =  expedicion;
    
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarDatosGnDominio4::~CConsultarDatosGnDominio4()
{
}
    
void CConsultarDatosGnDominio4::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
