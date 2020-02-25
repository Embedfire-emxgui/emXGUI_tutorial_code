.. vim: syntax=rst

显示BMP图片
--------------

emXGUI 支持的 BMP 图片显示，有两种方式：

一、从内部存储器读取数据来显示图片，显示速度较快，但需要的内存空间较多；

二、直接从外部存储器（SD卡）读取数据并显示。

.. image:: /media/docx094.png
   :align: center
   :alt: 图 21‑1 BMP图片
   :name: 图21_1

图 21‑1 BMP图片

图21_1_ 的BMP 图片0.bmp存放在工程目录下的User\app\GUI_Demo\fish中，文件大小为66.1KB，颜色格式为32位，大小是92*184。这些图片参数，是如何在BMP 图片文件中体现的？在学习如何显示BMP 图片之前，我们需要了解一下BMP 图片文件的格式。

BMP图片格式
~~~~~~~~~~~~~~

BMP文件格式，又称为位图（Bitmap）或是DIB(Device-Independent Device，设备无关位图)，是Windows系统中广泛使用的图像文件格式。BMP文件保存了一幅图像中所有的像素。

BMP格式可以保存单色位图、16色或256色索引模式像素图、24位真彩色图象，每种模式中单一像素点的大小分别为1/8字节，1/2字节，1字节和32字节。目前最常见的是256位色BMP和24位色BMP。

BMP文件格式还定义了像素保存的几种方法，包括不压缩、RLE压缩等。常见的BMP文件大多是不压缩的。

BMP文件的数据可以分为四个部分：

1) bmp文件头：存放了有关文件的格式、大小等信息；我们仅讨论24位色不压缩的BMP，所以文件头中的信息基本不需要注意，

2) 位图信息头：包括图像大小、位平面数、压缩方式、颜色索引等信息。在位图信息头之中，只有“大小”这一项对我们比较有用。图像的宽度和高度都是一个32位整数，在文件中的地址分别为0x0012和0x0016。

3) 调色板：索引与其对应的颜色的映射表。16色或256色BMP有颜色表，但在24位色BMP文件则没有，我们这里不考虑。

4) 位图数据：实际的像素数据。

因此总的来说BMP图片的优点是简单。下面来用WinHex软件(跟UltraEdit软件功能类似)来分析一下BMP图像的文件内容。

bmp文件头
^^^^^^^^^^^^

见 图21_2_，阴影部分处是文件头部信息，具体说明参考 表格21_1_。

.. image:: /media/docx095.jpg
   :align: center
   :alt: 图 21‑2文件头部信息
   :name: 图21_2

图 21‑2文件头部信息

.. _表格21_1:

表格 21‑1 bmp文件头说明

=========== ====== ============================================================= =========== ====================================================================================================================
变量名      地址   作用                                                          阴影部分处
=========== ====== ============================================================= =========== ====================================================================================================================
\                                                                                值          参数说明
bfType      00~01h 文件类型                                                      42 4D       如果是位图文件类型，必须分别为0x42 和0x4D ，0x424D=’BM’。
bfSize      02~05h 文件大小                                                      B6 08 01 00 0x000108B6 = 67766B 约等于 67k，和前面提到的文件大小一致
bfReserved1 06~07h 保留字                                                        00 00       不考虑
bfReserved2 08~09h 保留字                                                        00 00       同上
bfOffBits   0a~0dh 实际位图数据的偏移字节数，即bmp文件头，位图信息头与调色板之和 36 00 00 00 00000036h = 54，刚刚好等于我们文件头部信息（BMP文件头和位图信息头），因为我们使用的是24位位图，所以调色板的大小为0，
=========== ====== ============================================================= =========== ====================================================================================================================

3到14字节的意义可以用一个结构体来描述,见 代码清单21_1_ 。

.. code-block:: c
    :caption: 代码清单 21‑1 BMP文件信息数据结构体
    :linenos:
    :name: 代码清单21_1

     typedef struct tagBITMAPFILEHEADER
     {
<<<<<<< HEAD
     //attention: sizeof(DWORD)=4 sizeof(WORD)=2
     DWORD bfSize; //文件大小
     WORD bfReserved1; //保留字，不考虑
     WORD bfReserved2; //保留字，同上
     DWORD bfOffBits; //实际位图数据的偏移字节数，即前三个部分长度之和
=======
        //attention: sizeof(DWORD)=4 sizeof(WORD)=2
        DWORD bfSize; //文件大小
        WORD bfReserved1; //保留字，不考虑
        WORD bfReserved2; //保留字，同上
        DWORD bfOffBits; //实际位图数据的偏移字节数，即前三个部分长度之和
>>>>>>> dev
     } BITMAPFILEHEADER,tagBITMAPFILEHEADER;

位图信息头
^^^^^^^^^^

剩下的部分就是位图信息头，也就是 图21_3_ 的红标处，具体说明参考 表格21_2_ 。

.. image:: /media/docx096.jpg
   :align: center
   :alt: 图 21‑3 位图信息头
   :name: 图21_3

图 21‑3 位图信息头

.. _表格21_2:

表格 21‑2 位图信息头

=============== ====== =============================================== =========== =====================================================
变量名          地址   作用                                            阴影部分处
=============== ====== =============================================== =========== =====================================================
\                                                                      值          参数说明
biSize          0e~11h 指定结构体BITMAPINFOHEADER的长度，为40          28 00 00 00 00000028h = 40,就是说这个位图信息头的大小为40个字节。
biWidth         12~15h 位图宽，以像素为单位                            5C 00 00 00 0000005Ch = 92像素
biHeight        16~19h 位图高，以像素为单位                            B8 00 00 00 000000B8h = 184像素
biPlanes        1A~1Bh 平面数，该值总为1                               00 01       平面数:1
biBitCount      1C~1Dh 采用颜色位数，可以是1，2，4，8，16，24或 32     20 00       0020h=32位颜色格式
biCompression   1E~21h 压缩方式，可以是0，1，2，其中0表示不压缩        00 00 00    不压缩
biSizeImage     22~25h 实际位图数据占用的字节数                        00 00 00 00 图像不压缩，所以设置为0。
biXPelsPerMeter 26~29h X方向分辨率                                     13 0B 00 00 00000B13h=2835像素/米
biYPelsPerMeter 2A~2Dh Y方向分辨率                                     13 0B 00 00 00000B13h=2835像素/米
biClrUsed       2E~31h 使用的颜色数，如果为0，则表示默认值(2^颜色位数) 00 00 00 00 默认值
biClrImportant  32~35h 重要颜色数，如果为0，则表示所有颜色都是重要的   00 00 00 00 所有颜色都是重要的
=============== ====== =============================================== =========== =====================================================

位图信息头结构体，见 代码清单21_2_ 。

.. code-block:: c
    :caption: 代码清单 21‑2 位图信息头内容
    :linenos:
    :name: 代码清单21_2

     typedef struct tagBITMAPINFOHEADER
     {
<<<<<<< HEAD
     //attention: sizeof(DWORD)=4 sizeof(WORD)=2
     DWORD biSize; //指定此结构体的长度，为40
     LONG biWidth; //位图宽，说明本图的宽度，以像素为单位
     LONG biHeight; //位图高，指明本图的高度，像素为单位
     WORD biPlanes; //平面数，为1
     WORD biBitCount; //采用颜色位数，可以是1，2，4，8，16，24新的可以是32
     DWORD biCompression; //压缩方式，可以是0，1，2，其中0表示不压缩

     DWORD biSizeImage; //实际位图数据占用的字节数
     LONG biXPelsPerMeter; //X方向分辨率
     LONG biYPelsPerMeter; //Y方向分辨率
     DWORD biClrUsed; //使用的颜色数，如果为0，则表示默认值(2^颜色位数)
     DWORD biClrImportant; //重要颜色数，如果为0，则表示所有颜色都是重要的
=======
        //attention: sizeof(DWORD)=4 sizeof(WORD)=2
        DWORD biSize; //指定此结构体的长度，为40
        LONG biWidth; //位图宽，说明本图的宽度，以像素为单位
        LONG biHeight; //位图高，指明本图的高度，像素为单位
        WORD biPlanes; //平面数，为1
        WORD biBitCount; //采用颜色位数，可以是1，2，4，8，16，24新的可以是32
        DWORD biCompression; //压缩方式，可以是0，1，2，其中0表示不压缩

        DWORD biSizeImage; //实际位图数据占用的字节数
        LONG biXPelsPerMeter; //X方向分辨率
        LONG biYPelsPerMeter; //Y方向分辨率
        DWORD biClrUsed; //使用的颜色数，如果为0，则表示默认值(2^颜色位数)
        DWORD biClrImportant; //重要颜色数，如果为0，则表示所有颜色都是重要的
>>>>>>> dev
     } BITMAPINFOHEADER,tagBITMAPINFOHEADER;

由于使用的是24位的位图，所以没有调色板。而且位图的大小为92*184，和开头提到的一致。

图像像素数据
^^^^^^^^^^^^^^^^^^

本章节章节使用的是24位真彩色,则54字节之后就是像素部分，如 图21_4_ 的阴影部分处。

.. image:: /media/docx097.jpg
   :align: center
   :alt: 图 21‑4 像素数据
   :name: 图21_4

图 21‑4 像素数据

以上内容就是对BMP图像文件的介绍。想要了解更多的读者，可以上网搜索相关的内容。

生成图片数组
~~~~~~~~~~~~~~~~~~

上面的图片都是b i n文件格式，如何转换成 C数组。这就需要我们的工具：bin2c（工程目录\\ emxgui\tools中），界面图如 图21_5_ 所示。

.. image:: /media/docx098.jpg
   :align: center
   :alt: 图 21‑5 软件界面
   :name: 图21_5

图 21‑5 软件界面

它的使用方法如 图21_6_ 所示，非常的简单。

.. image:: /media/docx099.jpg
   :align: center
   :alt: 图 21‑6 使用方法
   :name: 图21_6

图 21‑6 使用方法

单击处的按钮，选择图片所在的路径；生成图片C数组，是一个.c文件，单击处的按钮，选择文件存放的位置。最后单击处的按钮，等待文件生成，如 图21_7_ 。

.. image:: /media/docx100.jpg
   :align: center
   :alt: 图 21‑7 生成文件的内容
   :name: 图21_7

图 21‑7 生成文件的内容

tagBITMAP结构体
~~~~~~~~~~~~~~~~~~~~~~~~

emXGUI使用tagBITMAP结构体来存放位图的相关信息，见 代码清单21_3_ 。

.. code-block:: c
    :caption: 代码清单 21‑3 tagBITMAP结构体（文件emXGUI.h）
    :linenos:
    :name: 代码清单21_3

     typedef struct tagBITMAP
     {
<<<<<<< HEAD
     U32 Format; // 位图格式。
     U32 Width; // 位图宽度(行)。
     U32 Height; // 位图高度(列)。
     U32 WidthBytes;// 位图图像每一行的字节数。
     LPVOID Bits; // 指向位图数据。
     COLORREF *LUT; // 颜色表,只有索引位图,BM_ALPHA4,BM_ALPHA8格式时才用到。
=======
        U32 Format; // 位图格式。
        U32 Width; // 位图宽度(行)。
        U32 Height; // 位图高度(列)。
        U32 WidthBytes;// 位图图像每一行的字节数。
        LPVOID Bits; // 指向位图数据。
        COLORREF *LUT; // 颜色表,只有索引位图,BM_ALPHA4,BM_ALPHA8格式时才用到。
>>>>>>> dev
     } BITMAP;

1) Format：位图的格式，对应位图文件的biBitCount（1C~1Dh），可以是BM_ARGB8888、BM_RGB888、BM_RGB565等等。

2) Width：位图的宽度，对应位图文件的biWidth（12~15h）

3) Height：位图的高度，对应位图文件的biHeight（16~19h）

4) WidthBytes：位图图像每一行的字节数，该值与位图的宽度和颜色格式有关系。假设位图使用的颜色格式为BM_ARGB8888，也就是说一个像素是占4个字节，乘上图片的宽度，就是图像每一行的字节数。

5) Bits：指向位图像素数据

6) LUT：颜色查找表，本章节没有使用到，赋值为NULL即可。

DrawBitmap函数
~~~~~~~~~~~~~~~~~~~~~~~~

emXGUI使用DrawBitmap函数可以在当前窗口中的指定位置绘制位图图像。函数的原型见 代码清单21_4_。

.. code-block:: c
    :caption: 代码清单 21‑4 DrawBitmap函数
    :linenos:
    :name: 代码清单21_4

     BOOL DrawBitmap(HDC hdc,int x,int y,const BITMAP *bitmap,const RECT *lpRect);

1) hdc：绘图上下文；

2) x，y：绘制图片的起始坐标；

3) bitmap：BITMA位图数据结构体参数，存放位图的大小，格式等信息；

4) lpRect：要绘制的位图区域，如果该值为NULL， 则绘制整个位图。

显示位图实验（图片在内部FLASH）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

下面介绍emXGUI第一种显示图片的方式：从内部存储器中读取数据来显示图片。

.. _设计要求-13:

设计要求
^^^^^^^^^^^^

调用DrawBitmap函数，使0.
bmp的图像铺满整个屏幕，如 图21_8_。

.. image:: /media/docx101.jpg
   :align: center
   :alt: 图 21‑8 设计要求
   :name: 图21_8

图 21‑8 设计要求

.. _代码分析-13:

代码分析
^^^^^^^^^^^^

(1) 创建父窗口

.. code-block:: c
    :caption: 代码清单 21‑5 GUI_DEMO_Drawbitmap函数（文件GUI_DEMO_Drawbitmap.c）
    :linenos:
    :name: 代码清单21_5

     void GUI_DEMO_Drawbitmap(void)
     {
<<<<<<< HEAD
     HWND hwnd;
     WNDCLASS wcex;
     MSG msg;

     /////
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
     _T("DrawBitmap(ARGB8888 Format)"),
     WS_CLIPCHILDREN,
     0,0,GUI_XSIZE,GUI_YSIZE,
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

        /////
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
        _T("DrawBitmap(ARGB8888 Format)"),
        WS_CLIPCHILDREN,
        0,0,GUI_XSIZE,GUI_YSIZE,
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

创建父窗口，标题栏为“DrawBitmap(ARGB8888 Format)”，设置winProc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

.. code-block:: c
    :caption: 代码清单 21‑6 WM_CREATE消息响应（文件GUI_DEMO_Drawbitmap.c）
    :linenos:
    :name: 代码清单21_6

     static BITMAP bm_0;
     case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口
     {
<<<<<<< HEAD
     //设置位图结构参数
     bm_0.Format = BM_ARGB8888; //位图格式
     bm_0.Width = 92; //宽度
     bm_0.Height = 184; //高度
     bm_0.WidthBytes =bm_0.Width*4; //每行字节数
     bm_0.LUT =NULL; //查找表(RGB/ARGB格式不使用该参数)

     bm_0.Bits =(void*)gImage_0; //位图数据
     return TRUE;
=======
        //设置位图结构参数
        bm_0.Format = BM_ARGB8888; //位图格式
        bm_0.Width = 92; //宽度
        bm_0.Height = 184; //高度
        bm_0.WidthBytes =bm_0.Width*4; //每行字节数
        bm_0.LUT =NULL; //查找表(RGB/ARGB格式不使用该参数)

        bm_0.Bits =(void*)gImage_0; //位图数据
        return TRUE;
>>>>>>> dev
     }

定义一个BITMAP 类型的结构体变量bm_0，前面我们讲过 图21_1_ 是32位的位图，因此，使用的颜色格式为BM_ARGB8888，宽和高为92和184，每行的字节数为宽度*4。32位色的位图，没有调试板，所以不使用查找表参数。
位图像素数据则是采用之前软件生成图片数组。注意，Bits存放的是位图的像素数据，也就是54个字节后的内容。因此，生成图像数组需要去掉前54个字节的数据。

2. WM_ERASEBKGND

.. code-block:: c
    :caption: 代码清单 21‑7 WM_ERASEBKGND消息（文件GUI_DEMO_Drawbitmap.c）
    :linenos:
    :name: 代码清单21_7

     //清除背景
     case WM_ERASEBKGND:
     {
<<<<<<< HEAD
     HDC hdc=(HDC)wParam;
     GetClientRect(hwnd,&rc);
     SetBrushColor(hdc,MapRGB(hdc,0,30,130));
     FillRect(hdc,&rc);
     return TRUE;
=======
        HDC hdc=(HDC)wParam;
        GetClientRect(hwnd,&rc);
        SetBrushColor(hdc,MapRGB(hdc,0,30,130));
        FillRect(hdc,&rc);
        return TRUE;
>>>>>>> dev
     }

这里使用WM_ERASEBKGND消息，来绘制窗口的背景：以RGB为(0,30,130)的颜色来填充背景。

3. WM_PAINT

.. code-block:: c
    :caption: 代码清单 21‑8 WM_PAINT消息（文件GUI_DEMO_Drawbitmap.c）
    :linenos:
    :name: 代码清单21_8

     case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
     {
<<<<<<< HEAD
     PAINTSTRUCT ps;
     HDC hdc;
     RECT rc0;
     int x,y;
     hdc =BeginPaint(hwnd,&ps);
     //获取客户区的位置和大小
     GetClientRect(hwnd,&rc0);

     SetPenColor(hdc,MapRGB(hdc,200,200,220));
     for(y=0; y<rc0.h; y+=bm_0.Height)
     {
     for(x=0; x<rc0.w; x+=bm_0.Width)
     {
     //绘制图片
     DrawBitmap(hdc,x,y,&bm_0,NULL);
     rc.x=x;
     rc.y=y;
     rc.w=bm_0.Width;
     rc.h=bm_0.Height;
     DrawRect(hdc,&rc);//绘制矩形
     }
     }
     EndPaint(hwnd,&ps);
     break;
=======
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rc0;
        int x,y;
        hdc =BeginPaint(hwnd,&ps);
        //获取客户区的位置和大小
        GetClientRect(hwnd,&rc0);

        SetPenColor(hdc,MapRGB(hdc,200,200,220));
        for(y=0; y<rc0.h; y+=bm_0.Height)
        {
            for(x=0; x<rc0.w; x+=bm_0.Width)
            {
                //绘制图片
                DrawBitmap(hdc,x,y,&bm_0,NULL);
                rc.x=x;
                rc.y=y;
                rc.w=bm_0.Width;
                rc.h=bm_0.Height;
                DrawRect(hdc,&rc);//绘制矩形
            }
        }
        EndPaint(hwnd,&ps);
        break;
>>>>>>> dev
     }

在WM_PAINT消息，调用BeginPaint函数开始绘图。变量x和y用来记录窗口可以显示的图片张数。利用DrawBitmap函数绘制图片，且使用DrawRect给图片绘制一个外边框。

最后，将GUI_DEMO_Drawbitmap函数加入到GUI_AppMain函数即可。

.. _实验结果-5:

实验结果
^^^^^^^^^^^^

实验结果如 图21_9_ 所示，和设计要求一模一样，每一张小图都有一个“画框”。

.. image:: /media/docx102.jpg
   :align: center
   :alt: 图 21‑9实验结果
   :name: 图21_9

图 21‑9实验结果

显示外部BMP图片实验（图片在SD卡）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

上一节，我们实现了将内部FLASH的图片数组显示到屏幕上， 92*\184的32位图片，需要92*\184*4=67712个字节的空间来存放，已经是相当大了。这一讲，我们介绍另一种方式：显示外部BMP图片，图片存放在SD卡中。

绘制位图API
^^^^^^^^^^^^^^^^^^^^^

BMP_GetInfoEx
''''''''''''''''''''''''''

emXGUI提供一个API：BMP_GetInfoEx，用来读取BMP图片的信息，函数原型见 代码清单21_9_ 。

.. code-block:: c
    :caption: 代码清单 21‑9 BMP_GetInfoEx函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单21_9

     BOOL BMP_GetInfoEx(BITMAPINFO *bm_info,GUI_GET_DATA *read_data);

1) bm_info ：输出BMP图片信息结构体，存放BMP图片的大小、格式；

2) read_data： GUI_GET_DATA结构体类型，该结构体有两个结构体成员，一个是 lParam，用户自定义的参数，该参数会作为实参传入pfReadData回调函数；另一个是pfReadData，存放用来读取数据的回调函数指针。

BMP_DrawEx
''''''''''''''''''''

使用BMP_DrawEx函数来绘制BMP图像，函数原型见代码清单 21‑10。

代码清单 21‑10 BMP_DrawEx（文件emXGUI.h）

<<<<<<< HEAD
1 BOOL BMP_DrawEx(HDC hdc,int x,int y,GUI_GET_DATA *read_data,const RECT *lprc);
=======
1 BOOL BMP_DrawEx(HDC hdc,int x,int y,GUI_GET_DATA \*read_data,const RECT \*lprc);
>>>>>>> dev

1) hdc：绘图上下文；

2) x， y：起始的绘制坐标；

3) read_data： 指向读取BMP数据源的回调函数；

4) lprc：要绘制的BMP图像矩形区域，如果设置该参数为NULL，则绘制整个BMP图像区域。

.. _设计要求-14:

设计要求
^^^^^^^^^^^^

SD卡内有一张图片（ 图21_10_ ）。使用上述的API，将它显示在屏幕上。

.. image:: /media/docx103.bmp
   :align: center
   :alt: 图 21‑10 文件头部信息
   :name: 图21_10

图 21‑10 设计要求

.. _代码分析-14:

代码分析
^^^^^^^^^^^^

(1) 创建父窗口


.. code-block:: c
    :caption: 代码清单 21‑11 GUI_DEMO_Drawbitmap_Extern函数（文件GUI_DEMO_Drawbitmap_Extern.c）
    :linenos:
    :name: 代码清单21_11

     void GUI_DEMO_Drawbitmap_Extern(void)
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
     wcex.hInstance = NULL;//hInst;
     wcex.hIcon = NULL;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);
     wcex.hCursor = NULL;//LoadCursor(NULL, IDC_ARROW);

     //创建主窗口
     hwnd =CreateWindowEx( NULL,
                            &wcex,
                            _T("DrawBitmap_Extern"),
                            /*WS_MEMSURFACE|*/WS_CAPTION|WS_BORDER|WS_CLIPCHILDREN,
                            0,0,GUI_XSIZE,GUI_YSIZE,
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
        wcex.hInstance = NULL;//hInst;
        wcex.hIcon = NULL;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);
        wcex.hCursor = NULL;//LoadCursor(NULL, IDC_ARROW);

        //创建主窗口
        hwnd =CreateWindowEx( NULL,
                                &wcex,
                                _T("DrawBitmap_Extern"),
                                /*WS_MEMSURFACE|*/WS_CAPTION|WS_BORDER|WS_CLIPCHILDREN,
                                0,0,GUI_XSIZE,GUI_YSIZE,
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

创建父窗口，标题栏为“DrawBitmap_Extern”，设置winProc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

.. code-block:: c
    :caption: 代码清单 21‑12 WM_CREATE消息（文件GUI_DEMO_Drawbitmap_Extern.c）
    :linenos:
    :name: 代码清单21_12

     case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口

     {

<<<<<<< HEAD
     HWND wnd;

     GetClientRect(hwnd,&rc); //获得窗口的客户区矩形

     /* 读取文件系统中的图片信息*/

     PIC_BMP_GetInfo_FS(&bm_0, DEMO_BMP_NAME);

     CreateWindow(BUTTON,L"OK",WS_VISIBLE,

     rc.w-70,rc.h-40,68,32,hwnd,ID_OK,NULL,NULL);



     /* 创建内存对象 */

     hdc_mem =CreateMemoryDC(SURF_SCREEN,bm_0.Width,bm_0.Height);

     /* 绘制至内存对象 */

     PIC_BMP_Draw_FS(hdc_mem,0,0,DEMO_BMP_NAME,NULL);

     return TRUE;
=======
        HWND wnd;

        GetClientRect(hwnd,&rc); //获得窗口的客户区矩形

        /* 读取文件系统中的图片信息*/

        PIC_BMP_GetInfo_FS(&bm_0, DEMO_BMP_NAME);

        CreateWindow(BUTTON,L"OK",WS_VISIBLE,

        rc.w-70,rc.h-40,68,32,hwnd,ID_OK,NULL,NULL);



        /* 创建内存对象 */

        hdc_mem =CreateMemoryDC(SURF_SCREEN,bm_0.Width,bm_0.Height);

        /* 绘制至内存对象 */

        PIC_BMP_Draw_FS(hdc_mem,0,0,DEMO_BMP_NAME,NULL);

        return TRUE;
>>>>>>> dev

     }

在WM_CREATE消息中，创建了一个BUTTON按键。创建MemoryDC，大小为图片的大小。使用MemoryDC，可以绘制图片到缓冲区，肉眼看不到绘制的过程，不会出现“闪屏”。调用PIC_BMP_GetInfo_FS函数来获取图片的消息，存放在bm_0结构体中，具体的实现方式，见 代码清单21_13_ 。

.. code-block:: c
    :caption: 代码清单 21‑13 PIC_BMP_GetInfo_FS（文件gui_picture_port.c）
    :linenos:
    :name: 代码清单21_13

     /**
     * @brief 获得BMP图像的信息(文件系统)
     * @param bm_info（输出）：存储得到的图像信息
     * @param file_name（输入）: 绘制到目标的坐标
     * @retval FALSE:失败; TRUE:成功
     */
     BOOL PIC_BMP_GetInfo_FS(BITMAPINFO *bm_info, char *file_name)
     {
<<<<<<< HEAD
     /* file objects */

     FIL *file;
     FRESULT fresult;
     BOOL res = TRUE;
     GUI_GET_DATA get_data;
    
     file =(FIL*)GUI_VMEM_Alloc(sizeof(FIL));
    
     /* 打开文件 */
     fresult = f_open(file, file_name, FA_OPEN_EXISTING | FA_READ );
     if (fresult != FR_OK)
     {
     GUI_ERROR("Open Pic failed!");
     GUI_VMEM_Free(file);
     return FALSE;
     }
     /* 把文件指针作为lParam参数*/
     get_data.lParam = (LPARAM)file;
     /* 读取数据的回调函数 */
     get_data.pfReadData = bmp_read_data_fs;
     /* 获取图片信息 */
     res = BMP_GetInfoEx(bm_info,&get_data);
     f_close(file);
    
     /* 释放空间 */
     GUI_VMEM_Free(file);
    
     return res;
=======
        /* file objects */

        FIL *file;
        FRESULT fresult;
        BOOL res = TRUE;
        GUI_GET_DATA get_data;
        
        file =(FIL*)GUI_VMEM_Alloc(sizeof(FIL));
        
        /* 打开文件 */
        fresult = f_open(file, file_name, FA_OPEN_EXISTING | FA_READ );
        if (fresult != FR_OK)
        {
            GUI_ERROR("Open Pic failed!");
            GUI_VMEM_Free(file);
            return FALSE;
        }
        /* 把文件指针作为lParam参数*/
        get_data.lParam = (LPARAM)file;
        /* 读取数据的回调函数 */
        get_data.pfReadData = bmp_read_data_fs;
        /* 获取图片信息 */
        res = BMP_GetInfoEx(bm_info,&get_data);
        f_close(file);
        
        /* 释放空间 */
        GUI_VMEM_Free(file);
        
        return res;
>>>>>>> dev
     }

调用GUI_VMEM_Alloc函数，在VMEM申请内存，并将申请到内存地址转换为FIL指针类型。使用文件之前，必须使用f_open函数打开文件，不再使用文件必须使用f_close函数关闭文件，f_close函数运行可以确保缓冲区完全写入到文件内。定义一个GUI_GET_DATA类型的结构体变量，把文件指针作为lParam参数，读取数据的回调函数设置为bmp_read_data_fs。
最后调用emXGUI提供的API：BMP_GetInfoEx来获取图片信息。bmp_read_data_fs函数，代码清单21_14_。

.. code-block:: c
    :caption: 代码清单 21‑14 bmp_read_data_fs（文件gui_picture_port.c）
    :linenos:
    :name: 代码清单21_14

     /**
     * @brief 从流媒体加载内容的回调函数(文件系统)
     * @param buf[out] 存储读取到的数据缓冲区
     * @param offset 要读取的位置
     * @param size 要读取的数据大小
     * @param lParam 调用函数时的自定义参数（用户参数）
     * @retval 读取到的数据大小
     */
     static int bmp_read_data_fs(void *buf,int offset,int size,LPARAM lParam)

     {
<<<<<<< HEAD
     int rw;

     /* 本回调函数中lParam是对应的文件指针*/
     FIL * p_file = (FIL*)lParam;

     /* 偏移到指定位置 */
     f_lseek(p_file, offset);
     /* 读取数据到缓冲区 */
     f_read(p_file, buf, (UINT)size, (UINT *)&rw);
     /* 返回读取到的数据大小 */
     return rw;
=======
        int rw;

        /* 本回调函数中lParam是对应的文件指针*/
        FIL * p_file = (FIL*)lParam;

        /* 偏移到指定位置 */
        f_lseek(p_file, offset);
        /* 读取数据到缓冲区 */
        f_read(p_file, buf, (UINT)size, (UINT *)&rw);
        /* 返回读取到的数据大小 */
        return rw;
>>>>>>> dev
     }

bmp_read_data_fs函数的形参lParam是用户自定义的参数，这里传递的是文件指针。使用文件系统函数f_lseek偏移到指定位置offset，从SD卡中读取数据到缓冲区，最后返回读取到的数据大小。

调用PIC_BMP_Draw_FS函数将图片绘制到MemoryDC，见 代码清单21_15_。

.. code-block:: c
    :caption: 代码清单 21‑15 PIC_BMP_Draw_FS（文件gui_picture_port.c）
    :linenos:
    :name: 代码清单21_15

     /**
     * @brief 显示文件系统中的BMP图片(文件系统)
     * @param hdc（输入）：绘图上下文
     * @param x，y（输入）: 绘制到目标的坐标
     * @param lprc（输入）:
     要绘制的BMP图像矩形区域，如果设置该参数为NULL，则绘制整个BMP图像区域。
     * @retval FALSE:失败; TRUE:成功
     */
     BOOL PIC_BMP_Draw_FS(HDC hdc, int x, int y, char *file_name, const RECT *lprc)

     {
     /* file objects */
     FIL *file;
     FRESULT fresult;
     BOOL res = TRUE;
     GUI_GET_DATA get_data;

     file =(FIL*)GUI_VMEM_Alloc(sizeof(FIL));

     /* 打开文件 */
     fresult = f_open(file, file_name, FA_OPEN_EXISTING | FA_READ );
     if (fresult != FR_OK)
     {
<<<<<<< HEAD
     GUI_ERROR("Open Pic failed!");
     GUI_VMEM_Free(file);
     return FALSE;
=======
        GUI_ERROR("Open Pic failed!");
        GUI_VMEM_Free(file);
        return FALSE;
>>>>>>> dev
     }

     /* 把文件指针作为lParam参数 */
     get_data.lParam = (LPARAM)file;
     /* 读取数据的回调函数 */
     get_data.pfReadData = bmp_read_data_fs;
     /* 显示图片 */
     res = BMP_DrawEx(hdc,x,y,&get_data,lprc);

     /* 关闭文件 */
     f_close(file);

     /* 释放空间 */
     GUI_VMEM_Free(file);

     return res;
     }

在PIC_BMP_Draw_FS函数中，在VMEM申请内存，并将申请到内存地址转换为FIL指针类型。调用BMP_DrawEx函数来显示图片，BMP数据源通过bmp_read_data_fs回调函数获得，最后释放申请的内存。

2. WM_NOTIFY

.. code-block:: c
    :caption: 代码清单21_16  WM_NOTIFY消息（文件GUI_DEMO_Drawbitmap_Extern.c）
    :linenos:
    :name: 代码清单21_16

     /* wParam低16位为发送该消息的控件ID,高16位为通知码;lParam指向了一个NMHDR结构体 */
     case WM_NOTIFY:
     {
<<<<<<< HEAD
     u16 code,id;
     code =HIWORD(wParam); //获得通知码类型.
     id =LOWORD(wParam); //获得产生该消息的控件ID.
     if(id==ID_OK && code==BN_CLICKED)
     {
     PostCloseMessage(hwnd); //产生WM_CLOSE消息关闭窗口

     }
     break;
=======
        u16 code,id;
        code =HIWORD(wParam); //获得通知码类型.
        id =LOWORD(wParam); //获得产生该消息的控件ID.
        if(id==ID_OK && code==BN_CLICKED)
        {
            PostCloseMessage(hwnd); //产生WM_CLOSE消息关闭窗口
        }
        break;
>>>>>>> dev
     }

WM_NOTIFY消息中的wParam低16位为发送该消息的控件ID，高16位为通知码。单击OK按键，则发送WM_CLOSE消息关闭窗口。

3. WM_ERASEBKGND

.. code-block:: c
    :caption: 代码清单 21‑17 WM_ERASEBKGND消息（文件GUI_DEMO_Drawbitmap_Extern.c）
    :linenos:
    :name: 代码清单21_17

     case WM_ERASEBKGND:
     {
<<<<<<< HEAD
     HDC hdc=(HDC)wParam;
     GetClientRect(hwnd,&rc);
     SetBrushColor(hdc,MapRGB(hdc,0,30,130));
     FillRect(hdc,&rc);
     return TRUE;
=======
        HDC hdc=(HDC)wParam;
        GetClientRect(hwnd,&rc);
        SetBrushColor(hdc,MapRGB(hdc,0,30,130));
        FillRect(hdc,&rc);
        return TRUE;
>>>>>>> dev
     }

在客户区绘制一个矩形，大小为整个客户区的大小，填充颜色设置为RGB(0，30，130)。

4. WM_PAINT

.. code-block:: c
    :caption: 代码清单 21‑18 WM_PAINT（文件GUI_DEMO_Drawbitmap_Extern.c）
    :linenos:
    :name: 代码清单21_18

     case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
     {
<<<<<<< HEAD
     PAINTSTRUCT ps;
     HDC hdc;
     RECT rc0;
     int x,y;
     hdc =BeginPaint(hwnd,&ps);//开始绘制
     ////用户的绘制内容...
     GetClientRect(hwnd,&rc0);

     SetPenColor(hdc,MapRGB(hdc,200,200,220));
     for(y=0; y<rc0.h; y+=bm_0.Height)
     {
     for(x=0; x<rc0.w; x+=bm_0.Width)
     {
     /* 显示文件系统中的图片文件 */
     BitBlt(hdc,x,y,bm_0.Width,bm_0.Height,hdc_mem,0,0,SRCCOPY); //将MEMDC输出到窗口中。
     rc.x=x;
     rc.y=y;
     rc.w=bm_0.Width;
     rc.h=bm_0.Height;
     DrawRect(hdc,&rc);
     }
     }
     EndPaint(hwnd,&ps);
     break;
=======
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rc0;
        int x,y;
        hdc =BeginPaint(hwnd,&ps);//开始绘制
        ////用户的绘制内容...
        GetClientRect(hwnd,&rc0);

        SetPenColor(hdc,MapRGB(hdc,200,200,220));
        for(y=0; y<rc0.h; y+=bm_0.Height)
        {
            for(x=0; x<rc0.w; x+=bm_0.Width)
            {
                /* 显示文件系统中的图片文件 */
                BitBlt(hdc,x,y,bm_0.Width,bm_0.Height,hdc_mem,0,0,SRCCOPY); //将MEMDC输出到窗口中。
                rc.x=x;
                rc.y=y;
                rc.w=bm_0.Width;
                rc.h=bm_0.Height;
                DrawRect(hdc,&rc);
            }
        }
        EndPaint(hwnd,&ps);
        break;
>>>>>>> dev
     }

在WM_CREATE中，已经将图片绘制到MemoryDC中，因此，我们只需要将MemoryDC中的图形拷贝到hdc中即可。调用BitBlt函数将MEMDC的（0，0）处的内容输出到窗口的（x，y）中，数据的数目由图片的大小决定。使用DrawRect函数给图片画个“画框”。

.. _实验结果-6:

实验结果
^^^^^^^^

绘制出来的界面截图如 图21_11_ 所示。

.. image:: /media/docx104.jpg
   :align: center
   :alt: 图 21‑11 实验结果
   :name: 图21_11

图 21‑11 实验结果
