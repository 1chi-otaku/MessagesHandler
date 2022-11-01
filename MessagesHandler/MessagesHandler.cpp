// Файл WINDOWS.H содержит определения, макросы, и структуры 
// которые используются при написании приложений под Windows. 
#include <windows.h>
#include <tchar.h>

//прототип оконной процедуры
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Êàðêàñíîå ïðèëîæåíèå"); /* Èìÿ êëàññà îêíà */

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;

	/* 1. Определение класса окна  */

	wcl.cbSize = sizeof (wcl);	// ðàçìåð ñòðóêòóðû WNDCLASSEX 
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// îêíî ñìîæåò ïîëó÷àòü ñîîáùåíèÿ î äâîéíîì ùåë÷êå (DBLCLK)
	wcl.lpfnWndProc = WindowProc;	// àäðåñ îêîííîé ïðîöåäóðû
	wcl.cbClsExtra = 0;		// èñïîëüçóåòñÿ Windows 
	wcl.cbWndExtra  = 0; 	// èñïîëüçóåòñÿ Windows 
	wcl.hInstance = hInst;	// äåñêðèïòîð äàííîãî ïðèëîæåíèÿ
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// çàãðóçêà ñòàíäàðòíîé èêîíêè
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);		// çàãðóçêà ñòàíäàðòíîãî êóðñîðà
	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);	//çàïîëíåíèå îêíà áåëûì öâåòîì			
	wcl.lpszMenuName = NULL;	// ïðèëîæåíèå íå ñîäåðæèò ìåíþ
	wcl.lpszClassName = szClassWindow;	// èìÿ êëàññà îêíà
	wcl.hIconSm = NULL;	// îòñóòñòâèå ìàëåíüêîé èêîíêè äëÿ ñâÿçè ñ êëàññîì îêíà


	/*  2. Регистрация класса окна  */

	if (!RegisterClassEx(&wcl))
		return 0;	// ïðè íåóäà÷íîé ðåãèñòðàöèè - âûõîä

	/*  3. Ñîçäàíèå îêíà  */

	// ñîçäàåòñÿ îêíî è  ïåðåìåííîé hWnd ïðèñâàèâàåòñÿ äåñêðèïòîð îêíà
	hWnd = CreateWindowEx(
		0,		// ðàñøèðåííûé ñòèëü îêíà
		szClassWindow,	// èìÿ êëàññà îêíà
		TEXT("Êàðêàñ  Windows ïðèëîæåíèÿ"),	// çàãîëîâîê îêíà
		/* Çàãîëîâîê, ðàìêà, ïîçâîëÿþùàÿ ìåíÿòü ðàçìåðû, ñèñòåìíîå ìåíþ,
			êíîïêè ðàçâ¸ðòûâàíèÿ è ñâ¸ðòûâàíèÿ îêíà  */
		WS_OVERLAPPEDWINDOW,	// ñòèëü îêíà
		CW_USEDEFAULT,	// õ-êîîðäèíàòà ëåâîãî âåðõíåãî óãëà îêíà
		CW_USEDEFAULT,	// y-êîîðäèíàòà ëåâîãî âåðõíåãî óãëà îêíà
		CW_USEDEFAULT,	// øèðèíà îêíà
		CW_USEDEFAULT,	// âûñîòà îêíà
		NULL,			// äåñêðèïòîð ðîäèòåëüñêîãî îêíà
		NULL,			// äåñêðèïòîð ìåíþ îêíà
		hInst,		// èäåíòèôèêàòîð ïðèëîæåíèÿ, ñîçäàâøåãî îêíî
		NULL);		// óêàçàòåëü íà îáëàñòü äàííûõ ïðèëîæåíèÿ


	/* 4. Отображение окна */

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);	// ïåðåðèñîâêà îêíà


	/* 5.Запуск цикла обработки сообщений  */

	// ïîëó÷åíèå î÷åðåäíîãî ñîîáùåíèÿ èç î÷åðåäè ñîîáùåíèé
	while (GetMessage(&Msg, NULL, 0, 0)) 
	{
		TranslateMessage(&Msg);	// òðàíñëÿöèÿ ñîîáùåíèÿ
		DispatchMessage(&Msg);	// äèñïåò÷åðèçàöèÿ ñîîáùåíèé
	}
	return Msg.wParam;
}


// Оконная процедура âûçûâàåòñÿ îïåðàöèîííîé ñèñòåìîé è ïîëó÷àåò â êà÷åñòâå 
// ïàðàìåòðîâ ñîîáùåíèÿ èç î÷åðåäè ñîîáùåíèé äàííîãî ïðèëîæåíèÿ	

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[50];
	TCHAR header[50];

	switch (uMessage) {
	case WM_LBUTTONDOWN:
	{
		bool PlayAgain = true;

		while (PlayAgain == true)
		{
			unsigned int result = 0;
			int random = 0;
			int tries = 0;
			bool isWon = false;
			
			do {
				tries++;
				random = rand() % (1 - 101) + 1;
				wsprintf(str, TEXT("Is it %d?"), random); // òåêóùèå êîîðäèíàòû êóðñîðà ìûøè
				wsprintf(header, TEXT("Try # - %d"), tries); // òåêóùèå êîîðäèíàòû êóðñîðà ìûøè
				result = MessageBox(0, str, header, MB_OKCANCEL | MB_ICONQUESTION);
				if (tries >= 10) {
					MessageBox(0, "You won..", "You're smarter than computer", MB_OKCANCEL | MB_ICONQUESTION);
					result = IDOK;
					isWon = true;
				}

			} while (result != IDOK);

			if (isWon != true) {
				wsprintf(str, TEXT("I won! Tries = %d"), tries); // òåêóùèå êîîðäèíàòû êóðñîðà ìûøè
				MessageBox(0, str, "The computer is better than you", MB_OK | MB_ICONQUESTION);
			}
			result = MessageBox(0, "Wanna play again?", "Game over", MB_OKCANCEL | MB_ICONQUESTION);
			if (result != IDOK)
				PlayAgain = false;

		}
		
		

		break;
	}
	case WM_MOUSEMOVE:
	{
		wsprintf(str, TEXT("X=%d  Y=%d"), LOWORD(lParam), HIWORD(lParam)); // òåêóùèå êîîðäèíàòû êóðñîðà ìûøè
		SetWindowText(hWnd, str);	// ñòðîêà âûâîäèòñÿ â çàãîëîâîê îêíà
		break;
	case WM_CHAR:
		wsprintf(str, TEXT("Íàæàòà êëàâèøà %c"), (TCHAR)wParam);	// ASCII-êîä íàæàòîé êëàâèøè
		MessageBox(0, str, TEXT("WM_CHAR"), MB_OK | MB_ICONINFORMATION);
		break;
	case WM_DESTROY: // ñîîáùåíèå î çàâåðøåíèè ïðîãðàììû
		PostQuitMessage(0);	// ïîñûëêà ñîîáùåíèÿ WM_QUIT
		break;
	default:
		// âñå ñîîáùåíèÿ, êîòîðûå íå îáðàáàòûâàþòñÿ â äàííîé îêîííîé 
		// ôóíêöèè íàïðàâëÿþòñÿ îáðàòíî Windows íà îáðàáîòêó ïî óìîë÷àíèþ
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	}
	return 0;
}

