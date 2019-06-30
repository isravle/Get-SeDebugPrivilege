#include <stdio.h>
#include <windows.h>

BOOL(WINAPI * RtlAdjustPrivilege)(IN ULONG Privilege, IN BOOL Enable, IN BOOL CurrentThread, OUT PULONG pPreviousState);

BOOL Get_SeDebugPrivilege()
{
	HMODULE ntDll = GetModuleHandleA("ntdll");

	RtlAdjustPrivilege = (NTSTATUS(WINAPI *)(IN ULONG Privilege, IN BOOL Enable, IN BOOL CurrentThread, OUT PULONG pPreviousState))GetProcAddress(ntDll, "RtlAdjustPrivilege");

	ULONG privId = 0x14;
	ULONG previousState;
	BOOL status;
	status = RtlAdjustPrivilege(privId, TRUE, FALSE, &previousState);
	if (!status)
		printf("Privilege \'%d\' OK\n", privId);
	else
		printf("RtlAdjustPrivilege (%x) %08x\n", privId, status);
	return status;
}

int main() {

	printf("Click enter to get SeDebugPrivilege token");
	getchar();
	BOOL ganav = Get_SeDebugPrivilege();

	if (ganav == 0) {
		getchar();
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, 948); // 948 PID of LSASS 
		printf("LSASS handle -> 0x%x\r\n", hProcess);
		printf("Go check Process Hacker and find the Handle to LSASS.exe\r\n", hProcess);
		printf("Enter to closehandle\r\n", hProcess);
		getchar();
		CloseHandle(hProcess);
	}
	else {
		printf("its looks like that you dont have admin priviliges..");
	}

	return 0;
}
