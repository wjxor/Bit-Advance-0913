//start.cpp

#include "std.h"

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
	{
		return TRUE;
	}
	case WM_COMMAND: {
		return OnCommand(hDlg, wParam, lParam);
		switch (LOWORD(wParam))	{
		case IDCANCEL: EndDialog(hDlg, IDCANCEL); return TRUE;
		}
	}
	}
	return FALSE;
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	INT_PTR ret = DialogBox(hInst,// instance
		MAKEINTRESOURCE(IDD_DIALOG1), // 다이얼로그 선택
		0, // 부모 윈도우
		DlgProc); // Proc..

	return 0;
}
