#pragma once


class CIniciarDiaCajas
{

public:

    CIniciarDiaCajas(void);
    ~CIniciarDiaCajas(void);

    char cIP[20];
    int iTienda, iCaja, iCiudad, iDesplegarError, iDiaActual, iMesActual, iYearActual;
    long lFechaSys, lEmpleadoSys;

    bool iniciarDia(void);
    bool checarInicioCajas(int iModo);
    bool consultarFlags(int iTipoFlag, char cArea, int &iFlag);
    bool borrarCaAjustesAutomaticos();
    bool borrarTablasTiendaNumero();
    bool borrarTdListaNegraForaneos();
    bool grabarSoComplementoZonas();
    bool inicializaTdStel(int iFlagRespaldaStel);
    bool actualizarMetas();
    bool obtenerCiudadCobranza(int &iCiudadCobranzaTelefonica);
    bool grabarTdNumRegCT(long lClientesContactados, long lRegNumRegCT);
    bool respaldarNumReg();
    bool grabarMetasTdNumRegCT(int iFlag, long lMetaMensual);
    bool actualizarMetasTdNumRegCT(long lMeta);
    bool actualizarClaveInicioCajas();
    bool actualizarClaveInicioRopa(int iFlag);
    bool pasarRegistrosRetirosParciales();
    bool deleteTablasTiendaNumero(int iFlag);
    bool deleteTablasTienda(int iFlag);
    bool actualizarClaveInicioMuebles();
    bool actualizarFechaGnDominio();
    bool depurarControlLlamadas();
    bool depurarEstadistica();
    bool depurarEstadisticaNumReg();
    bool inicializarKC();
    bool inicializaFolioMiniFicha();
    bool graboBandera();
    bool respaldarConveniosPorSupervisor();
    bool iniciarTl();
    bool pasarRechajus();

    void capturaCajeras(int iModo);
    void confirmarEnvioConsultaBuro();
    void generarInformeBloque4y5();
    void capturarGerente();
    void actualizarNumreg(int iFlagActCobTel);

    int  checarGenerarCartera(int iFlagTda);
    int  actualizarFlagCartera(int iFlagChecar);
    int  existeBandera(bool &bContinuar);
    int  checarUltimoRegistroCT(bool &bContinuar);

    long obtenerRegistrosNtdImpre(bool &bContinuar);
    long ctesContactadosTdEstadisticaCT(bool &bContinuar);
    long regsTdCobTelCiudad(bool &bContinuar);
    long regsTdNumRegCT(bool &bContinuar);
    long obtenerMeta(bool &bContinuar);
    long actualizaMetasCobranza(bool &bContinuar);
    void traslapeAutomaticoCartera();


private:

};
