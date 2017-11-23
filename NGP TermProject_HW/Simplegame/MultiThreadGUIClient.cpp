#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "resource.h"
#include <CommCtrl.h>

using namespace std;

#define SERVERIP	"127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 512

//��ȭ���� ���ν���
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
//���� ��Ʈ�� ����Լ�
void DisPlayText(char * fmt, ...);
//���� ��� �Լ�

// ����� ���� ������ ���� �Լ�
int recvn(SOCKET s, char *buf, int len, int flags);
// ���� ��� ������ �Լ�
DWORD WINAPI ClientMain(LPVOID arg);

SOCKET sock;
char buf[BUFSIZE];
HANDLE hReadEvent, hWriteEvent;
HWND hSendButton;
HWND hEdit1, hEdit2, hEditProgress;
HWND hfileOpen;

char fileName[30];
OPENFILENAME OFN;
char str[300];
char lpstrFile[MAX_PATH] = "";
char filepath[MAX_PATH]; // ���� ���


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �̺�Ʈ ����
	hReadEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (hReadEvent == NULL) return 1;
	hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hWriteEvent == NULL) return 1;

	// ���� ��� ������ ����
	CreateThread(NULL, 0, ClientMain, NULL, 0, NULL);
	// ��ȭ���� ����
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);


	// �̺�Ʈ ���� 
	CloseHandle(hReadEvent);
	CloseHandle(hWriteEvent);

	//closesocket()
	closesocket(sock);

	// ��������
	WSACleanup();
	return 0;
}

// ��ȭ���� ���ν���
BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		hEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
		hEdit2 = GetDlgItem(hDlg, IDC_EDIT2);
		hEditProgress = GetDlgItem(hDlg, IDC_PROGRESS1);
		hSendButton = GetDlgItem(hDlg, IDOK);
		hfileOpen = GetDlgItem(hDlg, IDC_BUTTON1);
		SendMessage(hEdit1, EM_SETLIMITTEXT, BUFSIZE, 0);
		SendMessage(hEditProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
		SendMessage(hEditProgress, PBM_SETPOS, 0, 0);

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EnableWindow(hSendButton, FALSE); // ������ ��ư ��Ȱ��ȭ
			EnableWindow(hfileOpen, FALSE);
			WaitForSingleObject(hReadEvent, INFINITE); // �б� �Ϸ� ��ٸ���
			GetDlgItemText(hDlg, IDC_EDIT1, buf, BUFSIZE + 1);
			SetEvent(hWriteEvent);// ����Ϸ� �˸���
			SetFocus(hEdit1);
			SendMessage(hEdit1, EM_SETSEL, 0, -1);
			return TRUE;
		case IDC_BUTTON1:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hDlg;
			OFN.lpstrFilter = "��� ���� (*.*)\0*.*\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = MAX_PATH;
			OFN.lpstrFileTitle = fileName;
			OFN.nMaxFileTitle = MAX_PATH;
			OFN.lpstrInitialDir = "C:\\Users\\Jino\\Desktop\\��������\\2017-2�б�\\NetworkGamePrograming\\MultiThreadGUI";
			if (GetOpenFileName(&OFN) != 0) {
				wsprintf(str, "%s ������ ����.", OFN.lpstrFileTitle);
				MessageBox(hDlg, str, "���� ���� ����", MB_OK);
			}
			SetDlgItemText(hDlg, IDC_EDIT1, OFN.lpstrFileTitle);
			return 0;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}

		return FALSE;
	}
	return FALSE;
}

void DisPlayText(char *fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);

	char cbuf[BUFSIZE + 256];
	vsprintf(cbuf, fmt, arg);

	int nLength = GetWindowTextLength(hEdit2);
	SendMessage(hEdit2, EM_SETSEL, nLength, nLength);
	SendMessage(hEdit2, EM_REPLACESEL, FALSE, (LPARAM)cbuf);

	va_end(arg);
}

// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ���� �Լ� ���� ���
void err_display(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&lpMsgBuf, 0, NULL);
	DisPlayText("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0)
	{
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}

// TCP Ŭ���̾�Ʈ ���� �κ�
DWORD WINAPI ClientMain(LPVOID arg)
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;


	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");



	//-----------------------------------����� ���� �̸� �Է�

	// ������ ��ſ� ����� ����
	//char buf[BUFSIZE];
	int fileSize =0;			// ���� ũ�⸦ ������ ����

	ZeroMemory(buf, BUFSIZE);
	int sendCount;					// ����� ����
	int sendCountMod;				// ������
	float TotalSend = 0;
	char fileName[30];
	FILE *fp;
	
	//-------------------------------------

	//-------------------------------------

	// ������ ������ ���
	while (1)
	{
		WaitForSingleObject(hWriteEvent, INFINITE); // ���� �Ϸ� ��ٸ���

		// ���ڿ� ���̰� 0 �̸� ������ ����
		if (strlen(buf) == 0)
		{
			EnableWindow(hSendButton, TRUE); // ������ ��ư Ȱ��ȭ
			SetEvent(hReadEvent);
			continue;
		}
		//strcpy(fileName, OFN.lpstrFileTitle);
		memcpy(fileName, buf, sizeof(fileName));

		retval = send(sock, fileName, sizeof(fileName), 0);
		//EnableWindow(hSendButton, TRUE); // ������ ��ư Ȱ��ȭ
		//SetEvent(hReadEvent);
		////////////////////////////////////////////


		//������ �ޱ�
		//�����̸� ����
		//retval = recvn(sock, fileName, sizeof(fileName), 0);
		buf[retval] = '\0';
		//-------------���� ������ ũ�⸦ ������ (�������� �Ѿ�� ������!)
		retval = recvn(sock, (char *)&fileSize, sizeof(fileSize), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			return 1;
		}

		fp = fopen(fileName, "wb+");
		ZeroMemory(buf, BUFSIZE);
		
		// Ŭ���̾�Ʈ�� ������ ���
		while (retval != 0)
		{
			// ������ �ޱ�(���� ����)
			//system("cls");
			retval = recvn(sock, buf, BUFSIZE, 0);
			fwrite(buf, 1, retval, fp);

			TotalSend += retval;
			//DisplayText("Ŭ���̾�Ʈ[%s] : ������� �ٿ� : %d (%%) \n", inet_ntoa(clientaddr.sin_addr), (int)((TotalDown / fileSize) * 100));
			SendMessage(hEditProgress, PBM_SETPOS, (int)((TotalSend / fileSize) * 100), 0);
		}
		fclose(fp);
		DisPlayText("���� �������� ũ�� : %d\n", fileSize);
		//EnableWindow(hSendButton, TRUE); // ������ ��ư Ȱ��ȭ
		SetEvent(hReadEvent); // �б� �Ϸ� �˸���
	return 1;
	}
}
