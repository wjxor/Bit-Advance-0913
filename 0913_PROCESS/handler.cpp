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

	if (b == TRUE) { // 프로세스 실행 성공
		WaitForInputIdle(pi.hProcess, INFINITE);
		MessageBox(hDlg, TEXT("프로세스 생성 완료"), TEXT("알림"), MB_OK);

		SetDlgItemInt(hDlg, IDC_EDIT5, (UINT)pi.hProcess, 0);
		SetDlgItemInt(hDlg, IDC_EDIT6, (UINT)pi.dwProcessId, 0);
	}
}

// mspaint.ext : 그림판
void OnTerminateProcess(HWND hDlg) {
	HANDLE hProcess = (HANDLE)GetDlgItemInt(hDlg, IDC_EDIT5, 0, 0);
	TerminateProcess(hProcess, -1);
	WaitForSingleObject(hProcess, INFINITE);
	MessageBox(hDlg, TEXT("프로세스 종료"), TEXT("알림"), MB_OK);
}

void OnGetExitCode(HWND hDlg) {
	DWORD code;
	HANDLE hProcess = (HANDLE)GetDlgItemInt(hDlg, IDC_EDIT5, 0, 0);

	GetExitCodeProcess(hProcess, &code);

	TCHAR temp[100];
	if (code == STILL_ACTIVE) {
		wsprintf(temp, TEXT("살아있다"));
	}
	else {
		wsprintf(temp, TEXT("죽었다:%d"), code);
	}

	// 만약 내가 관리하고 있던 프로세스가 종료되었다면
	// 해당 프로세스의 핸들을 Close해야한다.
	// why? 커널오브젝트를 메모리에서 제거해야 하기 떄문이다.

	SetDlgItemInt(hDlg, IDC_EDIT6, code, 0);
}

void OnCloseHandle(HWND hDlg) {
	// 핸들값은 양의 정수이기 때문에 양의 정수값이 동일하면 동일한 핸들이다.
	HANDLE hProcess = (HANDLE)GetDlgItemInt(hDlg, IDC_EDIT5, 0, 0);

	// 핸들테이블에서 제거, 커널객체의 사용카운트 감소
	CloseHandle(hProcess);
}