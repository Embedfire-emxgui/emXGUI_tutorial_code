.. vim: syntax=rst


显示jpeg图片
----------------

JPEG是Joint Photographic Experts Group(联合图像专家组)的缩写，文件后辍名为"．jpg"或"．jpeg"，
是最常用的图像文件格式，能够将图像压缩在很小的储存空间，
图像中重复或不重要的资料会被丢失，压缩比率通常在10：1到40：1之间，压缩比越大，品质就越低；相反地
，压缩比越小，品质就越好，可以把1.37Mb的BMP位图文件压缩至20.3KB，是目前最流行的图像格式。

图22_1_ 就是一张jpeg格式的图片，本章的重点在于，将这张图片显示到屏幕上，和上一节的BMP显示一样，也有两种方式：从内部存储器读取数据来显示图片和直接从外部存储器读取数据并显示图片。

.. image:: /media/docx105.jpg
   :align: center
   :alt: 图 22‑1虎啸山林图
   :name: 图22_1

图 22‑1虎啸山林图

显示jpeg图片（数据在内部存储空间）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. _绘图api-2:

绘图API
^^^^^^^^^^^^^^^

emXGUI提供了一些JPEG的函数（位于emXGUI_JPEG.h文件），见 表格22_1_。

.. _表格22_1:

表格 22_1 emXGUI提供的JPEG的函数

================== ===============
函数名             描述
================== ===============
JPG_Open()         获取JPG_DEC句柄
JPG_GetImageSize() 获取图片的宽高
JPG_Draw()         绘制图片
JPG_Close()        释放绘图句柄
================== ===============

JPG_Open（）
''''''''''''''''''''

JPG_Open函数用于获取图片句柄，调用该函数后，会生成一个JPG_DEC句柄，之后的所有操作，都可以利用该句柄来实现。函数声明，见 代码清单22_1_。

.. code-block:: c
    :caption: 代码清单 22‑1 JPG_Open函数（文件emXGUI_JPEG.h）
    :linenos:
    :name: 代码清单22_1

     JPG_DEC* JPG_Open(const void *dat,int cbSize);

1) dat：图片所在的缓冲区，一般是使用软件生成图片数组的数组名；

2) cbSize：图片数组的大小，可以使用sizeof()函数获得；

JPG_GetImageSize（）
''''''''''''''''''''''''''''''''''''

JPG_GetImageSize函数用于获取图片的宽高，函数声明，见 代码清单22_2_。

.. code-block:: c
    :caption: 代码清单 22‑2 JPG_GetImageSize函数（文件emXGUI_JPEG.h）
    :linenos:
    :name: 代码清单22_2

     BOOL JPG_GetImageSize(U16 *width,U16 * height,JPG_DEC* jdec);

1) width、height：图片的宽度、高度

2) jdec：图片的句柄，通过JPG_Open函数生成。

JPG_Draw（）
''''''''''''''''''''

JPG_Draw函数用于绘制图片，函数声明，见 代码清单22_3_ 。

.. code-block:: c
    :caption: 代码清单 22‑3 JPG_Draw函数（文件emXGUI_JPEG.h）
    :linenos:
    :name: 代码清单22_3

     BOOL JPG_Draw(HDC hdc,int x,int y,JPG_DEC *jdec);

1) hdc：绘图上下文，类似于图层；为了实现更好视觉效果，通常将图片绘制到MemoryDC中，再使用BitBlt位块传输函数绘制至屏幕图层。

2) x、y：图片的显示坐标；

3) jdec：图片的句柄，通过JPG_Open函数生成。

JPG_Close（）
''''''''''''''''''''''

JPG_Close函数用于释放绘图句柄，函数声明，见 代码清单22_4_。

.. code-block:: c
    :caption: 代码清单 22‑4 JPG_Close函数（文件emXGUI_JPEG.h）
    :linenos:
    :name: 代码清单22_4

     void JPG_Close(JPG_DEC *jdec);

1) jdec：图片的句柄，通过JPG_Open函数生成。

显示jpeg图片实验（数据在内部FLASH）
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. _代码分析-15:

代码分析
''''''''''''

-  窗口回调函数

-  WM_CREATE

.. code-block:: c
    :caption: 代码清单 22‑5 WM_CREATE消息（文件GUI_DEMO_DrawJPEG.c）
    :linenos:
    :name: 代码清单22_5

     case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口
     {
     JPG_DEC *dec;
     GetClientRect(hwnd,&rc); //获得窗口的客户区矩形
     /* 根据图片数据创建JPG_DEC句柄 */
     dec = JPG_Open(tiger_jpg, tiger_jpg_size());
     /* 读取图片文件信息 */
     JPG_GetImageSize(&pic_width, &pic_height,dec);
     /* 创建内存对象 */

     hdc_mem =CreateMemoryDC(SURF_SCREEN,pic_width,pic_height);
     /* 绘制至内存对象 */
     JPG_Draw(hdc_mem, 0, 0, dec);
     /* 关闭JPG_DEC句柄 */
     JPG_Close(dec);
     CreateWindow(BUTTON,L"OK",WS_VISIBLE,
     rc.w-70,rc.h-40,68,32,hwnd,ID_OK,NULL,NULL);
     return TRUE;
     }

定义一个JPG_EDC变量，存放图片句柄。例程的图片数据的数组名为tiger_jpg，且定义函数tiger_jpg_size来获取数组的大小，见 代码清单22_7_。

.. code-block:: c
    :caption: 代码清单 22‑6 tiger_jpg_size函数（文件tiger_jpg.c）
    :linenos:
    :name: 代码清单22_6

     unsigned int tiger_jpg_size(void)
     {
     return sizeof(tiger_jpg);
     }

tiger_jpg_size函数使用sizeof函数，直接返回tiger_jpg数组的大小。

调用JPG_Open创建一个图片句柄。使用CreateMemoryDC函数创建MemoryDC，这样肉眼看不到绘制的过程，也就不会“闪屏”。它的大小为图片的大小，通过JPG_GetImageSize函数读取图片文件的信息。调用JPG_Draw函数将图片数据绘制至MemoryDC中，完成后，释放图片句柄。

-  WM_PAINT

.. code-block:: c
    :caption: 代码清单 22‑7 WM_PAINT消息（文件GUI_DEMO_DrawJPEG.c）
    :linenos:
    :name: 代码清单22_7

     case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
     {
     PAINTSTRUCT ps;
     HDC hdc;
     RECT rc0;
     int x=0,y=0;
     hdc =BeginPaint(hwnd,&ps);
     ////用户的绘制内容...
     GetClientRect(hwnd,&rc0);

     for(y=0; y<rc0.h; y+=pic_height)
     {
     for(x=0; x<rc0.w; x+=pic_width)
     {
     /* 把内存对象绘制至屏幕 */
     BitBlt(hdc,x,y,pic_width,pic_height,hdc_mem,0,0,SRCCOPY);//将MEMDC输出到窗口中。
     rc.x=x;
     rc.y=y;
     rc.w=pic_width;
     rc.h=pic_height;
     DrawRect(hdc,&rc);
     }
     }
     EndPaint(hwnd,&ps);
     break;
     }

在WM_Create消息中，将图片绘制到MemoryDC中，因此，需要显示图片时，只需要将MemoryDC的内容绘制到屏幕hdc即可。WM_PAINT消息，调用BeginPaint函数开始绘图，绘图结束需调用EndPaint函数。使用BitBlt块传输函数，将内存对象绘制至屏幕。调用DrawRect
函数给图片绘制一个“画框”。

最后，将绘制的界面函数GUI_DEMO_DrawJPEG添加到AppMain中即可。

.. _实验结果-7:

实验结果
''''''''''''

实验结果如 图22_2_ 所示，单击右下角的OK键，则会退出该窗口。

.. image:: /media/docx106.jpg
   :align: center
   :alt: 图 22‑2 实验结果
   :name: 图22_2

图 22‑2 实验结果

显示外部JPEG图片
~~~~~~~~~~~~~~~~~~~~

读取图片函数
^^^^^^^^^^^^^^^^^^

.. code-block:: c
    :caption: 代码清单 22‑8 图片位置宏定义（文件GUI_DEMO_DrawJPEG_Extern.c）
    :linenos:
    :name: 代码清单22_8

     /* 为1时显示RES FLASH资源文件，为0时显示SD卡的文件 */
     #define RES_PIC_DEMO 1

     #if(RES_PIC_DEMO)
     /* FLASH资源文件加载 */
     #define DEMO_JPEG_FILE_NAME "tiger.jpg"
     #else
     /* SD文件系统加载 */
     #define DEMO_JPEG_FILE_NAME "0:srcdata/tiger.jpg"

     #endif

RES_PIC_DEMO决定从什么位置读取图片数据，为1时，则显示FLASH内的图片数据，为0则显示SD卡的文件。在gui_resource_port.c文件中，提供了从SPI_FLASH或者SD卡读取图片数据的函数。

RES_Load_Content
''''''''''''''''''''''''''''''''

RES_Load_Content函数是从SPI_FLASH中读取图片数据，函数声明，见 代码清单22_9_。

.. code-block:: c
    :caption: 代码清单 22‑9 RES_Load_Content函数（文件gui_resource_port.c）
    :linenos:
    :name: 代码清单22_9

     /**
     * @brief 从资源设备加载内容
     * @param file_name[in]: 文件名
     * @param buf[out]：加载后得到的缓冲区
     * @param size[out]：内容的大小
     * @note buf是根据内容的大小动态从VMEM中申请的，
     * 使用完毕buf后，需要调用h文件中的Release_Content函数释放buf的空间
     * @retval FALSE:失败; TRUE:成功
     */


     BOOL RES_Load_Content(char * file_name, char** buf, u32* size)
     {
     int content_offset;
     CatalogTypeDef dir;
     BOOL result = TRUE;

     content_offset = RES_GetInfo_AbsAddr(file_name, &dir);
     if(content_offset > 0)
     {
     /* 文件内容空间 */
     *buf = (char *)GUI_VMEM_Alloc(dir.size);
     if(*buf != NULL)
     {
     /* 加载数据*/
     RES_DevRead((u8 *)*buf,content_offset,dir.size);

     *size = dir.size;
     }
     else
     result = FALSE;
     }
     else
     result = FALSE;

     return result;
     }

RES_Load_Content函数有三个形参：file_name是图片的文件名；buf是读取的图片数据存放缓冲区，是根据内容的大小，调用GUI_VMEM_Alloc函数，
动态从VMEM中申请的，使用完毕buf后，需要调用Release_Content函数释放buf的空间。Size用来存放数据的大小。

数据在SPI_FLASH存放格式在第四章已经讲解过了，这里就不进行讲解。调用RES_GetInfo_AbsAddr函数来查找相应资源的信息，然后使用RES_DevRead将数据加载到数据缓冲区中，见 代码清单22_10_。

.. code-block:: c
    :caption: 代码清单 22‑10 RES_DevRead函数（文件gui_resource_port.c）
    :linenos:
    :name: 代码清单22_10

     /**
     * @brief 从设备中读取内容
     * @param buf 存储读取到的内容
     * @param addr 读取的目标地址
     * @param size 读取的数据量
     * @retval 是否读取正常
     */
     BOOL RES_DevRead(u8 *buf,u32 addr,u32 size)
     {

     GUI_MutexLock(mutex_lock,5000);

     SPI_FLASH_BufferRead(buf,addr,size);
     GUI_MutexUnlock(mutex_lock);
     return TRUE;
     }

FS_Load_Content
''''''''''''''''''''''''''''''

FS_Load_Content是用于从SD卡中加载内容，函数声明，见 代码清单22_11_。

.. code-block:: c
    :caption: 代码清单 22‑11 FS_Load_Content函数（文件gui_resource_port.c）
    :linenos:
    :name: 代码清单22_11

    /**
    * @brief 从文件系统加载内容
    * @param file_name[in]: 文件路径
    * @param buf[out]：加载后得到的缓冲区
    * @param size[out]：内容的大小
    * @note buf是根据内容的大小动态从VMEM中申请的，
    * 使用完毕buf后，需要调用h文件中的Release_Content函数释放buf的空间
    * @retval FALSE:失败; TRUE:成功
    */

     BOOL FS_Load_Content(char * file_name, char** buf, u32* size)
     {
     /* file objects */
     FIL *file;
     FRESULT fresult;
     BOOL result = TRUE;
     UINT br;

     /* 文件句柄空间 */
     file =(FIL*)GUI_VMEM_Alloc(sizeof(FIL));

     /* 打开文件 */
     fresult = f_open(file, file_name, FA_OPEN_EXISTING | FA_READ );
     if (fresult != FR_OK)
     {
     GUI_ERROR("Open file failed!");
     GUI_VMEM_Free(file);
     return FALSE;
     }

     *size = f_size(file);
     /* 文件内容空间 */
     *buf = (char *)GUI_VMEM_Alloc(*size);
     if(*buf != NULL)
     {
     /* 加载整个图片文件 */
     fresult = f_read(file, *buf, *size, &br);
     /* 关闭文件 */
     f_close(file);
     }
     else
     result = FALSE;

     /* 释放空间 */
     GUI_VMEM_Free(file);

     return result;
     }

FS_Load_Content函数也有三个形参，作用与SPI_FLASH一样。使用GUI_VMEM_Alloc申请内存，并强制转换为FIL指针类型，用来存放文件句柄。

使用f_open函数打开打开文件，根据内容的大小，动态申请内存，存放文件内容。加载完成后，调用f_close函数关闭文件，同时释放文件句柄。

显示外部JPEG图片实验
^^^^^^^^^^^^^^^^^^^^^^^^

.. _代码分析-16:

代码分析
''''''''

-  WM_CREATE

.. code-block:: c
    :caption: 代码清单 22‑12 WM_CREATE消息（文件GUI_DEMO_DrawJPEG_Extern.c）
    :linenos:
    :name: 代码清单22_12

     case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口
     {
     u8 *jpeg_buf;
     u32 jpeg_size;
     JPG_DEC *dec;
     GetClientRect(hwnd,&rc); //获得窗口的客户区矩形
     #if(RES_PIC_DEMO)
     /* 资源设备中加载 */
     res = RES_Load_Content(DEMO_JPEG_FILE_NAME, (char **)&jpeg_buf, &jpeg_size);

     #else
     /* SD文件系统加载 */
     res = FS_Load_Content(DEMO_JPEG_FILE_NAME, (char **)&jpeg_buf, &jpeg_size);
     #endif
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
     CreateWindow(BUTTON,L"OK",WS_VISIBLE,
     rc.w-70,rc.h-40,68,32,hwnd,ID_OK,NULL,NULL);
     return TRUE;
     }

WM_CREATE中，调用RES_Load_Content函数从外部设备读取图片数据，保存到数组jpeg_buf中。 JPG_Open函数用于创建JPG_DEC句柄。创建MemoryDC，大小为图片的大小
，图片的大小通过JPG_GetImageSize函数获得。最后，将图片数据绘制到MemoryDC中，并释放图片占用的内存空间，关闭JPG_DEC句柄。

-  WM_PAINT

.. code-block:: c
    :caption: 代码清单 22‑13 WM_PAINT消息（文件GUI_DEMO_DrawJPEG_Extern.c）
    :linenos:
    :name: 代码清单22_13

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
     for(y=0; y<rc0.h; y+=pic_height)
     {
     for(x=0; x<rc0.w; x+=pic_width)
     {
     /* 把内存对象绘制至屏幕 */
     BitBlt(hdc,x,y,pic_width,pic_height,hdc_mem,0,0,SRCCOPY);//将MEMDC输出到窗口中。
     rc.x=x;
     rc.y=y;
     rc.w=pic_width;
     rc.h=pic_height;
     DrawRect(hdc,&rc);
     }
     }
     }
     EndPaint(hwnd,&ps);
     break;
     }

WM_PAINT消息用来绘制图片，利用BitBlt函数将MEMDC输出到窗口中。在绘制的时候，要先调用BeginPaint函数，结束时调用EndPaint函数。

-  WM_DESTROY

.. code-block:: c
    :caption: 代码清单 22‑14 WM_DESTROY消息（文件GUI_DEMO_DrawJPEG_Extern.c）
    :linenos:
    :name: 代码清单22_3

     case WM_DESTROY: //窗口销毁时，会自动产生该消息，在这里做一些资源释放的操作.
     {
     DeleteDC(hdc_mem);
     return PostQuitMessage(hwnd); //调用PostQuitMessage，使用主窗口结束并退出消息循环.
     }

窗口销毁时，会自动产生消息WM_DESTROY，窗口退出时，注意，要将MemoryDC释放掉。

最后，将设计好的窗口函数GUI_DEMO_DrawJPEG_Extern加入GUI_AppMain函数中。

.. _实验结果-8:

实验结果
''''''''''''

图22_3_ 加载的图片数据是存放在SPI_FLASH中，显示的效果和从内部存储空间读取（ 图22_2_ ）是一样的。读者也可以尝试将宏定义RES_PIC_DEMO改为0，从SD卡加载图片的效果。

.. image:: /media/docx107.jpg
   :align: center
   :alt: 图 22‑3 实验结果
   :name: 图22_3

图 22‑3 实验结果
