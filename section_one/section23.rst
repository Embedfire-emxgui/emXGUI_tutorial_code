.. vim: syntax=rst

显示png图片
--------------

PNG（Portable Network Graphics）是一种新兴的网络图像格式。1999年，Unisys公司进一步中止了对自由软件和非商用软件开发者的GIF专利免费许可，从而使PNG格式获得了更多的关注。PNG是目前保证最不失真的格式，采用LZ77算法的派生算法进行压缩，能把图像文件压缩到极限
以利于网络传输，但又能保留所有与图像品质有关的信息。 PNG同样支持透明图片的制作，图23_1_ 就是一种透明的png格式的图片。

.. image:: /media/docx108.png
   :align: center
   :alt: 图 23‑1 png图片
   :name: 图23_1

图 23‑1 png图片

显示png图片（数据在内部存储空间）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

下表列出了PNG 绘制API函数。

表格 23‑1 PNG 绘制API

=============== ==================
函数            描述
=============== ==================
PNG_Open()      获取PNG_DEC句柄
PNG_GetBitmap() 把图片转换成bitmap
PNG_Close()     释放绘图句柄
=============== ==================

PNG 绘制API
^^^^^^^^^^^^^^^^^^

PNG_Open
''''''''''''''''

PNG_Open来获取PNG_DEC句柄，函数原型见 代码清单23_1_。

.. code-block:: c
    :caption: 代码清单 23‑1 PNG_Open函数（文件emxgui_png.h）
    :linenos:
    :name: 代码清单23_1

     PNG_DEC* PNG_Open(const u8 *png_dat,int png_size);

1) png_dat：图片所在的缓冲区，使用软件生成的图片数组的数组名；

2) png_size：图片数组的大小，可以使用sizeof获取数组的大小。

PNG_GetBitmap
'''''''''''''

emXGUI显示PNG图片的方式，是通过将PNG格式的图片，转换成BMP格式，利用显示位图的API函数来显示图片，函数原型，见 代码清单23_2_。

.. code-block:: c
    :caption: 代码清单 23‑2 PNG_GetBitmap函数（文件emxgui_png.h）
    :linenos:
    :name: 代码清单23_2

     BOOL PNG_GetBitmap(PNG_DEC *png_dec,BITMAP *bm);

1) png_dec：PNG_DEC句柄，由PNG_Open函数生成；

2) bm：位图结构体，存放着位图数据的大小，格式、图像数据等；

PNG_Close
'''''''''

PNG_Close用来释放绘图句柄，函数原型见 代码清单23_3_。

.. code-block:: c
    :caption: 代码清单 23‑3 PNG_Close函数（文件emxgui_png.h）
    :linenos:
    :name: 代码清单23_3

     void PNG_Close(PNG_DEC *png_dec);

1) png_dec：要释放的PNG_DEC句柄。

注意，这个函数操作与JPG的释放绘图句柄有所不同，只有当读者不再使用与PNG_DEC句柄相关的操作，包括不再使用PNG_GetBitmap函数生成的位图结构体，才可以释放绘图句柄，因此，该函数只有在窗口退出时进行调用，即放在WM_DESTROY消息中使用。

显示png图片实验
^^^^^^^^^^^^^^^^^^

学习了绘制上述的PNG图片绘制API之后，我们开始编写代码，将 图23_1_ 显示在屏幕上。

.. _代码分析-17:

代码分析
''''''''''''

(1) 窗口回调函数

-  WM_CREATE

.. code-block:: c
    :caption: 代码清单 23‑4 WM_CREATE消息（文件GUI_DEMO_DrawPNG.c）
    :linenos:
    :name: 代码清单23_4

     case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口
     {
        u8 *jpeg_buf;
        u32 jpeg_size;
        JPG_DEC *dec;

        GetClientRect(hwnd,&rc); //获得窗口的客户区矩形
        /* 根据图片数据创建PNG_DEC句柄 */
        png_dec = PNG_Open((u8 *)redfish, redfish_size());

        /* 把图片转换成bitmap */
        PNG_GetBitmap(png_dec, &png_bm);

        res = FS_Load_Content(DEMO_JPEG_FILE_NAME, (char **)&jpeg_buf, &jpeg_size);
        if(res)
        {
            /* 根据图片数据创建JPG_DEC句柄 */
            dec = JPG_Open(jpeg_buf, jpeg_size);
            /* 读取图片文件信息 */
            JPG_GetImageSize(&pic_width, &pic_height,dec);

            /* 创建内存对象 */
            hdc_mem =CreateMemoryDC(SURF_SCREEN,pic_width,pic_height);

            /* 绘制至内存对象 */
            JPG_Draw(hdc_mem, 0, 0, dec);

            /* 关闭JPG_DEC句柄 */
            JPG_Close(dec);
        }
        /* 释放图片内容空间 */
        RES_Release_Content((char **)&jpeg_buf);
        return TRUE;
     }

在WM_CREATE消息中，调用PNG_Open创建PNG_DEC句柄，以后的一切操作都可以使用PNG_DEC句柄来实现，同时通过PNG_GetBitmap将图片转换成bitmap，存放在png_bm结构体变量中。
这里我们使用JPG图片作为背景，更好地突出 图23_1_ 是张带透明度的图片。
使用FS_Load_Content函数从SD卡读取sea.jpg的图片数据。JPG_Open创建一个新的图片句柄，同时绘制图片数组到MemoryDC中。

-  WM_ERASEBKGND

.. code-block:: c
    :caption: 代码清单 23‑5 WM_ERASEBKGND消息（文件GUI_DEMO_DrawPNG.c）
    :linenos:
    :name: 代码清单23_5

     case WM_ERASEBKGND:
     {
        HDC hdc=(HDC)wParam;
        BitBlt(hdc,0,0,pic_width,pic_height,hdc_mem,0,0,SRCCOPY); //将MEMDC输出到窗口中。
        return TRUE;
    }

WM_ERASEBKGND消息中，使用BitBlt块传输函数将背景图片，绘制到屏幕HDC上。

-  WM_PAINT

.. code-block:: c
    :caption: 代码清单 23‑6 WM_PAINT消息（文件GUI_DEMO_DrawPNG.c）
    :linenos:
    :name: 代码清单23_6

     case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
     {
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rc0;
        int x=0,y=0;
        hdc =BeginPaint(hwnd,&ps);
        ////用户的绘制内容...
        GetClientRect(hwnd,&rc0);

        for(y=0; y<rc0.h; y+=png_bm.Height)
        {
            for(x=0; x<rc0.w; x+=png_bm.Width)
            {
                /* 显示图片 */
                DrawBitmap(hdc, x, y, &png_bm, NULL);
            }
        }
        EndPaint(hwnd,&ps);
        break;
     }

WM_CREATE消息里面，我们使用PNG_GetBitmap函数将图片转换成位图，存放在png_bm结构体变量中，因此，在WM_PAINT中，调用DrawBitmap就可以完成显示PNG格式的图片。

-  WM_DESTROY

.. code-block:: c
    :caption: 代码清单 23‑7 WM_DESTROY消息（文件GUI_DEMO_DrawPNG.c）
    :linenos:
    :name: 代码清单23_7

     case WM_DESTROY: //窗口销毁时，会自动产生该消息，在这里做一些资源释放的操作.
     {
        /* 关闭PNG_DEC句柄 */
        PNG_Close(png_dec);
        DeleteDC(hdc_mem);
        return PostQuitMessage(hwnd); //调用PostQuitMessage，使用主窗口结束并退出消息循环.
     }

当窗口关闭时，意味着我们不再使用PNG_DEC句柄和png_bm结构体变量，此时就可以调用PNG_Close函数，将PNG_DEC句柄释放，同时释放MEMDC的内存空间，如代码清单 23‑7。

.. _实验现象-10:

实验现象
''''''''''''

图23_2_ 就是我们绘制的结果，用户可以在WM_ERASEBKGND消息替换背景图片。

.. image:: /media/docx109.jpg
   :align: center
   :alt: 图 23‑2 实验结果
   :name: 图23_2

图 23‑2 实验结果

显示外部png图片
~~~~~~~~~~~~~~~~~~

由于png图片是调用位图的API来进行绘制的，本节的知识点与绘制外部bmp的内容大同小异，这里就不讲解绘图的API了，有疑问的话，可以查看绘制外部bmp图片的章节。

显示外部png图片实验
^^^^^^^^^^^^^^^^^^^^^^

.. _代码分析-18:

代码分析
''''''''''''

(1) 窗口回调函数

-  WM_CREATE

.. code-block:: c
    :caption: 代码清单 23‑8 WM_CREATE消息（文件GUI_DEMO_DrawPNG_Extern.c）
    :linenos:
    :name: 代码清单23_8

     case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口
     {
        u8 *png_buf;
        u32 png_size;
        u8 *jpg_buf;
        u32 jpg_size;
        GetClientRect(hwnd,&rc); //获得窗口的客户区矩形
        #if(RES_PIC_DEMO)
        /* 资源设备中加载 */

        res = RES_Load_Content(DEMO_PNG_FILE_NAME, (char **)&png_buf, &png_size);
        #else
        /* SD文件系统加载 */
        res = FS_Load_Content(DEMO_PNG_FILE_NAME, (char **)&png_buf, &png_size);
        #endif
        if(res)
        {
            /* 根据图片数据创建PNG_DEC句柄 */
            png_dec = PNG_Open(png_buf, png_size);
            /* 把图片转换成bitmap */
            PNG_GetBitmap(png_dec, &png_bm);
        }
        /* 释放图片内容空间 */
        RES_Release_Content((char **)&png_buf);

        res = FS_Load_Content(DEMO_JPEG_FILE_NAME, (char **)&jpg_buf, &jpg_size);
        if(res)
        {
            jdec = JPG_Open(jpg_buf, jpg_size);
            JPG_GetImageSize(&pic_width, &pic_height, jdec);
            hdc_mem = CreateMemoryDC(SURF_SCREEN,pic_width,pic_height);
            JPG_Draw(hdc_mem,0,0,jdec);
            JPG_Close(jdec);
        }
        /* 释放图片内容空间 */
        RES_Release_Content((char **)&jpg_buf);

        return TRUE;
    }

RES_PIC_DEMO宏定义决定程序从什么位置读取PNG图片，代码中的RES_PIC_DEMO为0，即从SD卡读取图片数据。根据读取成功的图片数据，调用PNG_Open函数创建图片句柄，通过PNG_GetBitmap转换为位图格式，存放在png_bm结构体中，完成之后释放PNG图片句柄。

这里也使用sea.jpg作为窗口背景，使用FS_Load_Content读取SD卡中的sea.jpg图片数据，存放在jpg_buf中。创建一个MemoryDC，大小为图片的尺寸，将图片数据绘制到MemoryDC中，最后释放图片所占用的内存和JPG图片句柄。

-  WM_PAINT

.. code-block:: c
    :caption: 代码清单 23‑9 WM_PAINT 消息（文件GUI_DEMO_DrawPNG_Extern.c）
    :linenos:
    :name: 代码清单23_9

     case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
     {
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rc0;
        int x=0,y=0;
        hdc =BeginPaint(hwnd,&ps);
        ////用户的绘制内容...
        GetClientRect(hwnd,&rc0);

        /* 若正常加载了图片 */
        if(res)
        {
            for(y=0; y<rc0.h; y+=png_bm.Height)
            {
                for(x=0; x<rc0.w; x+=png_bm.Width)
                {
                    /* 显示图片 */
                    DrawBitmap(hdc, x, y, &png_bm, NULL);
                }
            }
        }
        EndPaint(hwnd,&ps);
        break;
     }

WM_PAINT消息中， PNG图片已经转换成位图，存放在png_bm结构体中，调用DrawBitmap来显示图片。WM_PAINT消息绘制前，需要调用BeginPaint函数，结束时需要使用EndPaint函数。

-  WM_DESTROY

.. code-block:: c
    :caption: 代码清单 23‑10 WM_DESTROY消息（文件GUI_DEMO_DrawPNG_Extern.c）
    :linenos:
    :name: 代码清单23_10

     case WM_DESTROY: //窗口销毁时，会自动产生该消息，在这里做一些资源释放的操作.
     {
        /* 关闭PNG_DEC句柄 */
        PNG_Close(png_dec);
        return PostQuitMessage(hwnd); //调用PostQuitMessage，使用主窗口结束并退出消息循环.
     }

退出窗口时，需要调用PNG_Close来释放PNG_DEC句柄。

最后，将设计的主窗口函数加入到GUI_AppMain函数中。

.. _实验结果-9:

实验结果
''''''''''''

实验现象如 图23_3_，与上一节的实验结果一模一样。

.. image:: /media/docx109.jpg
   :align: center
   :alt: 图 23‑3 实验结果
   :name: 图23_3

图 23‑3 实验结果
