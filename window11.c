#include <windows.h>
#include <math.h>
#define MAN_TIMER 16                         //�˵��ƶ�Ƶ��,ms
#define HUNTER_TIMER 29                      //������ƶ�Ƶ��
#define MOUTH_TIMER 40                        //����ƶ�Ƶ�� 
#define MAN_STEPTIMES 5                         //һ��ǽ��N������ 
#define HUNTER_STEPTIMES 5                         //һ��ǽ��N������  
#define WALL_LENGTH 20                       //���鳤�� 
#define WALL_COLOR RGB(30, 54, 225)          //ǽ����ɫ 
#define MAN_COLOR RGB(255, 201, 14)          //�˵���ɫ 
#define BEAN_COLOR RGB(0, 221, 0)            //������ɫ 
#define HUNTER_COLOR RGB(235, 58, 129)       //������ɫ 
#define COLOR_WHITE RGB(255, 255, 255)       //��ɫ 
#define BACKGROUND_COLOR RGB(0, 0, 0)        //������ɫ 
#define WINDOW_WIDTH  40*WALL_LENGTH         //���ڿ�� 
#define WINDOW_HEIGHT 32*WALL_LENGTH+20      //���ڸ߶�
#define MAN_RUN 1
#define HUNTER_RUN 2 
#define MOUTH 3
#define PI 3.1415926535898
#define CM_GAMESTART WM_USER+1
#define CM_GAMEOVER WM_USER+2
#define CM_CREATE WM_USER+3
#define CM_RESTART WM_USER+4
long dir[5][2] = { { 0, 1 },{ -1, 0 },{ 0, -1 },{ 1, 0 }, {0, 0} };
int maze[200][200] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0 },
{ 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
{ 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
{ 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
{ 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
{ 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 2, 2, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 2, 2, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 2, 2, 2, 2, 2, 2, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 }, //!
{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
{ 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
{ 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
{ 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0 },
{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
{ 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0 },
{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
{ 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);        //��������������Ϣ�ĺ���
LRESULT CALLBACK StartProc(hwnd, message, wParam, lParam);
LRESULT CALLBACK GamingProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK GameoverProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
static HBRUSH hbWallColor;
	static HBRUSH hbManColor;
	static HBRUSH hbBkColor;
	static HBRUSH hbBeanColor;
	static HBRUSH hbHunterColor;
struct point
{
	int x, y, k, step;
};
void Hunter_Run(HWND hwnd, HBRUSH hbBkColor, HBRUSH hbHunterColor, HBRUSH hbBeanColor, struct point p, struct point *a, struct point *Nowp);
struct point Man_Run(HWND hwnd, HBRUSH hbBkColor, HBRUSH hbManColor, struct point *p, int d, int *bean, double Mouth_Angle);
TCHAR szButtonClass[] = TEXT("ButtonClass") ;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("MyWindow");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;        //����һ�����������

							  //����Ϊ���������wndclass������                                                 
	wndclass.style = CS_HREDRAW | CS_VREDRAW;                         //������ʽ
	wndclass.lpszClassName = szAppName;                               //��������
	wndclass.lpszMenuName = NULL;                                     //���ڲ˵�:��
	wndclass.hbrBackground = CreateSolidBrush(COLOR_BACKGROUND);//���ڱ�����ɫ
	wndclass.lpfnWndProc = WndProc;                                   //���ڴ�����
	wndclass.cbWndExtra = 0;                                          //����ʵ����չ:��
	wndclass.cbClsExtra = 0;                                          //��������չ:��
	wndclass.hInstance = hInstance;                                   //����ʵ�����
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);               //������С��ͼ��:ʹ��ȱʡͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);                 //���ڲ��ü�ͷ���

	if (!RegisterClass(&wndclass)) {    //ע�ᴰ����, ���ע��ʧ�ܵ���������ʾ
		MessageBox(NULL, TEXT("����ע��ʧ��!"), TEXT("����"), MB_OK | MB_ICONERROR);
		return 0;
	}
    RegisterClass( &wndclass ) ;
	hwnd = CreateWindow(                   //��������
		szAppName,                 //��������
		TEXT("�Զ���"),           //���ڱ���
		WS_OVERLAPPEDWINDOW,// || !WS_SIZEBOX,       //���ڵķ��
		10,//CW_USEDEFAULT,             //���ڳ�ʼ��ʾλ��x:ʹ��ȱʡֵ
		10,//CW_USEDEFAULT,             //���ڳ�ʼ��ʾλ��y:ʹ��ȱʡֵ
		WINDOW_WIDTH,//CW_USEDEFAULT,             //���ڵĿ��:ʹ��ȱʡֵ
		WINDOW_HEIGHT,//CW_USEDEFAULT,             //���ڵĸ߶�:ʹ��ȱʡֵ
		NULL,                      //������:��
		NULL,                      //�Ӳ˵�:��
		hInstance,                 //�ô���Ӧ�ó����ʵ����� 
		NULL                       //
	);

	ShowWindow(hwnd, iCmdShow);        //��ʾ����
	UpdateWindow(hwnd);                //���´���

	while (GetMessage(&msg, NULL, 0, 0))        //����Ϣ�����л�ȡ��Ϣ
	{
		TranslateMessage(&msg);                 //���������Ϣת��Ϊ�ַ���Ϣ
		DispatchMessage(&msg);                  //�ַ����ص�����(���̺���)
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static int Status = 0;       //�ֶ�������Ϣ�ı�״̬ 
	switch(message) {
		case CM_GAMESTART:
			Status = 1;
			KillTimer(hwnd, 1);
			PostMessage( hwnd, CM_CREATE, 0, 0 );
			InvalidateRect( hwnd, NULL, TRUE );
			return 0;
		case CM_GAMEOVER:
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 3);
			if( IDOK != MessageBox( hwnd, TEXT("�Ƿ���������һ��"), TEXT("������"), MB_OKCANCEL | MB_ICONQUESTION ) ) {
			Status = 2; 
			PostMessage( hwnd, CM_CREATE, 0, 0 );
			InvalidateRect( hwnd, NULL, TRUE );   
			}
			else{ 
				PostMessage( hwnd, CM_CREATE, 0, 0 ); 
				InvalidateRect(NULL, NULL, TRUE);
				//PostMessage( hwnd, WM_PAINT, 0, 0 ); 
			} 
			return 0; 
		case WM_CLOSE:
			KillTimer(hwnd, 1);
			KillTimer(hwnd, 2);
			KillTimer(hwnd, 3); 
			PostQuitMessage(0);
			return 0;
	}
	switch (Status) {
		case 0:
			return(
				StartProc(hwnd, message, wParam, lParam) );
		case 1:
			return(
				GamingProc(hwnd, message, wParam, lParam) );
		case 2:
			return(GameoverProc(hwnd, message, wParam, lParam)); 
	}
}
LRESULT CALLBACK GameoverProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static HWND QuitButtonHwnd; 
	switch(message) {
			case CM_CREATE:
			QuitButtonHwnd = CreateWindow( TEXT("button"), TEXT("�˳�"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            450, 400,        //�ڸ����ڿͻ���(0, 0)λ�ô���һ���Ӵ���
            100, 50,    //�Ӵ��ڵĴ�СΪ0x0
            hwnd,        //�����ھ��
            (HMENU)2,    //�Ӵ���ID
            (HINSTANCE) GetWindowLong(hwnd, GWLP_HINSTANCE ),
            NULL ) ;
            return 0; 
        case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case 2:
					//MessageBox( hwnd, TEXT("��Ϸ��ʼ!"), TEXT("��Ϸ��ʼ"), MB_OK ) ;
					SendMessage( QuitButtonHwnd, WM_CLOSE, 0, 0 );
					DestroyWindow(hwnd);
					//PostMessage( hwnd, WM_CLOSE, 0, 0 );
					return 0;
					
			}
	} 
	return DefWindowProc(hwnd, message, wParam, lParam);
}
void Paint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc;
    HDC mdc;
    HBITMAP hbmp; // λͼ���ƶ�����
 
    hdc = BeginPaint(hwnd, &ps); 
 
    // ��������DC (��ǰ����DC�ļ���DC)
    mdc = CreateCompatibleDC(hdc);
 
    // ���� "E:\\bg.bmp" ��λͼ���ƶ��� hbmp ��
    hbmp = (HBITMAP)LoadImage(
        NULL,           // ģ��ʵ�����(Ҫ���ص�ͼƬ������DLL��ʱ)
        "1.bmp",   // λͼ·��
        IMAGE_BITMAP,   // λͼ����
        301,   // ָ��ͼƬ��
        284,  // ָ��ͼƬ��
        LR_LOADFROMFILE // ��·��������ͼƬ
        );
 
    // ����DCѡ��λͼ���ƶ��󣨿������Ϊ��ͼƬ�浽mdc�У�
    SelectObject(mdc, hbmp);
 
    // ������DC�е�λͼ���Ƶ�����DC��
    BitBlt(
        hdc,            // Ŀ��DC
        0,0,            // Ŀ��DC�� x,y ����
        301,   // Ҫճ����ͼƬ��
        284,  // Ҫճ����ͼƬ��
        mdc,            // ����DC
        0,0,            // ����DC�� x,y ����
        SRCCOPY         // ճ����ʽ
        );
 
    DeleteObject(hbmp);
    DeleteDC(mdc);
    EndPaint(hwnd, &ps);
}
LRESULT CALLBACK StartProc(hwnd, message, wParam, lParam) {
	static HWND StartButtonHwnd;
	HWND hbn; 
	HDC hdc;
	PAINTSTRUCT ps;
	static HBRUSH ButtonBkColor;
	static POINT pt;
	static int Mouth_Angle = 1;
	static int MouthAngle_Mark = 0;
	switch(message) {
		case WM_CREATE:
			StartButtonHwnd = CreateWindow( TEXT("BUTTON"), TEXT("��ʼ��Ϸ"),
            WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,//BS_PUSHBUTTON,
            17*WALL_LENGTH, 12*WALL_LENGTH,        //�ڸ����ڿͻ���(0, 0)λ�ô���һ���Ӵ���
            3.75*WALL_LENGTH, 1.75*WALL_LENGTH,    //�Ӵ��ڵĴ�СΪ0x0
            hwnd,        //�����ھ��
            (HMENU)1,    //�Ӵ���ID
            (HINSTANCE) GetWindowLong(hwnd, GWLP_HINSTANCE ),
            NULL ) ;
            ButtonBkColor = CreateSolidBrush(RGB(127,0,255));
              SetTimer(hwnd, 1, 60, NULL);
			  SetTimer(hwnd, 2, 40, NULL); 
			  hbManColor = CreateSolidBrush(MAN_COLOR);
		hbWallColor = CreateSolidBrush(WALL_COLOR);
		hbBkColor = CreateSolidBrush(BACKGROUND_COLOR);
		hbBeanColor = CreateSolidBrush(BEAN_COLOR);
		hbHunterColor = CreateSolidBrush(HUNTER_COLOR);
            return 0; 
        case WM_CTLCOLORBTN:          	 
//			if ((HWND)lParam == GetDlgItem(hDlg, IDOK))
//  			{
   			hbn = StartButtonHwnd;//(HWND)lParam;
   			HDC hdc = (HDC)wParam;
   			RECT rc;
   			TCHAR text[64];
   			GetWindowText(hbn, text, 63);
  			 GetClientRect(hbn, &rc);
   			SetTextColor(hdc, RGB(255, 255, 255));//���ð�ť���ı�����ɫ
   			SetBkMode(hdc, TRANSPARENT);
   			DrawText(hdc, text, lstrlen(text), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
   			return (INT_PTR)ButtonBkColor;//���ػ�ˢ���ð�ť�ı���ɫ
  			//} 
  		case WM_PAINT:
  			//Paint(hwnd);
  			hdc = BeginPaint(hwnd, &ps);
  			HFONT hFont = CreateFont(96,         // nHeight, ������������ַ��߶�
						0,           // nWidth,       ������ַ�ƽ�����
						200,          // nEscapement,  �ַ����������ˮƽ���ҵķ������ɽǶ�,��0.1��Ϊ��λ
						0,             // nOrientation, �ַ�����ߵĽǶȣ���0.1��Ϊ��λ
						FW_BOLD,        // nWeight,      �ַ���ɫ����ǳ��
						TRUE,            // bItalic,      б�����Ա�־(FALSE:�������壬TRUE:б��)
						FALSE,            // bUnderline,   �»������Ա�־(FALSE:���»��ߣ�TRUE:���»���)
						FALSE,             // cStrikeOut,   ɾ�������Ա�־(FALSE:��ɾ���ߣ�TRUE:��ɾ����)
						ANSI_CHARSET,       // nCharSet,        �ַ�����ʶ0:ANSI�ַ�����1:ϵͳȱʡ�ַ���
						OUT_DEFAULT_PRECIS,  // nOutPrecision,   �������
						CLIP_DEFAULT_PRECIS, // nClipPrecision,  ���о���
						DEFAULT_QUALITY,      // nQuality,        ���Ʒ��
						DEFAULT_PITCH|FF_SWISS, // nPitchAndFamily, �ַ����
						TEXT("Arial"));          // lpszFacename,    ����ϵͳTrueType��������
			HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(0x00, 0xFF, 0xFF));
			TextOut(hdc, 11.6*WALL_LENGTH, 6.6*WALL_LENGTH, TEXT("Monster"), 7);
			DeleteObject(hFont);
  			EndPaint(hwnd, &ps);
			return 0;
  		case WM_TIMER:
  			//MessageBox( hwnd, TEXT("��Ϸ��ʼ!"), TEXT("��Ϸ��ʼ"), MB_OK ) ;
  			switch(wParam){
  			case 1:
  			GetCursorPos(&pt);
  			ScreenToClient( hwnd, &pt ) ; 
  			if(pt.x > 17*WALL_LENGTH && pt.x < (17+3.75)*WALL_LENGTH && pt.y > 12*WALL_LENGTH && pt.y < (12+1.75)*WALL_LENGTH){
				ButtonBkColor = CreateSolidBrush(RGB(127,0,0)); 
				InvalidateRect( StartButtonHwnd, NULL, TRUE );
				return 0;
			}
			ButtonBkColor = CreateSolidBrush(RGB(127,0,255));
			InvalidateRect( StartButtonHwnd, NULL, TRUE );	
			return 0;     
			case 2:
				if(Mouth_Angle == 10 || Mouth_Angle == 0)
					MouthAngle_Mark = !MouthAngle_Mark;
				if(MouthAngle_Mark)
					Mouth_Angle++;
				else
					Mouth_Angle--;
				hdc = GetDC(hwnd);
				static int step = 0;
				int i;
				for(i = 0; i < 5; i++){
					SelectObject(hdc, hbBkColor);
					Ellipse(hdc, 800-i*100-step*5+5, 375,850-i*100-step*5+5, 425);
					SelectObject(hdc, hbBeanColor);
					Ellipse(hdc, 800-i*100-step*5,375 , 850-i*100-step*5, 425);
					if(step == 20)
						step = 0;
				}
				SelectObject(hdc, hbBkColor);
				Ellipse(hdc, 200, 350, 300, 450);
				SelectObject(hdc, hbManColor);
				Pie(hdc, 200, 350, 300, 450,
					200 + 100 / 2 * (1 + cos(PI / 2 * (double)Mouth_Angle/10)), 350 + 100 / 2 * (1 - sin(PI / 2 * (double)Mouth_Angle/10)),
					200 + 100 / 2 * (1 + cos(PI / 2 * (double)Mouth_Angle/10)), 350 + 100 / 2 * (1 + sin(PI / 2 * (double)Mouth_Angle/10)));
					
				
				if(step < 11){
					SelectObject(hdc, hbBkColor);
					Ellipse(hdc, 800-5*100-step*5+5, 375, 850-5*100-step*5+5, 425);
					SelectObject(hdc, hbBeanColor);
					Ellipse(hdc, 800-5*100-step*5, 375, 850-5*100-step*5, 425);
				}
				step++;
				ReleaseDC(hwnd, hdc);
			}
        case WM_COMMAND: 
			switch(LOWORD(wParam)) {
				case 1:
					switch(HIWORD(wParam)){
						case BN_CLICKED:
					MessageBox( hwnd, TEXT("��Ϸ��ʼ!"), TEXT("��Ϸ��ʼ"), MB_OK ) ;
					//DestroyWindow(StartButtonHwnd);
					PostMessage( hwnd, CM_GAMESTART, 0, 0 );
					SendMessage( StartButtonHwnd, WM_CLOSE, 0, 0 );
					return 0;       
					}
					
			}
	} 
	return DefWindowProc(hwnd, message, wParam, lParam);
}
LRESULT CALLBACK GamingProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;                //�豸�������
	PAINTSTRUCT ps;         //���ƽṹ
	RECT rect;               //���νṹ
	//��ɫ��ˢ 
	
	static int d = 1;
	static int bean = 294;
	static int Mouth_Angle = 1; 
	static int MouthAngle_Mark = 0;  //��¼��ı仯����,1��0�� 
	//static int ManStep, HunterStep;
	static struct point HunterNowp[3], ManNowp;
	//�˵Ľṹ�� 
	static struct point p = { 12, 23 },
		hunter[3] = { {14, 15, 1}, {15, 15, 1}, {13, 15, 1} };
	switch (message)        //����õ�����Ϣ
	{
	case CM_CREATE:          //���ڴ������ʱ��������Ϣ
		SetTimer(hwnd, MAN_RUN, MAN_TIMER, NULL);
		SetTimer(hwnd, HUNTER_RUN, HUNTER_TIMER, NULL);
		SetTimer(hwnd, MOUTH, MOUTH_TIMER, NULL);
		//����ˢ��ֵ
		d = 1;
		p.x = 12, p.y = 23, p.step = MAN_STEPTIMES;
		hunter[0].x = 14; hunter[0].y = 15; hunter[0].step = HUNTER_STEPTIMES;
		hunter[1].x = 15; hunter[1].y = 15; hunter[0].step = HUNTER_STEPTIMES;
		hunter[2].x = 13; hunter[2].y = 15; hunter[0].step = HUNTER_STEPTIMES; 
		return 0;
	case CM_RESTART:
		p.x = 12; p.y = 23;
		hunter[0].x = 14; hunter[1].y = 15;
		hunter[1].x = 15; hunter[1].y = 15;
		hunter[2].x = 13; hunter[2].y = 15;
		//hunter[3] = { {14, 15, 1}, {15, 15, 1}, {13, 15, 1} };
	case WM_PAINT:           //������������Чʱ��������Ϣ
		hdc = BeginPaint(hwnd, &ps);
		int i, j;
		SelectObject(hdc, hbBeanColor);
		for (i = 0; i < 31; i++) {
			for (j = 0; j < 28; j++)
				if (!maze[i][j]) {
					SetRect(&rect, j*WALL_LENGTH, i*WALL_LENGTH, j*WALL_LENGTH + WALL_LENGTH, i*WALL_LENGTH + WALL_LENGTH);
					FillRect(hdc, &rect, hbWallColor);
				}
				else if (maze[i][j] == 1) {
					Ellipse(hdc, j*WALL_LENGTH + WALL_LENGTH / 3, i*WALL_LENGTH + WALL_LENGTH / 3, j*WALL_LENGTH + WALL_LENGTH * 2 / 3, i*WALL_LENGTH + WALL_LENGTH * 2 / 3);
				}
		}
		EndPaint(hwnd, &ps);
		return 0;
	case WM_TIMER:
		//MessageBox( hwnd, TEXT("ʱ��������һ��!"), TEXT("��ʱ����Ϣ"), MB_OK );
		switch (wParam) {
		case MAN_RUN:
			ManNowp = Man_Run(hwnd, hbBkColor, hbManColor, &p, d, &bean, (double)Mouth_Angle/10);	
			for(i = 0; i < 3; i++)
				if( (ManNowp.x == HunterNowp[i].x) && (ManNowp.y == HunterNowp[i].y) )
					PostMessage( hwnd, CM_GAMEOVER, 0, 0 );	
			return 0;
		case HUNTER_RUN:
			Hunter_Run(hwnd, hbBkColor, hbHunterColor, hbBeanColor, p, hunter, HunterNowp);
			for(i = 0; i < 3; i++)
				if( (ManNowp.x == HunterNowp[i].x) && (ManNowp.y == HunterNowp[i].y) )
					PostMessage( hwnd, CM_GAMEOVER, 0, 0 );	
			return 0;
		case MOUTH:
			if(Mouth_Angle == 10 || Mouth_Angle == 0)
				MouthAngle_Mark = !MouthAngle_Mark;
			if(MouthAngle_Mark)
				Mouth_Angle++;
			else
				Mouth_Angle--;
		}
	case WM_KEYDOWN:    //������������Ϣ
		switch (wParam) {
		case VK_UP:        //��
			d = 0;
			break;
		case VK_DOWN:    //��
			d = 2;
			break;
		case VK_LEFT:    //��
			d = 1;
			break;
		case VK_RIGHT:    //��
			d = 3;
			break;
		default:
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:     //���������������µ���Ϣ
		MessageBox(hwnd, TEXT("�����������¡�"), TEXT("����"), MB_OK | MB_ICONINFORMATION);
		return 0;

	case WM_CLOSE:         //�������رհ�ťʱ����Ϣ
						   //if( IDOK == MessageBox( hwnd, TEXT("�رճ���!"), TEXT("����"), MB_OKCANCEL | MB_ICONQUESTION ) )
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);        //DefWindowProc���������Զ������Ϣ������û�д�������Ϣ
}
struct point Man_Run(HWND hwnd, HBRUSH hbBkColor, HBRUSH hbManColor, struct point *p, int d, int *bean, double Mouth_Angle) {
	static int Nowd = 4;         //�����ƶ����ߵķ��� 
	if (p->step == 0 && maze[p->y][p->x] == 1) {
		(*bean)--;
		maze[p->y][p->x] = 2;
	} 
	if(p->step == MAN_STEPTIMES)
		if (maze[p->y - dir[d][1]][p->x + dir[d][0]]) {
			Nowd = d;
			p->y -= dir[d][1];
			p->x += dir[d][0];
			p->step = 0;
		}
		else
			Nowd = 4;	
	else
		p->step++; 
	
	HDC hdc = GetDC(hwnd);
	HFONT hFont = CreateFont(40,         // nHeight, ������������ַ��߶�
						0,           // nWidth,       ������ַ�ƽ�����
						0,          // nEscapement,  �ַ����������ˮƽ���ҵķ������ɽǶ�,��0.1��Ϊ��λ
						0,             // nOrientation, �ַ�����ߵĽǶȣ���0.1��Ϊ��λ
						FW_BOLD,        // nWeight,      �ַ���ɫ����ǳ��
						FALSE,            // bItalic,      б�����Ա�־(FALSE:�������壬TRUE:б��)
						FALSE,            // bUnderline,   �»������Ա�־(FALSE:���»��ߣ�TRUE:���»���)
						FALSE,             // cStrikeOut,   ɾ�������Ա�־(FALSE:��ɾ���ߣ�TRUE:��ɾ����)
						ANSI_CHARSET,       // nCharSet,        �ַ�����ʶ0:ANSI�ַ�����1:ϵͳȱʡ�ַ���
						OUT_DEFAULT_PRECIS,  // nOutPrecision,   �������
						CLIP_DEFAULT_PRECIS, // nClipPrecision,  ���о���
						DEFAULT_QUALITY,      // nQuality,        ���Ʒ��
						DEFAULT_PITCH|FF_SWISS, // nPitchAndFamily, �ַ����
						TEXT("Arial"));          // lpszFacename,    ����ϵͳTrueType��������
			//HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(255, 0, 0));			
	char strbean[4];
	memset(strbean, ' ', 4);
	itoa(*bean, strbean, 10);
	RECT rect;
	SetRect(&rect, 1080, 200, 1200, 240);
	FillRect(hdc, &rect, hbBkColor);
	SelectObject(hdc, hFont);
	TextOut(hdc, 1080, 200, TEXT(strbean), lstrlen(strbean));
	/*SelectObject(hdc, hbBkColor);
	Ellipse(hdc, p.x*WALL_LENGTH, p.y*WALL_LENGTH, p.x*WALL_LENGTH+WALL_LENGTH, p.y*WALL_LENGTH+WALL_LENGTH );

	SelectObject(hdc, hbManColor);
	Ellipse(hdc, p.x*WALL_LENGTH, p.y*WALL_LENGTH, p.x*WALL_LENGTH+WALL_LENGTH, p.y*WALL_LENGTH+WALL_LENGTH );*/
	SelectObject(hdc, hbManColor);
	TextOut(hdc, 860, 200, TEXT("ʣ�ඹ�Ӹ���:"), lstrlen(TEXT("ʣ�ඹ�Ӹ���:")));
	DeleteObject(hFont);
	struct point Nowp;
	Nowp = *p;
	if(p->step){   //������һ������ͼ�� 
		Nowp.x = (p->x-dir[Nowd][0])*WALL_LENGTH + dir[Nowd][0]*(p->step-1)*WALL_LENGTH/MAN_STEPTIMES;
		Nowp.y = (p->y+dir[Nowd][1])*WALL_LENGTH - dir[Nowd][1]*(p->step-1)*WALL_LENGTH/MAN_STEPTIMES;
		SelectObject(hdc, hbBkColor);
		Ellipse(hdc, Nowp.x, Nowp.y, Nowp.x+WALL_LENGTH, Nowp.y+WALL_LENGTH);   
	}
	//����ͼ�� 
	Nowp.x = (p->x-dir[Nowd][0])*WALL_LENGTH + dir[Nowd][0]*p->step*WALL_LENGTH/MAN_STEPTIMES;
	Nowp.y = (p->y+dir[Nowd][1])*WALL_LENGTH - dir[Nowd][1]*p->step*WALL_LENGTH/MAN_STEPTIMES;
	SelectObject(hdc, hbManColor);
	if(Nowd == 3)    //�������߷������ͼ�� 
		Pie(hdc, Nowp.x, Nowp.y, Nowp.x + WALL_LENGTH, Nowp.y + WALL_LENGTH,
			Nowp.x + WALL_LENGTH / 2 * (1 + cos(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 - sin(PI / 2 * Mouth_Angle)),
			Nowp.x + WALL_LENGTH / 2 * (1 + cos(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 + sin(PI / 2 * Mouth_Angle)));
	else if(Nowd == 2)
		Pie(hdc, Nowp.x, Nowp.y, Nowp.x + WALL_LENGTH, Nowp.y + WALL_LENGTH,
			Nowp.x + WALL_LENGTH / 2 * (1 + sin(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 + cos(PI / 2 * Mouth_Angle)),
			Nowp.x + WALL_LENGTH / 2 * (1 - sin(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 + cos(PI / 2 * Mouth_Angle)));
	else if(Nowd == 1)
		Pie(hdc, Nowp.x, Nowp.y, Nowp.x + WALL_LENGTH, Nowp.y + WALL_LENGTH,
			Nowp.x + WALL_LENGTH / 2 * (1 - cos(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 + sin(PI / 2 * Mouth_Angle)),
			Nowp.x + WALL_LENGTH / 2 * (1 - cos(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 - sin(PI / 2 * Mouth_Angle)));
	else if(Nowd == 0)
		Pie(hdc, Nowp.x, Nowp.y, Nowp.x + WALL_LENGTH, Nowp.y + WALL_LENGTH,
			Nowp.x + WALL_LENGTH / 2 * (1 - cos(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 - sin(PI / 2 * Mouth_Angle)),
			Nowp.x + WALL_LENGTH / 2 * (1 + cos(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 - sin(PI / 2 * Mouth_Angle)));
	else{       //Nowd = 4,ײǽ,����d�жϷ��� 
		if(d == 3)
			Pie(hdc, Nowp.x, Nowp.y, Nowp.x + WALL_LENGTH, Nowp.y + WALL_LENGTH,
				Nowp.x + WALL_LENGTH / 2 * (1 + cos(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 - sin(PI / 2 * Mouth_Angle)),
				Nowp.x + WALL_LENGTH / 2 * (1 + cos(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 + sin(PI / 2 * Mouth_Angle)));
		else if(d == 2)
			Pie(hdc, Nowp.x, Nowp.y, Nowp.x + WALL_LENGTH, Nowp.y + WALL_LENGTH,
				Nowp.x + WALL_LENGTH / 2 * (1 + sin(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 + cos(PI / 2 * Mouth_Angle)),
				Nowp.x + WALL_LENGTH / 2 * (1 - sin(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 + cos(PI / 2 * Mouth_Angle)));
		else if(d == 1)
			Pie(hdc, Nowp.x, Nowp.y, Nowp.x + WALL_LENGTH, Nowp.y + WALL_LENGTH,
				Nowp.x + WALL_LENGTH / 2 * (1 - cos(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 + sin(PI / 2 * Mouth_Angle)),
				Nowp.x + WALL_LENGTH / 2 * (1 - cos(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 - sin(PI / 2 * Mouth_Angle)));
		else if(d == 0)
			Pie(hdc, Nowp.x, Nowp.y, Nowp.x + WALL_LENGTH, Nowp.y + WALL_LENGTH,
				Nowp.x + WALL_LENGTH / 2 * (1 - cos(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 - sin(PI / 2 * Mouth_Angle)),
				Nowp.x + WALL_LENGTH / 2 * (1 + cos(PI / 2 * Mouth_Angle)), Nowp.y + WALL_LENGTH / 2 * (1 - sin(PI / 2 * Mouth_Angle)));
	}
	//Ellipse(hdc, Nowp.x, Nowp.y, Nowp.x+WALL_LENGTH, Nowp.y+WALL_LENGTH);
	ReleaseDC(hwnd, hdc);
	return Nowp;
}
void Hunter_Run(HWND hwnd, HBRUSH hbBkColor, HBRUSH hbHunterColor, HBRUSH hbBeanColor, struct point p, struct point *reala, struct point *Nowp) {        //aΪ����ṹ�����飬pΪ��λ��  
	struct point queue[30000],
		a[3] = { *reala, reala[1], reala[2] };
	int i, j, mark[50][50];
	int h[3] = { 1, 1, 1 }; //��¼���������Ƿ��Ѿ��ƶ� PS��ɾ������
	for (i = 0; i < 3; i++)
		a[i].k = i;
	int head, tail;
	struct point cur, next;
	static int Nowd[3] = {4, 4, 4};
	if(reala->step == HUNTER_STEPTIMES) {
		for(i = 0; i < 3; i++) {
			int Oldx = reala[i].x-dir[Nowd[i]][0],
				Oldy = reala[i].y+dir[Nowd[i]][1];
			//��������߰Ѷ��Ӹ��ǵ���
			if(maze[Oldy][Oldx] == 1) {
				HDC hdc = GetDC(hwnd);
				SelectObject(hdc, hbBeanColor);
				Ellipse(hdc, Oldx*WALL_LENGTH + WALL_LENGTH / 3, Oldy*WALL_LENGTH + WALL_LENGTH / 3, Oldx*WALL_LENGTH + WALL_LENGTH * 2 / 3, Oldy*WALL_LENGTH + WALL_LENGTH * 2 / 3);
				ReleaseDC(hwnd, hdc);
			} 
		} 
	memset(mark, -1, sizeof(mark));   //����
	head = tail = 0;
	queue[head] = p;
	tail++;
	while (head < tail) {
		cur = queue[head++];
		for (i = 0; i < 4; i++) {
			next.x = cur.x + dir[i][0];
			next.y = cur.y - dir[i][1];
			if (maze[next.y][next.x] && mark[next.y][next.x] &&
				(next.x != p.x || next.y != p.y + 1 || next.y != p.y - 1) &&
				(next.x != p.x + 1 || next.y != p.y)) {
				for (j = 0; j < 3; j++) {
					if (reala[j].x == next.x && reala[j].y == next.y && h[j]) {
						h[a[j].k] = 0;                  //k�Ź����Ѿ��ҵ���λ�� 
						a[j] = cur;                     //��Ҫ�ߵ���λ�ø�ֵ 
						break;
					}
				}
				if (j < 3) break;
				else {
					mark[cur.y][cur.x] = 0;//����߹�
					queue[tail++] = next;
				}
			}
		}
		if (i < 4) break;
	}

	memset(mark, -1, sizeof(mark));   //�·���
	head = tail = 0;
	queue[head] = p;
	tail++;
	while (head < tail) {
		cur = queue[head++];
		for (i = 0; i < 4; i++) {
			next.x = cur.x + dir[i][0];
			next.y = cur.y - dir[i][1];
			if (maze[next.y][next.x] && mark[next.y][next.x] &&
				(next.y != p.y || next.x != p.x + 1 || next.x != p.x - 1) &&
				(next.x != p.x || next.y != p.y - 1)) {
				for (j = 0; j < 3; j++) {
					if (reala[j].x == next.x && reala[j].y == next.y && h[j]) {
						h[a[j].k] = 0;
						a[j] = cur;
						break;
					}
				}
				if (j < 3) break;
				else {
					mark[cur.y][cur.x] = 0;//����߹�
					queue[tail++] = next;
				}
			}
		}
		if (i < 4) break;
	}

	memset(mark, -1, sizeof(mark));   //�ҷ���
	head = tail = 0;
	queue[head] = p;
	tail++;
	while (head < tail) {
		cur = queue[head++];
		for (i = 0; i < 4; i++) {
			next.x = cur.x + dir[i][0];
			next.y = cur.y - dir[i][1];
			if (maze[next.y][next.x] && mark[next.y][next.x] &&
				(next.x != p.x || next.y != p.y + 1 || next.y != p.y - 1) &&
				(next.y != p.y || next.x != p.x - 1)) {
				for (j = 0; j < 3; j++) {
					if (reala[j].x == next.x && reala[j].y == next.y && h[j]) {
						h[a[j].k] = 0;
						a[j] = cur;
						break;
					}
				}
				if (j < 3) break;
				else {
					mark[cur.y][cur.x] = 0;//����߹�
					queue[tail++] = next;
				}
			}
		}
		if (i < 4) break;
	}

	memset(mark, -1, sizeof(mark));   //�Ϸ���
	head = tail = 0;
	queue[head] = p;
	tail++;
	while (head < tail) {
		cur = queue[head++];
		for (i = 0; i < 4; i++) {
			next.x = cur.x + dir[i][0];
			next.y = cur.y - dir[i][1];
			if (maze[next.y][next.x] && mark[next.y][next.x] &&
				(next.y != p.y || next.x != p.x + 1 || next.x != p.x - 1) &&
				(next.x != p.x || next.y != p.y - 1)) {
				for (j = 0; j < 3; j++) {
					if (reala[j].x == next.x && reala[j].y == next.y && h[j]) {
						h[a[j].k] = 0;
						a[j] = cur;
						break;
					}
				}
				if (j < 3) break;
				else {
					mark[cur.y][cur.x] = 0;//����߹�
					queue[tail++] = next;
				}
			}
		}
		if (i < 4) break;
	} 
	for(i = 0; i < 3; i++) {
		if(a[i].y < reala[i].y)
			Nowd[i] = 0;
		else if(a[i].x < reala[i].x)
			Nowd[i] = 1;
		else if(a[i].y > reala[i].y)
			Nowd[i] = 2;
		else if(a[i].x > reala[i].x)
			Nowd[i] = 3;
		else
			Nowd[i] = 4;
	}
	for(i = 0; i < 3; i++)
		reala[i] = a[i];
	reala->step = 0;

}
else
	reala->step++;

	HDC hdc = GetDC(hwnd);
	//struct point Nowp[3];
	for(i = 0; i < 2;i++)
		Nowp[i] = reala[i];
	if(reala->step){   //������һ������ͼ��
		for(i = 0; i < 3; i++){ 
			Nowp[i].x = (reala[i].x-dir[Nowd[i]][0])*WALL_LENGTH + dir[Nowd[i]][0]*(reala->step-1)*WALL_LENGTH/MAN_STEPTIMES;
			Nowp[i].y = (reala[i].y+dir[Nowd[i]][1])*WALL_LENGTH - dir[Nowd[i]][1]*(reala->step-1)*WALL_LENGTH/MAN_STEPTIMES;
			SelectObject(hdc, hbBkColor);
			Ellipse(hdc, Nowp[i].x, Nowp[i].y, Nowp[i].x+WALL_LENGTH, Nowp[i].y+WALL_LENGTH); 
		}  
	}
	//����ͼ�� 
	for(i = 0 ; i < 3; i++){
		Nowp[i].x = (reala[i].x-dir[Nowd[i]][0])*WALL_LENGTH + dir[Nowd[i]][0]*(reala->step)*WALL_LENGTH/MAN_STEPTIMES;
		Nowp[i].y = (reala[i].y+dir[Nowd[i]][1])*WALL_LENGTH - dir[Nowd[i]][1]*(reala->step)*WALL_LENGTH/MAN_STEPTIMES;
		SelectObject(hdc, hbHunterColor);
		Ellipse(hdc, Nowp[i].x, Nowp[i].y, Nowp[i].x+WALL_LENGTH, Nowp[i].y+WALL_LENGTH); 
	} 
	ReleaseDC(hwnd, hdc);
	/*
	a[0].x *= WALL_LENGTH;
	a[0].y *= WALL_LENGTH;
	a[2].x *= WALL_LENGTH;
	a[2].y *= WALL_LENGTH;
	a[1].x *= WALL_LENGTH;
	a[1].y *= WALL_LENGTH;
	int n[] = { reala->x - a[0].x, reala[1].x - a[1].x, reala[2].x - a[2].x };
	int m[] = { reala->x - a[0].x, reala[1].y - a[1].x, reala[2].y - a[2].x };
	for (i = 0; i < 3) {
		n[i] = n * 20 / t;
		m[i] = m * 20 / t;
	}
	for (i = 0; i < t; i++) {
		p.x += dir[d][0] * a * (WALL_LENGTH / t / 2);
		p.y -= dir[d][1] * a * (WALL_LENGTH / t / 2);
		SelectObject(hdc, hbManColor);
		Pie(hdc, p.x, p.y, p.x + WALL_LENGTH, p.y + WALL_LENGTH,
			p.x + WALL_LENGTH / 2 * (1 + cos(PI / 2 * (i / t))), p.y + WALL_LENGTH / 2 * (1 - sin(PI / 2 * (i / t))),
			p.x + WALL_LENGTH / 2 * (1 + cos(PI / 2 * (i / t))), p.y + WALL_LENGTH / 2 * (1 + sin(PI / 2 * (i / t))));
		Sleep(33);
		SelectObject(hdc, hbBkColor);
		Ellipse(hdc, p.x, p.y, p.x + WALL_LENGTH, p.y + WALL_LENGTH);
	}  */
	return;
}
