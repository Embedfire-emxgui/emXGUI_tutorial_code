.. vim: syntax=rst

复选框控件
----------

前面我们已经讲过按钮控件，下面我们开始学习 图7_1_ 处的复选框控件。

.. image:: /media/docx024.jpg
   :align: center
   :alt: 图 7‑1 各种按钮
   :name: 图7_1

复选框是一种可同时选中多项的基础控件。假设我们现在做一个电子调查问卷，了解大家的爱好，有些人的爱好很广泛，如唱歌，骑车，旅游，美食等等，我们就可以使用复选框来完成。

创建复选框控件
~~~~~~~~~~~~~~~~~~~~~

.. _标准消息类型及参数说明-2:

标准消息类型及参数说明
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

复选框也是按钮控件的一种，使用的消息和处理方式也都大同小异。有什么不懂的地方，可以参考上一章的标准消息类型及参数说明。

创建复选框控件函数
^^^^^^^^^^^^^^^^^^^^^^^^^^^

复选框属于子控件（子窗口），可以通过调用CreateWindow函数来创建。实际上，无论什么控件，都是调用CreateWindow函数来创建的，下面重点讲解一下差异之处。

.. code-block:: c
    :caption: 代码清单 7‑1 创建窗口函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单7_1

<<<<<<< HEAD
     HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,
     U32 dwStyle, int x, int y, int nWidth, int nHeight,
     HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);
=======
    HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,
            U32 dwStyle, int x, int y, int nWidth, int nHeight,
            HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam); 
>>>>>>> dev

1) lpClass：复选框属于按钮控件中的一类，这里应该选择BUTTON类。

2) lpWindowName：复选框项目的名称，可以是中文。注意，这里也是使用的宽字符串，一个字符占两个字节。

3) dwStyle：复选框的风格。参数BS_CHECKBOX代表该控件为复选框。当使用复选框这个控件时，这个参数是必须的，否则就和普通按钮一样了。还可以使用按钮控件的风格（BS_NOTIFY），只有控件拥有该属性，才可以接收到控件被按下（未松手）的消息。以及窗口风格。

..

   至于其他的参数，和创建按钮一样，也是同样的用法，这里不作描述。

创建复选框控件实验
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. _设计要求-2:

设计要求
^^^^^^^^^^^^

图7_2_ 是excel设计的复选框界面的内容，比较简单，容易理解。下面通过代码讲解如何实现这个界面。

.. image:: /media/docx032.jpg
   :align: center
   :alt: 图 7‑2 复选框界面
   :name: 图7_2

.. _代码设计-2:

代码设计
^^^^^^^^^^^^

.. _编程要点-2:

编程要点
''''''''''''

1) 配置WNDCLASS窗口结构体，调用CreateWindowEx创建父窗口；

2) 实现消息循环

3) 编写窗口回调函数，完成对消息的处理。

.. _代码分析-2:

代码分析
''''''''''''

(1) 创建父窗口代码分析

.. code-block:: c
    :caption: 代码清单 7‑2 创建父窗口（文件GUI_DEMO_Checkbox.c）
    :linenos:
    :name: 代码清单7_2

<<<<<<< HEAD
     void GUI_DEMO_Checkbox(void)
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
     _T("GUI Demo - Checkbox"),
     WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,
     0,0,GUI_XSIZE,GUI_YSIZE,
     NULL,NULL,NULL,NULL);

     ShowWindow(hwnd,SW_SHOW);
     while(GetMessage(&msg,hwnd))
     {
     TranslateMessage(&msg);
     DispatchMessage(&msg);
     }
     }
=======
    void  GUI_DEMO_Checkbox(void)
    {
        HWND  hwnd;
        WNDCLASS  wcex;
        MSG msg;
    
        wcex.Tag        = WNDCLASS_TAG;
        wcex.Style      = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc  = win_proc;
        wcex.cbClsExtra   = 0;
        wcex.cbWndExtra   = 0;
        wcex.hInstance    = 0;//hInst;
        wcex.hIcon      = 0;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);
        wcex.hCursor    = 0;//LoadCursor(NULL, IDC_ARROW);
        
        hwnd  =CreateWindowEx(  NULL,
                    &wcex,
                    _T("GUI Demo - Checkbox"),
                    WS_CAPTION| WS_DLGFRAME| WS_BORDER|WS_CLIPCHILDREN,
                    0,0,GUI_XSIZE,GUI_YSIZE,
                    NULL,NULL,NULL,NULL);
        
        ShowWindow(hwnd,SW_SHOW); 
        while(GetMessage(&msg,hwnd))
        {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        }
    }
>>>>>>> dev

每一个控件都是在父窗口上显示，调用CreateWindowEx创建父窗口，设置win_proc作为窗口回调函数，详细解释可以参考，按钮控件章节的代码分析。

(2) 窗口回调函数

.. code-block:: c
    :caption: 代码清单 7‑3 窗口回调函数win_proc（文件GUI_DEMO_Checkbox.c）
    :linenos:
    :name: 代码清单7_3

<<<<<<< HEAD
     static LRESULT win_proc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
     {
     // HDC hdc;
     // PAINTSTRUCT ps;
     RECT rc;
     // WCHAR wbuf[128];
     //int i,x,y;
     // HWND wnd;

     switch(msg)
     {
     case WM_CREATE:
     GetClientRect(hwnd,&rc);
     //创建按钮(EXIT)
     CreateWindow(BUTTON,L"EXIT",WS_VISIBLE,
     rc.w-100,8,80,48,hwnd,ID_EXIT,NULL,NULL);
     rc.x =20;
     rc.y =40;
     rc.w =128;
     rc.h =30;
     //创建复选框Checkbox1（BS_CHECKBOX）
     CreateWindow(BUTTON,L"Checkbox1",BS_CHECKBOX|WS_VISIBLE,
     rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB1,NULL,NULL);
     //往下移动矩形位置(X轴不变,Y轴位置增加rc.h+10个像素)
     OffsetRect(&rc,0,rc.h+10);
     //创建复选框Checkbox2（BS_CHECKBOX）
     CreateWindow(BUTTON,L"Checkbox2",BS_CHECKBOX|WS_VISIBLE,
     rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB2,NULL,NULL);
     OffsetRect(&rc,0,rc.h+10);
     //创建复选框Checkbox3--不响应输入设备（WS_DISABLED）
     CreateWindow(BUTTON,L"Checkbox3",WS_DISABLED|BS_CHECKBOX|WS_VISIBLE,
     rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB3,NULL,NULL);
     OffsetRect(&rc,0,rc.h+10);
     //创建复选框Checkbox4--类似按钮，当被按下时，该按钮下沉（BS_PUSHLIKE）
     CreateWindow(BUTTON,L"Checkbox4",BS_PUSHLIKE|BS_CHECKBOX|WS_VISIBLE,
     rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB4,NULL,NULL);
     rc.x =160;
     rc.y =40;
     rc.w =128;
     rc.h =30;
     //创建复选框Checkbox5--检测BN_CHECKED消息（BS_NOTIFY）
     CreateWindow(BUTTON,L"Checkbox5",BS_NOTIFY|BS_CHECKBOX|WS_VISIBLE,
     rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB5,NULL,NULL);
     return TRUE;
     case WM_NOTIFY: //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,高16位为通知码;
     lParam指向了一个NMHDR结构体.
     {
     u16 code,id;
     NMHDR *nr=(NMHDR*)lParam;
     id =LOWORD(wParam);
     code=HIWORD(wParam);
     if(id >= ID_CB1 && id<= ID_CB5)
     {
     if(code == BN_CLICKED) //被点击了
     {
     if(SendMessage(nr->hwndFrom,BM_GETSTATE,0,0)&BST_CHECKED) //获取当前状态
     { //复选框选中.
     GUI_Printf("Checkbox Checked: ID:%04XH\r\n",id);
     }
     else
     {//复选未框选中.
     GUI_Printf("Checkbox Unchecked: ID:%04XH\r\n",id);
     }
     }

     if(code == BN_CHECKED) //指定了BS_NOTIFY,才会产生该消息.
     { //复选框被选中.
     GUI_Printf("Checkbox Checked: ID:%04XH\r\n",id);
     }

     }
     if(id == ID_EXIT && code == BN_CLICKED)
     {
     PostCloseMessage(hwnd); //产生WM_CLOSE消息关闭主窗口
     }

     }
     break;
     case WM_CTLCOLOR:
     {
     u16 id;

     id =LOWORD(wParam);

     if(id== ID_CB5)
     {
     CTLCOLOR *cr;
     cr =(CTLCOLOR*)lParam;

     if(SendMessage(GetDlgItem(hwnd,id),BM_GETSTATE,0,0)&BST_CHECKED)
     {
     //设置文字颜色
     cr->TextColor =RGB888(250,0,0);
     //设置背景颜色
     cr->BackColor =RGB888(220,200,200);
     //设置边框颜色
     cr->BorderColor =RGB888(30,30,230);
     //设置前景颜色
     cr->ForeColor =RGB888(100,250,100);

     }
     else
     {
     cr->TextColor =RGB888(10,150,10);
     cr->BackColor =RGB888(200,220,200);
     cr->BorderColor =RGB888(50,50,50);
     cr->ForeColor =RGB888(180,200,230);
     }
     return TRUE;
     }
     else
     {
     return FALSE;
     }

     }
     default:
     return DefWindowProc(hwnd,msg,wParam,lParam);
     }

     return WM_NULL;
     }
=======
    static  LRESULT win_proc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
    {
    //  HDC hdc;
    //  PAINTSTRUCT ps;
    RECT rc;
    //  WCHAR wbuf[128];
    //int i,x,y;
    //  HWND wnd;

    switch(msg)
    {
        case  WM_CREATE:
            GetClientRect(hwnd,&rc);    
                //创建按钮(EXIT)
            CreateWindow(BUTTON,L"EXIT",WS_VISIBLE,
                            rc.w-100,8,80,48,hwnd,ID_EXIT,NULL,NULL);
            rc.x =20;
            rc.y =40;
            rc.w =128;
            rc.h =30;
                //创建复选框Checkbox1（BS_CHECKBOX）
            CreateWindow(BUTTON,L"Checkbox1",BS_CHECKBOX|WS_VISIBLE,
                            rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB1,NULL,NULL);
                //往下移动矩形位置(X轴不变,Y轴位置增加rc.h+10个像素)
            OffsetRect(&rc,0,rc.h+10);
                //创建复选框Checkbox2（BS_CHECKBOX）
            CreateWindow(BUTTON,L"Checkbox2",BS_CHECKBOX|WS_VISIBLE,
                            rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB2,NULL,NULL);
            OffsetRect(&rc,0,rc.h+10);
                //创建复选框Checkbox3--不响应输入设备（WS_DISABLED）
            CreateWindow(BUTTON,L"Checkbox3",WS_DISABLED|BS_CHECKBOX|WS_VISIBLE,
                            rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB3,NULL,NULL);
            OffsetRect(&rc,0,rc.h+10);
                //创建复选框Checkbox4--类似按钮，当被按下时，该按钮下沉（BS_PUSHLIKE）
            CreateWindow(BUTTON,L"Checkbox4",BS_PUSHLIKE|BS_CHECKBOX|WS_VISIBLE,
                            rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB4,NULL,NULL);
            rc.x =160;
            rc.y =40;
            rc.w =128;
            rc.h =30;
                //创建复选框Checkbox5--检测BN_CHECKED消息（BS_NOTIFY）
            CreateWindow(BUTTON,L"Checkbox5",BS_NOTIFY|BS_CHECKBOX|WS_VISIBLE,
                            rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB5,NULL,NULL);
            return TRUE;
        case  WM_NOTIFY: //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,高16位为通知码;
                            lParam指向了一个NMHDR结构体.
        {
        u16 code,id;
        NMHDR *nr=(NMHDR*)lParam;
        id  =LOWORD(wParam);
        code=HIWORD(wParam);
        if(id >= ID_CB1 && id<= ID_CB5)
        {
            if(code == BN_CLICKED) //被点击了
            {
            if(SendMessage(nr->hwndFrom,BM_GETSTATE,0,0)&BST_CHECKED) //获取当前状态
            { //复选框选中.
                GUI_Printf("Checkbox Checked: ID:%04XH\r\n",id);
            }
            else
            {//复选未框选中.
                GUI_Printf("Checkbox Unchecked: ID:%04XH\r\n",id);
            }
            }
    
            if(code == BN_CHECKED) //指定了BS_NOTIFY,才会产生该消息.
            { //复选框被选中.
            GUI_Printf("Checkbox Checked: ID:%04XH\r\n",id);
            }
    
        }
            if(id == ID_EXIT && code == BN_CLICKED)
            {
                    PostCloseMessage(hwnd); //产生WM_CLOSE消息关闭主窗口
            }
    
        }
        break;
        case  WM_CTLCOLOR:
        {
        u16 id;
    
        id =LOWORD(wParam);
    
        if(id== ID_CB5)
        {
            CTLCOLOR *cr;
            cr =(CTLCOLOR*)lParam;
    
            if(SendMessage(GetDlgItem(hwnd,id),BM_GETSTATE,0,0)&BST_CHECKED)
                {
                    //设置文字颜色
            cr->TextColor =RGB888(250,0,0);
                //设置背景颜色
            cr->BackColor =RGB888(220,200,200);
                //设置边框颜色
            cr->BorderColor =RGB888(30,30,230);
                //设置前景颜色
            cr->ForeColor =RGB888(100,250,100);
            }
            else
            {
            cr->TextColor =RGB888(10,150,10);
            cr->BackColor =RGB888(200,220,200);
            cr->BorderColor =RGB888(50,50,50);
            cr->ForeColor =RGB888(180,200,230);
                }
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    
        }
        default:
            return  DefWindowProc(hwnd,msg,wParam,lParam);
    }
    return  WM_NULL;
    }
>>>>>>> dev

1. WM_CREATE

在WM_CREATE消息创建控件，如 表格7_1_ 所示。

表格 7_1 控件的具体信息

.. _表格7_1:

======== ========= ======= ==================================
控件类型 名称      ID值    风格
======== ========= ======= ==================================
BUTTON   EXIT      ID_EXIT WS_VISIBLE
\        Checkbox1 ID_CB1  BS_CHECKBOX|WS_VISIBLE
\        Checkbox2 ID_CB2  BS_CHECKBOX|WS_VISIBLE
\        Checkbox3 ID_CB3  WS_DISABLED|BS_CHECKBOX|WS_VISIBLE
\        Checkbox4 ID_CB4  BS_PUSHLIKE|BS_CHECKBOX|WS_VISIBLE
\        Checkbox5 ID_CB5  BS_NOTIFY|BS_CHECKBOX|WS_VISIBLE
======== ========= ======= ==================================

每一个复选框各自的ID号。复选框的风格可以使用窗口类和按钮的风格，但是都必须要有BS_CHECKBOX的属性值 。调用OffsetRect函数来移动控件的位置：X轴不变，Y轴位置增加rc.h+10个像素。

2. WM_NOTIFY

WM_NOTIFY消息用来处理控件的动作响应，该消息的参数wParam低16位为发送该消息的控件ID，高16位为通知码，即控件的动作。可以利用LOWORD函数和HIWORD函数来读取控件的ID和通知码。根据通知码，来实现控件的动作响应。代码清单7_3_ 中，调用SendMessage给复选框控件发送消息BM_GETSTATE，实现检测复选框是否被选中。并输出到串口助手。

既然已经知道控件被点击了，为什么还要发送消息，去获取控件的当前状态呢？可能会有人有这个疑问。举个例子，电源开关。你拨了一下，你怎么知道电路有没有电？是不是要看电源指示灯亮不亮。亮了，说明开关是由断开到闭合。灭了，说明开关是由闭合到断开。这里也是一样的道理：你点击控件，至于控件是由选中到未选中，还是由
未选中到选中，就是通过发送消息BM_GETSTATE来检测的。

注意，只有拥有BS_NOTIFY的控件，才可以发送BN_CHECKED的消息，用于检测控件是否被按下（未松开）。

按钮控件EXIT，是用来关闭父窗口的。单击时，会发送关闭消息。

3. WM_CTLCOLOR

控件在绘制前，会向其父窗口发送WM_CTLCOLOR消息，该消息的参数wParm低16位产生该消息的窗口ID。参数lParam指向一个CTLCOLOR的结构体指针地址。代码清单7_4_ 。

.. code-block:: c
    :caption: 代码清单 7‑4 CTLCOLOR的结构体（文件emXGUI.h）
    :linenos:
    :name: 代码清单7_4

<<<<<<< HEAD
     typedef struct
     {
     COLOR_RGB32 TextColor; //文字颜色
     COLOR_RGB32 BorderColor; //边框颜色。
     COLOR_RGB32 BackColor; //背景颜色。
     COLOR_RGB32 ForeColor; //前景颜色。
     }CTLCOLOR;
=======
    typedef struct
    {
        COLOR_RGB32 TextColor;    //文字颜色
        COLOR_RGB32 BorderColor;  //边框颜色。
        COLOR_RGB32 BackColor;    //背景颜色。
        COLOR_RGB32 ForeColor;    //前景颜色。
    }CTLCOLOR;  
>>>>>>> dev

在 代码清单7_3_ 中，调用GetDlgItem来获取父窗口中CheckBox5的句柄，向CheckBox5发送消息BM_GETSTATE，来获取CheckBox5的状态值。GetDlgItem的用法，可以查阅《emXGUI API编程手册》的窗口/消息系统API。

根据控件的状态值，设置控件窗口的文字颜色(TextColor)，边框颜色(BorderColor)，
背景颜色(BackColor)，前景颜色(ForeColor)，改变控件窗口的外观颜色。一定要返回TRUE，否则的话，则按照默认方案来配置。前景颜色指的是选中后，CheckBox框框，也就是平时打钩的地方，显示的颜色。

4. default—用户不关心的消息

调用DefWindowProc来处理。

为什么没有重绘消息呢？是窗口不用重绘吗？答案是肯定的，不是说任何窗口在移动和创建的过程中，都需要进行重绘吗。这是没有错的，不过因为在图 7‑2我们并没有在客户区显示内容，而控件的重绘是由emXGUI内部完成的，因此，这里没有WM_PAINT也是可以的。

最后，将函数GUI_DEMO_Checkbox加入到GUI_AppMain函数中。

.. code-block:: c
    :caption: 代码清单 7_5 GUI_AppMain函数（文件GUI_AppMain.c）
    :linenos:
    :name: 代码清单7_5

<<<<<<< HEAD
     void GUI_AppMain(void)
     {
     while(1)
     {
     GUI_DEMO_Button();
     GUI_DEMO_Checkbox();
     }
     }
=======
    void GUI_AppMain(void)
    {
        while(1)
        {
            GUI_DEMO_Button();
            GUI_DEMO_Checkbox();
        }
    }
>>>>>>> dev

.. _实验现象-2:

实验现象
^^^^^^^^^^^^

实验结果如 图7_3_ 和 图7_4_。图7_3_ 是界面的初始化状态，图7_4_ 是界面的CheckBox被选中状态。当CheckBox4被选中时，CheckBox4会像按钮一样下沉。CheckBox5在选中状态下的文字，边框， 背景和前景的颜色发生了改变。

.. image:: /media/docx033.jpg
   :align: center
   :alt: 图 7‑3 实验结果
   :name: 图7_3

图 7‑3 实验结果

.. image:: /media/docx034.jpg
   :align: center
   :alt: 图 7‑4 实验结果（选中状态）
   :name: 图7_4

图 7‑4 实验结果（选中状态）
