#include"Shell.h"
Shell::Shell() {
	
}
Shell::Shell(LPWSTR process) {
	m_hChildInputRead = NULL;
	m_hChildInputWrite = NULL;
	m_hChildOutputRead = NULL;
	m_hChildOutputWrite = NULL;
	RunProcess(process);
}
Shell::~Shell() {
	StopProcess();
}
bool Shell::RunProcess(LPWSTR process) {
	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof sa;
	if (FALSE == CreatePipe(&m_hChildOutputRead, &m_hChildOutputWrite, &sa, 0)) {
		return false;
	}
	if (FALSE == CreatePipe(&m_hChildInputRead, &m_hChildInputWrite, &sa, 0)) {
		CloseHandle(m_hChildOutputRead);
		CloseHandle(m_hChildOutputWrite);
		return false;
	}
	ZeroMemory(&m_cmdPI, sizeof m_cmdPI);
	STARTUPINFO si;
	GetStartupInfo(&si);

	si.cb = sizeof STARTUPINFO;
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = m_hChildInputRead;
	si.hStdOutput = m_hChildOutputWrite;
	si.hStdError = m_hChildOutputWrite;

	if (FALSE == CreateProcess(process, NULL, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &m_cmdPI)) {
		::CloseHandle(m_hChildInputRead);
		::CloseHandle(m_hChildInputWrite);
		::CloseHandle(m_hChildOutputRead);
		::CloseHandle(m_hChildOutputWrite);
		ZeroMemory(&m_cmdPI, sizeof PROCESS_INFORMATION);
		return false;
	}
	return true;
}
bool Shell::StopProcess(void) {
	::CloseHandle(m_hChildInputRead);
	::CloseHandle(m_hChildInputWrite);
	::CloseHandle(m_hChildOutputRead);
	::CloseHandle(m_hChildOutputWrite);
	TerminateProcess(m_cmdPI.hProcess, -1);
	CloseHandle(m_cmdPI.hProcess);
	CloseHandle(m_cmdPI.hThread);

	ZeroMemory(&m_cmdPI, sizeof PROCESS_INFORMATION);
	return true;
}
bool Shell::GetOutput(const string &endStr, int timeout, string &outstr) 
{
	if (NULL == m_hChildOutputRead)
	{
		return false;
	}

	outstr = "";
	char buffer[4096] = { 0 };
	DWORD readBytes = 0;
	while (timeout > 0)
	{ 
		if (FALSE == PeekNamedPipe(m_hChildOutputRead, buffer, sizeof(buffer) - 1, &readBytes, 0, NULL))
		{
			return false;
		}
  
		if (0 == readBytes)
		{
			::Sleep(200);
			timeout -= 200;
			continue;
		}

		readBytes = 0;
		if (::ReadFile(m_hChildOutputRead, buffer, sizeof(buffer) - 1, &readBytes, NULL))
		{
			outstr.insert(outstr.end(), buffer, buffer + readBytes);
			size_t pos = outstr.rfind(endStr);
			if (string::npos == pos)
			{
				continue;
			}
			if (pos == outstr.size() - endStr.size())
			{
				return true;//找到数据  
			}
		}
		else
		{
			return false;
		}
	}

	return false;
}
bool Shell::SetInput(const string &cmd)//执行命令 
{

	if (NULL == m_hChildInputWrite)
	{
		return false;
	}

	string tmp = cmd + "\n";
	DWORD writeBytes = 0;
	if (FALSE == ::WriteFile(m_hChildInputWrite, tmp.c_str(), tmp.size(), &writeBytes, NULL))
	{
		return false;
	}
	return true;
}