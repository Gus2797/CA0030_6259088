#include "CUtil.h"
#include "general.hpp"

CUtil::CUtil()
{
}

CUtil::~CUtil(void)
{
}

void CUtil::GrabarLog(const char* cTexto)
{
	const std::string LOG_PATH_BASE = "C:\\sys\\mem\\CapturarAbonos";

	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << LOG_PATH_BASE
		<< std::setfill('0') << std::setw(2) << tm.tm_mon + 1
		<< std::setfill('0') << std::setw(2) << tm.tm_mday
		<< ".log";
	std::string sArch = oss.str();

	std::ostringstream ossLog;
	ossLog << std::setfill('0') << std::setw(4) << tm.tm_year + 1900 << "-"
		<< std::setfill('0') << std::setw(2) << tm.tm_mon + 1 << "-"
		<< std::setfill('0') << std::setw(2) << tm.tm_mday << " "
		<< std::setfill('0') << std::setw(2) << tm.tm_hour << ":"
		<< std::setfill('0') << std::setw(2) << tm.tm_min << ":"
		<< std::setfill('0') << std::setw(2) << tm.tm_sec << " "
		<< cTexto << "\n";
	std::string cTextoGrabar = ossLog.str();

	std::ofstream archivo(sArch, std::ios::app); // Abre el archivo en modo append

	if (archivo.is_open())
	{
		archivo << cTextoGrabar;
		archivo.close();
	}
	else
	{
		// Manejar el error al abrir el archivo (por ejemplo, registrar un error)
		// Puedes usar OutputDebugString o tu propio mecanismo de logging de errores.
		OutputDebugStringA(("Error al abrir el archivo de log: " + sArch + "\n").c_str());
	}
}

void CUtil::GrabarLog(CString sLog)
{
	char cLog[2048] = { 0 };
	if (sprintf_s(cLog, sLog) < 0) { ; }
	this->GrabarLog(cLog);

}

void CUtil::ClickCenter()
{
	int iWidth = 0;
	int iHeight = 0;
	gnConsultarResolucion(iWidth, iHeight);
	iWidth = iWidth / 2;
	iHeight = iHeight / 2;
	Click(iWidth, iHeight);
}

void CUtil::Click(int iWidth, int iHeight)
{
	SetCursorPos(iWidth, iHeight);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void CUtil::SendAltTab()
{
	// press DOWN "Alt-Tab"
	keybd_event(VK_MENU, 0, 0, 0);
	keybd_event(VK_TAB, 0, 0, 0);
	Sleep(100);
	// stop pressing "Alt-Tab"
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
}