.. vim: syntax=rst

文本框控件
---------------

文本框控件在我们生活中，并不少见。如 图9_1_，这是一个登录界面。我们输入账号和密码处，其实就是文本框控件。emXGUI也提供这样的功能，需要用户外加键盘作为输入设备。

.. image:: /media/docx038.jpg
   :align: center
   :alt: 图 9‑1 常见的文本框控件
   :name: 图9_1

图 9_1 常见的文本框控件

创建文本框控件
~~~~~~~~~~~~~~~~~~~~~

.. _标准消息类型及参数说明-4:

标准消息类型及参数说明
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

本章只是大致上讲解如何创建文本框控件，修稿控件的外观颜色，是禁止用户输入的。键盘输入，Emmmmm…

本章使用的消息类型，有WM_CREATE、WM_TIMER、WM_NOTIFY和WM_CTLCOLOR。WM_CREATE消息用于创建控件；这里使用WM_TIMER，主要是给大家演示一下， 如何在文本框显示变量。WM_NOTIFY消息用来处理
EXIT按钮消息。使用WM_CTLCOLOR消息来改变控件的外观颜色。

创建文本框控件函数
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c
    :caption: 代码清单 9‑1 创建窗口函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单9_1

    HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,
            U32 dwStyle, int x, int y, int nWidth, int nHeight,
            HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam); 

1) lpClass：窗口类。对于系统标准控件，可以为：BUTTON(常规按钮，复选框，单选框，组合框)，SCROLLBAR(水平/垂直滚动条)， LISTBOX(列表框)。TEXTBOX（文本框）…等等。这里选择PROGRESSBAR。

2) dwStyle：文本框的风格。参数TBS_SUNK表示该控件具有凹下边框样式。文本框控件支持窗口风格参数。

至于其他的参数，也是同样的用法，这里不作描述。我们创建控件调用的CreateWindow函数，实际上就是CreateWindowEx函数。

创建文本框控件实验
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. _设计要求-4:

设计要求
^^^^^^^^^^^^^^^^

图9_2_ ，是本章节的设计要求。左边这一列文本框显示的文本内容格式不同。右边的文本框第一个是显示变量，变量值实时更新。后两个是多行显示。下面看看，如何用代码实现该界面。

.. image:: /media/docx039.jpg
   :align: center
   :alt: 图 9‑2 设计要求
   :name: 图9_2

图 9-2 设计要求

.. _代码分析-4:

代码分析
^^^^^^^^^^^^

(1) 创建父窗口

.. code-block:: c
    :caption: 代码清单 9_2 GUI_DEMO_Textbox函数（文件GUI_DEMO_Textbox.c）
    :linenos:
    :name: 代码清单9_2

    void  GUI_DEMO_Textbox(void)
    {
        HWND  hwnd;
        WNDCLASS  wcex;
        MSG msg;
        //配置wcex参数
        wcex.Tag        = WNDCLASS_TAG;
        wcex.Style      = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc  = win_proc;
        wcex.cbClsExtra   = 0;
        wcex.cbWndExtra   = 0;
        wcex.hInstance    = NULL;//hInst;
        wcex.hIcon  =  NULL;//LoadIcon(hInstance,(LPCTSTR)IDI_WIN32_APP_TEST); 
        wcex.hCursor    = NULL;//LoadCursor(NULL, IDC_ARROW);
        //创建主窗口
        hwnd  =CreateWindowEx(  NULL,
                    &wcex,
                    L"GUI Demo - Textbox",
                    WS_CAPTION| WS_DLGFRAME| WS_BORDER|WS_CLIPCHILDREN,
                    0,0,GUI_XSIZE,GUI_YSIZE,
                    NULL,NULL,NULL,NULL);   
        //显示主窗口
        ShowWindow(hwnd,SW_SHOW); 
        //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)
        while(GetMessage(&msg,hwnd))
        {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        }
    }

创建父窗口，标题栏为“GUI Demo - Textbox”，带有大小边框，设置win_proc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

.. code-block:: c
    :caption: 代码清单 9‑3 WM_CREATE消息响应（文件GUI_DEMO_Textbox.c）
    :linenos:
    :name: 代码清单9_3

    case  WM_CREATE:
    {
        GetClientRect(hwnd,&rc);
        
        CreateWindow(BUTTON,L"EXIT",WS_VISIBLE,rc.w-100,8,80,48,hwnd,ID_EXIT,NULL,NULL);
        rc.x =20;
        rc.y =30;
        rc.w =200;
        rc.h =80;
        //创建文本框控件，返回控件句柄wnd
        wnd=CreateWindow(TEXTBOX,L"Text1",WS_VISIBLE,
                rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB1,NULL,NULL);
        //发送TBM_SET_TEXTFLAG，设置文本框的内容，lParam参数代表显示内容的格式
        SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_SINGLELINE| DT_LEFT| DT_VCENTER| DT_BKGND|DT_BORDER);
        //往下移动矩形位置(X轴不变,Y轴位置增加rc.h+10个像素)
        OffsetRect(&rc,0,rc.h+10);
        //创建文本框控件(可见，具有凹下边框样式)，返回控件句柄wnd
        wnd=CreateWindow(TEXTBOX,L"Text2",TBS_SUNK|WS_VISIBLE,
                rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB2,NULL,NULL);
        SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_SINGLELINE| DT_CENTER| DT_VCENTER|DT_BKGND);
    
        OffsetRect(&rc,0,rc.h+10);
        wnd=CreateWindow(TEXTBOX,L"Text3",WS_VISIBLE,
                rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB3,NULL,NULL);
        SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_SINGLELINE| DT_RIGHT| DT_VCENTER| DT_BKGND|DT_BORDER);
    
        OffsetRect(&rc,0,rc.h+10);
        wnd=CreateWindow(TEXTBOX,L"Text4",WS_DISABLED|WS_VISIBLE,
                rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB4,NULL,NULL);
        SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_SINGLELINE| DT_VCENTER| DT_BOTTOM| DT_BKGND|DT_BORDER);
    
        rc.x =250;
        rc.y =30;
        rc.w =200;
        rc.h =80;
        wnd=CreateWindow(TEXTBOX,L"Text5",WS_VISIBLE,
            rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB5,NULL,NULL);
        SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_SINGLELINE| DT_CENTER| DT_VCENTER|DT_BKGND);
        OffsetRect(&rc,0,rc.h+10);
        rc.w =320;
        rc.h =140;
        //创建文本框控件Text6，返回控件句柄wnd
        wnd=CreateWindow(TEXTBOX,L"Text6\r\nMulti-Line\r\nVCENTER+CENTER",WS_VISIBLE,
                rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB6,NULL,NULL);
        //发送TBM_SET_TEXTFLAG，设置文本框的内容，多行显示
        SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_VCENTER| DT_CENTER| DT_BKGND|DT_BORDER);
    
        OffsetRect(&rc,0,rc.h+10);
    
        wnd=CreateWindow(TEXTBOX,L"Text7\r\nMulti-Line\r\nBOTTOM+RIGHT",TBS_SUNK|WS_VISIBLE,
                rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB7,NULL,NULL);
        SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_BOTTOM| DT_RIGHT| DT_BKGND|DT_BORDER);
    
        SetTimer(hwnd,ID_TMR1,200,TMR_START,NULL); //创建一个200ms定时器
        return TRUE;
    }

WM_CREATE消息创建的控件，如 表格9_1_ 所示。

表格 9_1 控件的具体信息

.. _表格9_1:

======== ====== ======== ============================================ ============================================================================================================
控件类型   名称     ID值     窗口风格                                                            文本格式
======== ====== ======== ============================================ ============================================================================================================
BUTTON   EXIT   ID_EXIT     WS_VISIBLE                                              无
TEXTBOX  Text1  ID_TB1      WS_VISIBLE                                  DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_BKGND|DT_BORDER
\        Text2  ID_TB2      TBS_SUNK|WS_VISIBLE                         DT_SINGLELINE|DT_CENTER\|DT_VCENTER|DT_BKGND 
\        Text3  ID_TB3      WS_VISIBLE                                  DT_SINGLELINE|DT_RIGHT|DT_VCENTER\|DT_BKGND|DT_BORDER 
\        Text4  ID_TB4      WS_DISABLED|WS_VISIBLE                      DT_SINGLELINE|DT_VCENTER|DT_BOTTOM\|DT_BKGND|DT_BORDER 
\        Text5  ID_TB5      WS_VISIBLE                                  DT_SINGLELINE|DT_CENTER\|DT_VCENTER|DT_BKGND 
\        Text6  ID_TB6      WS_VISIBLE                                  DT_VCENTER|DT_CENTER\|DT_BKGND|DT_BORDER
\        Text7  ID_TB7      TBS_SUNK|WS_VISIBLE                         DT_BOTTOM|DT_RIGHT\|DT_BKGND|DT_BORDER 
======== ====== ======== ============================================ ============================================================================================================

点击EXIT按钮，产生WM_CLOSE消息关闭主窗口。调用CreateWindow函数，创建7个文本框，文本框的文本格式，见 表格9_2_。

.. _表格9_2:

表格 9_2 文本框的文本格式说明

============= ==================================
属性值        文本格式
============= ==================================
DT_SINGLELINE 单行模式。没有该参数时，为多行模式
DT_CENTER     水平居中对齐
DT_LEFT       水平居左对齐
DT_RIGHT      水平居右对齐
DT_BOTTOM     垂直底部对齐
DT_VCENTER    垂直中间对齐
DT_BORDER     是否绘制边框
DT_BKGND      是否绘制背景
============= ==================================

2. WM_NOTIFY


.. code-block:: c
    :caption: 代码清单 9‑4 WM_NOTIFY消息响应（文件GUI_DEMO_Textbox.c）
    :linenos:
    :name: 代码清单9_4

    case WM_NOTIFY:
    {
        u16 id, code;
        id =LOWORD(wParam);        
        code = HIWORD(wParam);
        //EXIT按钮弹起
        if(id == ID_EXIT && code == BN_CLICKED)
        {
            count = 0;
            PostCloseMessage(hwnd);//产生WM_CLOSE消息关闭主窗口
        }
    }

ID_EXIT单击时，会调用PostCloseMessage发送窗口关闭消息WM_CLOSE，来关闭主窗口。

3. WM_TIMER

.. code-block:: c
    :caption: 代码清单 9‑5 WM_TIMER消息响应（文件GUI_DEMO_Textbox.c）
    :linenos:
    :name: 代码清单9_5

    case  WM_TIMER:
    {
        u16 id;
        //读取控件ID值
        id =LOWORD(wParam);
        
        if(id==ID_TMR1)
        {
            count++;
        
            x_wsprintf(wbuf,L"%04d",count);
        //获取控件句柄
            wnd =GetDlgItem(hwnd,ID_TB5);
        //设置控件显示文本框
            SetWindowText(wnd,wbuf);
        }
    }
    return TRUE;

WM_CREATE消息中，创建了ID为ID_TMR1的定时器。定时器到达设定值时，发送WM_TIMER消息。在WM_TIMER消息中，实现count变量自加，同时调用SetWindowText函数将变量值在文本框Text5显示。

4. WM_CTLCOLOR

.. code-block:: c
    :caption: 代码清单 9‑6 WM_CTLCOLOR消息响应（文件GUI_DEMO_Textbox.c）
    :linenos:
    :name: 代码清单9_6

    case  WM_CTLCOLOR:
    {
        /* 控件在绘制前，会发送 WM_CTLCOLOR到父窗口.
            * wParam参数指明了发送该消息的控件ID;lParam参数指向一个CTLCOLOR的结构体指针.
            * 用户可以通过这个结构体改变控件的颜色值.
            用户修改颜色参数后，需返回TRUE，否则，系统
            * 将忽略本次操作，继续使用默认的颜色进行绘制.
            *
            */
        u16 id;
        id =LOWORD(wParam);
        if(id== ID_TB5 || id== ID_TB6)
        {
            CTLCOLOR *cr;
            cr =(CTLCOLOR*)lParam;
            cr->TextColor =RGB888(255,180,180);//文字颜色（RGB888颜色格式)
            cr->BackColor =RGB888(100,0,0);//背景颜色（RGB888颜色格式)
            cr->BorderColor =RGB888(255,10,10);//边框颜色（RGB888颜色格式)
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

改变控件窗口的文字颜色(TextColor)，边框颜色(BorderColor)， 背景颜色(BackColor)，一定要返回TRUE，否则的话，则按照默认方案来配置。

最后，将GUI_DEMO_Textbox加入到GUI_AppMain中，见 代码清单9_7_。

.. code-block:: c
    :caption: 代码清单9_7_ GUI_AppMain函数（文件GUI_AppMain.c）
    :linenos:
    :name: 代码清单9_7

    void GUI_AppMain(void)
    {
        while(1)
        {   
            GUI_DEMO_Button();
            GUI_DEMO_Checkbox();
            GUI_DEMO_Radiobox();
            GUI_DEMO_Textbox();
        }
    }

.. _实验现象-4:

实验现象
^^^^^^^^^^^^

如 图9_3_ 除了控件的尺寸有些变化，布局和 图9_2_ 差不多是一模一样的。

.. image:: /media/docx040.jpg
   :align: center
   :alt: 图 9_3 实验结果
   :name: 图9_3

图 9‑3 实验结果
