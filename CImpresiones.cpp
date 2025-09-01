#include "stdafx.h"
#include "DlgCapturarAbono.h"

void CDlgCapturarAbono::imprimirMensajeInvitacionBancoppel()
{
    CWnd pWnd;
    CClientDC dc(&pWnd);
    CGenerarImpresion termica("c:\\sys\\mem\\InvitacionBancoppel.prn", true);
    int iRenglon = 0;

    termica.iniciarImpresion("BIXOLON SAMSUNG SRP-350plus", false);
    termica.impresionHorizontal(IMPRESION_VERTICAL);
    termica.ponerTituloCoppelRFC(iRenglon, dc);
    iRenglon += 240;

    termica.alinearTexto(CENTRO);
    termica.tipoLetra(&cNewFont, "Arial", &pcOldFont, 11);
    termica.ponerTermica(iRenglon, 250, "Mensaje BanCoppel");

    termica.alinearTexto(IZQUIERDA);
    iRenglon += 30;
    termica.ponerLinea(iRenglon, 5, iRenglon, 500);

    //Cuerpo Mensaje
    termica.tipoLetra(&cNewFont, "Arial", &pcOldFont, 8);

    iRenglon += 25;

    termica.ponerTermica(iRenglon, 25, "Usted  es  un  muy  buen  Cliente  de  Coppel  y");
    iRenglon += 25;
    termica.ponerTermica(iRenglon, 25, "PROBABLEMENTE    PUEDA    obtener    su");
    iRenglon += 25;
    termica.ponerTermica(iRenglon, 25, "Tarjeta de Crédito BanCoppel VISA.");

    iRenglon += 40;

    termica.ponerTermica(iRenglon, 25, "Lo  invitamos  a  que  pase  a  BanCoppel  para");
    iRenglon += 25;
    termica.ponerTermica(iRenglon, 25, "que  realice  el  tramite.");
    iRenglon += 25;
    termica.ponerTermica(iRenglon, 25, "Es  muy  fácil.");
    iRenglon += 50;
    termica.ponerTermica(iRenglon, 0, ".");
    termica.terminarImpresion();
}

void CDlgCapturarAbono::ImprimirMensajeActualizarDatos()
{
    char cMensaje[160] = { 0 };
    int iRen = 0;
    CString sTexto = "";
    CWnd pWnd;
    CClientDC dc(&pWnd);
    CGenerarImpresion termica("C:\\sys\\mem\\MENSAJE.txt", true);

    sTexto.Format("%.15s", cNombre);
    sTexto.Trim();
	if(sprintf_s(cNombre, "%s", sTexto) < 0){;}

    sTexto.Format("%.15s", cApellidoPaterno);
    sTexto.Trim();
	if(sprintf_s(cApellidoPaterno, "%s", sTexto) < 0){;}

    sTexto.Format("%.15s", cApellidoMaterno);
    sTexto.Trim();
	if(sprintf_s(cApellidoMaterno, "%s", sTexto) < 0){;}

    termica.iniciarImpresion("BIXOLON SAMSUNG SRP-350plus", false);
    termica.tipoLetra(&cNewFont, "Arial", &pcOldFont, 8);
    termica.ponerTituloCoppelRFC(iRen, dc);
    termica.alinearTexto(IZQUIERDA);
    termica.tipoLetra(&cNewFont, "Arial Bolt", &pcOldFont, 8);
    iRen += 200;
    termica.ponerLinea(iRen, 0, iRen, 540);
    iRen += 50;

	if(sprintf_s(cMensaje, "Estimado Sr(a). %s %s %s", cNombre, cApellidoPaterno, cApellidoMaterno) < 0){;}
    termica.ponerParrafoTermica(cMensaje, iRen, 0, 500);
    iRen += 25;
    SecureZeroMemory(cMensaje, sizeof(cMensaje));
	if(sprintf_s(cMensaje, "Le informamos que es necesario que pase al área de clientes nuevos de su Tienda Coppel más cercana a actualizar sus datos para brindarle un mejor servicio") < 0){;}
    termica.ponerParrafoTermica(cMensaje, iRen, 0, 500);
    iRen += 50;
    termica.ponerParrafoTermica("Muchas Gracias.", iRen, 0, 500);

    iRen += 100;
    termica.ponerTermica(iRen + 10, 5, ".");
    termica.terminarImpresion();
}

void CDlgCapturarAbono::ImprimirTicketGanadorCoppelMax(int dineroGenerado)
{
    list<string> lsMensajes; // Lista de mensajes a obtener en la BD.
	string cadena; // Cadena con el contenido de cada mensaje en la BD.
	char cMensaje[1100] = { 0 };
	CWnd pWnd;
    CClientDC dc(&pWnd);
    CString sTexto = "";
    CGenerarImpresion termica("C:\\sys\\mem\\COPPELMAX.PRN", true);
	int iRenglon = 0;

	if(!ConsultarMensajeCoppelMax(lsMensajes, 152) || lsMensajes.size() == 0) // Método para obtener los mensajes desde la BD.
	{
		grabarLog("CImpresiones::ImprimirTicketGanadorCoppelMax::Ticket CoppelMax NO impreso.");
		return;
	}

	grabarLog("CImpresiones::ImprimirTicketGanadorCoppelMax::Imprimiendo ticket CoppelMax.");

	termica.iniciarImpresion("BIXOLON SAMSUNG SRP-350plus", false);
    termica.impresionHorizontal(IMPRESION_VERTICAL);
    termica.cargarImagen(dc, "C:\\sys\\progs\\logo.bmp", iRenglon, 0);

	iRenglon += 100;

	termica.cargarImagen(dc, "C:\\sys\\progs\\logoCoppelMax.bmp", iRenglon, 20);

	iRenglon += 120;

	auto it = lsMensajes.begin(); // Obtiene un iterador que apunta al inicio de la lista.
	cadena = *it; // Se obtiene el valor del elemento al que apunta el iterador.

	if(sprintf_s(cMensaje, cadena.c_str()) < 0){;} // Se asigna a cMensaje el mensaje promocional de CoppelMax.

	termica.tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 11);
    termica.ponerTermica(iRenglon, 25, cMensaje);

	sTexto.Format("%.15s", cNombre);
    sTexto.Trim();
	if(sprintf_s(cNombre, "%s", sTexto) < 0){;}

    sTexto.Format("%.15s", cApellidoPaterno);
    sTexto.Trim();
	if(sprintf_s(cApellidoPaterno, "%s", sTexto) < 0){;}

    sTexto.Format("%.15s", cApellidoMaterno);
    sTexto.Trim();
	if(sprintf_s(cApellidoMaterno, "%s", sTexto) < 0){;}

	advance(it,1); // Se itera un elemento hacia adelante.
	cadena = *it; // Se obtiene el valor del elemento al que apunto el iterador luego de avanzar.
	// Nombre:
	if(sprintf_s(cMensaje, "%s %s %s %s", cadena.c_str(), cNombre, cApellidoPaterno, cApellidoMaterno) < 0){;}

	iRenglon += 70;

	termica.tipoLetra(&cNewFont, "Arial", &pcOldFont, 8);
	termica.ponerParrafoTermica(cMensaje, iRenglon, 25, 500);

	advance(it,1);
	cadena = *it;
	// No. Cliente:
	if(sprintf_s(cMensaje, "%s %ld", cadena.c_str(), m_grid.lCliente) < 0){;}
	
	iRenglon += 25;
	termica.ponerTermica(iRenglon, 25, cMensaje);


	advance(it,1);
	cadena = *it;
	// Mensaje de Felicitación: "¡Felicidades!"
	if(sprintf_s(cMensaje, cadena.c_str()) < 0){;}

	termica.tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 16);
	iRenglon += 45;
	termica.ponerTermica(iRenglon, 100, cMensaje);
	
	advance(it,1);
	cadena = *it; // Leyenda ganadora: Haz realizado # abonos puntuales

	int indice = cadena.find('#'); // Encuentra la posición del caracter '#'
	
	if(indice != string::npos) // Valida que el caracter sí exista en la cadena de texto.
	{
		if(bMostrarMensajeGenerico) // Valida que se haya realizado el numero de abonos puntuales que establece el programa
		{
			cadena.replace(indice, 1, "tus");
		} else {
			cadena.replace(indice, 1, to_string(iValorAbonosPuntuales));
		}
	} else {
		if(bMostrarMensajeGenerico) // Valida que se haya realizado el numero de abonos puntuales que establece el programa
		{
			for(int i = 0; i < cadena.length(); i++)
			{
				// Ciclo para encontrar un digito en la cadena de texto
				if(isdigit(cadena[i]))
				{
					indice = i; // indice toma como valor la posición del digito a reemplazar
				}
			}
			cadena.replace(indice, 1, "tus");
		}
	}

	if(sprintf_s(cMensaje, cadena.c_str()) < 0){;}
	termica.tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 8);
	iRenglon += 60;
	termica.ponerTermica(iRenglon, 10, cMensaje);

	// Cargar imagen de abonos puntuales
	iRenglon += 50;
    termica.cargarImagen(dc, "C:\\sys\\progs\\monedasTicketGanadorCoppelMax.bmp", iRenglon, 25);

	// Mostrar dinero electrónico generado
	string cifraGenerada = SepararMiles(dineroGenerado); 

	iRenglon += 125;
	termica.tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 10);
	if(sprintf_s(cMensaje, "$%s", cifraGenerada.c_str()) < 0){;}
	
	termica.ponerTermica(iRenglon, 350, cMensaje);

	// Mostrar mensaje de Saldo actual
	advance(it, 1);
	cadena = *it;
	iRenglon += 40;
	
	if(sprintf_s(cMensaje, cadena.c_str()) < 0){;}
	termica.tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 8);
    termica.ponerTermica(iRenglon, 20, cMensaje);

	// Obtener saldo actual de dinero electrónico actualizado
	iRenglon += 25;
	advance(it, 1);
	cadena = *it;

	string cifraTotal = iDineroElectronico > 0 ? SepararMiles(iDineroElectronico) : "0";
	termica.tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 12);
	// Saldo generado, Mensaje de saldo acumulado
	if(sprintf_s(cMensaje, "$%s %s", cifraTotal.c_str(), cadena.c_str()) < 0){;}
	termica.ponerTermica(iRenglon, 20, cMensaje);

	// Mostrar información relevante del programa CoppelMax
	iRenglon += 65;
	advance(it, 1);
	cadena = *it;

	if(sprintf_s(cMensaje, cadena.c_str()) < 0){;}
	termica.tipoLetra(&cNewFont, "Arial", &pcOldFont, 8);
	termica.ponerParrafoTermica(cMensaje, iRenglon, 20, 500);

	iRenglon += 35;
	advance(it, 1);
	cadena = *it;

	if(sprintf_s(cMensaje, cadena.c_str()) < 0){;}
	termica.tipoLetra(&cNewFont, "Arial", &pcOldFont, 8);
	termica.ponerParrafoTermica(cMensaje, iRenglon, 20, 500);

	iRenglon += 35;
	advance(it, 1);
	cadena = *it;

	if(sprintf_s(cMensaje, cadena.c_str()) < 0){;}
	termica.tipoLetra(&cNewFont, "Arial", &pcOldFont, 8);
	termica.ponerParrafoTermica(cMensaje, iRenglon, 20, 500);

	iRenglon += 70;
	termica.tipoLetra(&cNewFont, "Arial", &pcOldFont, 1);
	termica.ponerTermica(iRenglon, 15, ".");

	termica.terminarImpresion();
	grabarLog("CImpresiones::ImprimirTicketGanadorCoppelMax::Finalizó impresión de ticket CoppelMax.");
}

void CDlgCapturarAbono::ImprimirTicketAbonoCoppelMax()
{
	list<string> lsMensajes; // Lista de mensajes a obtener en la BD.
	string cadena; // Cadena con el contenido de cada mensaje en la BD.
	char cMensaje[1100] = { 0 };
	CWnd pWnd;
    CClientDC dc(&pWnd);
    CString sTexto = "";
    CGenerarImpresion termica("C:\\sys\\mem\\COPPELMAX.PRN", true);
	int iRenglon = 0;

	if(!ConsultarMensajeCoppelMax(lsMensajes, 151) || lsMensajes.size() == 0) // Método para obtener los mensajes desde la BD.
	{
		grabarLog("CImpresiones::ImprimirTicketAbonoCoppelMax::Ticket CoppelMax NO impreso.");
		return;
	}

	grabarLog("CImpresiones::ImprimirTicketGanadorCoppelMax::Imprimiendo ticket CoppelMax.");

	termica.iniciarImpresion("BIXOLON SAMSUNG SRP-350plus", false);
    termica.impresionHorizontal(IMPRESION_VERTICAL);
    termica.cargarImagen(dc, "C:\\sys\\progs\\logo.bmp", iRenglon, 0);

	iRenglon += 100;

	termica.cargarImagen(dc, "C:\\sys\\progs\\logoCoppelMax.bmp", iRenglon, 20);

	iRenglon += 140;

	termica.alinearTexto(CENTRO);
	auto it = lsMensajes.begin(); // Obtiene un iterador que apunta al inicio de la lista.
	cadena = *it; // Se obtiene el valor del elemento al que apunta el iterador.
	if(sprintf_s(cMensaje, cadena.c_str()) < 0){;} // Se asigna a cMensaje el mensaje promocional de CoppelMax.
	termica.tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 12);
	termica.ponerTermica(iRenglon, 250, cMensaje);
	iRenglon += 35;

	advance(it, 1);
	cadena = *it;
	if(sprintf_s(cMensaje, cadena.c_str()) < 0){;}
	termica.ponerTermica(iRenglon, 250, cMensaje);
	
	iRenglon += 80;

	termica.alinearTexto(IZQUIERDA);
	sTexto.Format("%.15s", cNombre);
    sTexto.Trim();
	if(sprintf_s(cNombre, "%s", sTexto) < 0){;}

    sTexto.Format("%.15s", cApellidoPaterno);
    sTexto.Trim();
	if(sprintf_s(cApellidoPaterno, "%s", sTexto) < 0){;}

    sTexto.Format("%.15s", cApellidoMaterno);
    sTexto.Trim();
	if(sprintf_s(cApellidoMaterno, "%s", sTexto) < 0){;}

	if(sprintf_s(cMensaje, "%s %s %s", cNombre, cApellidoPaterno, cApellidoMaterno) < 0){;}

	termica.tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 8);
	termica.ponerParrafoTermica(cMensaje, iRenglon, 40, 500);

	iRenglon += 80;
	termica.alinearTexto(CENTRO);

	advance(it, 1);
	cadena = *it;
	if(sprintf_s(cMensaje, cadena.c_str()) < 0){;}
	termica.tipoLetra(&cNewFont, "Arial", &pcOldFont, 11);
	termica.ponerTermica(iRenglon, 250, cMensaje);

	iRenglon += 30;

	string cifraTotal = iDineroElectronico > 0 ? SepararMiles(iDineroElectronico) : "0";
	termica.tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 11);
	// Saldo generado, Mensaje de saldo acumulado
	if(sprintf_s(cMensaje, "$%s", cifraTotal.c_str()) < 0){;}
	termica.ponerTermica(iRenglon, 250, cMensaje);
	
	iRenglon += 70;
	
	// Impresión Meses de Abono Puntual
	advance(it, 1);
	cadena = *it;
	if(sprintf_s(cMensaje, cadena.c_str()) < 0){;}
	termica.ponerTermica(iRenglon, 250, cMensaje);

	iRenglon += 55;

	// Impresion de Monedas de abono puntual

	iMonedasTicket = iMonedasTicket == 4 ? 0 : iMonedasTicket;

	if(iMonedasTicket > 0)
	{
		termica.cargarImagen(dc, "C:\\sys\\progs\\monedaRellenaTicketCoppelMax.bmp", iRenglon, 50);
	} else {
		termica.cargarImagen(dc, "C:\\sys\\progs\\monedaVaciaTicketCoppelMax.bmp", iRenglon, 50);
	}
	if(iMonedasTicket > 1)
	{
		termica.cargarImagen(dc, "C:\\sys\\progs\\monedaRellenaTicketCoppelMax.bmp", iRenglon, 155);
	} else {
		termica.cargarImagen(dc, "C:\\sys\\progs\\monedaVaciaTicketCoppelMax.bmp", iRenglon, 155);
	}
	if(iMonedasTicket > 2)
	{
		termica.cargarImagen(dc, "C:\\sys\\progs\\monedaRellenaTicketCoppelMax.bmp", iRenglon, 260);
	} else {
		termica.cargarImagen(dc, "C:\\sys\\progs\\monedaVaciaTicketCoppelMax.bmp", iRenglon, 260);
	}
	if(iMonedasTicket > 3)
	{
		termica.cargarImagen(dc, "C:\\sys\\progs\\monedaRellenaTicketCoppelMax.bmp", iRenglon, 365);
	} else {
		termica.cargarImagen(dc, "C:\\sys\\progs\\monedaVaciaTicketCoppelMax.bmp", iRenglon, 365);
	}

	iMonedasTicket = 0;

	iRenglon += 150;
	termica.tipoLetra(&cNewFont, "Arial", &pcOldFont, 1);
	termica.ponerTermica(iRenglon, 15, ".");

	termica.terminarImpresion();
}

bool CDlgCapturarAbono::ConsultarMensajeCoppelMax(list<string> &lsMensajes, int tipoProceso)
{
	// Método para obtener los mensajes desde la BD.
	int iVal = 0;
	char cSql[250] = { 0 };
	iVal = sprintf_s(cSql, "SELECT des_mensaje FROM FUN_CONSULTARMENSAJESIMPRESIONCOPPELMAX() WHERE idu_tipoproceso = %ld", tipoProceso);
	bool bRegresa = false;
	CConsultarMensajesCoppelMax Consulta(&odbc);
	string oldMensaje;
	char cOldMensaje[1024];
	char newMensaje[1024];
	string mensaje;

	if(Consulta.Exec(cSql))
	{
		bRegresa = true;
		Consulta.activarCols();

		while(Consulta.leer())
		{
			// Este while se itera por cada registro en la tabla de mensajes.
			// Cada mensaje se irá insertando en la lista de string lsMensajes.
			oldMensaje = Consulta.mensaje;
			iVal = sprintf_s(newMensaje, oldMensaje.c_str());
			replaceString(newMensaje, "=", "Á", newMensaje);
            replaceString(newMensaje, "Ã�", "Á", newMensaje);
            replaceString(newMensaje, "Ã¡", "á", newMensaje);
            replaceString(newMensaje, "_#", "É", newMensaje);
            replaceString(newMensaje, "Ã‰", "É", newMensaje);
            replaceString(newMensaje, "Ã©", "é", newMensaje);
            replaceString(newMensaje, "%", "Ó", newMensaje);
            replaceString(newMensaje,"Ã“", "Ó", newMensaje);
            replaceString(newMensaje,"?", "Í", newMensaje);
            replaceString(newMensaje,"¿", "Ú", newMensaje);
            replaceString(newMensaje,"Ãš", "Ú", newMensaje);
            replaceString(newMensaje,"Ãº", "ú", newMensaje);
            replaceString(newMensaje,"Ã³", "ó", newMensaje);
            replaceString(newMensaje,"Â¡", "¡", newMensaje);
			string str(newMensaje);
			lsMensajes.push_back(str);
		}
	} else {
		Consulta.odbc->GetLastError(Consulta.GetHstmt());
		grabarLog("CImpresiones::ConsultarMensajeCoppelMax::ERROR AL CONSULTAR MENSAJE" );
		grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CA0030", "CImpresiones", "ConsultarMensajeCoppelMax", cSql, m_grid.lEmpleado, "ERROR AL CONSULTAR MENSAJE", Consulta.odbc, m_grid.iMuestraMsg);
	}
	if (iVal){}
	return bRegresa;
}

string CDlgCapturarAbono::SepararMiles(int valor)
{
	// Metodo para separar cifras con comas por miles
	string cadena = to_string(valor);

	for (int i = cadena.length() - 3; i > 0; i -= 3) {
		cadena.insert(i, ",");
	}

	return cadena;	
}
