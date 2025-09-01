#include "JsonAbonoCelularesC.h"


JsonAbonoCelularesC::JsonAbonoCelularesC(void)
{
}


JsonAbonoCelularesC::~JsonAbonoCelularesC(void)
{
}

void JsonAbonoCelularesC::agregarAbono(int tienda, int ciudad, long cliente, int caja, long importe, int meses,
                                   const std::string& fechanacimiento, char clavesexo,
                                   const std::string& fechavencimiento, int empleado, int cobertura,
                                   const std::string& ip, const std::string& nombrecliente,
                                   const std::string& poliza, const std::string& fechacobertura,
                                   const std::string& motor, const std::string& serie,
                                   const std::string& placas, const std::string& area,
                                   const std::string& tiposeguro,
								   long importemensual, long importetotal) {
    // Verificar si el abono ya existe en base al cliente y la poliza
    for (size_t i = 0; i < abonos.size(); ++i) {
        if (abonos[i].cliente == cliente && abonos[i].poliza == poliza) {
            // El abono ya existe, sustituirlo por el nuevo registro
            abonos[i].tienda = tienda;
            abonos[i].ciudad = ciudad;
            abonos[i].cliente = cliente;
            abonos[i].caja = caja;
            abonos[i].importe = importe;
            abonos[i].meses = meses;
            abonos[i].fechanacimiento = fechanacimiento;
            abonos[i].clavesexo = clavesexo;
            abonos[i].fechavencimiento = fechavencimiento;
            abonos[i].empleado = empleado;
            abonos[i].cobertura = cobertura;
            abonos[i].ip = ip;
            abonos[i].nombrecliente = nombrecliente;
            abonos[i].poliza = poliza;
            abonos[i].fechacobertura = fechacobertura;
            abonos[i].motor = motor;
            abonos[i].serie = serie;
            abonos[i].placas = placas;
            abonos[i].area = area;
            abonos[i].tiposeguro = tiposeguro;
			abonos[i].importemensual = importemensual;
			abonos[i].importetotal = importetotal;
            return;
        }
    }

    // El abono no existe, agregarlo como un nuevo abono en el vector
    AbonoC abono;
    abono.tienda = tienda;
    abono.ciudad = ciudad;
    abono.cliente = cliente;
    abono.caja = caja;
    abono.importe = importe;
    abono.meses = meses;
    abono.fechanacimiento = fechanacimiento;
    abono.clavesexo = clavesexo;
    abono.fechavencimiento = fechavencimiento;
    abono.empleado = empleado;
    abono.cobertura = cobertura;
    abono.ip = ip;
    abono.nombrecliente = nombrecliente;
    abono.poliza = poliza;
    abono.fechacobertura = fechacobertura;
    abono.motor = motor;
    abono.serie = serie;
    abono.placas = placas;
    abono.area = area;
    abono.tiposeguro = tiposeguro;
	abono.importemensual = importemensual;
	abono.importetotal = importetotal;

    abonos.push_back(abono);
}

std::string JsonAbonoCelularesC::getJson() const {
    std::string json = "{\"abonos\":[";
    for (size_t i = 0; i < abonos.size(); ++i) {
        json += "{";
        json += "\"tienda\": " + std::to_string(abonos[i].tienda) + ",";
        json += "\"ciudad\": " + std::to_string(abonos[i].ciudad) + ",";
        json += "\"cliente\":" + std::to_string(abonos[i].cliente) + ",";
        json += "\"caja\": " + std::to_string(abonos[i].caja) + ",";
        json += "\"importe\": " + std::to_string(abonos[i].importe) + ",";
        json += "\"meses\": " + std::to_string(abonos[i].meses) + ",";
        json += "\"fechanacimiento\": \"" + abonos[i].fechanacimiento + "\",";
        json += "\"clavesexo\": \"" + std::string(1, abonos[i].clavesexo) + "\",";
        json += "\"fechavencimiento\": \"" + abonos[i].fechavencimiento + "\",";
        json += "\"empleado\": " + std::to_string(abonos[i].empleado) + ",";
        json += "\"cobertura\": " + std::to_string(abonos[i].cobertura) + ", ";
        json += "\"ip\": \"" + abonos[i].ip + "\",";
        json += "\"nombrecliente\": \"" + abonos[i].nombrecliente + "\",";
        json += "\"poliza\": \"" + abonos[i].poliza + "\",";
        json += "\"fechacobertura\": \"" + abonos[i].fechacobertura + "\",";
        json += "\"motor\": \"" + abonos[i].motor + "\",";
        json += "\"serie\": \"" + abonos[i].serie + "\",";
        json += "\"placas\": \"" + abonos[i].placas + "\",";
        json += "\"area\":\"" + abonos[i].area + "\",";
        json += "\"tiposeguro\":\"" + abonos[i].tiposeguro + "\",";
		json += "\"importemensual\":\"" + std::to_string(abonos[i].importemensual) + "\",";
		json += "\"importetotal\":\"" + std::to_string(abonos[i].importetotal) + "\"";
        json += "}";
        if (i != abonos.size() - 1) {
            json += ",";
        }
    }
    json += "]}";

	json = "'" + json + "'";

    return json;
}


bool JsonAbonoCelularesC::vacio() {
	if(abonos.size() > 0){
		return false;
	}
	return true;
}

void JsonAbonoCelularesC::limpiar() {
    abonos.clear();
}


void JsonAbonoCelularesC::eliminarAbono(CString poliza){
	CString polizaAbono = "";
	int tamanio = 0;
	int eliminar = -1;
	std::vector<AbonoC> abonosCapturados;
	if(!this->vacio())
	{
		tamanio = abonos.size();

		for(int i = 0; i < tamanio; i ++){
			polizaAbono.Format("%s", abonos.at(i).poliza);

			if(poliza.CompareNoCase(polizaAbono) == 0)
			{
				eliminar = i;
			} else {
				abonosCapturados.push_back(abonos.at(i));
			}
		}

		if(eliminar > -1)
		{
			this->abonos.swap(abonosCapturados);
		}
	}
}