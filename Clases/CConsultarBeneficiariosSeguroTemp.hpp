// Consulta original solicitada:...
//  SELECT importe,cantidadmeses,fechavencimiento,fol_sucursal as idu_adicional,cantidadseguros,folio FROM mov_cacarmovtemporal
    
#ifndef CCONSULTARBENEFICIARIOSSEGUROTEMP
#define CCONSULTARBENEFICIARIOSSEGUROTEMP
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarBeneficiariosSeguroTemp : public CRecordSet 
{
public:
    CConsultarBeneficiariosSeguroTemp(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarBeneficiariosSeguroTemp();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[18];
    int nCTipo[18];
    long nLongitud[18];
    long nLongResp[18];
    void *pVar[18];
    
    short int			idu_seguro;
    _int64				fol_ultimapoliza;
    _int64				idu_adicional;
    char				nom_beneficiario[17];
    char				nom_apellidopaterno[17];
	char 				nom_apellidomaterno[17];
	SqlTimeStamp        fec_nacimiento;
	short int			idu_parentesco;
	short int			num_orden;
	char				clv_sexo[2];
	_int64				num_telefono;
	short int			prc_asignado;
	SqlTimeStamp		fec_altabeneficiario;
	short int			num_movimiento;
	short int			num_tienda;
	short int			num_caja;
	long				num_recibo;
	
};
#endif CCONSULTARBENEFICIARIOSSEGUROTEMP
