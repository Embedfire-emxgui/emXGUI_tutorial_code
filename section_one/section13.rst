.. vim: syntax=rst

列表框控件
---------------

列表框（ListBox）用于提供多个选项，用户可以选择其中一个或者多个条目，但是不能直接编辑列表框的数据。如 图13_1_ 。

.. image:: /media/docx055.jpg
   :align: center
   :alt: 图 13‑1 列表框
   :name: 图13_1

图 13‑1 列表框

创建列表框
~~~~~~~~~~~~~~~

.. _标准消息类型及参数说明-8:

标准消息类型及参数说明
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

这里使用的消息类型有：WM_CREATE、WM_NOTIFY、WM_CTLCOLOR、WM_DRAWITEM和WM_PAINT。这些消息使用方法都是大同小异，重点说明一下消息WM_NOTIFY。

WM_NOTIFY消息的参数lParam是指向一个NMHDR结构体数据头的地址指针，其成员code存放的是控件发送的事件，可以是列表项被选中（LBN_SELCHANGE），列表项被单击（LBN_CLICKED），成员idFrom表示消息来自于哪个控件，为控件的ID值。

列表框命令说明
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

列表框没有类似进度条的配置结构体，配置列表框，获取列表框的参数，都是通过发送相应的命令来实现的。下面我们看一下，每一个列表框命令的作用。

表格 13‑1 列表框命令

================ ========== ========================== ============================
命令             参数lParam 参数wParam                 具体说明
================ ========== ========================== ============================
LB_ADDSTRING     列表项编号 显示的字符串               设置列表项的内容
LB_INSERTSTRING  列表项编号 显示的字符串               在某个位置插入列表项
LB_DELETESTRING  列表项编号 无                         删除某个位置的列表项
LB_RESETCONTENT  无         无                         清除所有列表项的内容
LB_SETCURSEL     列表项编号 无                         选中某个列表项
LB_GETCURSEL     无         无                         获取当前选中项
LB_GETTEXT       列表项编号 存放的地址，通常使用数组。 获取列表项的显示内容
LB_GETTEXTLEN    列表项编号 无                         得到列表项的内容长度
LB_GETCOUNT      列表项编号 无                         得到列表框中的项目数
LB_SETPOS        无         偏移值                     设置列表框的偏移位置
LB_GETPOS        无         无                         得到列表框的偏移值
LB_GETTOPINDEX   无         无                         获取列表框中当前第一项的编号
LB_GETITEMRECT   列表项编号 无                         得到列表项的位置，大小
LB_GETITEMDATA   列表项编号 无                         得到列表项的附加值
LB_SETITEMDATA   列表项编号 附加值                     设置列表项的附加值
LB_SETITEMHEIGHT 列表项编号 高度值                     设置列表项的高度值
LB_GETITEMHEIGHT 列表项编号 无                         获取列表项的高度值
================ ========== ========================== ============================

注意，列表项编号值都是从零开始，每个列表框的编号都是相互独立，如 图13_2_。

.. image:: /media/docx056.jpg
   :align: center
   :alt: 图 13‑2 列表项编号
   :name: 图13_2

图 13‑2 列表项编号

List1，List2都是列表框，item后面的括号代表的是编号值，两个列表框的项目编号都是独立开的。编号值可以理解为当前列表项所在的行数（从0开始计数），当用户设置的索引值大于现有的总行数，便会把这个新的item的索引值强制修正到“总行数－１”的值，也就是在最后面的位置。

.. image:: /media/docx057.jpg
   :align: center
   :alt: 图 13‑3 列表行号
   :name: 图13_3

图 13_3 列表行号

图13_3_，我们要在原有的列表框中，加入新的item，他的行数为10，此时的总行数为7（算上新来的），emXGUI则会将行数修改为“7-1”，使item7插入到列表框的最后面。

创建列表框控件函数
^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c
    :caption: 代码清单 13‑1 创建列表框控件函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单13_1

     HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,
<<<<<<< HEAD
     U32 dwStyle, int x, int y, int nWidth, int nHeight,
     HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);
=======
                        U32 dwStyle, int x, int y, int nWidth, int nHeight,
                        HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);
>>>>>>> dev

1) lpClass：窗口类。列表项控件，这里选择LISTBOX。

2) dwStyle：列表框的风格。列表框控件支持窗口风格参数，还可以使用以下参数：产生额外的通知码（LBS_NOTIFY）、行与行之间有分界线（LBS_LINE） 和没有可选择项（LBS_NOSEL）。

至于其他的参数，也是同样的用法，这里不作描述。我们创建控件调用的CreateWindow函数，实际上就是CreateWindowEx函数。

创建列表框控件实验
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. _设计要求-8:

设计要求
^^^^^^^^^^^^

设计一个窗口，包括三个列表框：List1、List2以及List3。其中List2是采用自定义重绘的控件，List1和List2是系统自带的控件。

.. image:: /media/docx058.jpg
   :align: center
   :alt: 图 13‑4 设计要求
   :name: 图13_4

图 13‑4 设计要求

.. _代码分析-8:

代码分析
^^^^^^^^^^^^

(1) 创建父窗口

.. code-block:: c
    :caption: 代码清单 13‑2 GUI_DEMO_Listbox函数（GUI_DEMO_Listbox.c）
    :linenos:
    :name: 代码清单13_2

     void GUI_DEMO_Listbox(void)
     {
<<<<<<< HEAD
     HWND hwnd;
     WNDCLASS wcex;
     MSG msg;

     InvalidateRect(GetDesktopWindow(),NULL,TRUE);

     wcex.Tag = WNDCLASS_TAG;

     wcex.Style = CS_HREDRAW | CS_VREDRAW;
     wcex.lpfnWndProc = win_proc;
     wcex.cbClsExtra = 0;
     wcex.cbWndExtra = 0;
     wcex.hInstance = 0;//hInst;
     wcex.hIcon = 0;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);
     wcex.hCursor = 0;//LoadCursor(NULL, IDC_ARROW);
     hwnd =CreateWindowEx( NULL,
     &wcex,
     _T("GUI Demo - Listbox"),
     WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,
     0,0,GUI_XSIZE,GUI_YSIZE,
     NULL,NULL,NULL,NULL);
     ShowWindow(hwnd,SW_SHOW);
     while(GetMessage(&msg,hwnd))
     {
     TranslateMessage(&msg);
     DispatchMessage(&msg);
     }

=======
        HWND hwnd;
        WNDCLASS wcex;
        MSG msg;

        InvalidateRect(GetDesktopWindow(),NULL,TRUE);

        wcex.Tag = WNDCLASS_TAG;

        wcex.Style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = win_proc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = 0;//hInst;
        wcex.hIcon = 0;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);
        wcex.hCursor = 0;//LoadCursor(NULL, IDC_ARROW);
        hwnd =CreateWindowEx( NULL,
        &wcex,
        _T("GUI Demo - Listbox"),
        WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,
        0,0,GUI_XSIZE,GUI_YSIZE,
        NULL,NULL,NULL,NULL);
        ShowWindow(hwnd,SW_SHOW);
        while(GetMessage(&msg,hwnd))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
>>>>>>> dev
     }

创建父窗口，标题栏为“GUI Demo - Listbox”，带有大小边框，设置winProc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

.. code-block:: c
    :caption: 代码清单 13‑3 WM_CREATE消息响应 （文件GUI_DEMO_Listbox.c）
    :linenos:
    :name: 代码清单13_3

     case WM_CREATE:
     {
<<<<<<< HEAD
     //创建自绘制列表框LISTBOX1
     wnd=CreateWindow(LISTBOX,_T("Listbox"),WS_OWNERDRAW|LBS_LINE|LBS_NOTIFY|WS_VISIBLE,
     8,120,160,200,hwnd,ID_LISTBOX1,NULL,NULL);
     //设置列表项的内容
     SendMessage(wnd,LB_ADDSTRING,0,(LPARAM)L" ");
     SendMessage(wnd,LB_ADDSTRING,1,(LPARAM)L" ");
     SendMessage(wnd,LB_ADDSTRING,2,(LPARAM)L"Item-1-2");

     SendMessage(wnd,LB_ADDSTRING,3,(LPARAM)L"Item-1-3");
     SendMessage(wnd,LB_ADDSTRING,4,(LPARAM)L"Item-1-4");
     SendMessage(wnd,LB_ADDSTRING,5,(LPARAM)L"Item-1-5");
     SendMessage(wnd,LB_ADDSTRING,6,(LPARAM)L"Item-1-6");
     SendMessage(wnd,LB_ADDSTRING,7,(LPARAM)L"Item-1-7");
     SendMessage(wnd,LB_ADDSTRING,8,(LPARAM)L"Item-1-8");
     SendMessage(wnd,LB_ADDSTRING,9,(LPARAM)L"Item-1-9");
     SendMessage(wnd,LB_ADDSTRING,10,(LPARAM)L"Item-1-10");

     //设置LISTBOX1中的列表项行高
     for(int i = 0; i < 11; i++)
     SendMessage(wnd,LB_SETITEMHEIGHT,i,40);
     //创建列表框LISTBOX2
     wnd=CreateWindow(LISTBOX,_T("Listbox2"),LBS_LINE|WS_BORDER|WS_VISIBLE,
     200,8,100,160,hwnd,ID_LISTBOX2,NULL,NULL);
     //设置列表项的内容
     SendMessage(wnd,LB_ADDSTRING,0,(LPARAM)L"Item-2-0");
     SendMessage(wnd,LB_ADDSTRING,1,(LPARAM)L"Item-2-1");
     SendMessage(wnd,LB_ADDSTRING,2,(LPARAM)L"Item-2-2");
     SendMessage(wnd,LB_ADDSTRING,3,(LPARAM)L"Item-2-3");
     SendMessage(wnd,LB_ADDSTRING,4,(LPARAM)L"Item-2-4");
     SendMessage(wnd,LB_ADDSTRING,5,(LPARAM)L"Item-2-5");
     SendMessage(wnd,LB_ADDSTRING,6,(LPARAM)L"Item-2-6");
     SendMessage(wnd,LB_ADDSTRING,7,(LPARAM)L"Item-2-7");
     SendMessage(wnd,LB_ADDSTRING,8,(LPARAM)L"Item-2-8");

     //创建列表框LISTBOX3
     wnd=CreateWindow(LISTBOX,_T("Listbox3"),LBS_LINE|WS_BORDER|WS_VISIBLE,
     8,8,160,100,hwnd,ID_LISTBOX3,NULL,NULL);
     //设置列表项的内容
     SendMessage(wnd,LB_ADDSTRING,0,(LPARAM)L"Item-3-0");
     SendMessage(wnd,LB_ADDSTRING,1,(LPARAM)L"Item-3-1");
     SendMessage(wnd,LB_ADDSTRING,2,(LPARAM)L"Item-3-2");
     SendMessage(wnd,LB_ADDSTRING,3,(LPARAM)L"Item-3-3");
     SendMessage(wnd,LB_ADDSTRING,4,(LPARAM)L"Item-3-4");
     SendMessage(wnd,LB_ADDSTRING,5,(LPARAM)L"Item-3-5");
     SendMessage(wnd,LB_ADDSTRING,6,(LPARAM)L"Item-3-6");
     SendMessage(wnd,LB_ADDSTRING,7,(LPARAM)L"Item-3-7");
     SendMessage(wnd,LB_ADDSTRING,8,(LPARAM)L"Item-3-8");

     return TRUE;
=======
        //创建自绘制列表框LISTBOX1
        wnd=CreateWindow(LISTBOX,_T("Listbox"),WS_OWNERDRAW|LBS_LINE|LBS_NOTIFY|WS_VISIBLE,
        8,120,160,200,hwnd,ID_LISTBOX1,NULL,NULL);
        //设置列表项的内容
        SendMessage(wnd,LB_ADDSTRING,0,(LPARAM)L" ");
        SendMessage(wnd,LB_ADDSTRING,1,(LPARAM)L" ");
        SendMessage(wnd,LB_ADDSTRING,2,(LPARAM)L"Item-1-2");

        SendMessage(wnd,LB_ADDSTRING,3,(LPARAM)L"Item-1-3");
        SendMessage(wnd,LB_ADDSTRING,4,(LPARAM)L"Item-1-4");
        SendMessage(wnd,LB_ADDSTRING,5,(LPARAM)L"Item-1-5");
        SendMessage(wnd,LB_ADDSTRING,6,(LPARAM)L"Item-1-6");
        SendMessage(wnd,LB_ADDSTRING,7,(LPARAM)L"Item-1-7");
        SendMessage(wnd,LB_ADDSTRING,8,(LPARAM)L"Item-1-8");
        SendMessage(wnd,LB_ADDSTRING,9,(LPARAM)L"Item-1-9");
        SendMessage(wnd,LB_ADDSTRING,10,(LPARAM)L"Item-1-10");

        //设置LISTBOX1中的列表项行高
        for(int i = 0; i < 11; i++)
        SendMessage(wnd,LB_SETITEMHEIGHT,i,40);
        //创建列表框LISTBOX2
        wnd=CreateWindow(LISTBOX,_T("Listbox2"),LBS_LINE|WS_BORDER|WS_VISIBLE,
        200,8,100,160,hwnd,ID_LISTBOX2,NULL,NULL);
        //设置列表项的内容
        SendMessage(wnd,LB_ADDSTRING,0,(LPARAM)L"Item-2-0");
        SendMessage(wnd,LB_ADDSTRING,1,(LPARAM)L"Item-2-1");
        SendMessage(wnd,LB_ADDSTRING,2,(LPARAM)L"Item-2-2");
        SendMessage(wnd,LB_ADDSTRING,3,(LPARAM)L"Item-2-3");
        SendMessage(wnd,LB_ADDSTRING,4,(LPARAM)L"Item-2-4");
        SendMessage(wnd,LB_ADDSTRING,5,(LPARAM)L"Item-2-5");
        SendMessage(wnd,LB_ADDSTRING,6,(LPARAM)L"Item-2-6");
        SendMessage(wnd,LB_ADDSTRING,7,(LPARAM)L"Item-2-7");
        SendMessage(wnd,LB_ADDSTRING,8,(LPARAM)L"Item-2-8");

        //创建列表框LISTBOX3
        wnd=CreateWindow(LISTBOX,_T("Listbox3"),LBS_LINE|WS_BORDER|WS_VISIBLE,
        8,8,160,100,hwnd,ID_LISTBOX3,NULL,NULL);
        //设置列表项的内容
        SendMessage(wnd,LB_ADDSTRING,0,(LPARAM)L"Item-3-0");
        SendMessage(wnd,LB_ADDSTRING,1,(LPARAM)L"Item-3-1");
        SendMessage(wnd,LB_ADDSTRING,2,(LPARAM)L"Item-3-2");
        SendMessage(wnd,LB_ADDSTRING,3,(LPARAM)L"Item-3-3");
        SendMessage(wnd,LB_ADDSTRING,4,(LPARAM)L"Item-3-4");
        SendMessage(wnd,LB_ADDSTRING,5,(LPARAM)L"Item-3-5");
        SendMessage(wnd,LB_ADDSTRING,6,(LPARAM)L"Item-3-6");
        SendMessage(wnd,LB_ADDSTRING,7,(LPARAM)L"Item-3-7");
        SendMessage(wnd,LB_ADDSTRING,8,(LPARAM)L"Item-3-8");

        return TRUE;
>>>>>>> dev
     }

创建三个列表框：List1由用户自定义绘制的控件，且可以额外的通知码（LBN_SELCHANGE、LBN_KILLFOCUS和LBN_SETFOCUS），List2和List3是标准控件。发送消息LB_ADDSTRING来设置列表项的内容。发送消息LB_SETITEMHEIGHT来设置LISTBOX
1列表项的高度。List1这里创建了两个显示空白字符的列表项，是为了实现透明效果的，具体见WM_DRAWITEM消息。

2. WM_CTLCOLOR

.. code-block:: c
    :caption: 代码清单 13‑4 WM_CTLCOLOR消息响应（文件GUI_DEMO_Listbox.c）
    :linenos:
    :name: 代码清单13_4

    case WM_CTLCOLOR:
    {
<<<<<<< HEAD
    u16 id;
    id =LOWORD(wParam);
    //修改ID_LISTBOX3的颜色
    if(id== ID_LISTBOX3)
    {
    CTLCOLOR *cr;
    cr =(CTLCOLOR*)lParam;
     cr->TextColor =RGB888(255,255,255);//文字颜色
     cr->BackColor =RGB888(0,0,0);//背景颜色
     cr->BorderColor =RGB888(50,150,50);//边框颜色
     cr->ForeColor =RGB888(0,50,0);//选中框颜色
     return TRUE;
     }
     else
     {
     return FALSE;
     }
=======
        u16 id;
        id =LOWORD(wParam);
        //修改ID_LISTBOX3的颜色
        if(id== ID_LISTBOX3)
        {
            CTLCOLOR *cr;
            cr =(CTLCOLOR*)lParam;
            cr->TextColor =RGB888(255,255,255);//文字颜色
            cr->BackColor =RGB888(0,0,0);//背景颜色
            cr->BorderColor =RGB888(50,150,50);//边框颜色
            cr->ForeColor =RGB888(0,50,0);//选中框颜色
            return TRUE;
        }
        else
        {
            return FALSE;
        }
>>>>>>> dev
     }

LISTBOX3控件在绘制前，会发送WM_CTLCOLOR到父窗口，通过WM_CTLCOLOR消息来改变控件的颜色值，返回TRUE，否则，系统将忽略本次操作，继续使用默认的颜色进行绘制。

3. WM_DRAWITEM

.. code-block:: c
    :caption: 代码清单 13‑5 WM_DRAWITEM消息响应（文件GUI_DEMO_Listbox.c）
    :linenos:
    :name: 代码清单13_5

     case WM_DRAWITEM:
     {
<<<<<<< HEAD
     DRAWITEM_HDR *ds;
     ds =(DRAWITEM_HDR*)lParam;

     if(wParam==ID_LISTBOX1)
     {
     _listbox_owner_draw_x(ds);
     return TRUE;

     }
     return FALSE;
=======
        DRAWITEM_HDR *ds;
        ds =(DRAWITEM_HDR*)lParam;

        if(wParam==ID_LISTBOX1)
        {
        _listbox_owner_draw_x(ds);
        return TRUE;

        }
        return FALSE;
>>>>>>> dev
     }

WM_DRAWITEM消息里面负责对List Box1实现重绘。调用函数_listbox_owner_draw_x，来实现，见 代码清单13_6_。

.. code-block:: c
    :caption: 代码清单 13‑6 _listbox_owner_draw_x函数（文件GUI_DEMO_Listbox.c）
    :linenos:
    :name: 代码清单13_6

     static void _listbox_owner_draw_x(DRAWITEM_HDR *ds)
     {
<<<<<<< HEAD
     HWND hwnd;
     HDC hdc,hdc0,hdc1;
     HDC hdc_mem;
     RECT rc;
     int x,y,w,h;
     hwnd =ds->hwnd;

     hdc =ds->hDC;

     //创建三个一样大小的DC,把listbox分别绘制进去，但颜色参数不同的.
     hdc_mem = CreateMemoryDC(SURF_SCREEN,ds->rc.w,ds->rc.h); //透明图层
     hdc0 =CreateMemoryDC(SURF_SCREEN,ds->rc.w,ds->rc.h); //缩小图层
     hdc1 =CreateMemoryDC(SURF_SCREEN,ds->rc.w,ds->rc.h); //放大图层

     //绘制与窗口背景颜色一样的矩形（实现透明）
     SetBrushColor(hdc_mem,MapRGB(hdc_mem,207,212,215));
     FillRect(hdc_mem,&ds->rc);

     //一个listbox绘到hdc0中
     _draw_listbox(hdc0,hwnd,RGB888(100,149,237),RGB888(250,0,0),hDefaultFont);
     //
     //一个listbox绘到hdc1中（图片的第三部分）
     _draw_listbox(hdc1,hwnd,RGB888(0,0,0),RGB888(250,0,0),hZoomFont);

     //获取列表框中的第二行的高度
     SendMessage(hwnd,LB_GETITEMRECT,2,(LPARAM)&rc);
     //第一步/
     //将透明部分从hdc_mem里复制出来.
     x =0;
     y =0;
     w =rc_m.w;
     h =rc.y;
     BitBlt(hdc,x,y,w,h,hdc_mem,x,y,SRCCOPY);
     //第二步/
     //将缩小部分从hdc0里复制出来.
     x = 0;
     y = rc.y;
     w = rc_m.w;
     h = rc_m.y - rc.y;
     BitBlt(hdc,x,y,w,h,hdc0,x,y,SRCCOPY);
     //第三步/
     //中间矩形部分从hdc1里复制出来.
     BitBlt(hdc,rc_m.x,rc_m.y,rc_m.w,rc_m.h,hdc1,rc_m.x,rc_m.y,SRCCOPY);
     //第四步/
     //下面的矩形部分从hdc0里复制出来.
     x =0;
     y =rc_m.y+rc_m.h;
     w =rc_m.w;
     h =ds->rc.h-(rc_m.y+rc_m.h);
     BitBlt(hdc,x,y,w,h,hdc0,x,y,SRCCOPY);
     //释放内存
     DeleteDC(hdc0);
     DeleteDC(hdc1);
     DeleteDC(hdc_mem);
=======
        HWND hwnd;
        HDC hdc,hdc0,hdc1;
        HDC hdc_mem;
        RECT rc;
        int x,y,w,h;
        hwnd =ds->hwnd;

        hdc =ds->hDC;

        //创建三个一样大小的DC,把listbox分别绘制进去，但颜色参数不同的.
        hdc_mem = CreateMemoryDC(SURF_SCREEN,ds->rc.w,ds->rc.h); //透明图层
        hdc0 =CreateMemoryDC(SURF_SCREEN,ds->rc.w,ds->rc.h); //缩小图层
        hdc1 =CreateMemoryDC(SURF_SCREEN,ds->rc.w,ds->rc.h); //放大图层

        //绘制与窗口背景颜色一样的矩形（实现透明）
        SetBrushColor(hdc_mem,MapRGB(hdc_mem,207,212,215));
        FillRect(hdc_mem,&ds->rc);

        //一个listbox绘到hdc0中
        _draw_listbox(hdc0,hwnd,RGB888(100,149,237),RGB888(250,0,0),hDefaultFont);
        //
        //一个listbox绘到hdc1中（图片的第三部分）
        _draw_listbox(hdc1,hwnd,RGB888(0,0,0),RGB888(250,0,0),hZoomFont);

        //获取列表框中的第二行的高度
        SendMessage(hwnd,LB_GETITEMRECT,2,(LPARAM)&rc);
        //第一步/
        //将透明部分从hdc_mem里复制出来.
        x =0;
        y =0;
        w =rc_m.w;
        h =rc.y;
        BitBlt(hdc,x,y,w,h,hdc_mem,x,y,SRCCOPY);
        //第二步/
        //将缩小部分从hdc0里复制出来.
        x = 0;
        y = rc.y;
        w = rc_m.w;
        h = rc_m.y - rc.y;
        BitBlt(hdc,x,y,w,h,hdc0,x,y,SRCCOPY);
        //第三步/
        //中间矩形部分从hdc1里复制出来.
        BitBlt(hdc,rc_m.x,rc_m.y,rc_m.w,rc_m.h,hdc1,rc_m.x,rc_m.y,SRCCOPY);
        //第四步/
        //下面的矩形部分从hdc0里复制出来.
        x =0;
        y =rc_m.y+rc_m.h;
        w =rc_m.w;
        h =ds->rc.h-(rc_m.y+rc_m.h);
        BitBlt(hdc,x,y,w,h,hdc0,x,y,SRCCOPY);
        //释放内存
        DeleteDC(hdc0);
        DeleteDC(hdc1);
        DeleteDC(hdc_mem);
>>>>>>> dev
     }

下面我们重点讲解这个函数，只有学会这个函数里面的操作，未来才有可能在emXGUI中“为所欲为”。

在PS里面，有一个叫做图层的概念。简单地说，每一个图层都是一张独立的图像，每个图层依次取图像的一部分内容，将这些内容按顺序叠加起来，便可以看到完整的图像，参考 图13_5_。

.. image:: /media/docx059.jpg
   :align: center
   :alt: 图 13‑5 合成流程
   :name: 图13_5

图 13‑5 合成流程

当列表项经过白色区域时，颜色会改变，且它的字体会变大，而其他的列表项字体颜色和大小不发生改变。

1处：画个和背景颜色一样的图层，来实现透明的效果；

2、3处：绘制一个红色背景的矩形区域，在矩形的高度的1/4处绘制一个白色区域（选择框），采用淡蓝色的小字体来显示列表项内容。

4处：绘制一个与处一模一样的内容，在列表项内容显示的格式上，采用黑色的大字体。

依次取上述~处的内容，则可以合成最后的图画，以上就是理论部分的实现。在emXGUI中，内存型DC就相当于我们所说的图层，调用CreateMemoryDC函数来创建图层，见 代码清单13_7_。

.. code-block:: c
    :caption: 代码清单 13‑7 CreateMemoryDC（emXGUI。h）
    :linenos:
    :name: 代码清单13_7

     HDC CreateMemoryDC(SURF_FORMAT Format,int nWidth,int nHeight);

1) Format：颜色的格式，可以是屏幕颜色一致（SURF_SCREEN）、ARGB4444格式（SURF_ARGB4444）、ARGB8888格式（SURF_ARGB8888）。使用的时候，不需要修改底层驱动。

2) nWidth、nHeight：创建DC的大小。创建内存型DC，实际上就是在我们的内存中开辟一块区域，用来绘制图形的。这块区域的起始位置一定是（0，0），我们只需要负责定义这块区域的大小即可。

切记，在使用后，需要使用DeleteDC，来释放掉内存型DC。

在 代码清单13_6_ 中，创建了三个内存型DC，分别对应了 图13_5_ 的图片（从左到右）。

调用_draw_listbox函数来绘制列表框的外观，包括矩形区域，白色选择框以及字体，见 代码清单13_8_ 。

.. code-block:: c
    :caption: 代码清单 13‑8 _draw_listbox函数（文件GUI_DEMO_Listbox.c）
    :linenos:
    :name: 代码清单13_8

     static void _draw_listbox(HDC hdc,HWND hwnd,COLOR_RGB32 text_c,COLOR_RGB32 back_c,HFONT hFont)
     {
<<<<<<< HEAD
     RECT rc,rc_cli;
     int i,count;
     WCHAR wbuf[128];
     GetClientRect(hwnd,&rc_cli);

     SetBrushColor(hdc,MapRGB888(hdc,back_c));
     FillRect(hdc,&rc_cli);


     //定义一个中间的矩形．
     rc_m.w =rc_cli.w;
     rc_m.h =40;
     rc_m.x =0;
     rc_m.y =(rc_cli.h-rc_m.h)>>1;
     //中间框绘制到hdc1中．
     SetBrushColor(hdc,MapRGB(hdc,255,255,255));
     FillRect(hdc,&rc_m);

     SetFont(hdc,hFont);
     SetTextColor(hdc,MapRGB888(hdc,text_c));

     i=SendMessage(hwnd,LB_GETTOPINDEX,0,0);
     count=SendMessage(hwnd,LB_GETCOUNT,0,0);
     while(i<count)
     {
     SendMessage(hwnd,LB_GETITEMRECT,i,(LPARAM)&rc);
     if(rc.y > rc_cli.h)
     {
     break;
     }

     SendMessage(hwnd,LB_GETTEXT,i,(LPARAM)wbuf);
     DrawText(hdc,wbuf,-1,&rc,DT_SINGLELINE|DT_CENTER|DT_VCENTER);

     i++;
     }
=======
        RECT rc,rc_cli;
        int i,count;
        WCHAR wbuf[128];
        GetClientRect(hwnd,&rc_cli);

        SetBrushColor(hdc,MapRGB888(hdc,back_c));
        FillRect(hdc,&rc_cli);

        //定义一个中间的矩形．
        rc_m.w =rc_cli.w;
        rc_m.h =40;
        rc_m.x =0;
        rc_m.y =(rc_cli.h-rc_m.h)>>1;
        //中间框绘制到hdc1中．
        SetBrushColor(hdc,MapRGB(hdc,255,255,255));
        FillRect(hdc,&rc_m);

        SetFont(hdc,hFont);
        SetTextColor(hdc,MapRGB888(hdc,text_c));

        i=SendMessage(hwnd,LB_GETTOPINDEX,0,0);
        count=SendMessage(hwnd,LB_GETCOUNT,0,0);
        while(i<count)
        {
            SendMessage(hwnd,LB_GETITEMRECT,i,(LPARAM)&rc);
            if(rc.y > rc_cli.h)
            {
                break;
            }

            SendMessage(hwnd,LB_GETTEXT,i,(LPARAM)wbuf);
            DrawText(hdc,wbuf,-1,&rc,DT_SINGLELINE|DT_CENTER|DT_VCENTER);

            i++;
        }
>>>>>>> dev
     }

_draw_listbox函数的形参为：窗口的绘图DC，父窗口，文字颜色，背景颜色以及使用的字体。

使用LB_GETTOPINDEX来获取处于当前列表框的第一项，注意，这里的第一项不是我们自己定义的第一项，是列表框滑动后，显示在最开始位置的那一项。

发送LB_GETCOUNT来获取列表框的总行数。如果第一项的值小于总行数，则对第一项及其后面的N项进行重绘。

例程中，通过发送LB_GETITEMRECT来获取每一个列表项的位置以及大小，并在这个区域内，使用DrawText函数来显示文字。

到这里，就完成了放大图层和缩小图层的绘制，也就是图 13‑5的第二幅和第三幅小图。

第一幅小图的实现，是通过调用SetBrushColor函数设置矩形的颜色，与窗口的颜色一致，这里的窗口颜色为RGB(207,212,215)，调用FillRect函数来填充矩形。

以上操作，就将三个图层的内容绘制完毕。至于如何每个图层显示的内容，请看下面讲解。

.. image:: /media/docx060.jpg
   :align: center
   :alt: 图 13‑6 合成图的放大版
   :name: 图13_6

图 13_6 合成图的放大版

图13_6_，是合成图层的放大版。处是item2的x，y坐标。处是选择框的x，y坐标，处的坐标是（0，选择框的y坐标+选择框的高度）。

有了这三个坐标，我们就可以对每一个图层进行切割合成了。在emXGUI中，使用BitBlt函数来实现图像的切割合成，函数的具体使用方法，可以参考《emXGUI API编程手册》章节：绘图API。

对于透明的图层，我们只需要顶部到item处的区域即可，也就是起点为（0，0），高度为item2的y坐标，宽度则为控件的宽度，见 代码清单13_9_。

.. code-block:: c
    :caption: 代码清单 13‑9 切割图像以及合成图像
    :linenos:
    :name: 代码清单13_9

     //获取列表框中的第二行的高度
     SendMessage(hwnd,LB_GETITEMRECT,2,(LPARAM)&rc);
     //第一步/
     //将透明部分从hdc_mem里复制出来.
     x =0;
     y =0;
     w =rc_m.w;
     h =rc.y;
     BitBlt(hdc,x,y,w,h,hdc_mem,x,y,SRCCOPY);

使用LB_GETITEMRECT消息来获取Item2的位置以及大小。使用BitBlt函数，将透明图层（hdc_mem）的内容，复制到合成图层中（hdc）。这里的w，h限制了截取的大小，是否就相等于切割的过程。将hdc_mem的内容复制到合成图层中，则是合成的过程。请注意，合成图层和透明图像的x，y坐
标需要是一致的，否则就会产生错位，读者可以脑补一下画面。

~之间的区域：起始位置为（item2的x坐标，item2的y坐标），大小为控件的宽度*（白色选择框的y坐标减去item2的y坐标）和处的区域：起始位置为（白色选择框的x坐标, 白色选择框的y坐标），大小为控件的宽度*（控件的高度减去白色选择框的y坐标），就是缩小图层的内容，见 代码清单13_10_。

.. code-block:: c
    :caption: 代码清单 13_10 切割缩小图层以及合成图像
    :linenos:
    :name: 代码清单13_10

     //第二步/
     //将缩小部分从hdc0里复制出来.
     x = 0;
     y = rc.y;
     w = rc_m.w;
     h = rc_m.y - rc.y;
     BitBlt(hdc,x,y,w,h,hdc0,x,y,SRCCOPY);

     //第四步/
     //下面的矩形部分从hdc0里复制出来.
     x =0;
     y =rc_m.y+rc_m.h;
     w =rc_m.w;
     h =ds->rc.h-(rc_m.y+rc_m.h);
     BitBlt(hdc,x,y,w,h,hdc0,x,y,SRCCOPY);

上述代码将~之间的区域和处的区域提取出来，并赋值到合成图层（hdc）中。

最后，将放大图层的选择框区域提取出来，就可以得到我们的放大图像了，见 代码清单13_11_。

.. code-block:: c
    :caption: 代码清单 13‑11切割放大图层以及合成图像
    :linenos:
    :name: 代码清单13_11

     //第三步/
     //中间矩形部分从hdc1里复制出来.
     BitBlt(hdc,rc_m.x,rc_m.y,rc_m.w,rc_m.h,hdc1,rc_m.x,rc_m.y,SRCCOPY);

这样窗口就设计完成了，将GUI_DEMO_Listbox函数加入到GUI_AppMain中，见 代码清单13_12_。

.. code-block:: c
    :caption: 代码清单13_12 GUI_AppMain函数（文件GUI_AppMain.c）
    :linenos:
    :name: 代码清单13_12

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
        }
>>>>>>> dev
     }

.. _实验结果-1:

实验结果
^^^^^^^^^^^^

.. image:: /media/docx061.jpg
   :align: center
   :alt: 图 13‑7 实验结果
   :name: 图13_7

图 13‑7 实验结果

实验结果如 图13_7_，窗口设计与设计要求基本相同。滑动红色的列表框，跳过的列表项会在上方显示。这是我们自定义绘制的列表框。左上方和右边的列表框为系统自带的控件。用户点击某个项目，则会选择某个项目。
