#pragma once
#include <iostream>
#include <vector>
#include <string>

class JsonAbonoMotosCL
{
public:

	private:
    struct Abono {
        long cliente;
        long importe;
        int meses;
        int tienda;
        long minimo;
        int caja;
        int empleado;
		int ciudad;
		std::string area;
        std::string poliza;
    };

    std::vector<Abono> abonos;

	public:
		void agregarAbono(long cliente, long importe, int meses, int tienda, long minimo, int caja,
                     int empleado, int ciudad, const std::string& area, const std::string& poliza);
		std::string getJson() const;
		JsonAbonoMotosCL(void);
		~JsonAbonoMotosCL(void);
		void limpiar(void);
		bool vacio(void);
};

