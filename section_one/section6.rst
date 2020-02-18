.. vim: syntax=rst

按钮控件
----------------

emXGUI提供了三种按钮：按钮，复选框，单选按钮。

图6_1_ 的处是emXGUI的按钮控件，可以被单击，按下；处是复选框，可以同时选中多个功能；处是单选框，只可以选择单个选项。处和处区别在于：处，串口的停止位只可以是1位、1.5位和2位中的某一个；处，串口助手可以同时使能自动发送，自动清空和以十六进制发送。本章，我们先学习使用按钮控件。

.. image:: /media/docx024.jpg
   :align: center
   :alt: 图 6‑1 各种按钮
   :name: 图6_1

按钮控件，主要用于用户和应用程序之间的交互，按钮会对每一个动作做出相应的回应。例如，单击按钮时，该按钮会改变其外观和状态，同时向父窗口发送消息，通知父窗口，我被按下了，假如该按钮的功能是关闭窗口，则父窗口会被关闭。图6_2_ 和 图6_3_ 。正所谓，众口难调。emXGUI除了提供系统自带的标准控件
，用户还可以自定义控件的外观以及行为。 图6_4_ ，是一个自定义控件。当该按钮被按下后，按钮的显示内容发生了改变。除此之外，用户也可以选择改变背景等等。只有一句话：只有你想不到的，没有emXGUI做不到的。

.. image:: /media/docx025.jpg
   :align: center
   :alt: 图 6_2 按钮未被按下
   :name: 图6_2

.. image:: /media/docx026.jpg
   :align: center
   :alt: 图 6_3 按钮被按下
   :name: 图6_3

.. image:: /media/docx027.jpg
   :align: center
   :alt: 图 6_4 自定义控件
   :name: 图6_4


创建按钮控件
~~~~~~~~~~~~~~~~~~

.. _标准消息类型及参数说明-1:

标准消息类型及参数说明
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

部分消息在第五章已经详细介绍过了，这里就简单说明一下，不懂的地方，可以查阅第五章的标准消息类型及参数说明。

(1) WM_CREATE消息。

当窗口被创建时，会收到WM_CREATE消息，用户可以在该消息里做一些初始化操作或创建子窗口。

(2) default消息。

一些我们并不关心的系统消息，调用DefWindowProc函数进行处理。

(3) WM_PAINT消息。

.. image:: /media/docx028.jpg
   :align: center
   :alt: 图 6_5 桌面重绘
   :name: 图6_5

如 图6_5_ 所示，当我们将窗口1从处移动到处时，此时处的客户区内容实际上只会显示我们的桌面背景，因此我们需要把处的客户区内容“移动”到处的客户区进行显示，这个过程叫做重绘。
创建窗口的时候，新建的窗口如 图6_5_ 的窗口，也需要进行重绘。当窗口客户区需要重绘制时，会产生WM_PAINT消息。在该消息里，用户应调用BeginPaint来开始绘制，BeginPaint会返回一个DC，用于绘图操作，所有绘图完成后，需调用EndPaint来结束绘制。

BeginPaint有两个形参，一个是重绘窗口的句柄，另一个是PAINTSTRUCT类型的结构体，见 代码清单6_1_ PAINTSTRUCT结构体（文件emXGUI.。下面简单介绍一下该结构体的成员的作用。更多详细内容，请参考《emXGUI API编程手册》窗口/消息系统API。

.. code-block:: c
    :caption: 代码清单 6_1 PAINTSTRUCT结构体（文件emXGUI.h）
    :linenos:
    :name: 代码清单6_1

    typedef struct tagPAINTSTRUCT {
        HDC         hdc;           //绘图上下文
        RECT        rcPaint;       //需要重绘的矩形区域
        BOOL        fErase;        //背景是否必须被清除
    } PAINTSTRUCT; 

1. hdc：绘图上下文，用于保存绘图参数。

2. rcPaint：RECT结构体变量，保存要求重绘的矩形区域。

3. fErase：背景是否必须被清除。fErase为非零值则在 WM_PAINT 里来擦除背景，否则不擦除背景。如果用户在消息WM_ERASEBKGND 里直接返回FALSE，这个fErase值就会是TRUE。注意，在WM_PAINT
   里绘制背景，用户要在窗口过程函数里添加WM_ERASEBKGND消息，并直接返回TRUE，使系统不要再执行默认的背景绘制。

每当窗口1收到WM_PAINT这个消息时，会执行 代码清单6_2_ 的内容，重绘后结果如 图6_6_ 所示，这样就实现了窗口的移动。

.. code-block:: c
    :caption: 代码清单 6_2桌面重绘示例
    :linenos:
    :name: 代码清单6_2

    LRESULT win_proc(HWND hwnd,UINT msg,
                WPARAM wParam,LPARAM lParam)
    {
    switch(msg)
    {
        case WM_PAINT:
        BeginPaint();
        //显示文字(“我是内容”);
        EndPaint();
        break;
    }
    }

.. image:: /media/docx020.jpg
   :align: center
   :alt: 图 6_6 重绘后界面
   :name: 图6_6

这里有的人或许会有这样的疑问：为什么我已经移动了窗口，假设水平移动x个像素，但是WM_PAINT中文字的显示位置不用偏移x个像素呢？这是因为这个文字显示的位置是在客户区的某个位置。这个坐标是以客户区原点来定义的。

.. image:: /media/docx029.jpg
   :align: center
   :alt: 图 6_7 坐标说明
   :name: 图6_7

做了一个简单的水平移动，只是为了方便说明。其实原理都是一样的。（8，4）这个坐标是相对于客户区的原点（0，0），即使我们移动窗口1，但是客户区的原点依然没有改变。因此，重绘的时候，我们只需要实现窗口客户区显示的东西，至于客户区和非客户区之间坐标变换，我们可以不用考虑。

(4) WM_NOTIFY消息。

WM_NOTIFY一般是由窗口所属的控件产生的。当控件发生某些状态改变时，便会向父窗口发送WM_NOTIFY消息。接收到的wParam的高16位：控件通知码；低16位：产生该消息的控件窗口ID（CreateWindow的窗口ID参数）。用户可以根据接收到的控件通知码，来执行不同的操作。例如，当点击某
个按钮时，弹出对话框，切换图片，切换窗口等等。还是那一句话：只有想不到的，没有做不到的。

(5) WM_CTLCOLOR消息。

该消息来自于控件窗口。控件在绘制前，会向其父窗口发送WM_CTLCOLOR消息，在该消息的处理函数中，用户可以对控件窗口的文字颜色(TextColor)，边框颜色(BorderColor)，背景颜色(BackColor)，前景颜色(ForeColor)进行设置，丛而改变控件窗口的外观颜色。注意，如果
设置了新的颜色值，需要返回TRUE；如果返回FALSE，系统将忽略用户新设置的颜色值，继续使用系统默认的颜色进行绘制。

(6) WM_DRAWITEM消息。

用于用户自定义控件，可以自己定制外观。如果一个控件在创建时，指定了WS_OWNERDRAW标志，那么当这个控件需要重绘制时，会向其父窗口发送WM_DRAWITEM消息，wParam参数指明了发送该消息的控件ID；lParam参数指向一个DRAWITEM_HDR的结构体指针。用户可以在该消息处理函数里
，对产生该消息的控件进行自定义重绘。如果用户进行了重绘操作，应返回TRUE；否则如果返回FALSE。

创建按钮控件函数
^^^^^^^^^^^^^^^^^^^^^^^^

创建按钮控件，也是调用CreateWindow函数来创建。函数声明，见 代码清单6_3_ 创建按钮控件（文件emXGUI.。

.. code-block:: c
    :caption: 代码清单 6_3创建按钮控件（文件emXGUI.h）
    :linenos:
    :name: 代码清单6_3

    #define CreateWindow(lpClass,lpWindowName,dwStyle,
                x,y,nWidth,nHeight,
                hwndParent,WinId,hInstance,lpParam)\
                CreateWindowEx(0,lpClass,lpWindowName,dwStyle,
                x,y,nWidth,nHeight,hwndParent,WinId,hInstance,lpParam)

    //创建窗口函数            
    HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,
                U32 dwStyle, int x, int y, int nWidth, int nHeight,
            HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam); 

调用CreateWindow函数，也就是调用了CreateWindowEx函数。CreateWindowEx函数参数如下：

1) dwExStyle：窗口扩展风格标志，可以是窗口位置不能被拖动（WS_EX_LOCKPOS），窗口不能通过点击来改变Z序（WS_EX_LOCKZORDER）。

2) lpClass：系统标准控件，可以是BUTTON(常规按钮， 复选框， 单选框， 组合框)， SCROLLBAR(水平/垂直滚动条)，LISTBOX(列表框)。 TEXTBOX（文字框）等等。

3) lpWindowName：窗口名， 指向unicode UCS-2格式字符串。在字符串前加一个L表示，这里的字符串采用的是宽字符，即每个字符占用两个字节。

4) dwStyle：窗口风格标志，可以是WS_CAPTON（窗口会带有标题栏）、WS_BORDER（窗口会带有小边框）、WS_DLGFRAME（窗口会带有大边框）、WS_VISIBLE（窗口创建后,默认是可见的）、WS_DISABLED（窗口创建后,不会响应输入设备的事件）、WS_CLIPCHIL
DREN（窗口绘制时,不会对子窗口区域重绘）、WS_OWNERDRAW（用户自定义控件。窗口绘制前,将发送WM_DRAWITEM消息通知父窗口,该标志只对控件类子窗口有效）。还有按钮控件特有的类型：创建立体风格的按钮(BS_3D)、创建平面风格的按钮(BS_FLAT)、创建圆角风格的按钮(BS_RO
UND)、创建圆角风格的按钮(BS_ROUND)。按下按钮发送 BN_PUSHED（BS_NOTIFY）

5) x，y，nWidth，nHeight: 指定窗口的位置和大小，位置是父窗口客户区坐标。

6) hwndParent: 指向该窗口的父窗口句柄，如果是创建主窗口，则设为NULL。

7) WinId: 窗口ID，用于对多个窗口进行标识区分，如果是创建主窗口，则忽略该参数。

8) hInstance: 应用程序实例句柄，目前版本为保留参数…，应设置为NULL。

9) lpParam: 窗口创建时，用户自定义参数，在WM_CREATE消息中，由lParam传入，如果不使用，可以忽略该参数。

创建按钮控件实验
~~~~~~~~~~~~~~~~~~~~~~~~

.. _设计要求-1:

设计要求
^^^^^^^^^^^^

图6_8_ 是本章节的设计目标，旨在介绍按钮控件的创建及使用方法。只有掌握基础使用方法后，才可以设计出高大上的效果。本章节的例程中，在客户区创建八个按钮控件，每个控件的功能，风格不完全相同，该图是使用excel表格绘制而成的，一些按钮控件的风格可能无法体现出来。读者可以通过本章节了解按钮控件的基础用法
，单击按钮控件的响应操作以及自绘制按钮控件。

.. image:: /media/docx030.jpg
   :align: center
   :alt: 图 6_8 窗口客户区设计效果
   :name: 图6_8

.. _代码设计-1:

代码设计
^^^^^^^^^^^^

.. _编程要点-1:

编程要点
''''''''''''

1) 配置WNDCLASS窗口结构体，调用CreateWindowEx创建父窗口；

2) 实现消息循环

3) 编写窗口回调函数，完成对消息的处理。

这是基础的三个步骤。与第五章的区别在于，在第三个步骤中，新增加了一些消息处理case，来处理按钮控件的动作响应。

.. _代码分析-1:

代码分析
''''''''''''

.. code-block:: c
    :caption: 代码清单 6_4 App线程GUI_AppMain（GUI_AppMain.c文件）
    :linenos:
    :name: 代码清单6_4

    void GUI_AppMain(void)
    {
        while(1)
        { 
            GUI_DEMO_Button();
        }
    }

桌面窗口创建完成后，WM_CREATE消息创建的App线程GUI_AppMain会开始启动，我们自己编写的界面都是放在该线程下执行的。见 代码清单6_4_ 。

(1) 创建父窗口代码

在创建按钮控件之前，需要先创建一个父窗口。任何一个控件，都是在其父窗口显示的。你见过哪个应用程序打开之后，什么东西都没有，只有一个按钮的吗？

.. code-block:: c
    :caption: 代码清单 6_5 GUI_DEMO_Button函数（GUI_DEMO_Button.c文件）
    :linenos:
    :name: 代码清单6_5

     void GUI_DEMO_Button(void)
     {
        HWND  hwnd;
        WNDCLASS  wcex;
        MSG msg;
    
        //第1部分：配置wcex参数。
        wcex.Tag        = WNDCLASS_TAG;
        wcex.Style      = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc  = win_proc; //设置主窗口消息处理的回调函数.
        wcex.cbClsExtra   = 0;
        wcex.cbWndExtra   = 0;
        wcex.hInstance    = NULL;//hInst;
        wcex.hIcon      = NULL;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);
        wcex.hCursor    = NULL;//LoadCursor(NULL, IDC_ARROW);
        //第2部分：创建主窗口
        hwnd  =CreateWindowEx(  NULL,
                    &wcex,
                    _T("GUI Demo - Button"),
                    WS_CAPTION| WS_DLGFRAME| WS_BORDER| WS_CLIPCHILDREN,
                    0,0,GUI_XSIZE,GUI_YSIZE,
                    NULL,NULL,NULL,NULL);
        
        //第3部分：显示主窗口
        ShowWindow(hwnd,SW_SHOW); 
        //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。
        while(GetMessage(&msg,hwnd))
        {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        }
    }

代码清单6_5_ 的第1部分主要配置了wcex结构体来设置窗口的风格为CS_HREDRAW | CS_VREDRAW（宽高发生改变时，发送重绘消息），设置win_proc作为主窗口消息处理的回调函数。

第2部分调用CreateWindowEx函数在（0，0）创建一个800*480，带有大，小边框的窗口，标题为GUI Demo - Button，创建后可见且当桌面重绘时，对子窗口进行重绘。GUI_CreateDesktop创建成功后，会返回桌面窗口的句柄。

第3部分代码是调用ShowWindow函数来显示窗口。

第4部分代码是开始窗口消息循环，负责接收和发送消息。在发送消息之前，需要调用TranslateMessage函数，将按键的消息转换为emXGUI的消息类型。窗口关闭并销毁时，GetMessage将返回FALSE，退出本消息循环。

到此为止，我们就完成了我们编程要点的前两点。

(2) 窗口回调函数

1) WM_CREATE

.. code-block:: c
    :caption: 代码清单 6‑6 WM_CREATE消息响应（文件GUI_DEMO_Button.c）
    :linenos:
    :name: 代码清单6_6

     case WM_CREATE:

        GetClientRect(hwnd,&rc); //获得窗口的客户区矩形

        CreateWindow(BUTTON,L"EXIT",WS_VISIBLE,rc.w-100,8,80,48,hwnd,ID_EXIT,NULL,NULL);

        //设置矩形参数，用于创建按钮
        rc.x =20;
        rc.y =50;

        rc.w =100;
        rc.h =40;
        CreateWindow(BUTTON,L"Button1",WS_VISIBLE,
        rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN1,NULL,NULL);

        OffsetRect(&rc,0,rc.h+10); //往下移动矩形位置(X轴不变,Y轴位置增加rc.h+10个像素)
        //创建立体风格的按钮(BS_3D)
        CreateWindow(BUTTON,L"Button2",BS_3D|WS_VISIBLE,
        rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN2,NULL,NULL);

        OffsetRect(&rc,0,rc.h+10);
        //创建平面风格的按钮(BS_FLAT)
        CreateWindow(BUTTON,L"Button3",BS_FLAT|WS_VISIBLE,
        rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN3,NULL,NULL);

        OffsetRect(&rc,0,rc.h+10);
        //创建圆角风格的按钮 (BS_ROUND )
        CreateWindow(BUTTON,L"Button4",BS_ROUND|WS_VISIBLE,
        rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN4,NULL,NULL);
        rc.x =150;
        rc.y =30;
        rc.w =120;
        rc.h =60;
        //创建圆角风格的按钮(BS_ROUND+BS_NOTIFY)
        CreateWindow(BUTTON,L"Button5",BS_ROUND|BS_NOTIFY|WS_VISIBLE,
        rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN5,NULL,NULL);

        OffsetRect(&rc,0,rc.h+10);
        //创建自绘制按钮(WS_OWNERDRAW)
        CreateWindow(BUTTON,L"Button6\r\nOwnerDraw",WS_OWNERDRAW|WS_VISIBLE,
        rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN6,NULL,NULL);

        OffsetRect(&rc,0,rc.h+10);
        //创建圆角风格的按钮(BS_ROUND+WS_DISABLE)
        CreateWindow(BUTTON,L"Button7",BS_ROUND|WS_DISABLED|WS_VISIBLE,
        rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN7,NULL,NULL);
        return TRUE;

前面我们提到过，WM_CREATE消息主要是负责创建控件的。代码清单6_6_ WM_CREATE消息响应（文件GUI_DEMO_Button.中我们创建了六个不同风格的按钮。调用OffsetRect来移动显示的位置，间隔为每个控件的高度下10个像素值，
代码清单6_6_ ，请参考《emXGUI API编程手册》的章节：位置及区域操作运算API。用户也可以选择自己输入坐标，一样能够达到效果。

由于按钮也是窗口，所以也可以使用窗口的属性值。这些属性值都是定义在emXGUI.h文件中，见 代码清单6_7_。
不同的属性值可以随意组合。每个控件都有各自的ID号，ID号的值可以随意给定。ID号主要是为了方便管理。比如，我们单击了某个按钮，就会发生WM_NOTIFY的消息，这个消息的wParam低16位就是控件的ID号。利用这个我们就可以来检测到底是什么按钮被单击。是不是很方便呢。

.. code-block:: c
    :caption: 代码清单 6_7 按钮属性值（文件emXGUI.h）
    :linenos:
    :name: 代码清单6_7

     /*
     * Button Control Styles
     */
     #define BS_FLAT (1<<0) //平面风格
     #define BS_3D (2<<0) //立体风格
     #define BS_ROUND (3<<0) //圆角风格
     #define BS_NOTIFY (1<<15) //是否发送PUSHED消息

     //窗口公共风格(高16位)

     /*
     * Window Styles
     */
     #define WS_DISABLED 0x08000000UL //窗口创建后,不会响应输入设备的事件(键盘与鼠标).

     #define WS_CLIPCHILDREN 0x02000000UL //父对象重绘时，是否对子窗口重绘
     #define WS_VISIBLE 0x01000000UL //窗口创建后,默认是可见的.
     #define WS_BORDER 0x00800000UL //窗口会带有小边框.
     #define WS_DLGFRAME 0x00400000UL //窗口会带有大边框.
     #define WS_CAPTION 0x00080000UL //窗口会带有标题栏.
     #define WS_OWNERDRAW 0x00020000UL //用户自定义样式

代码清单6_6_ WM_CREATE消息响应（文件GUI_DEMO_Button.中每个按钮都有多个属性和各自的ID值，见 表格6_1_。

表格 6‑1 按钮的属性和ID值

.. _表格6_1:

==================== ======= ===============================
BUTTON 控件          ID值    风格
==================== ======= ===============================
EXIT                 ID_EXIT WS_VISIBLE
Button1              ID_BTN1 WS_VISIBLE
Button2              ID_BTN2 BS_3D|WS_VISIBLE
Button3              ID_BTN3 BS_FLAT|WS_VISIBLE
Button4              ID_BTN4 BS_ROUND|WS_VISIBLE
Button5              ID_BTN5 BS_ROUND|BS_NOTIFY|WS_VISIBLE
Button6\r\nOwnerDraw ID_BTN6 WS_OWNERDRAW|WS_VISIBLE
Button7              ID_BTN7 BS_ROUND|WS_DISABLED|WS_VISIBLE
==================== ======= ===============================

表格6_1_ 中的ID值，其实是宏定义，用户可以自己修改。见 代码清单6_8_ 控件ID（文件GUI_DEMO_Button.。

.. code-block:: c
    :caption: 代码清单6_8 控件ID（文件GUI_DEMO_Button.c）
    :linenos:
    :name: 代码清单6_8

     //定义控件ID
     #define ID_EXIT 0x1000
     #define ID_BTN1 0x1101
     #define ID_BTN2 0x1102
     #define ID_BTN3 0x1103
     #define ID_BTN4 0x1104
     #define ID_BTN5 0x1105
     #define ID_BTN6 0x1106
     #define ID_BTN7 0x1107

2) Default

用户不关心的消息可以通过调用DefWindowProc函数来处理。见 代码清单6_9_。

.. code-block:: c
    :caption: 代码清单 6_9 用户不关心的消息处理（文件GUI_DEMO_Button.c）
    :linenos:
    :name: 代码清单6_9

     default:

     return DefWindowProc(hwnd,msg,wParam,lParam);

3) WM_PAINT

.. code-block:: c
    :caption: 代码清单 6_10 WM_PAINT消息响应（文件GUI_DEMO_Button.c）
    :linenos:
    :name: 代码清单6_10

    case WM_PAINT: //窗口需要重绘制时，会自动收到该消息.
     {
        PAINTSTRUCT ps;
        hdc =BeginPaint(hwnd,&ps);
        SetTextColor(hdc,MapRGB(hdc,0,0,255));
        TextOut(hdc,8,4,L"Button Test:",-1);
        EndPaint(hwnd,&ps);
        return TRUE;
     }

代码清单6_10_ 中，使用SetTextColor设置字体颜色为RGB(0，0，255)。调用TextOut函数在客户区（8，4）显示字符串： “Button Test:”。 SetTextColor和TextOut函数说明，请参考《emXGUI
API编程手册》的章节：绘图API。注意，重绘时需要调用BeginPaint函数获取绘图上下文。绘制完成后 ，调用EndPaint函数结束绘制。

4) WM_DRAWITEM

Button6是用户自定义风格按钮，所以在绘制时，会给父窗口发送WM_DRAWITEM消息，来进行绘制，用户可以自己设计。例程中，只是改变按钮在按下时，按钮的字体颜色和背景颜色。在不同的状态值下，上述的三者的颜色有所不同。
见 表格6_2_。按钮处于弹起状态时，字体是黑色，背景是深绿色，边框是浅绿。如果按钮被按下的话，字体会变红色，背景为淡蓝色，边框为红色。

表格 6‑2 不同的状态值的颜色值

.. _表格6_2:

============ =============== =============
\            按下            弹起
============ =============== =============
画刷（背景） （150,200,250） （30,150,30）
画笔（边框） （250,0,0）     （0,250,0）
文字         （250,0,0）     （0,50,100）
============ =============== =============

具体的代码实现，见 代码清单6_11_ 和 代码清单6_12_ 。

.. code-block:: c
    :caption: 代码清单 6‑11 WM_DRAWITEM消息响应（文件GUI_DEMO_Button.c）
    :linenos:
    :name: 代码清单6_11

    case  WM_DRAWITEM:
    {
        /*　当控件指定了WS_OWNERDRAW风格，则每次在绘制前都会给父窗口发送WM_DRAWITEM消息。
        *  wParam参数指明了发送该消息的控件ID;lParam参数指向一个DRAWITEM_HDR的结构体指针，
        *  该指针成员包含了一些控件绘制相关的参数.
        */

        DRAWITEM_HDR *ds;

        ds =(DRAWITEM_HDR*)lParam;

        if(ds->ID >= ID_BTN1 && ds->ID<= ID_BTN6)
        {
        button_owner_draw(ds); //执行自绘制按钮
        }
        return TRUE;
    }

.. code-block:: c
    :caption: 代码清单 6_12 绘制按钮外观函数（文件GUI_DEMO_Button.c）
    :linenos:
    :name: 代码清单6_12

     static void button_owner_draw(DRAWITEM_HDR *ds) //绘制一个按钮外观
     {
     // HWND hwnd;
        HDC hdc;
        RECT rc;
        WCHAR wbuf[128];
        
        //  hwnd =ds->hwnd; //button的窗口句柄.
        hdc =ds->hDC;   //button的绘图上下文句柄.
        rc =ds->rc;     //button的绘制矩形区.
        
        if(ds->State & BST_PUSHED)
        { //按钮是按下状态
            
            SetBrushColor(hdc,MapRGB(hdc,150,200,250)); //设置填充色(BrushColor)
            SetPenColor(hdc,MapRGB(hdc,250,0,0));        //设置绘制色(PenColor)
            SetTextColor(hdc,MapRGB(hdc,250,0,0));      //设置文字色
        }
        else
        { //按钮是弹起状态
            SetBrushColor(hdc,MapRGB(hdc,30,150,30));
            SetPenColor(hdc,MapRGB(hdc,0,250,0));
            SetTextColor(hdc,MapRGB(hdc,0,50,100));
        }
        
        FillRect(hdc,&rc); //用矩形填充背景
        DrawRect(hdc,&rc); //画矩形外框
        GetWindowText(ds->hwnd,wbuf,128); //获得按钮控件的文字
        DrawText(hdc,wbuf,-1,&rc,DT_VCENTER|DT_CENTER);//绘制文字(居中对齐方式)
    }


代码清单6_11_ 利用DRAWITEM_HDR结构体成员的ID值来执行自绘制按钮。由于只有Button6拥有WS_OWNERDRAW属性，所以只有ID值为ID_BTN6的Button6会执行自绘制，调用绘制外观函数button_owner_draw，
见 代码清单6_12_ 。根据按钮的状态值（ds->state），设置不同的画刷、画笔、文字的颜色。调用FillRect函数填充矩形的背景，使用DrawRect函数来画矩形外框，调用GetWindowText可以获取控件的文字，使用DrawText来绘制文字，使其居中对齐。具体的函数说明，请参考《emXGUI
API编程手册》的章节：绘图API。

5) WM_NOTIFY

WM_NOTIFY 消息的wParam低16位为发送该消息的控件ID，高16位为通知码。LOWORD和HIWORD用来读取消息参数的低16位和高16位。ID_BTN1~ ID_BTN6每一个按钮的动作响应都是在这里定义的。用户可以自己修改这里的代码。

.. code-block:: c
    :caption: 代码清单 6_13 WM_NOTIFY消息响应（文件GUI_DEMO_Button.c）
    :linenos:
    :name: 代码清单6_13

    case  WM_NOTIFY: //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,高16位为通知码;
        lParam指向了一个NMHDR结构体.
        {
        u16 code,id;
    //      NMHDR *nr=(NMHDR*)lParam;
    
        id  =LOWORD(wParam);
        code=HIWORD(wParam);
    
        if(id >= ID_BTN1 && id<= ID_BTN6)
        {
            if(code == BN_PUSHED)
            { //按钮被按下了.
            GUI_Printf("Button PUSHED: ID:%04XH\r\n",id);
            }
    
            if(code == BN_CLICKED)
            { //按钮弹起了.
            GUI_Printf("Button UNPUSHED: ID:%04XH\r\n",id);
            }
        }
    
        if(id== ID_EXIT && code==BN_CLICKED)
        { // EXIT按钮弹起
            PostCloseMessage(hwnd); //产生WM_CLOSE消息关闭主窗口
        }
        }
        break;

代码清单6_13_ 只是简单检测按钮的动作，同时打印到串口。注意，只有当按钮的属性有BS_NOTIFY时，才会检测到BN_PUSHED状态值。ID_EXIT单击时，会调用PostCloseMessage发送窗口关闭消息WM_CLOSE，来关闭主窗口。

6) WM_CTLCOLOR

WM_NOTIFY 消息的wParam参数指明了发送该消息的控件ID；lParam参数指向一个CTLCOLOR的结构体指针。可以使用LOWORD来读取wParam的低16位，获取ID。

.. code-block:: c
    :caption: 代码清单 6_14 WM_CTLCOLOR消息响应（文件GUI_DEMO_Button.c）
    :linenos:
    :name: 代码清单6_14

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
        if(id== ID_BTN5) //只改变BTN5的颜色.
        {
        CTLCOLOR *cr;
        cr =(CTLCOLOR*)lParam;
        if(SendMessage(GetDlgItem(hwnd,id),BM_GETSTATE,0,0)&BST_PUSHED)
        {
            cr->TextColor =RGB888(50,220,50);  //文字颜色（RGB32颜色格式)
            cr->BackColor =RGB888(20,100,20);  //背景颜色（RGB32颜色格式)
            cr->BorderColor =RGB888(30,30,30); //边框颜色（RGB32颜色格式)
        }
        else
        {
            cr->TextColor =RGB888(250,250,250);
            cr->BackColor =RGB888(200,0,0);
            cr->BorderColor =RGB888(50,50,50);
        }
        return TRUE;
        }
        else
        {
        //其它按钮使用系统默认的颜色进行绘制，所以直接返回FALSE.
        return FALSE;
        }
    }

代码清单6_14_ 只改变Button5的文字、背景和边框的颜色。函数GetDlgItem可以得到某个控件的句柄值，发送消息
BM_GETSTATE来获取Button的状态值。如果按下按钮，则文字为浅绿色，背景为深绿色，边框为黑色。反之，则文字为白色，背景为红色，边框为灰色。当用户自己定义的文字、背景和边框的颜色后，需要返回TRUE，否则将按照系统默认的进行配置。

.. _实验现象-1:

实验现象
^^^^^^^^^^^^

利用我们的桌面截图DEMO，可以对我们的屏幕进行截图，如 图6_9_ 。可以看出，Button1~ Button4、
Button7的按钮风格有明显的变化，Button5和Button6，在单击时，控件的文字、背景和边框的颜色均发生改变，不过Button5是用户自定义按钮控件，Button6是系统提供的标准控件。

.. image:: /media/docx031.jpg
   :align: center
   :alt: 图 6‑9 窗口显示效果
   :name: 图6_9

