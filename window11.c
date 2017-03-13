#include <windows.h>
#include <math.h>
#define MAN_TIMER 16                         //人的移动频率,ms
#define HUNTER_TIMER 29                      //幽灵的移动频率
#define MOUTH_TIMER 40                        //嘴的移动频率 
#define MAN_STEPTIMES 5                         //一个墙分N步走完 
#define HUNTER_STEPTIMES 5                         //一个墙分N步走完  
#define WALL_LENGTH 20                       //方块长度 
#define WALL_COLOR RGB(30, 54, 225)          //墙的颜色 
#define MAN_COLOR RGB(255, 201, 14)          //人的颜色 
#define BEAN_COLOR RGB(0, 221, 0)            //豆子颜色 
#define HUNTER_COLOR RGB(235, 58, 129)       //幽灵颜色 
#define COLOR_WHITE RGB(255, 255, 255)       //白色 
#define BACKGROUND_COLOR RGB(0, 0, 0)        //背景颜色 
#define WINDOW_WIDTH  40*WALL_LENGTH         //窗口宽度 
#define WINDOW_HEIGHT 32*WALL_LENGTH+20      //窗口高度
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
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);        //声明用来处理消息的函数
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
	WNDCLASS wndclass;        //声明一个窗口类对象

							  //以下为窗口类对象wndclass的属性                                                 
	wndclass.style = CS_HREDRAW | CS_VREDRAW;                         //窗口样式
	wndclass.lpszClassName = szAppName;                               //窗口类名
	wndclass.lpszMenuName = NULL;                                     //窗口菜单:无
	wndclass.hbrBackground = CreateSolidBrush(COLOR_BACKGROUND);//窗口背景颜色
	wndclass.lpfnWndProc = WndProc;                                   //窗口处理函数
	wndclass.cbWndExtra = 0;                                          //窗口实例扩展:无
	wndclass.cbClsExtra = 0;                                          //窗口类扩展:无
	wndclass.hInstance = hInstance;                                   //窗口实例句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);               //窗口最小化图标:使用缺省图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);                 //窗口采用箭头光标

	if (!RegisterClass(&wndclass)) {    //注册窗口类, 如果注册失败弹出错误提示
		MessageBox(NULL, TEXT("窗口注册失败!"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return 0;
	}
    RegisterClass( &wndclass ) ;
	hwnd = CreateWindow(                   //创建窗口
		szAppName,                 //窗口类名
		TEXT("吃豆人"),           //窗口标题
		WS_OVERLAPPEDWINDOW,// || !WS_SIZEBOX,       //窗口的风格
		10,//CW_USEDEFAULT,             //窗口初始显示位置x:使用缺省值
		10,//CW_USEDEFAULT,             //窗口初始显示位置y:使用缺省值
		WINDOW_WIDTH,//CW_USEDEFAULT,             //窗口的宽度:使用缺省值
		WINDOW_HEIGHT,//CW_USEDEFAULT,             //窗口的高度:使用缺省值
		NULL,                      //父窗口:无
		NULL,                      //子菜单:无
		hInstance,                 //该窗口应用程序的实例句柄 
		NULL                       //
	);

	ShowWindow(hwnd, iCmdShow);        //显示窗口
	UpdateWindow(hwnd);                //更新窗口

	while (GetMessage(&msg, NULL, 0, 0))        //从消息队列中获取消息
	{
		TranslateMessage(&msg);                 //将虚拟键消息转换为字符消息
		DispatchMessage(&msg);                  //分发到回调函数(过程函数)
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static int Status = 0;       //手动产生消息改变状态 
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
			if( IDOK != MessageBox( hwnd, TEXT("是否重新再来一次"), TEXT("你死了"), MB_OKCANCEL | MB_ICONQUESTION ) ) {
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
			QuitButtonHwnd = CreateWindow( TEXT("button"), TEXT("退出"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            450, 400,        //在父窗口客户区(0, 0)位置创建一个子窗口
            100, 50,    //子窗口的大小为0x0
            hwnd,        //父窗口句柄
            (HMENU)2,    //子窗口ID
            (HINSTANCE) GetWindowLong(hwnd, GWLP_HINSTANCE ),
            NULL ) ;
            return 0; 
        case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case 2:
					//MessageBox( hwnd, TEXT("游戏开始!"), TEXT("游戏开始"), MB_OK ) ;
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
    HBITMAP hbmp; // 位图绘制对象句柄
 
    hdc = BeginPaint(hwnd, &ps); 
 
    // 创建缓存DC (当前窗口DC的兼容DC)
    mdc = CreateCompatibleDC(hdc);
 
    // 加载 "E:\\bg.bmp" 到位图绘制对象 hbmp 中
    hbmp = (HBITMAP)LoadImage(
        NULL,           // 模块实例句柄(要加载的图片在其他DLL中时)
        "1.bmp",   // 位图路径
        IMAGE_BITMAP,   // 位图类型
        301,   // 指定图片宽
        284,  // 指定图片高
        LR_LOADFROMFILE // 从路径处加载图片
        );
 
    // 缓存DC选择位图绘制对象（可以理解为将图片存到mdc中）
    SelectObject(mdc, hbmp);
 
    // 将缓存DC中的位图复制到窗口DC上
    BitBlt(
        hdc,            // 目的DC
        0,0,            // 目的DC的 x,y 坐标
        301,   // 要粘贴的图片宽
        284,  // 要粘贴的图片高
        mdc,            // 缓存DC
        0,0,            // 缓存DC的 x,y 坐标
        SRCCOPY         // 粘贴方式
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
			StartButtonHwnd = CreateWindow( TEXT("BUTTON"), TEXT("开始游戏"),
            WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,//BS_PUSHBUTTON,
            17*WALL_LENGTH, 12*WALL_LENGTH,        //在父窗口客户区(0, 0)位置创建一个子窗口
            3.75*WALL_LENGTH, 1.75*WALL_LENGTH,    //子窗口的大小为0x0
            hwnd,        //父窗口句柄
            (HMENU)1,    //子窗口ID
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
   			SetTextColor(hdc, RGB(255, 255, 255));//设置按钮上文本的颜色
   			SetBkMode(hdc, TRANSPARENT);
   			DrawText(hdc, text, lstrlen(text), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
   			return (INT_PTR)ButtonBkColor;//返回画刷设置按钮的背景色
  			//} 
  		case WM_PAINT:
  			//Paint(hwnd);
  			hdc = BeginPaint(hwnd, &ps);
  			HFONT hFont = CreateFont(96,         // nHeight, 所创建字体的字符高度
						0,           // nWidth,       字体的字符平均宽度
						200,          // nEscapement,  字符输出方向与水平向右的方向所成角度,以0.1度为单位
						0,             // nOrientation, 字符与基线的角度，以0.1度为单位
						FW_BOLD,        // nWeight,      字符颜色的深浅度
						TRUE,            // bItalic,      斜体属性标志(FALSE:正常字体，TRUE:斜体)
						FALSE,            // bUnderline,   下划线属性标志(FALSE:无下划线，TRUE:有下划线)
						FALSE,             // cStrikeOut,   删除线属性标志(FALSE:无删除线，TRUE:有删除线)
						ANSI_CHARSET,       // nCharSet,        字符集标识0:ANSI字符集，1:系统缺省字符集
						OUT_DEFAULT_PRECIS,  // nOutPrecision,   输出精度
						CLIP_DEFAULT_PRECIS, // nClipPrecision,  剪切精度
						DEFAULT_QUALITY,      // nQuality,        输出品质
						DEFAULT_PITCH|FF_SWISS, // nPitchAndFamily, 字符间距
						TEXT("Arial"));          // lpszFacename,    现有系统TrueType字体名称
			HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(0x00, 0xFF, 0xFF));
			TextOut(hdc, 11.6*WALL_LENGTH, 6.6*WALL_LENGTH, TEXT("Monster"), 7);
			DeleteObject(hFont);
  			EndPaint(hwnd, &ps);
			return 0;
  		case WM_TIMER:
  			//MessageBox( hwnd, TEXT("游戏开始!"), TEXT("游戏开始"), MB_OK ) ;
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
					MessageBox( hwnd, TEXT("游戏开始!"), TEXT("游戏开始"), MB_OK ) ;
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
	HDC hdc;                //设备环境句柄
	PAINTSTRUCT ps;         //绘制结构
	RECT rect;               //矩形结构
	//颜色笔刷 
	
	static int d = 1;
	static int bean = 294;
	static int Mouth_Angle = 1; 
	static int MouthAngle_Mark = 0;  //记录嘴的变化方向,1张0合 
	//static int ManStep, HunterStep;
	static struct point HunterNowp[3], ManNowp;
	//人的结构体 
	static struct point p = { 12, 23 },
		hunter[3] = { {14, 15, 1}, {15, 15, 1}, {13, 15, 1} };
	switch (message)        //处理得到的消息
	{
	case CM_CREATE:          //窗口创建完成时发来的消息
		SetTimer(hwnd, MAN_RUN, MAN_TIMER, NULL);
		SetTimer(hwnd, HUNTER_RUN, HUNTER_TIMER, NULL);
		SetTimer(hwnd, MOUTH, MOUTH_TIMER, NULL);
		//给笔刷赋值
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
	case WM_PAINT:           //处理窗口区域无效时发来的消息
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
		//MessageBox( hwnd, TEXT("时间间隔增加一秒!"), TEXT("计时器消息"), MB_OK );
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
	case WM_KEYDOWN:    //处理按键按下消息
		switch (wParam) {
		case VK_UP:        //上
			d = 0;
			break;
		case VK_DOWN:    //下
			d = 2;
			break;
		case VK_LEFT:    //左
			d = 1;
			break;
		case VK_RIGHT:    //右
			d = 3;
			break;
		default:
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:     //处理鼠标左键被按下的消息
		MessageBox(hwnd, TEXT("鼠标左键被按下。"), TEXT("单击"), MB_OK | MB_ICONINFORMATION);
		return 0;

	case WM_CLOSE:         //处理点击关闭按钮时的消息
						   //if( IDOK == MessageBox( hwnd, TEXT("关闭程序!"), TEXT("结束"), MB_OKCANCEL | MB_ICONQUESTION ) )
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);        //DefWindowProc处理我们自定义的消息处理函数没有处理到的消息
}
struct point Man_Run(HWND hwnd, HBRUSH hbBkColor, HBRUSH hbManColor, struct point *p, int d, int *bean, double Mouth_Angle) {
	static int Nowd = 4;         //本次移动行走的方向 
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
	HFONT hFont = CreateFont(40,         // nHeight, 所创建字体的字符高度
						0,           // nWidth,       字体的字符平均宽度
						0,          // nEscapement,  字符输出方向与水平向右的方向所成角度,以0.1度为单位
						0,             // nOrientation, 字符与基线的角度，以0.1度为单位
						FW_BOLD,        // nWeight,      字符颜色的深浅度
						FALSE,            // bItalic,      斜体属性标志(FALSE:正常字体，TRUE:斜体)
						FALSE,            // bUnderline,   下划线属性标志(FALSE:无下划线，TRUE:有下划线)
						FALSE,             // cStrikeOut,   删除线属性标志(FALSE:无删除线，TRUE:有删除线)
						ANSI_CHARSET,       // nCharSet,        字符集标识0:ANSI字符集，1:系统缺省字符集
						OUT_DEFAULT_PRECIS,  // nOutPrecision,   输出精度
						CLIP_DEFAULT_PRECIS, // nClipPrecision,  剪切精度
						DEFAULT_QUALITY,      // nQuality,        输出品质
						DEFAULT_PITCH|FF_SWISS, // nPitchAndFamily, 字符间距
						TEXT("Arial"));          // lpszFacename,    现有系统TrueType字体名称
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
	TextOut(hdc, 860, 200, TEXT("剩余豆子个数:"), lstrlen(TEXT("剩余豆子个数:")));
	DeleteObject(hFont);
	struct point Nowp;
	Nowp = *p;
	if(p->step){   //覆盖上一次填充的图形 
		Nowp.x = (p->x-dir[Nowd][0])*WALL_LENGTH + dir[Nowd][0]*(p->step-1)*WALL_LENGTH/MAN_STEPTIMES;
		Nowp.y = (p->y+dir[Nowd][1])*WALL_LENGTH - dir[Nowd][1]*(p->step-1)*WALL_LENGTH/MAN_STEPTIMES;
		SelectObject(hdc, hbBkColor);
		Ellipse(hdc, Nowp.x, Nowp.y, Nowp.x+WALL_LENGTH, Nowp.y+WALL_LENGTH);   
	}
	//绘制图形 
	Nowp.x = (p->x-dir[Nowd][0])*WALL_LENGTH + dir[Nowd][0]*p->step*WALL_LENGTH/MAN_STEPTIMES;
	Nowp.y = (p->y+dir[Nowd][1])*WALL_LENGTH - dir[Nowd][1]*p->step*WALL_LENGTH/MAN_STEPTIMES;
	SelectObject(hdc, hbManColor);
	if(Nowd == 3)    //根据行走方向绘制图形 
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
	else{       //Nowd = 4,撞墙,按照d判断方向 
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
void Hunter_Run(HWND hwnd, HBRUSH hbBkColor, HBRUSH hbHunterColor, HBRUSH hbBeanColor, struct point p, struct point *reala, struct point *Nowp) {        //a为怪物结构体数组，p为人位置  
	struct point queue[30000],
		a[3] = { *reala, reala[1], reala[2] };
	int i, j, mark[50][50];
	int h[3] = { 1, 1, 1 }; //记录三个怪物是否已经移动 PS：删除二号
	for (i = 0; i < 3; i++)
		a[i].k = i;
	int head, tail;
	struct point cur, next;
	static int Nowd[3] = {4, 4, 4};
	if(reala->step == HUNTER_STEPTIMES) {
		for(i = 0; i < 3; i++) {
			int Oldx = reala[i].x-dir[Nowd[i]][0],
				Oldy = reala[i].y+dir[Nowd[i]][1];
			//怪物的行走把豆子覆盖掉了
			if(maze[Oldy][Oldx] == 1) {
				HDC hdc = GetDC(hwnd);
				SelectObject(hdc, hbBeanColor);
				Ellipse(hdc, Oldx*WALL_LENGTH + WALL_LENGTH / 3, Oldy*WALL_LENGTH + WALL_LENGTH / 3, Oldx*WALL_LENGTH + WALL_LENGTH * 2 / 3, Oldy*WALL_LENGTH + WALL_LENGTH * 2 / 3);
				ReleaseDC(hwnd, hdc);
			} 
		} 
	memset(mark, -1, sizeof(mark));   //左方向
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
						h[a[j].k] = 0;                  //k号怪物已经找到新位置 
						a[j] = cur;                     //将要走的新位置赋值 
						break;
					}
				}
				if (j < 3) break;
				else {
					mark[cur.y][cur.x] = 0;//标记走过
					queue[tail++] = next;
				}
			}
		}
		if (i < 4) break;
	}

	memset(mark, -1, sizeof(mark));   //下方向
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
					mark[cur.y][cur.x] = 0;//标记走过
					queue[tail++] = next;
				}
			}
		}
		if (i < 4) break;
	}

	memset(mark, -1, sizeof(mark));   //右方向
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
					mark[cur.y][cur.x] = 0;//标记走过
					queue[tail++] = next;
				}
			}
		}
		if (i < 4) break;
	}

	memset(mark, -1, sizeof(mark));   //上方向
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
					mark[cur.y][cur.x] = 0;//标记走过
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
	if(reala->step){   //覆盖上一次填充的图形
		for(i = 0; i < 3; i++){ 
			Nowp[i].x = (reala[i].x-dir[Nowd[i]][0])*WALL_LENGTH + dir[Nowd[i]][0]*(reala->step-1)*WALL_LENGTH/MAN_STEPTIMES;
			Nowp[i].y = (reala[i].y+dir[Nowd[i]][1])*WALL_LENGTH - dir[Nowd[i]][1]*(reala->step-1)*WALL_LENGTH/MAN_STEPTIMES;
			SelectObject(hdc, hbBkColor);
			Ellipse(hdc, Nowp[i].x, Nowp[i].y, Nowp[i].x+WALL_LENGTH, Nowp[i].y+WALL_LENGTH); 
		}  
	}
	//绘制图形 
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
