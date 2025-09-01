#include "CCRHUELLAS.HPP"
CCrHuellas::CCrHuellas(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
	int i,j;
    odbc = odbc_ext;
    nCols=90;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_CHAR;
	for(i=2;i<=89;i++) nSqlTipo[i] = SQL_BIGINT;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_CHAR;
	for(i=2;i<=89;i++) nCTipo[i] = SQL_C_SBIGINT;
 
    nLongitud[0] = 5;
    nLongitud[1] = 3;
	for(i=2;i<=89;i++) nLongitud[i] = 9;

    pVar[0] = &cliente;
    pVar[1] =  flagadicional;
	for(i=2,j=0;i<=89;i++,j++) pVar[i] = &templatededoderecho[j];

    /*pVar[2] = &templatededoderecho001;
    pVar[3] = &templatededoderecho002;
    pVar[4] = &templatededoderecho003;
    pVar[5] = &templatededoderecho004;
    pVar[6] = &templatededoderecho005;
    pVar[7] = &templatededoderecho006;
    pVar[8] = &templatededoderecho007;
    pVar[9] = &templatededoderecho008;
    pVar[10] = &templatededoderecho009;
    pVar[11] = &templatededoderecho010;
    pVar[12] = &templatededoderecho011;
    pVar[13] = &templatededoderecho012;
    pVar[14] = &templatededoderecho013;
    pVar[15] = &templatededoderecho014;
    pVar[16] = &templatededoderecho015;
    pVar[17] = &templatededoderecho016;
    pVar[18] = &templatededoderecho017;
    pVar[19] = &templatededoderecho018;
    pVar[20] = &templatededoderecho019;
    pVar[21] = &templatededoderecho020;
    pVar[22] = &templatededoderecho021;
    pVar[23] = &templatededoderecho022;
    pVar[24] = &templatededoderecho023;
    pVar[25] = &templatededoderecho024;
    pVar[26] = &templatededoderecho025;
    pVar[27] = &templatededoderecho026;
    pVar[28] = &templatededoderecho027;
    pVar[29] = &templatededoderecho028;
    pVar[30] = &templatededoderecho029;
    pVar[31] = &templatededoderecho030;
    pVar[32] = &templatededoderecho031;
    pVar[33] = &templatededoderecho032;
    pVar[34] = &templatededoderecho033;
    pVar[35] = &templatededoderecho034;
    pVar[36] = &templatededoderecho035;
    pVar[37] = &templatededoderecho036;
    pVar[38] = &templatededoderecho037;
    pVar[39] = &templatededoderecho038;
    pVar[40] = &templatededoderecho039;
    pVar[41] = &templatededoderecho040;
    pVar[42] = &templatededoderecho041;
    pVar[43] = &templatededoderecho042;
    pVar[44] = &templatededoderecho043;
    pVar[45] = &templatededoderecho044;
    pVar[46] = &templatededoderecho045;
    pVar[47] = &templatededoderecho046;
    pVar[48] = &templatededoderecho047;
    pVar[49] = &templatededoderecho048;
    pVar[50] = &templatededoderecho049;
    pVar[51] = &templatededoderecho050;
    pVar[52] = &templatededoderecho051;
    pVar[53] = &templatededoderecho052;
    pVar[54] = &templatededoderecho053;
    pVar[55] = &templatededoderecho054;
    pVar[56] = &templatededoderecho055;
    pVar[57] = &templatededoderecho056;
    pVar[58] = &templatededoderecho057;
    pVar[59] = &templatededoderecho058;
    pVar[60] = &templatededoderecho059;
    pVar[61] = &templatededoderecho060;
    pVar[62] = &templatededoderecho061;
    pVar[63] = &templatededoderecho062;
    pVar[64] = &templatededoderecho063;
    pVar[65] = &templatededoderecho064;
    pVar[66] = &templatededoderecho065;
    pVar[67] = &templatededoderecho066;
    pVar[68] = &templatededoderecho067;
    pVar[69] = &templatededoderecho068;
    pVar[70] = &templatededoderecho069;
    pVar[71] = &templatededoderecho070;
    pVar[72] = &templatededoderecho071;
    pVar[73] = &templatededoderecho072;
    pVar[74] = &templatededoderecho073;
    pVar[75] = &templatededoderecho074;
    pVar[76] = &templatededoderecho075;
    pVar[77] = &templatededoderecho076;
    pVar[78] = &templatededoderecho077;
    pVar[79] = &templatededoderecho078;
    pVar[80] = &templatededoderecho079;
    pVar[81] = &templatededoderecho080;
    pVar[82] = &templatededoderecho081;
    pVar[83] = &templatededoderecho082;
    pVar[84] = &templatededoderecho083;
    pVar[85] = &templatededoderecho084;
    pVar[86] = &templatededoderecho085;
    pVar[87] = &templatededoderecho086;
    pVar[88] = &templatededoderecho087;
    pVar[89] = &templatededoderecho088;*/
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CCrHuellas::~CCrHuellas()
{
    Commit();
}
    
void CCrHuellas::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CCrHuellas::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crhuellas");
    return (retorno);
}
BOOL CCrHuellas::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cliente, flagadicional, " 
	   "templatededoderecho001, templatededoderecho002, templatededoderecho003, templatededoderecho004, templatededoderecho005, templatededoderecho006, templatededoderecho007, templatededoderecho008, templatededoderecho009, templatededoderecho010, templatededoderecho011, templatededoderecho012, templatededoderecho013, templatededoderecho014, templatededoderecho015, templatededoderecho016, templatededoderecho017, templatededoderecho018, templatededoderecho019, templatededoderecho020, templatededoderecho021, templatededoderecho022, templatededoderecho023, templatededoderecho024, templatededoderecho025, templatededoderecho026, templatededoderecho027, templatededoderecho028, templatededoderecho029, templatededoderecho030, templatededoderecho031, templatededoderecho032, templatededoderecho033, templatededoderecho034, templatededoderecho035, templatededoderecho036, templatededoderecho037, templatededoderecho038, templatededoderecho039, templatededoderecho040, templatededoderecho041, templatededoderecho042, templatededoderecho043, templatededoderecho044, "
	   "templatededoderecho045, templatededoderecho046, templatededoderecho047, templatededoderecho048, templatededoderecho049, templatededoderecho050, templatededoderecho051, templatededoderecho052, templatededoderecho053, templatededoderecho054, templatededoderecho055, templatededoderecho056, templatededoderecho057, templatededoderecho058, templatededoderecho059, templatededoderecho060, templatededoderecho061, templatededoderecho062, templatededoderecho063, templatededoderecho064, templatededoderecho065, templatededoderecho066, templatededoderecho067, templatededoderecho068, templatededoderecho069, templatededoderecho070, templatededoderecho071, templatededoderecho072, templatededoderecho073, templatededoderecho074, templatededoderecho075, templatededoderecho076, templatededoderecho077, templatededoderecho078, templatededoderecho079, templatededoderecho080, templatededoderecho081, templatededoderecho082, templatededoderecho083, templatededoderecho084, templatededoderecho085, templatededoderecho086, templatededoderecho087, templatededoderecho088) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
