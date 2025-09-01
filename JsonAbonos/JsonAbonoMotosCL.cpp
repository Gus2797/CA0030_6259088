#include "JsonAbonoMotosCL.h"


JsonAbonoMotosCL::JsonAbonoMotosCL(void)
{
}


JsonAbonoMotosCL::~JsonAbonoMotosCL(void)
{
}

void JsonAbonoMotosCL::agregarAbono(long cliente, long importe, int meses, int tienda, long minimo, int caja,
                                    int empleado, int ciudad, const std::string& area, const std::string& poliza) {
    // Verificar si el abono ya existe en base al cliente y la poliza
    for (size_t i = 0; i < abonos.size(); ++i) {
        if (abonos[i].cliente == cliente && abonos[i].poliza == poliza) {
            // El abono ya existe, sustituirlo por el nuevo registro
            abonos[i].cliente = cliente;
            abonos[i].importe = importe;
            abonos[i].meses = meses;
            abonos[i].tienda = tienda;
            abonos[i].minimo = minimo;
            abonos[i].caja = caja;
            abonos[i].empleado = empleado;
            abonos[i].poliza = poliza;
			abonos[i].area = area;
			abonos[i].ciudad = ciudad;
            return;
        }
    }

    // El abono no existe, agregarlo como un nuevo abono en el vector
    Abono abono;
    abono.cliente = cliente;
    abono.importe = importe;
    abono.meses = meses;
    abono.tienda = tienda;
    abono.minimo = minimo;
    abono.caja = caja;
    abono.empleado = empleado;
	abono.area = area;
    abono.poliza = poliza;
	abono.ciudad = ciudad;

    abonos.push_back(abono);
}

std::string JsonAbonoMotosCL::getJson() const {
    std::string json = "{ \"abonos\": [";
    for (size_t i = 0; i < abonos.size(); ++i) {
        json += "{";
        json += "\"cliente\": " + std::to_string(abonos[i].cliente) + ",";
        json += "\"importe\": " + std::to_string(abonos[i].importe) + ",";
        json += "\"meses\": " + std::to_string(abonos[i].meses) + ",";
        json += "\"tienda\": " + std::to_string(abonos[i].tienda) + ",";
        json += "\"minimo\": " + std::to_string(abonos[i].minimo) + ",";
        json += "\"caja\": " + std::to_string(abonos[i].caja) + ",";
        json += "\"empleado\": " + std::to_string(abonos[i].empleado) + ",";
		json += "\"ciudad\": " + std::to_string(abonos[i].ciudad) + ",";
        json += "\"area\":\"" + abonos[i].area + "\",";
        json += "\"poliza\": \"" + abonos[i].poliza + "\"";
		json += "}";
        if (i != abonos.size() - 1) {
            json += ",";
        }
    }
    json += "]}";

	json = "'" + json + "'";

    return json;
}

bool JsonAbonoMotosCL::vacio() {
	if(abonos.size() > 0){
		return false;
	}
	return true;
}

void JsonAbonoMotosCL::limpiar() {
    abonos.clear();
}