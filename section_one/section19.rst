.. vim: syntax=rst

文本显示
------------

窗口显示文字的方式，前面讲过一个TEXTBOX文本框，下面讲解一下另一种方式。这种方式之前我们也稍微接触过，就是在WM_PAINT消息，调用TextOut函数绘制文本。

.. _文本显示-1:

文本显示
~~~~~~~~~~~~

文本显示相关的函数
^^^^^^^^^^^^^^^^^^^^^^^^^^^

x_wsprintf函数
''''''''''''''''''''''''''''''''''''

为了适应各种平台，emXGUI自带了C标准库的函数，这些库函数都带了个“x\_”的前缀，它们的函数功能与 C 标准库函数的一样。本章使用的函数x_wsprintf就是其中之一，代码清单19_1_。x_wsprintf是字符串格式化命令，主要功能是把格式化的数据写入某个缓冲区中。

.. code-block:: c
    :caption: 代码清单 19_1 x_wsprintf函数（文件x_libc.h）
    :linenos:
    :name: 代码清单19_1

     int x_wsprintf(WCHAR *dest, const WCHAR *format, ...);

(1) dest：WCHAR型指针，指向将要写入的字符串的缓冲区。

(2) format：格式化字符串。

emXGUI中WCHAR型是unsigned short类型，这与C库的sprintf有点区别。因此，我们传入的format实参应该是一个unsigned short类型的字符串，否则，则会出现Error。

在C语言中，我们使用char来定义字符，占用一个字节，最多只能表示128个字符，也就是ASCII码中的字符。中文则需要用多个字节来表示，可以通过用字母 L 作为 ASCII 字符串的前缀将任何 ASCII
字符串表示为宽字符字符串形式，例如，L"野火"。L与字符串之间没有空格，这样编译器才知道每个字符占用两个字节，即宽字符。

TextOut函数
''''''''''''''''''

在指定位置显示字符串，使用的是函数TextOut。与DrawText的区别在于：TextOut可以在窗口的任何位置显示字符串。但是却不可以设置文字的格式，如居中对齐，左对齐等，见 代码清单19_2_。

.. code-block:: c
    :caption: 代码清单 19‑2 TextOut函数
    :linenos:
    :name: 代码清单19_2

     BOOL TextOut(HDC hdc,int x,int y,LPCWSTR lpString,int nCount);

(1) hdc：绘图上下文。

(2) x，y：文字显示的起点坐标。

(3) lpString：字符串（Unicode-UCS2格式），传入的实参需是宽字符型，支持换行’\r’和回车符’\n’。

(4) nCount：要显示字符的字符数， 当设置小于0时， 将显示整个字符串文本的内容。

文本显示实验
~~~~~~~~~~~~~~~~~~

.. _设计要求-9:

设计要求
^^^^^^^^^^^^

在窗口中输出文字，在首行的位置显示所需的时长。

.. image:: /media/docx081.jpg
   :align: center
   :alt: 图 19‑1 设计要求
   :name: 图19_1

图 19‑1 设计要求

.. _代码分析-9:

代码分析
^^^^^^^^^^^^

(1) 创建父窗口

.. code-block:: c
    :caption: 代码清单 19‑3 GUI_DEMO_Listbox函数（GUI_DEMO_Listbox.c）
    :linenos:
    :name: 代码清单19_3

     void GUI_DEMO_TextOut(void)
     {
<<<<<<< HEAD
     HWND hwnd;
     WNDCLASS wcex;
     MSG msg;

     wcex.Tag = WNDCLASS_TAG;
     wcex.Style = CS_HREDRAW | CS_VREDRAW;
     wcex.lpfnWndProc = WinProc; //设置主窗口消息处理的回调函数.

     wcex.cbClsExtra = 0;
     wcex.cbWndExtra = 0;
     wcex.hInstance = NULL;
     wcex.hIcon = NULL;
     wcex.hCursor = NULL;

     //创建主窗口
     hwnd =CreateWindowEx( NULL,
     &wcex,
     _T("GUI_DEMO - TextOut"), //窗口名称
     WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,
     0,0,GUI_XSIZE,GUI_YSIZE, //窗口位置和大小
     NULL,NULL,NULL,NULL);

     //显示主窗口
     ShowWindow(hwnd,SW_SHOW);

     //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。
     while(GetMessage(&msg,hwnd))
     {
     TranslateMessage(&msg);
     DispatchMessage(&msg);
     }
=======
        HWND hwnd;
        WNDCLASS wcex;
        MSG msg;

        wcex.Tag = WNDCLASS_TAG;
        wcex.Style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WinProc; //设置主窗口消息处理的回调函数.

        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = NULL;
        wcex.hIcon = NULL;
        wcex.hCursor = NULL;

        //创建主窗口
        hwnd =CreateWindowEx( NULL,
        &wcex,
        _T("GUI_DEMO - TextOut"), //窗口名称
        WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,
        0,0,GUI_XSIZE,GUI_YSIZE, //窗口位置和大小
        NULL,NULL,NULL,NULL);

        //显示主窗口
        ShowWindow(hwnd,SW_SHOW);

        //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。
        while(GetMessage(&msg,hwnd))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
>>>>>>> dev
     }

创建父窗口，标题栏为“GUI_DEMO_TextOut”，带有大小边框，设置winProc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

.. code-block:: c
    :caption: 代码清单 19‑4 WM_CREATE消息响应（文件GUI_DEMO_TextOut.c）
    :linenos:
    :name: 代码清单19_4

    case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口.
     {
<<<<<<< HEAD
     GetClientRect(hwnd,&rc); //获得窗口的客户区矩形.

     CreateWindow(BUTTON,L"OK",WS_VISIBLE,
     rc.w-80,8,68,32,hwnd,ID_OK,NULL,NULL); //创建一个按钮(示例).
=======
        GetClientRect(hwnd,&rc); //获得窗口的客户区矩形.

        CreateWindow(BUTTON,L"OK",WS_VISIBLE,
        rc.w-80,8,68,32,hwnd,ID_OK,NULL,NULL); //创建一个按钮(示例).
>>>>>>> dev
     }

WM_CREATE消息中，在坐标（rc.w-80,8）处创建了一个OK按键。用来退出该界面。

2. WM_NOTIFY

.. code-block:: c
    :caption: 代码清单 19‑5 WM_NOTIFY消息响应（文件GUI_DEMO_TextOut.c）
    :linenos:
    :name: 代码清单19_5

     case WM_NOTIFY: //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,高16位为通知码;
     lParam指向了一个NMHDR结构体.
     {
<<<<<<< HEAD
     u16 code,id;

     code =HIWORD(wParam); //获得通知码类型.
     id =LOWORD(wParam); //获得产生该消息的控件ID.

     if(id==ID_OK && code==BN_CLICKED) // 按钮“单击”了.

     {
     PostCloseMessage(hwnd); //使产生WM_CLOSE消息关闭窗口.
     }
     break;
=======
        u16 code,id;

        code =HIWORD(wParam); //获得通知码类型.
        id =LOWORD(wParam); //获得产生该消息的控件ID.

        if(id==ID_OK && code==BN_CLICKED) // 按钮“单击”了.

        {
            PostCloseMessage(hwnd); //使产生WM_CLOSE消息关闭窗口.
        }
        break;
>>>>>>> dev
     }

WM_NOTIFY消息用来检测OK键是否被按下。使用HIWORD和LOWORD函数读取控件的ID和通知码。如果OK键被按下，则发送WM_CLOSE消息关闭窗口。

3. WM_PAINT


.. code-block:: c
    :caption: 代码清单 19‑6 WM_PAINT消息响应
    :linenos:
    :name: 代码清单19_6

     case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
     {
<<<<<<< HEAD
     PAINTSTRUCT ps;
     HDC hdc;
     RECT rc;
     int i,t,y;
     WCHAR wbuf[128];
     POINT Point;
     GetClientRect(hwnd,&rc);

     hdc =BeginPaint(hwnd,&ps); //开始绘图

     ////用户的绘制内容...
     SetTextColor(hdc,MapRGB(hdc,10,10,100));
     t=GUI_GetTickCount();
     y=24;
     i=0;
     Point.x = 0;
     while(y<rc.h)
     {
     Point.y = y;
     ClientToScreen(hwnd, &Point, 1);
     if(Point.y > 480) break;
     TextOut(hdc,10,y,L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",-1);
     y+=20;
     i++;
     }
     t =GUI_GetTickCount()-t;
     SetTextColor(hdc,MapRGB(hdc,250,10,10));
     x_wsprintf(wbuf,L"TextOut Time used:%dms; %.1fms/line",t,(float)t/(float)i);
     TextOut(hdc,10,4,wbuf,-1);
     EndPaint(hwnd,&ps); //结束绘图
     break;
=======
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rc;
        int i,t,y;
        WCHAR wbuf[128];
        POINT Point;
        GetClientRect(hwnd,&rc);

        hdc =BeginPaint(hwnd,&ps); //开始绘图

        ////用户的绘制内容...
        SetTextColor(hdc,MapRGB(hdc,10,10,100));
        t=GUI_GetTickCount();
        y=24;
        i=0;
        Point.x = 0;
        while(y<rc.h)
        {
            Point.y = y;
            ClientToScreen(hwnd, &Point, 1);
            if(Point.y > 480) break;
            TextOut(hdc,10,y,L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",-1);
            y+=20;
            i++;
        }
        t =GUI_GetTickCount()-t;
        SetTextColor(hdc,MapRGB(hdc,250,10,10));
        x_wsprintf(wbuf,L"TextOut Time used:%dms; %.1fms/line",t,(float)t/(float)i);
        TextOut(hdc,10,4,wbuf,-1);
        EndPaint(hwnd,&ps); //结束绘图
        break;
>>>>>>> dev
     }

在WM_PAINT消息中，绘制显示的文字。绘制过程中，需要调用BeginPaint来获取绘图上下文和EndPaint函数结束绘图。使用GUI_GetTickCount函数来得到当前系统的时间，存放到变量t中。TextOut函数用来输出文本，这里显示的内容为：0123456789ABCDEFGHIJK
LMNOPQRSTUVWXYZ。我们使用的字体为GB2312_20_4BPP，字体高是20，所以使每行的文本的起点y坐标偏移20个像素。

调用ClientToScreen函数，将每行的起点坐标，转换为屏幕坐标，这里的起点坐标指的是客户区里面的坐标。这样的话，一旦起点坐标超出了屏幕的高度，就会停止显示文字。ClientToScreen函数的具体说明，可以查阅《emXGUI API 编程手册》章节：窗口/消息系统API。

变量i记录行数，耗费的时间=总时间t/总行数i。x_wsprintf函数的用法，与C语言的sprintf用法一致。以x_w开头的函数，都是emXGUI封装的C库函数。最后，将耗费的时间显示在（10，4）处。


.. code-block:: c
    :caption: 代码清单 19‑7 GUI_AppMain函数（文件GUI_AppMain.c）
    :linenos:
    :name: 代码清单19_7

     void GUI_AppMain(void)
     {
<<<<<<< HEAD
     while(1)
     {
     GUI_DEMO_Button();
     GUI_DEMO_Checkbox();
     GUI_DEMO_Radiobox();
     GUI_DEMO_Textbox();
     GUI_DEMO_Progressbar();

     GUI_DEMO_Scrollbar();
     GUI_DEMO_Listbox();
     GUI_DEMO_Messagebox();
     GUI_DEMO_TextOut();
     }
=======
        while(1)
        {
            GUI_DEMO_Button();
            GUI_DEMO_Checkbox();
            GUI_DEMO_Radiobox();
            GUI_DEMO_Textbox();
            GUI_DEMO_Progressbar();

            GUI_DEMO_Scrollbar();
            GUI_DEMO_Listbox();
            GUI_DEMO_Messagebox();
            GUI_DEMO_TextOut();
        }
>>>>>>> dev
     }

将GUI_DEMO_TextOut函数创建的窗口，加入到GUI_AppMain中，如 代码清单19_7_。

.. _实验现象-9:

实验现象
^^^^^^^^^^^^

实验结果如 图19_2_ 所示。图19_2_ 是在Textout窗口中显示整个屏幕的文字，所花费的时间为200ms。图19_3_ 是拖动窗口到屏幕底端，刚刚好显示3行文字。可以看到耗费的时间大大减少，如果将行数输出到串口的话，串口会输出3。

.. image:: /media/docx082.jpg
   :align: center
   :alt: 图 19‑2 实验结果
   :name: 图19_2

图 19‑2 实验结果

.. image:: /media/docx083.jpg
   :align: center
   :alt: 图 19‑3 实验结果
   :name: 图19_3

图 19‑3 实验结果
