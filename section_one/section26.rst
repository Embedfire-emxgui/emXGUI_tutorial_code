.. vim: syntax=rst

如何制作字库
------------------

熟悉字符的编码后，我们学习如何制作字库文件。emXGUI支持的字库文件为*.xft类型的文件，可以使用XBF字体制作工具X_GUI_SIM.exe（位于过程目录下\\ \\emxgui\tools），这里我们以simfang.ttf为例。

.. image:: /media/docx116.jpg
   :align: center
   :alt: 图 26‑1 文件目录
   :name: 图26_1

图 26‑1 文件目录

工具介绍
~~~~~~~~~~~~

.. image:: /media/docx117.jpg
   :align: center
   :alt: 图 26‑2 工具界面图
   :name: 图26_2

图 26‑2 工具界面图

运行X_GUI_SIM.exe程序，会得到 图26_2_ 的界面图片。具体操作步骤：

1. 选择字体文件

这里我们以simfang.ttf文件为例，该文件存放在XBF字体制作工具\font目录下，见 图26_3_ 的处。单击处按键，选择simfang.ttf，如 图26_3_ 的处所示。

.. image:: /media/docx118.jpg
   :align: center
   :alt: 图 26‑3 选择字体文件
   :name: 图26_3

图 26‑3 选择字体文件

2. 生成的字体范围

假如现在只需要使用字母Q，W，E，R，我们可以只生成一个只含有字母Q，W，E，R的xft文件，具体做法：新建一个txt文件，内容为
QWER。注意，Q前面有一个空格，一般情况下，会保留空格的编码。另外，索引文件要使用ucs-2_little_edition编码。我们可以使用Notepad++来进行设置，
.如 图26_5_ 。最后在 图26_2_ 的处选择刚刚新建的txt文件。

本章使用的simfang.ttf，这里以所有的字符编码为例，其txt文档（位于XBF字体制作工具\font目录下），如 图26_4_ 所示，包含了所有的数字，字母还有中文等编码

.. image:: /media/docx119.jpeg
   :align: center
   :alt: 图 26‑4 txt文档内容
   :name: 图26_4

图 26‑4 txt文档内容

.. image:: /media/docx120.jpg
   :align: center
   :alt: 图 26‑5设置编码
   :name: 图26_5

图 26‑5设置编码

单击处的按键，选择生成的字体范围，如 图26_6_。

.. image:: /media/docx121.jpg
   :align: center
   :alt: 图 26‑6 选择生成的字体范围
   :name: 图26_6

图 26‑6 选择生成的字体范围

3. 选择输出路径

点击 图26_7_ 的 1 处，选择输出的xft文件的保存路径，注意，在处输入文件名时，需要手动输入.
xft后缀。

.. image:: /media/docx122.jpg
   :align: center
   :alt: 图 26‑7 选择路径
   :name: 图26_7

图 26‑7 选择路径

4. 设置输出的格式

点击 图26_8_ 的 1 处，弹出选项框Setting。处用来设置字体的大小，处主要是设置字体抗锯齿度，emXGUI最高可提供8 BPP，我们通常选择4BPP，处都是些默认参数，不需要修改。Xoff和Yoff负责字体的偏移。DPI代表图像每英寸面积内的像素点数。

.. image:: /media/docx123.jpg
   :align: center
   :alt: 图 26‑8 选择字体格式
   :name: 图26_8

图 26‑8 选择字体格式

这里解释一下什么叫抗锯齿？在这之前，需要先知道什么叫锯齿现象。图26_9_ 是图像的原始尺寸。当图像放大时，由于图像的像素点与图像的尺寸是相关的，因此就出现了锯齿现象，类似于楼梯的形状，如 图26_10_ 的下半部分。

.. image:: /media/docx124.jpeg
   :align: center
   :alt: 图 26‑9 原始尺寸“印刷”
   :name: 图26_9

图 26‑9 原始尺寸“印刷”

.. image:: /media/docx125.jpg
   :align: center
   :alt: 图 26‑10 放大的“印刷”
   :name: 图26_10

图 26‑10 放大的“印刷”

抗锯齿是一种消除图物边缘出现凹凸锯齿的技术，就是将图像边缘及其两侧的像素颜色进行混合得到的新点，用来替换原来位置上的点以达到平滑边缘，达到消除锯齿的效果。抗锯齿程度越高 ，计算时间越长，但是效果越好。如 图26_11_ 的下半部分，这是设置抗锯齿（边缘平滑化）之后放大的效果图。

.. image:: /media/docx126.jpg
   :align: center
   :alt: 图 26‑11 抗锯齿效果图
   :name: 图26_11

图 26‑11 抗锯齿效果图

5. 开始生成

经过前四步的设置之后，单击 图26_2_ 的 5 处，就可以生成xft文件了，操作成功的结果，如图 26‑12所示。在输出文件夹下，会有一个新的xft文件。这里我选择的输出路径是XBF字体制作工具\Out中，xft文件的名字为wildfire.xtf，注意输入xft文件时，一定要自己输入xft后缀。

.. image:: /media/docx127.jpg
   :align: center
   :alt: 图 26‑12 txt文档内容
   :name: 图26_12

图 26‑12 生成结果

6. 测试生成的字体

X_GUI_SIM.exe提供测试生成字体的功能，使用方法如 图26_13_ 所示。单击 图26_13_ 处的Test按键，在弹出的对话框中选择刚刚生成的xft文件。这里我们选择的上面生成的wildfire.
xft文件。测试的结果如 图26_14_ 所示，读者可以和 图26_2_ 对比一下。

.. image:: /media/docx128.jpg
   :align: center
   :alt: 图 26‑13 测试方法
   :name: 图26_13

图 26‑13 测试方法

.. image:: /media/docx129.jpg
   :align: center
   :alt: 图 26‑14测试结果
   :name: 图26_14

图 26‑14测试结果

最后，将我们生成的xft文件，放到我们的SD卡中，如 图26_15_ 。这里统一放到根目录下的文件夹srcdata中。读者也可以选择其他的文件夹，但是程序需要进行修改，建议初学者依葫芦画瓢。

.. image:: /media/docx130.jpg
   :align: center
   :alt: 图 26‑15 添加字库文件至SD卡中
   :name: 图26_15

图 26‑15 添加字库文件至SD卡中

到这里为止，就完成字库的制作，接下来，我们看一下如何在emXGUI使用我们刚刚生成的字库。

使用字库
~~~~~~~~~~~~

相关函数API
^^^^^^^^^^^^^^

SetFont
''''''''''''''

SetFont函数用来设置显示的字体格式，我们通过调用这个函数，可以切换至我们生成的字体，函数原型见 代码清单26_1_ SetFont函数（文件emXGUI.h）。

.. code-block:: c
    :caption: 代码清单 26‑1 SetFont函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单26_1

     HFONT SetFont(HDC hdc,HFONT hFont);

1) hdc：绘图上下文；

2) hFont：字体句柄。字体句柄是通过XFT_CreateFontEx函数来创建；

此外，该函数还会返回旧的字体句柄，我们可以利用这个返回值，进行两种字体的切换。

GetFont
'''''''

调用GetFont函数会返回当前正在使用的字体，函数原型，见代码清单 26‑2 GetFont函数（文件emXGUI.h）。

.. code-block:: c
    :caption: 代码清单 26‑2 GetFont函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单26_2

     HFONT GetFont(HDC hdc);

1) hdc：绘图上下文；

XFT_CreateFont
''''''''''''''

.. code-block:: c
    :caption: 代码清单 26‑3 XFT_CreateFont函数（文件GUI_Font_XFT.h）
    :linenos:
    :name: 代码清单26_3

     HFONT XFT_CreateFont(const void *xft_dat);

1) xft_dat：字体数据，可以使用bin2c工具可以将字库文件（.xtf后缀文件）生成C语言的数组，可以放在内部FLASH中。

font_read_data_SDCARD
'''''''''''''''''''''

font_read_data_SDCARD函数从SD卡读取字库文件，得到的字体数组存放在buf中。

.. code-block:: c
    :caption: 代码清单 26‑4 font_read_data_SDCARD函数（文件gui_font_port.c）
    :linenos:
    :name: 代码清单26_4

    BOOL font_read_data_SDCARD(char** buf, u32 size)

     {
<<<<<<< HEAD
     /* file objects */
     FIL *file;
     FRESULT fresult;
     BOOL result = TRUE;
     UINT br;
     file =(FIL*)GUI_VMEM_Alloc(sizeof(FIL));

     fresult = f_open(file, GUI_DEFAULT_SDCARD_FONT, FA_OPEN_EXISTING | FA_READ );

     size = f_size(file);
     /* 文件内容空间 */
     *buf = (char *)GUI_VMEM_Alloc(size);
     fresult = f_read(file, *buf, size, &br);
     /* 关闭文件 */
     f_close(file);

     /* 释放空间 */
     GUI_VMEM_Free(file);

     return result;
=======
        /* file objects */
        FIL *file;
        FRESULT fresult;
        BOOL result = TRUE;
        UINT br;
        file =(FIL*)GUI_VMEM_Alloc(sizeof(FIL));

        fresult = f_open(file, GUI_DEFAULT_SDCARD_FONT, FA_OPEN_EXISTING | FA_READ );

        size = f_size(file);
        /* 文件内容空间 */
        *buf = (char *)GUI_VMEM_Alloc(size);
        fresult = f_read(file, *buf, size, &br);
        /* 关闭文件 */
        f_close(file);

        /* 释放空间 */
        GUI_VMEM_Free(file);

        return result;
>>>>>>> dev
     }

f_open函数的参数GUI_DEFAULT_SDCARD_FONT是我们的字库文件名字，见 代码清单26_5_。如果我们存放的字库文件不是这个文件的话， 则需要修改该宏定义。

.. code-block:: c
    :caption: 代码清单26_5 GUI_DEFAULT_SDCARD_FONT宏定义（文件gui_drv_cfg.h）
    :linenos:
    :name: 代码清单26_5

     #define GUI_DEFAULT_SDCARD_FONT "0:srcdata/GB2312_16_4BPP.xft"

调用f_read函数，读取字库文件数据，需要读取的数据大小，为整个文件的的大小，通过f_size函数可以得到文件的大小。最后f_close函数关闭文件，同时释放文件句柄的空间。

使用字库实验
^^^^^^^^^^^^^^^^^^

.. _实验要求-2:

实验要求
''''''''''''

本章节的例程代码与Textout类似，区别在于WM_PAINT消息的处理：在一个窗口中，同一个文本，使用两种字体进行显示，如 图26_16_ 实验要求。

.. image:: /media/docx131.jpg
   :align: center
   :alt: 图 26‑16 实验要求
   :name: 图26_16

图 26‑16 实验要求

.. _代码分析-21:

代码分析
''''''''''''

(1) 创建字体句柄

.. code-block:: c
    :caption: 代码清单 26‑6 GUI_Default_FontInit （文件gui_font_port.c）
    :linenos:
    :name: 代码清单26_6

     HFONT GUI_Default_FontInit(void)
     {

<<<<<<< HEAD
     HFONT hFont=NULL;
     //此处省略一些代码
     #elif (GUI_USE_SDCARD_FONT)
     {
     /* 指向缓冲区的指针 */
     static u8 *pFontData_XFT=NULL;

     u32 fsize;

     if(hFont==NULL)
     {
     res = font_read_data_SDCARD((char **)&pFontData_XFT, fsize);
     hFont_SDCARD = XFT_CreateFont(pFontData_XFT);
     }

     }
     #endif
     /* 若前面的字体加载失败，使用内部FLASH中的数据（工程中的C语言数组）
     * 添加字体数据时，把数组文件添加到工程，在本文件头添加相应字体数组的声明，
     * 然后调用XFT_CreateFont函数创建字体即可
     */
     if(hFont==NULL)
     {
     /* 从本地加载(本地数组数据) */
     hFont =XFT_CreateFont(GUI_DEFAULT_FONT); /* ASCii字库,20x20,4BPP抗锯齿*/
     /* 中文字库存储占用空间非常大，不推荐放在内部FLASH */
     //hFont =XFT_CreateFont(GB2312_16_2BPP); /* GB2312字库,16x16,2BPP抗锯齿*/
     //hFont =XFT_CreateFont(GB2312_20_4BPP); /* GB2312字库,20x20,4BPP抗锯齿*/
     }
     return hFont;
=======
        HFONT hFont=NULL;
        //此处省略一些代码
    #elif (GUI_USE_SDCARD_FONT)
        {
        /* 指向缓冲区的指针 */
        static u8 *pFontData_XFT=NULL;

        u32 fsize;

        if(hFont==NULL)
        {
            res = font_read_data_SDCARD((char **)&pFontData_XFT, fsize);
            hFont_SDCARD = XFT_CreateFont(pFontData_XFT);
        }

        }
    #endif
        /* 若前面的字体加载失败，使用内部FLASH中的数据（工程中的C语言数组）
        * 添加字体数据时，把数组文件添加到工程，在本文件头添加相应字体数组的声明，
        * 然后调用XFT_CreateFont函数创建字体即可
        */
        if(hFont==NULL)
        {
            /* 从本地加载(本地数组数据) */
            hFont =XFT_CreateFont(GUI_DEFAULT_FONT); /* ASCii字库,20x20,4BPP抗锯齿*/
            /* 中文字库存储占用空间非常大，不推荐放在内部FLASH */
            //hFont =XFT_CreateFont(GB2312_16_2BPP); /* GB2312字库,16x16,2BPP抗锯齿*/
            //hFont =XFT_CreateFont(GB2312_20_4BPP); /* GB2312字库,20x20,4BPP抗锯齿*/
        }
        return hFont;
>>>>>>> dev
     }

这里使用了条件编译，只有打开GUI_USE_SDCARD_FONT这个宏，见 代码清单26_7_，emXGUI才会从SD卡读取字库文件。

.. code-block:: c
    :caption: 代码清单 26_7 GUI_USE_SDCARD_FONT宏定义（文件gui_drv_cfg.h）
    :linenos:
    :name: 代码清单26_7

     #define GUI_USE_SDCARD_FONT 1

例程中创建了两种字体句柄，见 代码清单26_8_ 。默认的字体是由XFT_CreateFont函数创建的，而字体wildfire是由font_read_data_SDCARD函数从SD卡中读取的字库文件之后，调用XFT_CreateFont函数创建。

.. code-block:: c
    :caption: 代码清单 26_8 字体类型（文件gui_drv_cfg.h）
    :linenos:
    :name: 代码清单26_8

     #define GUI_DEFAULT_SDCARD_FONT "0:srcdata/wildfire.xft"

     /* 默认内部字体数组名，USE_EXTERN_FONT为0或 外部字体加载失败时会采用的字体 */

     #define GUI_DEFAULT_FONT ASCII_20_4BPP

(2) 窗口回调函数

-  WM_PAINT

.. code-block:: c
    :caption: 代码清单 26‑9 WM_PAINT消息（文件GUI_DEMO_TextOut.c）
    :linenos:
    :name: 代码清单26_9

     case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
     {
<<<<<<< HEAD
     PAINTSTRUCT ps;
     HDC hdc;
     RECT rc;
     int i,t,y;
     WCHAR wbuf[128];

     GetClientRect(hwnd,&rc);

     hdc =BeginPaint(hwnd,&ps); //开始绘图

     ////用户的绘制内容...
     SetTextColor(hdc,MapRGB(hdc,10,10,100));
     t=GUI_GetTickCount();
     y=24;
     i=0;
     while(y<rc.h)
     {
     if(i == 11)//11行的后面使用wildfire字体文件
     {
     old_hfont = SetFont(hdc, hFont_SDCARD);
     }
     TextOut(hdc,10,y,L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",-1);
     y+=20;

     i++;
     }
     t =GUI_GetTickCount()-t;

     SetTextColor(hdc,MapRGB(hdc,250,10,10));
     SetFont(hdc, old_hfont);
     if(rc.w < 300)
     {
     x_wsprintf(wbuf,L"Time:%dms; %.1fms/line",t,(float)t/(float)i);
     }
     else
     {
     x_wsprintf(wbuf,L"TextOut Time used:%dms; %.1fms/line",t,(float)t/(float)i);
     }
     TextOut(hdc,10,4,wbuf,-1);
     EndPaint(hwnd,&ps); //结束绘图
     break;
=======
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rc;
        int i,t,y;
        WCHAR wbuf[128];

        GetClientRect(hwnd,&rc);

        hdc =BeginPaint(hwnd,&ps); //开始绘图

        ////用户的绘制内容...
        SetTextColor(hdc,MapRGB(hdc,10,10,100));
        t=GUI_GetTickCount();
        y=24;
        i=0;
        while(y<rc.h)
        {
            if(i == 11)//11行的后面使用wildfire字体文件
            {
                old_hfont = SetFont(hdc, hFont_SDCARD);
            }
            TextOut(hdc,10,y,L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",-1);
            y+=20;
            i++;
        }
        t =GUI_GetTickCount()-t;

        SetTextColor(hdc,MapRGB(hdc,250,10,10));
        SetFont(hdc, old_hfont);
        if(rc.w < 300)
        {
            x_wsprintf(wbuf,L"Time:%dms; %.1fms/line",t,(float)t/(float)i);
        }
        else
        {
            x_wsprintf(wbuf,L"TextOut Time used:%dms; %.1fms/line",t,(float)t/(float)i);
        }
        TextOut(hdc,10,4,wbuf,-1);
        EndPaint(hwnd,&ps); //结束绘图
        break;
>>>>>>> dev
     }

WM_PAINT消息中，在客户区显示多行文字，内容为： “0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ”，使用宽字符型字符串。
我们使用的字体高是20，所以使每行的文本的起点y坐标偏移20个像素。前11行，使用默认字体（ASCII_20_4BPP）显示文字，
后面的所有行，使用wildfire的字体格式。调用SetFont函数，hFont_SDCARD作为参数，实现字体的切换，同时将旧字体句柄存放在old_hfont中。
显示消耗时间的文字使用默认字体进行显示，也就是调用SetFont函数，字体句柄选择旧字体句柄old_hfont。这样就可以实现一个窗口有两种文字格式的显示。

最后，将GUI_DEMO_TextOutEX函数添加到GUI_AppMain函数中即可。

.. _实验结果-12:

实验结果
''''''''''''

实验结果如 图26_17_ 实验结果所示，图26_17_ 实验结果的 1 处使用的是ASCII_20_4BPP字体，2 处使用的是wildfire字体。

.. image:: /media/docx132.jpg
   :align: center
   :alt: 图 26‑17 实验结果
   :name: 图26_17

图 26‑17 实验结果
