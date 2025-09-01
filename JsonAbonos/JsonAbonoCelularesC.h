#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "stdafx.h"

class JsonAbonoCelularesC
{
	private:
		struct AbonoC {
			int tienda;
			int ciudad;
			long cliente;
			int caja;
			long importe;
			int meses;
			std::string fechanacimiento;
			char clavesexo;
			std::string fechavencimiento;
			int empleado;
			int cobertura;
			std::string ip;
			std::string nombrecliente;
			std::string poliza;
			std::string fechacobertura;
			std::string motor;
			std::string serie;
			std::string placas;
			std::string area;
			std::string tiposeguro;
			long importemensual;
			long importetotal;
		};

		std::vector<AbonoC> abonos;

	public:
		JsonAbonoCelularesC(void);
		~JsonAbonoCelularesC(void);
		void agregarAbono(int tienda, int ciudad, long cliente, int caja, long importe, int meses,
                     const std::string& fechanacimiento, char clavesexo,
                     const std::string& fechavencimiento, int empleado, int cobertura,
                     const std::string& ip, const std::string& nombrecliente,
                     const std::string& poliza, const std::string& fechacobertura,
                     const std::string& motor, const std::string& serie,
                     const std::string& placas, const std::string& area,
                     const std::string& tiposeguro,
					 long importemensual, long importetotal);
		std::string getJson() const;
		void limpiar(void);
		bool vacio(void);
		void eliminarAbono(CString poliza);
};

