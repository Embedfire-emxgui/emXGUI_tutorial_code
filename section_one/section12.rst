.. vim: syntax=rst

滚动条控件
---------------

在我们使用WINDOWS的软件的时候，右侧有一个条，用于翻页，他就是滚动条，如 图12_1_，由滚动滑块和滚动箭头组成。滚动条可以用于滚动列表框或任何其他类型的窗口。滚动条的方向确定用户操作滚动条时滚动的方向。水平滚动条只允许用户向左或向右滚动窗口的内容，垂直滚动条允许用户向上或向下滚动内容。

.. image:: /media/docx049.jpg
   :align: center
   :alt: 图 12‑1滚动条
   :name: 图12_1

创建滚动条
~~~~~~~~~~~~~~~

.. _标准消息类型及参数说明-7:

标准消息类型及参数说明
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

本章使用的消息类型有：WM_CREATE、WM_NOTIFY、WM_CTLCOLOR和WM_DRAWITEM。这些消息的参数及作用，前面已经解释得很详细了。这里只讲解一下，WM_NOTIFY在滚动条中的用法。

WM_NOTIFY的wParam低16位存放着发送该消息的控件ID，lParam参数是以NMHDR结构体开头，实际为 NM_SCROLLBAR扩展结构，里面附带了更多的信息，见 代码清单12_1_。
一般采用NMHDR结构体的code来判断是否发生单击事件，是的话则通过NM_SCROLLBAR的cmd成员判断用户单击的位置。

.. code-block:: c
    :caption: 代码清单 12‑1 滚动条通知命令（文件emXGUI.h）
    :linenos:
    :name: 代码清单12_1

     #define SB_TRACK (0) //点击滑块
     #define SB_ARROWUP (1) //单击上箭头
     #define SB_ARROWDOWN (2) //单击上箭头
     #define SB_PAGEUP (3) //单击滚动条的上半部分（空白区域）
     #define SB_PAGEDOWN (4) //单击滚动条的下半部分（空白区域）

     #define SB_ARROWLEFT (5) //单击左箭头
     #define SB_ARROWRIGHT (6) //单击右箭头
     #define SB_PAGELEFT (7) //单击滚动条的左半部分（空白区域）

     #define SB_PAGERIGHT (8) //单击滚动条的右半部分（空白区域）

以水平滚动条为例，见 图12_2_ ，讲解一下上面的命令。

.. image:: /media/docx050.jpg
   :align: center
   :alt: 图 12‑2 滚动条命令
   :name: 图12_2

代码清单12_2_ 中的SB_ARROWLEFT及SB_ARROWRIGHT就是 图12_2_ 中的最左端和最右端的箭头。而SB_PAGELEFT对应的是 图12_2_ 中处，SB_PAGERIGHT对应的 是 图12_2_ 中处。

滚动条配置结构体
^^^^^^^^^^^^^^^^^^^^^^^^

创建滚动条之后，需要发送SBM_SETSCROLLINFO消息，来配置滚动条的参数，这些参数都存放在SCROLLINFO结构体中，见代码清单 12‑2。

.. code-block:: c
    :caption: 代码清单 12‑2 SCROLLINFO结构体（文件emXGUI.h）
    :linenos:
    :name: 代码清单12_2

     typedef struct tagSCROLLINFO
     {
        u16 cbSize; //SCROLLINFO结构体大小
        u16 fMask; //功能选择位
        s32 nMin; //最小值
        s32 nMax; //最大值
        s32 nValue; //当前值
        u16 TrackSize; //滑块大小
        u16 ArrowSize; //箭头框的大小
     }SCROLLINFO,SCROLLBAR_CFG;

1) cbSize：用来存放结构体的大小。必须要将cbSize值设置成 sizeof(SCROLLINFO)。

2) fMask：功能选择位。只有相应的 MASK 位置1，才会更新到滚动条控件的内部数据结构体。

3) nMin、nMax、nValue：滚动条的最小值，最大值和当前值。

4) TrackSize：滑块的大小。对于水平滚动条，这里指的是滑块的宽度，而垂直滚动条，则是滑块的高度。

5) ArrowSize：箭头框的大小。对于水平滚动条，指的是箭头框的水平宽度，高度就是控件的客户区高度。对于垂直滚动条，是箭头框"的垂直高度，宽度就是控件的客户区宽度。

以水平滚动条为例，如 图12_3_。

.. image:: /media/docx051.jpg
   :align: center
   :alt: 图 12‑3 SCROLLINFO结构体
   :name: 图12_3

创建滚动条控件函数
^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c
    :caption: 代码清单 12‑3创建窗口函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单12_3

     HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,
                        U32 dwStyle, int x, int y, int nWidth, int nHeight,
                        HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);

1) lpClass：窗口类。对于系统标准控件，可以为：BUTTON(常规按钮，复选框，单选框，组合框)，SCROLLBAR(水平/垂直滚动条)， LISTBOX(列表框)。TEXTBOX（文本框）…等等。这里选择SCROLLBAR。

2) dwStyle：滚动条的风格。参数SBS_VERT代表垂直风格类型。参数SBS_HORZ表示水平风格类型。SBS_LEFT_ALIGN表示左对齐增长方式，如果向左增长方式，往左移动滑块，数值就是增大，往右就减小。SBS_RIGHT_ALIGN表示右对齐增长方式。滚动条控件支持窗口风格参数。

至于其他的参数，也是同样的用法，这里不作描述。我们创建控件调用的CreateWindow函数，实际上就是CreateWindowEx函数

创建滚动条控件实验
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. _设计要求-7:

设计要求
^^^^^^^^^^^^

设计一个窗口，如 图12_4_ 所示。有三个滚动条，分别是垂直风格，自绘制外观风格、水平风格（从左往右，从上到下）。

.. image:: /media/docx052.jpg
   :align: center
   :alt: 图 12‑4 设计要求
   :name: 图12_4

.. _代码分析-7:

代码分析
^^^^^^^^^^^^

(1) 创建父窗口

.. code-block:: c
    :caption: 代码清单 12‑4 GUI_DEMO\_ Scrollbar函数（文件GUI_DEMO\_ Scrollbar.c）
    :linenos:
    :name: 代码清单12_4

     void GUI_DEMO_Scrollbar(void)
     {
        HWND hwnd;
        WNDCLASS wcex;
        MSG msg;
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
        _T("GUI Demo - Scrollbar"),
        /*WS_MEMSURFACE|*/WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,
        0,0,GUI_XSIZE,GUI_YSIZE,
        NULL,NULL,NULL,NULL);
        ShowWindow(hwnd,SW_SHOW);
        while(GetMessage(&msg,hwnd))
        {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        }
     }

创建父窗口，标题栏为“GUI Demo - Scrollbar”，带有大小边框，设置WinProc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

.. code-block:: c
    :caption: 代码清单 12‑5 WM_CREATE消息响应（文件GUI_DEMO\_ Scrollbar.c）
    :linenos:
    :name: 代码清单12_5

     case WM_CREATE:
     {
        GetClientRect(hwnd,&rc);
        if(1)
        {
        //滚动条参数结构体
        SCROLLINFO sif;
        sif.cbSize =sizeof(sif);//结构体大小
        sif.fMask =SIF_ALL; //使能所有功能

        //取值范围：-50~50
        sif.nMin =-50;
        sif.nMax =+50;
        //当前值为0
        sif.nValue =0;
        //滑块的大小为60
        sif.TrackSize =60;
        //两端的大小为60
        sif.ArrowSize =60;
        //创建垂直风格滑动条
        wnd = CreateWindow(SCROLLBAR,L"VScroll",SBS_VERT|WS_VISIBLE,
        40,20,40,400,hwnd,ID_SCROLLBAR1,NULL,NULL);
        //配置滑动条的属性
        SendMessage(wnd,SBM_SETSCROLLINFO,TRUE,(LPARAM)&sif);
        //创建自绘制滑动条
        wnd = CreateWindow(SCROLLBAR,L"HScroll",WS_OWNERDRAW|WS_VISIBLE,
        130,120,400,40,hwnd,ID_SCROLLBAR2,NULL,NULL);
        SendMessage(wnd,SBM_SETSCROLLINFO,TRUE,(LPARAM)&sif);
        //创建滑动条
        wnd = CreateWindow(SCROLLBAR,L"HScroll",WS_VISIBLE,
        130,240,400,40,hwnd,ID_SCROLLBAR3,NULL,NULL);
        SendMessage(wnd,SBM_SETSCROLLINFO,TRUE,(LPARAM)&sif);
        }
        return TRUE;
     }

设置滚动条的取值范围在-50~50，滑块的大小为60px，初始位置位于0处，箭头框的大小为60px。调用CreateWindow函数来创建滚动条。创建完成后，发送消息SBM_SETSCROLLINFO来设置滚动条的属性。这里创建了三个滚动条，分别是SCROLLBAR1、SCROLLBAR2和SCROLLBAR3。

2. WM_CTLCOLOR

.. code-block:: c
    :caption: 代码清单 12‑6 WM_CTLCOLOR消息响应（文件GUI_DEMO\_ Scrollbar.c）
    :linenos:
    :name: 代码清单12_6

     case WM_CTLCOLOR:
     {
        u16 id;
        id =LOWORD(wParam);
        if(id== ID_SCROLLBAR3)
        {
        CTLCOLOR *cr;
        cr =(CTLCOLOR*)lParam;
        cr->TextColor =RGB888(100,255,255);

        cr->BackColor =RGB888(100,100,150);
        cr->BorderColor =RGB888(50,50,150);
        cr->ForeColor =RGB888(50,150,250);
        return TRUE;
        }
        else
        {
        return FALSE;
        }
     }

在WM_CTLCOLOR中，对SCROLLBAR3滚动条的外观颜色进行更改，并返回TRUE。其余两个滚动条按照系统默认方案来配置。

3. WM_DRAWITEM

.. code-block:: c
    :caption: 代码清单 12‑7 WM_DRAWITEM消息响应（文件GUI_DEMO\_ Scrollbar.c）
    :linenos:
    :name: 代码清单12_7

     case WM_DRAWITEM:
     {
        DRAWITEM_HDR *ds;
        ds =(DRAWITEM_HDR*)lParam;
        {
            scrollbar_owner_draw(ds);
            return TRUE;
        }
     }

滚动条控件SCROLLBAR2拥有自定义绘制属性WS_OWNERDRAW，在绘制前都会给父窗口发送WM_DRAWITEM消息。在WM_DRAWITEM消息中，调用函数scrollbar_owner_draw实现控件自定义，最后返回TURE。

.. code-block:: c
    :caption: 代码清单 12‑8 scrollbar_owner_draw函数（文件GUI_DEMO\_ Scrollbar.c）
    :linenos:
    :name: 代码清单12_8

     static void scrollbar_owner_draw(DRAWITEM_HDR *ds)
     {
        HWND hwnd;
        HDC hdc;
        RECT rc;
        WCHAR wbuf[128];
        SCROLLINFO sif;
        hwnd =ds->hwnd;
        hdc =ds->hDC;

        //绘制滚动条的背景（第一步）
        SetBrushColor(hdc,MapRGB(hdc,150,200,250));
        FillRect(hdc,&ds->rc);
        sif.fMask =SIF_ALL;
        SendMessage(hwnd,SBM_GETSCROLLINFO,0,(LPARAM)&sif);
        //得到滑块的大小（第二步）
        SendMessage(hwnd,SBM_GETTRACKRECT,0,(LPARAM)&rc);
        //滑块被选中
        if(ds->State & SST_THUMBTRACK)
        {
            SetPenColor(hdc,MapRGB(hdc,250,50,50));
        }
        else//滑块未被选中
        {
            SetPenColor(hdc,MapRGB(hdc,50,50,50));
        }
        DrawRect(hdc,&rc);
        //显示滑块的位置
        x_wsprintf(wbuf,L"%d",sif.nValue);

        DrawText(hdc,wbuf,-1,&rc,DT_VCENTER|DT_CENTER);
     }

图12_4_ 的中滚动条SCROLLBAR2重绘，就是在窗口处绘制两个矩形，一个作为滚动条的背景，另一个则作为滑块。如 图12_5_ 所示。

.. image:: /media/docx053.jpg
   :align: center
   :alt: 图 12‑5滚动条重绘
   :name: 图12_5

滚动条的背景重绘，通过调用SetBrushColor函数设置背景颜色，同时使用FillRect函数绘制一个矩形，如 图12_5_ 的处。

滚动条的滑块重绘，滑块的大小，受到滚动条控件的影响，对于本例程，不可以超过控件的高度。
发送SBM_GETSCROLLINFO消息来获得滚动条的配置信息，在发送消息之前，需要将成员fMask的值设置为SIF_ALL，否则的话，获取的内容不完整。
通过发送SBM_GETTRACKRECT消息来获得滑块的大小，这里指的是创建滚动条时，配置的TrackSize参数，保存到rc中。
判断滑块当前的状态，设置滑块边框的颜色，调用DrawRect来绘制边框，同时将滑块的当前显示出来，得到 图12_5_ 的处。

由于 图12_5_ 的处是处进行绘制，受到滚动条控件的位置以及大小的影响，所以绘制完成后，就可以得到的滚动条。图12_5_ 拆开，只是为了方便读者理解。

这样窗口就设计完成了，将GUI_DEMO_Scrollbar函数加入到GUI_AppMain中，见 代码清单12_9_

.. code-block:: c
    :caption: 代码清单 12_9 GUI_AppMain函数（文件GUI_AppMain.c）
    :linenos:
    :name: 代码清单12_9

     void GUI_AppMain(void)
     {
        while(1)
        {
            GUI_DEMO_Button();//需要修改教程
            GUI_DEMO_Checkbox();
            GUI_DEMO_Radiobox();
            GUI_DEMO_Textbox();
            GUI_DEMO_Progressbar();//有瑕疵

            GUI_DEMO_Scrollbar();
        }
     }

实验结果
^^^^^^^^^^^^^^^^

实验结果如 图12_6_，单击SCROLLBAR1和SCROLLBAR2，会在串口输出单击的位置。当我们移动滑块SCROLLBAR2时，滑块的数字会发送改变，默认是右增长模式。

.. image:: /media/docx054.jpg
   :align: center
   :alt: 图 12‑6 实验结果
   :name: 图12_6

图 12‑6 实验结果
