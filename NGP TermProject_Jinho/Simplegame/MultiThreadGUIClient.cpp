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

//대화상자 프로시저
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
//편집 컨트롤 출력함수
void DisPlayText(char * fmt, ...);
//오류 출력 함수

// 사용자 정의 데이터 수신 함수
int recvn(SOCKET s, char *buf, int len, int flags);
// 소켓 통신 스레드 함수
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
char filepath[MAX_PATH]; // 파일 경로


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 이벤트 생성
	hReadEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (hReadEvent == NULL) return 1;
	hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hWriteEvent == NULL) return 1;

	// 소켓 통신 스레드 생성
	CreateThread(NULL, 0, ClientMain, NULL, 0, NULL);
	// 대화상자 생성
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);


	// 이벤트 제거 
	CloseHandle(hReadEvent);
	CloseHandle(hWriteEvent);

	//closesocket()
	closesocket(sock);

	// 윈속종료
	WSACleanup();
	return 0;
}

// 대화상자 프로시저
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
			EnableWindow(hSendButton, FALSE); // 보내기 버튼 비활성화
			EnableWindow(hfileOpen, FALSE);
			WaitForSingleObject(hReadEvent, INFINITE); // 읽기 완료 기다리기
			GetDlgItemText(hDlg, IDC_EDIT1, buf, BUFSIZE + 1);
			SetEvent(hWriteEvent);// 쓰기완료 알리기
			SetFocus(hEdit1);
			SendMessage(hEdit1, EM_SETSEL, 0, -1);
			return TRUE;
		case IDC_BUTTON1:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hDlg;
			OFN.lpstrFilter = "모든 파일 (*.*)\0*.*\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = MAX_PATH;
			OFN.lpstrFileTitle = fileName;
			OFN.nMaxFileTitle = MAX_PATH;
			OFN.lpstrInitialDir = "C:\\Users\\Jino\\Desktop\\수업폴더\\2017-2학기\\NetworkGamePrograming\\MultiThreadGUI";
			if (GetOpenFileName(&OFN) != 0) {
				wsprintf(str, "%s 파일을 선택.", OFN.lpstrFileTitle);
				MessageBox(hDlg, str, "파일 열기 성공", MB_OK);
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

// 소켓 함수 오류 출력 후 종료
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

// 소켓 함수 오류 출력
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

// TCP 클라이언트 시작 부분
DWORD WINAPI ClientMain(LPVOID arg)
{
	int retval;

	// 윈속 초기화
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



	//-----------------------------------사용자 파일 이름 입력

	// 데이터 통신에 사용할 변수
	//char buf[BUFSIZE];
	int fileSize =0;			// 파일 크기를 저장할 변수

	ZeroMemory(buf, BUFSIZE);
	int sendCount;					// 나누어서 전송
	int sendCountMod;				// 나머지
	float TotalSend = 0;
	char fileName[30];
	FILE *fp;
	
	//-------------------------------------

	//-------------------------------------

	// 서버와 데이터 통신
	while (1)
	{
		WaitForSingleObject(hWriteEvent, INFINITE); // 쓰기 완료 기다리기

		// 문자열 길이가 0 이면 보내지 않음
		if (strlen(buf) == 0)
		{
			EnableWindow(hSendButton, TRUE); // 보내기 버튼 활성화
			SetEvent(hReadEvent);
			continue;
		}
		//strcpy(fileName, OFN.lpstrFileTitle);
		memcpy(fileName, buf, sizeof(fileName));

		retval = send(sock, fileName, sizeof(fileName), 0);
		//EnableWindow(hSendButton, TRUE); // 보내기 버튼 활성화
		//SetEvent(hReadEvent);
		////////////////////////////////////////////


		//데이터 받기
		//파일이름 저장
		//retval = recvn(sock, fileName, sizeof(fileName), 0);
		buf[retval] = '\0';
		//-------------파일 데이터 크기를 저장함 (고정으로 넘어온 사이즈!)
		retval = recvn(sock, (char *)&fileSize, sizeof(fileSize), 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			return 1;
		}

		fp = fopen(fileName, "wb+");
		ZeroMemory(buf, BUFSIZE);
		
		// 클라이언트와 데이터 통신
		while (retval != 0)
		{
			// 데이터 받기(가변 길이)
			//system("cls");
			retval = recvn(sock, buf, BUFSIZE, 0);
			fwrite(buf, 1, retval, fp);

			TotalSend += retval;
			//DisplayText("클라이언트[%s] : 현재까지 다운 : %d (%%) \n", inet_ntoa(clientaddr.sin_addr), (int)((TotalDown / fileSize) * 100));
			SendMessage(hEditProgress, PBM_SETPOS, (int)((TotalSend / fileSize) * 100), 0);
		}
		fclose(fp);
		DisPlayText("받은 데이터의 크기 : %d\n", fileSize);
		//EnableWindow(hSendButton, TRUE); // 보내기 버튼 활성화
		SetEvent(hReadEvent); // 읽기 완료 알리기
	return 1;
	}
}
