.. vim: syntax=rst

显示gif图片
--------------

GIF(Graphics Interchange
Format)的原义是“图像互换格式”，是CompuServe公司开发的图像文件格式。GIF文件的数据，是一种基于LZW算法的连续色调的无损压缩格式。其压缩率一般在50%左右。
GIF格式可以存多幅彩色图像，如果把存于一个文件中的多幅图像数据逐幅读出并显示到屏幕上，就可构成一种最简单的动画，如 图24_1_。

.. image:: /media/docx110.jpg
   :align: center
   :alt: 图 24‑1 GIF图片
   :name: 图24_1

图 24‑1 GIF图片

GIF图片显示原理
~~~~~~~~~~~~~~~~~~

GIF动态图片是由多张静态图片组合而成，按照一定的顺序和时间进行播放。GIF图片有多少帧，就有多少张静态图片。
是本章节要显示的GIF图片，每一个箭头代表一个延时值。显示第一张静态图，延时delay1时长后，显示第二张，共有16张静态图片，则需要显示16次，这样就实现了动态图的效果。

.. image:: /media/docx111.jpg
   :align: center
   :alt: 图 24‑2 GIF图片
   :name: 图24_2

图 24‑2 GIF图片分解图

显示gif图片（数据在内部存储空间）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

gif图片绘制API
^^^^^^^^^^^^^^^^^^^^

表格 24‑1 绘制API

=================== =====================
函数                描述
=================== =====================
GIF_Open()          创建HGIF句柄
GIF_GetInfo()       获取GIF的图片信息
GIF_GetFrameCount() 获取GIF的帧数
GIF_GetFrameDelay() 获取GIF某一帧的延时值
GIF_DrawFrame()     绘制GIF图片
GIF_Close()         释放绘图句柄
=================== =====================

GIF_Open
''''''''

GIF_Open函数来获取HGIF句柄，函数原型见代码清单 24‑1。

.. code-block:: c
    :caption: 代码清单 24‑1 GIF_Open函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单24_1

     HGIF GIF_Open(const void *dat);

1) dat：图片所在的缓冲区，使用软件生成的图片数组

GIF_GetInfo
'''''''''''

GIF_GetInfo函数来获取GIF图片信息，函数原型见代码清单 24‑2。

.. code-block:: c
    :caption: 代码清单 24‑2 GIF_GetInfo函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单24_2

     BOOL GIF_GetInfo(HGIF hGIF,IMAGE_INFO *Info);

1) hGIF：HGIF句柄，由函数GIF_Open创建；

2) Info：GIF图片信息结构体，存放GIF的图片信息。

.. code-block:: c
    :caption: 代码清单 24‑3 IMAGE_INFO结构体（文件emXGUI.h）
    :linenos:
    :name: 代码清单24_3

     typedef struct tagIMAGE_INFO
     {
        U8 Tag[7]; //图像类型的标识
        U8 Bpp;//图像颜色位宽
        U16 Width; //图片宽度
        U16 Height;//图片高度
     }IMAGE_INFO;

这个结构体主要存放了GIF图片的一些信息， Tag参数里记录的图像的类型; 比如打开的数据是JPG图像, Tag参数里就是'J','P','G'字符标识; 如果是GIF图像,Tag参数里就是'G','I','F'。具体实现过程是由GIF_GetInfo函数来完成的，这里简单了解一下即可。

GIF_GetFrameCount
''''''''''''''''''''''''''''''''''

GIF_GetFrameDelay函数来获取GIF图片的总帧数，也就是说我们需要显示多少张图片，函数原型见 代码清单24_4_。

.. code-block:: c
    :caption: 代码清单 24‑4 GIF_GetFrameCount函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单24_4

     UINT GIF_GetFrameCount(HGIF hGIF);

1) hGIF：HGIF句柄

前面提到过， GIF图片是将多幅图像保存为一个图像文件，从而形成动画，调用GIF_GetFrameCount函数就可以得到有多少张图片，在调用下面的GIF_GetFrameDelay函数得到的延时值，进行延时，就是实现“动画”的效果了。

GIF_GetFrameDelay
'''''''''''''''''

GIF_GetFrameDelay函数用于获取GIF图片中某一帧播放时需要延时的时间，见 代码清单24_5_。

.. code-block:: c
    :caption: 代码清单 24‑5 GIF_GetFrameDelay函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单24_5

     GIF_DELAY GIF_GetFrameDelay(HGIF gif_dec,UINT frame_idx);

1) hGIF：HGIF句柄

2) frame_idx：GIF图片的某一帧的帧数值；

GIF_DrawFrame
'''''''''''''

GIF_DrawFrame函数用来绘制GIF图片的某一帧，代码原型见代码清单 24‑6。

.. code-block:: c
    :caption: 代码清单 24‑6 GIF_DrawFrame函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单24_6

     GIF_DELAY GIF_DrawFrame(HDC hdc,int x,int y,COLORREF bk_color,HGIF hGIF,UINT frame_idx);

1) hdc：绘图上下文

2) x、y：显示GIF图片的起点坐标；

3) bk_color：GIF图片的背景颜色；

4) hGIF：HGIF句柄

5) frame_idx：当前的帧数值

GIF_Close
'''''''''

当我们不再使用图片句柄时，调用GIF_Close函数来释放图片句柄，函数原型见 代码清单24_7_。

.. code-block:: c
    :caption: 代码清单 24‑7 GIF_Close函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单24_7

     void GIF_Close(HGIF hGIF);

1) hGIF：HGIF句柄

显示gif图片实验
^^^^^^^^^^^^^^^^^^

实验要求
''''''''''''

图24_3_ 是GIF图片的第一帧，使用上述的API函数，在emXGUI实现动态图的显示。

.. image:: /media/docx112.gif
   :align: center
   :alt: 图 24‑3 实验要求
   :name: 图24_3

图 24‑3 实验要求

.. _代码分析-19:

代码分析
''''''''''''

emXGUI通过在WM_PAINT中显示GIF图片的每一帧，延时一定时间，如此循环，最后实现显示GIF图片的动态效果，我们日常生活看到的GIF图片，也是这样的。

(1) 窗口回调函数

-  WM_CREATE

.. code-block:: c
    :caption: 代码清单 24‑8 WM_CREATE消息（文件GUI_DEMO_DrawGIF.c）
    :linenos:
    :name: 代码清单24_8

     case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口
     {
        GetClientRect(hwnd,&rc);
        /* 获取HGIF句柄 */
        hgif = GIF_Open(king);
        /* 获取GIF的图片信息 */
        GIF_GetInfo(hgif,&img_info);
        /* 获取GIF的帧数 */
        frame_num = GIF_GetFrameCount(hgif);

        CreateWindow(BUTTON,L"OK",WS_VISIBLE,rc.w-70,rc.h-40,68,32,hwnd,ID_OK,NULL,NULL);
        SetTimer(hwnd,0,0,TMR_SINGLE,NULL);
        return TRUE;
     }

代码清单24_8_，调用GIF_Open函数来获取HGIF句柄，参数king是使用软件生成的图像数组。使用GIF_GetInfo函数来得到图片的消息，存放在img_info结构体中。
GIF_GetFrameCount函数用来得到GIF图片的总帧数，作为循环显示的依据。最后，创建一个定时器，用来作为图片的显示延时，选择单次触发。这里设置定时时间为0，则定时器暂停工作。

-  WM_PAINT

.. code-block:: c
    :caption: 代码清单 24‑9 WM_PAINT消息（文件GUI_DEMO_DrawGIF.c）
    :linenos:
    :name: 代码清单24_9

     case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
     {
        PAINTSTRUCT ps;
        HDC hdc;
        hdc =BeginPaint(hwnd,&ps);
        GetClientRect(hwnd,&rc);
        if(hgif)
        {
            /* 创建MemoryDC */

            hdc_mem = CreateMemoryDC(SURF_SCREEN,img_info.Width,img_info.Height);
            /* 清除屏幕显示 */
            ClrDisplay(hdc_mem,NULL,MapRGB(hdc_mem,255,255,255));
            if(i>=frame_num)
            {
                i=0;
            }
            /* 绘制图片至MemoryDC */
            GIF_DrawFrame(hdc_mem,0,0,MapRGB(hdc_mem,255,255,255),hgif,i);
            BitBlt(hdc,rc.x,rc.y,img_info.Width,img_info.Height,hdc_mem,0,0,SRCCOPY); //将MEMDC输出到窗口中。
            /* 获取当前帧的延时值 */
            delay=GIF_GetFrameDelay(hgif,i);
            i++;
        }
        /* 释放MemoryDC */
        DeleteDC(hdc_mem);

        ResetTimer(hwnd,0,delay,TMR_SINGLE|TMR_START,NULL);
        EndPaint(hwnd,&ps);
        break;
     }

代码清单24_9_ 负责绘制GIF图片的每一帧，CreateMemoryDC函数创建MemoryDC，调用GIF_DrawFrame将每一帧图片绘制到MemoryDC，
然后使用BitBlt块传输输出到窗口HDC，绘制完成后，释放MemoryDC。调用GIF_GetFrameDelay获取GIF当前帧需
要延时的时间，使用ResetTimer函数，来重新设置延时时间，以及定时器的功能。

-  WM_TIMER

.. code-block:: c
    :caption: 代码清单 24‑10 WM_TIMER消息（文件GUI_DEMO_DrawGIF.c）
    :linenos:
    :name: 代码清单24_10

     case WM_TIMER:
     InvalidateRect(hwnd,NULL,FALSE);
     break;

WM_TIMER消息中，当超过延时时间时，调用InvalidateRect函数重绘窗口，实际上就是给窗口发送WM_PAINT消息。

最后，设计的GUI_DEMO_DrawGIF界面函数加入到GUI_AppMain函数中即可。

.. _实验结果-10:

实验结果
''''''''

实验结果如 图24_4_ 所示，这是GIF图片中的某一帧。具体的实验效果，读者可以下载本章的例程进行观看。

.. image:: /media/docx113.jpg
   :align: center
   :alt: 图 24‑4 实验结果
   :name: 图24_4

图 24‑4 实验结果

显示外部gif图片
~~~~~~~~~~~~~~~~~~

从外部读取图片数据，使用RES_Load_Content函数或者是FS_Load_Content函数。RES_Load_Content函数是从SPI_FLASH中读取图片，读取之前需要将图片烧写至SPI_FLASH中；而FS_Load_Content则是从SD卡中读取图片数据。这两个在前面章节已经讲
解过了，这里不进行过多的描述。使用两者中哪一个，由宏定义RES_PIC_DEMO决定。

.. code-block:: c
    :caption: 代码清单 24‑11 宏定义RES_PIC_DEMO（文件GUI_DEMO_DrawGIF_Extern.c）
    :linenos:
    :name: 代码清单24_11

     /* 为1时显示RES FLASH资源文件，为0时显示SD卡的文件 */
     #define RES_PIC_DEMO 0

     #if(RES_PIC_DEMO)
     /* FLASH资源文件加载 */
     #define DEMO_GIF_FILE_NAME "king.gif"
     #else
     /* SD文件系统加载 */
     #define DEMO_GIF_FILE_NAME "0:srcdata/king.gif"

     #endif

显示外部gif图片实验
^^^^^^^^^^^^^^^^^^^^^^

.. _实验要求-1:

实验要求
''''''''''''

实验要求和上一小节一样，区别在于上一小节图片是存放在内部FLASH中，而本节实验的图片数据是存放在SPI_FLASH或者是SD卡中，使用RES_Load_Content或者是FS_Load_Content函数来获得图片数据。

.. _代码分析-20:

代码分析
''''''''''''

(1) 窗口回调函数

-  WM_CREATE

.. code-block:: c
    :caption: 代码清单 24‑12 WM_CREATE消息（文件GUI_DEMO_DrawGIF_Extern.c）
    :linenos:
    :name: 代码清单24_12

     case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口
     {
        GetClientRect(hwnd,&rc);
        #if(RES_PIC_DEMO)
        /* 资源设备中加载 */
        res = RES_Load_Content(DEMO_GIF_FILE_NAME, (char **)&gif_buf, &gif_size);
        #else
        /* SD文件系统加载 */
        res = FS_Load_Content(DEMO_GIF_FILE_NAME, (char **)&gif_buf, &gif_size);

        #endif
        /* 获取GIF句柄 */
        hgif = GIF_Open(gif_buf);
        /* 获取GIF图片信息 */
        GIF_GetInfo(hgif,&img_info);
        /* 获取GIF图片的帧数 */
        frame_num = GIF_GetFrameCount(hgif);
        CreateWindow(BUTTON,L"OK",WS_VISIBLE,rc.w-70,rc.h-40,68,32,hwnd,ID_OK,NULL,NULL);
        SetTimer(hwnd,0,0,TMR_SINGLE,NULL);
        return TRUE;
     }

代码清单24_12_ WM_CREATE消息（文件GUI_DEMO_DrawGIF_Extern.使用FS_Load_Content函数从SD卡中读取图片数据，存放在数组gif_buf中。
调用GIF_Open函数来创建一个GIF图片句柄，图片数组gif_buf作为函数的实参。通过GIF_GetInfo函数来得到图片的尺寸，存放在img_info变量中，这里尺寸大小主要用于创建MemoryDC的大小。调用GIF_GetFrameCount函数来得到GIF图片的总帧数，读者可以将frame_num通过串口打印出来，可以看到刚刚好是16帧。创建定时器，定时时间设置为0，定时器主要用于实现GIF图片的
每一帧图片的延时，也就是 图24_2_ 的箭头。当超过设定时间时，就会发送WM_TIMER消息。在WM_TIMER消息中，调用InvalidateRect函数来实现窗口重绘，也就是绘制下一帧图片。

-  WM_PAINT

.. code-block:: c
    :caption: 代码清单 24‑13 WM_PAINT消息（文件GUI_DEMO_DrawGIF_Extern.c）
    :linenos:
    :name: 代码清单24_13

     case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
     {
        PAINTSTRUCT ps;
        HDC hdc;
        hdc =BeginPaint(hwnd,&ps);
        GetClientRect(hwnd,&rc);
        if(hgif)
        {
        /* 创建MemoryDC */

        hdc_mem = CreateMemoryDC(SURF_SCREEN,img_info.Width,img_info.Height);
        /* 清除窗口显示内容 */
        ClrDisplay(hdc_mem,NULL,MapRGB(hdc_mem,255,255,255));
        if(i>=frame_num)
        {
            i=0;
            }
            /* 绘制GIF图片 */
            GIF_DrawFrame(hdc_mem,0,0,MapRGB(hdc_mem,255,255,255),hgif,i);
            BitBlt(hdc,rc.x,rc.y,img_info.Width,img_info.Height,hdc_mem,0,0,SRCCOPY); //将MEMDC输出到窗口中。
            /* 获取GIF图片的延时值 */
            delay=GIF_GetFrameDelay(hgif,i);
            i++;
        }
        /* 释放MemoryDC */
        DeleteDC(hdc_mem);
        /*设置延时值，开启定时器 */
        ResetTimer(hwnd,0,delay,TMR_SINGLE|TMR_START,NULL);
        EndPaint(hwnd,&ps);
        break;
     }

CreateMemoryDC函数用于创建MemoryDC，将GIF图片的每一帧绘制到MemoryDC，使用BitBlt函数将MEMDC输出到窗口HDC中，最后需要释放MemoryDC。
图24_1_ 帧与帧之间存在一些重叠的内容，这里调用ClrDisplay函数，将上一帧的内容清除，再绘制下一帧。GIF_GetFrameDelay得到当前帧的延时值，
使用ResetTimer来设置定时器的延时值，开启定时器。对于例程的GIF图来说， 这个过程需要执行16次。

-  WM_DESTROY

.. code-block:: c
    :caption: 代码清单 24‑14 WM_DESTROY消息（文件GUI_DEMO_DrawGIF_Extern.c）
    :linenos:
    :name: 代码清单24_14

     case WM_DESTROY: //窗口销毁时，会自动产生该消息，在这里做一些资源释放的操作.
     {
        GIF_Close(hgif);
        return PostQuitMessage(hwnd); //调用PostQuitMessage，使用主窗口结束并退出消息循环.
     }

当窗口退出时，调用GIF_Close函数来释放GIF图片句柄。

最后，将设计好的GUI_DEMO_DrawGIF_Extern函数加入到GUI_AppMain中即可。

.. _实验结果-11:

实验结果
''''''''

图24_5_ 是GIF图片中的某一帧，具体的实验效果，读者可以下载本章的例程进行观看。

.. image:: /media/docx114.jpg
   :align: center
   :alt: 图 24‑5 实验结果
   :name: 图24_5

图 24‑5 实验结果
