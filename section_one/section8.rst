.. vim: syntax=rst

单选按钮控件
------------------

最后，我们学习 图7_1_ 处的单选按钮控件。顾名思义，单选按钮，就是只可以选择一个选项。例如串口收发的停止位，只可以是1、1.5、2位中的某一个值。

.. image:: /media/docx024.jpg
   :align: center
   :alt: 图 8‑1 各种按钮
   :name: 图8_1

创建单选按钮控件
~~~~~~~~~~~~~~~~~~~~~~~~

.. _标准消息类型及参数说明-3:

标准消息类型及参数说明
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

单选按钮需要用到的消息和处理方式，也没有什么变化。有什么不懂的地方，可以参考按钮控件章节的标准消息类型及参数说明。

创建单选按钮控件函数
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c
    :caption: 代码清单 8‑1 创建窗口函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单8_1

    HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,
            U32 dwStyle, int x, int y, int nWidth, int nHeight,
            HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam); 

1) lpClass：单选按钮属于按钮控件中的一类，这里选择BUTTON类。

2) dwStyle：单选按钮的风格。参数BS_RADIOBOX代表该控件为单选按钮。当使用单选按钮时，这个参数是必须的。单选按钮控件也支持窗口以及按钮的风格参数。

3) WinId：控件的ID值。单选按钮控件的ID值高16位为GroupID号，只有在同一组内的单选按钮，才会有“多选一"的效果。

至于其他的参数，和创建按钮一样，也是同样的用法，这里不作描述。

创建单选按钮控件实验
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. _设计要求-3:

设计要求
^^^^^^^^^^^^

图8_2_ 只是简单地展示了单选按钮控件，下面通过代码讲解如何实现这个界面。

.. image:: /media/docx035.jpg
   :align: center
   :alt: 图8_2 设计要求
   :name: 图8_2

.. _代码分析-3:

代码分析
^^^^^^^^^^^^

(1) 创建父窗口

.. code-block:: c
    :caption: 代码清单 8‑2 GUI_DEMO_Radiobox函数（文件GUI_DEMO_Radiobox.c）
    :linenos:
    :name: 代码清单8_2

    void  GUI_DEMO_Radiobox(void)
    {
        HWND  hwnd;
        WNDCLASS  wcex;
        MSG msg;
        /////
        wcex.Tag        = WNDCLASS_TAG;
        wcex.Style      = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc  = win_proc;
        wcex.cbClsExtra   = 0;
        wcex.cbWndExtra   = 0;
        wcex.hInstance    = 0;//hInst;
        wcex.hIcon      = 0;//LoadIcon(hInstance,(LPCTSTR)IDI_WIN32_APP_TEST);
        wcex.hCursor    = 0;//LoadCursor(NULL, IDC_ARROW);
        
        hwnd  =CreateWindowEx(  NULL,
                    &wcex,
                    _T("GUI Demo - Radiobox"),
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

创建父窗口，标题栏为“GUI Demo - Radiobox”，带有大小边框，设置win_proc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE消息

.. code-block:: c
    :caption: 代码清单 8‑3 WM_CREATE消息响应（文件GUI_DEMO_Radiobox.c）
    :linenos:
    :name: 代码清单8_3

    case  WM_CREATE:
    {
    //获得客户区的大小
    GetClientRect(hwnd,&rc);
    
        CreateWindow(BUTTON,L"EXIT",WS_VISIBLE,rc.w-100,8,80,48,hwnd,ID_EXIT,NULL,NULL);
    
    //创建第1组单选按钮(窗口ID的高16位为GroupID号，只有在同一组内的单选按钮，才会有"多选一"的效果)
                                    
        rc.x =20;
        rc.y =30;
        rc.w =120;
        rc.h =32;
        CreateWindow(BUTTON,L"Radiobox1",BS_RADIOBOX|WS_VISIBLE,
            rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|ID_RB1,NULL,NULL);
        OffsetRect(&rc,0,rc.h+10);
        CreateWindow(BUTTON,L"Radiobox2",WS_DISABLED|BS_RADIOBOX|WS_VISIBLE,
            rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|ID_RB2,NULL,NULL);
    
        //创建第2组单选按钮(GroupID号为2,使用常规按钮风格(BS_PUSHLIKE)).
        OffsetRect(&rc,0,rc.h+10);
        CreateWindow(BUTTON,L"Radiobox3",BS_RADIOBOX|BS_PUSHLIKE|WS_VISIBLE,
            rc.x,rc.y,rc.w,rc.h,hwnd,(2<<16)|ID_RB3,NULL,NULL);
        OffsetRect(&rc,0,rc.h+10);
        CreateWindow(BUTTON,L"Radiobox4",BS_RADIOBOX|BS_PUSHLIKE|WS_VISIBLE,
            rc.x,rc.y,rc.w,rc.h,hwnd,(2<<16)|ID_RB4,NULL,NULL);
    
        //创建第3组单选按钮(GroupID号为3).
        rc.x =160;
        rc.y =30;
        rc.w =120;
        rc.h =32;
        CreateWindow(BUTTON,L"Radiobox5",BS_RADIOBOX|WS_VISIBLE,
            rc.x,rc.y,rc.w,rc.h,hwnd,(3<<16)|ID_RB5,NULL,NULL);
        OffsetRect(&rc,0,rc.h+10);
        CreateWindow(BUTTON,L"Radiobox6",BS_RADIOBOX|WS_VISIBLE,
            rc.x,rc.y,rc.w,rc.h,hwnd,(3<<16)|ID_RB6,NULL,NULL);
        return TRUE;
    }

WM_CREATE消息创建的控件，如 表格8_1_ 所示。

表格 8‑1 控件的具体信息

.. _表格8_1:

======== ======== ========= ============== ==================================
控件类型 名称     ID值      风格
======== ======== ========= ============== ==================================
BUTTON   EXIT     ID_EXIT   WS_VISIBLE
\        RADIOBOX Radiobox1 (1<<16)|ID_RB1 BS_RADIOBOX|WS_VISIBLE
\                 Radiobox2 (1<<16)|ID_RB2 WS_DISABLED|BS_RADIOBOX|WS_VISIBLE
\                 Radiobox3 (2<<16)|ID_RB3 BS_RADIOBOX|BS_PUSHLIKE|WS_VISIBLE
\                 Radiobox4 (2<<16)|ID_RB4 BS_RADIOBOX|BS_PUSHLIKE|WS_VISIBLE
\                 Radiobox5 (3<<16)|ID_RB5 BS_RADIOBOX|WS_VISIBLE
\                 Radiobox6 (3<<16)|ID_RB6 BS_RADIOBOX|WS_VISIBLE
======== ======== ========= ============== ==================================

所有单选按钮控件都是BS_RADIOBOX 属性。Radiobox3和Radiobox4的属性BS_PUSHLIKE，表示控件的外观是一个按键，当被选中时，控件会下沉。

.. code-block:: c
    :caption: 代码清单 8‑4控件ID值（文件GUI_DEMO_Radiobox.c）
    :linenos:
    :name: 代码清单8_4

     #define ID_RB1 0x1101
     #define ID_RB2 0x1102
     #define ID_RB3 0x1103
     #define ID_RB4 0x1104
     #define ID_RB5 0x1105
     #define ID_RB6 0x1106

代码清单8_4_ 控件ID值（文件GUI_DEMO_Radiobox.罗列了所有单选按钮的ID值。其高16位代表所属Group的ID号。以组3为例，组1、组2都是一样的道理。3<<16等价于\ :math:`3*2^{16}`\
，转换为十六进制，就是0x00030000，再通过与ID_RB5进行或运算，得到结果为0x00031105，最前面的四位数就是Group的ID号。

2. WM_NOTIFY消息

.. code-block:: c
    :caption: 代码清单 8_5 WM_NOTIFY消息响应（文件GUI_DEMO_Radiobox.c）
    :linenos:
    :name: 代码清单8_5

    case  WM_NOTIFY: //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,高16位为通知码;
    lParam指向了一个NMHDR结构体.
    {
    u16 code,id;
    
    id  =LOWORD(wParam);
    code=HIWORD(wParam);
    if(id >= ID_RB1 && id<= ID_RB6)
    {
        if(code == BN_CHECKED)
        { //单选框选中.
        GUI_Printf("Radiobox Checked: ID:%04XH\r\n",id);
        }
    }      
        if(id == ID_EXIT && code == BN_CLICKED)
        {
            PostCloseMessage(hwnd);//产生WM_CLOSE消息关闭主窗口
        }  
    break;  
    }

调用LOWORD和HIWORD读取控件的ID和通知码。单选按钮选中，则在串口输出控件的ID号。单击EXIT按钮，则会发送WM_CLOSE消息关闭主窗口。

3. WM_CTLCOLOR消息

.. code-block:: c
    :caption: 代码清单 8‑6 WM_CTLCOLOR消息响应（文件GUI_DEMO_Radiobox.c）
    :linenos:
    :name: 代码清单8_6

    case  WM_CTLCOLOR:
    {
    u16 id;
    id =LOWORD(wParam);
    if(id== ID_RB5 || id == ID_RB6) //只改变 RB5,RB6的颜色.
    {
        CTLCOLOR *cr;
        cr =(CTLCOLOR*)lParam;
        if(SendMessage(GetDlgItem(hwnd,id),BM_GETSTATE,0,0)&BST_CHECKED)
        {
        cr->TextColor =RGB888(250,0,0);      //文字颜色（RGB32颜色格式)
        cr->BackColor =RGB888(220,200,200);    //背景颜色（RGB32颜色格式)
        cr->BorderColor =RGB888(30,30,230);  //边框颜色（RGB32颜色格式)
        cr->ForeColor =RGB888(100,250,100);  //前景颜色（RGB32颜色格式)
        }
        else
        {
        cr->TextColor =RGB888(20,20,250);
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

WM_CTLCOLOR消息的lParam参数为产生该消息的窗口ID。这里只改变组3成员的外观，最后返回TRUE，否则将按照系统默认的样式来配置。

通过发送消息BM_GETSTATE，来得到当前控件是否被选中，同时改变控件的外观颜色。前景颜色，就是控件在选中状态，显示的颜色。

4. WM_PAINT消息

.. code-block:: c
    :caption: 代码清单 8_7 WM_PAINT消息响应（文件GUI_DEMO_Radiobox.c）
    :linenos:
    :name: 代码清单8_7

    case  WM_PAINT: //窗口需要重绘制时，会自动收到该消息.
    { 
        PAINTSTRUCT ps;  
        HDC hdc;
        hdc =BeginPaint(hwnd,&ps);           
        SetTextColor(hdc,MapRGB(hdc,0,0,255)); 
        TextOut(hdc,8,4,L"Radiobox Test:",-1);  
        EndPaint(hwnd,&ps);
        return  TRUE;
    }

窗口重绘时，在客户区（8，4）处绘制蓝色的字符串：Radiobox Test:。

5. default消息

.. code-block:: c
    :caption: 代码清单 8‑8 default消息响应（文件GUI_DEMO_Radiobox.c）
    :linenos:
    :name: 代码清单8_8

    default:
        return  DefWindowProc(hwnd,msg,wParam,lParam);

调用DefWindowProc函数来处理用户不关心的消息。

最后，将GUI_DEMO_Radiobox加入到GUI_AppMain中，见 代码清单8_9_ GUI_AppMain函数（文件GUI_AppMain.。

.. code-block:: c
    :caption: 代码清单 8‑9 GUI_AppMain函数（文件GUI_AppMain.c）
    :linenos:
    :name: 代码清单8_9

    void GUI_AppMain(void)
    {
        while(1)
        {
            GUI_DEMO_Button();
            GUI_DEMO_Checkbox();
            GUI_DEMO_Radiobox();
        }
    }

.. _实验现象-3:

实验现象
^^^^^^^^^^^^

除了尺寸有些改变，在LCD显示的控件较大，其余的差不多是一模一样。见 图8_3_ 和 图8_4_ 。

.. image:: /media/docx036.jpg
   :align: center
   :alt: 图 8_3 窗口客户区设计效果
   :name: 图8_3

图 8‑3 实验结果

.. image:: /media/docx037.jpg
   :align: center
   :alt: 图 8‑4 实验结果（选中状态）
   :name: 图8_4

图 8‑4 实验结果（选中状态）