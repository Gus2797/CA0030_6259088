#include "CGenerarImagenImpresion.h"

class CImpresiones
{
public:
	CImpresiones( );
	~CImpresiones( );

private:
	CFont cNewFont;
	CFont *pcOldFont;

public:
	void imprimirMensajeInvitacionBancoppel( );
	void ImprimirMensajeActualizarDatos( char *cNombre, char *cApellidoPaterno, char *cApellidoMaterno );
};