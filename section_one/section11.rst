.. vim: syntax=rst

对话框控件
---------------

对话框一般情况下，用于确认信息。最简单的对话框是警告，当我们关闭窗口时，为了确认用户是有意或无意的关闭动作，会弹出一个对话框进行简单的确认，如 图11_1_，弹出对话框，是否需要进行文档的保存。

.. image:: /media/docx045.jpg
   :align: center
   :alt: 图 11‑1 对话框
   :name: 图11_1

创建对话框控件
~~~~~~~~~~~~~~~~~~~~~

.. _标准消息类型及参数说明-6:

标准消息类型及参数说明
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

本章使用的消息类型常用的有WM_CREATE、WM_NOTIFY。WM_CREATE消息用于创建控件； WM_NOTIFY消息用来处理按钮消息。还有一个新的消息类型：WM_DESTROY。

我们常常在EXIT按键的WM_NOTIFY中调用PostCloseMessage来关闭窗口。当PostCloseMessage产生 WM_CLOSE 消息时，这时用户还可以"选择"是否真正要关闭窗口，如果是，则调用DestroyWindow函数。DestroyWindows函数会再产生
WM_DESTROY消息。当收到WM_DESTROY时，说明窗口已经执行"注销"并结束了，在WM_DESTROY消息中可以做一些资源释放的操作。

对话框配置结构体
^^^^^^^^^^^^^^^^^^^^^^^^

emXGUI可以通过配置__MSGBOXOPTIONS结构体，来改变对话框内部的控件，如按键的个数，文字等，结构体__MSGBOXOPTIONS，见 代码清单11_1_。

.. code-block:: c
    :caption: 代码清单 11‑1 对话框配置结构体__MSGBOXOPTIONS
    :linenos:
    :name: 代码清单11_1

     typedef struct __MSGBOXOPTIONS
     {
        const WCHAR **pButtonText; //按键文字
        int ButtonCount; //按键个数
        u32 Flag; //消息框的图标
     }MSGBOX_OPTIONS;

1) pButtonText：存放按键显示文字，有几个按键，就需要几个字符串。

2) ButtonCount：对话框内按键的个数。

3) Flag：消息框的标志位。用来控制消息框的图标以及按钮宽度。可以是

显示 "出错" 图标（MB_ICONERROR）、"询问" 图标（MB_ICONQUESTION）、"警告" 图标（MB_ICONWARNING）和"信息"
图标（MB_ICONINFORMATION）。按钮宽度可以通过MB_BTN_WIDTH来设置，也可以由系统自动设置按钮宽度（MB_BTN_AUTOSIZE）。

创建对话框控件函数
^^^^^^^^^^^^^^^^^^^^^^^^^^^

emXGUI调用MessageBox函数创建对话框控件，同时会返回一个int类型的数据，用户可以通过该返回值，来确认对话框的哪一个按钮被按下。见 代码清单11_2_

.. code-block:: c
    :caption: 代码清单 11‑2创建对话框控件函数MessageBox
    :linenos:
    :name: 代码清单11_2

     int MessageBox(HWND hwndParent,int x,int y,int w,int h,
                    const WCHAR *pText,const WCHAR *pCaption,
                    const MSGBOX_OPTIONS *opt);

1. hwndParent：对话框所属的父窗口。控件不可以脱离窗口而存在，通过该成员来指定该控件是属于哪一个父窗口。

2. x， y，w，h：分别是对话框的起点坐标（x，y）以及对话框的宽w，高h。

3. pText：对话框显示的内容，使用宽字符型字符串。

4. pCaption：对话框的标题，同样使用宽字符型字符串。

5. opt：对话框配置结构体。调用MessageBox函数创建对话框时，作为参数，来配置对话框的布局。

创建对话框控件实验
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. _设计要求-6:

设计要求
^^^^^^^^^^^^

图11_2_ 是本章的设计要求。解释一下：这里的三个对话框，是分别对于三个按钮，且只有按下按钮，对话框才会出现。为了节约篇幅，所以将三个对话框，放在一张图片中。通过点击对话框内的按钮，会返回相应的值，例程中只实现了将返回值输出到串口。

.. image:: /media/docx046.jpg
   :align: center
   :alt: 图 11‑2 设计要求
   :name: 图11_2

.. _代码分析-6:

代码分析
^^^^^^^^^^^^

(1) 创建父窗口

.. code-block:: c
    :caption: 代码清单 11‑3 GUI_DEMO_Messagebox函数（文件GUI_DEMO_Messagebox.c）
    :linenos:
    :name: 代码清单11_3

     void GUI_DEMO_Messagebox(void)
     {
        HWND hwnd;
        WNDCLASS wcex;
        MSG msg;
        //
        wcex.Tag = WNDCLASS_TAG;
        wcex.Style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WinProc; //设置主窗口消息处理的回调函数.

        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = NULL;//hInst;
        wcex.hIcon = NULL;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);
        wcex.hCursor = NULL;//LoadCursor(NULL, IDC_ARROW);
        //创建主窗口
        hwnd =CreateWindowEx( NULL,
        &wcex,
        _T("GUI_DEMO-Messagebox"),
        WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,
        10,20,440,240,
        NULL,NULL,NULL,NULL);
        //显示主窗口
        ShowWindow(hwnd,SW_SHOW);
        //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。
        while(GetMessage(&msg,hwnd))
        {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        }
     }

创建父窗口，标题栏为“GUI Demo - Messagebox”，带有大小边框，设置WinProc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

.. code-block:: c
    :caption: 代码清单 11‑4 WM_CREATE消息响应（文件GUI_DEMO_Messagebox.c）
    :linenos:
    :name: 代码清单11_4

     case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口
     {
        GetClientRect(hwnd,&rc); //获得窗口的客户区矩形
        CreateWindow(BUTTON,L"OK",WS_VISIBLE,
        rc.w-80,8,68,32,hwnd,ID_OK,NULL,NULL);
        rc.x =20;
        rc.y =30;
        rc.w =100;
        rc.h =40;

        //创建按钮
        CreateWindow(BUTTON,L"Msgbox-1",WS_VISIBLE,
        rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN1,NULL,NULL);
        //往下移动矩形位置(X轴增加rc.w+10个像素)
        OffsetRect(&rc,rc.w+10,0);
        CreateWindow(BUTTON,L"Msgbox-2",WS_VISIBLE,
        rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN2,NULL,NULL);
        OffsetRect(&rc,rc.w+10,0);
        CreateWindow(BUTTON,L"Msgbox-3",WS_VISIBLE,
        rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN3,NULL,NULL);
        return TRUE;
     }

代码清单11_4_ 中，创建了四个按钮。点击BTN1、BTN2和BTN3按钮，会弹出相应的对话框。OK按钮用来关闭父窗口。

2. WM_DESTROY

.. code-block:: c
    :caption: 代码清单 11‑5 WM_DESTROY消息响应（文件GUI_DEMO_Messagebox.c）
    :linenos:
    :name: 代码清单11_5

    case WM_DESTROY: //窗口销毁时，会自动产生该消息，在这里做一些资源释放的操作.
    {
        return PostQuitMessage(hwnd); //调用PostQuitMessage，使用主窗口结束并退出消息循环.
    }

调用PostQuitMessage，使用主窗口结束并退出消息循环。具体说明，可以参考《emXGUI API编程手册》的章节：标准消息类型及参数说明。

3. WM_NOTIFY

.. code-block:: c
    :caption: 代码清单 11‑6 WM_NOTIFY消息响应（文件GUI_DEMO_Messagebox.c）
    :linenos:
    :name: 代码清单11_6

     //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,高16位为通知码;lParam指向了一个NMHDR结构体.
     case WM_NOTIFY:
     {
        u16 code,id;
        int ret=0;
        code =HIWORD(wParam); //获得通知码类型.
        id =LOWORD(wParam); //获得产生该消息的控件ID.
        if(id==ID_OK && code==BN_CLICKED)
        {

        PostCloseMessage(hwnd); //产生WM_CLOSE消息关闭窗口
        }
        if(id==ID_BTN1 && code==BN_CLICKED)
        {
        ret=MessageBox(hwnd,10,20,200,120,L"Hello!",L"MsgBox-1",NULL);
        }
        if(id==ID_BTN2 && code==BN_CLICKED)
        {
        const WCHAR *btn[] ={L"YES",L"NO",}; //对话框内按钮的文字
        MSGBOX_OPTIONS mb;
        mb.Flag =MB_BTN_WIDTH(80)|MB_ICONWARNING; //按钮的宽度为80px,使用警告图标
        mb.pButtonText =btn;
        mb.ButtonCount=2; //对话框内创建两个按钮
        ret=MessageBox(hwnd,10,20,320,150,
        L"MB_YESNO + MB_ICON\r\nABCDEFG",L"MsgBox-2",&mb);
        }
        if(id==ID_BTN3 && code==BN_CLICKED)
        {
        const WCHAR *btn[] ={L"Yes to all",L"取消",L"确认>>"};
        MSGBOX_OPTIONS mb;
        mb.Flag =MB_ICONINFORMATION; //使用信息图标
        mb.pButtonText =btn;
        mb.ButtonCount=3;
        ret=MessageBox(hwnd,10,20,360,180,
        L"Auto size + MB_ICON\r\nMulti-Line",L"MsgBox-3",&mb);
        }
        GUI_Printf("Messagebox Return:%d\r\n",ret);
        break;
     }

利用HIWORD和LOWORD函数来获取控件的ID和通知码。对于BTN2，定义了一个MSGBOX_OPTIONS类型的变量mb，使用警告图标，对话框内创建两个按钮，宽度为80px，显示的文字为“YES”和“NO”。我们点击其中一个按钮，MessageBox函数会有返回值，存放在ret中。这个值就是按
钮对应的文字下标，如点击YSE，会返回0；点击NO，则会返回1

BTN3使用信息图标，对话框内有三个按钮，显示的文字为“YES to all”、“取消”和“确认”，最后把ret的值打印到串口。

这样窗口就设计完成了，将GUI_DEMO_Messagebox函数加入到GUI_AppMain中，见 代码清单11_7_

.. code-block:: c
    :caption: 代码清单 11‑7 GUI_AppMain函数（文件GUI_AppMain.c）
    :linenos:
    :name: 代码清单11_7

     void GUI_AppMain(void)
     {
        while(1)
        {
            GUI_DEMO_Button();
            GUI_DEMO_Checkbox();
            GUI_DEMO_Radiobox();
            GUI_DEMO_Textbox();
            GUI_DEMO_Progressbar();

            GUI_DEMO_Messagebox();
        }
     }

.. _实验现象-6:

实验现象
^^^^^^^^^^^^

如 图11_3_ ，我们点击Msgbox-2按钮，此时，会弹出Msgbox-2的对话框。点击YSE的的时候，串口会输出0，见 图11_4_。

.. image:: /media/docx047.jpg
   :align: center
   :alt: 图 11‑3 实验结果
   :name: 图11_3

图 11‑3 实验结果

.. image:: /media/docx048.jpg
   :align: center
   :alt: 图 11‑4串口输出结果
   :name: 图11_4

图 11‑4串口输出结果

