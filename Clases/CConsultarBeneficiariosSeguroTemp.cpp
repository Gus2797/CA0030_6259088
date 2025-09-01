#include "CCONSULTARBENEFICIARIOSSEGUROTEMP.HPP"
CConsultarBeneficiariosSeguroTemp::CConsultarBeneficiariosSeguroTemp(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=17;
    odbcRet=TRUE;
	nSqlTipo[0] = SQL_SMALLINT;
	nSqlTipo[1] = SQL_BIGINT;
	nSqlTipo[2] = SQL_BIGINT;
	nSqlTipo[3] = SQL_VARCHAR;
	nSqlTipo[4] = SQL_VARCHAR;
	nSqlTipo[5] = SQL_VARCHAR;
    nSqlTipo[6] = SQL_VARCHAR;
	nSqlTipo[7] = SQL_SMALLINT;
	nSqlTipo[8] = SQL_SMALLINT;
    nSqlTipo[9] = SQL_VARCHAR;
    nSqlTipo[10] = SQL_BIGINT;
    nSqlTipo[11] = SQL_SMALLINT;
    nSqlTipo[12] = SQL_VARCHAR;
	nSqlTipo[13] = SQL_SMALLINT;
	nSqlTipo[14] = SQL_SMALLINT;
	nSqlTipo[15] = SQL_SMALLINT;
	nSqlTipo[16] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SSHORT;
	nCTipo[1] = SQL_C_SBIGINT;
	nCTipo[2] = SQL_C_SBIGINT;
	nCTipo[3] = SQL_C_CHAR;
	nCTipo[4] = SQL_C_CHAR;
	nCTipo[5] = SQL_C_CHAR;
	nCTipo[6] = SQL_C_CHAR;
	nCTipo[7] = SQL_C_SSHORT;
	nCTipo[8] = SQL_C_SSHORT;
	nCTipo[9] = SQL_C_CHAR;
    nCTipo[10] = SQL_C_SBIGINT;
    nCTipo[11] = SQL_C_SSHORT;
    nCTipo[12] = SQL_C_CHAR;
	nCTipo[13] = SQL_C_SSHORT;
	nCTipo[14] = SQL_C_SSHORT;
	nCTipo[15] = SQL_C_SSHORT;
	nCTipo[16] = SQL_C_SLONG;
 
    nLongitud[0] = 3;
	nLongitud[1] = 9;
	nLongitud[2] = 9;
	nLongitud[3] = 17;
	nLongitud[4] = 17;
	nLongitud[5] = 17;
	nLongitud[6] = 107;
	nLongitud[7] = 3;
	nLongitud[8] = 3;
	nLongitud[9] = 2;
    nLongitud[10] = 9;
    nLongitud[11] = 3;
    nLongitud[12] = 107;
    nLongitud[13] = 3;
	nLongitud[14] = 3;
	nLongitud[15] = 3;
	nLongitud[16] = 5;
    pVar[0] = &idu_seguro;
    pVar[1] = &fol_ultimapoliza;
    pVar[2] = &idu_adicional;
    pVar[3] = &nom_beneficiario;
    pVar[4] = &nom_apellidopaterno;
    pVar[5] = &nom_apellidomaterno;
	pVar[6] = &fec_nacimiento;
	pVar[7] = &idu_parentesco;
	pVar[8] = &num_orden;
	pVar[9] = &clv_sexo;
	pVar[10] = &num_telefono;
	pVar[11] = &prc_asignado;
	pVar[12] = &fec_altabeneficiario;
	pVar[13] = &num_movimiento;
	pVar[14] = &num_tienda;
	pVar[15] = &num_caja;
	pVar[16] = &num_recibo;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarBeneficiariosSeguroTemp::~CConsultarBeneficiariosSeguroTemp()
{
}
    
void CConsultarBeneficiariosSeguroTemp::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
