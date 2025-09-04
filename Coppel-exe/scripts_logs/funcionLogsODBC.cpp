#define ODBCVER 0x0351
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>

// Nueva función de manejo de errores
void mostrarError(SQLRETURN ret, SQLHANDLE handle, SQLSMALLINT type, const std::string& msg) {
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        SQLCHAR sqlState[6]; // SQLSTATE es de 5 caracteres + nulo
        SQLCHAR message[1024];
        SQLINTEGER nativeError;
        SQLSMALLINT textLength;

        // Intentar obtener el registro de diagnóstico
        if (SQLGetDiagRecA(type, handle, 1, sqlState, &nativeError, message,
            sizeof(message), &textLength) == SQL_SUCCESS) {
            std::cerr << "--- Diagnostico de Error ---" << std::endl;
            std::cerr << "Mensaje: " << msg << std::endl;
            std::cerr << "SQLSTATE: " << sqlState << std::endl;
            std::cerr << "Error Nativo: " << nativeError << std::endl;
            std::cerr << "Mensaje de ODBC: " << message << std::endl;
            std::cerr << "----------------------------" << std::endl;
        }
        else {
            std::cerr << "Error de ODBC pero no se pudo obtener diagnóstico: " << msg << std::endl;
        }
    }
}

// data de db 
//const std::string CONNECTION_STRING = "dbname=postgres user=postgres password=123 host=localhost port=5432";
bool conectarPostgreSQL(SQLHENV& hEnv, SQLHDBC& hDbc) {
    SQLRETURN ret;

    // 1. Allocate environment
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    mostrarError(ret, hEnv, SQL_HANDLE_ENV, "Error en el entorno ODBC.");
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) return false;

    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    mostrarError(ret, hEnv, SQL_HANDLE_ENV, "Error al establecer la version de ODBC.");
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) return false;

    // 2. Allocate connection handle
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    mostrarError(ret, hDbc, SQL_HANDLE_DBC, "Error en el handle de conexion.");
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) return false;

    // 3. Build DSN-less connection string
    SQLCHAR connStr[] =
        //"Driver={PostgreSQL ODBC Driver(UNICODE)};"
        //"Driver={PostgreSQL Unicode(x64)};" - 64 bits
        "Driver={PostgreSQL Unicode};" // - 32 bits
        "Server=localhost;"
        "Port=5432;"
        "Database=tienda0902;"
        "Uid=postgres;"
        "Pwd=admin;";

    SQLCHAR outStr[1024];
    SQLSMALLINT outLen;

    ret = SQLDriverConnectA(hDbc, NULL, connStr, SQL_NTS, outStr, sizeof(outStr), &outLen, SQL_DRIVER_NOPROMPT);
    mostrarError(ret, hDbc, SQL_HANDLE_DBC, "Error al conectar a PostgreSQL.");
    return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
}

// funcion para insertar logs con odbc sin checkerror
bool enviarLogParams(SQLHDBC hDbc, int cliente, int factura, const std::string& mensaje, const std::string& fechacompra, int tienda, const std::string& fuente) { //recibe 5 params
    SQLHSTMT hStmt; // statement sql
    SQLRETURN ret; // retorno de odbc

    // Crear statement
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    // validacion si se cre� statement
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) return false;

    // Consulta parametrizada: SELECT * FROM fun_guardarlogbonificaciondiaria(?, ?, ?, ?, ?, ?)
    SQLCHAR query[] = "SELECT * FROM fun_guardarlogbonificaciondiaria(?, ?, ?, ?, ?, ?)";
    // preparar consulta
    ret = SQLPrepareA(hStmt, query, SQL_NTS);
    // validacion de preparacion de consulta
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::cerr << "[Error] SQLPrepareA" << std::endl;
        return false;
    }

    // Bind de par�metros ordenados
    // param: cliente
    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER)&cliente, 0, NULL);
    // param: factura
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER)&factura, 0, NULL);
    // param: mensaje
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, mensaje.size(), 0, (SQLPOINTER)mensaje.c_str(), 0, NULL);
    // param: fechacompra
    SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, fechacompra.size(), 0, (SQLPOINTER)fechacompra.c_str(), 0, NULL);
    // param: tienda
    SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, (SQLPOINTER)&tienda, 0, NULL);
    // param: fuente
    SQLBindParameter(hStmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, fuente.size(), 0, (SQLPOINTER)fuente.c_str(), 0, NULL);

    // Ejecutar
    ret = SQLExecute(hStmt);
    // validacion dfe ejecucion
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::cerr << "[Error] SQLExecute" << std::endl;
        return false;
    }

    // Leer resultados si retorna algo
    char buffer[256];
    // indicador de longitud
    SQLLEN ind;

    // leer data de resultados
    while (SQLFetch(hStmt) == SQL_SUCCESS) {
        // ontener data de primer columna
        SQLGetData(hStmt, 1, SQL_C_CHAR, buffer, sizeof(buffer), &ind);
        // mostrar resultado
        std::cout << "Resultado: " << buffer << std::endl;
    }
    // liberar recursos
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    // retun existoso
    return true;
}

int main() {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    // Ejecucion de funciones
    std::cout << "Ejecutando main() " << std::endl;

    if (!conectarPostgreSQL(hEnv, hDbc)) {
        std::cerr << "El programa termino debido a un error de conexion." << std::endl;
        system("pause");
        return 1;
    }
    else {
        //std::cout << "Conexion exitosa" << std::endl;
        enviarLogParams(hDbc, 10203, 240340, "este es el log....", "2025-08-20", 803, "este log viene de.....");
        system("pause");
    }

    //funcion con odbc
    //SQLHDBC hDbc = conexionODBC(L"localhost", L"postgres", L"postgres", L"123", 5432);
    //std::cout << hDbc << std::endl;
    //conectaODBC();

    //enviarLogNoError("Factura 9432456", 14, 8, 2025, 101);
    //enviarLogParams(conexion, cliente, factura, mesaje_log, fechacompra, tienda, fuente_log);

    return 0; // Devuelve un c�digo de �xito
}