// Consulta original solicitada:...
//  SELECT  numerocliente,A.numerofactura,numerotienda,fechaprestamo,importeprestamo,interesfinanciamiento,comision,plazo,abonomensual,saldoprestamoanterior,saldomesanterior,saldoalafecha,interesadicional,abonosdelmes,prestamosdelmes,ajustes,tipoultimomovimiento,fechaultimomovimiento,importeultimomovimiento,fechadelconvenio,tipodeconvenio,subtipodeconvenio,plazodelconvenio,importedelconvenio,vecesrealizoconvenio,efectuoconvenio,interesadicionalmes,fechacuentasperdidas,COALESCE(tipoproducto,0) as tipoproducto,COALESCE(vistaentienda,'BANCOPPEL' ) as vistaentienda  FROM crctasperdidasdeudabancoppel AS A LEFT JOIN crcatalogotipoproductobanco AS B ON A.numerofactura = B.numerofactura WHERE numerocliente =356697
    
#ifndef CSALDOMESANTERIORBANCOPPEL
#define CSALDOMESANTERIORBANCOPPEL
#include "stdafx.h"
#include <RecordSet.hpp>
class CSaldoMesAnteriorBancoppel : public CRecordSet 
{
public:
    CSaldoMesAnteriorBancoppel(C_ODBC *odbc_ext, const char *select=NULL);
    ~CSaldoMesAnteriorBancoppel();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[31];
    int nCTipo[31];
    long nLongitud[31];
    long nLongResp[31];
    void *pVar[31];
    
    long                numerocliente;
    long                numerofactura;
    short int           numerotienda;
    SqlTimeStamp        fechaprestamo;
    long                importeprestamo;
    long                interesfinanciamiento;
    long                comision;
    short int           plazo;
    long                abonomensual;
    long                saldoprestamoanterior;
    long                saldomesanterior;
    long                saldoalafecha;
    long                interesadicional;
    long                abonosdelmes;
    long                prestamosdelmes;
    long                ajustes;
    char                tipoultimomovimiento[3];
    SqlTimeStamp        fechaultimomovimiento;
    long                importeultimomovimiento;
    SqlTimeStamp        fechadelconvenio;
    char                tipodeconvenio[3];
    char                subtipodeconvenio[3];
    short int           plazodelconvenio;
    long                importedelconvenio;
    short int           vecesrealizoconvenio;
    long                efectuoconvenio;
    long                interesadicionalmes;
    SqlTimeStamp        fechacuentasperdidas;
    long                tipoproducto;
    char                vistaentienda[32];
};
#endif CSALDOMESANTERIORBANCOPPEL
