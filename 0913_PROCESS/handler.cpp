//handler.cpp

#include "std.h"

INT_PTR OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam)) {
	case IDCANCEL: EndDialog(hDlg, IDCANCEL); return TRUE;
	case IDC_BUTTON2: OnCreateProcess(hDlg);	return TRUE;
	case IDC_BUTTON3: OnTerminateProcess(hDlg);	return TRUE;
	case IDC_BUTTON4: OnGetExitCode(hDlg);	return TRUE;
	case IDC_BUTTON5: OnCloseHandle(hDlg);	return TRUE;
	}

	return FALSE;
}

void OnCreateProcess(HWND hDlg) {
	TCHAR pname[100];
	GetDlgItemText(hDlg, IDC_EDIT4, pname, _countof(pname));

	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof(si) };

	BOOL b = CreateProcess(0, pname, 0, 0, FALSE, NORMAL_PRIORITY_CLASS, 0, 0, &si, &pi);

	if (b == TRUE) { // ���μ��� ���� ����
		WaitForInputIdle(pi.hProcess, INFINITE);
		MessageBox(hDlg, TEXT("���μ��� ���� �Ϸ�"), TEXT("�˸�"), MB_OK);

		SetDlgItemInt(hDlg, IDC_EDIT5, (UINT)pi.hProcess, 0);
		SetDlgItemInt(hDlg, IDC_EDIT6, (UINT)pi.dwProcessId, 0);
	}
}

// mspaint.ext : �׸���
void OnTerminateProcess(HWND hDlg) {
	HANDLE hProcess = (HANDLE)GetDlgItemInt(hDlg, IDC_EDIT5, 0, 0);
	TerminateProcess(hProcess, -1);
	WaitForSingleObject(hProcess, INFINITE);
	MessageBox(hDlg, TEXT("���μ��� ����"), TEXT("�˸�"), MB_OK);
}

void OnGetExitCode(HWND hDlg) {
	DWORD code;
	HANDLE hProcess = (HANDLE)GetDlgItemInt(hDlg, IDC_EDIT5, 0, 0);

	GetExitCodeProcess(hProcess, &code);

	TCHAR temp[100];
	if (code == STILL_ACTIVE) {
		wsprintf(temp, TEXT("����ִ�"));
	}
	else {
		wsprintf(temp, TEXT("�׾���:%d"), code);
	}

	// ���� ���� �����ϰ� �ִ� ���μ����� ����Ǿ��ٸ�
	// �ش� ���μ����� �ڵ��� Close�ؾ��Ѵ�.
	// why? Ŀ�ο�����Ʈ�� �޸𸮿��� �����ؾ� �ϱ� �����̴�.

	SetDlgItemInt(hDlg, IDC_EDIT6, code, 0);
}

void OnCloseHandle(HWND hDlg) {
	// �ڵ鰪�� ���� �����̱� ������ ���� �������� �����ϸ� ������ �ڵ��̴�.
	HANDLE hProcess = (HANDLE)GetDlgItemInt(hDlg, IDC_EDIT5, 0, 0);

	// �ڵ����̺��� ����, Ŀ�ΰ�ü�� ���ī��Ʈ ����
	CloseHandle(hProcess);
}