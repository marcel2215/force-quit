#include <windows.h>

static void terminate_foreground()
{
	DWORD pid;
	GetWindowThreadProcessId(GetForegroundWindow(), &pid);

	HANDLE hnd = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, TRUE, pid);

	TerminateProcess(hnd, 0);
	CloseHandle(hnd);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!RegisterHotKey(NULL, 1, MOD_WIN | MOD_NOREPEAT, VK_F4))
	{
		return 1;
	}

	MSG msg{};
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY)
		{
			terminate_foreground();
		}
	}

	UnregisterHotKey(NULL, 1);
	return 0;
}
