.. vim: syntax=rst

创建桌面
------------

桌面窗口是GUI系统创建的第一个窗口，也称作是根窗口，是占据整个GUI屏幕的最底层窗口。桌面窗口是GUI必需存在的唯一根窗口，一旦创建运行后，是不可以被删除销毁的，类似于Windows桌面，每一个应用程序的窗口都是在其上面显示。在学习桌面创建之前，我们先了解一下emXGUI的绘图过程。

绘图表面(Surface)
~~~~~~~~~~~~~~~~~~~~~~~~~~

Surface是对绘图设备的描述，其记录了绘图设备的颜色格式，物理像素大小，显示缓冲区，以及绘图引擎（GAL），GUI所有的绘图目标，最终都是在Surface上进行。每个Surface都是一个独立的绘图设备，可以由用户自由创建。函数原型及示例，见 代码清单5_1_。

.. code-block:: c
    :caption: 代码清单 5_1 创建Surface
    :linenos:
    :name: 代码清单5_1

    //函数原型
    SURFACE* CreateSurface(SURF_FORMAT Format,U32 nWidth,U32 nHeight,
                int LineBytes,void *Bits);
    //举例说明            
    //创建绘图表面
    /* 直接指定地址的方式， 显存地址，*/
    pSurf = GUI_CreateSurface(SURF_RGB565, 
                            LCD_XSIZE,LCD_YSIZE,
                            LCD_XSIZE*2,
                            (void*)LCD_FRAME_BUFFER);

CreateSurface函数参数说明如下：

Format ：Surface的颜色格式，可以是SURF_SCREEN(使用与屏幕相同的格式)，
SURF_RGB332，SURF_RGB565，SURF_ARGB4444， SURF_XRGB8888，
SURF_ARGB8888。通过修改宏定义LCD_FORMAT可以实现各种格式的切换。
这里我们使用的是RGB565，每个像素占2个字节。

nWidth 、nHeight ：Surface的宽度和高度，一般是LCD的宽度和高度，
即宽度（LCD_XSIZE）是800，高度（LCD_YSIZE）是480。

LineBytes ：Surface每行的内存字节数，这个值取决于Surface的颜色格式。
如果使用的SURF_ARGB8888，即每个像素占4个字节，则每行的内存字节数等于行的像素数*每个像素的字节数（LCD_XSIZE
\*4）。例子中，我们使用的是RGB565，因此，每行内存字节数为LCD_XSIZE \*2。

Bits：显存的首地址。例程中采用SDRAM作为显存，其首地址为0xD0000000。

绘图上下文(Drawing Context)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Drawing Context
简称DC，基本上所有的绘图函数，都需要传入一个DC的对象参数。它保存了各种用户层的绘图参数：如画笔颜色PenColor(作用于画线，框类图形)，画刷颜色BrushColor(作用于填充实心类的图形)，文字颜色TextColor(作用于文本显示相关函数)，字体对象…等等。代码清单5_2_ 修改了画刷，画笔以及文字的颜色，用户可以通过对这些参数进行修改来达到改变绘图输出效果。

.. code-block:: c
    :caption: 代码清单 5_2 代码示例
    :linenos:
    :name: 代码清单5_2

    SetBrushColor(hdc,MapRGB(hdc,30,150,30));
    SetPenColor(hdc,MapRGB(hdc,0,250,0));
    SetTextColor(hdc,MapRGB(hdc,0,50,100));

窗口及消息机制(Window & Message)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

窗口类型及特征
^^^^^^^^^^^^^^^^^^^^^

窗口是对多区域绘图及管理的基本对象元素。emXGUI是原生的多窗口系统，支持同屏下任意数量窗口叠层显示，并且窗口尺寸是不受屏幕分辨率约束的，可以是任意大小和位置。emXGUI的窗口分为以下几类:桌面窗口，主窗口，子窗口/控件，如 图5_1_。

.. image:: /media/docx016.png
   :align: center
   :alt: 图 5‑1窗口类型
   :name: 图5_1

主窗口是由用户在应用程序中创建，是用户图形界面应用程序的主体核心部分。一个应用程序，可以是由一个主窗口构成，也可以是由多个主窗口组成，多个主窗口间，是可以相互叠加及切换的，当然这些具体的应用方式是由用户实际的应用策略来决定，emXGUI只是给用户提供了这些丰富灵活的机制供驱使。当主窗口工作结束时，用
户可以对其进行删除/销毁，以回收不需再使用的资源。

子窗口是限定在主窗口范围内，是属于主窗口的私有资源，一般泛指各种控件：如按钮、复选框、进度条、列表框…等等。在主窗口创建时，可同时为其创建子窗口/控件。灵活运用emXGUI的子窗口/控件相关机制，可以极大提升应用程序代码资源的重用率用高可扩展性。比如，用户可对已有控件的默认行为及外观进行改变；或者用
户需自定义制作一款特殊的私有控件；甚至用户可以将一个复杂的窗口程序制作成一个控件来供使用，比如可以将一个完整播放器的界面控制程序都做成一个控件，以后只要在需要的地方，直接创建这个控件子窗口就可以了…限于本章篇幅，这里不作详说，后续将有章节会详细讲解这些机制的应用实例。当一个控件不需要再使用，用户也同
样可以对其进行删除/销毁；另外在这里，用户需要了解的一项规则是：一个窗口所属的私有资源（如控件，定时器），用户即便不删除/销毁它，当它的被拥有宿主窗口在删除/销毁时，它的私有资源也会被强制删除/销毁。用一个通俗点的方式描述就是：用户创建了一个主窗口A，并为其创建了一个按钮控件B，一个定时器C，当主窗
口A要结束并退出时，用户就算不删除按钮控件B和定时器C，GUI内部也会对这些未释放的资源进行强制删除/销毁。

窗口内部区域及坐标系统
^^^^^^^^^^^^^^^^^^^^^^

窗口内部区域分为客户区与非客户区。窗口最外边的区域为非客户区，是包括了标题栏，窗口边框。非客户区的绘制内容，默认是由GUI内部处理的，用户可以不去关心，除非用户需要自行定制窗口非客户的外观。除开非客户区之外的地方，称为客户区，用户的绘图区域及子窗口，都是在客户区范围内。

.. image:: /media/docx017.png
   :align: center
   :alt: 图 5_2窗口类型
   :name: 图5_2

图 5‑2 窗口区域

emXGUI的坐标以像素为单位，X轴向右为正，Y轴向下为正。按不同的窗口区域，坐标系分为屏幕坐标(Screen)，窗口坐标(Window)，客户坐标(Client)。这三类坐标系最明显区别在于坐标原点:屏幕坐标原点在显示设备的第一个物理像素点位置;窗口坐标原点在整个窗口(包括非客户区)的最左上角;客
户坐标在窗口客户区的最左上角。屏幕坐标，窗口坐标，客户坐标之间可以相互转换的，emXGUI给用户提供了相关的API函数，详细请参考API章节(ScreenToClient，WindowToClient，ClientToScreen，…)。在窗口非客户区绘图，应使用GetWindowDC来获得绘图上下
文(DC)， 非客户区的DC，使用的是窗口坐标，坐标原点在窗口最左上角，可以在整个窗口内绘制。在客户区内绘图，
使用BeginPaint或GetDC(后续章节会介绍BeginPaint与GetDC的区别)。
客户区DC使用的是客户区坐标，坐标原点为客户区最左上角，客户区DC只会在客户区范围内绘图，超出这
个范围内的绘图内容，将会被自动裁减掉。

消息机制概述
^^^^^^^^^^^^^^^^^^

emXGUI是以窗口为基础，以消息传递为运转机制的多窗口系统。通过消息机制，窗口可以响应来自输入设备(键盘，鼠标，触摸屏)的动作，
如按键弹起/按下，鼠标/触摸屏位置改变。消息也可以在窗口与窗口间传递，以实现窗口间的交互动作。窗口在创建时，GUI内部会对其绑定一个所属的消息队列(这个过程动作是不需要用
户干预的)。在主窗口创建后，在一个循环里执行获取消息(GetMessage)，派发消息(DispatchMessage)，
这样便是整个用户窗口系统的消息泵正常运转了， 获得到的消息将派发到所属窗口的窗口过程函数(WndProc)中。

消息发送方式
^^^^^^^^^^^^^^^^^^

向某个指定的窗口发送消息，按发送方式，可分为同步发送消息(SendMessage)和
异步发送消息(PostMessage/PostAsyncMessage) 。

同步消息发送也称为阻塞发送，发送消息时，会阻塞当前线程，直到该消息被目标窗口处理完成后，该函数才会返回，
当前线程才能得以继续运行；同步消息是不会进入消息队列的，直接发送到了目标窗口的窗口过程函数。
见 代码清单5_3_。示例中的函数参数分别是目标窗口的句柄，消息类型，wParam与lParam。

.. code-block:: c
    :caption: 代码清单5_3 同步发送消息(SendMessage)示例
    :linenos:
    :name: 代码清单5_3

     SendMessage(hwnd,LB_GETTEXT,i,(LPARAM)wbuf);

相反，异步消息发送为非阻塞方式，被发送的消息只是投放目标窗口所属的消息队列中，而不等该消息是否被目标窗口处理便立即返回。emXGUI给用户提供了两个异步发送消息的函数：PostMessage和PostAsyncMessage。这两个函数的区别是:PostMessage发送的消息队列容量长度是固定的，
当这个队列消息已满的情况下，便不能再接收新的消息，也就是说在这个情况下，PostMessage因消息队列容量已满将会丢弃掉新的消息。一个很典型的情况：当窗口被另一个高优先级的任务长时间阻塞时，如果一直往这个窗口PostMessage，那么到一定程度下，该窗口所属的消息队列便会被填满，使得不能再接收到
新的PostMessage。而PostAsyncMessage情况则不同，PostAsyncMessage的发送消息队列容量是不固定的，
可以理解为是一个不限长度的可动态增加的链表结构。
每次PostAsyncMessage都将会在消息队列增加一条消息，
除非GUI内核的动态内存已消耗完。

消息接收与派发(窗口消息循环)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

在用户创建完一个主窗口后，最后将在一个循环中调用GetMessage从消息队列中获取消息。GetMessage是一个阻塞性获取消息的函数，
只有消息队列中有消息时，该函数才会返回，并将获取的消息填充到一个MSG的结构体中，见 代码清单5_4_
MSG结构体成员（文件emXGUI.。随后调用DispatchMessage函数将该获取到消息派发到目标窗口过程函数中处理，这个过程也称作为窗口消息循环。消息派发到哪个窗口，这是不需要用户干预的， MSG
结构体中的hwnd参数，已经指明了消息派往的目标窗口。需要注意一点的事，前面说到同步发送的消息(SendMessage)是不会进入消息队列的，而是直接发送到了窗口过程函数(WndProc)，所以GetMessage是不会获取到SendMessage发出的消息的。

.. code-block:: c
    :caption: 代码清单 5_4 MSG结构体成员（文件emXGUI.h）
    :linenos:
    :name: 代码清单5_4

    typedef struct tagMSG {
        HWND    hwnd;    //目标窗口
        UINT  message; //消息
        WPARAM  wParam;  //参数0
        LPARAM  lParam;  //参数1
        LONG  ExtData; //扩展数据
        UINT  time;  //消息产生时间
    } MSG;

该结构体的成员变量说明如下：

1) hwnd：指明了消息派往的目标窗口，也就是目标窗口的句柄。
HWND是struct tagWINDOW*的别名。见 代码清单5_5_ HWND类型说明（文件emXGUI.。

.. code-block:: c
    :caption: 代码清单 5_5 HWND类型说明（文件emXGUI.h）
    :linenos:
    :name: 代码清单5_5

     typedef struct tagWINDOW* HWND;

2) message：用户发送消息内容，可以是常用的系统标准消息类型，也可以是用户自己定义的消息。
请注意，如果是用户自定义的消息类型，则起始值需要从WM_USER开始，见 代码清单5_6_
用户自定义消息类型（文件emXGUI.。对于用户自定义消息，wParam和lParam参数的含义也完全同用户自己约定。用户自定义的消息后，便可以像系统标准消息相同的方式来使用。比如用SendMessage或PostMessage来发送到某个指定的窗口，该窗口过程函数就会接收到用户自定义的消息。

.. code-block:: c
    :caption: 代码清单 5_6 用户自定义消息类型（文件emXGUI.h）
    :linenos:
    :name: 代码清单5_6

    #define WM_USER   0x8000 //0x8000-0xFFFF for user custom
    //用户自定义消息（emXGUI.h文件没有以下宏，只是举个例子来说明）
    #define MY_MSG_0 WM_USER+1
    #define MY_MSG_1 WM_USER+2
    #define MY_MSG_2 WM_USER+3

3) wParam和lParam：发送消息附带的参数。每个消息类型的参数都不同，可以是空值，即没有参数。

4) ExtData：

5) time：用于记录消息的产生时间，赋值过程由内部函数完成，不需要用户编写。

代码清单5_7_ 中，while循环中调用GetMessage从消息队列中获取消息。
收到消息后，调用TranslateMessage函数实现由按键消息转换产生字符消息。
最后通过DispatchMessage函数将消息发送到目标窗口。

.. code-block:: c
    :caption: 代码清单 5‑7 窗口消息循环的示例代码
    :linenos:
    :name: 代码清单5_7

    //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。
    while (GetMessage(&msg,hwnd)) /*获取消息。*/
    {
        TranslateMessage(&msg);/*消息转换,由按键消息(WM_KEYDOWN)转换产生字符消息(WM_CHAR)。*/
        DispatchMessage(&msg);/*派发消息。*/
    }

当目标窗口收到消息后，会执行消息处理回调函数。用户创建主窗口时，需要提供一个为“消息处理回调函数”的函数地址。
该函数即为窗口过程函数，是用户响应处理窗口消息的地方。
在窗口过程函数中，用户只需处理有用到消息，不用的消息可以不理会，交由系统来处理（调用DefWindowProc），见 代码清单5_8_。
窗口过程函数传入的4个形参含义，与发送消息函数的4个参数刚好是一一对应的。对于同步发送消息而言，SendMessage的返回值实际就是这个窗口过程函数处理该消息后的返回值。

.. code-block:: c
    :caption: 代码清单 5_8 窗口过程函数示例
    :linenos:
    :name: 代码清单5_8

    static LRESULT  WinProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
    {
        RECT rc;
        switch (msg) {
        case WM_CREATE: { //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口.
            GetClientRect(hwnd,&rc); //获得窗口的客户区矩形.
    //创建一个按钮(示例).
            CreateWindow(BUTTON,L"OK",WS_VISIBLE,rc.w-80,8,68,32,hwnd,ID_OK,NULL,NULL); 
        }
        return TRUE;
        ////
        //省略部分代码//
        ////
    
        default: { //用户不关心的消息,由系统处理.
            return DefWindowProc(hwnd,msg,wParam,lParam);
        }
    
        }
    
        return WM_NULL;
    }

标准消息类型及参数说明
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

WM_CREATE
^^^^^^^^^^^^^^^^^^

WM_CREATE消息。当窗口被创建时，会收到WM_CREATE消息，用户可以在该消息里做一些初始化操作或创建子窗口。

.. code-block:: c
    :caption: 代码清单 5_9 示例程序1
    :linenos:
    :name: 代码清单5_9

    void GUI_DEMO(void)
    {
        //创建主窗口；
        //创建子控件1；
        //创建子控件2；
        //省略一些内容
        //创建子控件10；
        //消息循环；
    }

.. code-block:: c
    :caption: 代码清单 5_10 示例程序2
    :linenos:
    :name: 代码清单5_10

    LRESULT win_proc(HWND hwnd,UINT msg,
            WPARAM wParam,LPARAM lParam)
    {
    switch(msg)
        {
            case WM_CREATE:
                //创建子控件1；
                //创建子控件2；
                //省略一些内容
                //创建子控件10；
            return TRUE;
        }
    }

对比一下 代码清单5_9_ 和 代码清单5_10_ ，两种代码都可以实现同一个功能：创建控件。但是 代码清单5_10_
是在GUI_DEMO这个函数中定义控件。如果我们需要十几个控件的话，就会显得GUI_DEMO_Button函数的内容特别多，影响美观。因此将创建子窗口放在WM_CREATE消息中，使得代码条理清晰，内容明确。

WM_TIMER
^^^^^^^^^^^^^^^^

利用emXGUI的定时器，我们就可以做一些炫酷的时钟桌面，如 图5_3_。

.. image:: /media/docx018.jpg
   :align: center
   :alt: 图 5_3 时钟样式
   :name: 图5_3

创建定时器API，见 代码清单5_11_ 。

.. code-block:: c
    :caption: 代码清单5_11 创建定时器API（文件emXGUI.h）
    :linenos:
    :name: 代码清单5_11

    HTMR SetTimer(HWND hwnd,UINT TMR_Id,U32 IntervalMS,U32 Flags,TIMERPROC Proc);

1) hwnd（输入）： 定时器所属窗口句柄，当定时器达到设定值时，该窗口会收到 WM_TIMER 消息。

2) TMR_Id（输入） ：定时器ID，用于区分多个定时标识。

3) IntervalMS（输入）：定时间隔时间，单位:毫秒。

4) Flags（输入）：标记，可以是以下组合：单次触发定时器（TMR_SINGLE），若没有指定单次触发定时器，则定时器为循环定时触发模式。TMR_START负责启动定时器。

5) Proc（输入）：定时器超时回调函数，可以为NULL。如果指定回调函数，窗口将不会收到WM_TIMER。

.. code-block:: c
    :caption: 代码清单 5‑12 定时器示例（文件GUI_DEMO_Timer.c）
    :linenos:
    :name: 代码清单5_12

    case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口
    {
        GetClientRect(hwnd,&rc); //获取窗口坐标       
        CreateWindow(BUTTON,L"OK",WS_VISIBLE,
                rc.w-70,rc.h-40,68,32,hwnd,ID_OK,NULL,NULL);
        SetTimer(hwnd,0,1000,TMR_START,NULL);
        return TRUE;
    }

    case WM_TIMER:
    {
        time++;        
        InvalidateRect(hwnd ,NULL,TRUE); //发送WM_PAINT消息
        break;
    }  

    case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
    {
        PAINTSTRUCT ps;
        HDC hdc;      
        hdc =BeginPaint(hwnd,&ps);  
        x_wsprintf(wbuf, L"Time(s):%d", time); 
        TextOut(hdc,300,200,wbuf,-1); //显示时间
        EndPaint(hwnd,&ps);
        break;
    }

    case WM_CLOSE:
    {
        time = 0;
        DestroyWindow(hwnd); //调用DestroyWindow函数来销毁窗口（该函数会产生WM_DESTROY消息）。
        return TRUE; //关闭窗口返回TRUE。
    }

代码清单5_12_，WM_CREATE消息中创建一个1s定时器，设置为循环定时触发定时器，开启定时器。

当1s的延时到达时，窗口会接收到WM_TIMER消息。在WM_TIMER消息中，time自增，同时调用InvalidateRect函数发送WM_PAINT消息，使窗口重绘更新时间。

在WM_PAINT消息中，调用TextOut函数将时间变量的值显示在屏幕（300，200）处。调用该函数前，需要将显示的文字，使用x_wsprintf函数进行格式化。

当窗口退出时，窗口会收到WM_CLOSE消息。在WM_CLOSE消息中将记录时间的变量清零。调用DestroyWindow函数来销毁窗口。

实验结果如 图5_4_ 所示，屏幕显示当前的时间，为249s。

.. image:: /media/docx019.jpeg
   :align: center
   :alt: 图 5_4 实验结果
   :name: 图5_4

除了使用SetTimer创建定时器来实现延时，也可以使用RTT系统的延时函数GUI_msleep，函数定义见 代码清单5_13_。区别在于使用GUI_msleep时，该进程会放弃CPU的使用权，直到延时结束。延时的整个过程中，窗口不会接收到任何消息，也就是屏幕无法实时显示定时值。GUI_msleep就
好比是一个无法触发中断的定时器，没有相应的中断服务函数，而SetTimer的定时器，WM_TIMER就是它的中断服务函数。因此，我们在使用的时候，要注意到这一点，选择合适的延时函数。

.. code-block:: c
    :caption: 代码清单 5_13 GUI_msleep函数（文件X_GUI_RTT.c）
    :linenos:
    :name: 代码清单5_13

    /*
    函数功能: 延时函数
    参数: ms: 延时时间(单位:毫秒) 
    返回: 无
    说明: 
    */
    void  GUI_msleep(u32 ms)
    {
        ms=rt_tick_from_millisecond(ms);
        rt_thread_delay(ms);
    }

WM_ERASEBKGND
^^^^^^^^^^^^^^^^^^^^^^^^^^

窗口移动时，需要先擦除背景，再对窗口客户区的内容进行重绘，否则的话，就会出现窗口重影的现象。这里我们先讲解一下背景擦除，图5_5_ 中，当窗口1从处移动到处的过程中，桌面背景依然会显示处的内容。因此，我们需要进行桌面背景擦除。这时候，窗口会收到该消息WM_ERASEBKGND。

.. image:: /media/docx020.jpg
   :align: center
   :alt: 图 5‑5 窗口移动
   :name: 图5_5

.. code-block:: c
    :caption: 代码清单 5_14 桌面背景清除示例程序
    :linenos:
    :name: 代码清单5_14

    case  WM_ERASEBKGND:
    {
        //画矩形（0，0，LCD宽，LCD高）；//清除桌面
        //显示文字（“桌面”）；
    }
    return TRUE;

代码清单5_14_，这里只是负责清除桌面背景，暂时没有涉及窗口重绘。所谓的桌面清除，其实就是画一个起点为（0，0），大小和桌面大小一样的矩形，再显示桌面的内容，这里显示的是桌面两个汉字。请读者注意，窗口的重绘不是在桌面背景清除消息中执行的。最终结果如 图5_6_。

.. image:: /media/docx021.jpg
   :align: center
   :alt: 图 5‑6 桌面背景清除
   :name: 图5_6

.. _创建桌面-1:

创建桌面
~~~~~~~~~~~~

桌面，父窗口都属于窗口，都可以使用WNDClass这个结构体来配置。该结构体成员用来设置窗口的风格、回调函数、光标样式等等，并调用GUI_CreateDesktop创建桌面，或者是CreateWindowEx来创建父窗口。WNDClass结构体定义在emXGUI.h文件中。

WNDClass窗口结构体详解
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

WNDClass结构体定义在emXGUI.h文件中，具体定义如下：

.. code-block:: c
    :caption: 代码清单 5_15 WNDClass结构体（文件emXGUI.h）
    :linenos:
    :name: 代码清单5_15

    typedef struct tagWNDCLASS{
        U32       Tag;          //必须设置为 WNDCLASS_TAG值。
        U32       Style;        //窗口类风格。
        WNDPROC   lpfnWndProc;  //窗口过程函数。
        U32       cbClsExtra;   //窗口类扩展数据大小。
        U32       cbWndExtra;   //窗口扩展数据大小。
        HINSTANCE hInstance;
        HICON     hIcon;        //图标
        HCURSOR   hCursor;      //光标
    
    } WNDCLASS;

1) Tag：窗口类型标签。创建桌面，窗口时，该成员变量的值必须设置为 WNDCLASS_TAG，该成员变量主要是用来区分窗口和子控件。

2) Style：窗口类风格。默认是CS_HREDRAW和CS_VREDRAW，当窗口发送改变时，会自动发送重绘消息WM_PAINT。CS_HREDRAW表示如果改变了客户区域的高度，则重绘整个窗口。CS_VREDRAW表示如果改变了客户区域的宽度，则重绘整个窗口。

3) lpfnWndProc：指向窗口过程函数的指针。窗口过程函数，用于处理发送到窗口的消息。

4) cbClsExtra：窗口类扩展数据大小，指定在窗口类结构之后分配的额外字节数，一般设置为0。

5) cbWndExtra：窗口扩展数据大小，指定窗口实例之后要分配的额外字节数，一般设置为0。

6) hInstance：应用程序实例句柄， 目前GUI版本为保留参数， 应设置为NULL。

7) hIcon：窗口图标，该成员指向图标资源的句柄，一般设置为NULL。

8) hCursor：桌面光标。该成员必须是游标资源的句柄，一般设置为NULL。

创建桌面函数详解
^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c
    :caption: 代码清单 5_16 创建桌面函数GUI_CreateDesktop
    :linenos:
    :name: 代码清单5_16

    HWND GUI_CreateDesktop(U32 dwExStyle, const WNDClass *wcex, LPCWSTR lpWindowName,
            U32 dwStyle, int x, int y, int nWidth, int nHeight,
            HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);

1) dwExStyle：指定窗口的扩展样式。可以是WS_EX_LOCKPOS（窗口不能拖动）、WS_EX_LOCKZORDER（窗口不能通过点击来改变Z序）。这里的Z序指的是窗口在屏幕上显示时的前后顺序。

2) wcex：指向窗口配置结构体的指针，用来配置窗口的样式和回调函数。

3) lpWindowName：窗口的名称，即窗口的标题。注意，这里一定要使用的宽字符串，每个字符占用两个字节。在C语言中，采用L”字符串”，来表示宽字符串。

4) dwStyle：窗口样式。主要是负责窗口的外形。可以是以下选项：WS_DISABLED（窗口创建后，不会响应输入设备的事件）、WS_CLIPCHILDREN（父窗口重绘时，对子窗口进行重绘）、WS_VISIBLE（窗口创建后，默认是可见的）、WS_BORDER（窗口会带有小边框）、WS_DLG
FRAME（窗口会带有大边框）、WS_CAPTION（窗口会带有标题栏）、WS_OWNERDRAW（用户自定义样式）。这些选项可以同时使用。

5) x, y, nWidth, nHeight：指定窗口的位置和大小。

6) hwndParent：指向该窗口的父窗口句柄， 如果是创建主窗口， 则设为NULL。

7) WinId：窗口ID，用于对多个窗口进行标识区分，如果是创建主窗口，则忽略该参数，设为0。

8) hInstance：应用程序实例句柄， 目前版本为保留参数， 应设置为NULL。

9) lpParam：窗口创建时， 用户自定义参数，如果不使用， 可以忽略该参数，设为NULL。

创建桌面实验
~~~~~~~~~~~~~~~~~~

设计要求
^^^^^^^^^^^^

用户可以设计自己的桌面背景，可以是图片桌面，也可以是纯颜色背景。青菜萝卜，各有喜爱。例程中采用RGB（32，72，144）的颜色作为背景颜色，在桌面（20，20）处显示字符串（emXGUI\@Embedfire STM32F429），
见 图5_7_。图片是采用Excel表格绘制的，下面我们一起学习，如何将 图5_7_ 变成我们的桌面。

.. image:: /media/docx022.jpg
   :align: center
   :alt: 图 5_7 桌面效果
   :name: 图5_7

代码设计
^^^^^^^^^^^^

这里只讲解核心的部分代码，有些变量的设置，头文件的包含等并没有涉及到，完整的代码请参考本章配套的工程。

编程要点
'''''''''''

1) 配置WNDCLASS窗口结构体，调用GUI_CreateDesktop创建桌面窗口

2) 实现消息循环

3) 编写窗口回调函数，完成对消息的处理。

每一个界面都可以按照上述三个步骤，进行程序编写，这是基础的框架。区别在于第三步，这里可以自由发挥，脑洞有多大，界面就有多炫酷，这是正比例关系。

代码分析
''''''''''''

(1) 创建桌面代码分析

GUI_Startup函数初始化了GUI依赖的各种设备后，在末尾调用了示例函数GUI_DesktopStartup创建桌面。

(2) 桌面窗口回调代码分析

桌面窗口在创建的时候，会创建一个定时器用来检测触摸屏的输入，以及创建一个新的App线程。见 代码清单5_17_。

.. code-block:: c
    :caption: 代码清单 5_17 窗口回调函数desktop_proc（gui_desktop.c文件）
    :linenos:
    :name: 代码清单5_17

    /**
    * @brief  桌面回调函数
    * @param  hwnd 当前处理该消息的窗口对象句柄
    * @param  msg 消息类型值，用以标识和区分当前产生的消息
    * @param  wParam 消息参数值，根据msg消息代码值不同
    * @param  lParam 消息参数值，根据msg消息代码值不同
    * @retval 返回给SendMessage的值
    */
    static   LRESULT    desktop_proc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
    {
    switch(msg)
    {
        /* 桌面创建时,会产生该消息,可以在这里做一些初始化工作. */
        case  WM_CREATE:  
            ////创建1个20ms定时器，处理循环事件.
            SetTimer(hwnd,1,20,TMR_START,NULL);
            //创建App线程           
            if(1)
            {
                rt_thread_t h;
                h=rt_thread_create("GUI_APP",gui_app_thread,NULL,2048,5,5);
                rt_thread_startup(h);       
            }

            break;
        /* 定时处理输入设备的信息 */
        case  WM_TIMER:
        #if(GUI_INPUT_DEV_EN)
            {
            u16 id;

            id =LOWORD(wParam);
            if(id==1)
            {
                GUI_InputHandler(); //处理输入设备
            }
            }
        #endif
        break;
        /* 客户区背景需要被擦除 */
        case  WM_ERASEBKGND:
        {
        HDC hdc =(HDC)wParam;
        _EraseBackgnd(hdc,NULL,hwnd);
        }
        return TRUE;
        /* 用户不关心的信息，由系统处理 */
        default:
            return  DefDesktopProc(hwnd,msg,wParam,lParam);
    }
    return WM_NULL;
    }

1) WM_CREATE消息

当执行完GUI_CreateDesktop之后，会执行WM_CREATE这个case的内容：调用SetTimer函数创建一个20ms的定时器，调用rt_thread_create创建App线程，见 代码清单5_18_。

.. code-block:: c
    :caption: 代码清单 5_18 创建App线程rt_thread_create函数（gui_desktop.c文件）
    :linenos:
    :name: 代码清单5_18

    static  void  gui_app_thread(void *p)
    {
    #if(GUI_TOUCHSCREEN_EN & GUI_TOUCHSCREEN_CALIBRATE)
        {
            int i=0;
            while (TouchPanel_IsPenDown())
            {
                GUI_msleep(100);
                if (i++>10) {
                    ShowCursor(FALSE);
                    TouchScreenCalibrate(NULL);
                    ShowCursor(TRUE);
                    break;
                }
            }
        }
    #endif

        /* 调用APP函数 */
        GUI_AppMain();
    //   GUI_UserAppStart();
    //    ShellWindowStartup();
        //  return 0;
    }

#if(GUI_TOUCHSCREEN_EN & GUI_TOUCHSCREEN_CALIBRATE)是条件编译，由于我们使用的是电容屏，不需要校准，因此GUI_TOUCHSCREEN_CALIBRATE为0。GUI_TOUCHSCREEN_EN为是否使能触摸屏，这里为1。所以#if的内容不执行。紧
接着调用GUI_AppMain函数，我们自己定义的界面是放在此处执行的。

2) WM_TIMER消息

当定时器计数达到设定值时，执行检测触摸屏的输入。见 代码清单5_19_

.. code-block:: c
    :caption: 代码清单 5_19桌面的过程函数之case： WM_TIMER（文件gui_desktop.c）
    :linenos:
    :name: 代码清单5_19

    /* 定时处理输入设备的信息 */
    case  WM_TIMER:
    #if(GUI_INPUT_DEV_EN)
    {
        u16 id;
        id =LOWORD(wParam);
        if (id==1) {
            GUI_InputHandler(); //处理输入设备
        }
    }
    #endif
    break;

#if(GUI_INPUT_DEV_EN)是条件编译，GUI_INPUT_DEV_EN为是否使用输入设备，这里设置为1。函数LOWORD是取数据的低16位。WM_TIMER消息中，带有wParam参数。这里将wParam参数，也就是定时器的
ID值赋给id变量。WM_CREATE消息中我们创建的定时器的ID是1，如果读取的ID是1，则执行GUI_InputHandler处理输入设备（这里我们只用到了触摸屏）。

.. code-block:: c
    :caption: 代码清单 5_20 触摸处理函数（文件gui_touch_port.c）
    :linenos:
    :name: 代码清单5_20

    /**
    * @brief  需要被定时调用的触摸处理函数
    * @note   本例子中通过gui_input_port.c文件的GUI_InputHandler被定时调用
    * @param  无
    * @retval 无
    */
    void  GUI_TouchHandler(void)
    {
        int act;
        POINT pt;

        /* 判断触摸状态及坐标 */
        act =TouchDev_GetPoint(&pt);
        if (act==TS_ACT_DOWN) {
            /* 触摸按下，使用触摸坐标作为输入 */
            MouseInput(pt.x,pt.y,MK_LBUTTON);
        }

        if (act==TS_ACT_UP) {
            /* 触摸释放，使用当前光标作为输入*/
            GetCursorPos(&pt);
            MouseInput(pt.x,pt.y,0);
        }
    }

代码清单5_20_ 触摸处理函数（文件gui_touch_port.中，调用GUI_TouchHandler来获取触摸状态以及触摸坐标，保存在pt结构体中。

3) WM_ERASEBKGND消息

.. code-block:: c
    :caption: 代码清单5_21 桌面的过程函数之case：WM_ERASEBKGND（文件gui_desktop.c）
    :linenos:
    :name: 代码清单5_21

    /* 客户区背景需要被擦除 */
    case  WM_ERASEBKGND:
    {
        HDC hdc =(HDC)wParam;
        _EraseBackgnd(hdc,NULL,hwnd);
    }
    return TRUE;

当桌面创建完成后，会发送该消息，来绘制桌面。接收该消息时，会收到wParam参数，见 代码清单5_21_。调用_EraseBackgnd来绘制桌面。见 代码清单5_22_ 桌面背景绘制函数（文件gui_desktop.。

.. code-block:: c
    :caption: 代码清单 5_22 桌面背景绘制函数（文件gui_desktop.c）
    :linenos:
    :name: 代码清单5_22

    /**
    * @brief  桌面背景绘制函数，触发背景绘制时会调用本函数，
                通过修改本函数的内容可更改桌面的背景
    * @param  hdc 绘图上下文
    * @param  lprc 要绘制的矩形区域，为NULL时会自动绘制hwnd的客户区
    * @param  hwnd 窗口对象句柄
    * @retval 无
    */
    static  void  _EraseBackgnd(HDC hdc,const RECT *lprc,HWND hwnd)
    {
        RECT rc;
    
        if (lprc==NULL) {
            GetClientRect(hwnd,&rc);
        } else {
            CopyRect(&rc,lprc);
        }
        SetBrushColor(hdc,MapRGB(hdc,32,72,144));
        FillRect(hdc,&rc);
        SetTextColor(hdc,MapRGB(hdc,250,250,250));
    //  /* 居中显示结果 */
    //  DrawText(hdc,L"Hello emXGUI@Embedfire!",-1,&rc,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
        
        TextOut(hdc,20,20,L"emXGUI@Embedfire STM32F429 ",-1);
    }

调用GetClientRect函数来获取客户区的坐标，由于程序传进来的形参为NULL，所以绘制的区域为整个客户区。调用FillRect函数，设置桌面背景颜色为RGB(32,72,144)，调用TextOut在（20，20）处显示字符串：emXGUI\@Embedfire
STM32F429，字体颜色为RGB(250,250,250)。字体显示函数有两个：DrawText和TextOut。DrawText可以设置字体显示的格式，是左对齐，右对齐或者居中。而TextOut不行。相关的函数说明，请参考《emXGUI API编程手册》的绘图API章节。

4) default消息

这个消息是指一些我们并不关心的系统消息，我们就可以调用DefWindowProc这个函数来完成。见 代码清单5_23_ 。

.. code-block:: c
    :caption: 代码清单 5_23 default消息响应
    :linenos:
    :name: 代码清单5_23

    default:
        return DefWindowProc(hwnd,msg,wParam,lParam);

到这里为止，桌面回调函数已经讲完了。

实验现象
^^^^^^^^^^^^

利用我们的桌面截图DEMO，可以对我们的屏幕进行截图，如 图5_8_ ，这就是一系列操作后得到的桌面。是不是和 图5_7_ 的样子一模一样

.. image:: /media/docx023.jpg
   :align: center
   :alt: 图 5‑8 桌面显示效果
   :name: 图5_8

