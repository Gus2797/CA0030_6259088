#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "stdafx.h"

class JsonAbonoCelularesCL
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
		JsonAbonoCelularesCL(void);
		~JsonAbonoCelularesCL(void);
		void limpiar(void);
		bool vacio(void);
		void eliminarAbono(CString poliza);
};

