.. vim: syntax=rst

前言
--

如何学习本书
~~~~~~

本书是首本系统讲解emXGUI应用的中文书籍，共分为两个部分，第一部分为“emXGUI控件应用开发”，即重点讲解emXGUI的每个控件如何使用，并将控件的显示效果在野火STM32开发板上面的液晶显示出来，让你有客观的视觉感受，而不单单是停留在代码层面。

第二部分是综合例程实战，即在第一部分学会了如何使用emXGUI控件的基础上，利用这些控件制作各种界面，控制开发板上面的外设，比如制作音乐播放器、视频播放器、万年历和图片浏览器等具有实际项目意义的实战例程。

由于第一部分是第二部分的基础，所以学习的时候，必须先学习第一部分，然后再学习第二部分，不能进行跳跃式的阅读。如果第一部分的知识没有掌握好，贸贸然就进入第二部分的实战，出现问题了，定会让你焦头烂额，正所谓基础不牢，地动山摇。

本书的参考资料
~~~~~~~

1. emXGUI 官方作者刘巍手把手指导

2. emXGUI API编程手册（电子版）

3. 《STM32库开发实战指南》（电子版）

本书的配套硬件
~~~~~~~

本书支持野火STM32开发板全套系列，具体型号见表格 0‑1，具体图片见图 0‑1、图 0‑2、图 0‑3、图 0‑4和图 0‑5。学习的时候如果配套这些硬件平台做实验，学习必会达到事半功倍的效果，可以省去中间硬件不一样时移植遇到的各种问题。

表格 0‑1 野火STM32开发板型号汇总

====== ========= ==== ===== =====
型号   区别
====== ========= ==== ===== =====
-      内核      引脚 RAM   ROM MINI   Cortex-M3 64   48KB  256KB 指南者 Cortex-M3 100  64KB  512KB 霸道   Cortex-M3 144  64KB  512KB 霸天虎 Cortex-M4 144  192KB
  1MB 挑战者 Cortex-M4 176  256KB 1MB ====== ========= ==== ===== =====

|docx002|

图 0‑1 野火【MINI】STM32F103RCT6 开发板

|docx003|

图 0‑2 野火【指南者】STM32F103VET6 开发板

|docx004|

图 0‑3 野火【霸道】STM32F103ZET6 开发板

|docx005|

图 0‑4 野火【霸天虎】STM32F407ZGT6 开发板

|docx006|

图 0‑5 野火【挑战者】STM32F429IGT6 开发板

本书的技术论坛
~~~~~~~

如果在学习过程中遇到问题，可以到野火电子论坛emXGUI专区： `http://www.firebbs.cn/forum.php?mod=forumdisplay&fid=149\ 发帖交流 <http://www.firebbs.cn发帖交流>`__ ，开源共享，共同进步。

鉴于水平有限，本书难免有纰漏，热心的读者也可把勘误发到论坛好让我们改进做得更好，祝您学习愉快，emXGUI的世界，野火与您同行。

初识emXGUI
--------

emXGUI是什么
~~~~~~~~~

简而言之，emXGUI(是Embed X Graphics User Interface的缩写)是针对嵌入式平台开发的图形软件库，包含各种常用图形控件，通过调用emXGUI提供的函数接口，开发嵌入式图形界面应用变得简单而快捷。

而图形软件库究竟是什么？就是一些与图形界面相关的函数，它提供接口给用户调用。例如，在没有使用图形软件库时，要控制LCD显示一个圆，需要用户自行根据LCD驱动编写画圆的函数，而使用图形界面软件库的话，这个画圆函数已经由该软件库提供给用户，用户只需要调用这个函数，设置圆的半径、圆心、颜色就可以画出自己想
要的圆，不需要再考虑画圆的算法。

emXGUI的应用场合
~~~~~~~~~~~

emXGUI并不只是提供了画圆之类的基本绘图函数库，它的主要功能如下：

-  绘制2-D图形：绘制圆、椭圆、多边形、弧线、线图和饼形图等；

-  显示位图文件：显示BMP、JPEG、GIF及PNG格式的图片文件；

-  显示文字：支持显示多国语言的文字，如中英文、越南语、西班牙语等等；

-  处理用户输入：如键盘、鼠标及电阻/电容触摸屏的人机交互输入处理；

-  提供各种窗口对象：这些窗口对象也被称为图形控件，最常见的如菜单控件、窗口控件、按键控件、复选框及框架窗口控件等，有了这些控件，就非常容易地制作出类似Windows系统的控制界面了。

emXGUI的这些功能，就是为了解决人机交互应用的设计难题。而它对ROM和RAM的消耗相对来说并不高。最低推荐配置为：Cortex-M0 ，50MHZ ，32KB RAM ，128KB
ROM。这在当前大多数嵌入式平台都是可以接受的。又因为emXGUI可以在多任务系统及裸机的平台上运行，尤其适合嵌入式乱七八糟的开发要求，自然使得emXGUI在嵌入式人机交互场合中大放异彩。一些使用emXGUI制作出来的效果，见\ **错误!未找到引用源。**\ 。

|docx007|

图 1‑1 emXGUI效果演示效果图

emXGUI版本说明
~~~~~~~~~~

表格 1‑1 emXGUI版本说明

====== ========== ===================================== ==========
版本号 时间       更新说明                              作者
====== ========== ===================================== ==========
V1.0.0 2008-07-06 首发（公司内部产品使用至今2018-7-25） AATECH刘巍
\
\
\
\
\
\
\
\
====== ========== ===================================== ==========

emXGUI版权
~~~~~~~~

emXGUI由AATECH公司的刘巍编写，拥有完全自主的知识产权（包括emXGUI商标和软件著作权）。于2008年发布V1版本开始，十年深度优化，一直在公司产品中使用至今。

emXGUI收费
~~~~~~~~

emXGUI V1 版本商用免费，无论是个人还是公司均可免费使用。但是技术支持收费，即针对使用emXGUI开发产品的公司或者个人提供收费的技术支持。

emXGUI源码
~~~~~~~~

emXGUI不开源源代码，但提供多平台的LIB文件，提供完善的API手册，提供配套书籍《emXGUI应用开发实战指南》无论是个人还是公司都可以很快的上手。

emXGUI支持平台
~~~~~~~~~~

emXGUI目前测试过的平台如下，但主要目标还是针对M3、M4、M7、ARM9和A5这些内核的处理器，这个才是emXGUI的阵地，A8、A9等高端性能的处理器虽然能支持，但不是重点，不会花过多的精力去维护，毕竟这是安卓和QT的阵地。

-  ST：STM32F1、STM32F4、STM32F7、STM32H7

-  GD：GD32F207、GD32F407、GD32F450

-  NXP：i.MX RT1052、I.MX RT1020

-  ATMEL：SAMA5D3

-  三星：s3c2440、s3c2416、s3c6410

-  芯唐：N32903、N32905、N32926、NUC972

-  Cortex-A系列：S5PV210、Exynos4412、IMX6Q

emXGUI特色功能
~~~~~~~~~~

这个是重点，目前你们所能见到的GUI有的功能，emXGUI几乎都有，下面简单介绍几个emXGUI的特色：

1、占用资源少，效率高，在STM32F103不外扩RAM的情况下可以流畅运行，最低推荐配置为：Cortex-M0 ，50MHZ ，32KB RAM ，128KB ROM。

2、控件风格支持用户复位义，如果你想改成扁平化的控件，只需几行代码即可搞定，emXGUI默认是WIN 风格。

3、友好地支持矢量字体，提供矢量字体制作工具，除了制作矢量字体外，还可以制作矢量的符号。

4、使用unicode字符编码支持多国语言，中文，英文，越南语，西班牙语等等，如果你的产品有界面且需要销往国外，那么emXGUI将是你不二之选。

5、支持鼠标，支持触摸（电阻屏和电容屏）。

5、自带滑动控件，非常方便，即在液晶屏上可以实现类似现在手机界面滑动的效果。

6、高性能的绘图引擎+高效的Z序剪切策略，双管齐下，自带瓦伦增压。

emXGUI资料获取
~~~~~~~~~~

emXGUI的资料均可从emXGUI官网和野火电子论坛emXGUI专区获取。

-  emXGUI官网：\ `www.emxgui.com <http://www.emxgui.com>`__

-  野火电子论坛emXGUI专区：\ **http://www.firebbs.cn/forum.php?mod=forumdisplay&fid=149**

emXGUI配套书籍
~~~~~~~~~~

emXGUI的配套书籍由野火电子编写，书名为《emXGUI应用开发实战指南》，会有两本，分别基于STM32和i.MX RT 这两个平台处理器，会适配野火STM32和i.MX RT全系列的开发板。该书会编写边开源电子版，写完届时由机械工业出版社出版。

emXGUI配套的软件工具
~~~~~~~~~~~~~

-  emXGUI Font Creater：用于制作emXGUI字体，格式为xft格式；也可将ttf矢量字体转换成可以抗锯齿的字体，外观上和矢量字体一样，这样就可以不使用freetype库。

-  模拟器：暂时没有，但是以后会发布。

第一部分 emXGUI控件应用开发
=================

emXGUI文件和应用架构
-------------

emXGUI目录简介
~~~~~~~~~~

解压下载得的emXGUI文件后，进入到emXGUI目录见图 2‑1。

|docx008|

图 2‑1emXGUI文件说明

emXGUI库包含了如下内容：

-  arch文件夹：主要包含架构相关的内容，如不同类型液晶屏的绘图引擎示例以及不同操作系统平台下的信号量、延时接口。

-  drv文件夹：包含了emXGUI使用的驱动接口文件，如液晶、触摸、内存管理接口的初始化，这是移植emXGUI主要修改的内容；其中还包含有gui_drv_cfg.h文件用于定制驱动的各项配置；gui_startup.c包含初始化emXGUI的示例；gui_desktop.c包含使用emXGUI建立桌
  面的示例。

-  inc文件夹：它包含了全部的emXGUI库核心的头文件，各种关于库函数的声明、定义都在这些文件里面。

-  libs文件夹：它包含了emXGUI的代码库文件，针对Cortex-M0、M3和M4这些不同 CPU内核以及在GCC、MDK这些不同编译环境，都有一个相对应的emXGUI库，在使用的时候要根据自己的平台选择合适的库文件。

-  resource文件夹：包含emXGUI可能使用的资源文件，如字体数据、图片数据等。

-  tools文件夹：它包含了bin2c.exe、XBF字体生成器等软件工具。

文件说明
~~~~

下面的针对具体的文件进行介绍。

表格 2‑1 emXGUI具体文件说明

============================ =============================================================================================================================================================
目录/文件名                  说明
============================ =============================================================================================================================================================
libs                         emXGUI核心库文件
emXGUI100_MDK_xxx.lib        emXGUI核心API库文件，MDK版，XXX内核
x_libc_MDK_xxx.lib           重实现的C标准库文件，MDK版，XXX内核，

                             为方便移植至不同平台，emXGUI使用的C库都是x_libc中实现的 arch目录                     主要包含emXGUI架构相关的文件，如液晶类型、操作系统接口 GUI_Arch.c                   架构相关的总文件
                             GUI_TouchPanel_Calibration.c 电阻屏使用的校准接口 GUI_TouchPanel.c             触摸屏控制接口，包含初始化，坐标处理以及校准 arch/GAL目录                 本目录包含绘图引擎相关的文件 GL_Cursor.c
                             包含光标的外观及控制接口，可修改本文件定制光标的外观 GL_MEM_xBPP.c                x（8/16/32）位的内存绘图接口，适用于显存型液晶屏，往显存写入数据即可直接显示，如STM32F429使用LTDC驱动的液晶屏 GL_MPU_16Bit.c
                             16位MPU通用绘图接口，适用于自带液晶驱动的液晶屏，显示时需要使用特定命令与驱动寄存器进行交互，如自带ILI9341驱动器的液晶 arch/inc目录                 包含架构相关的主要头文件 gui_drv.h                    驱动头文件
                             GUI_Font_Freetype.h          自定义字体头文件 arch/Options目录             包含各种操作系统的接口文件 X_GUI_xxxx.c                 操作系统接口，包含互斥锁、信号量、线程句柄、系统时间和延时等操作 resource
                             /xft_font目录       emXGUI可能使用到的XBF字体资源文件 ASCII_x_yBPP.c
                             示例ASCII编码的xft字体数组文件，其中x为字体宽高，y为抗锯齿参数（数值越大越平滑，占用空间越大），C数组文件适用于直接添加至工程并作为程序数据烧录到MCU内部FLASH ASCII_x_yBPP.bin
                             示例ASCII编码的xft字体bin文件，与同名的C文件功能类似，主要用于作为资源文件烧录到外部SPI-FLASH、SD卡等存储器上 GB2312_x_yBPP.c
                             示例GB2312编码的xft字体数组文件，由于GB2312编码数据文件较大，不建议直接存储在MCU的内部FLASH GB2312_x_yBPP.bin            示例GB2312编码的xft字体bin文件 drv目录                      包含emXGUI驱动接口文件
                             gui_drv_cfg.h                驱动配置，包含是否使用鼠标、键盘、触摸屏等输入设备；使用的字体类型；液晶的分辨率和像素格式等内容。 gui_startup.c                emXGUI初始化和启动的示例文件 gui_desktop.c
                             使用emXGUI创建桌面的示例文件 gui_lcd_port.c/h             液晶驱动接口 gui_mem_port.c/h             内存管理接口 gui_log_port.c/h             日志输出接口 gui_font_port.c/h
                             字体管理接口 gui_input_port.c/h           输入设备接口（可选，可在gui_drv_cfg.h文件关闭输入设备配置，不使输入设备时可不添加本文件到工程） gui_touch_port.c/h           触摸设备接口，使用触摸屏时在此添加驱动（可选）
                             gui_resource_port.c/h        资源设备读写接口，如把资源文件存储在外部SPI-FLASH可使用该接口进行访问（可选） gui_picture_port.c/h         图片读写接口，显示外部资源图片时可在此编写访问资源设备的接口（可选） inc目录 def.h
                             一些类型和常用函数定义 emXGUI_Arch.h                emXGUI架构头文件 emXGUI.h                     emXGUI总的头文件，包含emxGUI上层API的声明 GUI_Font_XFT.h               字体配置头文件
                             x_libc.h                     重实现的C库x_libc相关头文件 x_obj.c/h                    链表相关代码 ============================ ======================================
                             =======================================================================================================================

emXGUI核心库文件
~~~~~~~~~~~

emXGUI核心库文件（如emXGUI100_MDK_CM4.lib）提供了emXGUI所有可用的API，它所提供的API函数声明都可在emXGUI.h文件找到，在编写界面应用程序时，也只需要包含emXGUI.h这一个头文件。

C标准库x_libc
~~~~~~~~~~

为适应不同的平台，emXGUI自带了C标准库的函数，如字符串处理strlen、strcpy等，为进行区分，这些重新实现的库函数都带了个“x_”前缀，如x_strlen、x_strcpy等，这些函数与C标准库函数的功能一样，整个库被称为x_libc（如x_libc_MDK_CM4.lib）。使用时可通
过x_libc.h文件查看x_libc中提供的函数声明。

特别地，x_libc中还包含了内存堆管理函数，如x_heap_init、x_heap_alloc、x_heap_realloc、x_heap_free等，使用这些函数可管理多个x_heap内存堆。

emXGUI 应用的软件架构
~~~~~~~~~~~~~~

典型的emXGUI构建程序其架构见图 2‑2。

|docx009|

图 2‑2 emXGUI软件架构图

该架构看起来并不复杂，从最底层看起，
首先是硬件层，硬件层就是指最基本的板级支持软件包(BSP)，也就是我们常说的底层驱动，它提供了对硬件平台资源最直接的访问；emXGUI软件库承上启下，它运行在硬件层之上，与硬件层之间主要靠液晶驱动和输入设备连接起来，向应用层则提供了各种便于用户制作GUI应用的接口。

在没有使用emXGUI的软件架构中，很可能就是由硬件层直接过渡到应用层，甚至根本没有分层的概念，这样的应用程序将十分依赖于某个特定的硬件平台，不容易迁移到其它设备之中。从这个架构图可以看出，只需要编写好液晶驱动这个粘合emXGUI库和硬件BSP层的中间件，就可以正常使用emXGUI了，迁移应用到不同
的平台也简单得多。

新建工程—RT-Thread+STM32固件库
-----------------------

本章内容待添加…

移植emXGUI到STM32
--------------

要使emXGUI在特定的硬件平台上运行，需要为emXGUI提供与底层硬件操作相关的函数接口，主要为液晶驱动接口、触摸屏接口以及内存管理接口。

本章以配套例程“emXGUI工程模板（RTT+emXGUI）”为例，对emXGUI的执行过程和移植步骤进行解构，阅读时请打开该工程配套学习。

emXGUI的初始化过程
~~~~~~~~~~~~

在移植emXGUI前，需要了解它的初始化过程以及它依赖的硬件接口。在示例代码中，emXGUI通过GUI_Startup函数初始化依赖的设备，以初始化emXGUI运行所需要的环境，在这个GUI_Startup函数里，调用了emXGUI底层的配置函数，具体见表格
4‑1，完成了存储器分配、屏幕类型配置及初始化液晶驱动的工作。

表格 4‑1 GUI_Startup调用到的初始化函数

==================== =================== ===================================== ========
函数名               所在文件            功能                                  是否必须
==================== =================== ===================================== ========
GUI_MEM_Init         gui_mem_port.c      初始化GUI内核使用的内存空间           是
GUI_DisplayInit      gui_lcd_port.c      初始化液晶屏及GUI的绘图表面           是
GUI_Default_FontInit gui_font_port.c     初始化GUI使用的默认字体               是
GUI_Log_Init         gui_log_port.c      初始化日志输出接口，一般使用串口      是
GUI_VMEM_Init        gui_mem_port.c      初始化GUI提供给用户的VMEM内存空间     否
GUI_InputInit        gui_input_port.c    初始化输入设备，如鼠标、键盘、触摸屏  否
RES_DevInit          gui_resource_port.c 初始化资源设备，如外部SPI-FLASH、SD卡 否
==================== =================== ===================================== ========

GUI_Startup函数的示例代码具体见代码清单 4‑1。

代码清单 4‑1 GUI_Startup示例代码（gui_startup.c文件）

1 /第1部分/

2 /*\*

3 \* @brief GUI低级别的初始化,这是GUI的第一个初始化函数

4 \* @param 无

5 \* @retval TRUE:成功; FALSE：失败.

6 \*/

7 static BOOL GUI_LowLevelInit(void)

8 {

9

10 //GUI Core内存管理初始化

11 GUI_MEM_Init();

12

13 #if(GUI_VMEM_EN)

14 //vmem内存管理初始化

15 GUI_VMEM_Init();

16 #endif

17

18 //初始化日志接口

19 if (GUI_Log_Init() != TRUE) {

20

21 }

22

23 /\* 直接返回TRUE，为了部分设备初始化不正常不影响后续运行 \*/

24 return TRUE;

25 }

26

27 /第2部分/

28 /*\*

29 \* @brief 启动GUI，包含各种内存、液晶、输入设备的初始化

30 \* @param 无

31 \* @retval 无

32 \*/

33 void GUI_Startup(void)

34 {

35 SURFACE \*pSurf=NULL;

36 HFONT hFont=NULL;

37 /第3部分/

38 if (!GUI_LowLevelInit()) { //GUI低级初始化.

39 GUI_ERROR("GUI_LowLevelInit Failed.");

40 return;

41 }

42 /第4部分/

43 if (!GUI_Arch_Init()) { //GUI架构适配层初始化.

44 GUI_ERROR("GUI_Arch_Init Failed.");

45 return;

46 }

47

48 if (!X_GUI_Init()) { //GUI内核初始化.

49 GUI_ERROR("X_GUI_Init Failed.");

50 return;

51 }

52 /第5部分/

53 pSurf =GUI_DisplayInit(); //显示设备初始化

54 if (pSurf==NULL) {

55 GUI_ERROR("GUI_DisplayInit Failed.");

56 return;

57 }

58 GUI_SetScreenSurface(pSurf); //设置屏幕Surface对象

59 /第6部分/

60 #if(GUI_RES_DEV_EN)

61 //资源设备初始化（FLASH）

62 if (RES_DevInit() != TRUE) {

63 GUI_ERROR("RES_DevInit Failed.");

64 }

65 #endif

66 /第7部分/

67 #if(GUI_INPUT_DEV_EN)

68 //初始化输入设备

69 if (GUI_InputInit() != TRUE) {

70 GUI_ERROR("GUI_InputInit Failed.");

71 }

72 GL_CursorInit(pSurf,pSurf->Width>>1,pSurf->Height>>1); //初始化光标

73 #endif

74 /第8部分/

75 hFont =GUI_Default_FontInit(); //初始化默认的字体

76 if (hFont==NULL) {

77 GUI_ERROR("GUI_Default_FontInit Failed.");

78 return;

79 }

80 GUI_SetDefFont(hFont); //设置默认的字体

81 /第9部分/

82 GUI_DesktopStartup(); //启动桌面窗口(该函数不会返回).

83

84 }

在这段代码中条件编译中的内容如“#if(GUI_VMEM_EN) …#endif”、“#if(GUI_RES_DEV_EN) …#endif”是可以通过gui_drv_cfg.h头文件配置的宏，可以根据自己的应用需要决定是否加入这些接口。

下面对这段代码的各个部分进行讲解，下面的描述中，“接口”一般指需要用户自行编写的具体驱动，“库函数”一般是指GUI中提供API：

-  第1部分。GUI_LowLevelInit函数，它包含最基础的初始化内容，是GUI_Startup函数第一个调用的初始化函数，它包含内存管理接口GUI_MEM_Init、GUI_VMEM_Init和日志输出接口GUI_Log_Init的初始化。

1) 其中GUI_MEM_Init管理的内存是后续GUI_Arch_Init、X_GUI_Init等GUI库函数使用到的内存空间，所以这段内存初始化必须在调用任何一个GUI API函数之前完成。

2) GUI_VMEM_Init初始化的是提供给用户使用的VMEM和GMEM内存，应用中没有使用的话可以不初始化。

3) GUI_Log_Init初始化的是日志输出接口，提前初始化以便后续代码运行时能正常输出调试信息。

-  第2部分的内容是GUI_Startup函数的主体；第3部分调用了前面的GUI_LowLevelInit函数初始化基础设备。

-  第4部分调用库函数GUI_Arch_Init初始化GUI的架构层，它主要包含适配不同类型液晶屏的绘图引擎；调用X_GUI_Init函数初始化GUI内核。

-  第5部分。调用GUI_DisplayInit接口初始化液晶屏，并利用它返回的绘图表面pSruf作为输入参数调用GUI_SetScreenSurface设置屏幕的绘图表面对象。

-  第6部分。调用RES_DevInit接口初始化外部资源设备，如使用外部SPI-FLASH存储字体文件、图片文件，若使用到这样的设备需要调用该接口进行初始化。

-  第7部分。调用GUI_InputInit接口初始化输入设备，如鼠标、键盘和触摸屏，然后调用库函数GL_CursorInit初始化光标。

-  第8部分。调用GUI_Default_FontInit接口初始化默认字体，并利用返回的字体句柄hFont作为输入参数调用库函数GUI_SetDefFont进行设置。

-  第9部分。初始化完成，调用GUI_DesktopStartup函数初始化GUI的示例桌面，可修改gui_desktop.c文件对桌面进行定制。

在接下来的移植过程主要是修改这个GUI_Startup函数调用到的接口，以适配运行的硬件平台。根据GUI_Startup函数的内容，可整理出移植emXGUI所需要的配置：

-  配置操作系统的接口。

-  配置内存管理接口。

-  配置日志接口

-  配置显示驱动接口。

-  配置默认字体。

以上是移植emXGUI需要的最小配置，为适应更复杂的应用需求，还可添加如下内容：

-  配置输入设备接口。

-  配置外部资源设备接口。

-  配置图片解码接口。

配置操作系统接口
~~~~~~~~

使用操作系统时，需要给emXGUI提供操作系统的接口，emXGUI的内核使用这些接口管理系统资源，便于适配不同的操作系统。

在emXGUI资料的如下目录提供了常用的操作系统接口范例：

操作系统接口范例目录：emxgui\arch\OS_Options

|docx010|

图 4‑1 常用操作系统的emXGUI接口示例文件

以本教程配套的RT-Thread系统为例，它的操作系统接口示例文件为X_GUI_RTT.c，具体见代码清单 4‑2。

代码清单 4‑2 配置操作系统接口（X_GUI_RTT.c文件）

1 /\*

2 函数功能: 创建一个互斥(该互斥锁必须支持嵌套使用)

3 返回: 互斥对象句柄(唯一标识)

4 说明: 互斥对象句柄按实际OS所定,可以是指针,ID号等...

5 \*/

6 GUI_MUTEX\* GUI_MutexCreate(void)

7 {

8 return (GUI_MUTEX*)rt_mutex_create(NULL,RT_IPC_FLAG_FIFO);

9 }

10

11 /\*

12 函数功能: 互斥锁定

13 参数: hMutex(由GUI_MutexCreate返回的句柄);

14 time 最长等待毫秒数,0立既返回,0xFFFFFFFF,一直等待

15 返回: TRUE:成功;FALSE:失败或超时

16 说明: .

17 \*/

18 BOOL GUI_MutexLock(GUI_MUTEX \*hMutex,U32 time)

19 {

20

21 if (rt_mutex_take((rt_mutex_t)hMutex,rt_tick_from_millisecond(time))==RT_EOK) {

22 return TRUE;

23 }

24 return FALSE;

25 }

26

27 /\*

28 函数功能: 互斥解锁

29 参数: hMutex(由GUI_MutexCreate返回的句柄);

30 返回: 无

31 说明: .

32 \*/

33 void GUI_MutexUnlock(GUI_MUTEX \*hMutex)

34 {

35 rt_mutex_release((rt_mutex_t)hMutex);

36 }

37

38 /\*

39 函数功能: 互斥删除

40 参数: hMutex(由GUI_MutexCreate返回的句柄);

41 返回: 无

42 说明: .

43 \*/

44 void GUI_MutexDelete(GUI_MUTEX \*hMutex)

45 {

46 rt_mutex_delete((rt_mutex_t)hMutex);

47 }

48

49 /\*

50 函数功能: 创建一个信号量

51 参数: init: 信号量初始值; max: 信号量最大值

52 返回: 信号量对象句柄(唯一标识)

53 说明: 信号量对象句柄按实际OS所定,可以是指针,ID号等...

54 \*/

55 GUI_SEM\* GUI_SemCreate(int init,int max)

56 {

57 return (GUI_SEM*)rt_sem_create(NULL,init,RT_IPC_FLAG_FIFO);

58 }

59

60 /\*

61 函数功能: 信号量等待

62 参数: hsem(由GUI_SemCreate返回的句柄);

63 time 最长等待毫秒数,0立既返回,0xFFFFFFFF,一直等待

64 返回: TRUE:成功;FALSE:失败或超时

65 说明: .

66 \*/

67 BOOL GUI_SemWait(GUI_SEM \*hsem,U32 time)

68 {

69

70 if (rt_sem_take((rt_sem_t)hsem,rt_tick_from_millisecond(time))== RT_EOK) {

71 return TRUE;

72 }

73 return FALSE;

74 }

75

76 /\*

77 函数功能: 信号量发送

78 参数: hsem(由GUI_SemCreate返回的句柄);

79 返回: 无

80 说明: .

81 \*/

82 void GUI_SemPost(GUI_SEM \*hsem)

83 {

84 rt_sem_release((rt_sem_t)hsem);

85 }

86

87 /\*

88 函数功能: 信号量删除

89 参数: hsem(由GUI_SemCreate返回的句柄);

90 返回: 无

91 说明: .

92 \*/

93 void GUI_SemDelete(GUI_SEM \*hsem)

94 {

95 rt_sem_delete((rt_sem_t)hsem);

96 }

97

98 /\*

99 函数功能: 获得当前线程句柄(唯一标识)

100 参数: 无

101 返回: 当前线程唯一标识,按实际OS所定,可以是指针,ID号等...

102 说明: .

103 \*/

104 HANDLE GUI_GetCurThreadHandle(void)

105 {

106 return (HANDLE)rt_thread_self();

107 }

108

109 /\*

110 函数功能: 获得当前系统时间(单位:毫秒)

111 参数: 无

112 返回: 当前系统时间

113 说明: .

114 \*/

115 U32 GUI_GetTickCount(void)

116 {

117 U32 i;

118

119 i=rt_tick_get();

120

121 return (i*1000)/RT_TICK_PER_SECOND;

122

123 }

124

125 /\*

126 函数功能: 最短时间内让出CPU

127 参数: 无

128 返回: 无

129 说明: 按具体OS情况而定,最简单的方法是:OS Delay 一个 tick 周期.

130 \*/

131 void GUI_Yield(void)

132 {

133 rt_thread_delay(2);

134 }

135

136 /\*

137 函数功能: 延时函数

138 参数: ms: 延时时间(单位:毫秒)

139 返回: 无

140 说明:

141 \*/

142 void GUI_msleep(u32 ms)

143 {

144 ms=rt_tick_from_millisecond(ms);

145 rt_thread_delay(ms);

146 }

示例代码就是针对具体的操作系统进行封装，它封装的操作系统接口总结如表格 4‑2，主要包括互斥信号量、信号量的创建、删除、等待和释放的操作，还包含有获取任务句柄、当前系统时间戳以及延时相关的操作。

表格 4‑2 需要提供给emXGUI的操作系统接口

====================== ================================
操作系统接口           功能
====================== ================================
GUI_MutexCreate        创建互斥信号量
GUI_MutexLock          互斥锁定
GUI_MutexUnlock        互斥解锁
GUI_MutexDelete        删除互斥信号量
GUI_SemCreate          创建信号量
GUI_SemWait            等待信号量
GUI_SemPost            发送信号量
GUI_SemDelete          删除信号量
GUI_GetCurThreadHandle 获取当前任务句柄（唯一标识）
GUI_GetTickCount       获取当前系统时间戳（单位：毫秒）
GUI_Yield              最短时间内让出CPU
GUI_msleep             延时函数（单位：毫秒）
====================== ================================

配置内存管理接口
~~~~~~~~

GUI_MEM_Init和GUI_VMEM_Init接口是GUI_Startup调用的第一个初始化函数，它们的示例代码位于gui_mem_port.c文件。

在本示例代码中，使用了两段内存空间，具体见图 4‑2和表格 4‑3。

|docx011|

图 4‑2 内存管理接口示意图

表格 4‑3 示例代码的内存管理接口

============== ================================== ========
内存管理接口   说明                               是否必须
============== ================================== ========
GUI_MEM_Init   初始化emXGUI内核对象使用的内存空间 是
GUI_MEM_Alloc  emXGUI内核对象申请内存的接口       是
GUI_MEM_Free   emXGUI内核对象释放内存的接口       是
GUI_VMEM_Init  初始化提供给用户使用的内存空间     否
GUI_VMEM_Alloc 从用户内存块申请空间               否
GUI_VMEM_Free  释放空间回用户内存块               否
GUI_GRAM_Alloc 申请空间作为液晶显存               否
GUI_GRAM_Free  释放液晶显存                       否
============== ================================== ========

此处我们分别把这三类管理接口相关的内存分别称为MEM、VMEM以及GRAM，说明如下：

-  MEM是emXGUI内核对象申请内存的区域，即GUI内核都通过GUI_MEM_Alloc接口申请空间。创建的GUI对象越多，就需要越大的MEM空间，推荐这部分内存空间至少为8KB。

-  VMEM是提供给用户使用的内存空间，若用户的应用程序没有从VMEM申请空间，可以不实现该接口。

-  GRAM用于动态申请液晶显存的空间，如STM32F429的LTDC外设需要一块内存区域存储液晶像素数据。在本示例中液晶驱动使用固定的内存空间，不需要从GRAM中分配，并且为方便起见，直接让GRAM与VMEM使用同一块内存区域进行管理。

MEM内存接口
^^^^^^^

示例代码中的MEM内存直接封装了RT-Thread系统的rt_malloc和rt_free接口，具体见\ **错误!未找到引用源。**\ 。

代码清单 4‑3 MEM内存管理接口（gui_mem_port.c文件）

1 /*\*

2 \* @brief 创建一个内存堆（用于GUI内核对象）,可参考vmem配置

3 \* @retval 无

4 \*/

5 void GUI_MEM_Init(void)

6 {

7 /\* 本示例中的GUI内核对象使用 rt_malloc ，

8 它已由rtt系统初始化*/

9 return ;

10 }

11

12 /*\*

13 \* @brief 动态内存申请(用于GUI内核对象)

14 \* @param size 要申请的内存大小

15 \* @retval 申请到的内存指针

16 \*/

17 void\* GUI_MEM_Alloc(U32 size)

18 {

19 void \*p=NULL;

20

21 p =rt_malloc(size);

22 if (p==NULL) {

23 GUI_ERROR("GUI_MEM_Alloc.");

24 }

25

26 return p;

27 }

28

29 /*\*

30 \* @brief 释放内存(用于GUI内核对象)

31 \* @param p:需要释放的内存首址

32 \* @retval 无

33 \*/

34 void GUI_MEM_Free(void \*p)

35 {

36 rt_free(p);

37 }

由于使用RT-Thread系统接口管理，初始化已经由系统实现，这段代码的GUI_MEM_Init为空，在RT-Thread系统启动前就完成了内存堆的初始化。而配置该空间的大小则是在gui_drv_cfg.h和board.c文件中实现的，具体见代码清单 4‑4。

代码清单 4‑4 RT-Thread内存空间的初始化（gui_drv_cfg.h和board.c文件）

1 //

2 /**gui_drv_cfg.h文件**/

3 /\* GUI内核使用的存储区大小，推荐最小值为8KB \*/

4 #define GUI_CORE_MEM_SIZE (32*1024) (1)

5 //

6 /**board.c文件**/

7 #define RT_HEAP_SIZE (GUI_CORE_MEM_SIZE) (1)

8 /\* 从内部SRAM里面分配一部分静态内存来作为rtt的堆空间，这里配置为4KB \*/

9 static uint8_t rt_heap[RT_HEAP_SIZE]; (2)

10 RT_WEAK void \*rt_heap_begin_get(void) (3)

11 {

12 return rt_heap;

13 }

14

15 RT_WEAK void \*rt_heap_end_get(void) (4)

16 {

17 return rt_heap + RT_HEAP_SIZE;

18 }

这段代码中的第1部分定义了MEM存储区大小的宏GUI_CORE_MEM_SIZE，第2部分利用该宏定义了一个静态大小为GUI_CORE_MEM_SIZE的数组rt_heap，第3部分是RT-Thread内存堆管理的接口，用于获取内存空间的边界，即数组rt_heap的起始和结束地址。

用户可通过gui_drv_cfg.h中的宏GUI_CORE_MEM_SIZE改变MEM区域的大小，本示例中的大小为32KB。

若使用其它没有提供内存堆管理接口的操作系统，可以参考下面VMEM接口的配置方式定制MEM内存空间。

VMEM和GRAM内存接口
^^^^^^^^^^^^^

使用emXGUI的x_libc中的x_heap可管理多个内存堆，示例代码正是使用x_heap对VMEM和GRAM内存堆进行管理，具体见代码清单 4‑5。

代码清单 4‑5 VMEM和GRAM内存接口（gui_drv_cfg.h和gui_mem_port.c文件）

1 /第1部分/

2 /**gui_drv_cfg.h文件**/

3 /\* 配置vmem的基地址，大小以及分配粒度 \*/

4 /\* 是否使能VMEM内存堆 \*/

5 #define GUI_VMEM_EN 1

6 /\* 内存堆的基地址，可以为内部SRAM、外扩的SDRAM等 \*/

7 #define VMEM_BASE 0xD0200000 // 本SDRAM前2MB给LCD控制器作为显存了

8 /\* 内存堆的总大小，单位为字节 \*/

9 #define VMEM_SIZE (6<<20) // 6MB

10 /\* 最小分配粒度，单位为字节*/

11 #define VMEM_ALLOC_UNIT (64) //64字节

12 /*..gui_mem_port.c文件..*/

13 /第2部分/

14 #if(GUI_VMEM_EN)

15 /\* VMEM内存管理 \*/

16 /\* 互斥信号量 \*/

17 static GUI_MUTEX \*mutex_vmem = NULL;

18 /\* 内存堆管理句柄 \*/

19 static heap_t heap_vmem;

20 /\* VMEM缓冲区 \*/

21 static uint8_t buff_vmem[VMEM_SIZE] \__attribute__((at(VMEM_BASE)));

22 #endif

23 /第3部分/

24 /*\*

25 \* @brief 创建一个内存堆

26 \* @note 使用vmalloc前必须调用本函数初始化内存堆句柄

27 \* @retval 无

28 \*/

29 void GUI_VMEM_Init(void)

30 {

31 #if(GUI_VMEM_EN)

32 mutex_vmem = GUI_MutexCreate();

33 x_heap_init(&heap_vmem,

34 (void*)buff_vmem,

35 VMEM_SIZE,

36 VMEM_ALLOC_UNIT); /\* 创建一个内存堆 \*/

37 #endif

38 }

39

40 /*\*

41 \* @brief 从内存堆里申请空间

42 \* @param size 要申请的内存大小

43 \* @retval 申请到的内存指针

44 \*/

45 void\* GUI_VMEM_Alloc(u32 size)

46 {

47 #if(GUI_VMEM_EN)

48 u8 \*p;

49 GUI_MutexLock(mutex_vmem,5000);

50 p =x_heap_alloc(&heap_vmem,size);

51 GUI_MutexUnlock(mutex_vmem);

52 return p;

53 #endif

54 }

55

56 /*\*

57 \* @brief 释放内存

58 \* @param p:需要释放的内存首址

59 \* @retval 无

60 \*/

61 void GUI_VMEM_Free(void \*p)

62 {

63 #if(GUI_VMEM_EN)

64 GUI_MutexLock(mutex_vmem,5000);

65 x_heap_free(&heap_vmem,p);

66 GUI_MutexUnlock(mutex_vmem);

67 #endif

68 }

69

70 /第4部分/

71 /*\*

72 \* @brief 显示动态内存申请(用于GUI显示器缓存)

73 \* @param size 要申请的内存大小

74 \* @retval 申请到的内存指针

75 \*/

76 void\* GUI_GRAM_Alloc(U32 size)

77 {

78 return GUI_VMEM_Alloc(size);

79 }

80

81 /*\*

82 \* @brief 显示动态内存申请(用于GUI显示器缓存)

83 \* @param p:需要释放的内存首址

84 \* @retval 无

85 \*/

86 void GUI_GRAM_Free(void \*p)

87 {

88 GUI_VMEM_Free(p);

89 }

这段代码说明如下：

-  第1部分。这是gui_drv_cfg.h文件中的配置内容，它包含是否使能VMEM内存堆、内存堆的基地址、大小以及最小分配粒度的配置。示例中VMEM使用外部SDRAM所在的存储空间。

-  第2部分。定义内存堆管理用到的静态变量，如互斥信号量指针mutex_vmem、内存堆管理句柄heap_vmem以及缓冲区数组buff_vmem，其中缓冲区数组的基地址和大小是由第1部分中的宏配置的。

-  第3部分。在x_libc库函数x_heap_init/alloc/free之上添加互斥信号量的创建、申请以及释放的操作，封装得到GUI_VMEM_Init/Alloc/Free接口。

-  第4部分。直接把GUI_VMEM_Alloc和GUI_VMEM_Free封装成GRAM使用的GUI_GRAM_Alloc和GUI_GRAM_Free接口，所以示例代码中VMEM和GRAM使用相同的内存空间。

本示例只是粗略地分配外部SDRAM的空间作为VMEM使用，实际应用中请根据需要修改gui_drv_cfg.h文件重新定制，提供SDRAM空间的利用率。有需要也可以参考VMEM的接口管理其它内存堆。

配置日志接口
~~~~~~

在emXGUI的内核中使用了日志输出函数GUI_Printf，所以即使是不希望有输出，也要提供一个空的GUI_Printf函数。本示例中使用RT-Thread系统的rt_kprintf进行输出，具体见代码清单 4‑6。

代码清单 4‑6 日志接口（gui_log_port.c文件）

1 /*\*

2 \* @brief 初始化GUI日志接口

3 \* @param 无

4 \* @retval 是否初始化正常

5 \*/

6 BOOL GUI_Log_Init(void)

7 {

8 /\* 本例子在board.c文件中 rtt系统启动时就已初始化，此处不再重复 \*/

9 /\* 初始化串口 \*/

10 // Debug_USART_Config();

11 return TRUE;

12 }

13

14 /*\*

15 \* @brief 格式化字符串输出

16 \* @param 可变参数

17 \* @note 如果不用输出GUI调试信息,这个函数可以为空

18 \* @retval 无

19 \*/

20 void GUI_Printf(const char \*fmt,...)

21 {

22 #if 0

23 x_va_list ap;

24 char \*buf;

25 static char str_buf[256];

26 static GUI_MUTEX \*mutex_gui_printf=NULL;

27 ////

28 buf =str_buf/*(char*)GUI_MEM_Alloc(256)*/;

29 if (buf) {

30

31 if (GUI_MutexLock(mutex_gui_printf,0xFFFFFFFF)) {

32 x_va_start(ap,fmt);

33 x_vsprintf(buf,fmt,ap);

34 /\* 底层需要提供DebugPuts接口进行输出 \*/

35 **DebugPuts(buf);**

36 //DebugOutput(buf);

37

38 GUI_MutexUnlock(mutex_gui_printf);

39 x_va_end(ap);

40 }

41

42 //GUI_MEM_Free(buf);

43 }

44 #else

45

46 rt_kprintf(fmt);

47 #endif

48

49 }

代码中的GUI_Log_Init是GUI_Startup函数会调用的日志初始化接口，可在此处初始化串口作为日志输出，本示例中在RT-Thread系统正式运行前就已经在board.c文件的rt_hw_board_init函数初始化了，此处不再重复。

示例中的GUI_Printf直接封装了RT-Thread系统的rt_kprintf输出函数，若不使用rt_kprintf，可以使用代码中条件编译 的另一个分支，底层提供DebugPuts接口即可，DebugPuts函数以buf作为输入参数进行输出。

在gui_log_port.h文件中还对GUI_Printf函数进行了封装，得到GUI_INFO、GUI_ERROR、GUI_DEBUG、GUI_DEBUG_ARRAY和GUI_DEBUG_FUNC函数，这些函数预定义了一些输出信息，或可通过宏来设置是否进行输出，使用的时候比较方便，具体见代码清单
4‑7。

代码清单 4‑7 其它日志输出接口（gui_log_port.h文件）

1 /\* INFO和ERROR在任何情况下都会输出 \*/

2 /\* 信息输出 \*/

3 #define GUI_INFO(fmt,arg...) GUI_Printf("<<-GUI-INFO->> "fmt"\n",##arg)

4 /\* 错误输出 \*/

5 #define GUI_ERROR(fmt,arg...) GUI_Printf("<<-GUI-ERROR->> "fmt"\n",##arg)

6 /\* 调试输出，受GUI_DEBUG_EN控制 \*/

7 #define GUI_DEBUG(fmt,arg...) do{\\

8 if(GUI_DEBUG_EN)\\

9 GUI_Printf("<<-GUI-DEBUG->> [%s] [%d]"fmt"\n",__FILE__,__LINE__, ##arg);\\

10 }while(0)

11 /\* 数组输出，受GUI_DEBUG_ARRAY_EN控制 \*/

12 #define GUI_DEBUG_ARRAY(array, num) do{\\

13 int32_t i;\\

14 uint8_t\* a = array;\\

15 if(GUI_DEBUG_ARRAY_EN)\\

16 {\\

17 GUI_Printf("<<-GUI-DEBUG-ARRAY->>\n");\\

18 for (i = 0; i < (num); i++)\\

19 {\\

20 GUI_Printf("%02x ", (a)[i]);\\

21 if ((i + 1 ) %10 == 0)\\

22 {\\

23 GUI_Printf("\n");\\

24 }\\

25 }\\

26 GUI_Printf("\n");\\

27 }\\

28 }while(0)

29

30 /\* 进入函数输出，受GUI_DEBUG_FUNC_EN控制

31 一般在需要调试的函数开头进行调用，

32 调试时可通过输出信息了解运行了什么函数或运行顺序

33 \*/

34 #define GUI_DEBUG_FUNC() do{\\

35 if(GUI_DEBUG_FUNC_EN)\\

36 GUI_Printf("<<-GUI-FUNC->> Func:%s@Line:%d\n",__func__,__LINE__);\\

37 }while(0)

其中GUI_INFO和GUI_ERROR函数默认都会进行输出，主要用于输出提示信息和错误信息，而GUI_DEBUG、GUI_DEBUG_ARRAY和GUI_DEBUG_FUNC函数一般用于调试输出，可以在gui_drv_cfg.h文件设置它们是否进行输出，具体见代码清单 4‑8。

代码清单 4‑8 是否开启调试、数组及进行函数的输出功能（gui_drv_cfg.h文件）

1 /\* 是否开启调试输出、数组输出、进入函数的输出功能 \*/

2 #define GUI_DEBUG_EN 1

3 #define GUI_DEBUG_ARRAY_EN 0

4 #define GUI_DEBUG_FUNC_EN 0

配置显示驱动接口
~~~~~~~~

emXGUI的显示驱动接口主要包含绘图引擎、绘图表面以及底层液晶驱动的内容，移植时主要是针对gui_lcd_port.c文件进行修改。

先来了解显示驱动接口GUI_DisplayInit的初始化流程，它会在GUI_Startup函数中被调用，具体见代码清单 4‑9。

代码清单 4‑9 GUI_DisplayInit接口（gui_lcd_port.c文件）

1 /第1部分/

2 /*\*

3 \* @brief 初始化显示设备接口，并创建SURFACE表面

4 \* @param 无

5 \* @retval 显示设备Surface对象指针，创建得到的绘图表面

6 \*/

7 SURFACE\* GUI_DisplayInit(void)

8 {

9 /\* 绘图表面 \*/

10 SURFACE \*pSurf;

11 /第2部分/

12 #if (LCD_FORMAT == COLOR_FORMAT_RGB565)

13

14 //创建绘图表面

15 /\* 动态申请的方式 \*/

16 // pSurf = GUI_CreateSurface(SURF_RGB565,

17 // LCD_XSIZE,LCD_YSIZE,

18 // LCD_XSIZE*2,

19 // NULL);

20

21 /\* 直接指定地址的方式， 显存地址，*/

22 pSurf = GUI_CreateSurface(SURF_RGB565,

23 LCD_XSIZE,LCD_YSIZE,

24 LCD_XSIZE*2,

25 (void*)LCD_FRAME_BUFFER);

26

27 #endif

28

29 #if (LCD_FORMAT == COLOR_FORMAT_XRGB8888)

30 //动态申请的方式，初始化LCD Surface结构数据(XRGB8888格式)

31 //lcd_buffer =(u8*)GUI_GRAM_Alloc(LCD_XSIZE,LCD_YSIZE*4);

32

33 /\* 直接指定地址的方式， 显存地址，*/

34 /\* 动态申请的方式 \*/

35 // pSurf = GUI_CreateSurface(SURF_XRGB8888,

36 // LCD_XSIZE,LCD_YSIZE,

37 // LCD_XSIZE*4,

38 // NULL);

39

40 pSurf = GUI_CreateSurface(SURF_XRGB8888,

41 LCD_XSIZE,LCD_YSIZE,

42 LCD_XSIZE*4,

43 (void*)LCD_FRAME_BUFFER);

44

45 #endif

46 /第3部分/

47 if (pSurf == NULL) {

48 GUI_Printf("#Error: GUI_CreateSurface Failed.\r\n");

49 }

50

51 //LCD硬件初始化

52 LCD_HardInit((u32)pSurf->Bits);

53 /第4部分/

54 //清屏

55 pSurf->GL->FillArea(pSurf,0,0,LCD_XSIZE,LCD_YSIZE,pSurf->CC->MapRGB(0,0,0));

56 //打开背光

57 LCD_BkLight(TRUE);

58 /第5部分/

59 return pSurf;

60 }

该代码的说明如下：

-  第1部分。GUI_DisplayInit作为显示设备的驱动接口，它初始化了液晶屏硬件并创建emXGUI绘图表面Surface，执行完毕把绘图表面的指针返回，然后由库函数GUI_SetScreenSurface设置为屏幕的绘图表面，emXGUI的所有绘制操作将在该表面展开。

-  第2部分。根据宏LCD_FORMAT的定义调用GUI_CreateSurface函数，创建格式为RGB565和XRGB8888的绘图表面，调用时输入的参数为绘图表面格式、液晶屏的宽高、一行像素数据占多少字节以及显存空间的首地址，示例中输入使用的这些宏都定义在bsp_lcd.h和gui_drv_cf
  g.h头文件中，具体见代码清单 4‑10。

代码清单 4‑10 液晶屏相关的宏定义（bsp_lcd.h和gui_drv_cfg.h文件）

1 /*\* bsp_lcd.h文件 \**/

   2 /\* LCD Size (Width and Height) \*/

   3 #define LCD_PIXEL_WIDTH ((uint16_t)800)

   4 #define LCD_PIXEL_HEIGHT ((uint16_t)480)

   5

   6 #define LCD_BUFFER ((uint32_t)0xD0000000)

   7

   8 /*\* gui_drv_cfg.h文件 \**/

   9 //野火5.0 / 7.0TFT,800x480

   10 /\* 显存基地址 \*/

   11 #define LCD_FRAME_BUFFER LCD_BUFFER

   12

   13 /\* 使用的显示格式 \*/

   14 #define LCD_FORMAT COLOR_FORMAT_RGB565

   15 //#define LCD_FORMAT COLOR_FORMAT_XRGB8888

   16

   17 /\* 液晶宽高 \*/

   18 #define LCD_XSIZE LCD_PIXEL_WIDTH

   19 #define LCD_YSIZE LCD_PIXEL_HEIGHT

   特别地，若调用GUI_CreateSurface时显存地址指定为NULL时，函数执行时会从GRAM中分配显存空间（代码清单 4‑9第2部分中注释掉的调用方式即从GRAM中分配显存）。

-  代码清单 4‑9的第3部分。调用液晶初始化接口LCD_HardInit初始化液晶屏硬件，它接受显存地址作为输入参数，本示例中以前面创建的绘图表面pSurf->Bits作为显存。移植时用户需要根据液晶屏配置LCD_HardInit接口。

-  代码清单 4‑9的第4部分。调用绘图表面的矩形绘图函数pSurf->GL->FillArea把整个屏幕清除为黑色，并且调用液晶背光控制接口LCD_BkLight使能屏幕的背光。移植时用户需要配置LCD_BkLight接口。

-  代码清单 4‑9的第5部分，返回执行GUI_CreateSurface函数得到的pSurf，GUI_Startup函数中会利用它设置屏幕的绘图表面。

配置绘图表面（Surface）
^^^^^^^^^^^^^^^

代码清单
4‑9中调用GUI_CreateSurface函数创建了绘图表面，所谓绘图表面是对绘图设备的描述，其内容记录了绘图设备的颜色格式，物理像素大小，显示缓冲区，以及绘图引擎，GUI所有的绘图目标，最终都是在绘图表面上进行。每个绘图表面都是一个独立的绘图设备，可以由用户自由创建，它的类型定义具体见代码清单
4‑11。

代码清单 4‑11 绘图表面的类型定义（emXGUI_Arch.h文件）

1 typedef struct tagSURFACE SURFACE;

2

3 /*\*

4 \* @brief 绘图表面，包含格式、宽高、显存地址等内容

5 \*/

6 struct tagSURFACE {

7 U32 Format; //绘图表面的格式

8 U32 Width; //绘图表面的宽

9 U32 Height; //绘图表面的高

10 U32 WidthBytes; //一行像素点占多少字节

11 LPVOID Bits; //所在的显存地址

12 const COLOR_CONVERT \*CC; //颜色转换函数指针

13 const GL_OP \*GL; //绘图引擎指针

14 const void \*pdata; //附加数据

15 u32 Flags; //标志

16 };

17

该结构体的类型说明如下：

-  Format：绘图表面的像素格式，如RGB565/XRGB888/ARGB8888等，通常把它配置为与底层液晶驱动一致的格式，具体枚举值见代码清单 4‑12。

代码清单 4‑12 绘图表面的像素格式（emXGUI.h文件）

1 typedef enum {

2 SURF_SCREEN = 0,

3 SURF_RGB332 = COLOR_FORMAT_RGB332,

4 SURF_RGB565 = COLOR_FORMAT_RGB565,

5 SURF_ARGB4444 = COLOR_FORMAT_ARGB4444,

6 SURF_XRGB8888 = COLOR_FORMAT_XRGB8888,

7 SURF_ARGB8888 = COLOR_FORMAT_ARGB8888,

8

9 } SURF_FORMAT;

-  Width和Height：分别表示绘图表面的宽和高。

-  WidthBytes：表示绘图表面一行像素占多少个字节，计算方式为“Width*每个像素点的字节数”。

-  Bits：绘图表面对应的显存地址，如STM32F429中通常会把它赋值为液晶层的显存地址，绘制操作就是在显存中写入像素数据。

-  CC和GL：分别是颜色转换和绘图引擎（GAL）的函数指针。

-  pdata：附加数据。

-  Flags：包含指示绘图表面特性的某些标志，如可使用宏SURF_FLAG_GRAM表示绘图表面的显存空间是否从GRAM中分配得来的。

在emXGUI中提供了SurfaceInit_RGB332/ RGB565/ARGB4444/ XRGB8888/ ARGB8888等库函数用于初始化绘图表面，函数的声明形如代码清单 4‑13。

代码清单 4‑13 初始化绘图表面的函数声明（emXGUI_Arch.h文件）

1 /*\*

2 \* @brief 初始化绘图表面

3 \* @param pSurf[out] 根据其它参数对pSurf进行初始化

4 \* @param gdraw[in] 绘图引擎对象，如GL_MEM_8PP、GL_MEM_16PP、GL_MEM_32PP

5 \* @param w h 绘图表面的宽和高

6 \* @param line_bytes 一行像素占多少个字节

7 \* @param bits[in] 显存指针

8 \*/

9 void SurfaceInit_RGB332(SURFACE \*pSurf,

10 const GL_OP \*gdraw,

11 int w,int h,

12 int line_bytes,

13 void \*bits);

这些函数会根据输入参数配置绘图表面指针pSurf，为方便应用，在gui_lcd_port.c文件中把这些函数封装成了GUI_CreateSurface接口，具体见代码清单 4‑14。

代码清单 4‑14 GUI_CreateSurface接口（gui_lcd_port.c文件）

1 /*\*

2 \* @brief 创建SURFACE表面

3 \* @param Format 绘图表面格式

4 \* @param Width Height 绘图表面宽高

5 \* @param LineBytes 绘图表面每行像素占多少字节

6 \* @param bits 显存地址，若为NULL，则会使用GUI_GMEM_Alloc申请动态显存

7 \* @retval 显示设备Surface对象指针，创建得到的绘图表面

8 \*/

9 SURFACE\* GUI_CreateSurface(SURF_FORMAT Format,

10 int Width,int Height,

11 int LineBytes,

12 void \*bits)

13 {

14 SURFACE \*pSurf;

15 switch (Format) {

16 case SURF_RGB332:

17 pSurf = (SURFACE*)GUI_MEM_Alloc(sizeof(SURFACE));

18 pSurf->Flags =0;

19 if (LineBytes <= 0) {

20 LineBytes = Width;

21 }

22 if (bits==NULL) {

23 bits = (void*)GUI_GRAM_Alloc(Height*LineBytes);

24 pSurf->Flags \|= SURF_FLAG_GRAM;

25 }

26 SurfaceInit_RGB332(pSurf,&\ **GL_MEM_8PP**,Width,Height,LineBytes,bits);

27 break;

28 ////

29

30 case SURF_RGB565:

31 pSurf = (SURFACE*)GUI_MEM_Alloc(sizeof(SURFACE));

32 pSurf->Flags =0;

33 if (LineBytes <= 0) {

34 LineBytes = Width*2;

35 }

36 if (bits==NULL) {

37 bits = (void*)GUI_GRAM_Alloc(Height*LineBytes);

38 pSurf->Flags \|= SURF_FLAG_GRAM;

39 }

40 SurfaceInit_RGB565(pSurf,&\ **GL_MEM_16PP**,Width,Height,LineBytes,bits);

41 break;

42 ////

43 /*...后面省略其它像素格式的配置内容...*/

44 }

45 }

代码中根据输入的像素格式调用不同的绘图表面初始化函数，利用GUI_MEM_Alloc接口从MEM分配绘图表面变量的空间，并且当显存地址输入为NULL的时候，通过GUI_GRAM_Alloc从GRAM分配显存空间。

代码中加粗显示的GL_MEM_8PP和GL_MEM_16PP是下面要介绍的内存型绘图引擎。

emXGUI的绘图引擎（GAL）
^^^^^^^^^^^^^^^^

emXGUI能适配不同的液晶屏，按照适配的驱动接口主要把液晶屏分为两类：

-  内存型液晶屏：类似STM32F429这类自带LTDC液晶控制器的MCU，只要初始化好LTDC控制器，GUI控制液晶屏绘制操作时直接往显存写入像素数据即可，非常简单、通用。

-  MPU型液晶屏：类似STM32F103/407这类不自带液晶控制器的MCU，控制液晶屏绘制操作往往需要与外部的液晶控制器通讯，如发送命令、数据等操作，控制起来不如内存型液晶屏简便。

针对不同类型的液晶屏，emXGUI在资料目录“emxgui\arch\GAL”中提供了不同的绘图引擎，具体见图 4‑3。

   |docx012|

图 4‑3 emXGUI提供的不同类型绘图引擎示例

所谓绘图引擎，就是提供给emXGUI控制液晶显示操作的接口，它包含一系列基础绘制函数，而对于像素格式宽度不同的绘制操作，底层是有差异的。示例代码中针对内存型绘图引擎提供了8/16/32位格式的接口，针对MPU型绘图引擎提供了最常用的16位格式接口。

绘图引擎涉及到的绘制操作具体见代码清单 4‑15。

代码清单 4‑15 绘图引擎结构体类型定义（emXGUI_Arch.h文件）

1 /*\*

2 \* @brief 绘图对象，包含相应的绘图操作函数指针

3 \*/

4 typedef struct tagGL_OP {

5

6 FN_GL_SetPos \*SetPos;

7 FN_GL_SetPixel \*SetPixel;

8 FN_GL_GetPixel \*GetPixel;

9 FN_GL_XorPixel \*XorPixel;

10 FN_GL_HLine \*HLine;

11 FN_GL_VLine \*VLine;

12 FN_GL_Line \*Line;

13 FN_GL_FillArea \*FillArea;

14 FN_GL_CopyBits \*CopyBits;

15

16 FN_GL_DrawBitmap_LUT1 \*DrawBitmap_LUT1;

17 FN_GL_DrawBitmap_LUT2 \*DrawBitmap_LUT2;

18 FN_GL_DrawBitmap_LUT4 \*DrawBitmap_LUT4;

19 FN_GL_DrawBitmap_LUT8 \*DrawBitmap_LUT8;

20

21 FN_GL_DrawBitmap_RGB \*DrawBitmap_RGB332;

22 FN_GL_DrawBitmap_RGB \*DrawBitmap_RGB565;

23 FN_GL_DrawBitmap_RGB \*DrawBitmap_XRGB1555;

24 FN_GL_DrawBitmap_RGB \*DrawBitmap_ARGB1555;

25 FN_GL_DrawBitmap_RGB \*DrawBitmap_ARGB4444;

26 FN_GL_DrawBitmap_RGB \*DrawBitmap_RGB888;

27 FN_GL_DrawBitmap_RGB \*DrawBitmap_XRGB8888;

28 FN_GL_DrawBitmap_RGB \*DrawBitmap_ARGB8888;

29

30 FN_GL_DrawBitmap_AL1 \*DrawBitmap_AL1;

31 FN_GL_DrawBitmap_AL2 \*DrawBitmap_AL2;

32 FN_GL_DrawBitmap_AL4 \*DrawBitmap_AL4;

33 FN_GL_DrawBitmap_AL8 \*DrawBitmap_AL8;

34

35 FN_GL_ScaleBitmap \*ScaleBitmap;

36 FN_GL_RotateBitmap \*RotateBitmap;

37

38 } GL_OP;

这个结构体中的内容全是函数指针，包含如获取坐标、绘制像素点、获取像素点、像素点异或运算、绘制各种线段和矩形等操作。以16位内存型绘图引擎GL_MEM_16BPP.c为例，具体见代码清单 4‑16。

代码清单 4‑16 16位内存型绘图引擎的部分代码（GL_MEM_16BPP.c文件）

1 /\* 像素点类型 \*/

2 #define COLOR16 U16

3

4 /*\*

5 \* @brief 根据坐标计算像素点的地址

6 \* @param pSurf 绘图表面

7 \* @param x y 坐标

8 \* @retval 坐标在绘图表面对应的地址

9 \*/

10 #define \__set_addr(pSurf,x,y) (COLOR16*)((U8*)pSurf->Bits + (x*2) + ((y)*pSurf->WidthBytes))

11

12 /*\*

13 \* @brief 绘制单个像素点

14 \* @param pSurf 绘图表面

15 \* @param x y 坐标

16 \* @param 要绘制的颜色

17 \* @retval 坐标在绘图表面对应的地址

18 \*/

19 void GL16_set_pixel(const SURFACE \*pSurf,int x,int y,COLORREF c)

20 {

21 COLOR16 \*addr;

22

23 addr = \__set_addr(pSurf,x,y);

24 \*addr =c;

25 }

26

27 COLORREF GL16_get_pixel(const SURFACE \*pSurf,int x,int y)

28 {

29 COLOR16 \*addr;

30

31 addr = \__set_addr(pSurf,x,y);

32 return \*addr;

33 }

34

35 void GL16_draw_hline(const SURFACE \*pSurf,int x0,int y0,int x1,COLORREF c)

36 {

37 COLOR16 \*addr;

38

39 addr = \__set_addr(pSurf,x0,y0);

40 GUI_memset16(addr,c,x1-x0);

41 }

42

43 /\* ...省略大部分内容...
\*/

44 /\* 给绘图引擎结构体赋值为具体函数 \*/

45 void GL_MEM_16BPP_Init(GL_OP \*gd)

46 {

47 gd->SetPos =GL16_set_addr;

48 gd->SetPixel =GL16_set_pixel;

49 gd->GetPixel =GL16_get_pixel;

50 gd->XorPixel =GL16_xor_pixel;

51 gd->HLine =GL16_draw_hline;

52 gd->VLine =GL16_draw_vline;

53 gd->FillArea =GL16_fill_rect;

54 gd->CopyBits =GL16_copy_bits;

55

56 gd->DrawBitmap_LUT1 =GL16_draw_bitmap_LUT1;

57 gd->DrawBitmap_LUT2 =GL16_draw_bitmap_LUT2;

58 gd->DrawBitmap_LUT4 =GL16_draw_bitmap_LUT4;

59 gd->DrawBitmap_LUT8 =GL16_draw_bitmap_LUT8;

60 gd->DrawBitmap_RGB332 =GL16_draw_bitmap_RGB332;

61 gd->DrawBitmap_RGB565 =GL16_draw_bitmap_RGB565;

62 gd->DrawBitmap_XRGB1555 =GL16_draw_bitmap_XRGB1555;

63 gd->DrawBitmap_ARGB1555 =GL16_draw_bitmap_ARGB1555;

64 gd->DrawBitmap_ARGB4444 =GL16_draw_bitmap_ARGB4444;

65 gd->DrawBitmap_RGB888 =GL16_draw_bitmap_RGB888;

66 gd->DrawBitmap_XRGB8888 =GL16_draw_bitmap_XRGB8888;

67 gd->DrawBitmap_ARGB8888 =GL16_draw_bitmap_ARGB8888;

68

69 gd->DrawBitmap_AL1 =GL16_draw_bitmap_AL1;

70 gd->DrawBitmap_AL2 =GL16_draw_bitmap_AL2;

71 gd->DrawBitmap_AL4 =GL16_draw_bitmap_AL4;

72 gd->DrawBitmap_AL8 =GL16_draw_bitmap_AL8;

73

74 gd->ScaleBitmap =GL16_scale_bitmap;

75 gd->RotateBitmap =GL16_rotate_bitmap;

76 }

77

在这段代码中，先定义了一个__set_addr宏，根据输入的绘图表面、像素点xy坐标计算显存地址，其后的绘制像素点函数GL16_set_pixel、获取像素点函数GL16_get_pixel以及绘制水平线函数GL16_draw_hline则针对具体的地址和颜色赋予像素数据值。其余的绘制操作也类似，具
体可直接查看源码了解。本段代码的最后通过GL_MEM_16BPP_Init函数对输入的绘图引擎结构体gd赋值，赋值内容为以上具体的16位绘制操作函数。在GUI_Startup函数通过调用GUI_Arch_Init会完成这部分绘图引擎的初始化，具体见代码清单 4‑17。

代码清单 4‑17 GUI_Arch_Init函数的内容（GUI_Arch.c文件）

1 GL_OP GL_MEM_8PP;

2 GL_OP GL_MEM_16PP;

3 GL_OP GL_MEM_32PP;

4 /*\*

5 \* @brief GUI架构适配层初始化.

6 \*/

7 BOOL GUI_Arch_Init(void)

8 {

9 \_RectLL_Init(); //初始化GUI内核矩形链表，用于窗口叠加时的Z序管理

10

11 GL_MEM_8BPP_Init(&GL_MEM_8PP); //初始化8位内存型绘图对象.

12 GL_MEM_16BPP_Init(&GL_MEM_16PP); //初始化16位内存型绘图对象.

13 GL_MEM_32BPP_Init(&GL_MEM_32PP); //初始化32位内存型绘图对象.

14

15 return TRUE;

16 }

若不是有特殊的应用需求，在移植时通常不需要修改绘图引擎相关的内容，直接根据液晶屏的类型把相应的绘图引擎文件添加到工程即可。

如果有硬件加速器，则可根据具体的平台进行定制，例如STM32F429具有DMA2D外设，可以加速直线、矩形以及部分颜色转换的操作，那么可通过修改绘图引擎接口提升emXGUI的绘制性能。

配置液晶驱动
^^^^^^

由于绘图引擎已包含丰富的绘制接口，所以液晶驱动主要是提供液晶初始化和背光控制的内容，具体见代码清单 4‑18。

代码清单 4‑18 液晶驱动接口（gui_lcd_port.c文件）

1 /*\*

2 \* @brief 液晶屏初始化接口

3 \* @param fb_addr 要使用的显存地址

4 \*/

5 void LCD_HardInit(u32 fb_addr)

6 {

7 /\* 初始化液晶屏 \*/

8 #if (LCD_FORMAT == COLOR_FORMAT_RGB565)

9 LCD_Init(fb_addr, 33, LTDC_Pixelformat_RGB565);

10 #endif

11

12 #if (LCD_FORMAT == COLOR_FORMAT_XRGB8888)

13 LCD_Init(fb_addr, 21, LTDC_Pixelformat_ARGB8888);

14 #endif

15

16 }

17

18 /*\*

19 \* @brief 液晶背光控制接口

20 \* @param on 1为亮，其余值为灭

21 \*/

22 void LCD_BkLight(int on)

23 {

24 LCD_BackLed_Control(on);

25 }

代码中的液晶初始化接口LCD_HardInit接收参数fb_addr作为显存地址，函数的内部根据gui_drv_cfg.h文件中的宏LCD_FORMAT使用不同的参数初始化STM32的LTDC外设，分为RGB565和XRGB8888格式，不同格式的主要区别是LTDC层的像素格式和像素时钟频率的差异，
初始化时调用了底层驱动文件bsp_lcd.c中的LCD_Init函数，该函数的函数声明见代码清单 4‑19，具体源码请直接在工程中查看。

代码清单 4‑19 LCD_Init函数（bsp_lcd.c文件）

1 /*\*

2 \* @brief LCD初始化

3 \* @param fb_addr 显存首地址

4 \* @param lcd_clk_mhz 像素时钟频率，

5 RGB565格式推荐为30~33，

6 XRGB8888格式推荐为20~22

7 极限范围为15~52，其余值会超出LTDC时钟分频配置范围

8 \* @param pixel_format 像素格式，如LTDC_Pixelformat_ARGB8888 、

9 LTDC_Pixelformat_RGB565等

10 \* @retval None

11 \*/

12 void LCD_Init(uint32_t fb_addr,

13 int lcd_clk_mhz,

14 uint32_t pixel_format );

LCD_Init函数主要是根据具体的液晶屏时序配置不同的LTDC参数，关于LTDC的驱动原理请参考野火的《零死角玩转STM32》教程，STM32F429的LTDC支持使用两个液晶层进行混合效果显示，不过使用多层时数据量太大，驱动液晶屏时像素时钟无法调高，导致存在闪屏现象（特别是ARGB8888双层显
示时），而且emXGUI并不需要使用到双层混合效果的功能，所以本示例都只使用了LTDC的单层显示。

配置默认字体
~~~~~~

emXGUI推荐使用XFT作为默认字体显示字符，可通过gui_font_port.c文件进行配置。在emXGUI的目录“emxgui\resource\xft_font”提供了部分示例字体资源文件，具体见图 4‑4。

|docx013|

图 4‑4 XFT字体示例数据

示例文件中的命名格式为“编码库_字体宽度_平滑度”，如图 4‑4包含ASCII和GB2312两种字体编码；字体宽度值表示字符横向占据的像素个数；平滑度越高，字体边沿的锯齿越不明显，显示的字符效果越好。

这些字体资源文件是使用配套的字体生成器得到的（目前还没有发布），以ASCII_20_4BPP.c文件文件为例，它的内容具体见代码清单 4‑20。

代码清单 4‑20 ASCII_20_4BPP字体资源文件的内容（ASCII_20_4BPP.c文件）

1 const char ASCII_20_4BPP[]= {

2 88,70,84,0,88,71,85,73,32,70,111,110,116,0,0,0,

3 0,0,0,0,16,83,0,0,16,115,0,0,64,0,0,0,

4 212,0,0,0,10,0,100,0,20,0,20,0,4,0,0,0,

5 /*..省略大部分内容..*/

6 }

可以看到，字体资源就是一个超大数组，使用时把需要的字体资源的添加到工程，然后调用库函数XFT_CreateFont创建字体句柄，即可使用该字体进行显示，下面以创建默认字体的GUI_Default_FontInit函数为例进行说明，具体见代码清单 4‑21。

代码清单 4‑21创建默认字体（gui_font_port.c文件）

1

2 extern const char ASCII_20_4BPP[];

3 /*\*

4 \* @brief GUI默认字体初始化

5 \* @param 无

6 \* @retval 返回默认字体的句柄

7 \*/

8 HFONT GUI_Default_FontInit(void)

9 {

10 HFONT hFont=NULL;

11 /*..此处省略从外部SPI-FLASH加载字体数据的方式..*/

12 /\* 使用内部FLASH中的数据（工程中的C语言数组）

13 \* 添加字体数据时，把数组文件添加到工程，在本文件头添加相应字体数组的声明，

14 \* 然后调用XFT_CreateFont函数创建字体即可

15 \*/

16 if (hFont==NULL) {

17 /\* 从本地加载(本地数组数据) \*/

18 hFont =XFT_CreateFont(ASCII_20_4BPP); /*ASCii字库,20x20,4BPP抗锯齿*/

19

20 /\* 中文字库存储占用空间非常大，不推荐放在内部FLASH \*/

21 //hFont =XFT_CreateFont(GB2312_16_2BPP); /*GB2312字库,16x16,2BPP抗锯齿*/

22 //hFont =XFT_CreateFont(GB2312_20_4BPP); /*GB2312字库,20x20,4BPP抗锯齿*/

23 }

24 return hFont;

25 }

在这段代码的开头，声明了在ASCII_20_4BPP.c定义的外部变量ASCII_20_4BPP，然后把它作为输入参数调用库函数XFT_CreateFont，函数执行后返回字体句柄hFont，在GUI_Startup函数内再通过库函数GUI_SetDefFont以hFont作为输入参数设置为默认字体
。

注意ASCII编码不支持中文，而支持中文的任何一个GB2312编码字体资源文件都非常大，不建议直接以数组的方式添加到工程，这样会占用宝贵的MCU内部FLASH空间，在后续的教程中我们会讲解增加外部资源接口，把字体资源文件放置在外部SPI-FLASH，节省MCU的内部FLASH空间。

扩展触摸屏支持
~~~~~~~

emXGUI支持使用鼠标、键盘及触摸屏作为输入设备，本示例以触摸屏进行讲解。

输入设备接口
^^^^^^

在gui_drv_cfg.h文件包含有输入设备的配置宏，具体见代码清单 4‑22。

代码清单 4‑22 输入设备配置（gui_drv_cfg.h文件）

1 /\* 是否使用输入设备 \*/

2 #define GUI_INPUT_DEV_EN 1

3

4 /\* 是否使能键盘、鼠标、触摸屏 \*/

5 #define GUI_TOUCHSCREEN_EN 1

6 #define GUI_KEYBOARD_EN 0

7 #define GUI_MOUSE_EN 0

8

9 /\* 是否需要触摸校准-电阻屏才需要 \*/

10 #define GUI_TOUCHSCREEN_CALIBRATE 0

以上的宏会影响gui_input_port.c文件中的条件编译，使用电容触摸屏时，需要使能宏GUI_INPUT_DEV_EN和GUI_TOUCHSCREEN_EN，gui_input_port.c文件的内容具体见代码清单 4‑23。

代码清单 4‑23 输入设备初始化与处理接口（gui_input_port.c文件）

1 /*\*

2 \* @brief GUI输入设备的初始化

3 \* @param 无

4 \* @retval 是否初始化正常

5 \*/

6 BOOL GUI_InputInit(void)

7 {

8 BOOL state = FALSE;

9 #if(GUI_KEYBOARD_EN)

10 {

11 state = KeyBoardDev_Init();

12 }

13 #endif

14

15 #if(GUI_TOUCHSCREEN_EN)

16 {

17 state = TouchDev_Init();

18 if (state) { /*触摸屏设备初始化*/

19 #if(GUI_TOUCHSCREEN_CALIBRATE)

20 TS_CFG_DATA ts_cfg;

21 if (TouchDev_LoadCfg(&ts_cfg)) { /*加载校正数据(电阻屏需要)*/

22 TouchPanel_TranslateInit(&ts_cfg); /*初始化坐标转换函数(电阻屏需要)*/

23 }

24 #endif

25 }

26

27 }

28 #endif

29

30 #if(GUI_MOUSE_EN)

31 {

32 state = MouseDev_Init();

33 }

34 #endif

35 return state;

36 }

37

38 /*===================================================================*/

39

40 /*\*

41 \* @brief GUI输入设备的定时处理函数

42 \* @note 该函数需要被定时执行，

43 \* 如使用独立的线程调用 或 在桌面的定时器消息中调用

44 \*

45 \* @param 无

46 \* @retval 无

47 \*/

48 void GUI_InputHandler(void)

49 {

50

51 #if(GUI_KEYBOARD_EN)

52 {

53 if (KeyBoardDev_IsActive())

54 {

55 KeyBoardDev_Handler();

56 }

57 }

58 #endif

59

60 #if(GUI_TOUCHSCREEN_EN)

61 {

62 GUI_TouchHandler(); //调用触摸屏处理函数

63 }

64 #endif

65

66 #if(GUI_MOUSE_EN)

67 {

68 if (MouseDev_IsActive())

69 {

70 MouseDev_Handler();

71 }

72 }

73 #endif

74 }

本文件是输入设备的统一接口，只是简单地调用了鼠标、键盘及触摸屏相应的初始化和处理函数，需要针对具体的设备定制驱动接口。

代码中的GUI_InputInit接口用于初始化输入设备，初始化触摸设备时调用了TouchDev_Init接口。

GUI_InputHandler接口用于处理输入设备传回的信息，需要定时调用，可以创建一个独立的操作系统任务调用该接口，也可以在emXGUI桌面的回调函数中通过定时器定时处理。其中触摸设备的信息处理通过调用GUI_TouchHandler接口实现。

代码清单 4‑24 示例代码中在桌面回调函数定时处理输入设备信息（gui_desktop.c文件）

1 /*\*

2 \* @brief 桌面回调函数

3 \* @param hwnd 当前处理该消息的窗口对象句柄

4 \* @param msg 消息类型值，用以标识和区分当前产生的消息

5 \* @param wParam 消息参数值，根据msg消息代码值不同

6 \* @param lParam 消息参数值，根据msg消息代码值不同

7 \* @retval 返回给SendMessage的值

8 \*/

9 static LRESULT desktop_proc(HWND hwnd,

10 UINT msg,

11 WPARAM wParam,

12 LPARAM lParam)

13 {

14 switch (msg) {

15 /\* 桌面创建时,会产生该消息,可以在这里做一些初始化工作.
\*/

16 case **WM_CREATE**:

17 ////创建1个20ms定时器，处理循环事件.

18 SetTimer(hwnd,1,20,TMR_START,NULL);

19 /*..省略部分内容..*/

20 break;

21

22 /\* 定时处理输入设备的信息 \*/

23 case **WM_TIMER**: {

24 u16 id;

25 id =LOWORD(wParam);

26 if (id==1)

27 GUI_InputHandler(); //处理输入设备

28 }

29 break;

30 /*..省略部分内容..*/

31

32 /\* 用户不关心的信息，由系统处理 \*/

33 default:

34 return DefDesktopProc(hwnd,msg,wParam,lParam);

35 }

36 return WM_NULL;

37 }

这个回调函数与输入设备相关的主要是WM_CREATE和WM_TIMER处理分支，WM_CREATE是桌面窗口创建时会执行的分支，此处创建了一个20ms的定时器，每20ms时间到后会进入WM_TIMER分支，在该分支下我们直接调用GUI_InputHandler处理输入设备的信息。实际应用中可根据需要
调整定时间隔。

触摸设备接口
^^^^^^

以上触摸设备控制相关的接口位于gui_touch_port.c文件，具体见代码清单 4‑25。

代码清单 4‑25 触摸设备的控制接口（gui_touch_port.c文件）

1 /*\*

2 \* @brief 触摸初始化接口,会被gui_input_port.c文件的GUI_InputInit函数调用

3 \* @note 需要在本函数初始化触摸屏相关硬件

4 \* @retval 是否初始化正常

5 \*/

6 BOOL TouchDev_Init(void)

7 {

8 /\* 初始化配套的5/7寸屏 \*/

9 if (**GTP_Init_Panel**\ () == 0)

10 return TRUE;

11 else

12 return FALSE;

13 }

14

15 /*\*

16 \* @brief 获取触摸状态及坐标，不需要用户修改

17 \* @note 本函数依赖GTP_Execu接口，该接口需要返回触摸坐标和是否被按下的状态，

18 \* 本例子在bsp_touch_gt9xx.c文件实现

19 \* @param pt[out] 存储获取到的x y坐标

20 \* @retval 触摸状态

21 \* @arg TS_ACT_DOWN 触摸按下

22 \* @arg TS_ACT_UP 触摸释放

23 \* @arg TS_ACT_NONE 无触摸动作

24 \*/

25 BOOL TouchDev_GetPoint(POINT \*pt)

26 {

27 static int ts_state=TS_ACT_NONE;

28

29 /\* 通过GTP_Execu获取触摸坐标和状态 \*/

30 if (**GTP_Execu**\ (&pt->x,&pt->y) > 0)

31 ts_state =TS_ACT_DOWN;

32 else {

33 if (ts_state==TS_ACT_DOWN)

34 ts_state =TS_ACT_UP;

35 else

36 ts_state =TS_ACT_NONE;

37 }

38 return ts_state;

39 }

40

41 /*\*

42 \* @brief 需要被定时调用的触摸处理函数

43 \* @note 本例子中通过gui_input_port.c文件的GUI_InputHandler被定时调用

44 \* @param 无

45 \* @retval 无

46 \*/

47 void GUI_TouchHandler(void)

48 {

49 int act;

50 POINT pt;

51

52 /\* 判断触摸状态及坐标 \*/

53 act =TouchDev_GetPoint(&pt);

54 if (act==TS_ACT_DOWN) {

55 /\* 触摸按下，使用触摸坐标作为输入 \*/

56 MouseInput(pt.x,pt.y,MK_LBUTTON);

57 }

58

59 if (act==TS_ACT_UP) {

60 /\* 触摸释放，使用当前光标作为输入*/

61 GetCursorPos(&pt);

62 MouseInput(pt.x,pt.y,0);

63 }

64 }

这部分代码说明如下：

-  TouchDev_Init函数，其功能为初始化触摸设备，它通过调用bsp_touch_gt9xx.c文件提供的触摸屏初始化函数GTP_Init_Panel实现。

-  TouchDev_GetPoint函数，它的功能为读取触摸坐标，并返回触摸屏的状态（按下、释放、无操作），它通过调用bsp_touch_gt9xx.c文件中的GTP_Execu函数初始，GTP_Execu函数根据原驱动中的Goodix_TS_Work_Func函数修改而来，只读取一个触摸点，并且按
  照emXGUI接口的要求返回状态，关于触摸屏的控制原理请参考《零死角玩转STM32》教程。

-  GUI_TouchHandler函数，它会被代码清单 4‑23的GUI_InputHandler函数调用，定时处理触摸屏的信息。该函数调用前面的TouchDev_GetPoint获取触摸状态和坐标，若是触摸按下状态，那么调用emXGUI库函数MouseInput传入最新的触摸坐标，并且使用参数MK
  _LBUTTON表示点击鼠标的左键；若是触摸释放状态，则调用库函数GetCursorPos获取当前鼠标的坐标，然后再调用MouseInput传入当前鼠标的坐标，并使用输入参数“0”表示鼠标按键的释放。

配置触摸驱动时需要注意，原bsp_touch_gt9xx.c文件中使用了中断读取触摸坐标，而本示例中emXGUI定时通过定时调用GUI_TouchHandler函数处理触摸信息，所以触摸驱动中需要关闭触摸中断。

扩展外部资源设备
~~~~~~~~

图形界面应用常常需要字体、图片等非常大的数据资源，而MCU宝贵的内部FLASH空间通常用于存储程序，所以推荐扩展外部资源设备的接口为emXGUI提供数据内容，常用的外部资源设备有SPI-FLASH和SD卡。

外部资源设备接口
^^^^^^^^

本示例以SPI-FLASH作为外部资源设备进行讲解，其接口具体见代码清单 4‑26。

代码清单 4‑26资源设备访问接口（gui_resource_port.c文件）

1 /*访问资源设备的互斥信号量*/

2 static GUI_MUTEX \*mutex_lock=NULL;

3

4 /*\*

5 \* @brief 初始化资源设备（外部FLASH）

6 \* @param 无

7 \* @retval 是否初始化正常

8 \*/

9 BOOL RES_DevInit(void)

10 {

11 mutex_lock=GUI_MutexCreate();

12

13 if (SPI_FLASH_Init() == 0)

14 return TRUE;

15 else

16 return FALSE;

17 }

18

19 /*\*

20 \* @brief 向设备写入内容

21 \* @param buf 要写入的内容

22 \* @param addr 写入的目标地址

23 \* @param size 写入的数据量（size不应超过BLOCK大小）

24 \* @retval 是否写入正常

25 \*/

26 BOOL RES_DevWrite(u8 \*buf,u32 addr,u32 size)

27 {

28 GUI_MutexLock(mutex_lock,5000);

29 SPI_FLASH_SectorErase(addr&0xFFFFF000);

30 SPI_FLASH_BufferWrite(buf,addr,size);

31 GUI_MutexUnlock(mutex_lock);

32 return TRUE;

33 }

34

35 /*\*

36 \* @brief 从设备中读取内容

37 \* @param buf 存储读取到的内容

38 \* @param addr 读取的目标地址

39 \* @param size 读取的数据量

40 \* @retval 是否读取正常

41 \*/

42 BOOL RES_DevRead(u8 \*buf,u32 addr,u32 size)

43 {

44 GUI_MutexLock(mutex_lock,5000);

45

46 SPI_FLASH_BufferRead(buf,addr,size);

47 GUI_MutexUnlock(mutex_lock);

48 return TRUE;

49 }

50

51 /*\*

52 \* @brief 擦除扇区

53 \* @param addr 要擦除的扇区地址

54 \* @retval 扇区的字节数

55 \*/

56 int RES_DevEraseSector(u32 addr)

57 {

58 GUI_MutexLock(mutex_lock,5000);

59 SPI_FLASH_SectorErase(addr&0xFFFFF000);

60 GUI_MutexUnlock(mutex_lock);

61 return SPI_FLASH_SectorSize;

62 }

代码中包含了函数RES_DevInit、RES_DevWrite、RES_DevRead、RES_DevEraseSector，分别用于初始化资源设备、写入数据、读取数据以及擦除扇区，它们都是简单地调用了底层驱动文件bsp_spi_flash.c中相关的函数，实现对外部SPI-FLASH的访问。

外部资源存储结构
^^^^^^^^

为了提高访问速度，示例中的SPI-FLASH没有使用文件系统管理资源文件，它们都是直接以二进制数据的方式写入到FLASH中的，而只存储二进制数据由不便于管理，所以我们增加了资源目录以便对FLASH内的资源文件进行定位寻址，具体资源分配如表格 4‑4所示。

表格 4‑4 资源的目录管理

========================== ===================== ==================== ========================
地址　                     内容
========================== ===================== ==================== ========================
资源基地址(目录的首地址)   资源A的名字（24字节） 资源A的大小（4字节） 资源A的偏移地址（4字节）
…                          资源B的名字（24字节） 资源B的大小（4字节） 资源B的偏移地址（4字节）
…                          资源C的名字（24字节） 资源C的大小（4字节） 资源C的偏移地址（4字节）
资源基地址+目录总大小      …
资源基地址+资源A的偏移地址 资源A的内容
…
…
资源基地址+资源B的偏移地址 资源B的内容
…
资源基地址+资源B的偏移地址 资源C的内容
…                          …
========================== ===================== ==================== ========================

也就是说，假如资源设备上存储了A/B/C文件，那么可以在资源基地址开头的目录中找到A/B/C文件的文件名、文件大小以及文件数据在资源设备的偏移地址，方便检索信息。目录中的每一项都是由代码清单 4‑27中的结构体CatalogTypeDef组成。

代码清单 4‑27 目录项的结构体类型（gui_resource_port.h文件）

1 /\* 目录信息类型 \*/

2 typedef struct {

3 char name[24]; /\* 资源的名字 \*/

4 u32 size; /\* 资源的大小 \*/

5 u32 offset; /\* 资源相对于基地址的偏移 \*/

6 } CatalogTypeDef;

以上信息是往SPI-FLASH中写入资源文件时记录到目录中的，目录中每一项大小为24+4+4=32字节，在查找资源文件时，我们每次从FLASH的目录中读取一项，把目标资源文件名与目录信息中的“name”进行比对，若一致的话，再查看相应的“offset”计算出资源所在的地址，具体的实现见代码清单
4‑28。

代码清单 4‑28 获取资源信息_绝对地址（gui_drv_cfg.h和gui_resource_port.c文件）

1 /第1部分/

2 /*..gui_drv_cfg.h文件..*/

3 /\* 是否使用资源设备 \*/

4 #define GUI_RES_DEV_EN 1

5 /\* 资源所在的基地址 \*/

6 #define GUI_RES_BASE 4096

7 /\* 存储在FLASH中的资源目录大小 \*/

8 #define GUI_CATALOG_SIZE 4096

9

10 /第2部分/

11 /*..gui_resource_portc文件..*/

12 /*\*

13 \* @brief 从FLASH中的目录查找相应资源的信息

14 \* @param res_base 目录在FLASH中的基地址

15 \* @param res_name[in] 要查找的资源名字

16 \* @param dir[out] 要查找的资源名字

17 \* @note 此处dir.offset会被赋值为资源的绝对地址！！

18 \* @retval -1表示找不到，其余值表示资源在FLASH中的基地址

19 \*/

20 s32 RES_GetInfo_AbsAddr(const char \*res_name, CatalogTypeDef \*dir)

21 {

22 int i,len;

23

24 len =x_strlen(res_name);

25 /第3部分/

26 /\* 根据名字遍历目录 \*/

27 for (i=0; i<GUI_CATALOG_SIZE; i+=32) {

28 RES_DevRead((u8*)dir,GUI_RES_BASE+i,32);

29 if (x_strncasecmp(dir->name,res_name,len)==0) {

30 /第4部分/

31 /\* dir.offset是相对基地址的偏移，此处返回绝对地址 \*/

32 dir->offset += GUI_RES_BASE;

33 return dir->offset ;

34 }

35 }

36 return -1;

37 }

这段代码说明如下：

-  第1部分。这是在gui_drv_cfg.h头文件定义的宏，宏GUI_RES_DEV_EN用于设置是否使用外部资源设备；宏GUI_RES_BASE设置资源所在的基地址，也就是目录在FLASH中的首地址，此处配置为4096，是由烧录资源数据的程序决定的；宏GUI_CATALOG_SIZE设置目录的大小
  ，它也是由烧录资源数据的程序决定的，此处的值为4096，即最多记录4096/32=128项资源文件。

-  第2部分。函数RES_GetInfo_AbsAddr，其功能是根据输入的资源名res_name，在FLASH中查找资源的大小、绝对地址信息，若返回值小于0，说明找不到资源，若大于0，则输入的dir指向的目录结构会包含该资源的信息。

-  第3部分。函数RES_GetInfo_AbsAddr内部通过for循环每次读取FLASH中目录的32字节，并把读取到的资源名字dir->name与输入的res_name进行对比。

-  第4部分。若资源名字与输入的res_name匹配，那么给读取到的dir->offset加上基地址GUI_RES_BASE并返回。函数执行结束时dir->offset包含的即是资源文件在FLASH中的绝对地址。

后面将会介绍利用RES_GetInfo_AbsAddr函数获取字体资源文件的地址，并加载外部字体的示例。

烧录数据到资源设备
^^^^^^^^^

我们提供了一个示例工程“刷外部FLASH程序（烧录emXGUI资源文件）”，它用于从SD卡拷贝数据到FLASH，并且拷贝时会生成表格 4‑4中的目录，使用该程序时，可配置res_mgr.h文件修改资源目录的首地址和目录的大小。

代码清单 4‑29 烧录资源的配置（res_mgr.h文件）

1 /\* 资源在SD卡中的路径 \*/

2 #define RESOURCE_DIR "0:/srcdata"

3 /\* 资源烧录到的FLASH基地址（目录地址） \*/

4 #define RESOURCE_BASE_ADDR 4096

5 /\* 存储在FLASH中的资源目录大小 \*/

6 #define CATALOG_SIZE 4096

7

使用该工程时，需要准备一张SD卡，使用电脑在SD卡的根目录下建立一个文件夹“srcdata”，把需要拷贝的资源文件放置到该目录，这个“srcdata”就是资源文件的数据来源，即res_mgr.h文件中宏RESOURCE_DIR表示的路径。

而拷贝到FLASH的目录基地址和目录大小则由宏RESOURCE_BASE_ADDR和CATALOG_SIZE进行配置，以上代码配置均为4096，表示资源目录在FLASH的起始地址为4096，大小也为4096。前面代码清单 4‑28中的资源基地址和目录地址就是根据这个设置的。

下面以烧录中文字体为例，我们在SD卡的srcdata目录下存放GB2312_16_4BPP.xft、GB2312_20_4BPP.xft、GB2312_24_4BPP.xft字体文件，注意使用字体资源时不要使用“C”后缀的数组文件。

|docx014|

图 4‑5 示例资源文件

复制完毕后把SD卡插到开发板，然后下载“刷外部FLASH程序（烧录emXGUI资源文件）”程序运行，打开串口调试助手可看到开发板返回的信息，提示按按键“KEY1”开始烧录，并且包含具体文件的烧录信息。

|docx015|

图 4‑6 程序运行的输出信息

烧录完成时串口会输出校验正常的提示，此时SPI-FLASH中包含带目录的字体资源文件。

使用外部字体文件
~~~~~~~~

扩展了外部资源设备接口并烧录了字体资源文件后，emXGUI即可利用这些字体显示字符。使用外部字体文件主要有两种方式：

-  初始化字体时把整个字体文件加载到RAM（内部SRAM、外部SDRAM等），显示字符时从RAM得到字体数据进行显示；

-  通过流设备加载字体，在显示字符时emXGUI根据需要从资源设备中加载。

简单来说，整体加载方式在初始化的时候就把整个字体文件从FLASH加载到RAM，然后显示的时候从RAM中读取具体的字符数据；而流设备加载的方式则是显示的时候才从FLASH中读取具体的字符数据。

由于资源设备如SPI-FLASH或SD卡的读取速度明显慢于RAM设备，所以使用流设备加载字体的方式显示的速度稍慢，但好处是节省了宝贵的RAM空间，应用时请根据需求进行取舍。

加载整个字体文件到RAM
^^^^^^^^^^^^

加载整个字体文件到RAM的方式比较简单，相比前面《\ **错误!未找到引用源。错误!未找到引用源。**\ 》小节中使用数组文件创建默认字体，只是增加了字体文件的读取过程，它们都采用库函数XFT_CreateFont创建字体句柄。

本示例在创建默认字体时包含有整体加载方式的演示，具体见代码清单 4‑30。

代码清单 4‑30 整体加载字体文件到RAM（gui_font_port.c文件）

1 /*\*

2 \* @brief GUI默认字体初始化

3 \* @param 无

4 \* @retval 返回默认字体的句柄

5 \*/

6 HFONT GUI_Default_FontInit(void)

7 {

8 /\* 整个字体文件加载至RAM \*/

9

10 int font_base;

11

12 /\* 指向缓冲区的指针 \*/

13 static u8 \*pFontData_XFT=NULL;

14 CatalogTypeDef dir;

15

16 /\* RES_GetInfo读取到的dir.offset是资源的绝对地址 \*/

17 font_base =RES_GetInfo_AbsAddr("GB2312_24_4BPP.xft", &dir);

18

19 if (font_base > 0) {

20 pFontData_XFT =(u8*)GUI_VMEM_Alloc(dir.size);

21 if (pFontData_XFT!=NULL) {

22 RES_DevRead(pFontData_XFT, font_base, dir.size);

23

24 hFont = XFT_CreateFont(pFontData_XFT);

25 }

26 }

27

28 /*..省略部分内容..*/

29 return hFont;

30 }

这是初始化默认字体GUI_Default_FontInit函数中的流设备加载部分，它的执行过程如下：

(1) 调用外部资源接口RES_GetInfo_AbsAddr读取字体“GB2312_24_4BPP.xft”的目录信息，主要是为了得到该字体文件在FLASH的基地址font_base和整个字体文件的大小dir.size；

(2) 根据字体文件的大小，调用GUI_VMEM_Alloc从VMEM申请dir.size大小的空间，使用指针pFontData_XFT指向该空间；

(3) 调用外部资源接口RES_DevRead读取整个字体文件数据，读取数据的基地址为前面得到的字体基地址font_base，要读取的数据大小为dir.size表示整个字体文件，读取得的数据存储在申请得到的pFontData_XFT指向的空间。

(4) 调用库函数XFT_CreateFont创建字体，直接把字体文件在VMEM的基地址pFontData_XFT作为输入参数即可。

(5) 调用XFT_CreateFont创建得到的字体句柄hFont被返回，可在GUI_Startup函数中设置为默认字体。

由于步骤（3）中读取整个字体文件到RAM的过程比较长，所以这种方式在初始化的时候需要等上一会儿，其后显示时直接访问RAM的数据，速度非常快。示例字体数据的大小超过2MB，所以用这种方式要注意RAM空间是否足够。

(6)

使用流设备加载字体
^^^^^^^^^

使用流设备方式加载字体需要使用到库函数XFT_CreateFontEx（Ex表示extern）实现，该函数接受两个输入参数，分别是读取外部设备数据的回调函数以及自定义的输入参数，具体见代码清单 4‑31。

代码清单 4‑31 XFT_CreateFontEx和它使用的回调函数（gui_font_port.h文件）

1 /*\*

2 \* @brief XFT_CreateFontEx使用的回调函数指针定义

3 \* @param buf[out] 存储读取到的数据缓冲区

4 \* @param offset 要读取的位置

5 \* @param size 要读取的数据大小

6 \* @param lParam 调用函数时的自定义参数（用户参数）

7 \* @retval 读取到的数据大小

8 \*/

9 typedef int (FN_XFT_GetData)(void \*buf,int offset,int size,LONG lParam);

10

11 /*\*

12 \* @brief XFT_CreateFontEx使用外部字体

13 \* @param FN_XFT_GetData 加载数据的函数指针

14 \* @param lParam 调用函数FN_XFT_GetData时传入自定义参数（用户参数）

15 \* @retval 创建得到的字体句柄

16 \*/

17 HFONT XFT_CreateFontEx(FN_XFT_GetData \*pfnGetData,LONG lParam);

通过XFT_CreateFontEx创建字体后，在显示字符时它会调用创建字体句柄时XFT_CreateFontEx输入的FN_XFT_GetData型函数指针，并向该函数传入buf、offset、size以及lParam参数，FN_XFT_GetData型函数指针根据输入参数从外部FLASH中读取数
据存储至buf，然后字符显示函数根据读取得的buf数据处理显示。

本示例在创建默认字体时包含有流设备加载方式的演示，具体见代码清单 4‑32。

代码清单 4‑32 使用流设备加载默认字体（gui_font_port.c文件）

1 /第1部分/

2 /*\*

3 \* @brief 从流媒体加载内容的回调函数

4 \* @param buf[out] 存储读取到的数据缓冲区

5 \* @param offset 要读取的位置

6 \* @param size 要读取的数据大小

7 \* @param lParam 调用函数时的自定义参数（用户参数）

8 \* @retval 读取到的数据大小

9 \*/

10 static int font_read_data_exFlash(void \*buf,int offset,int size,LONG lParam)

11 {

12 /\* 本例子中offset是具体字符数据在字体文件中的偏移

13 \* lParam 是字体文件在FLASH中的基地址

14 \*/

15 offset += lParam;

16

17 /\* 读取具体的字模数据内容 \*/

18 RES_DevRead(buf,offset,size);

19 return size;

20 }

21

22 /第2部分/

23 /*\*

24 \* @brief GUI默认字体初始化

25 \* @param 无

26 \* @retval 返回默认字体的句柄

27 \*/

28 HFONT GUI_Default_FontInit(void)

29 {

30 HFONT hFont=NULL;

31 /*..省略部分内容..*/

32 /\* 使用流设备加载字体，按需要读取 \*/

33 if (hFont==NULL) {

34 int font_base;

35 CatalogTypeDef dir;

36 /\* 从外部资源查找字体相关的目录信息 \*/

37 font_base=RES_GetInfo_AbsAddr("GB2312_24_4BPP.xft", &dir);

38 if (font_base> 0) {

39 hFont =XFT_CreateFontEx(font_read_data_exFlash, font_base);

40 }

41 }

42 /*..省略部分内容..*/

43 return hFont;

44 }

-  第1部分。定义了font_read_data_exFlash 函数，它是FN_XFT_GetData型函数指针的实例，用于流式加载字体数据。其中参数offset是具体字符数据在字体文件中的偏移，而lParam参数则是字体文件在FLASH设备中的基地址，所以在读取具体数据前，我们对offset加上l
  Param得到具体字符数据在FLASH中的绝对地址，最后通过外部资源设备接口RES_DevRead从绝对地址offset中读取size大小的字体数据，存储到buf指向的空间中。

-  第2部分。这是初始化默认字体GUI_Default_FontInit函数中的流设备加载部分，首先调用外部资源接口RES_GetInfo_AbsAddr读取字体“GB2312_24_4BPP.xft”的目录信息，主要是为了得到该字体文件在FLASH的基地址font_base，然后调用库函数XFT_C
  reateFontEx创建字体，以第一部分的font_read_data_exFlash
  作为回调函数，并且以font_base作为自定义参数lParam，所以在font_read_data_exFlash函数中offset加上lParam就可以得到具体字符在FLASH中的“GB2312_24_4BPP.xft”字体数据了。

-  调用XFT_CreateFontEx创建得到的字体句柄hFont被返回，可在GUI_Startup函数中设置为默认字体。

下面以具体的实例进行说明字体数据的加载过程，假设我们创建了字体A和B，字体A在FLASH中的基地址是X，字体B在FLASH中的基地址为Y，它们使用同一个读取字体数据的函数指针R，现在分别使用字体A和字体B显示字符“野火”，那么它们的执行过程如下：

(1) 调用XFT_CreateFontEx创建字体A和B的句柄，给它们输入同样的FN_XFT_GetData函数指针R，而lParam参数不同，创建A时lParam输入的值为它在FLASH中的基地址X，创建B时lParam输入的值为它的基地址Y。

(2) 调用字符显示库函数TextOut，该函数的输入参数包含有显示的坐标和要显示的字符“野火”，若当前使用的字体为A，那么在该函数内部执行时会根据字体的大小、编码计算出“野”字在字体A文件中的偏移offset，以及单个字体数据的大小size，并且给出要接收该字体数据的缓冲区指针buf，创建字体A时
得到的lParam基地址X，把这四个参数传入到函数指针R，获取到“野”字的字体数据，然后进行显示处理；若当前使用的字体为B，执行过程类似，计算出相应的offset、size，并给出缓冲区指针buf，以及字体B的lParam基地址Y，作为参数输入并调用函数指针R得到“野”字的字体数据然后处理；然后再使
用同样的方式显示“火”字。

默认字体配置
^^^^^^

前面为了方便讲解，GUI_Default_FontInit函数被分成整体加载、流设备加载以及数组加载三部分分别讲解，下面把该函数的完整版列出重新说明，具体见代码清单 4‑33。

代码清单 4‑33 完整版的GUI_Default_FontInit函数（gui_font_port.c文件）

1 /*\*

2 \* @brief GUI默认字体初始化

3 \* @param 无

4 \* @retval 返回默认字体的句柄

5 \*/

6 HFONT GUI_Default_FontInit(void)

7 {

8 HFONT hFont=NULL;

9

10 #if (GUI_FONT_LOAD_TO_RAM )

11 {

12 /\* 整个字体文件加载至RAM \*/

13

14 /\* 指向缓冲区的指针 \*/

15 static u8 \*pFontData_XFT=NULL;

16 CatalogTypeDef dir;

17

18 /\* RES_GetInfo读取到的dir.offset是资源的绝对地址 \*/

19 if (RES_GetInfo_AbsAddr(**GUI_DEFAULT_EXTERN_FONT**, &dir) > 0) {

20 pFontData_XFT =(u8*)GUI_VMEM_Alloc(dir.size);

21 if (pFontData_XFT!=NULL) {

22 RES_DevRead(pFontData_XFT, dir.offset, dir.size);

23

24 hFont = XFT_CreateFont(pFontData_XFT);

25 }

26 }

27 }

28 #elif (GUI_USE_EXTERN_FONT)

29 {

30 /\* 使用流设备加载字体，按需要读取 \*/

31 if (hFont==NULL) {

32 int offset;

33 CatalogTypeDef dir;

34

35 offset =RES_GetInfo_AbsAddr(\ **GUI_DEFAULT_EXTERN_FONT**, &dir);

36 if (offset > 0) {

37 hFont =XFT_CreateFontEx(font_read_data_exFlash,offset);

38 }

39 }

40 }

41 #endif

42

43 /\* 若前面的字体加载失败，使用内部FLASH中的数据（工程中的C语言数组）

44 \* 添加字体数据时，把数组文件添加到工程，在本文件头添加相应字体数组的声明，

45 \* 然后调用XFT_CreateFont函数创建字体即可

46 \*/

47 if (hFont==NULL) {

48 /\* 从本地加载(本地数组数据) \*/

49 hFont =XFT_CreateFont(\ **GUI_DEFAULT_FONT**); /*ASCii字库,20x20,4BPP抗锯齿*/

50

51 /\* 中文字库存储占用空间非常大，不推荐放在内部FLASH \*/

52 //hFont =XFT_CreateFont(GB2312_16_2BPP); /*GB2312字库,16x16,2BPP抗锯齿*/

53 //hFont =XFT_CreateFont(GB2312_20_4BPP); /*GB2312字库,20x20,4BPP抗锯齿*/

54 }

55 return hFont;

56 }

相对前面的代码，完整版的主要是增加了条件编译以及使用宏来设置默认字体，这些宏可在gui_drv_cfg.h文件进行配置，具体见代码清单 4‑34。

代码清单 4‑34 默认字体配置（gui_drv_cfg.h文件）

1 /\* 是否使用外部FLASH中的字体

2 \* 流设备和整体加载方式都要把这个宏设置为1

3 \*/

4 #define GUI_USE_EXTERN_FONT 1

5

6 /\*

7 \* 是否把整个外部字体数据加载至VMEM区域，初始化加载时需要较长时间，

8 \* 加载后可大幅提高字符显示的速度

9 \* 若设置为真，则使用整体加载方式，否则使用流设备方式

10 \*/

11 #define GUI_FONT_LOAD_TO_RAM (0 && GUI_USE_EXTERN_FONT)

12

13 /\* 要使用的外部默认字体文件，USE_EXTERN_FONT为1时生效 \*/

14 #define GUI_DEFAULT_EXTERN_FONT "GB2312_24_4BPP.xft"

15

16 /\* 默认内部字体数组名，USE_EXTERN_FONT为0或 外部字体加载失败时会采用的字体 \*/

17 #define GUI_DEFAULT_FONT ASCII_20_4BPP

使用外部SPI-FLASH的字体数据文件时，需要把宏GUI_USE_EXTERN_FONT设置为真值，当宏GUI_FONT_LOAD_TO_RAM设置为真值时，则使用整体加载的方式，否则使用流设备加载方式。而外部字体数据文件的文件名可通过宏GUI_DEFAULT_EXTERN_FONT设置。

若GUI_USE_EXTERN_FONT设置为假或外部数据字体设置失败时，会采用GUI_DEFAULT_FONT配置的数组作为默认字体。

创建桌面
----

桌面窗口是GUI系统创建的第一个窗口，也称作是根窗口，是占据整个GUI屏幕的最底层窗口。桌面窗口是GUI必需存在的唯一根窗口，一旦创建运行后，是不可以被删除销毁的，类似于Windows桌面，每一个应用程序的窗口都是在其上面显示。在学习桌面创建之前，我们先了解一下emXGUI的绘图过程。

绘图表面(Surface)
~~~~~~~~~~~~~

Surface是对绘图设备的描述，其记录了绘图设备的颜色格式，物理像素大小，显示缓冲区，以及绘图引擎（GAL），GUI所有的绘图目标，最终都是在Surface上进行。每个Surface都是一个独立的绘图设备，可以由用户自由创建。函数原型及示例，见代码清单 5‑1。

代码清单 5‑1 创建Surface

1 //函数原型

2 SURFACE\* CreateSurface(SURF_FORMAT Format,U32 nWidth,U32 nHeight,

3 int LineBytes,void \*Bits);

4 //举例说明

5 //创建绘图表面

6 /\* 直接指定地址的方式， 显存地址，*/

7 pSurf = GUI_CreateSurface(SURF_RGB565,

8 LCD_XSIZE,LCD_YSIZE,

9 LCD_XSIZE*2,

10 (void*)LCD_FRAME_BUFFER);

CreateSurface函数参数说明如下：

Format ：Surface的颜色格式，可以是SURF_SCREEN(使用与屏幕相同的格式)， SURF_RGB332，SURF_RGB565，SURF_ARGB4444， SURF_XRGB8888，
SURF_ARGB8888。通过修改宏定义LCD_FORMAT可以实现各种格式的切换。这里我们使用的是RGB565，每个像素占2个字节。

nWidth 、nHeight ：Surface的宽度和高度，一般是LCD的宽度和高度，即宽度（LCD_XSIZE）是800，高度（LCD_YSIZE）是480。

LineBytes ：Surface每行的内存字节数，这个值取决于Surface的颜色格式。如果使用的SURF_ARGB8888，即每个像素占4个字节，则每行的内存字节数等于行的像素数*每个像素的字节数（LCD_XSIZE
\*4）。例子中，我们使用的是RGB565，因此，每行内存字节数为LCD_XSIZE \*2。

Bits：显存的首地址。例程中采用SDRAM作为显存，其首地址为0xD0000000。

绘图上下文(Drawing Context)
~~~~~~~~~~~~~~~~~~~~~~

Drawing Context
简称DC，基本上所有的绘图函数，都需要传入一个DC的对象参数。它保存了各种用户层的绘图参数：如画笔颜色PenColor(作用于画线，框类图形)，画刷颜色BrushColor(作用于填充实心类的图形)，文字颜色TextColor(作用于文本显示相关函数)，字体对象…等等。代码清单
5‑2修改了画刷，画笔以及文字的颜色，用户可以通过对这些参数进行修改来达到改变绘图输出效果。

代码清单 5‑2 代码示例

1 SetBrushColor(hdc,MapRGB(hdc,30,150,30));

2 SetPenColor(hdc,MapRGB(hdc,0,250,0));

3 SetTextColor(hdc,MapRGB(hdc,0,50,100));

窗口及消息机制(Window & Message)
~~~~~~~~~~~~~~~~~~~~~~~~~

窗口类型及特征
^^^^^^^

窗口是对多区域绘图及管理的基本对象元素。emXGUI是原生的多窗口系统，支持同屏下任意数量窗口叠层显示，并且窗口尺寸是不受屏幕分辨率约束的，可以是任意大小和位置。emXGUI的窗口分为以下几类:桌面窗口，主窗口，子窗口/控件，如图 5‑1。

|docx016|

图 5‑1窗口类型

主窗口是由用户在应用程序中创建，是用户图形界面应用程序的主体核心部分。一个应用程序，可以是由一个主窗口构成，也可以是由多个主窗口组成，多个主窗口间，是可以相互叠加及切换的，当然这些具体的应用方式是由用户实际的应用策略来决定，emXGUI只是给用户提供了这些丰富灵活的机制供驱使。当主窗口工作结束时，用
户可以对其进行删除/销毁，以回收不需再使用的资源。

子窗口是限定在主窗口范围内，是属于主窗口的私有资源，一般泛指各种控件：如按钮、复选框、进度条、列表框…等等。在主窗口创建时，可同时为其创建子窗口/控件。灵活运用emXGUI的子窗口/控件相关机制，可以极大提升应用程序代码资源的重用率用高可扩展性。比如，用户可对已有控件的默认行为及外观进行改变；或者用
户需自定义制作一款特殊的私有控件；甚至用户可以将一个复杂的窗口程序制作成一个控件来供使用，比如可以将一个完整播放器的界面控制程序都做成一个控件，以后只要在需要的地方，直接创建这个控件子窗口就可以了…限于本章篇幅，这里不作详说，后续将有章节会详细讲解这些机制的应用实例。当一个控件不需要再使用，用户也同
样可以对其进行删除/销毁；另外在这里，用户需要了解的一项规则是：一个窗口所属的私有资源（如控件，定时器），用户即便不删除/销毁它，当它的被拥有宿主窗口在删除/销毁时，它的私有资源也会被强制删除/销毁。用一个通俗点的方式描述就是：用户创建了一个主窗口A，并为其创建了一个按钮控件B，一个定时器C，当主窗
口A要结束并退出时，用户就算不删除按钮控件B和定时器C，GUI内部也会对这些未释放的资源进行强制删除/销毁。

窗口内部区域及坐标系统
^^^^^^^^^^^

窗口内部区域分为客户区与非客户区。窗口最外边的区域为非客户区，是包括了标题栏，窗口边框。非客户区的绘制内容，默认是由GUI内部处理的，用户可以不去关心，除非用户需要自行定制窗口非客户的外观。除开非客户区之外的地方，称为客户区，用户的绘图区域及子窗口，都是在客户区范围内。

|docx017|

图 5‑2 窗口区域

emXGUI的坐标以像素为单位，X轴向右为正，Y轴向下为正。按不同的窗口区域，坐标系分为屏幕坐标(Screen)，窗口坐标(Window)，客户坐标(Client)。这三类坐标系最明显区别在于坐标原点:屏幕坐标原点在显示设备的第一个物理像素点位置;窗口坐标原点在整个窗口(包括非客户区)的最左上角;客
户坐标在窗口客户区的最左上角。屏幕坐标，窗口坐标，客户坐标之间可以相互转换的，emXGUI给用户提供了相关的API函数，详细请参考API章节(ScreenToClient，WindowToClient，ClientToScreen，…)。在窗口非客户区绘图，应使用GetWindowDC来获得绘图上下
文(DC)， 非客户区的DC，使用的是窗口坐标，坐标原点在窗口最左上角，可以在整个窗口内绘制。在客户区内绘图，使用BeginPaint或GetDC(后续章节会介绍BeginPaint与GetDC的区别)。客户区DC使用的是客户区坐标，坐标原点为客户区最左上角，客户区DC只会在客户区范围内绘图，超出这
个范围内的绘图内容，将会被自动裁减掉。

消息机制概述
^^^^^^

emXGUI是以窗口为基础，以消息传递为运转机制的多窗口系统。通过消息机制，窗口可以响应来自输入设备(键盘，鼠标，触摸屏)的动作，如按键弹起/按下，鼠标/触摸屏位置改变。消息也可以在窗口与窗口间传递，以实现窗口间的交互动作。窗口在创建时，GUI内部会对其绑定一个所属的消息队列(这个过程动作是不需要用
户干预的)。在主窗口创建后，在一个循环里执行获取消息(GetMessage)，派发消息(DispatchMessage)，这样便是整个用户窗口系统的消息泵正常运转了， 获得到的消息将派发到所属窗口的窗口过程函数(WndProc)中。

消息发送方式
^^^^^^

向某个指定的窗口发送消息，按发送方式，可分为同步发送消息(SendMessage)和异步发送消息(PostMessage/PostAsyncMessage) 。

同步消息发送也称为阻塞发送，发送消息时，会阻塞当前线程，直到该消息被目标窗口处理完成后，该函数才会返回，当前线程才能得以继续运行；同步消息是不会进入消息队列的，直接发送到了目标窗口的窗口过程函数。见代码清单 5‑3。示例中的函数参数分别是目标窗口的句柄，消息类型，wParam与lParam。

代码清单 5‑3同步发送消息(SendMessage)示例

1 SendMessage(hwnd,LB_GETTEXT,i,(LPARAM)wbuf);

相反，异步消息发送为非阻塞方式，被发送的消息只是投放目标窗口所属的消息队列中，而不等该消息是否被目标窗口处理便立即返回。emXGUI给用户提供了两个异步发送消息的函数：PostMessage和PostAsyncMessage。这两个函数的区别是:PostMessage发送的消息队列容量长度是固定的，
当这个队列消息已满的情况下，便不能再接收新的消息，也就是说在这个情况下，PostMessage因消息队列容量已满将会丢弃掉新的消息。一个很典型的情况：当窗口被另一个高优先级的任务长时间阻塞时，如果一直往这个窗口PostMessage，那么到一定程度下，该窗口所属的消息队列便会被填满，使得不能再接收到
新的PostMessage。而PostAsyncMessage情况则不同，PostAsyncMessage的发送消息队列容量是不固定的，可以理解为是一个不限长度的可动态增加的链表结构。每次PostAsyncMessage都将会在消息队列增加一条消息，除非GUI内核的动态内存已消耗完。

消息接收与派发(窗口消息循环)
^^^^^^^^^^^^^^^

在用户创建完一个主窗口后，最后将在一个循环中调用GetMessage从消息队列中获取消息。GetMessage是一个阻塞性获取消息的函数，只有消息队列中有消息时，该函数才会返回，并将获取的消息填充到一个MSG的结构体中，见代码清单 5‑4
MSG结构体成员（文件emXGUI.。随后调用DispatchMessage函数将该获取到消息派发到目标窗口过程函数中处理，这个过程也称作为窗口消息循环。消息派发到哪个窗口，这是不需要用户干预的， MSG
结构体中的hwnd参数，已经指明了消息派往的目标窗口。需要注意一点的事，前面说到同步发送的消息(SendMessage)是不会进入消息队列的，而是直接发送到了窗口过程函数(WndProc)，所以GetMessage是不会获取到SendMessage发出的消息的。

代码清单 5‑4 MSG结构体成员（文件emXGUI.h）

1 typedef struct tagMSG {

2 HWND hwnd; //目标窗口

3 UINT message; //消息

4 WPARAM wParam; //参数0

5 LPARAM lParam; //参数1

6 LONG ExtData; //扩展数据

7 UINT time; //消息产生时间

8 } MSG;

该结构体的成员变量说明如下：

1) hwnd：指明了消息派往的目标窗口，也就是目标窗口的句柄。HWND是struct tagWINDOW*的别名。见代码清单 5‑5 HWND类型说明（文件emXGUI.。

代码清单 5‑5 HWND类型说明（文件emXGUI.h）

1 typedef struct tagWINDOW\* HWND;

2) message：用户发送消息内容，可以是常用的系统标准消息类型，也可以是用户自己定义的消息。请注意，如果是用户自定义的消息类型，则起始值需要从WM_USER开始，见代码清单 5‑6
用户自定义消息类型（文件emXGUI.。对于用户自定义消息，wParam和lParam参数的含义也完全同用户自己约定。用户自定义的消息后，便可以像系统标准消息相同的方式来使用。比如用SendMessage或PostMessage来发送到某个指定的窗口，该窗口过程函数就会接收到用户自定义的消息。

代码清单 5‑6 用户自定义消息类型（文件emXGUI.h）

1 #define WM_USER 0x8000 //0x8000-0xFFFF for user custom

2 //用户自定义消息（emXGUI.h文件没有以下宏，只是举个例子来说明）

3 #define MY_MSG_0 WM_USER+1

4 #define MY_MSG_1 WM_USER+2

5 #define MY_MSG_2 WM_USER+3

3) wParam和lParam：发送消息附带的参数。每个消息类型的参数都不同，可以是空值，即没有参数。

4) ExtData：

5) time：用于记录消息的产生时间，赋值过程由内部函数完成，不需要用户编写。

代码清单 5‑7中，while循环中调用GetMessage从消息队列中获取消息。收到消息后，调用TranslateMessage函数实现由按键消息转换产生字符消息。最后通过DispatchMessage函数将消息发送到目标窗口。

代码清单 5‑7 窗口消息循环的示例代码

1 //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。

2 while (GetMessage(&msg,hwnd)) /*获取消息。*/

3 {

4 TranslateMessage(&msg);/*消息转换,由按键消息(WM_KEYDOWN)转换产生字符消息(WM_CHAR)。*/

5 DispatchMessage(&msg);/*派发消息。*/

6 }

当目标窗口收到消息后，会执行消息处理回调函数。用户创建主窗口时，需要提供一个为“消息处理回调函数”的函数地址。该函数即为窗口过程函数，是用户响应处理窗口消息的地方。在窗口过程函数中，用户只需处理有用到消息，不用的消息可以不理会，交由系统来处理（调用DefWindowProc），见代码清单
5‑8。窗口过程函数传入的4个形参含义，与发送消息函数的4个参数刚好是一一对应的。对于同步发送消息而言，SendMessage的返回值实际就是这个窗口过程函数处理该消息后的返回值。

代码清单 5‑8 窗口过程函数示例

1 static LRESULT WinProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)

2 {

3 RECT rc;

4 switch (msg) {

5 case WM_CREATE: { //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口.

6 GetClientRect(hwnd,&rc); //获得窗口的客户区矩形.

7 //创建一个按钮(示例).

8 CreateWindow(BUTTON,L"OK",WS_VISIBLE,rc.w-80,8,68,32,hwnd,ID_OK,NULL,NULL);

9 }

10 return TRUE;

11 ////

12 //省略部分代码//

13 ////

14

15 default: { //用户不关心的消息,由系统处理.

16 return DefWindowProc(hwnd,msg,wParam,lParam);

17 }

18

19 }

20

21 return WM_NULL;

22 }

标准消息类型及参数说明
~~~~~~~~~~~

WM_CREATE
^^^^^^^^^

WM_CREATE消息。当窗口被创建时，会收到WM_CREATE消息，用户可以在该消息里做一些初始化操作或创建子窗口。

代码清单 5‑9 示例程序1

1 void GUI_DEMO(void)

2 {

3 创建主窗口；

4 创建子控件1；

5 创建子控件2；

6 //省略一些内容

7 创建子控件10；

8

9 消息循环；

10 }

代码清单 5‑10 示例程序2

1 LRESULT win_proc(HWND hwnd,UINT msg,

2 WPARAM wParam,LPARAM lParam)

3 {

4 switch(msg)

5 {

6 case WM_CREATE:

7 创建子控件1；

8 创建子控件2；

9 //省略一些内容

10 创建子控件10；

11 return TRUE;

12 }

13 }

对比一下\ **错误!未找到引用源。**\ 和\ **错误!未找到引用源。**\ ，两种代码都可以实现同一个功能：创建控件。但是\ **错误!未找到引用源。**\
是在GUI_DEMO这个函数中定义控件。如果我们需要十几个控件的话，就会显得GUI_DEMO_Button函数的内容特别多，影响美观。因此将创建子窗口放在WM_CREATE消息中，使得代码条理清晰，内容明确。

WM_TIMER
^^^^^^^^

利用emXGUI的定时器，我们就可以做一些炫酷的时钟桌面，如图 5‑3。

|docx018|

图 5‑3 时钟样式

创建定时器API，见代码清单 5‑11。

代码清单 5‑11 创建定时器API（文件emXGUI.h）

1 HTMR SetTimer(HWND hwnd,UINT TMR_Id,U32 IntervalMS,U32 Flags,TIMERPROC Proc);

1) hwnd（输入）： 定时器所属窗口句柄，当定时器达到设定值时，该窗口会收到 WM_TIMER 消息。

2) TMR_Id（输入） ：定时器ID，用于区分多个定时标识。

3) IntervalMS（输入）：定时间隔时间，单位:毫秒。

4) Flags（输入）：标记，可以是以下组合：单次触发定时器（TMR_SINGLE），若没有指定单次触发定时器，则定时器为循环定时触发模式。TMR_START负责启动定时器。

5) Proc（输入）：定时器超时回调函数，可以为NULL。如果指定回调函数，窗口将不会收到WM_TIMER。

代码清单 5‑12 定时器示例（文件GUI_DEMO_Timer.c）

1 case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口

2 {

3 GetClientRect(hwnd,&rc); //获取窗口坐标

4 CreateWindow(BUTTON,L"OK",WS_VISIBLE,

5 rc.w-70,rc.h-40,68,32,hwnd,ID_OK,NULL,NULL);

6 SetTimer(hwnd,0,1000,TMR_START,NULL);

7 return TRUE;

8 }

9

10 case WM_TIMER:

11 {

12 time++;

13 InvalidateRect(hwnd ,NULL,TRUE); //发送WM_PAINT消息

14 break;

15 }

16

17 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

18 {

19 PAINTSTRUCT ps;

20 HDC hdc;

21 hdc =BeginPaint(hwnd,&ps);

22 x_wsprintf(wbuf, L"Time(s):%d", time);

23 TextOut(hdc,300,200,wbuf,-1); //显示时间

24 EndPaint(hwnd,&ps);

25 break;

26 }

27

28 case WM_CLOSE:

29 {

30 time = 0;

31 DestroyWindow(hwnd); //调用DestroyWindow函数来销毁窗口（该函数会产生WM_DESTROY消息）。

32 return TRUE; //关闭窗口返回TRUE。

33 }

代码清单 5‑12，WM_CREATE消息中创建一个1s定时器，设置为循环定时触发定时器，开启定时器。

当1s的延时到达时，窗口会接收到WM_TIMER消息。在WM_TIMER消息中，time自增，同时调用InvalidateRect函数发送WM_PAINT消息，使窗口重绘更新时间。

在WM_PAINT消息中，调用TextOut函数将时间变量的值显示在屏幕（300，200）处。调用该函数前，需要将显示的文字，使用x_wsprintf函数进行格式化。

当窗口退出时，窗口会收到WM_CLOSE消息。在WM_CLOSE消息中将记录时间的变量清零。调用DestroyWindow函数来销毁窗口。

实验结果如图 5‑4所示，屏幕显示当前的时间，为249s。

|docx019|

图 5‑4 实验结果

除了使用SetTimer创建定时器来实现延时，也可以使用RTT系统的延时函数GUI_msleep，函数定义见代码清单 5‑13。区别在于使用GUI_msleep时，该进程会放弃CPU的使用权，直到延时结束。延时的整个过程中，窗口不会接收到任何消息，也就是屏幕无法实时显示定时值。GUI_msleep就
好比是一个无法触发中断的定时器，没有相应的中断服务函数，而SetTimer的定时器，WM_TIMER就是它的中断服务函数。因此，我们在使用的时候，要注意到这一点，选择合适的延时函数。

代码清单 5‑13 GUI_msleep函数（文件X_GUI_RTT.c）

1 /\*

2 函数功能: 延时函数

3 参数: ms: 延时时间(单位:毫秒)

4 返回: 无

5 说明:

6 \*/

7 void GUI_msleep(u32 ms)

8 {

9 ms=rt_tick_from_millisecond(ms);

10 rt_thread_delay(ms);

11 }

WM_ERASEBKGND
^^^^^^^^^^^^^

窗口移动时，需要先擦除背景，再对窗口客户区的内容进行重绘，否则的话，就会出现窗口重影的现象。这里我们先讲解一下背景擦除，图 5‑5中，当窗口1从处移动到处的过程中，桌面背景依然会显示处的内容。因此，我们需要进行桌面背景擦除。这时候，窗口会收到该消息WM_ERASEBKGND。

|docx020|

图 5‑5 窗口移动

代码清单 5‑14 桌面背景清除示例程序

1 case WM_ERASEBKGND:

2 {

3 画矩形（0，0，LCD宽，LCD高）；//清除桌面

4 显示文字（“桌面”）；

5

6 }

7 return TRUE;

代码清单 5‑14，这里只是负责清除桌面背景，暂时没有涉及窗口重绘。所谓的桌面清除，其实就是画一个起点为（0，0），大小和桌面大小一样的矩形，再显示桌面的内容，这里显示的是桌面两个汉字。请读者注意，窗口的重绘不是在桌面背景清除消息中执行的。最终结果如图 5‑6。

|docx021|

图 5‑6 桌面背景清除

.. _创建桌面-1:

创建桌面
~~~~

桌面，父窗口都属于窗口，都可以使用WNDClass这个结构体来配置。该结构体成员用来设置窗口的风格、回调函数、光标样式等等，并调用GUI_CreateDesktop创建桌面，或者是CreateWindowEx来创建父窗口。WNDClass结构体定义在emXGUI.h文件中。

WNDClass窗口结构体详解
^^^^^^^^^^^^^^^

WNDClass结构体定义在emXGUI.h文件中，具体定义如下：

代码清单 5‑15 WNDClass结构体（文件emXGUI.h）

1 typedef struct tagWNDCLASS{

2 U32 Tag; //必须设置为 WNDCLASS_TAG值。

3 U32 Style; //窗口类风格。

4 WNDPROC lpfnWndProc; //窗口过程函数。

5 U32 cbClsExtra; //窗口类扩展数据大小。

6 U32 cbWndExtra; //窗口扩展数据大小。

7 HINSTANCE hInstance;

8 HICON hIcon; //图标

9 HCURSOR hCursor; //光标

10

11 } WNDCLASS;

1) Tag：窗口类型标签。创建桌面，窗口时，该成员变量的值必须设置为 WNDCLASS_TAG，该成员变量主要是用来区分窗口和子控件。

2) Style：窗口类风格。默认是CS_HREDRAW和CS_VREDRAW，当窗口发送改变时，会自动发送重绘消息WM_PAINT。CS_HREDRAW表示如果改变了客户区域的高度，则重绘整个窗口。CS_VREDRAW表示如果改变了客户区域的宽度，则重绘整个窗口。

3) lpfnWndProc：指向窗口过程函数的指针。窗口过程函数，用于处理发送到窗口的消息。

4) cbClsExtra：窗口类扩展数据大小，指定在窗口类结构之后分配的额外字节数，一般设置为0。

5) cbWndExtra：窗口扩展数据大小，指定窗口实例之后要分配的额外字节数，一般设置为0。

6) hInstance：应用程序实例句柄， 目前GUI版本为保留参数， 应设置为NULL。

7) hIcon：窗口图标，该成员指向图标资源的句柄，一般设置为NULL。

8) hCursor：桌面光标。该成员必须是游标资源的句柄，一般设置为NULL。

创建桌面函数详解
^^^^^^^^

代码清单 5‑16 创建桌面函数GUI_CreateDesktop

1 HWND GUI_CreateDesktop(U32 dwExStyle, const WNDClass \*wcex, LPCWSTR lpWindowName,

2 U32 dwStyle, int x, int y, int nWidth, int nHeight,

3 HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);

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
~~~~~~

设计要求
^^^^

用户可以设计自己的桌面背景，可以是图片桌面，也可以是纯颜色背景。青菜萝卜，各有喜爱。例程中采用RGB（32，72，144）的颜色作为背景颜色，在桌面（20，20）处显示字符串（emXGUI@Embedfire STM32F429），见图
5‑7。图片是采用Excel表格绘制的，下面我们一起学习，如何将图 5‑7变成我们的桌面。

|docx022|

图 5‑7 桌面效果

代码设计
^^^^

这里只讲解核心的部分代码，有些变量的设置，头文件的包含等并没有涉及到，完整的代码请参考本章配套的工程。

编程要点
''''

1) 配置WNDCLASS窗口结构体，调用GUI_CreateDesktop创建桌面窗口

2) 实现消息循环

3) 编写窗口回调函数，完成对消息的处理。

每一个界面都可以按照上述三个步骤，进行程序编写，这是基础的框架。区别在于第三步，这里可以自由发挥，脑洞有多大，界面就有多炫酷，这是正比例关系。

代码分析
''''

(1) 创建桌面代码分析

GUI_Startup函数初始化了GUI依赖的各种设备后，在末尾调用了示例函数GUI_DesktopStartup创建桌面。

c

(2) 桌面窗口回调代码分析

桌面窗口在创建的时候，会创建一个定时器用来检测触摸屏的输入，以及创建一个新的App线程。见代码清单 5‑17。

代码清单 5‑17 窗口回调函数desktop_proc（gui_desktop.c文件）

1 /*\*

2 \* @brief 桌面回调函数

3 \* @param hwnd 当前处理该消息的窗口对象句柄

4 \* @param msg 消息类型值，用以标识和区分当前产生的消息

5 \* @param wParam 消息参数值，根据msg消息代码值不同

6 \* @param lParam 消息参数值，根据msg消息代码值不同

7 \* @retval 返回给SendMessage的值

8 \*/

9 static LRESULT desktop_proc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)

10 {

11 switch(msg)

12 {

13 /\* 桌面创建时,会产生该消息,可以在这里做一些初始化工作.
\*/

14 case WM_CREATE:

15 ////创建1个20ms定时器，处理循环事件.

16 SetTimer(hwnd,1,20,TMR_START,NULL);

17 //创建App线程

18 if(1)

19 {

20 rt_thread_t h;

21 h=rt_thread_create("GUI_APP",gui_app_thread,NULL,2048,5,5);

22 rt_thread_startup(h);

23 }

24

25 break;

26 /\* 定时处理输入设备的信息 \*/

27 case WM_TIMER:

28 #if(GUI_INPUT_DEV_EN)

29 {

30 u16 id;

31

32 id =LOWORD(wParam);

33 if(id==1)

34 {

35 GUI_InputHandler(); //处理输入设备

36 }

37 }

38 #endif

39 break;

40 /\* 客户区背景需要被擦除 \*/

41 case WM_ERASEBKGND:

42 {

43 HDC hdc =(HDC)wParam;

44 \_EraseBackgnd(hdc,NULL,hwnd);

45 }

46 return TRUE;

47 /\* 用户不关心的信息，由系统处理 \*/

48 default:

49 return DefDesktopProc(hwnd,msg,wParam,lParam);

50 }

51 return WM_NULL;

52 }

1) WM_CREATE消息

当执行完GUI_CreateDesktop之后，会执行WM_CREATE这个case的内容：调用SetTimer函数创建一个20ms的定时器，调用rt_thread_create创建App线程，见代码清单 5‑18。

代码清单 5‑18 创建App线程rt_thread_create函数（gui_desktop.c文件）

1 static void gui_app_thread(void \*p)

2 {

3 #if(GUI_TOUCHSCREEN_EN & GUI_TOUCHSCREEN_CALIBRATE)

4 {

5 int i=0;

6 while (TouchPanel_IsPenDown())

7 {

8 GUI_msleep(100);

9 if (i++>10) {

10 ShowCursor(FALSE);

11 TouchScreenCalibrate(NULL);

12 ShowCursor(TRUE);

13 break;

14 }

15 }

16 }

17 #endif

18

19 /\* 调用APP函数 \*/

20 GUI_AppMain();

21 // GUI_UserAppStart();

22 // ShellWindowStartup();

23 // return 0;

24 }

#if(GUI_TOUCHSCREEN_EN & GUI_TOUCHSCREEN_CALIBRATE)是条件编译，由于我们使用的是电容屏，不需要校准，因此GUI_TOUCHSCREEN_CALIBRATE为0。GUI_TOUCHSCREEN_EN为是否使能触摸屏，这里为1。所以#if的内容不执行。紧
接着调用GUI_AppMain函数，我们自己定义的界面是放在此处执行的。

2) WM_TIMER消息

当定时器计数达到设定值时，执行检测触摸屏的输入。见代码清单 5‑19

代码清单 5‑19桌面的过程函数之case： WM_TIMER（文件gui_desktop.c）

1 /\* 定时处理输入设备的信息 \*/

2 case WM_TIMER:

3 #if(GUI_INPUT_DEV_EN)

4 {

5 u16 id;

6 id =LOWORD(wParam);

7 if (id==1) {

8 GUI_InputHandler(); //处理输入设备

9 }

10 }

11 #endif

12 break;

#if(GUI_INPUT_DEV_EN)是条件编译，GUI_INPUT_DEV_EN为是否使用输入设备，这里设置为1。函数LOWORD是取数据的低16位。WM_TIMER消息中，带有wParam参数。这里将wParam参数，也就是定时器的
ID值赋给id变量。WM_CREATE消息中我们创建的定时器的ID是1，如果读取的ID是1，则执行GUI_InputHandler处理输入设备（这里我们只用到了触摸屏）。

代码清单 5‑20 触摸处理函数（文件gui_touch_port.c）

1 /*\*

2 \* @brief 需要被定时调用的触摸处理函数

3 \* @note 本例子中通过gui_input_port.c文件的GUI_InputHandler被定时调用

4 \* @param 无

5 \* @retval 无

6 \*/

7 void GUI_TouchHandler(void)

8 {

9 int act;

10 POINT pt;

11

12 /\* 判断触摸状态及坐标 \*/

13 act =TouchDev_GetPoint(&pt);

14 if (act==TS_ACT_DOWN) {

15 /\* 触摸按下，使用触摸坐标作为输入 \*/

16 MouseInput(pt.x,pt.y,MK_LBUTTON);

17 }

18

19 if (act==TS_ACT_UP) {

20 /\* 触摸释放，使用当前光标作为输入*/

21 GetCursorPos(&pt);

22 MouseInput(pt.x,pt.y,0);

23 }

24 }

代码清单 5‑20 触摸处理函数（文件gui_touch_port.中，调用GUI_TouchHandler来获取触摸状态以及触摸坐标，保存在pt结构体中。

3) WM_ERASEBKGND消息

代码清单 5‑21桌面的过程函数之case：WM_ERASEBKGND（文件gui_desktop.c）

1 /\* 客户区背景需要被擦除 \*/

2 case WM_ERASEBKGND:

3 {

4 HDC hdc =(HDC)wParam;

5 \_EraseBackgnd(hdc,NULL,hwnd);

6 }

7 return TRUE;

当桌面创建完成后，会发送该消息，来绘制桌面。接收该消息时，会收到wParam参数，见代码清单 5‑21。调用_EraseBackgnd来绘制桌面。见代码清单 5‑22桌面背景绘制函数（文件gui_desktop.。

代码清单 5‑22桌面背景绘制函数（文件gui_desktop.c）

1 /*\*

2 \* @brief 桌面背景绘制函数，触发背景绘制时会调用本函数，

3 通过修改本函数的内容可更改桌面的背景

4 \* @param hdc 绘图上下文

5 \* @param lprc 要绘制的矩形区域，为NULL时会自动绘制hwnd的客户区

6 \* @param hwnd 窗口对象句柄

7 \* @retval 无

8 \*/

9 static void \_EraseBackgnd(HDC hdc,const RECT \*lprc,HWND hwnd)

10 {

11 RECT rc;

12

13 if (lprc==NULL) {

14 GetClientRect(hwnd,&rc);

15 } else {

16 CopyRect(&rc,lprc);

17 }

18 SetBrushColor(hdc,MapRGB(hdc,32,72,144));

19 FillRect(hdc,&rc);

20 SetTextColor(hdc,MapRGB(hdc,250,250,250));

21 // /\* 居中显示结果 \*/

22 // DrawText(hdc,L"Hello emXGUI@Embedfire!",-1,&rc,DT_SINGLELINE|DT_VCENTER|DT_CENTER);

23

24 TextOut(hdc,20,20,L"emXGUI@Embedfire STM32F429 ",-1);

25 }

调用GetClientRect函数来获取客户区的坐标，由于程序传进来的形参为NULL，所以绘制的区域为整个客户区。调用FillRect函数，设置桌面背景颜色为RGB(32,72,144)，调用TextOut在（20，20）处显示字符串：emXGUI@Embedfire
STM32F429，字体颜色为RGB(250,250,250)。字体显示函数有两个：DrawText和TextOut。DrawText可以设置字体显示的格式，是左对齐，右对齐或者居中。而TextOut不行。相关的函数说明，请参考《emXGUI API编程手册》的绘图API章节。

4) default消息

这个消息是指一些我们并不关心的系统消息，我们就可以调用DefWindowProc这个函数来完成。见代码清单 5‑23。

代码清单 5‑23 default消息响应

1default:

2 return DefWindowProc(hwnd,msg,wParam,lParam);

到这里为止，桌面回调函数已经讲完了。

实验现象
^^^^

利用我们的桌面截图DEMO，可以对我们的屏幕进行截图，如图 5‑8，这就是一系列操作后得到的桌面。是不是和图 5‑7的样子一模一样

|docx023|

图 5‑8 桌面显示效果

按钮控件
----

emXGUI提供了三种按钮：按钮，复选框，单选按钮。

图 6‑1的处是emXGUI的按钮控件，可以被单击，按下；处是复选框，可以同时选中多个功能；处是单选框，只可以选择单个选项。处和处区别在于：处，串口的停止位只可以是1位、1.5位和2位中的某一个；处，串口助手可以同时使能自动发送，自动清空和以十六进制发送。本章，我们先学习使用按钮控件。

|docx024|

图 6‑1 各种按钮

按钮控件，主要用于用户和应用程序之间的交互，按钮会对每一个动作做出相应的回应。例如，单击按钮时，该按钮会改变其外观和状态，同时向父窗口发送消息，通知父窗口，我被按下了，假如该按钮的功能是关闭窗口，则父窗口会被关闭。图 6‑2和图 6‑3。正所谓，众口难调。emXGUI除了提供系统自带的标准控件
，用户还可以自定义控件的外观以及行为。图 6‑4，是一个自定义控件。当该按钮被按下后，按钮的显示内容发生了改变。除此之外，用户也可以选择改变背景等等。只有一句话：只有你想不到的，没有emXGUI做不到的。

|docx025|

图 6‑2 按钮未被按下

|docx026|

图 6‑3 按钮被按下

|docx027|

图 6‑4 自定义控件

创建按钮控件
~~~~~~

.. _标准消息类型及参数说明-1:

标准消息类型及参数说明
^^^^^^^^^^^

部分消息在第五章已经详细介绍过了，这里就简单说明一下，不懂的地方，可以查阅第五章的标准消息类型及参数说明。

(1) WM_CREATE消息。

当窗口被创建时，会收到WM_CREATE消息，用户可以在该消息里做一些初始化操作或创建子窗口。

(2) default消息。

一些我们并不关心的系统消息，调用DefWindowProc函数进行处理。

(3) WM_PAINT消息。

|docx028|

图 6‑5 桌面重绘

如图 6‑5所示，当我们将窗口1从处移动到处时，此时处的客户区内容实际上只会显示我们的桌面背景，因此我们需要把处的客户区内容“移动”到处的客户区进行显示，这个过程叫做重绘。创建窗口的时候，新建的窗口如图
6‑5的窗口，也需要进行重绘。当窗口客户区需要重绘制时，会产生WM_PAINT消息。在该消息里，用户应调用BeginPaint来开始绘制，BeginPaint会返回一个DC，用于绘图操作，所有绘图完成后，需调用EndPaint来结束绘制。

BeginPaint有两个形参，一个是重绘窗口的句柄，另一个是PAINTSTRUCT类型的结构体，见代码清单 6‑1 PAINTSTRUCT结构体（文件emXGUI.。下面简单介绍一下该结构体的成员的作用。更多详细内容，请参考《emXGUI API编程手册》窗口/消息系统API。

代码清单 6‑1 PAINTSTRUCT结构体（文件emXGUI.h）

1 typedef struct tagPAINTSTRUCT {

2 HDC hdc; //绘图上下文

3 RECT rcPaint; //需要重绘的矩形区域

4 BOOL fErase; //背景是否必须被清除

5 } PAINTSTRUCT;

1. hdc：绘图上下文，用于保存绘图参数。

2. rcPaint：RECT结构体变量，保存要求重绘的矩形区域。

3. fErase：背景是否必须被清除。fErase为非零值则在 WM_PAINT 里来擦除背景，否则不擦除背景。如果用户在消息WM_ERASEBKGND 里直接返回FALSE，这个fErase值就会是TRUE。注意，在WM_PAINT
   里绘制背景，用户要在窗口过程函数里添加WM_ERASEBKGND消息，并直接返回TRUE，使系统不要再执行默认的背景绘制。

每当窗口1收到WM_PAINT这个消息时，会执行代码清单 6‑2的内容，重绘后结果如图 6‑6所示，这样就实现了窗口的移动。

代码清单 6‑2桌面重绘示例

1 LRESULT win_proc(HWND hwnd,UINT msg,

2 WPARAM wParam,LPARAM lParam)

3 {

4 switch(msg)

5 {

6 case WM_PAINT:

7 BeginPaint();

8 显示文字(“我是内容”);

9 EndPaint();

10 break;

11 }

12 }

|docx020|

图 6‑6 重绘后界面

这里有的人或许会有这样的疑问：为什么我已经移动了窗口，假设水平移动x个像素，但是WM_PAINT中文字的显示位置不用偏移x个像素呢？这是因为这个文字显示的位置是在客户区的某个位置。这个坐标是以客户区原点来定义的。\ |docx029|

图 6‑7 坐标说明

**错误!未找到引用源。**\ 做了一个简单的水平移动，只是为了方便说明。其实原理都是一样的。（8，4）这个坐标是相对于客户区的原点（0，0），即使我们移动窗口1，但是客户区的原点依然没有改变。因此，重绘的时候，我们只需要实现窗口客户区显示的东西，至于客户区和非客户区之间坐标变换，我们可以不用考虑。

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
^^^^^^^^

创建按钮控件，也是调用CreateWindow函数来创建。函数声明，见代码清单 6‑3创建按钮控件（文件emXGUI.。

代码清单 6‑3创建按钮控件（文件emXGUI.h）

1 #define CreateWindow(lpClass,lpWindowName,dwStyle,

2 x,y,nWidth,nHeight,

3 hwndParent,WinId,hInstance,lpParam)\\

4 CreateWindowEx(0,lpClass,lpWindowName,dwStyle,

5 x,y,nWidth,nHeight,hwndParent,WinId,hInstance,lpParam)

6

7 //创建窗口函数

8 HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,

9 U32 dwStyle, int x, int y, int nWidth, int nHeight,

10 HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);

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
~~~~~~~~

.. _设计要求-1:

设计要求
^^^^

图 6‑8是本章节的设计目标，旨在介绍按钮控件的创建及使用方法。只有掌握基础使用方法后，才可以设计出高大上的效果。本章节的例程中，在客户区创建八个按钮控件，每个控件的功能，风格不完全相同，该图是使用excel表格绘制而成的，一些按钮控件的风格可能无法体现出来。读者可以通过本章节了解按钮控件的基础用法
，单击按钮控件的响应操作以及自绘制按钮控件。

|docx030|

图 6‑8 窗口客户区设计效果

.. _代码设计-1:

代码设计
^^^^

.. _编程要点-1:

编程要点
''''

1) 配置WNDCLASS窗口结构体，调用CreateWindowEx创建父窗口；

2) 实现消息循环

3) 编写窗口回调函数，完成对消息的处理。

这是基础的三个步骤。与第五章的区别在于，在第三个步骤中，新增加了一些消息处理case，来处理按钮控件的动作响应。

.. _代码分析-1:

代码分析
''''

代码清单 6‑4 App线程GUI_AppMain（GUI_AppMain.c文件）

1 void GUI_AppMain(void)

2 {

3 while(1)

4 {

5 GUI_DEMO_Button();

6 }

7 }

桌面窗口创建完成后，WM_CREATE消息创建的App线程GUI_AppMain会开始启动，我们自己编写的界面都是放在该线程下执行的。见代码清单 6‑4。

(1) 创建父窗口代码

在创建按钮控件之前，需要先创建一个父窗口。任何一个控件，都是在其父窗口显示的。你见过哪个应用程序打开之后，什么东西都没有，只有一个按钮的吗？

代码清单 6‑5 GUI_DEMO_Button函数（GUI_DEMO_Button.c文件）

1 void GUI_DEMO_Button(void)

2 {

3 HWND hwnd;

4 WNDCLASS wcex;

5 MSG msg;

6

7 //第1部分：配置wcex参数。

8 wcex.Tag = WNDCLASS_TAG;

9 wcex.Style = CS_HREDRAW \| CS_VREDRAW;

10 wcex.lpfnWndProc = win_proc; //设置主窗口消息处理的回调函数.

11 wcex.cbClsExtra = 0;

12 wcex.cbWndExtra = 0;

13 wcex.hInstance = NULL;//hInst;

14 wcex.hIcon = NULL;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);

15 wcex.hCursor = NULL;//LoadCursor(NULL, IDC_ARROW);

16 //第2部分：创建主窗口

17 hwnd =CreateWindowEx( NULL,

18 &wcex,

19 \_T("GUI Demo - Button"),

20 WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,

21 0,0,GUI_XSIZE,GUI_YSIZE,

22 NULL,NULL,NULL,NULL);

23

24 //第3部分：显示主窗口

25 ShowWindow(hwnd,SW_SHOW);

26 //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。

27 while(GetMessage(&msg,hwnd))

28 {

29 TranslateMessage(&msg);

30 DispatchMessage(&msg);

31 }

32 }

代码清单 6‑5的第1部分主要配置了wcex结构体来设置窗口的风格为CS_HREDRAW \| CS_VREDRAW（宽高发生改变时，发送重绘消息），设置win_proc作为主窗口消息处理的回调函数。

第2部分调用CreateWindowEx函数在（0，0）创建一个800*480，带有大，小边框的窗口，标题为GUI Demo - Button，创建后可见且当桌面重绘时，对子窗口进行重绘。GUI_CreateDesktop创建成功后，会返回桌面窗口的句柄。

第3部分代码是调用ShowWindow函数来显示窗口。

第4部分代码是开始窗口消息循环，负责接收和发送消息。在发送消息之前，需要调用TranslateMessage函数，将按键的消息转换为emXGUI的消息类型。窗口关闭并销毁时，GetMessage将返回FALSE，退出本消息循环。

到此为止，我们就完成了我们编程要点的前两点。

(2) 窗口回调函数

1) WM_CREATE

代码清单 6‑6 WM_CREATE消息响应（文件GUI_DEMO_Button.c）

1 case WM_CREATE:

2

3 GetClientRect(hwnd,&rc); //获得窗口的客户区矩形

4

5 CreateWindow(BUTTON,L"EXIT",WS_VISIBLE,rc.w-100,8,80,48,hwnd,ID_EXIT,NULL,NULL);

6

7 //设置矩形参数，用于创建按钮

8 rc.x =20;

9 rc.y =50;

10 rc.w =100;

11 rc.h =40;

12 CreateWindow(BUTTON,L"Button1",WS_VISIBLE,

13 rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN1,NULL,NULL);

14

15 OffsetRect(&rc,0,rc.h+10); //往下移动矩形位置(X轴不变,Y轴位置增加rc.h+10个像素)

16 //创建立体风格的按钮(BS_3D)

17 CreateWindow(BUTTON,L"Button2",BS_3D|WS_VISIBLE,

18 rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN2,NULL,NULL);

19

20 OffsetRect(&rc,0,rc.h+10);

21 //创建平面风格的按钮(BS_FLAT)

22 CreateWindow(BUTTON,L"Button3",BS_FLAT|WS_VISIBLE,

23 rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN3,NULL,NULL);

24

25 OffsetRect(&rc,0,rc.h+10);

26 //创建圆角风格的按钮 (BS_ROUND )

27 CreateWindow(BUTTON,L"Button4",BS_ROUND|WS_VISIBLE,

28 rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN4,NULL,NULL);

29 rc.x =150;

30 rc.y =30;

31 rc.w =120;

32 rc.h =60;

33 //创建圆角风格的按钮(BS_ROUND+BS_NOTIFY)

34 CreateWindow(BUTTON,L"Button5",BS_ROUND|BS_NOTIFY|WS_VISIBLE,

35 rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN5,NULL,NULL);

36

37 OffsetRect(&rc,0,rc.h+10);

38 //创建自绘制按钮(WS_OWNERDRAW)

39 CreateWindow(BUTTON,L"Button6\r\nOwnerDraw",WS_OWNERDRAW|WS_VISIBLE,

40 rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN6,NULL,NULL);

41

42 OffsetRect(&rc,0,rc.h+10);

43 //创建圆角风格的按钮(BS_ROUND+WS_DISABLE)

44 CreateWindow(BUTTON,L"Button7",BS_ROUND|WS_DISABLED|WS_VISIBLE,

45 rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN7,NULL,NULL);

46 return TRUE;

前面我们提到过，WM_CREATE消息主要是负责创建控件的。代码清单 6‑6 WM_CREATE消息响应（文件GUI_DEMO_Button.中我们创建了六个不同风格的按钮。调用OffsetRect来移动显示的位置，间隔为每个控件的高度下10个像素值， 代码清单 6‑6\
**错误!未找到引用源。**\ ，请参考《emXGUI API编程手册》的章节：位置及区域操作运算API。用户也可以选择自己输入坐标，一样能够达到效果。

由于按钮也是窗口，所以也可以使用窗口的属性值。这些属性值都是定义在emXGUI.h文件中，见代码清单
6‑7。不同的属性值可以随意组合。每个控件都有各自的ID号，ID号的值可以随意给定。ID号主要是为了方便管理。比如，我们单击了某个按钮，就会发生WM_NOTIFY的消息，这个消息的wParam低16位就是控件的ID号。利用这个我们就可以来检测到底是什么按钮被单击。是不是很方便呢。

代码清单 6‑7 按钮属性值（文件emXGUI.h）

1 /\*

2 \* Button Control Styles

3 \*/

4 #define BS_FLAT (1<<0) //平面风格

5 #define BS_3D (2<<0) //立体风格

6 #define BS_ROUND (3<<0) //圆角风格

7 #define BS_NOTIFY (1<<15) //是否发送PUSHED消息

8

9 //窗口公共风格(高16位)

10 /\*

11 \* Window Styles

12 \*/

13 #define WS_DISABLED 0x08000000UL //窗口创建后,不会响应输入设备的事件(键盘与鼠标).

14

15 #define WS_CLIPCHILDREN 0x02000000UL //父对象重绘时，是否对子窗口重绘

16 #define WS_VISIBLE 0x01000000UL //窗口创建后,默认是可见的.

17 #define WS_BORDER 0x00800000UL //窗口会带有小边框.

18 #define WS_DLGFRAME 0x00400000UL //窗口会带有大边框.

19 #define WS_CAPTION 0x00080000UL //窗口会带有标题栏.

20 #define WS_OWNERDRAW 0x00020000UL //用户自定义样式

代码清单 6‑6 WM_CREATE消息响应（文件GUI_DEMO_Button.中每个按钮都有多个属性和各自的ID值，见表格 6‑1。

表格 6‑1 按钮的属性和ID值

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

表格 6‑1中的ID值，其实是宏定义，用户可以自己修改。见代码清单 6‑8 控件ID（文件GUI_DEMO_Button.。

代码清单 6‑8 控件ID（文件GUI_DEMO_Button.c）

1 //定义控件ID

2 #define ID_EXIT 0x1000

3 #define ID_BTN1 0x1101

4 #define ID_BTN2 0x1102

5 #define ID_BTN3 0x1103

6 #define ID_BTN4 0x1104

7 #define ID_BTN5 0x1105

8 #define ID_BTN6 0x1106

9 #define ID_BTN7 0x1107

2) Default

用户不关心的消息可以通过调用DefWindowProc函数来处理。见代码清单 6‑9。

代码清单 6‑9 用户不关心的消息处理（文件GUI_DEMO_Button.c）

1 default:

2 return DefWindowProc(hwnd,msg,wParam,lParam);

3) WM_PAINT

代码清单 6‑10 WM_PAINT消息响应（文件GUI_DEMO_Button.c）

1case WM_PAINT: //窗口需要重绘制时，会自动收到该消息.

2 {

3 PAINTSTRUCT ps;

4 hdc =BeginPaint(hwnd,&ps);

5 SetTextColor(hdc,MapRGB(hdc,0,0,255));

6 TextOut(hdc,8,4,L"Button Test:",-1);

7 EndPaint(hwnd,&ps);

8 return TRUE;

9 }

代码清单 6‑10中，使用SetTextColor设置字体颜色为RGB(0，0，255)。调用TextOut函数在客户区（8，4）显示字符串： “Button Test:”。 SetTextColor和TextOut函数说明，请参考《emXGUI
API编程手册》的章节：绘图API。注意，重绘时需要调用BeginPaint函数获取绘图上下文。绘制完成后 ，调用EndPaint函数结束绘制。

4) WM_DRAWITEM

Button6是用户自定义风格按钮，所以在绘制时，会给父窗口发送WM_DRAWITEM消息，来进行绘制，用户可以自己设计。例程中，只是改变按钮在按下时，按钮的字体颜色和背景颜色。在不同的状态值下，上述的三者的颜色有所不同。见表格
6‑2。按钮处于弹起状态时，字体是黑色，背景是深绿色，边框是浅绿。如果按钮被按下的话，字体会变红色，背景为淡蓝色，边框为红色。

表格 6‑2 不同的状态值的颜色值

============ =============== =============
\            按下            弹起
============ =============== =============
画刷（背景） （150,200,250） （30,150,30）
画笔（边框） （250,0,0）     （0,250,0）
文字         （250,0,0）     （0,50,100）
============ =============== =============

具体的代码实现，见代码清单 6‑11和 代码清单 6‑12。

代码清单 6‑11 WM_DRAWITEM消息响应（文件GUI_DEMO_Button.c）

1 case WM_DRAWITEM:

2 {

3 /*　当控件指定了WS_OWNERDRAW风格，则每次在绘制前都会给父窗口发送WM_DRAWITEM消息。

4 \* wParam参数指明了发送该消息的控件ID;lParam参数指向一个DRAWITEM_HDR的结构体指针，

5 \* 该指针成员包含了一些控件绘制相关的参数.

6 \*/

7

8 DRAWITEM_HDR \*ds;

9

10 ds =(DRAWITEM_HDR*)lParam;

11

12 if(ds->ID >= ID_BTN1 && ds->ID<= ID_BTN6)

13 {

14 button_owner_draw(ds); //执行自绘制按钮

15 }

16 return TRUE;

17 }

代码清单 6‑12 绘制按钮外观函数（文件GUI_DEMO_Button.c）

1 static void button_owner_draw(DRAWITEM_HDR \*ds) //绘制一个按钮外观

2 {

3 // HWND hwnd;

4 HDC hdc;

5 RECT rc;

6 WCHAR wbuf[128];

7

8 // hwnd =ds->hwnd; //button的窗口句柄.

9 hdc =ds->hDC; //button的绘图上下文句柄.

10 rc =ds->rc; //button的绘制矩形区.

11

12 if(ds->State & BST_PUSHED)

13 { //按钮是按下状态

14

15 SetBrushColor(hdc,MapRGB(hdc,150,200,250)); //设置填充色(BrushColor)

16 SetPenColor(hdc,MapRGB(hdc,250,0,0)); //设置绘制色(PenColor)

17 SetTextColor(hdc,MapRGB(hdc,250,0,0)); //设置文字色

18 }

19 else

20 { //按钮是弹起状态

21 SetBrushColor(hdc,MapRGB(hdc,30,150,30));

22 SetPenColor(hdc,MapRGB(hdc,0,250,0));

23 SetTextColor(hdc,MapRGB(hdc,0,50,100));

24 }

25

26 FillRect(hdc,&rc); //用矩形填充背景

27 DrawRect(hdc,&rc); //画矩形外框

28 GetWindowText(ds->hwnd,wbuf,128); //获得按钮控件的文字

29 DrawText(hdc,wbuf,-1,&rc,DT_VCENTER|DT_CENTER);//绘制文字(居中对齐方式)

30 }

代码清单 6‑11利用DRAWITEM_HDR结构体成员的ID值来执行自绘制按钮。由于只有Button6拥有WS_OWNERDRAW属性，所以只有ID值为ID_BTN6的Button6会执行自绘制，调用绘制外观函数button_owner_draw，见代码清单
6‑12。根据按钮的状态值（ds->state），设置不同的画刷、画笔、文字的颜色。调用FillRect函数填充矩形的背景，使用DrawRect函数来画矩形外框，调用GetWindowText可以获取控件的文字，使用DrawText来绘制文字，使其居中对齐。具体的函数说明，请参考《emXGUI
API编程手册》的章节：绘图API。

5) WM_NOTIFY

WM_NOTIFY 消息的wParam低16位为发送该消息的控件ID，高16位为通知码。LOWORD和HIWORD用来读取消息参数的低16位和高16位。ID_BTN1~ ID_BTN6每一个按钮的动作响应都是在这里定义的。用户可以自己修改这里的代码。

代码清单 6‑13 WM_NOTIFY消息响应（文件GUI_DEMO_Button.c）

1 case WM_NOTIFY: //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,高16位为通知码;

2 lParam指向了一个NMHDR结构体.

3 {

4 u16 code,id;

5 // NMHDR \*nr=(NMHDR*)lParam;

6

7 id =LOWORD(wParam);

8 code=HIWORD(wParam);

9

10 if(id >= ID_BTN1 && id<= ID_BTN6)

11 {

12 if(code == BN_PUSHED)

13 { //按钮被按下了.

14 GUI_Printf("Button PUSHED: ID:%04XH\r\n",id);

15 }

16

17 if(code == BN_CLICKED)

18 { //按钮弹起了.

19 GUI_Printf("Button UNPUSHED: ID:%04XH\r\n",id);

20 }

21 }

22

23 if(id== ID_EXIT && code==BN_CLICKED)

24 { // EXIT按钮弹起

25 PostCloseMessage(hwnd); //产生WM_CLOSE消息关闭主窗口

26 }

27 }

28 break;

代码清单 6‑13只是简单检测按钮的动作，同时打印到串口。注意，只有当按钮的属性有BS_NOTIFY时，才会检测到BN_PUSHED状态值。ID_EXIT单击时，会调用PostCloseMessage发送窗口关闭消息WM_CLOSE，来关闭主窗口。

6) WM_CTLCOLOR

WM_NOTIFY 消息的wParam参数指明了发送该消息的控件ID；lParam参数指向一个CTLCOLOR的结构体指针。可以使用LOWORD来读取wParam的低16位，获取ID。

代码清单 6‑14 WM_CTLCOLOR消息响应（文件GUI_DEMO_Button.c）

1 case WM_CTLCOLOR:

2 {

3 /\* 控件在绘制前，会发送 WM_CTLCOLOR到父窗口.

4 \* wParam参数指明了发送该消息的控件ID;lParam参数指向一个CTLCOLOR的结构体指针.

5 \* 用户可以通过这个结构体改变控件的颜色值.

6 用户修改颜色参数后，需返回TRUE，否则，系统

7 \* 将忽略本次操作，继续使用默认的颜色进行绘制.

8 \*

9 \*/

10 u16 id;

11 id =LOWORD(wParam);

12 if(id== ID_BTN5) //只改变BTN5的颜色.

13 {

14 CTLCOLOR \*cr;

15 cr =(CTLCOLOR*)lParam;

16 if(SendMessage(GetDlgItem(hwnd,id),BM_GETSTATE,0,0)&BST_PUSHED)

17 {

18 cr->TextColor =RGB888(50,220,50); //文字颜色（RGB32颜色格式)

19 cr->BackColor =RGB888(20,100,20); //背景颜色（RGB32颜色格式)

20 cr->BorderColor =RGB888(30,30,30); //边框颜色（RGB32颜色格式)

21 }

22 else

23 {

24 cr->TextColor =RGB888(250,250,250);

25 cr->BackColor =RGB888(200,0,0);

26 cr->BorderColor =RGB888(50,50,50);

27 }

28 return TRUE;

29 }

30 else

31 {

32 //其它按钮使用系统默认的颜色进行绘制，所以直接返回FALSE.

33 return FALSE;

34 }

35

36 }

代码清单 6‑14只改变Button5的文字、背景和边框的颜色。函数GetDlgItem可以得到某个控件的句柄值，发送消息
BM_GETSTATE来获取Button的状态值。如果按下按钮，则文字为浅绿色，背景为深绿色，边框为黑色。反之，则文字为白色，背景为红色，边框为灰色。当用户自己定义的文字、背景和边框的颜色后，需要返回TRUE，否则将按照系统默认的进行配置。

.. _实验现象-1:

实验现象
^^^^

利用我们的桌面截图DEMO，可以对我们的屏幕进行截图，如图 6‑9。可以看出，Button1~ Button4、
Button7的按钮风格有明显的变化，Button5和Button6，在单击时，控件的文字、背景和边框的颜色均发生改变，不过Button5是用户自定义按钮控件，Button6是系统提供的标准控件。

|docx031|

图 6‑9 窗口显示效果

复选框控件
-----

前面我们已经讲过按钮控件，下面我们开始学习图 7‑1处的复选框控件。

|docx024|

图 7‑1 各种按钮

复选框是一种可同时选中多项的基础控件。假设我们现在做一个电子调查问卷，了解大家的爱好，有些人的爱好很广泛，如唱歌，骑车，旅游，美食等等，我们就可以使用复选框来完成。

创建复选框控件
~~~~~~~

.. _标准消息类型及参数说明-2:

标准消息类型及参数说明
^^^^^^^^^^^

复选框也是按钮控件的一种，使用的消息和处理方式也都大同小异。有什么不懂的地方，可以参考上一章的标准消息类型及参数说明。

创建复选框控件函数
^^^^^^^^^

复选框属于子控件（子窗口），可以通过调用CreateWindow函数来创建。实际上，无论什么控件，都是调用CreateWindow函数来创建的，下面重点讲解一下差异之处。

代码清单 7‑1 创建窗口函数（文件emXGUI.h）

1 HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,

2 U32 dwStyle, int x, int y, int nWidth, int nHeight,

3 HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);

1) lpClass：复选框属于按钮控件中的一类，这里应该选择BUTTON类。

2) lpWindowName：复选框项目的名称，可以是中文。注意，这里也是使用的宽字符串，一个字符占两个字节。

3) dwStyle：复选框的风格。参数BS_CHECKBOX代表该控件为复选框。当使用复选框这个控件时，这个参数是必须的，否则就和普通按钮一样了。还可以使用按钮控件的风格（BS_NOTIFY），只有控件拥有该属性，才可以接收到控件被按下（未松手）的消息。以及窗口风格。

..

   至于其他的参数，和创建按钮一样，也是同样的用法，这里不作描述。

创建复选框控件实验
~~~~~~~~~

.. _设计要求-2:

设计要求
^^^^

图 7‑2是excel设计的复选框界面的内容，比较简单，容易理解。下面通过代码讲解如何实现这个界面。

|docx032|

图 7‑2 复选框界面

.. _代码设计-2:

代码设计
^^^^

.. _编程要点-2:

编程要点
''''

1) 配置WNDCLASS窗口结构体，调用CreateWindowEx创建父窗口；

2) 实现消息循环

3) 编写窗口回调函数，完成对消息的处理。

.. _代码分析-2:

代码分析
''''

(1) 创建父窗口代码分析

代码清单 7‑2 创建父窗口（文件GUI_DEMO_Checkbox.c）

1 void GUI_DEMO_Checkbox(void)

2 {

3 HWND hwnd;

4 WNDCLASS wcex;

5 MSG msg;

6

7 wcex.Tag = WNDCLASS_TAG;

8 wcex.Style = CS_HREDRAW \| CS_VREDRAW;

9 wcex.lpfnWndProc = win_proc;

10 wcex.cbClsExtra = 0;

11 wcex.cbWndExtra = 0;

12 wcex.hInstance = 0;//hInst;

13 wcex.hIcon = 0;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);

14 wcex.hCursor = 0;//LoadCursor(NULL, IDC_ARROW);

15

16 hwnd =CreateWindowEx( NULL,

17 &wcex,

18 \_T("GUI Demo - Checkbox"),

19 WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,

20 0,0,GUI_XSIZE,GUI_YSIZE,

21 NULL,NULL,NULL,NULL);

22

23 ShowWindow(hwnd,SW_SHOW);

24 while(GetMessage(&msg,hwnd))

25 {

26 TranslateMessage(&msg);

27 DispatchMessage(&msg);

28 }

29 }

每一个控件都是在父窗口上显示，调用CreateWindowEx创建父窗口，设置win_proc作为窗口回调函数，详细解释可以参考，按钮控件章节的代码分析。

(2) 窗口回调函数

代码清单 7‑3 窗口回调函数win_proc（文件GUI_DEMO_Checkbox.c）

1 static LRESULT win_proc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)

2 {

3 // HDC hdc;

4 // PAINTSTRUCT ps;

5 RECT rc;

6 // WCHAR wbuf[128];

7 //int i,x,y;

8 // HWND wnd;

9

10 switch(msg)

11 {

12 case WM_CREATE:

13 GetClientRect(hwnd,&rc);

14 //创建按钮(EXIT)

15 CreateWindow(BUTTON,L"EXIT",WS_VISIBLE,

16 rc.w-100,8,80,48,hwnd,ID_EXIT,NULL,NULL);

17 rc.x =20;

18 rc.y =40;

19 rc.w =128;

20 rc.h =30;

21 //创建复选框Checkbox1（BS_CHECKBOX）

22 CreateWindow(BUTTON,L"Checkbox1",BS_CHECKBOX|WS_VISIBLE,

23 rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB1,NULL,NULL);

24 //往下移动矩形位置(X轴不变,Y轴位置增加rc.h+10个像素)

25 OffsetRect(&rc,0,rc.h+10);

26 //创建复选框Checkbox2（BS_CHECKBOX）

27 CreateWindow(BUTTON,L"Checkbox2",BS_CHECKBOX|WS_VISIBLE,

28 rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB2,NULL,NULL);

29 OffsetRect(&rc,0,rc.h+10);

30 //创建复选框Checkbox3--不响应输入设备（WS_DISABLED）

31 CreateWindow(BUTTON,L"Checkbox3",WS_DISABLED|BS_CHECKBOX|WS_VISIBLE,

32 rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB3,NULL,NULL);

33 OffsetRect(&rc,0,rc.h+10);

34 //创建复选框Checkbox4--类似按钮，当被按下时，该按钮下沉（BS_PUSHLIKE）

35 CreateWindow(BUTTON,L"Checkbox4",BS_PUSHLIKE|BS_CHECKBOX|WS_VISIBLE,

36 rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB4,NULL,NULL);

37 rc.x =160;

38 rc.y =40;

39 rc.w =128;

40 rc.h =30;

41 //创建复选框Checkbox5--检测BN_CHECKED消息（BS_NOTIFY）

42 CreateWindow(BUTTON,L"Checkbox5",BS_NOTIFY|BS_CHECKBOX|WS_VISIBLE,

43 rc.x,rc.y,rc.w,rc.h,hwnd,ID_CB5,NULL,NULL);

44 return TRUE;

45 case WM_NOTIFY: //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,高16位为通知码;

46 lParam指向了一个NMHDR结构体.

47 {

48 u16 code,id;

49 NMHDR \*nr=(NMHDR*)lParam;

50 id =LOWORD(wParam);

51 code=HIWORD(wParam);

52 if(id >= ID_CB1 && id<= ID_CB5)

53 {

54 if(code == BN_CLICKED) //被点击了

55 {

56 if(SendMessage(nr->hwndFrom,BM_GETSTATE,0,0)&BST_CHECKED) //获取当前状态

57 { //复选框选中.

58 GUI_Printf("Checkbox Checked: ID:%04XH\r\n",id);

59 }

60 else

61 {//复选未框选中.

62 GUI_Printf("Checkbox Unchecked: ID:%04XH\r\n",id);

63 }

64 }

65

66 if(code == BN_CHECKED) //指定了BS_NOTIFY,才会产生该消息.

67 { //复选框被选中.

68 GUI_Printf("Checkbox Checked: ID:%04XH\r\n",id);

69 }

70

71 }

72 if(id == ID_EXIT && code == BN_CLICKED)

73 {

74 PostCloseMessage(hwnd); //产生WM_CLOSE消息关闭主窗口

75 }

76

77 }

78 break;

79 case WM_CTLCOLOR:

80 {

81 u16 id;

82

83 id =LOWORD(wParam);

84

85 if(id== ID_CB5)

86 {

87 CTLCOLOR \*cr;

88 cr =(CTLCOLOR*)lParam;

89

90 if(SendMessage(GetDlgItem(hwnd,id),BM_GETSTATE,0,0)&BST_CHECKED)

91 {

92 //设置文字颜色

93 cr->TextColor =RGB888(250,0,0);

94 //设置背景颜色

95 cr->BackColor =RGB888(220,200,200);

96 //设置边框颜色

97 cr->BorderColor =RGB888(30,30,230);

98 //设置前景颜色

99 cr->ForeColor =RGB888(100,250,100);

100 }

101 else

102 {

103 cr->TextColor =RGB888(10,150,10);

104 cr->BackColor =RGB888(200,220,200);

105 cr->BorderColor =RGB888(50,50,50);

106 cr->ForeColor =RGB888(180,200,230);

107 }

108 return TRUE;

109 }

110 else

111 {

112 return FALSE;

113 }

114

115 }

116 default:

117 return DefWindowProc(hwnd,msg,wParam,lParam);

118 }

119

120 return WM_NULL;

121 }

1. WM_CREATE

在WM_CREATE消息创建控件，如表格 7‑1所示。

表格 7‑1 控件的具体信息

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

WM_NOTIFY消息用来处理控件的动作响应，该消息的参数wParam低16位为发送该消息的控件ID，高16位为通知码，即控件的动作。可以利用LOWORD函数和HIWORD函数来读取控件的ID和通知码。根据通知码，来实现控件的动作响应。代码清单
7‑3中，调用SendMessage给复选框控件发送消息BM_GETSTATE，实现检测复选框是否被选中。并输出到串口助手。

既然已经知道控件被点击了，为什么还要发送消息，去获取控件的当前状态呢？可能会有人有这个疑问。举个例子，电源开关。你拨了一下，你怎么知道电路有没有电？是不是要看电源指示灯亮不亮。亮了，说明开关是由断开到闭合。灭了，说明开关是由闭合到断开。这里也是一样的道理：你点击控件，至于控件是由选中到未选中，还是由
未选中到选中，就是通过发送消息BM_GETSTATE来检测的。

注意，只有拥有BS_NOTIFY的控件，才可以发送BN_CHECKED的消息，用于检测控件是否被按下（未松开）。

按钮控件EXIT，是用来关闭父窗口的。单击时，会发送关闭消息。

3. WM_CTLCOLOR

控件在绘制前，会向其父窗口发送WM_CTLCOLOR消息，该消息的参数wParm低16位产生该消息的窗口ID。参数lParam指向一个CTLCOLOR的结构体指针地址。代码清单 7‑4。

代码清单 7‑4 CTLCOLOR的结构体（文件emXGUI.h）

1 typedef struct

2 {

3 COLOR_RGB32 TextColor; //文字颜色

4 COLOR_RGB32 BorderColor; //边框颜色。

5 COLOR_RGB32 BackColor; //背景颜色。

6 COLOR_RGB32 ForeColor; //前景颜色。

7 }CTLCOLOR;

在代码清单 7‑3中，调用GetDlgItem来获取父窗口中CheckBox5的句柄，向CheckBox5发送消息BM_GETSTATE，来获取CheckBox5的状态值。GetDlgItem的用法，可以查阅《emXGUI API编程手册》的窗口/消息系统API。

根据控件的状态值，设置控件窗口的文字颜色(TextColor)，边框颜色(BorderColor)，
背景颜色(BackColor)，前景颜色(ForeColor)，改变控件窗口的外观颜色。一定要返回TRUE，否则的话，则按照默认方案来配置。前景颜色指的是选中后，CheckBox框框，也就是平时打钩的地方，显示的颜色。

4. default—用户不关心的消息

调用DefWindowProc来处理。

为什么没有重绘消息呢？是窗口不用重绘吗？答案是肯定的，不是说任何窗口在移动和创建的过程中，都需要进行重绘吗。这是没有错的，不过因为在图 7‑2我们并没有在客户区显示内容，而控件的重绘是由emXGUI内部完成的，因此，这里没有WM_PAINT也是可以的。

最后，将函数GUI_DEMO_Checkbox加入到GUI_AppMain函数中。

代码清单 7‑5 GUI_AppMain函数（文件GUI_AppMain.c）

1 void GUI_AppMain(void)

2 {

3 while(1)

4 {

5 GUI_DEMO_Button();

6 GUI_DEMO_Checkbox();

7 }

8 }

.. _实验现象-2:

实验现象
^^^^

实验结果如图 7‑3和 图 7‑4。图 7‑3是界面的初始化状态，图 7‑4是界面的CheckBox被选中状态。当CheckBox4被选中时，CheckBox4会像按钮一样下沉。CheckBox5在选中状态下的文字，边框， 背景和前景的颜色发生了改变。

|docx033|

图 7‑3 实验结果

|docx034|

图 7‑4 实验结果（选中状态）

单选按钮控件
------

最后，我们学习图 7‑1处的单选按钮控件。顾名思义，单选按钮，就是只可以选择一个选项。例如串口收发的停止位，只可以是1、1.5、2位中的某一个值。

|docx024|

图 8‑1 各种按钮

创建单选按钮控件
~~~~~~~~

.. _标准消息类型及参数说明-3:

标准消息类型及参数说明
^^^^^^^^^^^

单选按钮需要用到的消息和处理方式，也没有什么变化。有什么不懂的地方，可以参考按钮控件章节的标准消息类型及参数说明。

创建单选按钮控件函数
^^^^^^^^^^

代码清单 8‑1 创建窗口函数（文件emXGUI.h）

1 HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,

2 U32 dwStyle, int x, int y, int nWidth, int nHeight,

3 HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);

1) lpClass：单选按钮属于按钮控件中的一类，这里选择BUTTON类。

2) dwStyle：单选按钮的风格。参数BS_RADIOBOX代表该控件为单选按钮。当使用单选按钮时，这个参数是必须的。单选按钮控件也支持窗口以及按钮的风格参数。

3) WinId：控件的ID值。单选按钮控件的ID值高16位为GroupID号，只有在同一组内的单选按钮，才会有“多选一"的效果。

至于其他的参数，和创建按钮一样，也是同样的用法，这里不作描述。

创建单选按钮控件实验
~~~~~~~~~~

.. _设计要求-3:

设计要求
^^^^

图 8‑2只是简单地展示了单选按钮控件，下面通过代码讲解如何实现这个界面。

|docx035|

图 8‑2 设计要求

.. _代码分析-3:

代码分析
^^^^

(1) 创建父窗口

代码清单 8‑2 GUI_DEMO_Radiobox函数（文件GUI_DEMO_Radiobox.c）

1 void GUI_DEMO_Radiobox(void)

2 {

3 HWND hwnd;

4 WNDCLASS wcex;

5 MSG msg;

6 /////

7 wcex.Tag = WNDCLASS_TAG;

8 wcex.Style = CS_HREDRAW \| CS_VREDRAW;

9 wcex.lpfnWndProc = win_proc;

10 wcex.cbClsExtra = 0;

11 wcex.cbWndExtra = 0;

12 wcex.hInstance = 0;//hInst;

13 wcex.hIcon = 0;//LoadIcon(hInstance,(LPCTSTR)IDI_WIN32_APP_TEST);

14 wcex.hCursor = 0;//LoadCursor(NULL, IDC_ARROW);

15

16 hwnd =CreateWindowEx( NULL,

17 &wcex,

18 \_T("GUI Demo - Radiobox"),

19 WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,

20 0,0,GUI_XSIZE,GUI_YSIZE,

21 NULL,NULL,NULL,NULL);

22 ShowWindow(hwnd,SW_SHOW);

23 while(GetMessage(&msg,hwnd))

24 {

25 TranslateMessage(&msg);

26 DispatchMessage(&msg);

27 }

28 }

创建父窗口，标题栏为“GUI Demo - Radiobox”，带有大小边框，设置win_proc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE消息

代码清单 8‑3 WM_CREATE消息响应（文件GUI_DEMO_Radiobox.c）

1 case WM_CREATE:

2 {

3 //获得客户区的大小

4 GetClientRect(hwnd,&rc);

5

6 CreateWindow(BUTTON,L"EXIT",WS_VISIBLE,rc.w-100,8,80,48,hwnd,ID_EXIT,NULL,NULL);

7

8 //创建第1组单选按钮(窗口ID的高16位为GroupID号，只有在同一组内的单选按钮，才会有"多选一"的效果)

9

10 rc.x =20;

11 rc.y =30;

12 rc.w =120;

13 rc.h =32;

14 CreateWindow(BUTTON,L"Radiobox1",BS_RADIOBOX|WS_VISIBLE,

15 rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|ID_RB1,NULL,NULL);

16 OffsetRect(&rc,0,rc.h+10);

17 CreateWindow(BUTTON,L"Radiobox2",WS_DISABLED|BS_RADIOBOX|WS_VISIBLE,

18 rc.x,rc.y,rc.w,rc.h,hwnd,(1<<16)|ID_RB2,NULL,NULL);

19

20 //创建第2组单选按钮(GroupID号为2,使用常规按钮风格(BS_PUSHLIKE)).

21 OffsetRect(&rc,0,rc.h+10);

22 CreateWindow(BUTTON,L"Radiobox3",BS_RADIOBOX|BS_PUSHLIKE|WS_VISIBLE,

23 rc.x,rc.y,rc.w,rc.h,hwnd,(2<<16)|ID_RB3,NULL,NULL);

24 OffsetRect(&rc,0,rc.h+10);

25 CreateWindow(BUTTON,L"Radiobox4",BS_RADIOBOX|BS_PUSHLIKE|WS_VISIBLE,

26 rc.x,rc.y,rc.w,rc.h,hwnd,(2<<16)|ID_RB4,NULL,NULL);

27

28 //创建第3组单选按钮(GroupID号为3).

29 rc.x =160;

30 rc.y =30;

31 rc.w =120;

32 rc.h =32;

33 CreateWindow(BUTTON,L"Radiobox5",BS_RADIOBOX|WS_VISIBLE,

34 rc.x,rc.y,rc.w,rc.h,hwnd,(3<<16)|ID_RB5,NULL,NULL);

35 OffsetRect(&rc,0,rc.h+10);

36 CreateWindow(BUTTON,L"Radiobox6",BS_RADIOBOX|WS_VISIBLE,

37 rc.x,rc.y,rc.w,rc.h,hwnd,(3<<16)|ID_RB6,NULL,NULL);

38 return TRUE;

39 }

WM_CREATE消息创建的控件，如表格 8‑1所示。

表格 8‑1 控件的具体信息

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

代码清单 8‑4控件ID值（文件GUI_DEMO_Radiobox.c）

1 #define ID_RB1 0x1101

2 #define ID_RB2 0x1102

3 #define ID_RB3 0x1103

4 #define ID_RB4 0x1104

5 #define ID_RB5 0x1105

6 #define ID_RB6 0x1106

代码清单 8‑4控件ID值（文件GUI_DEMO_Radiobox.罗列了所有单选按钮的ID值。其高16位代表所属Group的ID号。以组3为例，组1、组2都是一样的道理。3<<16等价于\ :math:`3*2^{16}`\
，转换为十六进制，就是0x00030000，再通过与ID_RB5进行或运算，得到结果为0x00031105，最前面的四位数就是Group的ID号。

2. WM_NOTIFY消息

代码清单 8‑5 WM_NOTIFY消息响应（文件GUI_DEMO_Radiobox.c）

1 case WM_NOTIFY: //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,高16位为通知码;

2 lParam指向了一个NMHDR结构体.

3 {

4 u16 code,id;

5

6 id =LOWORD(wParam);

7 code=HIWORD(wParam);

8 if(id >= ID_RB1 && id<= ID_RB6)

9 {

10 if(code == BN_CHECKED)

11 { //单选框选中.

12 GUI_Printf("Radiobox Checked: ID:%04XH\r\n",id);

13 }

14 }

15 if(id == ID_EXIT && code == BN_CLICKED)

16 {

17 PostCloseMessage(hwnd);//产生WM_CLOSE消息关闭主窗口

18 }

19 break;

20 }

调用LOWORD和HIWORD读取控件的ID和通知码。单选按钮选中，则在串口输出控件的ID号。单击EXIT按钮，则会发送WM_CLOSE消息关闭主窗口。

3. WM_CTLCOLOR消息

代码清单 8‑6 WM_CTLCOLOR消息响应（文件GUI_DEMO_Radiobox.c）

1 case WM_CTLCOLOR:

2 {

3 u16 id;

4 id =LOWORD(wParam);

5 if(id== ID_RB5 \|\| id == ID_RB6) //只改变 RB5,RB6的颜色.

6 {

7 CTLCOLOR \*cr;

8 cr =(CTLCOLOR*)lParam;

9 if(SendMessage(GetDlgItem(hwnd,id),BM_GETSTATE,0,0)&BST_CHECKED)

10 {

11 cr->TextColor =RGB888(250,0,0); //文字颜色（RGB32颜色格式)

12 cr->BackColor =RGB888(220,200,200); //背景颜色（RGB32颜色格式)

13 cr->BorderColor =RGB888(30,30,230); //边框颜色（RGB32颜色格式)

14 cr->ForeColor =RGB888(100,250,100); //前景颜色（RGB32颜色格式)

15 }

16 else

17 {

18 cr->TextColor =RGB888(20,20,250);

19 cr->BackColor =RGB888(200,220,200);

20 cr->BorderColor =RGB888(50,50,50);

21 cr->ForeColor =RGB888(180,200,230);

22 }

23 return TRUE;

24 }

25 else

26 {

27 return FALSE;

28 }

29 }

WM_CTLCOLOR消息的lParam参数为产生该消息的窗口ID。这里只改变组3成员的外观，最后返回TRUE，否则将按照系统默认的样式来配置。

通过发送消息BM_GETSTATE，来得到当前控件是否被选中，同时改变控件的外观颜色。前景颜色，就是控件在选中状态，显示的颜色。

4. WM_PAINT消息

代码清单 8‑7 WM_PAINT消息响应（文件GUI_DEMO_Radiobox.c）

1 case WM_PAINT: //窗口需要重绘制时，会自动收到该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5 hdc =BeginPaint(hwnd,&ps);

6 SetTextColor(hdc,MapRGB(hdc,0,0,255));

7 TextOut(hdc,8,4,L"Radiobox Test:",-1);

8 EndPaint(hwnd,&ps);

9 return TRUE;

10 }

窗口重绘时，在客户区（8，4）处绘制蓝色的字符串：Radiobox Test:。

5. default消息

代码清单 8‑8 default消息响应（文件GUI_DEMO_Radiobox.c）

1 default:

2 return DefWindowProc(hwnd,msg,wParam,lParam);

调用DefWindowProc函数来处理用户不关心的消息。

最后，将GUI_DEMO_Radiobox加入到GUI_AppMain中，见代码清单 8‑9 GUI_AppMain函数（文件GUI_AppMain.。

代码清单 8‑9 GUI_AppMain函数（文件GUI_AppMain.c）

1 void GUI_AppMain(void)

2 {

3 while(1)

4 {

5 GUI_DEMO_Button();

6 GUI_DEMO_Checkbox();

7 GUI_DEMO_Radiobox();

8 }

9 }

.. _实验现象-3:

实验现象
^^^^

除了尺寸有些改变，在LCD显示的控件较大，其余的差不多是一模一样。见图 8‑3和图 8‑4。

|docx036|

图 8‑3 实验结果

|docx037|

图 8‑4 实验结果（选中状态）

文本框控件
-----

文本框控件在我们生活中，并不少见。如图 9‑1，这是一个登录界面。我们输入账号和密码处，其实就是文本框控件。emXGUI也提供这样的功能，需要用户外加键盘作为输入设备。

|docx038|

图 9‑1 常见的文本框控件

创建文本框控件
~~~~~~~

.. _标准消息类型及参数说明-4:

标准消息类型及参数说明
^^^^^^^^^^^

本章只是大致上讲解如何创建文本框控件，修稿控件的外观颜色，是禁止用户输入的。键盘输入，Emmmmm…

本章使用的消息类型，有WM_CREATE、WM_TIMER、WM_NOTIFY和WM_CTLCOLOR。WM_CREATE消息用于创建控件；这里使用WM_TIMER，主要是给大家演示一下， 如何在文本框显示变量。WM_NOTIFY消息用来处理
EXIT按钮消息。使用WM_CTLCOLOR消息来改变控件的外观颜色。

创建文本框控件函数
^^^^^^^^^

代码清单 9‑1创建窗口函数（文件emXGUI.h）

1 HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,

2 U32 dwStyle, int x, int y, int nWidth, int nHeight,

3 HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);

1) lpClass：窗口类。对于系统标准控件，可以为：BUTTON(常规按钮，复选框，单选框，组合框)，SCROLLBAR(水平/垂直滚动条)， LISTBOX(列表框)。TEXTBOX（文本框）…等等。这里选择PROGRESSBAR。

2) dwStyle：文本框的风格。参数TBS_SUNK表示该控件具有凹下边框样式。文本框控件支持窗口风格参数。

至于其他的参数，也是同样的用法，这里不作描述。我们创建控件调用的CreateWindow函数，实际上就是CreateWindowEx函数。

创建文本框控件实验
~~~~~~~~~

.. _设计要求-4:

设计要求
^^^^

图 9‑2，是本章节的设计要求。左边这一列文本框显示的文本内容格式不同。右边的文本框第一个是显示变量，变量值实时更新。后两个是多行显示。下面看看，如何用代码实现该界面。

|docx039|

图 9‑2 设计要求

.. _代码分析-4:

代码分析
^^^^

(1) 创建父窗口

代码清单 9‑2 GUI_DEMO_Textbox函数（文件GUI_DEMO_Textbox.c）

1 void GUI_DEMO_Textbox(void)

2 {

3 HWND hwnd;

4 WNDCLASS wcex;

5 MSG msg;

6 //配置wcex参数

7 wcex.Tag = WNDCLASS_TAG;

8 wcex.Style = CS_HREDRAW \| CS_VREDRAW;

9 wcex.lpfnWndProc = win_proc;

10 wcex.cbClsExtra = 0;

11 wcex.cbWndExtra = 0;

12 wcex.hInstance = NULL;//hInst;

13 wcex.hIcon = NULL;//LoadIcon(hInstance,(LPCTSTR)IDI_WIN32_APP_TEST);

14 wcex.hCursor = NULL;//LoadCursor(NULL, IDC_ARROW);

15 //创建主窗口

16 hwnd =CreateWindowEx( NULL,

17 &wcex,

18 L"GUI Demo - Textbox",

19 WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,

20 0,0,GUI_XSIZE,GUI_YSIZE,

21 NULL,NULL,NULL,NULL);

22 //显示主窗口

23 ShowWindow(hwnd,SW_SHOW);

24 //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)

25 while(GetMessage(&msg,hwnd))

26 {

27 TranslateMessage(&msg);

28 DispatchMessage(&msg);

29 }

30 }

创建父窗口，标题栏为“GUI Demo - Textbox”，带有大小边框，设置win_proc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

代码清单 9‑3 WM_CREATE消息响应（文件GUI_DEMO_Textbox.c）

1 case WM_CREATE:

2 {

3 GetClientRect(hwnd,&rc);

4

5 CreateWindow(BUTTON,L"EXIT",WS_VISIBLE,rc.w-100,8,80,48,hwnd,ID_EXIT,NULL,NULL);

6 rc.x =20;

7 rc.y =30;

8 rc.w =200;

9 rc.h =80;

10 //创建文本框控件，返回控件句柄wnd

11 wnd=CreateWindow(TEXTBOX,L"Text1",WS_VISIBLE,

12 rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB1,NULL,NULL);

13 //发送TBM_SET_TEXTFLAG，设置文本框的内容，lParam参数代表显示内容的格式

14 SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_BKGND|DT_BORDER);

15 //往下移动矩形位置(X轴不变,Y轴位置增加rc.h+10个像素)

16 OffsetRect(&rc,0,rc.h+10);

17 //创建文本框控件(可见，具有凹下边框样式)，返回控件句柄wnd

18 wnd=CreateWindow(TEXTBOX,L"Text2",TBS_SUNK|WS_VISIBLE,

19 rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB2,NULL,NULL);

20 SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_BKGND);

21

22 OffsetRect(&rc,0,rc.h+10);

23 wnd=CreateWindow(TEXTBOX,L"Text3",WS_VISIBLE,

24 rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB3,NULL,NULL);

25 SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_SINGLELINE|DT_RIGHT|DT_VCENTER|DT_BKGND|DT_BORDER);

26

27 OffsetRect(&rc,0,rc.h+10);

28 wnd=CreateWindow(TEXTBOX,L"Text4",WS_DISABLED|WS_VISIBLE,

29 rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB4,NULL,NULL);

30SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_SINGLELINE|DT_VCENTER|DT_BOTTOM|DT_BKGND|DT_BORDER);

31

32 rc.x =250;

33 rc.y =30;

34 rc.w =200;

35 rc.h =80;

36 wnd=CreateWindow(TEXTBOX,L"Text5",WS_VISIBLE,

37 rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB5,NULL,NULL);

38 SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_BKGND);

39 OffsetRect(&rc,0,rc.h+10);

40 rc.w =320;

41 rc.h =140;

42 //创建文本框控件Text6，返回控件句柄wnd

43 wnd=CreateWindow(TEXTBOX,L"Text6\r\nMulti-Line\r\nVCENTER+CENTER",WS_VISIBLE,

44 rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB6,NULL,NULL);

45 //发送TBM_SET_TEXTFLAG，设置文本框的内容，多行显示

46 SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_VCENTER|DT_CENTER|DT_BKGND|DT_BORDER);

47

48 OffsetRect(&rc,0,rc.h+10);

49

50 wnd=CreateWindow(TEXTBOX,L"Text7\r\nMulti-Line\r\nBOTTOM+RIGHT",TBS_SUNK|WS_VISIBLE,

51 rc.x,rc.y,rc.w,rc.h,hwnd,ID_TB7,NULL,NULL);

52 SendMessage(wnd,TBM_SET_TEXTFLAG,0,DT_BOTTOM|DT_RIGHT|DT_BKGND|DT_BORDER);

53

54 SetTimer(hwnd,ID_TMR1,200,TMR_START,NULL); //创建一个200ms定时器

55 return TRUE;

56 }

WM_CREATE消息创建的控件，如表格 9‑1所示。

表格 9‑1 控件的具体信息

======== ===== ======= ====================== ====================================
控件类型 名称  ID值    窗口风格               文本格式
======== ===== ======= ====================== ====================================
BUTTON   EXIT  ID_EXIT WS_VISIBLE             无
TEXTBOX  Text1 ID_TB1  WS_VISIBLE             DT_SINGLELINE|DT_LEFT|DT_VCENTER

                                              \|DT_BKGND|DT_BORDER \        Text2 ID_TB2  TBS_SUNK|WS_VISIBLE    DT_SINGLELINE|DT_CENTER\|

                                              DT_VCENTER|DT_BKGND \        Text3 ID_TB3  WS_VISIBLE             DT_SINGLELINE|DT_RIGHT|DT_VCENTER\|

                                              DT_BKGND|DT_BORDER \        Text4 ID_TB4  WS_DISABLED|WS_VISIBLE DT_SINGLELINE|DT_VCENTER|DT_BOTTOM\|

                                              DT_BKGND|DT_BORDER \        Text5 ID_TB5  WS_VISIBLE             DT_SINGLELINE|DT_CENTER\|

                                              DT_VCENTER|DT_BKGND \        Text6 ID_TB6  WS_VISIBLE             DT_VCENTER|DT_CENTER\|

                                              DT_BKGND|DT_BORDER \        Text7 ID_TB7  TBS_SUNK|WS_VISIBLE    DT_BOTTOM|DT_RIGHT\|

                                              DT_BKGND|DT_BORDER ======== ===== ======= ====================== ====================================

点击EXIT按钮，产生WM_CLOSE消息关闭主窗口。调用CreateWindow函数，创建7个文本框，文本框的文本格式，见表格 9‑2。

表格 9‑2文本框的文本格式说明

============= ==================================
属性值        文本格式
============= ==================================
DT_SINGLELINE 单行模式。没有该参数时，为多行模式
DT_CENTER     水平居中对齐
DT_LEFT       水平居左对齐
DT_RIGHT      水平居右对齐
DT_BOTTOM     垂直底部对齐
DT_VCENTER    垂直中间对齐
DT_BORDER     是否绘制边框
DT_BKGND      是否绘制背景
============= ==================================

2. WM_NOTIFY

代码清单 9‑4 WM_NOTIFY消息响应（文件GUI_DEMO_Textbox.c）

1 case WM_NOTIFY:

2 {

3 u16 id, code;

4 id =LOWORD(wParam);

5 code = HIWORD(wParam);

6 //EXIT按钮弹起

7 if(id == ID_EXIT && code == BN_CLICKED)

8 {

9 count = 0;

10 PostCloseMessage(hwnd);//产生WM_CLOSE消息关闭主窗口

11 }

12 }

ID_EXIT单击时，会调用PostCloseMessage发送窗口关闭消息WM_CLOSE，来关闭主窗口。

3. WM_TIMER

代码清单 9‑5 WM_TIMER消息响应（文件GUI_DEMO_Textbox.c）

1 case WM_TIMER:

2 {

3 u16 id;

4 //读取控件ID值

5 id =LOWORD(wParam);

6

7 if(id==ID_TMR1)

8 {

9 count++;

10

11 x_wsprintf(wbuf,L"%04d",count);

12 //获取控件句柄

13 wnd =GetDlgItem(hwnd,ID_TB5);

14 //设置控件显示文本框

15 SetWindowText(wnd,wbuf);

16 }

17 }

18 return TRUE;

WM_CREATE消息中，创建了ID为ID_TMR1的定时器。定时器到达设定值时，发送WM_TIMER消息。在WM_TIMER消息中，实现count变量自加，同时调用SetWindowText函数将变量值在文本框Text5显示。

4. WM_CTLCOLOR

代码清单 9‑6 WM_CTLCOLOR消息响应（文件GUI_DEMO_Textbox.c）

1 case WM_CTLCOLOR:

2 {

3 /\* 控件在绘制前，会发送 WM_CTLCOLOR到父窗口.

4 \* wParam参数指明了发送该消息的控件ID;lParam参数指向一个CTLCOLOR的结构体指针.

5 \* 用户可以通过这个结构体改变控件的颜色值.

6 用户修改颜色参数后，需返回TRUE，否则，系统

7 \* 将忽略本次操作，继续使用默认的颜色进行绘制.

8 \*

9 \*/

10 u16 id;

11 id =LOWORD(wParam);

12 if(id== ID_TB5 \|\| id== ID_TB6)

13 {

14 CTLCOLOR \*cr;

15 cr =(CTLCOLOR*)lParam;

16 cr->TextColor =RGB888(255,180,180);//文字颜色（RGB888颜色格式)

17 cr->BackColor =RGB888(100,0,0);//背景颜色（RGB888颜色格式)

18 cr->BorderColor =RGB888(255,10,10);//边框颜色（RGB888颜色格式)

19 return TRUE;

20 }

21 else

22 {

23 return FALSE;

24 }

25 }

改变控件窗口的文字颜色(TextColor)，边框颜色(BorderColor)， 背景颜色(BackColor)，一定要返回TRUE，否则的话，则按照默认方案来配置。

最后，将GUI_DEMO_Textbox加入到GUI_AppMain中，见代码清单 9‑7。

代码清单 9‑7 GUI_AppMain函数（文件GUI_AppMain.c）

1 void GUI_AppMain(void)

2 {

3 while(1)

4 {

5 GUI_DEMO_Button();

6 GUI_DEMO_Checkbox();

7 GUI_DEMO_Radiobox();

8 GUI_DEMO_Textbox();

9 }

10 }

.. _实验现象-4:

实验现象
^^^^

如图 9‑3除了控件的尺寸有些变化，布局和图 9‑2差不多是一模一样的。\ |docx040|

图 9‑3 实验结果

进度条控件
-----

计算机在处理任务时，任务的进度经常采用进度条来显示，还可以表示处理任务的速度，完成度，剩余未完成任务量和可能需要处理时间，一般以长方形条状显示。如图 10‑1。

|docx041|

图 10‑1 进度条示例

创建进度条控件
~~~~~~~

.. _标准消息类型及参数说明-5:

标准消息类型及参数说明
^^^^^^^^^^^

本章使用的消息类型常用的有WM_CREATE、WM_TIMER、WM_NOTIFY和WM_CTLCOLOR。WM_CREATE消息用于创建控件；这里使用WM_TIMER，是用了修改进度值。WM_NOTIFY消息用来处理
EXIT按钮消息。使用WM_CTLCOLOR消息来改变控件的外观颜色。下面介绍一个新的消息类型：

WM_CLOSE消息：之前讲过，当用户按下EXIT按钮后，会调用PostCloseMessage发送关闭主窗口消息，这个消息就是WM_CLOSE。默认情况下，是执行emXGUI的关闭操作，这样就会导致进度条的进度值没有清零，计数依然从上一次的计数值开始。所以我需要在关闭主窗口之前做清零操作。利用窗口
关闭时，会接收到WM_CLOSE消息。在该消息中，对变量进行清零。

进度条配置结构体
^^^^^^^^

emXGUI使用PROGRESSBAR_CFG结构体来管理进度条。创建进度条完成后，需要发送PBM_SET_CFG消息，来初始化该结构体所有的参数。相关的成员变量，见代码清单 10‑1。

代码清单 10‑1进度条配置结构体PROGRESSBAR_CFG（文件emXGUI.h）

1 typedef struct{

2 u16 cbSize; //结构体的大小

3 u16 fMask; //功能选择

4 u32 Rangle; //进度值的最大值

5 u32 Value; //当前的进度值

6 u32 TextFlag; //文字格式

7 }PROGRESSBAR_CFG;

1) cbSize：用来存放结构体的大小。用户提供的 PROGRESSBAR_CFG , 必须要将 cbSize 值设置成 sizeof(PROGRESSBAR_CFG)。

2) fMask：功能选择位。只有相应的 MASK 位置1，才会更新到 进度条控件的内部数据结构体。

3) Rangle：进度值的最大值。默认是100。

4) Value：当前的进度值。可以发送PBM_GET_VALUE，来获取当前的进度值。

5) TextFlag：文字格式。可以是DT_BOTTOM（垂直底部对齐）、DT_RIGHT（水平居右对齐）、DT_SINGLELINE（单行模式）等等。还有其他的参数，可以参考emXGUI.h的注释来使用。

创建进度条控件函数
^^^^^^^^^

代码清单 10‑2创建窗口函数（文件emXGUI.h）

1 HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,

2 U32 dwStyle, int x, int y, int nWidth, int nHeight,

3 HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);

1) lpClass：窗口类。进度条控件，这里选择PROGRESSBAR。

2) dwStyle：进度条的风格。进度条控件支持窗口风格参数，还可以使用以下参数：PBS_TEXT（显示文字）、PBS_3D（立体风格）、PBS_FLAT（平面风格）、PBS_ALIGN_LEFT（从左往右增长）、PBS_ALIGN_RIGHT（从右往左增长）、PBS_ALIGN_TOP（从上往下
增长）和PBS_ALIGN_BOTTOM（从下往上增长）

至于其他的参数，也是同样的用法，这里不作描述。我们创建控件调用的CreateWindow函数，实际上就是CreateWindowEx函数。

创建进度条控件实验
~~~~~~~~~

.. _设计要求-5:

设计要求
^^^^

图 9‑2是本章节的设计要求，利用进度条实时显示进度条的进度值。下面看看，如何用代码实现该界面。

|docx042|

图 10‑2 设计要求

.. _代码分析-5:

代码分析
^^^^

(1) 创建父窗口

代码清单 10‑3 GUI_DEMO_Progressbar函数（文件GUI_DEMO_Progressbar.c）

1 void GUI_DEMO_Progressbar(void)

2 {

3 HWND hwnd;

4 WNDCLASS wcex;

5 MSG msg;

6 ////第1部分：配置wcex参数。

7 wcex.Tag = WNDCLASS_TAG;

8 wcex.Style = CS_HREDRAW \| CS_VREDRAW;

9 wcex.lpfnWndProc = win_proc;

10 wcex.cbClsExtra = 0;

11 wcex.cbWndExtra = 0;

12 wcex.hInstance = 0;//hInst;

13 wcex.hIcon = 0;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);

14 wcex.hCursor = 0;//LoadCursor(NULL, IDC_ARROW);

15 //第2部分：创建主窗口

16 hwnd =CreateWindowEx(NULL,

17 &wcex,

18 \_T("GUI Demo - Progressbar"),

19 WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,

20 0,0,GUI_XSIZE,GUI_YSIZE,

21 NULL,NULL,NULL,NULL);

22 //第3部分：显示主窗口

23 ShowWindow(hwnd,SW_SHOW);

24 //窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。

25 while(GetMessage(&msg,hwnd))

26 {

27 TranslateMessage(&msg);

28 DispatchMessage(&msg);

29 }

30 }

创建父窗口，标题栏为“GUI Demo - Progressbar”，带有大小边框，设置win_proc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

代码清单 10‑4 WM_CREATE消息响应（文件GUI_DEMO_Progressbar.c）

1 case WM_CREATE:

2 {

3 GetClientRect(hwnd,&rc);

4 if(1)

5 {

6 //PROGRESSBAR_CFG结构体的大小

7 cfg.cbSize = sizeof(PROGRESSBAR_CFG);

8 //开启所有的功能

9 cfg.fMask = PB_CFG_ALL;

10 //文字格式水平，垂直居中

11 cfg.TextFlag = DT_VCENTER|DT_CENTER;

12 // 创建自绘制的进度条VProgressbar

13 wnd = CreateWindow(PROGRESSBAR,L"VProgressbar",

14 WS_OWNERDRAW|PBS_ALIGN_BOTTOM|WS_VISIBLE,

15 20,20,48,320,hwnd,ID_PROGBAR1,NULL,NULL);

16 //初始化PROGRESSBAR_CFG结构体

17 SendMessage(wnd,PBM_GET_CFG,TRUE,(LPARAM)&cfg);

18 SendMessage(wnd,PBM_SET_CFG,TRUE,(LPARAM)&cfg);

19 // 创建从右往左增长的进度条VProgressbar

20 wnd = CreateWindow(PROGRESSBAR,L"PROGBAR2 & Right align",

21 PBS_TEXT|PBS_ALIGN_RIGHT|WS_VISIBLE,

22 100,100,280,48,hwnd,ID_PROGBAR2,NULL,NULL);

23 SendMessage(wnd,PBM_GET_CFG,TRUE,(LPARAM)&cfg);

24 SendMessage(wnd,PBM_SET_CFG,TRUE,(LPARAM)&cfg);

25 //创建从左往右增长的进度条VProgressbar

26 wnd = CreateWindow(PROGRESSBAR,L"PROGBAR3 & Left align",

27 PBS_TEXT|PBS_ALIGN_LEFT|WS_VISIBLE,

28 100,200,280,48,hwnd,ID_PROGBAR3,NULL,NULL);

29 SendMessage(wnd,PBM_GET_CFG,TRUE,(LPARAM)&cfg);

30 SendMessage(wnd,PBM_SET_CFG,TRUE,(LPARAM)&cfg);

31 }

32 //创建EXIT按钮

33 CreateWindow(BUTTON,L"EXIT",WS_VISIBLE,rc.w-100,8,80,48,hwnd,ID_EXIT,NULL,NULL);

34 //创建200ms定时器

35 SetTimer(hwnd,1,200,TMR_START,NULL);

36 return TRUE;

37 }

调用CreateWindow函数创建进度条控件，发送PBM_SET_CFG消息来配置进度条。cbSize的值必须为sizeof(PROGRESSBAR_CFG)。创建EXIT按钮，用来关闭窗口以及创建200ms定时器。

2. WM_TIMER

代码清单 10‑5 WM_TIMER消息响应（文件GUI_DEMO_Progressbar.c）

1 case WM_TIMER:

2 {

3 pb1_val +=1;

4 if(pb1_val > 100)

5 {

6 pb1_val =0;

7 }

8 wnd =GetDlgItem(hwnd,ID_PROGBAR1);

9 //设置进度值

10 SendMessage(wnd,PBM_SET_VALUE,TRUE,pb1_val);

11 pb2_val +=2;

12 if(pb2_val > 100)

13 {

14 pb2_val =0;

15 }

16 //获取窗口句柄

17 wnd =GetDlgItem(hwnd,ID_PROGBAR2);

18 SendMessage(wnd,PBM_SET_VALUE,TRUE,pb2_val);

19

20 wnd =GetDlgItem(hwnd,ID_PROGBAR3);

21 SendMessage(wnd,PBM_SET_VALUE,TRUE,pb2_val);

22 return TRUE;

23 }

每当200ms计时结束时，就会将pb1_val值加1，pb2_val的值加2。调用GetDlgItem获取进度条控件的窗口句柄，同时将进度值发送给窗口，来实现实时更新进度条的进度值。

3. WM_CLOSE

代码清单 10‑6 WM\_ CLOSE消息响应（文件GUI_DEMO_Progressbar.c）

1 case WM_CLOSE:

2 {

3 pb1_val=0;

4 pb2_val=0;

5 break;

6 }

在WM_CLOSE中，对两个变量的值进行清零操作。

4. WM_CTLCOLOR

代码清单 10‑7 WM\_ CTLCOLOR消息响应（文件GUI_DEMO_Progressbar.c）

1 case WM_CTLCOLOR:

2 {

3 u16 id;

4 CTLCOLOR \*cr;

5

6 id =wParam;

7 cr =(CTLCOLOR*)lParam;

8 if(id==ID_PROGBAR3)

9 {

10 cr->TextColor =RGB888(250,250,250);

11 cr->BackColor =RGB888(0,0,0);

12 cr->BorderColor =RGB888(130,30,130);

13 cr->ForeColor =RGB888(200,0,200);

14 return TRUE;

15 }

16 return FALSE;

17 }

在WM_CTLCOLOR消息中，改变进度条控件PROGBAR3 的外观颜色。

5. WM_NOTIFY

代码清单 10‑8 WM\_ NOTIFY消息响应（文件GUI_DEMO_Progressbar.c）

1 case WM_NOTIFY:

2 {

3 u16 code,id;

4 id =LOWORD(wParam);

5 code=HIWORD(wParam);

6 if(id== ID_EXIT && code==BN_CLICKED)

7 { // EXIT按钮弹起

8 PostCloseMessage(hwnd); //产生WM_CLOSE消息关闭主窗口

9 }

10 }

按下EXIT按键，产生WM_CLOSE消息关闭主窗口。

6. WM_DRAWITEM

代码清单 10‑9 WM_DRAWITEM消息响应（文件GUI_DEMO_Progressbar.c）

1 case WM_DRAWITEM:

2 {

3 DRAWITEM_HDR \*ds;

4

5 ds =(DRAWITEM_HDR*)lParam;

6 progressbar_owner_draw(ds);

7 return TRUE;

8 }

进度条控件PROGBAR1拥有自定义绘制属性WS_OWNERDRAW，在绘制前都会给父窗口发送WM_DRAWITEM消息。在WM_DRAWITEM消息中，调用函数progressbar_owner_draw实现控件自定义，最后返回TURE。这里必须返回TURE，否则会按照默认方案进行配置。

代码清单 10‑10 progressbar_owner_draw函数（文件GUI_DEMO_Progressbar.c）

1 static void progressbar_owner_draw(DRAWITEM_HDR \*ds)

2 {

3 HWND hwnd;

4 HDC hdc;

5 RECT rc,m_rc[2];

6 // int range,val;

7 WCHAR wbuf[128];

8 PROGRESSBAR_CFG cfg;

9 hwnd =ds->hwnd;

10 hdc =ds->hDC;

11 /第一步/

12 //获取客户区矩形位置，大小

13 GetClientRect(hwnd,&rc);

14 //设置进度条的背景颜色

15 SetBrushColor(hdc,MapRGB(hdc,150,200,250));

16 //填充进度条的背景

17 FillRect(hdc,&ds->rc);

18 //绘制进度条的背景边框

19 DrawRect(hdc,&rc);

20 /第二步/

21 cfg.cbSize =sizeof(cfg);

22 cfg.fMask =PB_CFG_ALL;

23 SendMessage(hwnd,PBM_GET_CFG,0,(LPARAM)&cfg);

24 //生成进度条矩形

25 MakeProgressRect(m_rc,&rc,cfg.Rangle,cfg.Value,PB_ORG_BOTTOM);

26 //设置进度条的颜色

27 SetBrushColor(hdc,MapRGB(hdc,250,10,10));

28 //填充进度条

29 FillRoundRect(hdc,&m_rc[0],2);

30 //设置画笔颜色

31 SetPenColor(hdc,MapRGB(hdc,100,10,10));

32 //绘制进度条的边框，采用圆角边框

33 DrawRoundRect(hdc,&m_rc[0],2);

34 /显示进度值/

35 x_wsprintf(wbuf,L"%d",cfg.Value);

36 //InflateRect(&rc,40,0);

37 DrawText(hdc,wbuf,-1,&rc,DT_VCENTER|DT_CENTER);

38 }

进度条，其实是由两个部分构成，如图 10‑3，是进度度条的背景，是已经完成的进度。只要我们可以绘制这样的两个矩形，同时将它俩叠加到一块的话，就可以得到处的进度条了。

|docx043|

图 10‑3 原理绘制原理

代码清单 10‑10中的第一步，就是绘制一个处的矩形框框。调用GetClientRect函数获取子控件的位置，大小。使用SetBrushColor和SetPenColor来设置背景和边框的颜色，最后调用FillRect和DrawRect来绘制成。

代码清单 10‑10中的第二步，对应上图的处。发送消息PBM_GET_CFG，来获得进度条的配置参数，主要是当前的进度值。发送消息前，必须要将cbSize值设置成
sizeof(PROGRESSBAR_CFG)，同时将fMask设置为PB_CFG_ALL，才可以得到正确的参数值。调用MakeProgressRect函数，最终输出时，m_rc[0]为已完成的进度矩形 。调用SetBrushColor、FillRoundRect和DrawRoundRect来绘制的
矩形。处的叠加过程，实际上在调用MakeProgressRect函数的时候，就已经完成了。因为MakeProgressRect函数的第二个参数的作用是，使输出m_rc的矩形位置和大小限定在控件的范围中。关于MakeProgressRect函数的具体说明，请参考《emXGUI
API编程手册》的章节：位置及区域操作运算API。

最后，将GUI_DEMO_Progressbar加入到GUI_AppMain中，见代码清单 10‑11。

代码清单 10‑11 GUI_AppMain函数（文件GUI_AppMain.c）

1 void GUI_AppMain(void)

2 {

3 while(1)

4 {

5 GUI_DEMO_Hello();

6 GUI_DEMO_Button();

7 GUI_DEMO_Checkbox();

8 GUI_DEMO_Radiobox();

9 GUI_DEMO_Textbox();

10 GUI_DEMO_Progressbar();

11

12 }

13 }

.. _实验现象-5:

实验现象
^^^^

实验结果，如图 10‑4所示。最左边的是PROGBAR1，是在progressbar_owner_draw函数绘制的进度条。PROGBAR2和PROGBAR3是系统自带的进度条，它们的增长方式相反，同时我们还通过WM_CTLCOLOR消息改变了PROGBAR3的外观颜色。

|docx044|

图 10‑4 实验结果

对话框控件
-----

对话框一般情况下，用于确认信息。最简单的对话框是\ `警告 <https://baike.baidu.com/item/%E8%AD%A6%E5%91%8A/33211>`__\ ，当我们关闭窗口时，为了确认用户是有意或无意的关闭动作，会弹出一个对话框进行简单的确认，如图
11‑1，弹出对话框，是否需要进行文档的保存。

|docx045|

图 11‑1 对话框

创建对话框控件
~~~~~~~

.. _标准消息类型及参数说明-6:

标准消息类型及参数说明
^^^^^^^^^^^

本章使用的消息类型常用的有WM_CREATE、WM_NOTIFY。WM_CREATE消息用于创建控件； WM_NOTIFY消息用来处理按钮消息。还有一个新的消息类型：WM_DESTROY。

我们常常在EXIT按键的WM_NOTIFY中调用PostCloseMessage来关闭窗口。当PostCloseMessage产生 WM_CLOSE 消息时，这时用户还可以"选择"是否真正要关闭窗口，如果是，则调用DestroyWindow函数。DestroyWindows函数会再产生
WM_DESTROY消息。当收到WM_DESTROY时，说明窗口已经执行"注销"并结束了，在WM_DESTROY消息中可以做一些资源释放的操作。

对话框配置结构体
^^^^^^^^

emXGUI可以通过配置__MSGBOXOPTIONS结构体，来改变对话框内部的控件，如按键的个数，文字等，结构体__MSGBOXOPTIONS，见代码清单 11‑1。

代码清单 11‑1 对话框配置结构体__MSGBOXOPTIONS

1 typedef struct \__MSGBOXOPTIONS

2 {

3 const WCHAR \**pButtonText; //按键文字

4 int ButtonCount; //按键个数

5 u32 Flag; //消息框的图标

6 }MSGBOX_OPTIONS;

1) pButtonText：存放按键显示文字，有几个按键，就需要几个字符串。

2) ButtonCount：对话框内按键的个数。

3) Flag：消息框的标志位。用来控制消息框的图标以及按钮宽度。可以是

显示 "出错" 图标（MB_ICONERROR）、"询问" 图标（MB_ICONQUESTION）、"警告" 图标（MB_ICONWARNING）和"信息"
图标（MB_ICONINFORMATION）。按钮宽度可以通过MB_BTN_WIDTH来设置，也可以由系统自动设置按钮宽度（MB_BTN_AUTOSIZE）。

创建对话框控件函数
^^^^^^^^^

emXGUI调用MessageBox函数创建对话框控件，同时会返回一个int类型的数据，用户可以通过该返回值，来确认对话框的哪一个按钮被按下。见代码清单 11‑2

代码清单 11‑2创建对话框控件函数MessageBox

1 int MessageBox(HWND hwndParent,int x,int y,int w,int h,

2 const WCHAR \*pText,const WCHAR \*pCaption,

3 const MSGBOX_OPTIONS \*opt);

1. hwndParent：对话框所属的父窗口。控件不可以脱离窗口而存在，通过该成员来指定该控件是属于哪一个父窗口。

2. x， y，w，h：分别是对话框的起点坐标（x，y）以及对话框的宽w，高h。

3. pText：对话框显示的内容，使用宽字符型字符串。

4. pCaption：对话框的标题，同样使用宽字符型字符串。

5. opt：对话框配置结构体。调用MessageBox函数创建对话框时，作为参数，来配置对话框的布局。

创建对话框控件实验
~~~~~~~~~

.. _设计要求-6:

设计要求
^^^^

图 11‑2是本章的设计要求。解释一下：这里的三个对话框，是分别对于三个按钮，且只有按下按钮，对话框才会出现。为了节约篇幅，所以将三个对话框，放在一张图片中。通过点击对话框内的按钮，会返回相应的值，例程中只实现了将返回值输出到串口。

|docx046|

图 11‑2 设计要求

.. _代码分析-6:

代码分析
^^^^

(1) 创建父窗口

代码清单 11‑3 GUI_DEMO_Messagebox函数（文件GUI_DEMO_Messagebox.c）

1 void GUI_DEMO_Messagebox(void)

2 {

3 HWND hwnd;

4 WNDCLASS wcex;

5 MSG msg;

6 //

7 wcex.Tag = WNDCLASS_TAG;

8 wcex.Style = CS_HREDRAW \| CS_VREDRAW;

9 wcex.lpfnWndProc = WinProc; //设置主窗口消息处理的回调函数.

10 wcex.cbClsExtra = 0;

11 wcex.cbWndExtra = 0;

12 wcex.hInstance = NULL;//hInst;

13 wcex.hIcon = NULL;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);

14 wcex.hCursor = NULL;//LoadCursor(NULL, IDC_ARROW);

15 //创建主窗口

16 hwnd =CreateWindowEx( NULL,

17 &wcex,

18 \_T("GUI_DEMO-Messagebox"),

19 WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,

20 10,20,440,240,

21 NULL,NULL,NULL,NULL);

22 //显示主窗口

23 ShowWindow(hwnd,SW_SHOW);

24 //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。

25 while(GetMessage(&msg,hwnd))

26 {

27 TranslateMessage(&msg);

28 DispatchMessage(&msg);

29 }

30 }

创建父窗口，标题栏为“GUI Demo - Messagebox”，带有大小边框，设置WinProc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

代码清单 11‑4 WM_CREATE消息响应（文件GUI_DEMO_Messagebox.c）

1 case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口

2 {

3 GetClientRect(hwnd,&rc); //获得窗口的客户区矩形

4 CreateWindow(BUTTON,L"OK",WS_VISIBLE,

5 rc.w-80,8,68,32,hwnd,ID_OK,NULL,NULL);

6 rc.x =20;

7 rc.y =30;

8 rc.w =100;

9 rc.h =40;

10 //创建按钮

11 CreateWindow(BUTTON,L"Msgbox-1",WS_VISIBLE,

12 rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN1,NULL,NULL);

13 //往下移动矩形位置(X轴增加rc.w+10个像素)

14 OffsetRect(&rc,rc.w+10,0);

15 CreateWindow(BUTTON,L"Msgbox-2",WS_VISIBLE,

16 rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN2,NULL,NULL);

17 OffsetRect(&rc,rc.w+10,0);

18 CreateWindow(BUTTON,L"Msgbox-3",WS_VISIBLE,

19 rc.x,rc.y,rc.w,rc.h,hwnd,ID_BTN3,NULL,NULL);

20 return TRUE;

21 }

代码清单 11‑4中，创建了四个按钮。点击BTN1、BTN2和BTN3按钮，会弹出相应的对话框。OK按钮用来关闭父窗口。

2. WM_DESTROY

代码清单 11‑5 WM_DESTROY消息响应（文件GUI_DEMO_Messagebox.c）

1 case WM_DESTROY: //窗口销毁时，会自动产生该消息，在这里做一些资源释放的操作.

2 {

3 return PostQuitMessage(hwnd); //调用PostQuitMessage，使用主窗口结束并退出消息循环.

4 }

调用PostQuitMessage，使用主窗口结束并退出消息循环。具体说明，可以参考《emXGUI API编程手册》的章节：标准消息类型及参数说明。

3. WM_NOTIFY

代码清单 11‑6 WM_NOTIFY消息响应（文件GUI_DEMO_Messagebox.c）

1 //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,高16位为通知码;lParam指向了一个NMHDR结构体.

2 case WM_NOTIFY:

3 {

4 u16 code,id;

5 int ret=0;

6 code =HIWORD(wParam); //获得通知码类型.

7 id =LOWORD(wParam); //获得产生该消息的控件ID.

8 if(id==ID_OK && code==BN_CLICKED)

9 {

10 PostCloseMessage(hwnd); //产生WM_CLOSE消息关闭窗口

11 }

12 if(id==ID_BTN1 && code==BN_CLICKED)

13 {

14 ret=MessageBox(hwnd,10,20,200,120,L"Hello!",L"MsgBox-1",NULL);

15 }

16 if(id==ID_BTN2 && code==BN_CLICKED)

17 {

18 const WCHAR \*btn[] ={L"YES",L"NO",}; //对话框内按钮的文字

19 MSGBOX_OPTIONS mb;

20 mb.Flag =MB_BTN_WIDTH(80)|MB_ICONWARNING; //按钮的宽度为80px,使用警告图标

21 mb.pButtonText =btn;

22 mb.ButtonCount=2; //对话框内创建两个按钮

23 ret=MessageBox(hwnd,10,20,320,150,

24 L"MB_YESNO + MB_ICON\r\nABCDEFG",L"MsgBox-2",&mb);

25 }

26 if(id==ID_BTN3 && code==BN_CLICKED)

27 {

28 const WCHAR \*btn[] ={L"Yes to all",L"取消",L"确认>>"};

29 MSGBOX_OPTIONS mb;

30 mb.Flag =MB_ICONINFORMATION; //使用信息图标

31 mb.pButtonText =btn;

32 mb.ButtonCount=3;

33 ret=MessageBox(hwnd,10,20,360,180,

34 L"Auto size + MB_ICON\r\nMulti-Line",L"MsgBox-3",&mb);

35 }

36 GUI_Printf("Messagebox Return:%d\r\n",ret);

37 break;

38 }

利用HIWORD和LOWORD函数来获取控件的ID和通知码。对于BTN2，定义了一个MSGBOX_OPTIONS类型的变量mb，使用警告图标，对话框内创建两个按钮，宽度为80px，显示的文字为“YES”和“NO”。我们点击其中一个按钮，MessageBox函数会有返回值，存放在ret中。这个值就是按
钮对应的文字下标，如点击YSE，会返回0；点击NO，则会返回1

BTN3使用信息图标，对话框内有三个按钮，显示的文字为“YES to all”、“取消”和“确认”，最后把ret的值打印到串口。

这样窗口就设计完成了，将GUI_DEMO_Messagebox函数加入到GUI_AppMain中，见代码清单 11‑7

代码清单 11‑7 GUI_AppMain函数（文件GUI_AppMain.c）

1 void GUI_AppMain(void)

2 {

3 while(1)

4 {

5 GUI_DEMO_Button();

6 GUI_DEMO_Checkbox();

7 GUI_DEMO_Radiobox();

8 GUI_DEMO_Textbox();

9 GUI_DEMO_Progressbar();

10 GUI_DEMO_Messagebox();

11 }

12 }

.. _实验现象-6:

实验现象
^^^^

如图 11‑3，我们点击Msgbox-2按钮，此时，会弹出Msgbox-2的对话框。点击YSE的的时候，串口会输出0，见图 11‑4。

|docx047|

图 11‑3 实验结果

|docx048|

图 11‑4串口输出结果

滚动条控件
-----

在我们使用WINDOWS的软件的时候，右侧有一个条，用于翻页，他就是滚动条，如图 12‑1，由滚动滑块和滚动箭头组成。滚动条可以用于滚动列表框或任何其他类型的窗口。滚动条的方向确定用户操作滚动条时滚动的方向。水平滚动条只允许用户向左或向右滚动窗口的内容，垂直滚动条允许用户向上或向下滚动内容。

|docx049|

图 12‑1滚动条

创建滚动条
~~~~~

.. _标准消息类型及参数说明-7:

标准消息类型及参数说明
^^^^^^^^^^^

本章使用的消息类型有：WM_CREATE、WM_NOTIFY、WM_CTLCOLOR和WM_DRAWITEM。这些消息的参数及作用，前面已经解释得很详细了。这里只讲解一下，WM_NOTIFY在滚动条中的用法。

WM_NOTIFY的wParam低16位存放着发送该消息的控件ID，lParam参数是以NMHDR结构体开头，实际为 NM_SCROLLBAR扩展结构，里面附带了更多的信息，见代码清单
12‑1。一般采用NMHDR结构体的code来判断是否发生单击事件，是的话则通过NM_SCROLLBAR的cmd成员判断用户单击的位置。

代码清单 12‑1 滚动条通知命令（文件emXGUI.h）

1 #define SB_TRACK (0) //点击滑块

2 #define SB_ARROWUP (1) //单击上箭头

3 #define SB_ARROWDOWN (2) //单击上箭头

4 #define SB_PAGEUP (3) //单击滚动条的上半部分（空白区域）

5 #define SB_PAGEDOWN (4) //单击滚动条的下半部分（空白区域）

6

7 #define SB_ARROWLEFT (5) //单击左箭头

8 #define SB_ARROWRIGHT (6) //单击右箭头

9 #define SB_PAGELEFT (7) //单击滚动条的左半部分（空白区域）

10 #define SB_PAGERIGHT (8) //单击滚动条的右半部分（空白区域）

以水平滚动条为例，见图 12‑2，讲解一下上面的命令。

|docx050|

图 12‑2 滚动条命令

代码清单 12‑1中的SB_ARROWLEFT及SB_ARROWRIGHT就是图 12‑2中的最左端和最右端的箭头。而SB_PAGELEFT对应的是图 12‑2中处，SB_PAGERIGHT对应的是图 12‑2中处。

滚动条配置结构体
^^^^^^^^

创建滚动条之后，需要发送SBM_SETSCROLLINFO消息，来配置滚动条的参数，这些参数都存放在SCROLLINFO结构体中，见代码清单 12‑2。

代码清单 12‑2 SCROLLINFO结构体（文件emXGUI.h）

1 typedef struct tagSCROLLINFO

2 {

3 u16 cbSize; //SCROLLINFO结构体大小

4 u16 fMask; //功能选择位

5 s32 nMin; //最小值

6 s32 nMax; //最大值

7 s32 nValue; //当前值

8 u16 TrackSize; //滑块大小

9 u16 ArrowSize; //箭头框的大小

10 }SCROLLINFO,SCROLLBAR_CFG;

1) cbSize：用来存放结构体的大小。必须要将cbSize值设置成 sizeof(SCROLLINFO)。

2) fMask：功能选择位。只有相应的 MASK 位置1，才会更新到滚动条控件的内部数据结构体。

3) nMin、nMax、nValue：滚动条的最小值，最大值和当前值。

4) TrackSize：滑块的大小。对于水平滚动条，这里指的是滑块的宽度，而垂直滚动条，则是滑块的高度。

5) ArrowSize：箭头框的大小。对于水平滚动条，指的是箭头框的水平宽度，高度就是控件的客户区高度。对于垂直滚动条，是箭头框"的垂直高度，宽度就是控件的客户区宽度。

以水平滚动条为例，如图 12‑3。

|docx051|

图 12‑3 SCROLLINFO结构体

创建滚动条控件函数
^^^^^^^^^

代码清单 12‑3创建窗口函数（文件emXGUI.h）

1 HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,

2 U32 dwStyle, int x, int y, int nWidth, int nHeight,

3 HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);

1) lpClass：窗口类。对于系统标准控件，可以为：BUTTON(常规按钮，复选框，单选框，组合框)，SCROLLBAR(水平/垂直滚动条)， LISTBOX(列表框)。TEXTBOX（文本框）…等等。这里选择SCROLLBAR。

2) dwStyle：滚动条的风格。参数SBS_VERT代表垂直风格类型。参数SBS_HORZ表示水平风格类型。SBS_LEFT_ALIGN表示左对齐增长方式，如果向左增长方式，往左移动滑块，数值就是增大，往右就减小。SBS_RIGHT_ALIGN表示右对齐增长方式。滚动条控件支持窗口风格参数。

至于其他的参数，也是同样的用法，这里不作描述。我们创建控件调用的CreateWindow函数，实际上就是CreateWindowEx函数

创建滚动条控件实验
~~~~~~~~~

.. _设计要求-7:

设计要求
^^^^

设计一个窗口，如图 12‑4所示。有三个滚动条，分别是垂直风格，自绘制外观风格、水平风格（从左往右，从上到下）。

|docx052|

图 12‑4 设计要求

.. _代码分析-7:

代码分析
^^^^

(1) 创建父窗口

代码清单 12‑4GUI_DEMO\_ Scrollbar函数（文件GUI_DEMO\_ Scrollbar.c）

1 void GUI_DEMO_Scrollbar(void)

2 {

3 HWND hwnd;

4 WNDCLASS wcex;

5 MSG msg;

6 wcex.Tag = WNDCLASS_TAG;

7 wcex.Style = CS_HREDRAW \| CS_VREDRAW;

8 wcex.lpfnWndProc = win_proc;

9 wcex.cbClsExtra = 0;

10 wcex.cbWndExtra = 0;

11 wcex.hInstance = 0;//hInst;

12 wcex.hIcon = 0;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);

13 wcex.hCursor = 0;//LoadCursor(NULL, IDC_ARROW);

14 hwnd =CreateWindowEx( NULL,

15 &wcex,

16 \_T("GUI Demo - Scrollbar"),

17 /*WS_MEMSURFACE|*/WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,

18 0,0,GUI_XSIZE,GUI_YSIZE,

19 NULL,NULL,NULL,NULL);

20 ShowWindow(hwnd,SW_SHOW);

21 while(GetMessage(&msg,hwnd))

22 {

23 TranslateMessage(&msg);

24 DispatchMessage(&msg);

25 }

26 }

创建父窗口，标题栏为“GUI Demo - Scrollbar”，带有大小边框，设置WinProc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

代码清单 12‑5 WM_CREATE消息响应（文件GUI_DEMO\_ Scrollbar.c）

1 case WM_CREATE:

2 {

3 GetClientRect(hwnd,&rc);

4 if(1)

5 {

6 //滚动条参数结构体

7 SCROLLINFO sif;

8 sif.cbSize =sizeof(sif);//结构体大小

9 sif.fMask =SIF_ALL; //使能所有功能

10 //取值范围：-50~50

11 sif.nMin =-50;

12 sif.nMax =+50;

13 //当前值为0

14 sif.nValue =0;

15 //滑块的大小为60

16 sif.TrackSize =60;

17 //两端的大小为60

18 sif.ArrowSize =60;

19 //创建垂直风格滑动条

20 wnd = CreateWindow(SCROLLBAR,L"VScroll",SBS_VERT|WS_VISIBLE,

21 40,20,40,400,hwnd,ID_SCROLLBAR1,NULL,NULL);

22 //配置滑动条的属性

23 SendMessage(wnd,SBM_SETSCROLLINFO,TRUE,(LPARAM)&sif);

24 //创建自绘制滑动条

25 wnd = CreateWindow(SCROLLBAR,L"HScroll",WS_OWNERDRAW|WS_VISIBLE,

26 130,120,400,40,hwnd,ID_SCROLLBAR2,NULL,NULL);

27 SendMessage(wnd,SBM_SETSCROLLINFO,TRUE,(LPARAM)&sif);

28 //创建滑动条

29 wnd = CreateWindow(SCROLLBAR,L"HScroll",WS_VISIBLE,

30 130,240,400,40,hwnd,ID_SCROLLBAR3,NULL,NULL);

31 SendMessage(wnd,SBM_SETSCROLLINFO,TRUE,(LPARAM)&sif);

32 }

33 return TRUE;

34 }

设置滚动条的取值范围在-50~50，滑块的大小为60px，初始位置位于0处，箭头框的大小为60px。调用CreateWindow函数来创建滚动条。创建完成后，发送消息SBM_SETSCROLLINFO来设置滚动条的属性。这里创建了三个滚动条，分别是SCROLLBAR1、SCROLLBAR2和SCRO
LLBAR3。

2. WM_CTLCOLOR

代码清单 12‑6 WM_CTLCOLOR消息响应（文件GUI_DEMO\_ Scrollbar.c）

1 case WM_CTLCOLOR:

2 {

3 u16 id;

4 id =LOWORD(wParam);

5 if(id== ID_SCROLLBAR3)

6 {

7 CTLCOLOR \*cr;

8 cr =(CTLCOLOR*)lParam;

9 cr->TextColor =RGB888(100,255,255);

10 cr->BackColor =RGB888(100,100,150);

11 cr->BorderColor =RGB888(50,50,150);

12 cr->ForeColor =RGB888(50,150,250);

13 return TRUE;

14 }

15 else

16 {

17 return FALSE;

18 }

19

20 }

在WM_CTLCOLOR中，对SCROLLBAR3滚动条的外观颜色进行更改，并返回TRUE。其余两个滚动条按照系统默认方案来配置。

3. WM_DRAWITEM

代码清单 12‑7 WM_DRAWITEM消息响应（文件GUI_DEMO\_ Scrollbar.c）

1 case WM_DRAWITEM:

2 {

3 DRAWITEM_HDR \*ds;

4 ds =(DRAWITEM_HDR*)lParam;

5 {

6 scrollbar_owner_draw(ds);

7 return TRUE;

8 }

9 }

滚动条控件SCROLLBAR2拥有自定义绘制属性WS_OWNERDRAW，在绘制前都会给父窗口发送WM_DRAWITEM消息。在WM_DRAWITEM消息中，调用函数scrollbar_owner_draw实现控件自定义，最后返回TURE。

代码清单 12‑8 scrollbar_owner_draw函数（文件GUI_DEMO\_ Scrollbar.c）

1 static void scrollbar_owner_draw(DRAWITEM_HDR \*ds)

2 {

3 HWND hwnd;

4 HDC hdc;

5 RECT rc;

6 WCHAR wbuf[128];

7 SCROLLINFO sif;

8 hwnd =ds->hwnd;

9 hdc =ds->hDC;

10 //绘制滚动条的背景（第一步）

11 SetBrushColor(hdc,MapRGB(hdc,150,200,250));

12 FillRect(hdc,&ds->rc);

13 sif.fMask =SIF_ALL;

14 SendMessage(hwnd,SBM_GETSCROLLINFO,0,(LPARAM)&sif);

15 //得到滑块的大小（第二步）

16 SendMessage(hwnd,SBM_GETTRACKRECT,0,(LPARAM)&rc);

17 //滑块被选中

18 if(ds->State & SST_THUMBTRACK)

19 {

20 SetPenColor(hdc,MapRGB(hdc,250,50,50));

21 }

22 else//滑块未被选中

23 {

24 SetPenColor(hdc,MapRGB(hdc,50,50,50));

25 }

26 DrawRect(hdc,&rc);

27 //显示滑块的位置

28 x_wsprintf(wbuf,L"%d",sif.nValue);

29

30 DrawText(hdc,wbuf,-1,&rc,DT_VCENTER|DT_CENTER);

31 }

图 12‑4的中滚动条SCROLLBAR2重绘，就是在窗口处绘制两个矩形，一个作为滚动条的背景，另一个则作为滑块。如图 12‑5所示。

|docx053|

图 12‑5滚动条重绘

滚动条的背景重绘，通过调用SetBrushColor函数设置背景颜色，同时使用FillRect函数绘制一个矩形，如图 12‑5的处。

滚动条的滑块重绘，滑块的大小，受到滚动条控件的影响，对于本例程，不可以超过控件的高度。发送SBM_GETSCROLLINFO消息来获得滚动条的配置信息，在发送消息之前，需要将成员fMask的值设置为SIF_ALL，否则的话，获取的内容不完整。通过发送SBM_GETTRACKRECT消息来获得滑块的大
小，这里指的是创建滚动条时，配置的TrackSize参数，保存到rc中。判断滑块当前的状态，设置滑块边框的颜色，调用DrawRect来绘制边框，同时将滑块的当前显示出来，得到图 12‑5的处。

由于图 12‑5的处是处进行绘制，受到滚动条控件的位置以及大小的影响，所以绘制完成后，就可以得到的滚动条。图 12‑5拆开，只是为了方便读者理解。

这样窗口就设计完成了，将GUI_DEMO_Scrollbar函数加入到GUI_AppMain中，见代码清单 11‑7

代码清单 12‑9 GUI_AppMain函数（文件GUI_AppMain.c）

1 void GUI_AppMain(void)

2 {

3 while(1)

4 {

5 GUI_DEMO_Button();//需要修改教程

6 GUI_DEMO_Checkbox();

7 GUI_DEMO_Radiobox();

8 GUI_DEMO_Textbox();

9 GUI_DEMO_Progressbar();//有瑕疵

10 GUI_DEMO_Scrollbar();

11 }

12 }

实验结果
^^^^

实验结果如图 12‑6，单击SCROLLBAR1和SCROLLBAR2，会在串口输出单击的位置。当我们移动滑块SCROLLBAR2时，滑块的数字会发送改变，默认是右增长模式。

|docx054|

图 12‑6 实验结果

列表框控件
-----

列表框（ListBox）用于提供多个选项，用户可以选择其中一个或者多个条目，但是不能直接编辑列表框的数据。如图 13‑1。

|docx055|

图 13‑1 列表框

创建列表框
~~~~~

.. _标准消息类型及参数说明-8:

标准消息类型及参数说明
^^^^^^^^^^^

这里使用的消息类型有：WM_CREATE、WM_NOTIFY、WM_CTLCOLOR、WM_DRAWITEM和WM_PAINT。这些消息使用方法都是大同小异，重点说明一下消息WM_NOTIFY。

WM_NOTIFY消息的参数lParam是指向一个NMHDR结构体数据头的地址指针，其成员code存放的是控件发送的事件，可以是列表项被选中（LBN_SELCHANGE），列表项被单击（LBN_CLICKED），成员idFrom表示消息来自于哪个控件，为控件的ID值。

列表框命令说明
^^^^^^^

列表框没有类似进度条的配置结构体，配置列表框，获取列表框的参数，都是通过发送相应的命令来实现的。下面我们看一下，每一个列表框命令的作用。

表格 13‑1 列表框命令

================ ========== ========================== ============================
命令             参数lParam 参数wParam                 具体说明
================ ========== ========================== ============================
LB_ADDSTRING     列表项编号 显示的字符串               设置列表项的内容
LB_INSERTSTRING  列表项编号 显示的字符串               在某个位置插入列表项
LB_DELETESTRING  列表项编号 无                         删除某个位置的列表项
LB_RESETCONTENT  无         无                         清除所有列表项的内容
LB_SETCURSEL     列表项编号 无                         选中某个列表项
LB_GETCURSEL     无         无                         获取当前选中项
LB_GETTEXT       列表项编号 存放的地址，通常使用数组。 获取列表项的显示内容
LB_GETTEXTLEN    列表项编号 无                         得到列表项的内容长度
LB_GETCOUNT      列表项编号 无                         得到列表框中的项目数
LB_SETPOS        无         偏移值                     设置列表框的偏移位置
LB_GETPOS        无         无                         得到列表框的偏移值
LB_GETTOPINDEX   无         无                         获取列表框中当前第一项的编号
LB_GETITEMRECT   列表项编号 无                         得到列表项的位置，大小
LB_GETITEMDATA   列表项编号 无                         得到列表项的附加值
LB_SETITEMDATA   列表项编号 附加值                     设置列表项的附加值
LB_SETITEMHEIGHT 列表项编号 高度值                     设置列表项的高度值
LB_GETITEMHEIGHT 列表项编号 无                         获取列表项的高度值
================ ========== ========================== ============================

注意，列表项编号值都是从零开始，每个列表框的编号都是相互独立，如图 13‑2。

|docx056|

图 13‑2 列表项编号

List1，List2都是列表框，item后面的括号代表的是编号值，两个列表框的项目编号都是独立开的。编号值可以理解为当前列表项所在的行数（从0开始计数），当用户设置的索引值大于现有的总行数，便会把这个新的item的索引值强制修正到“总行数－１”的值，也就是在最后面的位置。

|docx057|

图 13‑3 列表行号

图 13‑3，我们要在原有的列表框中，加入新的item，他的行数为10，此时的总行数为7（算上新来的），emXGUI则会将行数修改为“7-1”，使item7插入到列表框的最后面。

创建列表框控件函数
^^^^^^^^^

代码清单 13‑1 创建列表框控件函数（文件emXGUI.h）

1 HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,

2 U32 dwStyle, int x, int y, int nWidth, int nHeight,

3 HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);

1) lpClass：窗口类。列表项控件，这里选择LISTBOX。

2) dwStyle：列表框的风格。列表框控件支持窗口风格参数，还可以使用以下参数：产生额外的通知码（LBS_NOTIFY）、行与行之间有分界线（LBS_LINE） 和没有可选择项（LBS_NOSEL）。

至于其他的参数，也是同样的用法，这里不作描述。我们创建控件调用的CreateWindow函数，实际上就是CreateWindowEx函数。

创建列表框控件实验
~~~~~~~~~

.. _设计要求-8:

设计要求
^^^^

设计一个窗口，包括三个列表框：List1、List2以及List3。其中List2是采用自定义重绘的控件，List1和List2是系统自带的控件。

|docx058|

图 13‑4 设计要求

.. _代码分析-8:

代码分析
^^^^

(1) 创建父窗口

代码清单 13‑2 GUI_DEMO_Listbox函数（GUI_DEMO_Listbox.c）

1 void GUI_DEMO_Listbox(void)

2 {

3 HWND hwnd;

4 WNDCLASS wcex;

5 MSG msg;

6

7 InvalidateRect(GetDesktopWindow(),NULL,TRUE);

8

9 wcex.Tag = WNDCLASS_TAG;

10 wcex.Style = CS_HREDRAW \| CS_VREDRAW;

11 wcex.lpfnWndProc = win_proc;

12 wcex.cbClsExtra = 0;

13 wcex.cbWndExtra = 0;

14 wcex.hInstance = 0;//hInst;

15 wcex.hIcon = 0;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);

16 wcex.hCursor = 0;//LoadCursor(NULL, IDC_ARROW);

17 hwnd =CreateWindowEx( NULL,

18 &wcex,

19 \_T("GUI Demo - Listbox"),

20 WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,

21 0,0,GUI_XSIZE,GUI_YSIZE,

22 NULL,NULL,NULL,NULL);

23 ShowWindow(hwnd,SW_SHOW);

24 while(GetMessage(&msg,hwnd))

25 {

26 TranslateMessage(&msg);

27 DispatchMessage(&msg);

28 }

29

30 }

创建父窗口，标题栏为“GUI Demo - Listbox”，带有大小边框，设置winProc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

代码清单 13‑3 WM_CREATE消息响应 （文件GUI_DEMO_Listbox.c）

1 case WM_CREATE:

2 {

3 //创建自绘制列表框LISTBOX1

4 wnd=CreateWindow(LISTBOX,_T("Listbox"),WS_OWNERDRAW|LBS_LINE|LBS_NOTIFY|WS_VISIBLE,

5 8,120,160,200,hwnd,ID_LISTBOX1,NULL,NULL);

6 //设置列表项的内容

7 SendMessage(wnd,LB_ADDSTRING,0,(LPARAM)L" ");

8 SendMessage(wnd,LB_ADDSTRING,1,(LPARAM)L" ");

9 SendMessage(wnd,LB_ADDSTRING,2,(LPARAM)L"Item-1-2");

10 SendMessage(wnd,LB_ADDSTRING,3,(LPARAM)L"Item-1-3");

11 SendMessage(wnd,LB_ADDSTRING,4,(LPARAM)L"Item-1-4");

12 SendMessage(wnd,LB_ADDSTRING,5,(LPARAM)L"Item-1-5");

13 SendMessage(wnd,LB_ADDSTRING,6,(LPARAM)L"Item-1-6");

14 SendMessage(wnd,LB_ADDSTRING,7,(LPARAM)L"Item-1-7");

15 SendMessage(wnd,LB_ADDSTRING,8,(LPARAM)L"Item-1-8");

16 SendMessage(wnd,LB_ADDSTRING,9,(LPARAM)L"Item-1-9");

17 SendMessage(wnd,LB_ADDSTRING,10,(LPARAM)L"Item-1-10");

18 //设置LISTBOX1中的列表项行高

19 for(int i = 0; i < 11; i++)

20 SendMessage(wnd,LB_SETITEMHEIGHT,i,40);

21 //创建列表框LISTBOX2

22 wnd=CreateWindow(LISTBOX,_T("Listbox2"),LBS_LINE|WS_BORDER|WS_VISIBLE,

23 200,8,100,160,hwnd,ID_LISTBOX2,NULL,NULL);

24 //设置列表项的内容

25 SendMessage(wnd,LB_ADDSTRING,0,(LPARAM)L"Item-2-0");

26 SendMessage(wnd,LB_ADDSTRING,1,(LPARAM)L"Item-2-1");

27 SendMessage(wnd,LB_ADDSTRING,2,(LPARAM)L"Item-2-2");

28 SendMessage(wnd,LB_ADDSTRING,3,(LPARAM)L"Item-2-3");

29 SendMessage(wnd,LB_ADDSTRING,4,(LPARAM)L"Item-2-4");

30 SendMessage(wnd,LB_ADDSTRING,5,(LPARAM)L"Item-2-5");

31 SendMessage(wnd,LB_ADDSTRING,6,(LPARAM)L"Item-2-6");

32 SendMessage(wnd,LB_ADDSTRING,7,(LPARAM)L"Item-2-7");

33 SendMessage(wnd,LB_ADDSTRING,8,(LPARAM)L"Item-2-8");

34

35 //创建列表框LISTBOX3

36 wnd=CreateWindow(LISTBOX,_T("Listbox3"),LBS_LINE|WS_BORDER|WS_VISIBLE,

37 8,8,160,100,hwnd,ID_LISTBOX3,NULL,NULL);

38 //设置列表项的内容

39 SendMessage(wnd,LB_ADDSTRING,0,(LPARAM)L"Item-3-0");

40 SendMessage(wnd,LB_ADDSTRING,1,(LPARAM)L"Item-3-1");

41 SendMessage(wnd,LB_ADDSTRING,2,(LPARAM)L"Item-3-2");

42 SendMessage(wnd,LB_ADDSTRING,3,(LPARAM)L"Item-3-3");

43 SendMessage(wnd,LB_ADDSTRING,4,(LPARAM)L"Item-3-4");

44 SendMessage(wnd,LB_ADDSTRING,5,(LPARAM)L"Item-3-5");

45 SendMessage(wnd,LB_ADDSTRING,6,(LPARAM)L"Item-3-6");

46 SendMessage(wnd,LB_ADDSTRING,7,(LPARAM)L"Item-3-7");

47 SendMessage(wnd,LB_ADDSTRING,8,(LPARAM)L"Item-3-8");

48

49 return TRUE;

50 }

创建三个列表框：List1由用户自定义绘制的控件，且可以额外的通知码（LBN_SELCHANGE、LBN_KILLFOCUS和LBN_SETFOCUS），List2和List3是标准控件。发送消息LB_ADDSTRING来设置列表项的内容。发送消息LB_SETITEMHEIGHT来设置LISTBOX
1列表项的高度。List1这里创建了两个显示空白字符的列表项，是为了实现透明效果的，具体见WM_DRAWITEM消息。

2. WM_CTLCOLOR

代码清单 13‑4 WM_CTLCOLOR消息响应（文件GUI_DEMO_Listbox.c）

1 case WM_CTLCOLOR:

2 {

3 u16 id;

4 id =LOWORD(wParam);

5 //修改ID_LISTBOX3的颜色

6 if(id== ID_LISTBOX3)

7 {

8 CTLCOLOR \*cr;

9 cr =(CTLCOLOR*)lParam;

10 cr->TextColor =RGB888(255,255,255);//文字颜色

11 cr->BackColor =RGB888(0,0,0);//背景颜色

12 cr->BorderColor =RGB888(50,150,50);//边框颜色

13 cr->ForeColor =RGB888(0,50,0);//选中框颜色

14 return TRUE;

15 }

16 else

17 {

18 return FALSE;

19 }

20 }

LISTBOX3控件在绘制前，会发送WM_CTLCOLOR到父窗口，通过WM_CTLCOLOR消息来改变控件的颜色值，返回TRUE，否则，系统将忽略本次操作，继续使用默认的颜色进行绘制。

3. WM_DRAWITEM

代码清单 13‑5 WM_DRAWITEM消息响应（文件GUI_DEMO_Listbox.c）

1 case WM_DRAWITEM:

2 {

3 DRAWITEM_HDR \*ds;

4 ds =(DRAWITEM_HDR*)lParam;

5

6 if(wParam==ID_LISTBOX1)

7 {

8 \_listbox_owner_draw_x(ds);

9 return TRUE;

10 }

11 return FALSE;

12 }

WM_DRAWITEM消息里面负责对List Box1实现重绘。调用函数_listbox_owner_draw_x，来实现，见代码清单 13‑6。

代码清单 13‑6 \_listbox_owner_draw_x函数（文件GUI_DEMO_Listbox.c）

1 static void \_listbox_owner_draw_x(DRAWITEM_HDR \*ds)

2 {

3 HWND hwnd;

4 HDC hdc,hdc0,hdc1;

5 HDC hdc_mem;

6 RECT rc;

7 int x,y,w,h;

8

9 hwnd =ds->hwnd;

10 hdc =ds->hDC;

11

12 //创建三个一样大小的DC,把listbox分别绘制进去，但颜色参数不同的.

13 hdc_mem = CreateMemoryDC(SURF_SCREEN,ds->rc.w,ds->rc.h); //透明图层

14 hdc0 =CreateMemoryDC(SURF_SCREEN,ds->rc.w,ds->rc.h); //缩小图层

15 hdc1 =CreateMemoryDC(SURF_SCREEN,ds->rc.w,ds->rc.h); //放大图层

16

17 //绘制与窗口背景颜色一样的矩形（实现透明）

18 SetBrushColor(hdc_mem,MapRGB(hdc_mem,207,212,215));

19 FillRect(hdc_mem,&ds->rc);

20

21 //一个listbox绘到hdc0中

22 \_draw_listbox(hdc0,hwnd,RGB888(100,149,237),RGB888(250,0,0),hDefaultFont);

23 //

24 //一个listbox绘到hdc1中（图片的第三部分）

25 \_draw_listbox(hdc1,hwnd,RGB888(0,0,0),RGB888(250,0,0),hZoomFont);

26

27 //获取列表框中的第二行的高度

28 SendMessage(hwnd,LB_GETITEMRECT,2,(LPARAM)&rc);

29 /第一步/

30 //将透明部分从hdc_mem里复制出来.

31 x =0;

32 y =0;

33 w =rc_m.w;

34 h =rc.y;

35 BitBlt(hdc,x,y,w,h,hdc_mem,x,y,SRCCOPY);

36 /第二步/

37 //将缩小部分从hdc0里复制出来.

38 x = 0;

39 y = rc.y;

40 w = rc_m.w;

41 h = rc_m.y - rc.y;

42 BitBlt(hdc,x,y,w,h,hdc0,x,y,SRCCOPY);

43 /第三步/

44 //中间矩形部分从hdc1里复制出来.

45 BitBlt(hdc,rc_m.x,rc_m.y,rc_m.w,rc_m.h,hdc1,rc_m.x,rc_m.y,SRCCOPY);

46 /第四步/

47 //下面的矩形部分从hdc0里复制出来.

48 x =0;

49 y =rc_m.y+rc_m.h;

50 w =rc_m.w;

51 h =ds->rc.h-(rc_m.y+rc_m.h);

52 BitBlt(hdc,x,y,w,h,hdc0,x,y,SRCCOPY);

53 //释放内存

54 DeleteDC(hdc0);

55 DeleteDC(hdc1);

56 DeleteDC(hdc_mem);

57 }

下面我们重点讲解这个函数，只有学会这个函数里面的操作，未来才有可能在emXGUI中“为所欲为”。

在PS里面，有一个叫做图层的概念。简单地说，每一个图层都是一张独立的图像，每个图层依次取图像的一部分内容，将这些内容按顺序叠加起来，便可以看到完整的图像，参考图 13‑5。

|docx059|

图 13‑5 合成流程

当列表项经过白色区域时，颜色会改变，且它的字体会变大，而其他的列表项字体颜色和大小不发生改变。

处：画个和背景颜色一样的图层，来实现透明的效果；

、处：绘制一个红色背景的矩形区域，在矩形的高度的1/4处绘制一个白色区域（选择框），采用淡蓝色的小字体来显示列表项内容。

处：绘制一个与处一模一样的内容，在列表项内容显示的格式上，采用黑色的大字体。

依次取上述~处的内容，则可以合成最后的图画，以上就是理论部分的实现。在emXGUI中，内存型DC就相当于我们所说的图层，调用CreateMemoryDC函数来创建图层，见代码清单 13‑7。

代码清单 13‑7 CreateMemoryDC（emXGUI。h）

1 HDC CreateMemoryDC(SURF_FORMAT Format,int nWidth,int nHeight);

1) Format：颜色的格式，可以是屏幕颜色一致（SURF_SCREEN）、ARGB4444格式（SURF_ARGB4444）、ARGB8888格式（SURF_ARGB8888）。使用的时候，不需要修改底层驱动。

2) nWidth、nHeight：创建DC的大小。创建内存型DC，实际上就是在我们的内存中开辟一块区域，用来绘制图形的。这块区域的起始位置一定是（0，0），我们只需要负责定义这块区域的大小即可。

切记，在使用后，需要使用DeleteDC，来释放掉内存型DC。

在代码清单 13‑6中，创建了三个内存型DC，分别对应了图 13‑5的图片（从左到右）。

调用_draw_listbox函数来绘制列表框的外观，包括矩形区域，白色选择框以及字体，见代码清单 13‑8。

代码清单 13‑8 \_draw_listbox函数（文件GUI_DEMO_Listbox.c）

1 static void \_draw_listbox(HDC hdc,HWND hwnd,COLOR_RGB32 text_c,COLOR_RGB32 back_c,HFONT hFont)

2 {

3 RECT rc,rc_cli;

4 int i,count;

5 WCHAR wbuf[128];

6 GetClientRect(hwnd,&rc_cli);

7

8 SetBrushColor(hdc,MapRGB888(hdc,back_c));

9 FillRect(hdc,&rc_cli);

10

11 //定义一个中间的矩形．

12 rc_m.w =rc_cli.w;

13 rc_m.h =40;

14 rc_m.x =0;

15 rc_m.y =(rc_cli.h-rc_m.h)>>1;

16 //中间框绘制到hdc1中．

17 SetBrushColor(hdc,MapRGB(hdc,255,255,255));

18 FillRect(hdc,&rc_m);

19

20 SetFont(hdc,hFont);

21 SetTextColor(hdc,MapRGB888(hdc,text_c));

22

23 i=SendMessage(hwnd,LB_GETTOPINDEX,0,0);

24 count=SendMessage(hwnd,LB_GETCOUNT,0,0);

25 while(i<count)

26 {

27 SendMessage(hwnd,LB_GETITEMRECT,i,(LPARAM)&rc);

28 if(rc.y > rc_cli.h)

29 {

30 break;

31 }

32

33

34 SendMessage(hwnd,LB_GETTEXT,i,(LPARAM)wbuf);

35 DrawText(hdc,wbuf,-1,&rc,DT_SINGLELINE|DT_CENTER|DT_VCENTER);

36

37 i++;

38 }

39 }

\_draw_listbox函数的形参为：窗口的绘图DC，父窗口，文字颜色，背景颜色以及使用的字体。

使用LB_GETTOPINDEX来获取处于当前列表框的第一项，注意，这里的第一项不是我们自己定义的第一项，是列表框滑动后，显示在最开始位置的那一项。

发送LB_GETCOUNT来获取列表框的总行数。如果第一项的值小于总行数，则对第一项及其后面的N项进行重绘。

例程中，通过发送LB_GETITEMRECT来获取每一个列表项的位置以及大小，并在这个区域内，使用DrawText函数来显示文字。

到这里，就完成了放大图层和缩小图层的绘制，也就是图 13‑5的第二幅和第三幅小图。

第一幅小图的实现，是通过调用SetBrushColor函数设置矩形的颜色，与窗口的颜色一致，这里的窗口颜色为RGB(207,212,215)，调用FillRect函数来填充矩形。

以上操作，就将三个图层的内容绘制完毕。至于如何每个图层显示的内容，请看下面讲解。

|docx060|

图 13‑6 合成图的放大版

图 13‑6，是合成图层的放大版。处是item2的x，y坐标。处是选择框的x，y坐标，处的坐标是（0，选择框的y坐标+选择框的高度）。

有了这三个坐标，我们就可以对每一个图层进行切割合成了。在emXGUI中，使用BitBlt函数来实现图像的切割合成，函数的具体使用方法，可以参考《emXGUI API编程手册》章节：绘图API。

对于透明的图层，我们只需要顶部到item处的区域即可，也就是起点为（0，0），高度为item2的y坐标，宽度则为控件的宽度，见代码清单 13‑9。

代码清单 13‑9 切割图像以及合成图像

1 //获取列表框中的第二行的高度

2 SendMessage(hwnd,LB_GETITEMRECT,2,(LPARAM)&rc);

3 /第一步/

4 //将透明部分从hdc_mem里复制出来.

5 x =0;

6 y =0;

7 w =rc_m.w;

8 h =rc.y;

9 BitBlt(hdc,x,y,w,h,hdc_mem,x,y,SRCCOPY);

使用LB_GETITEMRECT消息来获取Item2的位置以及大小。使用BitBlt函数，将透明图层（hdc_mem）的内容，复制到合成图层中（hdc）。这里的w，h限制了截取的大小，是否就相等于切割的过程。将hdc_mem的内容复制到合成图层中，则是合成的过程。请注意，合成图层和透明图像的x，y坐
标需要是一致的，否则就会产生错位，读者可以脑补一下画面。

~之间的区域：起始位置为（item2的x坐标，item2的y坐标），大小为控件的宽度*（白色选择框的y坐标减去item2的y坐标）和处的区域：起始位置为（白色选择框的x坐标, 白色选择框的y坐标），大小为控件的宽度*（控件的高度减去白色选择框的y坐标），就是缩小图层的内容，见代码清单 13‑10。

代码清单 13‑10切割缩小图层以及合成图像

1 /第二步/

2 //将缩小部分从hdc0里复制出来.

3 x = 0;

4 y = rc.y;

5 w = rc_m.w;

6 h = rc_m.y - rc.y;

7 BitBlt(hdc,x,y,w,h,hdc0,x,y,SRCCOPY);

8

9

10 /第四步/

11 //下面的矩形部分从hdc0里复制出来.

12 x =0;

13 y =rc_m.y+rc_m.h;

14 w =rc_m.w;

15 h =ds->rc.h-(rc_m.y+rc_m.h);

16 BitBlt(hdc,x,y,w,h,hdc0,x,y,SRCCOPY);

上述代码将~之间的区域和处的区域提取出来，并赋值到合成图层（hdc）中。

最后，将放大图层的选择框区域提取出来，就可以得到我们的放大图像了，见代码清单 13‑11。

代码清单 13‑11切割放大图层以及合成图像

1 /第三步/

2 //中间矩形部分从hdc1里复制出来.

3 BitBlt(hdc,rc_m.x,rc_m.y,rc_m.w,rc_m.h,hdc1,rc_m.x,rc_m.y,SRCCOPY);

这样窗口就设计完成了，将GUI_DEMO_Listbox函数加入到GUI_AppMain中，见代码清单 13‑12。

代码清单 13‑12 GUI_AppMain函数（文件GUI_AppMain.c）

1 void GUI_AppMain(void)

2 {

3 while(1)

4 {

5 GUI_DEMO_Button();

6 GUI_DEMO_Checkbox();

7 GUI_DEMO_Radiobox();

8 GUI_DEMO_Textbox();

9 GUI_DEMO_Progressbar();

10 GUI_DEMO_Scrollbar();

11 GUI_DEMO_Listbox();

12 }

13 }

.. _实验结果-1:

实验结果
^^^^

|docx061|

图 13‑7 实验结果

实验结果如图 13‑7，窗口设计与设计要求基本相同。滑动红色的列表框，跳过的列表项会在上方显示。这是我们自定义绘制的列表框。左上方和右边的列表框为系统自带的控件。用户点击某个项目，则会选择某个项目。

添加示例应用
------

添加滑动窗口界面
--------

emXGUI扩展功能移植
------------

**注意！！！！！！**

**本章教程里介绍的代码都是针对旧版的，新版本配套的说明后续会持续更新。**

**目前霸道开发板使用的emXGUI例程改进了不少，但大体的原理还是和旧版类似的，所以本部分内容保留，阅读源码的时候使用新版代码即可。**

在\ **错误!未找到引用源。**\ 中已经完成了emXGUI基本功能的移植，已经可以用它来做绝大部分的应用了，但在制作显示图片、中文字体等应用时，需要用到文件系统，对内存空间消耗较大的应用需要扩展外部SRAM，这些在windows不需要操心的事情，在嵌入式平台上都需要我们亲自去完善。

添加文件系统
~~~~~~

实验描述及工程文件清单
^^^^^^^^^^^

实验描述
''''

emXGUI有文件系统的支持后，可以显示SD卡内的图片、文件数据，以及使用SD卡内的字库文件。在这个小节我们在emXGUI_touch工程上添加fatfs文件系统，具体操作其实只是把以前移植到STM32平台的文件添加到这个工程中，非常简单。

硬件连接
''''

需要为板子接上液晶屏，液晶屏与板子的连接原理图见\ **错误!未找到引用源。**\ ，给板子接入FAT格式的SD卡(支持32G以下的SD卡)。

主要工程文件
''''''

================== ============================================
   **工程名称**    **emXGUI_fatfs**
**emXGUI库文件**   **STemXGUI522/\ STemXGUI522_CM3_Keil.lib**

                   **STemXGUI522/GUIConf.c**

                   **STemXGUI522/LCDConf_FlexColor_Template.c**

                   **STemXGUI522/\ GUI_X.c**

                   **STemXGUI522/\ GUI_X_Touch_Analog.c** **用户编写的文件** **USER/\ main.c**

                   **USER/\ stm32f10x_it.c**

                   **USER/bsp_led.c**

                   **USER/\ bsp_ili9341_lcd.c**

                   **USER/bsp_usart1.c**

                   **USER/\ bsp_SysTick.c**

                   **USER/bsp_touch.c**

                   **USER/bsp_gpio_spi.c**

                   **USER/bsp_sdio_sdcard.c** **GUI应用文件**    Demo/\ **GUIDEMO_Touch.c**

                   Demo/\ **GUIDEMO_Fatfs.c** **ST固件库**       所有ST3.5版本标准库文件 **文件系统**       **ff9/diskio.c**

                   **ff9/ff.c**

                   **ff9/ccbcs.c** ================== ============================================

配置工程环境
''''''

以\ **错误!未找到引用源。**\ 中的例程为基础，我们往该工程目录中添加fatfs文件系统相关的库文件，这些文件可以从野火STM32-ISO的例程中找到，具体fatfs移植的教程在《STM32库开发实战指南》中已有讲解。有点小区别的是，在本工程中我们使用的bsp_sdio_sdcard.c驱动是
ST官方的5.0.1版本，这个版本相对于以前使用的4.5.0版本要稳定一点，图 16‑1。

|docx062|

图 16‑1 emXGUI_fatfs工程目录

测试文件系统
^^^^^^

添加了fatfs相关的bsp_sdio_sdcard.c、diskio.c、ff.c及ccbcs.c文件后，要注意在stm32f10x_it.c文件中添加sd相关的中断服务函数，见代码清单 16‑1。

代码清单 16‑1要添加到stm32f10x_it.c文件的中断服务函数

1

2 /\*

3 \* 函数名：SDIO_IRQHandler

4 \* 描述 ：在SDIO_ITConfig(）这个函数开启了sdio中断 ，

5 \* 数据传输结束时产生中断

6 \* 输入 ：无

7 \* 输出 ：无

8 \*/

9 void SDIO_IRQHandler(void)

10 {

11 /\* Process All SDIO Interrupt Sources \*/

12 SD_ProcessIRQSrc();

13 }

14

15

16 void SD_SDIO_DMA_IRQHANDLER(void)

17 {

18 /\* Process DMA2 Stream3 or DMA2 Stream6 Interrupt Sources \*/

19 SD_ProcessDMAIRQ();

20 }

21

完成了以上的步骤，就可以编写测试程序了，本工程的main文件内容见代码清单 16‑2。

代码清单 16‑2emXGUI_fatfs工程的main文件

1

2 #include "stm32f10x.h"

3 #include "bsp_led.h"

4 #include "GUI.h"

5 #include "diskio.h"

6 #include "bsp_touch.h"

7 #include "bsp_SysTick.h"

8 #include "bsp_usart1.h"

9 #include "bsp_sdio_sdcard.h"

10

11

12 extern void Touch_MainTask(void);

13 extern void Fatfs_MainTask(void);

14

15 /*\*

16 \* @brief 主函数

17 \* @param 无

18 \* @retval 无

19 \*/

20 int main(void)

21 {

22 /\* LED 端口初始化 \*/

23 LED_GPIO_Config();

24

25 /\* 初始化触屏 \*/

26 Touch_Init();

27

28 /\* 初始化定时器 \*/

29 SysTick_Init();

30

31 /*初始化sd卡*/

32 disk_initialize(0);

33

34 /*CRC和emXGUI没有关系，只是他们为了库的保护而做的，

35 这样STemXGUI的库只能用在ST的芯片上面，别的芯片是无法使用的。 \*/

36 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

37

38 /\* 初始化GUI \*/

39 GUI_Init();

40

41 /\* 初始化串口*/

42 USART1_Config();

43

44 DEBUG("\r\n wildfire ISO board emXGUI test \\r\n");

45

46 GUI_Delay (20);

47

48 #if 0

49 /\* 触摸校准demo \*/

50 Touch_MainTask();

51 #else

52 Fatfs_MainTask();

53 #endif

54

55 }

56

57

58 /END OF FILE/

59

在emXGUI_touch工程的基础上，初始化了各种外设用emXGUI后，在第32行添加了disk_initialize函数用于初始化SD卡及文件系统，在第52行，调用了自己编写的文件系统测试函数Fatfs_MainTask，其内容见代码清单 16‑3。

代码清单 16‑3Fatfs_MainTask函数内容

1 /*\*

2 \\*

3 \* @file GUIDEMO_Fatfs.c

4 \* @author fire

5 \* @version V1.0

6 \* @date 2013-xx-xx

7 \* @brief 测试文件系统

8 \\*

9 \* @attention

10 \*

11 \* 实验平台:野火 iSO STM32 开发板

12 \* 论坛 :http://www.chuxue123.com

13 \* 淘宝 :http://firestm32.taobao.com

14 \*

15 \\*

16 \*/

17

18 #include "stm32f10x.h"

19 #include "bsp_sdio_sdcard.h"

20 #include "bsp_usart1.h"

21 #include "ff.h"

22 #include "GUI.h"

23

24 FIL fnew; /\* file objects \*/

25 FATFS fs; /\* Work area (file system object) for logical drives \*/

26 FRESULT res;

27 UINT br, bw; /\* File R/W count \*/

28 BYTE buffer[4096]= {0}; /\* file copy buffer \*/

29 BYTE textFileBuffer[] = "Welcome to use Wildfire iso stm32 Development Board today is a good day";

30

31 void Fatfs_MainTask(void)

32 {

33 /\* 用于显示文件内容的窗口大小 \*/

34 GUI_RECT file_content= {5,120,235,200};

35

36 /\* 给屏幕刷上背景颜色 \*/

37 GUI_ClearRect(0,0,240,320);

38

39 /\* 设置字体颜色 \*/

40 GUI_SetFont(&GUI_Font8x16);

41

42 GUI_DispStringAt ("f_mount...",5,20);

43

44 /\* Register work area for each volume

45 (Always succeeds regardless of disk status) \*/

46 f_mount(0,&fs);

47

48 /\* function disk_initialize() has been called in f_open \*/

49

50 GUI_DispStringAt ("f_open :newfile.txt ...",5,40);

51

52 /\* Create new file on the drive 0 \*/

53 res = f_open(&fnew, "0:newfile.txt", FA_CREATE_ALWAYS \| FA_WRITE );

54

55 if ( res == FR_OK )

56 {

57 res = f_write(&fnew, textFileBuffer, sizeof(textFileBuffer), &bw);

58 f_close(&fnew);

59 }

60

61 GUI_DispStringAt ("f_read :newfile.txt ...",5,60);

62

63 res = f_open(&fnew, "0:newfile.txt", FA_OPEN_EXISTING \| FA_READ);

64 res = f_read(&fnew, buffer, sizeof(buffer), &br);

65

66 printf("\r\n %s ", buffer);

67

68 GUI_DispStringAt ("file content:",5,100);

69

70 /\* 设置前景颜色（字体颜色）*/

71 GUI_SetColor(GUI_RED);

72

73 /\* 设置字体 \*/

74 GUI_SetFont(GUI_FONT_COMIC18B_ASCII);

75

76 /\* 显示文本到屏幕上 \*/

77 GUI_DispStringInRectWrap((const char*)buffer, &file_content,GUI_TA_LEFT,GUI_WRAPMODE_WORD) ;

78

79 /\* Close open files \*/

80 f_close(&fnew);

81

82 /\* Unregister work area prior to discard it \*/

83 f_mount(0, NULL);

84

85 while (1);

86 }

87

88

89

90

本函数先在sd卡中创建一个空白的txt文件，并向txt文件写入句子“Welcome to use Wildfire iso stm32 Development Board today is a good
day”，关闭文件后重新打开，读取文件的内容，并把读到的内容使用emXGUI的库函数显示到液晶屏上。

实验步骤及现象
^^^^^^^

实验步骤
''''

直接把程序下载到STM32-ISO板子上，注意要给板子插入一张格式为FAT的SD卡(支持32G以下的SD卡)。

.. _实验现象-7:

实验现象
''''

液晶屏上显示出文件系统调用的函数流程f_mount、f_open、f_read等，在最后以红色字体显示从文件中读取到的文件内容，见图 16‑2。

|docx063|

图 16‑2emXGUI_fatfs实验截图

使用外部SRAM
~~~~~~~~

.. _实验描述及工程文件清单-1:

实验描述及工程文件清单
^^^^^^^^^^^

.. _实验描述-1:

实验描述
''''

复杂的emXGUI应用场合对RAM空间消耗较大，而片上RAM空间的资源非常紧张，这时我们就会用到外部扩展的SRAM芯片了，当STM32平台上使用外部SRAM时，对emXGUI也需要进行一些配置。

.. _硬件连接-1:

硬件连接
''''

为板子接上液晶屏，液晶屏与板子的连接原理图见\ **错误!未找到引用源。**\ ，给板子接入FAT格式的SD卡(支持32G以下的SD卡)，还需要接入配套的SRAM模块，野火使用的外部SRAM芯片型号为IS62WV51216BLL，其大小为1MB。野火外部SRAM模块实物见\
**错误!未找到引用源。**\ 。它与STM32芯片的连接见图 16‑3。

|docx064|

图 16‑3 SRAM模块原理图

.. _主要工程文件-1:

主要工程文件
''''''

================== ============================================
   **工程名称**    **emXGUI_sram**
**emXGUI库文件**   **STemXGUI522/\ STemXGUI522_CM3_Keil.lib**

                   **STemXGUI522/GUIConf.c**

                   **STemXGUI522/LCDConf_FlexColor_Template.c**

                   **STemXGUI522/\ GUI_X.c**

                   **STemXGUI522/\ GUI_X_Touch_Analog.c** **用户编写的文件** **USER/\ main.c**

                   **USER/\ stm32f10x_it.c**

                   **USER/bsp_led.c**

                   **USER/\ bsp_ili9341_lcd.c**

                   **USER/bsp_usart1.c**

                   **USER/\ bsp_SysTick.c**

                   **USER/bsp_touch.c**

                   **USER/bsp_gpio_spi.c**

                   **USER/bsp_sdio_sdcard.c**

                   **USER/\ bsp_fsmc_sram.c** **GUI应用文件**    Demo/\ **GUIDEMO_Touch.c**

                   Demo/\ **GUIDEMO_Fatfs.c** **ST固件库**       所有ST3.5版本标准库文件 **文件系统**       **ff9/diskio.c**

                   **ff9/ff.c**

                   **ff9/ccbcs.c** ================== ============================================

.. _配置工程环境-1:

配置工程环境
''''''

以\ **错误!未找到引用源。**\ 中的例程为基础，我们往该工程目录中添加SRAM的驱动bsp_fsmc_sram.c文件。

初始化外部SRAM
^^^^^^^^^

我们先从emXGUI_sram这个工程的main文件来分析一下，相对于上一个工程，它的改动不大，仅是在第32行添加了对FSMC_SRAM_Init函数的调用，见代码清单 16‑4。

代码清单 16‑4 emXGUI工程的main文件

1 #include "stm32f10x.h"

2 #include "bsp_led.h"

3 #include "GUI.h"

4 #include "diskio.h"

5 #include "bsp_touch.h"

6 #include "bsp_SysTick.h"

7 #include "bsp_usart1.h"

8 #include "bsp_sdio_sdcard.h"

9 #include "bsp_fsmc_sram.h"

10

11

12 extern void Touch_MainTask(void);

13 extern void Fatfs_MainTask(void);

14

15 /*\*

16 \* @brief 主函数

17 \* @param 无

18 \* @retval 无

19 \*/

20 int main(void)

21 {

22 /\* LED 端口初始化 \*/

23 LED_GPIO_Config();

24

25 /\* 初始化触屏 \*/

26 Touch_Init();

27

28 /\* 初始化定时器 \*/

29 SysTick_Init();

30

31 /\* 配置 FSMC Bank1 NOR/SRAM3 \*/

32 FSMC_SRAM_Init();

33

34 /*初始化sd卡*/

35 disk_initialize(0);

36

37 /*CRC和emXGUI没有关系，只是他们为了库的保护而做的，

38 这样STemXGUI的库只能用在ST的芯片上面，别的芯片是无法使用的。 \*/

39 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

40

41 /\* 初始化GUI \*/

42 GUI_Init();

43

44 /\* 初始化串口*/

45 USART1_Config();

46

47 DEBUG("\r\n wildfire ISO board emXGUI test \\r\n");

48

49 GUI_Delay (20);

50

51 #if 0

52 /\* 触摸校准demo \*/

53 Touch_MainTask();

54 #else

55 Fatfs_MainTask();

56 #endif

57

58 }

59

60

61 /END OF FILE/

由于SRAM也是使用FSMC外设驱动的，所以它的初始化和液晶屏的很类似，主要过程是对使用到的的GPIO引脚初始化、配置FSMC的使用模式，在这里不对SRAM的初始化函数FSMC_SRAM_Init详细讲解。

给emXGUI分配外部SRAM空间
^^^^^^^^^^^^^^^^^

本章的重点在于给emXGUI分配外部SRAM空间，关于emXGUI 的内存空间配置，都会于GUIConf.c文件中，在不使用外部SRAM时，我们也需要配置该文件，前面章节已有介绍，在本工程中，该文件内容见代码清单 16‑5。

代码清单 16‑5 emXGUI_sram工程的GUIConf.c文件内容

1 #include "GUI.h"

2 #include "bsp_fsmc_sram.h"

3

4 /\*

5 \*

6 \* Defines

7 \*

8 \\*

9 \*/

10 //

11 // Define the available number of bytes available for the GUI

12 //

13 #define GUI_NUMBYTES 1024*53 //modify by fire 原值为 0x200000

14

15 #define GUI_BLOCKSIZE 0x80

16 /\*

17 \*

18 \* Public code

19 \*

20 \\*

21 \*/

22 /\*

23 \*

24 \* GUI_X_Config

25 \*

26 \* Purpose:

27 \* Called during the initialization process in order to set up the

28 \* available memory for the GUI.

29 \*/

30 void GUI_X_Config(void)

31 {

32 #if 0

33 //

34 // 32 bit aligned memory area

35 //

36 static U32 aMemory[GUI_NUMBYTES / 4];

37 //

38 // Assign memory to emXGUI

39 //

40 GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES);

41

42 GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);

43 //

44 // Set default font

45 //

46 GUI_SetDefaultFont(GUI_FONT_6X8);

47 #else

48 //

49 // 32 bit aligned memory area

50 //

51 //

52 // Assign memory to emXGUI

53 //

54 GUI_ALLOC_AssignMemory((U32 \*)Bank1_SRAM3_ADDR, 1024*1024);

55

56 GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);

57 //

58 // Set default font

59 //

60 GUI_SetDefaultFont(GUI_FONT_6X8);

61 #endif

62 }

63

64 /\* End of file \/

65

在本文件中修改的内容为GUI_X_Config函数中调用的GUI_ALLOC_AssignMemory文件的输入参数(请对比第40行及第54行)。我们知道GUI_ALLOC_AssignMemory库函数是用于给emXGUI分配内存空间的，其中第一个输入参数为分配给它的内存空间首地址，第二个参数为内
存空间大小。

原来没有使用外部SRAM的时候，我们定义了一个大小为1024*53字节大小的数组aMemory，并把它作为GUI_ALLOC_AssignMemory函数的输入参数，作为分配给emXGUI。

在使用外部SRAM时，我们把外部SRAM的首地址Bank1_SRAM3_ADDR作为emXGUI内存空间的首地址，大小为1024*1024字节(1MB)，即我们简单粗暴地把整个外部SRAM芯片的空间都分配给了emXGUI使用。其中Bank1_SRAM3_ADDR参数是一个宏，它是一个指向外部SRAM
的首地址，使用原理就和FSMC驱动ILI9341液晶屏一样，宏定义如下：

1 #define Bank1_SRAM3_ADDR ((uint32_t)0x68000000)

完成了emXGUI的内存分配之后，就没有之后了，添加外部SRAM的支持就是这么简单。

.. _实验步骤及现象-1:

实验步骤及现象
^^^^^^^

.. _实验步骤-1:

实验步骤
''''

直接把程序下载到STM32-ISO板子上，注意要给板子插入一张格式为FAT的SD卡(支持32G以下的SD卡)，给STM32-ISO板子接入外部SRAM模块。

.. _实验现象-8:

实验现象
''''

正常的实验现象跟上一个章节一样。液晶屏上显示出文件系统调用的函数流程f_mount、f_open、f_read等，在最后以红色字体显示从文件中读取到的文件内容，见图 16‑2。

|docx063|

图 16‑4emXGUI_fatfs实验截图

野火GUI例程介绍
---------

**注意！！！！！！**

**本章教程里介绍的代码都是针对旧版的，新版本配套的说明后续会持续更新。**

**目前霸道开发板使用的emXGUI例程改进了不少，但大体的原理还是和旧版类似的，所以本部分内容保留，阅读源码的时候使用新版代码即可。**

目前，野火基于STM32-ISO开发板设计完成了一个GUI例程，该例程使用emXGUI模仿PDA界面，它具有浏览图片、阅读文字、发送短信、打电话等多种功能。在本章中，将对该例程的整体框架进行介绍。

野火GUI初体验
~~~~~~~~

为了让读者有更直观的感受，这里先介绍一下野火GUI的使用方法及主要功能。请读者先把野火GUI例程烧录到板子运行体验一下。

.. _实验步骤-2:

实验步骤
^^^^

把野火GUI例程(工程名称为wildfire_gui)下载到STM32-ISO板子上，给STM32-ISO板子接入外部SRAM模块，注意还要给板子插入一张格式为FAT的SD卡(支持32G以下的SD卡)，SD卡内需要事先从电脑中拷贝野火GUI例程目录下的“SD卡备份内容”到SD卡的根目录，见图
17‑1，例程中会使用到SD卡里的字库、图片等内容。

|docx065|

图 17‑1 wildfire_gui例程中的SD卡根目录

实验现象说明
^^^^^^

给板子上电后，会看到第一页桌面，见图 17‑2的左侧。为了方便管理，我们把整个屏幕分为三栏，分别为状态窗口、主窗口、及页面控制窗口。

|docx066|

图 17‑2 野火GUI第一页桌面及页面说明

状态窗口
''''

目前主要包含一个野火Logo及一个实时时钟，点击状态窗口左侧的野火Logo，会弹出野火GUI的版本号，而点击状态窗口右侧的时间文字，则会在主窗口弹出一个时间调整界面，见图 17‑3。后期我们还可以往状态窗口添加手机、蓝牙、GPS等信号。

|docx067|

图 17‑3 野火GUI状态窗口相关操作

控制窗口
''''

在屏幕最底部的是控制窗口，它主要是显示页面索引及返回按键，见图 17‑4，它分别为第一页桌面、第二页桌面及在应用程序界面时的截图，注意控制窗口显示内容的变化：在桌面时，它以较大的圆点来表示当前页数，在应用程序界面时，圆点会被隐藏，而在屏幕的左下角会出现一个返回键，用于关闭当前应用程序。

|docx068|

图 17‑4 野火GUI控制窗口在不同情况显示的状态

主窗口
'''

主窗口是野火GUI的核心显示界面，在桌面状态时，它显示的是各种应用图标，点击图标即可打开相关的应用，而所有应用在运行时均在主窗口显示。由于功能庞杂，这里有些应用的功能还有待开发，有些bug还有待解决，希望有兴趣的读者与我们慢慢完善这些应用，下面我们对它一一介绍。

-  SD卡文件浏览器(Browser)

野火GUI的SD卡文件浏览器应用具有查看SD卡内文件的功能，它以树形图的格式显示SD卡内的文件，如果点击本系统支持的文件格式，它会调用相关应用程序来打开阅读，如jpg、png、bmp、gif、txt等文件，图片会以缩放的形式显示出来，而文本文件则以电子书的格式打开，见图 17‑5。

|docx069|

图 17‑5 野火GUI SD文件浏览器应用界面

需要改善的问题：在emXGUI5.22版本中，官方推出了一个文件浏览器控件，使用该控件可更方便高效地浏览SD卡文件，后期我们会采用它改进文件浏览器。

-  实时时钟应用

点击时钟的应用图标后，会弹出时间调整界面，见图 17‑6。该应用使用STM32的RTC外设记录时间，所以如果给STM32-ISO开发板的电池座接上锂电池，调整了一次时间后，野火GUI的时间在主电源掉电的情况下也会保持正常。如果还没有调整过时间，野火GUI默认从2014年1月1日0时0分0秒开始计时，
在时间调整界面中，有6个分别为年月日时分秒的滚轮，通过上下滑动滚轮选择当前时间，然后点击OK按钮就可以设置时间了。

|docx070|

图 17‑6 野火GUI时钟应用界面

-  温度计应用

野火GUI的温度计应用是实时曲线图形式的，见图 17‑7。在温度曲线界面还可以调节x、y轴量程、暂停、是否使用网格、全屏显示等多种选项。

在野火STM32-ISO板子上，预留了温度传感器的接口，可以接入DHT11及DS18B20传感器，为了适应不同的硬件环境，温度计应用程序在初始化时，会检测硬件环境，根据不同的传感器调用不同的驱动程序。在应用程序窗口的左上角会显示当前使用的传感器。如果板子上两种传感器都没有接入时，则会使用STM32芯
片的片上温度传感器，这时检测的是STM32芯片的温度，一般情况下会比环境温度高。

|docx071|

图 17‑7 野火GUI温度计应用界面

-  图片浏览器

野火GUI的图片浏览器可以显示SD卡内的bmp、jpg、png及gif格式图片，它以缩放居中的形式显示到主窗口中，在主窗口的右下角有两个按钮分别用来控制查看上一张和下一张图片，见图 17‑8。

   |docx072|

图 17‑8 野火GUI图片浏览器

-  文本阅读器

野火GUI文本阅读器，可以用来打开txt等文本文件。点击应用图标后，会弹出SD目录，目录下仅显示txt格式的文件，点选文件即可打开阅读器，见图 17‑9。

   |docx073|

图 17‑9野火GUI文本阅读器

需要改善的问题：阅读器加载文件时一次过把整个文件都加载到SRAM，当文件较大时就会出错，可改为分段读取文本的内容。野火GUI已经移植了中文字库，可显示中文，但文本阅读器应用还没处理中文文本显示。

-  短信应用

给STM32-ISO开发板接入野火的GSM模块后(接入到ISO板子右下角的串口排针上，并把ISO板子左侧的两个跳帽“485R-A3”、“485D-A2”拔掉)，可以与野火GUI配合使用发送短信、拨打电话。野火GSM模块实物见图 17‑10。

|docx074|

图 17‑10野火GSM模块实物

运行野火GUI程序，点击短信及电话应用时它会先检测板子有没有接入GSM模块，如果没有它会弹出提示，见图 17‑11(a)。

接入GSM模块后(并在GSM模块中接入SIM卡)，通过硬件检测，主窗口会显示三个应用图标，分别表示收件箱(In box)、发件箱(Out box)及草稿箱(Draft
box)，点击发件箱，会出现已发信息列表，而列表中的第一栏则为“新建信息”功能，点击它会出现编写信息界面，在对话框中输入号码，短信内容 (点击键盘里的“C/E”、“123”可切换中英文及数字输入)，最后点击界面左下角的“Send”按钮，即可发送短信。见图 17‑11。

|docx075|

图 17‑11野火GUI短信应用：

(a)未接入GSM模块时的提示 (b)功能选择 (c)发件箱 (d)发送短信

需要改善的问题：短信应用里的T9输入法还不够人性化，如还没有实现退格、输入标点等功能，在中英文、数字输入切换时还没有添加提示。

-  电话应用

运行野火GUI中的电话应用也需要给STM32-ISO板子接入野火GSM模块。点击电话应用图标后，会出现电话拨号界面，输入要拨打的电话号码后点击“Call”按键即可拨打电话，然后主窗口会进入通话中的界面，见图 17‑12，在GSM模块中接入耳麦，就可以进行通话了。

|docx076|

图 17‑12 野火GUI电话应用

-  摄像机、地图、计算器应用

主窗口中的摄像机及桌面第二页的地图、计算器等应用没有实现，仅创建了图标，方便以后添加应用，见图 17‑13。

   |docx077|

图 17‑13 野火GUI还没实现的应用

-  关于截图

..

   野火GUI还具有屏幕截图功能，在本教程中的示例图片都是这样得来的。按下STM32-ISO板子上的KEY1按键，程序就会开始截图，同时板子上的LED1会亮，截图完成时，LED1会熄灭，同时屏幕上会弹出一个截图成功的提示，见图
   17‑14。截得的图片都保存在SD卡的：0：WF_OS\Snapshot路径中。

   |docx078|

图 17‑14 野火GUI截图

野火GUI例程框架
~~~~~~~~~

野火GUI例程比较庞大，为引导读者学习使用本例程，在这里向大家介绍该程序的框架。

.. _主要工程文件-2:

主要工程文件
^^^^^^

野火GUI例程是在\ **错误!未找到引用源。**\ 小节中的emXGUI 使用外部SRAM工程的基础上开发的，它包含了触摸、文件系统、及使用外扩SRAM的功能。在它的基础上，我们添加了各种应用，而每个应用都有独立的文件，修改非常方便，其工程文件目录见图 17‑15。
主要添加了bsp文件组、wildfireGUI文件组、PNGlib文件组及t9py文件组，其说明见表 17‑1。

表 17‑1 野火GUI例程主要文件列表

================ ========================= ============================
**工程名称**     **emXGUI_WildfireOS**
**bsp文件组**    **bsp_usart1.c**          串口驱动，调试时使用
\                **bsp_SysTick.c**         Systick驱动，提供系统时钟
\                **bsp_sdio_sdcard.c**     SD卡底层驱动
\                **bsp_led.c**             LED灯驱动
\                **bsp_gpio_spi.c**        触摸屏用到的GPIO模拟SPI驱动
\                **bsp_ili9341_lcd.c**     液晶屏控制器驱动
\                **bsp_touch.c**           触摸屏控制器驱动
\                **bsp_fsmc_sram.c**       外部SRAM驱动
\                **bsp_calendar.c**        万年历算法
\                **bsp_date.c**            日期算法
\                **bsp_rtc.c**             实时时钟驱动
\                **bsp_ov7725.c**          摄像头驱动
\                **bsp_sccb.c**            模拟SCCB总线驱动
\                **bsp_exti.c**            外部中断驱动
\                **bsp_dht11.c**           DHT11温湿度传感器驱动
\                **bsp_Timbase.c**         温湿度传感器提供的定时器驱动
\                **bsp_ds18b20.c**         DS18B20温度传感器
\                **bsp_internal_temp.c**   STM32内部温度传感器驱动
\                **sim900a.c**             GSM模块驱动
\                **bsp_usart2.c**          为GSM模拟提供的usart2驱动
**GUI应用文件**  **GUIDEMO_Touch.c**       emXGUI触摸校准应用
\                **WFGUI_DeskTop.c**       emXGUI桌面控制文件
\                **WFGUI_Icon.c**          EmXGUI图标资源文件
\                **WFGUI_SDView.c**        SD卡文件浏览器应用
\                **WFGUI_TextReader.c**    文件阅读器应用
\                **WFGUI_ImageReader.c**   图片浏览器应用
\                **WFGUI_Time.c**          实时时钟应用
\                **WFGUI_Message.c**       短信应用
\                **WFGUI_Keypad.c**        T9拼音键盘界面程序
\                **WFGUI_Phone.c**         电话应用
\                **WFGUI_Camera.c**        摄像头应用
\                **WFGUI_Snapshot.c**      GUI截屏程序
\                **WFGUI_Temperature.c**   温度计应用
\                **WFGUI_APPLinkedList.c** 应用程序链表程序
\                **WFGUI_UserAPP.c**       提供给用户扩展应用的接口
**t9py文件组**   **t9py.c**                T9拼音输入法主程序
**PNGlib文件组** **PNG.lib**               PNG图片解码库
================ ========================= ============================

|docx079|

图 17‑15 野火GUI程文件目录

初始化板载外设
^^^^^^^

我们先从main文件入手开始分析，main文件中主要包括板子的初始化函数BSP_Init及程序主函数main，见代码清单 17‑1。

代码清单 17‑1野火GUI的main文件

1 /*\*

2 \\*

3 \* @file main.c

4 \* @author fire

5 \* @version V1.0

6 \* @date 2013-xx-xx

7 \* @brief 测试led

8 \\*

9 \* @attention

10 \*

11 \* 实验平台:野火 iSO STM32 开发板

12 \* 论坛 :http://www.chuxue123.com

13 \* 淘宝 :http://firestm32.taobao.com

14 \*

15 \\*

16 \*/

17

18 #include "stm32f10x.h"

19 #include "GUI.h"

20 #include "diskio.h"

21 #include "ff.h"

22

23 #include "bsp_led.h"

24 #include "bsp_touch.h"

25 #include "bsp_SysTick.h"

26 #include "bsp_usart1.h"

27 #include "bsp_sdio_sdcard.h"

28 #include "bsp_fsmc_sram.h"

29 #include "bsp_rtc.h"

30 #include "bsp_exti.h"

31

32 #include "WFGUI_DeskTop.h"

33 #include "WFGUI_Common.h"

34

35 extern void Touch_MainTask(void);

36

37 /*时间结构体*/

38 struct rtc_time systmtime;

39

40

41 void BSP_Init(void)

42 {

43

44 static FATFS fsys;

45

46 /\* LED 端口初始化 \*/

47 LED_GPIO_Config();

48

49 /\* 初始化触屏 \*/

50 Touch_Init();

51

52 /\* 初始化定时器 \*/

53 SysTick_Init();

54

55 /\* 配置 FSMC Bank1 NOR/SRAM3 \*/

56 FSMC_SRAM_Init();

57

58 /*初始化sd卡*/

59 disk_initialize(0);

60

61 f_mount(0,&fsys); //注册文件系统工作区 // TBD 增加sd卡检测

62

63 /*CRC和emXGUI没有关系，只是他们为了库的保护而做的，

64 这样STemXGUI的库只能用在ST的芯片上面，别的芯片是无法使用的。 \*/

65 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

66

67 /\* 初始化GUI \*/

68 GUI_Init();

69

70 /\* 初始化串口*/

71 USART1_Config();

72

73 /\* 配置RTC秒中断优先级 \*/

74 RTC_NVIC_Config();

75

76 RTC_CheckAndConfig(&systmtime);

77

78 EXTI_Key_Config();

79

80 DEBUG("\r\n wildfire ISO board emXGUI test \\r\n");

81

82 }

83

84

85 /*\*

86 \* @brief 主函数

87 \* @param 无

88 \* @retval 无

89 \*/

90 int main(void)

91 {

92

93 BSP_Init();

94

95 GUI_Delay (20);

96

97 #if 0

98 /\* 触摸校准demo \*/

99 Touch_MainTask();

100

101 #else

102

103 WFGUI_MainTask();

104

105 while (1) {

106

107 GUI_Delay(50); //窗口在gui delay期间自动重绘，必须要有gui_delay

108 }

109 #endif

110

111 }

112

113

114 /END OF FILE/

115

我们看到，main函数调用了BSP_Init函数初始化了板子的各种外设，包括LED、液晶触摸屏、Systick时钟、外部SRAM、SD卡、文件系统、GUI、RTC时钟、串口和按键等等，然后就调用了野火GUI的主函数WFGUI_MainTask，野火GUI的所有操作从它开始。

.. _创建桌面-2:

创建桌面
^^^^

WFGUI_MainTask函数的定义位于WFGUI_DeskTop.c文件，它在调用emXGUI库函数WM_MOTION_Enable使能emXGUI的滑动操作后，调用了我们编写的CreatDeskTop函数。在这里提一下如何区分emXGUI库函数和野火编写的函数，如果在程序代码中无法找到函数定义
的，它都是emXGUI的库函数，这是因为emXGUI的库函数都编译成了库文件，无法查看源代码了。

代码清单 17‑2创建桌面

1

2 /*\*

3 \* @brief CreatDeskTop，创建gui桌面

4 \* @param none

5 \* @retval none

6 \*/

7 static void CreatDeskTop(void)

8 {

9

10 /\* 准备建立3个窗口，以下是使用到的用户定义参数，

11 方便在回调函数中使用 \*/

12 WinPara.xSizeLCD = LCD_GetXSize(); //LCD屏幕尺寸

13 WinPara.ySizeLCD = LCD_GetYSize(); //LCD屏幕尺寸

14 WinPara.xSizeWin = WinPara.xSizeLCD; //窗口尺寸

15 WinPara.ySizeWin = WinPara.ySizeLCD -20*2; //窗口尺寸

16 //屏幕大小减去状态栏和控制栏

17 WinPara.xPosWin = 0; //窗口的起始位置

18 WinPara.yPosWin = 20; //窗口的起始位置

19 WinPara.xSizeWinVirtual = WinPara.xSizeWin \* VIRTUAL_WIN_NUM;

20 //虚拟窗口尺寸，用于桌面

21

22 /\* 设置默认皮肤 \*/

23 SetDefaultSkin();

24

25

26 WM_EnableMemdev(WM_HBKWIN);

27

28 /\* 设置背景桌面的回调函数 \*/

29 WM_SetCallback(WM_HBKWIN, \_cbBKWin);

30

31 /\* 创建三个窗口 状态栏、控制栏、主窗口*/

32 CreatStatusWin();

33 CreatCtrlWin();

34 CreatMainWin();

35

36 /\* 初始化app链表 \*/

37 hAPPLinkedList_Init();

38

39

40 }

41

42

43 /\*

44 \*

45 \* Public routines

46 \* 公有函数

47 \*

48 \\*

49 \*/

50

51 /*\*

52 \* @brief WFGUI_MainTask,WFGUI主函数

53 \* @param none

54 \* @retval none

55 \*/

56 void WFGUI_MainTask(void)

57 {

58

59 WM_MOTION_Enable(1);

60 WM_MOTION_SetDefaultPeriod(1000);

61

62 CreatDeskTop(); //创建gui桌面

63

64 while (1) {

65

66 GUI_Delay(50);

67

68 }

69 }

70

初始化窗口大小
'''''''

在CreatDeskTop 函数中，初始化了一个全局结构体变量WinPara，它用于记录屏幕尺寸以及主窗口的位置及大小，通过这些参数，可以推算出状态窗口及控制窗口的大小，见代码清单 17‑3。

代码清单 17‑3 WIN_PARA结构体

1 typedef struct WIN_PARA {

2 //窗口使用到的用户定义参数，方便在回调函数中使用

3 int xSizeLCD, ySizeLCD; //LCD屏幕尺寸

4 int xPosWin, yPosWin; //窗口的起始位置

5 int xSizeWin, ySizeWin; //窗口尺寸

6 int xSizeWinVirtual; //虚拟窗口尺寸

7

8 unsigned char ctr_index; //记录icorn窗口的索引

9 unsigned char isDesktop; //记录桌面窗口是否在最前 0：桌面窗口不在最前

10 1：桌面窗口在最前

11

12 WM_HWIN hWinCtrl; //控制窗口的句柄（底部）

13 WM_HWIN hWinMain; //主显示窗的句柄（中部）

14 WM_HWIN hWinStatus; //状态窗口的句柄（顶部）

15 WM_HWIN hWinTime;

16

17 WM_HWIN hApp[20]; //记录正在运行的App句柄

18

19 } WIN_PARA;

-  xSizeLCD和 ySizeLCD

xSizeLCD和 ySizeLCD参数分别用于记录液晶屏的X、Y方向分辨率。在CreatDeskTop 函数初始化时，是使用库函数LCD_GetXSize、LCD_GetYSize来获取的，而不是直接固定分配240*320，使用库函数来获取屏幕大小有利于应用程序使用不同屏幕的移植。

-  xSizeWin和ySizeWin

xSizeWin和ySizeWin分别用于记录主窗口的X、Y方向的分辨率。按照我们的设计，整个液晶屏分为三个窗口，见图
17‑2，三个窗口在X方向均占满整个屏幕，所以xSizeWin被配置为xSizeLCD的值，即等于屏幕X宽度。而状态窗口及控制窗口的Y方向均为20像素分辨率，要预留位置给这两个窗口，所以主窗口的ySizeWin大小设置为屏幕的Y宽度减去20*2的像素。

-  xPosWin和yPosWin

xPosWin和yPosWin参数用于记录主窗口的原点(即主窗口左上角的位置)。在CreatDeskTop 函数分别对它赋值为0和20，配合上前面xSizeWin及ySizeWin的设置，刚好预留了位置给状态窗口及控制窗口。

-  xSizeWinVirtual

xSizeWinVirtual是指虚拟窗口大小，这个虚拟窗口大小是指野火GUI在桌面显示应用图标时的窗口X方向大小。我们的设计中有两页桌面用于显示应用图标，所以这里设置虚拟窗口尺寸为xSizeWin的2倍(CreatDeskTopk 的VIRTUAL_WIN_NUM宏值为2)。

-  ctr_index和isDesktop

ctr_index和isDesktop都是控制窗口使用到的标志位，ctr_index用于记录桌面的索引，控制窗口的小圆点就是根据这个参数来显示的。isDesktop标志是用来指示当前主窗口显示的是应用界面还是桌面界面，控制窗口通过这个标志来决定显示它的返回键还是圆点索引。

-  hWinctrl、hWinMain、hWinStatus和hWinTime

hWinctrl、hWinMain、hWinStatus和hWinTime都是窗口句柄，emXGUI创建每个窗口后都会有一个独立的句柄(相当于编号)，使用该句柄就可以访问该窗口进行各种操作。这四个分别是控制窗口句柄、主窗口句柄、状态窗口句柄以及时间窗口句柄。其中的时间窗口是指野火GUI运行时显示于屏
幕右上角的时间文字，实时时钟RTC通过这个句柄来访问并修改显示的时间。

-  hApp

在旧的开发版本中我们使用它来记录应用程序的句柄，现在不使用。改为用linux链表记录。

设置控件皮肤及字体
'''''''''

CreatDeskTop设置完各个窗口的大小后，调用了SetDefaultSkin函数设置各种控件的皮肤和SD卡外部字体，SetDefaultSkin函数定义见代码清单 17‑4。

代码清单 17‑4 SetDefaultSkin函数内容

1

2 /*\*

3 \* @brief SetDefaultSkin,设置gui的默认皮肤

4 \*

5 \* @param none

6 \* @retval none

7 \*/

8 static void SetDefaultSkin(void)

9 {

10 /\* 设置各种控件的皮肤为类win7的皮肤 \*/

11 BUTTON_SetDefaultSkin (BUTTON_SKIN_FLEX);

12 CHECKBOX_SetDefaultSkin (CHECKBOX_SKIN_FLEX);

13 DROPDOWN_SetDefaultSkin (DROPDOWN_SKIN_FLEX);

14 FRAMEWIN_SetDefaultSkin (FRAMEWIN_SKIN_FLEX);

15 HEADER_SetDefaultSkin (HEADER_SKIN_FLEX);

16 PROGBAR_SetDefaultSkin (PROGBAR_SKIN_FLEX);

17 RADIO_SetDefaultSkin (RADIO_SKIN_FLEX);

18 SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);

19 SLIDER_SetDefaultSkin (SLIDER_SKIN_FLEX);

20

21 /\* 设置滑动条 \*/

22 SCROLLBAR_SetDefaultWidth(15); //宽度

23 SCROLLBAR_SetThumbSizeMin(10); //滑块最小size

24

25 /\* 创建sd卡外部字体 \*/

26 CreateFont(&SDFont);

27

28 /\* 设置默认字体 \*/

29 TEXT_SetDefaultFont(&SDFont.XFont);

30

31 /\* 设置framwin \*/

32 FRAMEWIN_SetDefaultTitleHeight(20); //标题栏高度

33 FRAMEWIN_SetDefaultFont(GUI_FONT_8X16); //默认字体

34 FRAMEWIN_SetDefaultTextColor(1,GUI_BLACK); //设置激活状态时的标题文字颜色

35 WM_SetDesktopColor(GUI_BLACK);

36 }

在SetDefaultSkin函数中，调用了各种emXGUI控件的皮肤设置函数，它们的作用是把野火GUI里使用到的控件皮肤都设置为Win7风格，这样的控件比较好看。另外，还调用了CreateFont函数初始化外部SD卡字体，emXGUI自带的字体只包含英文字库，当需要显示中文的时候，就需要用到SD卡
里的外部字体库文件。该字体的字库文件保存在SD卡的WF_OS\Font文件夹内，它是由emXGUI提供的字库生成工具生成的。

创建状态窗口
''''''

设置完控件皮肤及字体后，CreatDeskTop函数依次创建了状态窗口、控制窗口以及主窗口，其中创建状态窗口的函数CreatStatusWin定义见代码清单 17‑5。

代码清单 17‑5CreatStatusWin函数内容

1 /*\*

2 \* @brief CreatStatusWin，创建顶部的状态栏

3 \* @param none

4 \* @retval none

5 \*/

6 static void CreatStatusWin(void)

7 {

8 WM_HWIN hText;

9 WM_HWIN hButton;

10

11 WinPara.hWinStatus = WM_CreateWindowAsChild(

12 0, //窗口位置、大小

13 0,

14 WinPara.xSizeLCD,

15 WinPara.yPosWin,

16 WM_HBKWIN, WM_CF_SHOW \| WM_CF_MEMDEV, \_cbStatusWin, sizeof(WIN_PARA \*)

17 );

18

19 /\* 顶部的 "wildfire OS "文本 \*/

20 hText = TEXT_CreateEx(0, 0, WinPara.xSizeWin , 20,

WinPara.hWinStatus, WM_CF_SHOW,

21 GUI_TA_HCENTER|TEXT_CF_VCENTER, GUI_ID_TEXT1, "Wildfire OS");

22 TEXT_SetFont(hText, GUI_FONT_16B_ASCII);

23 TEXT_SetTextColor(hText, 0xFF4040);

24

25 /\* 状态栏的时间显示文本 \*/

26 hText = TEXT_CreateEx(WinPara.xSizeLCD-55,5,55,20,

WinPara.hWinStatus,WM_CF_SHOW,TEXT_CF_LEFT,

27 GUI_ID_TEXT0,"");

28 TEXT_SetBkColor(hText,GUI_INVALID_COLOR);

29 TEXT_SetTextColor(hText,GUI_WHITE);

30 TEXT_SetFont(hText,GUI_FONT_13B_ASCII);

31

32 /\* 野火Logo 按钮 \*/

33 hButton = BUTTON_CreateEx(2,0,40,20,

WinPara.hWinStatus,WM_CF_SHOW,0,GUI_ID_BUTTON0);

34 BUTTON_SetBitmap(hButton,BUTTON_BI_UNPRESSED,&bmWF_Logo);

35 BUTTON_SetBitmap(hButton,BUTTON_BI_PRESSED,&bmWF_LogoPr);

36

37 }

38

在CreatStatusWin中，调用了比较多的emXGUI库函数，而且库函数的输入参数非常多，在这里我们不对细节具体展开，对输入参数有疑问的读者可以在《emXGUI用户手册》搜索相关的库函数说明。首先，调用WM_CreateWindowAsChild库函数，以背景窗口(emXGUI默认具有一个背景
窗口)为父窗口，在屏幕的顶部创建了状态窗口，并指定了状态窗口的回调函数_cbStatusWin，注意WM_CreateWindowAsChild的返回值赋给了全局变量WinPara.hWinStatus，即前面提到记录状态窗口句柄的变量，就是在这个时候初始化的。

紧接着，在创建完状态窗口后，马上在它上面创建了顶部显示“wildfire OS”的文本控件，实时时钟的文本以及野火Logo按钮，在创建这些控件时，由于要设置它所在的父窗口，都使用到了WinPara.hWinStatus句柄来访问状态窗口。

窗口的回调函数是用户定制emXGUI应用的核心，用户通过回调函数来处理各种事件、响应，函数中通过消息ID来 区分不同的事件，方便用户进行处理。状态窗口的回调函数_cbStatusWin见代码清单 17‑6。

代码清单 17‑6_cbStatusWin

1 /*\*

2 \* @brief \_cbStatusWin,状态栏回调函数

3 \* @param none

4 \* @retval none

5 \*/

6 static void \_cbStatusWin(WM_MESSAGE \* pMsg)

7 {

8 char text_buffer[20];

9 WM_HWIN hText;

10 int NCode;

11 int Id;

12

13 switch (pMsg->MsgId) {

14

15 case WM_NOTIFY_PARENT: //通知父窗口

16

17 Id = WM_GetId(pMsg->hWinSrc); // 控件的ID

18 NCode = pMsg->Data.v; // 通知代码

19

20 if (NCode == WM_NOTIFICATION_RELEASED) { //触摸释放消息

21 if (Id == GUI_ID_BUTTON0) { //野火Logo按键

22 /\* 显示消息提示框 \*/

23 MESSAGEBOX_Create("\n\n Wildfire OS 1.0 \\n\n",

   "About",0);

24

25 } else if (Id == GUI_ID_TEXT0) { //时间文本框

26 /\* 执行WFGUI_Time应用 \*/

27 WFGUI_Time();

28 }

29

30 }

31

32

33 break;

34

35

36 case WM_PAINT: //重绘背景

37 GUI_SetColor(GUI_BLACK);

38 GUI_FillRect(0,0,WinPara.xSizeLCD ,WinPara.yPosWin);

39

40 break;

41

42 case MY_MESSAGE_RTC:

43 //处理时间显示的信息，每秒钟修改一次时间

44

45 /\* 获取text句柄 \*/

46 hText = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0);

47

48 /\* 转换rtc值至北京时间 \*/

49 RTC_TimeCovr(&systmtime);

50

51 /\* 转换成字符串 \*/

52 sprintf(text_buffer,"%02d:%02d:%02d",

systmtime.tm_hour,systmtime.tm_min,systmtime.tm_sec);

53

54 /\* 输出时间 \*/

55 TEXT_SetText(hText,text_buffer);

56 break;

57

58

59 default:

60 WM_DefaultProc(pMsg);

61

62 }

63

64 }

65

在这个回调函数中，主要处理了三种消息，分别为WM_PAINT重绘消息，WM_NOTIFY_PARENT 通知父窗口消息以及我们为了RTC时钟自定义的MY_MESSAGE_RTC消息。

-  WM_PAINT消息

WM_PAINT消息是在窗口需要重绘时发送到回调函数的，也就是说，emXGUI机制通知该窗口需要刷新背景了。如果我们不处理这个消息，背景往往会出现各种重叠现象，比较奇怪。

在状态窗口的WM_PAINT消息中，我们调用库函数GUI_FillRect对状态窗口刷上黑色。

-  WM_NOTIFY_PARENT消息

WM_NOTIFY_PARENT消息用于通知父窗口，它的子窗口中发生了某些改变，要处理这个消息一般还需要使用几次switch进行分类，如区分是哪个子窗口的消息，子窗口的哪类消息。

在状态窗口的WM_NOTIFY_PARENT消息中，先判断子窗口消息的种类，由于我们只关注子窗口触摸释放的消息WM_NOTIFICATION_RELEASED，使用了if语句对这些消息进行了筛选。确定为触摸释放消息后，再进一步判断消息是由哪个子窗口发送的，处理时先通过消息结构体中的pMsg->hWi
nSrc获取得到控件的ID，再根据控件ID区分子窗口，如代码中使用if语句区分了GUI_ID_BUTTON0及GUI_ID_TEXT0子窗口，它们分别为状态窗口中的野火Logo按键和时间文本框，它们这ID标签是在前面CreatStatusWin函数创建控件时我们用户给控件分配的。最后，实现了当用用户
点击并释放野火Logo按键控件时，会弹出“Wildfire OS 1.0”提示框，点击并释放时间文本框时，会弹出时间调整应用的界面。

-  MY_MESSAGE_RTC

MY_MESSAGE_RTC消息并不是emXGUI默认的系统消息，而是我们为了让STM32
的RTC驱动通知时间显示控件而定义的，在每次RTC的秒中断触发时，它会向状态窗口发送MY_MESSAGE_RTC消息，而状态窗口接收到该消息后，就在回调函数这里对显示时间的文本进行更新。其中RTC的秒中断函数见代码清单
17‑7，它除了发送消息到状态窗口，在时间应用被激活的时候，还会把该消息发送到时间应用窗口。

代码清单 17‑7 RTC秒中断服务函数

1 /*\*

2 \* @brief This function handles RTC interrupt request.

3 \* @param None

4 \* @retval None

5 \*/

6 void RTC_IRQHandler(void)

7 {

8

9 if (RTC_GetITStatus(RTC_IT_SEC) != RESET) {

10 /\* Clear the RTC Second interrupt \*/

11 RTC_ClearITPendingBit(RTC_IT_SEC);

12

13 /\* Enable time update \*/

14 TimeDisplay = 1;

15

16 /\* 判断窗口是否有效 \*/

17 if (WM_IsWindow(WinPara.hWinStatus)) {

18 /\* 发送 \*/

19 WM_SendMessageNoPara(WinPara.hWinStatus,MY_MESSAGE_RTC);

20 }

21 if (WM_IsWindow(WinPara.hWinTime)) {

22 WM_SendMessageNoPara(WinPara.hWinTime,MY_MESSAGE_RTC);

23 }

24

25 /\* Wait until last write operation on RTC registers has finished \*/

26 RTC_WaitForLastTask();

27 }

28 }

创建控制窗口
''''''

控制窗口的创建跟状态窗口是类似的，其函数CreatCtrlWin内容见代码清单 17‑8。

代码清单 17‑8 CreatCtrWin函数定义

1 /*\*

2 \* @brief CreatCtrlWin，创建底部的控制栏

3 \* @param none

4 \* @retval none

5 \*/

6 static void CreatCtrlWin(void)

7 {

8 WM_HWIN hButtonWin;

9

10

11 WinPara.hWinCtrl = WM_CreateWindowAsChild(

12 0,

13 WinPara.yPosWin +WinPara.ySizeWin , //底部位置

14 WinPara.xSizeLCD,

15 WinPara.ySizeLCD -(WinPara.yPosWin +WinPara.ySizeWin),

16 //底部剩余宽度

17 WM_HBKWIN, WM_CF_SHOW \| WM_CF_MEMDEV, \_cbCtrlWin, sizeof(WIN_PARA \*) );

18

19

20 /\* 创建索引窗口 (以小圆点表示当前的图标页面)*/

21 WM_CreateWindowAsChild( 0,

22 0,

23 WM_GetWindowSizeX(WinPara.hWinCtrl),

24 WM_GetWindowSizeY(WinPara.hWinCtrl),

25 WinPara.hWinCtrl,WM_CF_SHOW,_cbIndexWin,0);

26

27 /\* 创建按键button窗口(该button在应用程序状态下 会显示返回按钮) \*/

28 hButtonWin = WM_CreateWindowAsChild(

0,

29 0,

30 WM_GetWindowSizeX(WinPara.hWinCtrl),

31 WM_GetWindowSizeY(WinPara.hWinCtrl),

32 WinPara.hWinCtrl,WM_CF_SHOW,_cbButtonWin,0);

33 /\* 默认隐藏button窗口 \*/

34 GUI_Delay(10);

35 WM_HideWindow(hButtonWin);

36 GUI_Delay(10);

37

38 }

39

在CreatCtrWin中调用库函数WM_CreateWindowAsChild在屏幕的下文创建一个窗口，作为控制窗口，并设置其回调函数为_cbCtrlWin。接着又在控制窗口中创建了小圆点索引窗口及返回键窗口，并默认隐藏返回键窗口。

这三个窗口都有对应的回调函数，分别为_cbCtrlWin、_cbIndexWin和_cbButtonWin。先来看看_cbCtrlWin的代码，见代码清单 17‑9。

代码清单 17‑9控制窗口回调函数_cbCtrlWin

1

2 /*\*

3 \* @brief \_cbCtrlWin,控制栏回调函数

4 \* @param none

5 \* @retval none

6 \*/

7 static void \_cbCtrlWin(WM_MESSAGE \* pMsg)

8 {

9 WM_HWIN hItem;

10 WM_HWIN hItemNext;

11

12 switch (pMsg->MsgId)

13 {

14

15 case WM_PAINT: //重绘背景

16

17 GUI_SetColor(GUI_BLACK);

18 GUI_FillRect(0,0,WM_GetWindowSizeX(pMsg->hWin),

WM_GetWindowSizeY(pMsg->hWin));

19 break;

20

21 case MY_MESSAGE_CTRLCHANGE:

22 if (hAPPLinkedList_GetAppTop()==NULL)

23 //如果没有app窗口，则控制栏显示桌面索引

24 {

25 hItem = WM_GetFirstChild(WinPara.hWinCtrl);

26 hItemNext = WM_GetNextSibling(hItem);

27

28 /\* 根据回调函数来区分窗口 \*/

29 if (WM_GetCallback(hItem) == \_cbIndexWin && WM_GetCallback(hItemNext) == \_cbButtonWin)

30

31 {

32 /\* 显示index窗口，隐藏button窗口 \*/

33 WM_ShowWindow(hItem);

34 WM_HideWindow(hItemNext);

35 WM_Paint(hItem); //要重绘索引窗口，更新索引

36

37 }

38 else if (WM_GetCallback(hItemNext) == \_cbIndexWin && WM_GetCallback(hItem) ==_cbButtonWin)

39

40 {

41 /\* 显示index窗口，隐藏button窗口 \*/

42 WM_ShowWindow(hItemNext);

43 WM_HideWindow(hItem);

44

45 WM_Paint(hItemNext); //要重绘索引窗口，更新索引

46

47 }

48

49 }

50 else //如果存在app窗口，显示控制按钮索引

51 {

52 hItem = WM_GetFirstChild(WinPara.hWinCtrl);

53 hItemNext = WM_GetNextSibling(hItem);

54

55 /\* 根据回调函数来区分窗口 \*/

56 if (WM_GetCallback(hItem) == \_cbIndexWin && WM_GetCallback(hItemNext) == \_cbButtonWin)

57

58 {

59 /\* 显示button窗口，隐藏index窗口 \*/

60 WM_ShowWindow(hItemNext);

61 WM_HideWindow(hItem);

62 }

63 else if (WM_GetCallback(hItemNext) == \_cbIndexWin && WM_GetCallback(hItem) == \_cbButtonWin)

64

65 {

66 /\* 显示button窗口，隐藏index窗口 \*/

67 WM_ShowWindow(hItem);

68 WM_HideWindow(hItemNext);

69

70 }

71

72

73 }

74

75 break;

76

77

78 default:

79 WM_DefaultProc(pMsg);

80 break;

81

82 }

83

84

85 }

控制窗口的回调函数主要处理了一个我们自宝义的消息MY_MESSAGE_CTRLCHANGE ，每当打开或关闭了应用程序，我们都会给控制窗口发送这个消息。

控制窗口收到该消息后，使用函数hAPPLinkedList_GetAppTop 来查询应用程序链表，如果查得目前没有打开应用(主窗口为桌面)，则在控制窗口显示小圆点索引窗口，如果查得目前有打开应用，则在控制窗口显示返回键窗口。索引窗口及返回键窗口的回调函数见代码清单 17‑10。

代码清单 17‑10索引窗口及返回键窗口的回调函数

1

2 /*\*

3 \* @brief \_cbIndexWin,索引窗口回调函数

4 \* @param none

5 \* @retval none

6 \*/

7 static void \_cbIndexWin(WM_MESSAGE \* pMsg)

8 {

9

10 switch (pMsg->MsgId)

11 {

12 case WM_PAINT: //重绘背景

13

14 GUI_SetColor(GUI_BLACK);

15 GUI_FillRect(0,0,WM_GetWindowSizeX(pMsg->hWin) ,

WM_GetWindowSizeY(pMsg->hWin));

16

17

18 /\* 绘制索引窗口 \*/

19 GUI_SetColor(GUI_LIGHTGRAY);

20

21 {

22 char i,r;

23

24 for (i=0; i<VIRTUAL_WIN_NUM; i++)

25 {

26 if (i == WinPara.ctr_index)

27 r=5; //当前窗口的圆点半径大

28 else

29 r=2; //非当前窗口的圆点半径小

30

31 if (i< VIRTUAL_WIN_NUM/2) //绘制圆点

32 {

33 /\* 绘制索引窗口 \*/

34 GUI_FillCircle(WM_GetWindowSizeX(pMsg->hWin)/2-10*i,

WM_GetWindowSizeY(pMsg-> hWin)/2,r);

35

36 }

37 else

38 {

39 /\* 绘制索引窗口 \*/

40 GUI_FillCircle(WM_GetWindowSizeX(pMsg->hWin)/2+10*i,

WM_GetWindowSizeY(pMsg-> hWin)/2,r);

41

42 }

43 }

44 }

45 break;

46

47

48

49 default:

50 break;

51

52 }

53

54 }

55

56 /*\*

57 \* @brief \_cbButtonWin,控制按钮窗口回调函数

58 \* @param none

59 \* @retval none

60 \*/

61 static void \_cbButtonWin(WM_MESSAGE \* pMsg)

62 {

63 int Id,NCode;

64 WM_HWIN hItem;

65

66 switch (pMsg->MsgId)

67 {

68

69 case WM_PAINT: //重绘窗口

70 GUI_SetColor(GUI_BLACK);

71 GUI_FillRect(0,0,WM_GetWindowSizeX(pMsg->hWin) ,

WM_GetWindowSizeY(pMsg->hWin));

72

73 break;

74

75 case WM_CREATE: //创建窗口

76

77 /*返回键*/

78 hItem = BUTTON_CreateEx(0,0,40, 20,

79 pMsg->hWin, WM_CF_SHOW|WM_CF_MEMDEV , 0, GUI_ID_BUTTON0);

80 BUTTON_SetText(hItem, "<");

81

82

83 break;

84

85

86 case WM_NOTIFY_PARENT: //处理子窗口消息

87 Id = WM_GetId(pMsg->hWinSrc);

88 NCode = pMsg->Data.v;

89

90 if (NCode == WM_NOTIFICATION_RELEASED)

91 {

92 if (Id == GUI_ID_BUTTON0)

93 {

94

95 HANDLE_LIST \*hAPPOnTop;

96

97 /\* 获取最上层的窗口句柄 \*/

98 hAPPOnTop = hAPPLinkedList_GetAppTop();

99 if (hAPPOnTop != NULL)

100 {

101 WM_DeleteWindow(hAPPOnTop->hAPP); // 关闭窗口

102

103 }

104

105

106 }

107 else if (Id == GUI_ID_BUTTON1)

108 //button1可以制作home键，现在没有实现

109 {

110

111 }

112

113 }

114

115 break;

116

117 default:

118 break;

119

120 }

121

122 }

索引窗口在它的重绘消息处理中绘制了大小不同的圆点，它根据全局变量WinPara.ctr_index来绘制半径不同的圆点。而返回窗口的回调函数则在返回键被按下时处理关闭最上层应用程序的操作。

创建主窗口
'''''

最后我们要创建主窗口，见代码清单 17‑11。它调用库函数WM_CreateWindowAsChild创建主窗口并指定其回调函数，接着在主窗口中创建一个图标窗口。

代码清单 17‑11 创建主窗口函数内容

1

2 /*\*

3 \* @brief CreatMainWin，创建主显示窗口

4 \* @param none

5 \* @retval none

6 \*/

7 static void CreatMainWin(void)

8 {

9

10 WinPara.hWinMain = WM_CreateWindowAsChild(

11 WinPara.xPosWin ,

12 WinPara.yPosWin , //位置

13 WinPara.xSizeWin,

14 WinPara.ySizeWin, //底部剩余宽度

15 WM_HBKWIN, WM_CF_SHOW \| WM_CF_MEMDEV, \_cbMainWin, sizeof(WIN_PARA \*)

16 );

17 /\* 创建icon图标窗口 \*/

18 WM_CreateWindowAsChild( 0 ,

19 0 , //位置

20 WinPara.xSizeWin \* VIRTUAL_WIN_NUM,

21 WinPara.ySizeWin, //高

22 WinPara.hWinMain,

23 WM_CF_SHOW \| WM_CF_MEMDEV|WM_CF_MOTION_X,

24 \_cbIconWin,

25 0

26 );

27

28

29

30 }

31

由于主窗口仅仅作为一个相当于背景的媒介，它需要处理的消息并不多，它的回调函数也相对简单，见代码清单 17‑12。

代码清单 17‑12主窗口的回调函数

1

2 /*\*

3 \* @brief \_cbMainWin,主窗口回调函数

4 \* @param none

5 \* @retval none

6 \*/

7 static void \_cbMainWin(WM_MESSAGE \* pMsg)

8 {

9

10 switch (pMsg->MsgId)

11 {

12

13 case WM_NOTIFY_PARENT:

14

15 break;

16

17

18 case MY_MESSAGE_SNAPSHOT: //处理截图消息

19

20 /\* 调用截图应用 \*/

21 WFGUI_Snapshot() ;

22

23 break;

24

25

26 case WM_PAINT: //重绘背景

27 GUI_SetColor(GUI_BLACK);

28 GUI_FillRect(0,0,WinPara.xSizeWin ,WinPara.ySizeWin);

29

30 break;

31

32

33 default:

34 WM_DefaultProc(pMsg);

35

36 }

37

38

39 }

在回调函数中，主要处理的为WM_PAINT重绘消息以及自定义的截图消息MY_MESSAGE_SNAPSHOT，它通过调用函数WFGUI_Snapshot函数保存截图到SD卡。截图消息是由按键中断服务函数发出的，当我们按下开发板的KEY1键时，就会触发截图中断，按键截图中断服务函数见代码清单
17‑13。

代码清单 17‑13 按键截图中断服务函数

1 void EXTI0_IRQHandler(void)

2 {

3

4 if (EXTI_GetITStatus(EXTI_Line0) != RESET) //确保是否产生了EXTI Line中断

5 {

6

7 if (WM_IsWindow(WinPara.hWinMain))

8 {

9 WM_SendMessageNoPara(WinPara.hWinMain ,MY_MESSAGE_SNAPSHOT);

10 }

11

12 EXTI_ClearITPendingBit(EXTI_Line0); //清除中断标志位

13 }

14 }

15

中断服务函数中，调用库函数WM_IsWindow检测窗口是否有效，若主窗口有效，则向它发送截图消息MY_MESSAGE_SNAPSHOT。

接下来我们看主窗口中的图标窗口的回调函数，图标窗口连接着野火GUI的所有应用，它的回调函数内容见代码清单 17‑14。

代码清单 17‑14主窗口的图标控件回调函数

1

2 /*\*

3 \* @brief Icon窗口回调函数

4 \* @param none

5 \* @retval none

6 \*/

7 static void \_cbIconWin(WM_MESSAGE \* pMsg)

8 {

9 WM_HWIN hWin;

10 WM_HWIN hItem;

11 WM_HWIN hParent;

12

13 WM_MOTION_INFO \* pInfo;

14

15 int NCode;

16 int Id;

17 int Sel;

18

19 unsigned char i,j;

20 hParent = pMsg->hWin;

21

22 switch (pMsg->MsgId) {

23

24 case WM_CREATE:

25

26 for (i=0; i<VIRTUAL_WIN_NUM; i++) {

27 /\*

28 \* 创建图标控件

29 \*/

30

31 hWin = ICONVIEW_CreateEx(i*240, 5, WinPara.xSizeWin, WinPara.ySizeWin, hParent, WM_CF_SHOW \| WM_CF_HASTRANS,

32 0, GUI_ID_ICONVIEW0+i, 55, 70);

33

34

35 /\* 设置选定图标的颜色 \*/

36 ICONVIEW_SetBkColor(hWin, ICONVIEW_CI_SEL, GUI_BLUE \| 0xC0000000);

37 /\* 设置图标的字体 \*/

38 ICONVIEW_SetFont(hWin, &GUI_Font13B_ASCII);

39

40 /\* 设置初始选择的图标为 -1 (表示尚未选择)*/

41 ICONVIEW_SetSel(hWin,-1);

42 }

43 /\* 设置当前索引 \*/

44 WinPara.ctr_index = 0;

45 /\* 显示第一个图标页 \*/

46 hWin = WM_GetDialogItem(pMsg->hWin,GUI_ID_ICONVIEW0);

47 /\*

48 \* 添加图标到图标控件

49 \*/

50 for (j = 0 ; j < ICON_PAGE_NUM && j < GUI_COUNTOF(_aBitmapItem); j++) {

51 ICONVIEW_AddBitmapItem(hWin, \_aBitmapItem[j].pBitmap, \_aBitmapItem[j].pText);

52 }

53

54 /\* 显示第二个图标页 \*/

55 hWin = WM_GetDialogItem(pMsg->hWin,GUI_ID_ICONVIEW1);

56

57 /\*

58 \* 添加图标到图标控件

59 \*/

60 for (j = 0 ; j < ICON_PAGE_NUM && j < GUI_COUNTOF(_aBitmapItem2); j++) {

61 ICONVIEW_AddBitmapItem(hWin, \_aBitmapItem2[j].pBitmap, \_aBitmapItem2[j].pText);

62 }

63

64 break;

65

66 case WM_NOTIFY_PARENT:

67

68 Id = WM_GetId(pMsg->hWinSrc); // 控件的ID

69 NCode = pMsg->Data.v; // 通知代码

70

71 switch (Id) {

72

73 case GUI_ID_ICONVIEW0: // 图标控件0

74

75 switch (NCode) {

76 case WM_NOTIFICATION_RELEASED:

77 //case WM_NOTIFICATION_SEL_CHANGED:

78 /\*

79 \* 获取当前选中的图标

80 \*/

81 Sel = ICONVIEW_GetSel(pMsg->hWinSrc);

82

83 switch (Sel) {

84 case 0:

85 GUI_Delay(500); //短暂延时以显示触摸效果

86 ShowTips(pMsg->hWin); //提示让用户等待

87 WFGUI_SDView();

88 break;

89

90 case 1:

91 GUI_Delay(500); //短暂延时以显示触摸效果

92 ShowTips(pMsg->hWin); //提示让用户等待

93 WFGUI_Time();

94 break;

95

96 case 2:

97 GUI_Delay(500);

98 ShowTips(pMsg->hWin); //提示让用户等待

99 WFGUI_Temperature();

100 break;

101

102 case 3:

103 GUI_Delay(500);

104 ShowTips(pMsg->hWin); //提示让用户等待

105 WFGUI_ImageReader();

106

107 break;

108

109 case 4:

110 GUI_Delay(500);

111 ShowTips(pMsg->hWin); //提示让用户等待

112 WFGUI_TextReader();

113 break;

114

115 case 5:

116 GUI_Delay(500); //短暂延时以显示触摸效果

117 ShowTips(pMsg->hWin); //提示让用户等待

118 WFGUI_Message();

119 break;

120

121 case 6:

122 GUI_Delay(500); //短暂延时以显示触摸效果

123 ShowTips(pMsg->hWin); //提示让用户等待

124 WFGUI_Phone();

125 break;

126

127 case 7:

128 GUI_Delay(500);

129 ShowTips(pMsg->hWin); //提示让用户等待

130 WFGUI_Camera();

131 break;

132 default:

133 break;

134 }

135

136 /\* 获取ICON的句柄 \*/

137 hItem = WM_GetDialogItem(hParent, GUI_ID_ICONVIEW0);

138 /\* 设置初始选择的图标为 -1 (表示尚未选择)*/

139 ICONVIEW_SetSel(hItem,-1);

140 break;//WM_NOTIFICATION_RELEASED

141 } //NCODE

142

143 break; //ICONVIEW0

144

145 case GUI_ID_ICONVIEW1: // 图标控件1

146

147 if (NCode == WM_NOTIFICATION_RELEASED) {

148

149 /\*

150 \* 获取当前选中的图标

151 \*/

152 Sel = ICONVIEW_GetSel(pMsg->hWinSrc);

153

154 switch (Sel) {

155 case 0:

156 case 1:

157 case 2:

158 GUI_Delay(500);

159 ShowTips(pMsg->hWin); //提示让用户等待

160 WFGUI_UserAPP();

161 break;

162 default:

163 break;

164 }

165

166 /\* 获取ICON的句柄 \*/

167 hItem = WM_GetDialogItem(hParent, GUI_ID_ICONVIEW1);

168 /\* 设置初始选择的图标为 -1 (表示尚未选择)*/

169 ICONVIEW_SetSel(hItem,-1);

170 }

171 break;

172

173 default:

174 break;

175 } //ID

176

177 break; //NOTIFYPARENT

178

179 case WM_MOTION:

180 pInfo = (WM_MOTION_INFO \*)pMsg->Data.p;

181 if (pInfo) {

182 switch (pInfo->Cmd) {

183 case WM_MOTION_INIT:

184 pInfo->SnapX = 240; //像素对齐

185 pInfo->SnapY = 0;

186 pInfo->Period = 500;

187

188 break;

189

190 case WM_MOTION_MOVE:

191 /\* 禁止图标控件 ，防止误触发*/

192 for (i=0; i<VIRTUAL_WIN_NUM; i++) {

193 hWin = WM_GetDialogItem(pMsg->hWin,GUI_ID_ICONVIEW0+i);

194 WM_DisableWindow(hWin);

195 }

196 break;

197

198 default:

199 break;

200 }

201 /\* 移动结束 \*/

202 if (pInfo->FinalMove) {

203 /\* 移动结束，使能图标控件 \*/

204 for (i=0; i<VIRTUAL_WIN_NUM; i++) {

205 hWin = WM_GetDialogItem(pMsg->hWin,GUI_ID_ICONVIEW0+i);

206 WM_EnableWindow(hWin);

207 }

208 //xpos指向窗口移动的距离，向左移动为负。

209 //一般第一窗口移动结束时xpos=-1

210 if (pInfo->xPos >= -120 && pInfo->xPos ) {

211 WinPara.ctr_index = 0; //第一个窗口

212 WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);

213 //WM_Paint(WinPara.hWinCtrl); //重绘ctrl窗口，刷新index

214

215 } else if (pInfo->xPos < -120) {

//一般第二窗口移动结束时xpos=-239

216 WinPara.ctr_index = 1; //第二个窗口

217 WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);

218 // WM_Paint(WinPara.hWinCtrl); //重绘ctrl窗口，刷新index

219 }

220

221

222 }

223 }

224

225 break;

226

227 case WM_PAINT: //重绘背景

228 GUI_SetColor(GUI_BLACK);

229 GUI_FillRect(0,0,WinPara.xSizeWin \*VIRTUAL_WIN_NUM ,WinPara.ySizeWin);

230 break; //WM_PAINT

231

232 default:

233 WM_DefaultProc(pMsg);

234

235 }

236

237

238 }

239

240

回调函数中主要处理了以下消息：

-  WM_CREATE消息

WM_CREATE消息是在窗口创建时产生的，我们通常在这个消息下初始化窗口。在图标窗口收到这个消息时，我们调用ICONVIEW_CreateEx函数在图标窗口中创建了两个图标控件(Icon
view)，在桌面中显示的两页应用图标就是这种控件。创建了图标控件之后，为每一页图标控件添加应用图标，这些应用图标都是使用emXGUI图片转换工具转换而来的数组，都保存在WFGUI_Icon.c文件中。

-  WM_NOTIFY_PARENT消息

WM_NOTIFY_PARENT消息就是由子窗口发送的通知消息。在本函数中该消息由图标控件产生，在触摸到图标控件中的不同应用图标时，它会返回一个选中的标号，我们就根据该标号来调用不同的应用，如标号0表示SD文件浏览器，标号1表示时间调整应用等。

-  WM_MOTION消息

WM_MOTION消息是在用户的触摸产生手势操作时产生的，如向左滑动、上下滑动等，关于WM_MOTION消息的说明要在《emXGUI5.24用户手册》才能找到，旧的中文版文档还没有它的说明。在本函数的该消息处理中，我们主要处理了屏幕滑动的速度及窗口自动对齐(指每次滑动的像素大小，这里设置为x方向滑动
单位为240(屏幕X的宽度)，即每次移动要么向左移动一屏，要么向右移动一屏)。另外，由于要区分滑动窗口的操作和点击应用图标的操作，在检测到滑动手势时，我们会禁止图标控件，防止在滑动窗口时误触发打开了应用，在窗口滑动结束时，我们再使能图标控件，以接受点选图标的操作。最后，滑动窗口完成时，还对记录页面索
引的全局变量WinPara.ctr_index修改赋值，并向控制窗口发送消息让它处理。

-  WM_PAINT消息

WM_PAINT消息用于通知窗口进行重绘。在本中我们对图标窗口刷上黑色背景。

对于野火GUI中的应用就不在此处一一分析了，读者可从图标控件程序源码中的应用程序主函数开始研究，如果读者需要添加自己的应用，只要在加上应用图标，并在这个回调函数的应用标号处理中添加应用主函数即可。

野火GUI中的应用链表
^^^^^^^^^^^

在野火GUI中，为了管理应用程序，使用了双向链表来记录应用程序的句柄，该链表的源代码由Linux双向链表修改而来。Linux链表是以头文件的形式给出的，都是宏定义，它的链表实现方式非常巧妙，有兴趣的读者可以参考这个网址的博文来学习一下：\
http://www.cnblogs.com/Anker/archive/2013/12/15/3475643.html\ 。为了使用方便，我们对Linux链表进行了封装，封装后的链表代码保存在WFGUI_APPLinkedList.c文件中，下面我们来分析链表相关的函数。

初始化链表
'''''

Linux的链表在使用前需要进行初始化， 也就是给它一个头部结点，见代码清单 17‑15。

代码清单 17‑15 初始化链表

1

2 typedef struct {

3 struct list_head listNode;

4 WM_HWIN hAPP;

5

6 } HANDLE_LIST;

7

8 static HANDLE_LIST hAppHead; //链表头部

9

10 /*\*

11 \* @brief hAPPLinkedlist_Init初始化hAPP链表

12 \* @param none

13 \* @retval none

14 \*/

15 void hAPPLinkedList_Init(void)

16 {

17

18 INIT_LIST_HEAD(&hAppHead.listNode );

19

20 }

代码中我们定义了一个结构体类型HANDLE_LIST，它包含Linux链表的指针域list_head类型以及我们自定义的数据域类型WM_HWIN hAPP，从这里可以看出我们建立链表的目的，就是为了把各个应用程序的句柄以链表的形式串起来。

链表初始化函数hAPPLinkedList_Init是调用Linux链表的宏INIT_LIST_HEAD把全局变量hAppHead初始化为头部结点。在我们的野火GUI工程中，链表的初始化是在创建GUI桌面时在CreatDeskTop函数完成的，大家可以回头去看看代码清单
17‑2，它在函数的最后调用了hAPPLinkedList_Init。链表只要初始化一次即可，在后面读者自己添加应用程序时无需再处理。

新建并添加结点到链表
''''''''''

新建并添加结点到链表的封装见代码清单 17‑16。

代码清单 17‑16 新建并添加结点到链表

1 /*\*

2 \* @brief hAPPLinkedlist_NewNode为创建一个新的hAPP结点，分配空间

3 \* @param none

4 \* @retval 指向新结点的指针

5 \*/

6 HANDLE_LIST\* hAPPLinkedList_NewNode(void)

7 {

8 HANDLE_LIST \*app = (HANDLE_LIST \*)malloc(sizeof(HANDLE_LIST));

9

10 if (app == NULL) {

11 DEBUG("\r\n hAPP linkedList malloc error\r\n ");

12 return NULL;

13 }

14 return app;

15 }

16

17 /*\*

18 \* @brief hAPPLinkedList_AddTail增加结点到链表

19 \* @param none

20 \* @retval none

21 \*/

22 void hAPPLinkedList_AddTail(HANDLE_LIST \*node)

23 {

24 list_add_tail(&node->listNode,&hAppHead.listNode);

25 }

26

hAPPLinkedList_NewNode函数采用malloc来给新的结点分配空间，并把结点指针以函数返回值给出。

创建了新的结点后通常我们会把该结点添加到链表结尾，我们把新建的结点指针作为参数调用我们封装好的hAPPLinkedList_AddTail即可。

在实际的使用中，我们先使用hAPPLinkedList_NewNode函数新建一个结点，然后在创建应用程序时把应用程序窗口的句柄赋值给该结点的数据域，然后把该结点添加到链表中，这样就可以使用链表来管理应用程序句柄了。在野火GUI中，每个新建的应用程序窗口都有这样的操作，在这里，以WFGUI_Temp
erature.c文件中的温度传感器应用为例，见代码清单 17‑17。

代码清单 17‑17WFGUI_Temperature函数内容

1

2

3 /*\*

4 \* @brief WFGUI_Temperature 温度计主函数

5 \*

6 \* @param none

7 \* @retval none

8 \*/

9 void WFGUI_Temperature(void)

10 {

11 WM_HWIN hGraph = 0;

12

13 HANDLE_LIST \*hDlg = hAPPLinkedList_NewNode();

14

15 WM_SetCreateFlags(WM_CF_MEMDEV);

16

17 /\* 根据资源表，创建温度计窗口 \*/

18 hDlg->hAPP = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbTEMPWin,

19 WinPara.hWinMain , 0, 0);

20

21 /\* 添加结点到链表 \*/

22 hAPPLinkedList_AddTail(hDlg);

23 /\* 向ctrl窗口发送消息 \*/

24 WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);

25

26 InitTEMPSensor();

27

28 /\* 如果本窗口有效，则一直更新数据 \*/

29 while (WM_IsWindow( hDlg->hAPP)) {

30 if (!_Stop) {

31 GUI_Delay(10);

32 if (!hGraph) {

33 hGraph = WM_GetDialogItem( hDlg->hAPP, GUI_ID_GRAPH0);

34 }

35 //_AddValues(hGraph);

36 GetTEMPData();

37 }

38 GUI_Delay(50);

39 }

40 }

我们看代码中的13~22行，先是调用了hAPPLinkedList_NewNode函数新建了一个结点，结点指针为hDlg，接着调用emXGUI的库函数GUI_CreateDialogBox创建一个温度计使用的窗口，并把函数的返回值(即温度计窗口句柄)赋值给了结点的数据域hDlg->hAPP变量，最后
调用hAPPLinkedList_AddTail函数把该结点添加到了链表尾，方便后面管理应用程序。

获取当前显示的应用句柄
'''''''''''

在用户按下控制窗口的返回键时，我们会把显示在最上层的应用程序窗口关闭，而要关闭窗口，必须获得该应用程序的句柄，这时我们精心准备的应用程序链表就派上用场了，获取当前显示的应用程序句柄的函数hAPPLinkedList_GetAppTop内容见代码清单 17‑18。

代码清单 17‑18 获取当前显示的应用程序

1

2 /*\*

3 \* @brief hAPPLinkedList_GetAppTop获取显示在最上层的窗口(即链表最后一个结点)

4 \* @param none

5 \* @retval app结点句柄，没有的话返回NULL

6 \*/

7 HANDLE_LIST\* hAPPLinkedList_GetAppTop(void)

8 {

9 HANDLE_LIST \*node;

10

11 if (!list_empty(&hAppHead.listNode)) { //若链表非空

12

13 /\* hAppHead.listNode.prev 头结点的前一个结点，即尾部结点*/

14 node = list_entry(hAppHead.listNode.prev,HANDLE_LIST,listNode);

15

16 DEBUG("\r\n node.app =%ld \\r\n ",node->hAPP);

17

18 return node;

19

20 } else

21 return NULL;

22

23 }

在hAPPLinkedList_GetAppTop函数中，先使用Linux链表的宏list_empty检测到链表非空时(即有至少有记录一个应用程序句柄)，调用宏list_entry来获取链表的尾部结点并存储到node指针变量中。

在野火GUI工程中，控制窗口返回键的回调函数应用了hAPPLinkedList_GetAppTop，见代码清单 17‑19。

代码清单 17‑19 返回键的回调函数

1 /*\*

2 \* @brief \_cbButtonWin,控制按钮窗口回调函数

3 \* @param none

4 \* @retval none

5 \*/

6 static void \_cbButtonWin(WM_MESSAGE \* pMsg)

7 {

8 int Id,NCode;

9 WM_HWIN hItem;

10

11 switch (pMsg->MsgId) {

12

13 case WM_PAINT: //重绘窗口

14 GUI_SetColor(GUI_BLACK);

15 GUI_FillRect(0,0,WM_GetWindowSizeX(pMsg->hWin) ,

WM_GetWindowSizeY(pMsg->hWin));

16 break;

17

18 case WM_CREATE: //创建窗口

19 /*返回键*/

20 hItem = BUTTON_CreateEx(0,0,40, 20,

21 pMsg->hWin, WM_CF_SHOW|WM_CF_MEMDEV , 0, GUI_ID_BUTTON0);

22 BUTTON_SetText(hItem, "<");

23 break;

24

25 case WM_NOTIFY_PARENT: //处理子窗口消息

26 Id = WM_GetId(pMsg->hWinSrc);

27 NCode = pMsg->Data.v;

28

29 if (NCode == WM_NOTIFICATION_RELEASED) {

30 if (Id == GUI_ID_BUTTON0) {

31 HANDLE_LIST \*hAPPOnTop;

32 /\* 获取最上层的窗口句柄 \*/

33 hAPPOnTop = hAPPLinkedList_GetAppTop();

34 if (hAPPOnTop != NULL) {

35 WM_DeleteWindow(hAPPOnTop->hAPP); // 关闭窗口

36 }

37 } else if (Id == GUI_ID_BUTTON1) {

38 //button1可以制作home键，现在没有实现

39 }

40 }

41 break;

42

43 default:

44 break;

45 }

46 }

当用户按下返回键时，触发进入它的回调函数，它会运行至代码第25~37行，在处理这个返回键消息时，我们使用hAPPLinkedList_GetAppTop函数从链表中获取了正在显示的应用程序句柄结点，接着通过结点的数据域找到相应的句柄，调用emXGUI的库函数WM_DeleteWindow关闭应用程序
窗口。

删除及遍历链表结点
'''''''''

在上面的程序处理中，关闭了应用程序，但还没有把记录应用程序句柄的结点从链表中删除，在后续的使用链表时，必然会导致错误，删除及遍历链表结点的函数见代码清单 17‑20。

代码清单 17‑20 删除及遍历链表结点的函数封装

1

2 /*\*

3 \* @brief hAPPLinkedList_Del删除链表中的结点，并释放malloc空间

4 \* @param none

5 \* @retval none

6 \*/

7 void hAPPLinkedList_Del(HANDLE_LIST \*node)

8 {

9 /\* TBD node在释放时没有被设置为NULL \*/

10 if (node == NULL \|\| (node->listNode.next == NULL &&

node->listNode.prev == NULL)) {

11 DEBUG("\r\n hAPP linkedList free error\r\n ");

12 return ;

13 }

14

15 /\* 删除在链表里的记录 \*/

16 list_del(&node->listNode);

17 /\* 释放结点的malloc空间 \*/

18 free(node);

19 }

20

21

22 /*\*

23 \* @brief hAPPLinkedList_GetAppNode根据APP句柄获取链表结点

24 \* @param none

25 \* @retval app结点句柄，没有的话返回NULL

26 \*/

27 HANDLE_LIST\* hAPPLinkedList_GetAppNode(WM_HWIN hAPP)

28 {

29 struct list_head \*pos;

30 HANDLE_LIST \*node;

31

32 list_for_each(pos,&hAppHead.listNode) {

33 /\* TBD 这里有个warning，不知道影响大不大*/

34 node = list_entry(pos,HANDLE_LIST,listNode);

35 DEBUG("\r\n node.app =%ld \\r\n ",node->hAPP);

36

37 /\* 返回与输入app句柄相同的结点 \*/

38 if (node->hAPP == hAPP) {

39 return node;

40 }

41 }

42

43 /\* 找不到与输入app句柄相同的结点 \*/

44 if (pos == &hAppHead.listNode)

45 return NULL;

46

47 return NULL;

48 }

在hAPPLinkedList_Del函数删除链表操作时，检查将要删除的结点是否为空，若不为空，仅需要调用Linux链表宏list_del，并把要删除的链表结点作为参数输入宏中即可，删除了链表结点后，我们还需要调用free函数释放结点的空间。

由于在我们的应用中，有时会需要使用应用程序的句柄来查找它在链表中的结点，所以我们需要遍历链表，链表遍历函数hAPPLinkedList_GetAppNode正是实现了这个功能。它以窗口句柄作为输入参数，然后调用Linux宏list_for_each遍历结点中的每一个元素，遍历时把结点中的数据域如输入
参数进行对比，如果相同，则返回该结点的指针，如果不同，则返回NULL。

当窗口关闭后，emXGUI机制会在窗口正式关闭前向该窗口发送一条WM_DELETE的消息，以使我们处理空间释放之类的事情。在野火GUI中，点击返回键关闭窗口(它的回调函数中调用WM_DeleteWindow关闭窗口)或者直接点击应用窗口右上角的关闭按钮后，emXGUI都会向该窗口发关WM_DELET
E消息，见图 17‑16。

|docx080|

图 17‑16 两种关闭应用程序窗口的方式

正是由于有多种关闭应用窗口的方式，在野火GUI工程中，我们统一在每个应用窗口回调函数的WM_DELETE消息中处理关闭窗口前的工作，而不会在返回键窗口调用了WM_DeleteWindow函数后，立即删除该窗口的链表结点，具体代码见前面的代码清单 17‑19。

在本教程中，我们以温度计窗口的回调函数为例，它的函数内容见代码清单 17‑21。

代码清单 17‑21温度计窗口的回调函数

1

2 /*\*

3 \* @brief \_cbCallback 温度计窗口回调函数

4 \*

5 \* @param pMsg

6 \* @retval none

7 \*/

8 static void \_cbTEMPWin(WM_MESSAGE \* pMsg)

9 {

10 int i, NCode, Id, Value;

11 WM_HWIN hDlg, hItem;

12 HANDLE_LIST \*appNode;

13

14 hDlg = pMsg->hWin;

15

16 switch (pMsg->MsgId) {

17

18 /\* ...
源代码这里还有很多消息，

19 由于篇幅问题在此省略了，具体可查看工程源代码...*/

20

21 case WM_DELETE:

22 /\* 获取app句柄对应的链表结点 \*/

23 appNode = hAPPLinkedList_GetAppNode(pMsg->hWin);

24 if (appNode != NULL) {

25 /\* 删除app句柄链表里的记录 \*/

26 hAPPLinkedList_Del(appNode);

27 /\* 发送消息通知ctrl窗口*/

28 WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);

29 }

30 break;

31

32 default:

33 WM_DefaultProc(pMsg);

34 }

35 }

36

在处理WM_DELETE消息时，先以pMsg->hWin(本窗口的句柄，即温度计窗口句柄)作为输入参数，调用了hAPPLinkedList_GetAppNode获取温度计窗口所在链表的结点appNode，判断appNode非空后即调用hAPPLinkedList_Del释放链表，完成链表的更新。

至此，野火GUI的框架已经讲解完毕，读者可继续阅读我们的源代码熟悉了本工程的框架，只有熟悉了工程框架，才能方便地在它之上开发出自己的应用。

野火GUI应用
-------

野火计划后续会推出基于STM32-ISO的emXGUI小程序，以独立的小程序讲解emXGUI的使用方式，让读者更加熟悉emXGUI，敬请期待。

RTT系统初始化
~~~~~~~~

RT-Thread在进行main函数前，在component.c文件中的rtthread_startup函数通过调用rt_hw_board_init初始化了systick、SDRAM、LED以及串口等外设。

初始化GUI
~~~~~~

操作系统运行后创建一个GUI专用任务，任务中调用GUI_Startup函数，它的执行流程如下：

GUI低级初始化GUI_LowLevelInit
^^^^^^^^^^^^^^^^^^^^^^^^

GUI_LowLevelInit函数主要初始化分配给x_heap的堆空间、位置以及分配内存时的最小粒度，初始化后GUI可从x_heap中分配内存空间。用来管理SDRAM的空间

GUI架构层初始化GUI_Arch_Init
^^^^^^^^^^^^^^^^^^^^^^

GUI_Arch_Init初始化GUI架构相关的内容，包含内核动态矩形链表初始化，它用于多窗口叠加时的Z序管理；还包含了不同的绘图对象，如使用8/16/32位像素格式时都有专门的内存操作函数。

GUI内核初始化X_GUI_Init
^^^^^^^^^^^^^^^^^^

X_GUI_Init会初始化GUI内核，在使用GUI前必须调用它。

初始化液晶硬件GUI_DisplayInit
^^^^^^^^^^^^^^^^^^^^^^

GUI_DisplayInit函数初始化显示屏，用户需要自己根据外接的液晶屏初始化相应的硬件，并且需要在该函数内初始化绘图表面，初始化后把SURFACE返回。

设置绘图表面GUI_SetScreenSurface
^^^^^^^^^^^^^^^^^^^^^^^^^^

GUI_SetScreenSurface使用GUI_DisplayInit函数返回的绘图表面SURFACE进行初始化，设置屏幕对象。

初始化字体GUI_FontInit和GUI_SetDefFont
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GUI_FontInit函数初始化字体，使用初始化字体得到的HFONT作为函数GUI_SetDefFont的输入，可设置为默认字体。在GUI_FontInit函数中，可以设置字体的来源，如主控芯片的内部FLASH、外部的SPI-FLASH或SD卡等。

创建桌面GUI_DesktopStartup
^^^^^^^^^^^^^^^^^^^^^^

以上一切准备就绪后，可通过调用GUI_DesktopStartup创建桌面。

在桌面回调函数的示例代码进行了如下操作：

-  WM_CREATE：初始化输入设备，如触摸屏、鼠标等；创建定时器；创建APP线程，APP线程包含各个应用。

-  WM_TIMER：定时器的处理消息，它会根据WM_CREATE中设置的定时器周期执行此处的内容，示例代码中在此处理触摸信息。

-  WM_ERASEBKGND：擦除背景，当需要绘制桌面背景时会进入此消息处理，示例代码中通过_EraseBackgnd绘制该背景。

初始化了输入设备，并通过定时器定时查询输入设备的消息。

WM_CREATE

文本显示
----

窗口显示文字的方式，前面讲过一个TEXTBOX文本框，下面讲解一下另一种方式。这种方式之前我们也稍微接触过，就是在WM_PAINT消息，调用TextOut函数绘制文本。

.. _文本显示-1:

文本显示
~~~~

文本显示相关的函数
^^^^^^^^^

x_wsprintf函数
''''''''''''

为了适应各种平台，emXGUI自带了C标准库的函数，这些库函数都带了个“x_”的前缀，它们的函数功能与 C 标准库函数的一样。本章使用的函数x_wsprintf就是其中之一，代码清单 19‑1。x_wsprintf是字符串格式化命令，主要功能是把格式化的数据写入某个\ `缓冲区
<https://baike.baidu.com/item/%E7%BC%93%E5%86%B2%E5%8C%BA>`__\ 中。

代码清单 19‑1 x_wsprintf函数（文件x_libc.h）

1 int x_wsprintf(WCHAR \*dest, const WCHAR \*format, ...);

(1) dest：\ `WCHAR <https://baike.baidu.com/item/char>`__\ 型指针，指向将要写入的字符串的缓冲区。

(2) format：格式化字符串。

emXGUI中WCHAR型是unsigned short类型，这与C库的sprintf有点区别。因此，我们传入的format实参应该是一个unsigned short类型的字符串，否则，则会出现Error。

在C语言中，我们使用char来定义字符，占用一个字节，最多只能表示128个字符，也就是ASCII码中的字符。中文则需要用多个字节来表示，可以通过用字母 L 作为 ASCII 字符串的前缀将任何 ASCII
字符串表示为宽字符字符串形式，例如，L"野火"。L与字符串之间没有空格，这样编译器才知道每个字符占用两个字节，即宽字符。

TextOut函数
'''''''''

在指定位置显示字符串，使用的是函数TextOut。与DrawText的区别在于：TextOut可以在窗口的任何位置显示字符串。但是却不可以设置文字的格式，如居中对齐，左对齐等，见代码清单 19‑2。

代码清单 19‑2 TextOut函数

1 BOOL TextOut(HDC hdc,int x,int y,LPCWSTR lpString,int nCount);

(1) hdc：绘图上下文。

(2) x，y：文字显示的起点坐标。

(3) lpString：字符串（Unicode-UCS2格式），传入的实参需是宽字符型，支持换行’\r’和回车符’\n’。

(4) nCount：要显示字符的字符数， 当设置小于0时， 将显示整个字符串文本的内容。

文本显示实验
~~~~~~

.. _设计要求-9:

设计要求
^^^^

在窗口中输出文字，在首行的位置显示所需的时长。

|docx081|

图 19‑1 设计要求

.. _代码分析-9:

代码分析
^^^^

(1) 创建父窗口

代码清单 19‑3 GUI_DEMO_Listbox函数（GUI_DEMO_Listbox.c）

1 void GUI_DEMO_TextOut(void)

2 {

3 HWND hwnd;

4 WNDCLASS wcex;

5 MSG msg;

6

7 wcex.Tag = WNDCLASS_TAG;

8 wcex.Style = CS_HREDRAW \| CS_VREDRAW;

9 wcex.lpfnWndProc = WinProc; //设置主窗口消息处理的回调函数.

10 wcex.cbClsExtra = 0;

11 wcex.cbWndExtra = 0;

12 wcex.hInstance = NULL;

13 wcex.hIcon = NULL;

14 wcex.hCursor = NULL;

15

16 //创建主窗口

17 hwnd =CreateWindowEx( NULL,

18 &wcex,

19 \_T("GUI_DEMO - TextOut"), //窗口名称

20 WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,

21 0,0,GUI_XSIZE,GUI_YSIZE, //窗口位置和大小

22 NULL,NULL,NULL,NULL);

23

24 //显示主窗口

25 ShowWindow(hwnd,SW_SHOW);

26

27 //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。

28 while(GetMessage(&msg,hwnd))

29 {

30 TranslateMessage(&msg);

31 DispatchMessage(&msg);

32 }

33 }

创建父窗口，标题栏为“GUI_DEMO_TextOut”，带有大小边框，设置winProc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

代码清单 19‑4 WM_CREATE消息响应（文件GUI_DEMO_TextOut.c）

1case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口.

2 {

3 GetClientRect(hwnd,&rc); //获得窗口的客户区矩形.

4

5 CreateWindow(BUTTON,L"OK",WS_VISIBLE,

6 rc.w-80,8,68,32,hwnd,ID_OK,NULL,NULL); //创建一个按钮(示例).

7 }

WM_CREATE消息中，在坐标（rc.w-80,8）处创建了一个OK按键。用来退出该界面。

2. WM_NOTIFY

代码清单 19‑5 WM_NOTIFY消息响应（文件GUI_DEMO_TextOut.c）

1 case WM_NOTIFY: //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,高16位为通知码;

2 lParam指向了一个NMHDR结构体.

3 {

4 u16 code,id;

5

6 code =HIWORD(wParam); //获得通知码类型.

7 id =LOWORD(wParam); //获得产生该消息的控件ID.

8

9 if(id==ID_OK && code==BN_CLICKED) // 按钮“单击”了.

10 {

11 PostCloseMessage(hwnd); //使产生WM_CLOSE消息关闭窗口.

12 }

13 break;

14 }

WM_NOTIFY消息用来检测OK键是否被按下。使用HIWORD和LOWORD函数读取控件的ID和通知码。如果OK键被按下，则发送WM_CLOSE消息关闭窗口。

3. WM_PAINT

代码清单 19‑6 WM_PAINT消息响应

1 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5 RECT rc;

6 int i,t,y;

7 WCHAR wbuf[128];

8 POINT Point;

9 GetClientRect(hwnd,&rc);

10 hdc =BeginPaint(hwnd,&ps); //开始绘图

11

12 ////用户的绘制内容...

13 SetTextColor(hdc,MapRGB(hdc,10,10,100));

14 t=GUI_GetTickCount();

15 y=24;

16 i=0;

17 Point.x = 0;

18 while(y<rc.h)

19 {

20 Point.y = y;

21 ClientToScreen(hwnd, &Point, 1);

22 if(Point.y > 480) break;

23 TextOut(hdc,10,y,L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",-1);

24 y+=20;

25 i++;

26 }

27 t =GUI_GetTickCount()-t;

28 SetTextColor(hdc,MapRGB(hdc,250,10,10));

29 x_wsprintf(wbuf,L"TextOut Time used:%dms; %.1fms/line",t,(float)t/(float)i);

30 TextOut(hdc,10,4,wbuf,-1);

31 EndPaint(hwnd,&ps); //结束绘图

32 break;

33 }

在WM_PAINT消息中，绘制显示的文字。绘制过程中，需要调用BeginPaint来获取绘图上下文和EndPaint函数结束绘图。使用GUI_GetTickCount函数来得到当前系统的时间，存放到变量t中。TextOut函数用来输出文本，这里显示的内容为：0123456789ABCDEFGHIJK
LMNOPQRSTUVWXYZ。我们使用的字体为GB2312_20_4BPP，字体高是20，所以使每行的文本的起点y坐标偏移20个像素。

调用ClientToScreen函数，将每行的起点坐标，转换为屏幕坐标，这里的起点坐标指的是客户区里面的坐标。这样的话，一旦起点坐标超出了屏幕的高度，就会停止显示文字。ClientToScreen函数的具体说明，可以查阅《emXGUI API 编程手册》章节：窗口/消息系统API。

变量i记录行数，耗费的时间=总时间t/总行数i。x_wsprintf函数的用法，与C语言的sprintf用法一致。以x_w开头的函数，都是emXGUI封装的C库函数。最后，将耗费的时间显示在（10，4）处。

代码清单 19‑7 GUI_AppMain函数（文件GUI_AppMain.c）

1 void GUI_AppMain(void)

2 {

3 while(1)

4 {

5 GUI_DEMO_Button();

6 GUI_DEMO_Checkbox();

7 GUI_DEMO_Radiobox();

8 GUI_DEMO_Textbox();

9 GUI_DEMO_Progressbar();

10 GUI_DEMO_Scrollbar();

11 GUI_DEMO_Listbox();

12 GUI_DEMO_Messagebox();

13 GUI_DEMO_TextOut();

14 }

15 }

将GUI_DEMO_TextOut函数创建的窗口，加入到GUI_AppMain中，如代码清单 19‑7。

.. _实验现象-9:

实验现象
^^^^

实验结果如图 19‑2所示。图 19‑2是在Textout窗口中显示整个屏幕的文字，所花费的时间为200ms。图 19‑3是拖动窗口到屏幕底端，刚刚好显示3行文字。可以看到耗费的时间大大减少，如果将行数输出到串口的话，串口会输出3。

|docx082|

图 19‑2 实验结果

|docx083|

图 19‑3 实验结果

绘图函数
----

emXGUI提供了各种绘图API，下表主要列出了一些常用的绘图API，用于绘制基本的图形，有关的详细描述，可以参阅后面的内容。更多的API函数说明，请阅读《emXGUI API 编程手册》章节：绘图API。

表格 20‑1 常用的API函数

==================================================== ==============================================
API函数                                              描述
==================================================== ==============================================
颜色API
MapRGB (hdc, U8 r, U8 g, U8 b)                       以r，g，b三基色方式设置颜色值，返回目标颜色
MapARGB(HDC hdc,U8 a,U8 r,U8 g,U8 b);                以a，r，g，b三基色方式设置颜色值，返回目标颜色
MapRGB565(HDC hdc,U16 rgb565);                       将RGB565格式转化为与hdc相同的颜色格式。
MapXRGB8888(HDC hdc,U32 xrgb8888);                   将XRGB8888格式转化为与hdc相同的颜色格式。
MapARGB8888(HDC hdc,U32 argb8888);                   将ARGB8888格式转化为与hdc相同的颜色格式。
SetTextColor(HDC hdc,COLORREF color);                设置字体的颜色，返回旧字体的颜色
SetPenColor(HDC hdc,COLORREF color);                 设置画笔颜色，返回旧的画笔颜色
SetBrushColor(HDC hdc,COLORREF color);               设置画刷颜色，返回旧的画刷颜色
绘图API
Line(HDC hdc,int sx,int sy,int ex,int ey);           画一条大小为一个像素的线
DrawRect(HDC hdc,const RECT \*lpRect);               画空心矩形
DrawRoundRect(HDC hdc,const RECT \*lpRect,int r);    画空心圆角矩形
DrawCircle(HDC hdc,int cx,int cy,int r);             画空心圆
DrawEllipse(HDC hdc,int cx, int cy, int rx, int ry); 画空心椭圆
FillRect(HDC hdc,const RECT \*lpRect);               填充矩形
GradientFillRect(HDC hdc,                            渐变色填充矩形

const RECT \*lpRect,COLORREF Color0,

COLORREF Color1,

BOOL bVert);                                         FillRoundRect(HDC hdc,                               填充圆角矩形

const RECT \*lpRect,int r);                          FillCircle(HDC hdc,int cx,int cy,int r);             画实心圆 FillEllipse(HDC hdc,int cx, int cy, int
rx,          画实心椭圆

int ry);                                             FillPolygon(HDC hdc,int xOff,int yOff,               画实心多边形

const POINT \*pt,int count);                         ====================================================
==============================================

颜色API
~~~~~

emXGUI设置颜色，通常有两种方式：一、使用MapRGB函数以r，g，b三基色方式设置颜色值；二、使用MapRGBxxx函数（xxx表示颜色格式），将某种颜色格式，转化为与hdc相同的颜色格式。MapRGBxxx函数有两个形参，一个是绘图上下文HDC，另一个是相应的颜色格式，见代码清单 20‑1。

代码清单 20‑1 设置颜色值（文件emXGUI.h）

1 #define RGB332(r,g,b) ((r&0x7)<<5)|((g&0x7)<<2)|(b&0x3)

2 #define RGB565(r,g,b) ((r&0x1F)<<11)|((g&0x3F)<<5)|(b&0x1F)

3 #define XRGB1555(r,g,b) ((r&0x1F)<<10)|((g&0x1F)<<5)|(b&0x1F)

4 #define ARGB1555(a,r,g,b) ((a<<15)|(r&0x1F)<<10)|((g&0x1F)<<5)|(b&0x1F)

5 #define ARGB4444(a,r,g,b) ((a<<12)|((r&0xF)<<8)|((g&0xF)<<4)|(b&0xF))

6 #define RGB888(r,g,b) ((r&0xFF)<<16)|((g&0xFF)<<8)|(b&0xFF)

7 #define XRGB8888(r,g,b) ((r&0xFF)<<16)|((g&0xFF)<<8)|(b&0xFF)

8 #define ARGB8888(a,r,g,b) ((a&0xFF)<<24)|((r&0xFF)<<16)|((g&0xFF)<<8)|(b&0xFF)

举个例子，假如我们现在要设置颜色，它RGB分量分别为R：0，G：0，B：255。

代码清单 20‑2使用MapRGB函数

1 MapRGB(hdc,0,0,255)

代码清单 20‑2使用MapRGB函数，将相应的RGB分量作为实参，完成颜色的设置。

代码清单 20‑3 使用MapRGB888函数

1 MapRGB888(hdc,RGB888(0,0,255))

以Map前缀开头的都是函数，代表颜色的映射关系，会返回一个COLORREF类型的值。COLORREF可以理解成是设备色，与 HDC相关，换句话说，就是所有用 COLORREF 的地方, 都要使用MapXXX 函数；而RGBxxx则是宏定义，表示某种颜色对应的RGB分量。

代码清单 20‑3使用MapRGB888函数，将RGB888（0，0，255）转化为与hdc相同的颜色格式。比如在一个RGB565的HDC中，RGB888（0，0，255）得到的颜色值为0000FF，经过MapRGB888(hdc，0x0000FF)后，实际就变成了设备色：0x001F。RGB888
每一个像素占3个字节，R、G、B各8位。而RGB565的R是5位，G是6位，B是5位。转换公式，参考代码清单 20‑4。注意，在使用MapRGB888函数时，后面的颜色格式必须为RGB888。

代码清单 20‑4 RGB888toRGB565转换公式

1 cRed = (n888Color & 0x00ff0000) >> 19;

2 cGreen = (n888Color & 0x0000ff00) >> 10;

3 cBlue = (n888Color & 0x000000ff) >> 3;

4

5 n565Color = (cRed << 11) + (cGreen << 5) + (cBlue << 0);

至于带透明度的颜色，则使用MapARGB、MapARGB8888和MapXRGB8888等函数，具体使用方法可以参考上面的内容。

介绍完颜色的格式之后，下面学习如何设置文字、画笔和画刷的颜色。

代码清单 20‑5 设置文字、画笔和画刷的颜色API （文件emXGUI.h）

1 COLORREF SetPenColor(HDC hdc,COLORREF color);

2 COLORREF SetBrushColor(HDC hdc,COLORREF color);

3 COLORREF SetTextColor(HDC hdc,COLORREF color);

1) hdc：绘图上下文；

2) color：颜色值。这里使用的是COLORREF类型的颜色值。因此，这里的实参应该是经过MapRGBxxx函数后得到的颜色值。

调用代码清单 20‑5的函数，就可以设置文字、画笔和画刷的颜色值。

绘制图形外框
~~~~~~

绘图API
^^^^^

Line()
''''''

绘制一条线宽为1个像素的直线。起点和终点可以由用户决定，线条的颜色由PenColor控制。

代码清单 20‑6 函数原型

1 void Line(HDC hdc,int sx,int sy,int ex,int ey);

1) hdc：绘图上下文；

2) sx，sy：直线起始点的坐标；

3) ex，ey：直线终点的坐标；

DrawRect()
''''''''''

绘制一个空心矩形，大小及位置由结构体rc决定，线条的颜色由PenColor控制。目前的emXGUI不支持修改矩形的线宽。

代码清单 20‑7函数原型

1 void DrawRect(HDC hdc,const RECT \*lpRect);

1) hdc：绘图上下文；

2) lpRect：矩形参数指针，决定矩形的显示位置和它的大小。

DrawRoundRect()
'''''''''''''''

绘制一个空心圆角矩形，大小及位置由结构体rc决定，用户可以自己定义圆角的半径。线条的颜色由PenColor控制。目前的emXGUI不支持修改矩形的线宽。

代码清单 20‑8 函数原型

1 void DrawRoundRect(HDC hdc,const RECT \*lpRect,int r);

1) hdc：绘图上下文；

2) lpRect：矩形参数指针，决定矩形的显示位置和它的大小。

3) r：圆角半径，一般不能超过某个值，该值取决于矩形的宽和高这两者中的最小值的一半。

DrawCircle()
''''''''''''

绘制一个空心圆，用户可以决定圆的圆心和半径 。线条的颜色由PenColor控制。目前的emXGUI不支持修改矩形的线宽。

代码清单 20‑9函数原型

1 void DrawCircle(HDC hdc,int cx,int cy,int r);

1) hdc：绘图上下文；

2) cx，cy：圆心的位置坐标；

3) r：圆的半径。

DrawEllipse()
'''''''''''''

绘制一个空心椭圆，用户可以决定椭圆的中心，水平半径以及以及垂直半径。线条的颜色由PenColor控制。目前的emXGUI不支持修改矩形的线宽。

代码清单 20‑10 函数原型

1 void DrawEllipse(HDC hdc,int cx, int cy, int rx, int ry);

1) hdc：绘图上下文；

2) cx，cy：椭圆的中心位置坐标；

3) rx：椭圆的水平半径；

4) ry：椭圆的垂直半径。

以上的这些函数，我们通常可以用来绘制一个图形的边框，但是由于改变不了线宽，一旦我们对图形的外边框有大小要求，则需要采用另一种方法，这个方法在下一小节进行讲解。

绘制图形外观实验
^^^^^^^^

.. _设计要求-10:

设计要求
''''

使用上面的几个绘图API，绘制出图 20‑1的界面。

|docx084|

图 20‑1 设计要求

.. _代码分析-10:

代码分析
''''

(1) 创建父窗口

代码清单 20‑11 GUI_DEMO_DrawTest函数（文件GUI_DEMO_DrawTest.c）

1 void GUI_DEMO_DrawTest(void)

2 {

3 HWND hwnd;

4 WNDCLASS wcex;

5 MSG msg;

6 wcex.Tag = WNDCLASS_TAG;

7

8 wcex.Style = CS_HREDRAW \| CS_VREDRAW;

9 wcex.lpfnWndProc = WinProc; //设置主窗口消息处理的回调函数.

10 wcex.cbClsExtra = 0;

11 wcex.cbWndExtra = 0;

12 wcex.hInstance = NULL;

13 wcex.hIcon = NULL;

14 wcex.hCursor = NULL;

15

16 //创建主窗口

17 hwnd =CreateWindowEx(NULL,

18 &wcex,

19 \_T("emXGUI Window"), //窗口名称

20 WS_CLIPCHILDREN,

21 0,0,GUI_XSIZE,GUI_YSIZE, //窗口位置和大小

22 NULL,NULL,NULL,NULL);

23

24 //显示主窗口

25 ShowWindow(hwnd,SW_SHOW);

26

27 //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。

28 while(GetMessage(&msg,hwnd))

29 {

30 TranslateMessage(&msg);

31 DispatchMessage(&msg);

32 }

33 }

创建父窗口，标题栏为“GUI_DEMO_DrawTest”，设置winProc作为窗口回调函数。

(2) 窗口回调函数

代码清单 20‑12 窗口回调函数winProc（文件GUI_DEMO_DrawTest.c）

1 static LRESULT WinProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)

2 {

3 RECT rc;

4 switch(msg)

5 {

6 //窗口创建时,会自动产生该消息,

7 //在这里做一些初始化的操作或创建子窗口.

8 case WM_CREATE:

9 {

10 GetClientRect(hwnd,&rc); //获得窗口的客户区矩形.

11 CreateWindow(BUTTON,L"OK",WS_VISIBLE,

12 rc.w-80,8,68,32,hwnd,ID_OK,NULL,NULL); //创建一个按钮(示例).

13 return TRUE;

14 }

15 //WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,

16 //高16位为通知码;lParam指向了一个NMHDR结构体

17 case WM_NOTIFY:

18 {

19 u16 code,id;

20

21 code =HIWORD(wParam); //获得通知码类型.

22 id =LOWORD(wParam); //获得产生该消息的控件ID.

23

24 if(id==ID_OK && code==BN_CLICKED) // 按钮“单击”了.

25 {

26 PostCloseMessage(hwnd); //使产生WM_CLOSE消息关闭窗口.

27 }

28 break;

29 }

30 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

31 {

32 PAINTSTRUCT ps;

33 HDC hdc;

34 RECT rc;

35 hdc =BeginPaint(hwnd,&ps); //开始绘图

36 GetClientRect(hwnd,&rc);

37 SetBrushColor(hdc, MapRGB(hdc, 0, 0, 0));

38 FillRect(hdc, &rc);

39 Draw_Func(hwnd, hdc);

40

41 EndPaint(hwnd,&ps); //结束绘图

42 break;

43 }

44 default: //用户不关心的消息,由系统处理.

45 {

46 return DefWindowProc(hwnd,msg,wParam,lParam);

47 }

48

49 }

50 return WM_NULL;

51 }

例程的窗口函数相对简单一点，有不明白的地方，可以查阅前面的章节，这里就进行展开讲解，重点看WM_PAINT消息。

在WM_PAINT消息中，使用GetClientRect函数获取客户区的位置和大小，并使用SetBrushColor和FillRect函数将桌面背景颜色设置为黑色。绘制外观的函数Draw_Func，见代码清单 20‑13。

代码清单 20‑13 Draw_Func函数（文件GUI_DEMO_DrawTest.c）

1 void Draw_Func(HWND hwnd, HDC hdc)

2 {

3 RECT rc;

4 //设置矩形参数

5 rc.x =50;

6 rc.y =80;

7 rc.w =140;

8 rc.h =75;

9 SetPenColor(hdc,MapRGB888(hdc, DrawRect_col)); //设置画笔颜色(用于画线，框).

10 DrawRect(hdc,&rc); //绘制一个空心矩形

11 //绘制一个空心圆.

12

13 SetPenColor(hdc,MapRGB888(hdc,DrawCir_col));

14 DrawCircle(hdc,80,100,50);

15 //画斜线

16 SetPenColor(hdc,MapRGB888(hdc,DrawLine_col));

17 Line(hdc,30,160,200,230);

18 //画椭圆

19 SetPenColor(hdc,MapRGB888(hdc,DrawEllipse_col));

20 DrawEllipse(hdc, 150, 155, 65, 40);

21 }

代码清单 20‑13中，Drawxxx每绘制一种图形，都调用一次SetPenColor函数来改变图形的颜色，这些颜色值采用RGB888的颜色格式，采用宏定义的形式，方便修改，见代码清单 20‑14。

代码清单 20‑14 颜色值的宏定义

1 //空心图形颜色

2 #define DrawRect_col RGB888(250,250,250) //矩形

3 #define DrawCir_col RGB888(79,129,189) //圆

4 #define DrawEllipse_col RGB888(247,186,0) //椭圆

5 #define DrawLine_col RGB888(146,208,80) //线

最后，将绘制的窗口加入到GUI_AppMain函数中，如代码清单 20‑15。

代码清单 20‑15 GUI_AppMain函数（文件GUI_AppMain.c）

1 void GUI_AppMain(void)

2 {

3 while(1)

4 {

5 GUI_DEMO_Button();

6 GUI_DEMO_Checkbox();

7 GUI_DEMO_Radiobox();

8 GUI_DEMO_Textbox();

9 GUI_DEMO_Progressbar();

10 GUI_DEMO_Scrollbar();

11 GUI_DEMO_Listbox();

12 GUI_DEMO_TextOut();

13 GUI_DEMO_Messagebox();

14 GUI_DEMO_DrawTest();

15 }

16 }

.. _实验结果-2:

实验结果
''''

实验结果如图 20‑2所示，本实验只是让读者熟悉绘制API的使用，比较简单。

|docx085|

图 20‑2实验结果

绘制实心图形
~~~~~~

.. _绘图api-1:

绘图API
^^^^^

FillRect()
''''''''''

绘制一个实心矩形，其位置大小由结构体RECT决定，填充颜色由BrushColor控制。

代码清单 20‑16函数原型

1 void FillRect(HDC hdc,const RECT \*lpRect);

1) hdc：绘图上下文；

2) lpRect：矩形参数，控制矩形的位置和大小。

GradientFillRect()
''''''''''''''''''

绘制一个实心矩形，其位置大小由结构体RECT决定，填充颜色采用渐变色填充。

代码清单 20‑17 函数原型

1 void GradientFillRect(HDC hdc,const RECT \*lpRect,

2 COLORREF Color0,COLORREF Color1, BOOL bVert);

1) hdc：绘图上下文；

2) lpRect：矩形参数。控制矩形的位置和大小；

3) Color0：起始颜色；

4) Color1：结束颜色

5) bVert：TURE——以垂直方向渐变填充； FALSE——以水平方向渐变填充。

注意，当填充的两种颜色间隔较大，会出现明显的断层。建议要么修改屏幕(或HDC)的颜色格式为XRGB888，或者修改颜色值，减下颜色的间隔。

FillRoundRect()
'''''''''''''''

绘制一个圆角矩形，其位置大小由结构体RECT决定，用户可以自定义圆角半径，填充颜色由BrushColor控制。

代码清单 20‑18 函数原型

1 void DrawRoundRect(HDC hdc,const RECT \*lpRect,int r);

1) hdc：绘图上下文；

2) lpRect：矩形参数。控制矩形的位置和大小；

3) r：圆角的半径值

FillCircle()
''''''''''''

绘制一个实心圆，用户可以决定圆的圆心和半径 。颜色由BrushColor控制。

代码清单 20‑19 函数原型

1 void DrawCircle(HDC hdc,int cx,int cy,int r);

1) hdc：绘图上下文；

2) cx、cy：圆心的位置坐标；

3) r：圆的半径。

FillEllipse()
'''''''''''''

绘制一个实心椭圆，用户可以决定椭圆的中心，水平半径以及以及垂直半径。\ *颜色由BrushColor控制。*

代码清单 20‑20 函数原型

1 void DrawEllipse(HDC hdc,int cx, int cy, int rx, int ry);

1) hdc：绘图上下文；

2) cx、cy：椭圆的中心位置坐标；

3) rx：椭圆的水平半径；

4) ry：椭圆的垂直半径；

FillPolygon()
'''''''''''''

绘制一个实心多边形，用户只需要给出多边形各个顶点的坐标就可以了。颜色由BrushColor控制。

代码清单 20‑21 函数原型

1 void FillPolygon(HDC hdc,int xOff,int yOff,const POINT \*pt,int count);

1) hdc：绘图上下文；

2) xOff，yOff：绘制到目标的偏移坐标位置；

3) pt：多边形各顶点坐标数组缓冲区，数组元素的排列顺序应该是各个顶点的逆时钟排序。图 20‑3，以五边形为例，若要绘制图中的五边形，pt数组中存放的坐标应该对应A，B，C，D，E。

4) count：多边顶点数。

|docx086|

图 20‑3 绘图顺序说明

这里补充一下：xOff以及yOff的用法。如果不使用的话，直接给0即可。

|docx087|

图 20‑4 xOff和yOff说明

以图 20‑4为例，进行讲解。我们要在客户区绘制这样的四边形。以A点为原点，即xOff等于A点的横坐标，yOff等于 A的纵坐标，得到如图 20‑5所示的坐标值，这样可以减少计算量。

|docx088|

图 20‑5 得到的坐标

绘制填充图形实验
^^^^^^^^

.. _设计要求-11:

设计要求
''''

在上一个实验的基础上，使用上述的绘图API，绘制如下界面，见图 20‑6。

|docx089|

图 20‑6 设计要求

.. _代码分析-11:

代码分析
''''

代码与上一节的实验相同，重点看WM_PAINT消息，

代码清单 20‑22 WM_PAINT消息响应（文件GUI_DEMO_DrawTest.c）

1 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5 RECT rc;

6 hdc =BeginPaint(hwnd,&ps); //开始绘图

7 GetClientRect(hwnd,&rc);

8 SetBrushColor(hdc, MapRGB(hdc, 0, 0, 0));

9 FillRect(hdc, &rc);

10 Draw_Func(hwnd, hdc);

11 Fill_Func(hwnd, hdc);

12 EndPaint(hwnd,&ps); //结束绘图

13 break;

14 }

代码清单 20‑22中，调用了Fill_Func函数，来绘制图形，见代码清单 20‑23。

代码清单 20‑23 Fill_Func函数（文件GUI_DEMO_DrawTest.c）

1 void Fill_Func(HWND hwnd, HDC hdc)

2 {

3 POINT pt_RTri[3]={{35, 200},

4 {35, 300},

5 {235, 300}

6 };

7 //绘制直角三角形

8 SetBrushColor(hdc, MapRGB888(hdc, FillRTri_col)); //设置颜色， 使用BrushColor。

9 FillPolygon(hdc, 10, 30, &pt_RTri[0],3); //填充多边形。

10 //绘制等边三角形

11 POINT pt_EqTri[3]={{220, 120},{320, 120},{270, 13}};

12 SetBrushColor(hdc, MapRGB888(hdc, FillEqTri_col)); //设置颜色， 使用BrushColor。

13 FillPolygon(hdc, 10, 30, &pt_EqTri[0],3); //填充多边形。

14 //绘制圆

15 SetBrushColor(hdc, MapRGB888(hdc, FillCir_col));

16 FillCircle(hdc, 320, 250, 60);

17 //绘制矩形

18 RECT rc_rect = {280, 320, 165, 55};

19 SetBrushColor(hdc, MapRGB888(hdc, FillRECT_col));

20 FillRect(hdc, &rc_rect);

21 //绘制圆角矩形

22 RECT rc_Roundrect = {390, 160, 55, 150};

23 SetBrushColor(hdc, MapRGB888(hdc, FillRoundRECT_col));

24 FillRoundRect(hdc, &rc_Roundrect,14);

25 //绘制椭圆

26 SetBrushColor(hdc, MapRGB888(hdc, FillEllipse_col));

27 FillEllipse(hdc, 500, 80, 90, 55);

28

29 //绘制渐变色正方形

30 RECT rc_square = {470, 235, 140, 140};

31 GradientFillRect(hdc, &rc_square, MapRGB888(hdc, Fillsquare_col0),

32 MapRGB888(hdc, Fillsquare_col1), FALSE);

33 //绘制正方体顶部

34 RECT Cube = {630, 120, 100, 100};

35 SetBrushColor(hdc, MapRGB888(hdc, FillCube_col));

36 FillRect(hdc, &Cube);

37 //绘制正方体侧面

38 POINT pt_SidePolygon[4]={{730, 120}, {730, 220},

39 {765, 185}, {765, 85}};

40 SetBrushColor(hdc, MapRGB888(hdc, FillCubeside_col));

41 FillPolygon(hdc, 0, 0, &pt_SidePolygon[0],4); //填充多边形。

42 //绘制正方体正面

43 POINT pt_TopPolygon[4]={{665, 85}, {630, 120},

44 {730, 120}, {765, 85}};

45 SetBrushColor(hdc, MapRGB888(hdc, FillCubetop_col));

46 FillPolygon(hdc, 0, 0, &pt_TopPolygon[0],4); //填充多边形。

47

48 //绘制长方体

49 RECT cuboid = {650, 280, 60, 165};

50 SetBrushColor(hdc, MapRGB888(hdc, Fillcuboid_col));

51 FillRect(hdc, &cuboid);

52 //绘制长方体侧面

53 POINT pt_cuboidSide[4]={{710, 280}, {710, 445},

54 {731, 424}, {731, 259}};

55 SetBrushColor(hdc, MapRGB888(hdc, Fillcuboidside_col));

56 FillPolygon(hdc, 0, 0, &pt_cuboidSide[0],4); //填充多边形。

57 //绘制长方体正面

58 POINT pt_cuboidTop[4]={{671, 259}, {650, 280},

59 {710, 280}, {731, 259}};

60 SetBrushColor(hdc, MapRGB888(hdc, Fillcuboidtop_col));

61 FillPolygon(hdc, 0, 0, &pt_cuboidTop[0],4); //填充多边形。

62 }

使用SetBrushColor函数来设置填充的颜色，调用Fillxxxx函数进行填充。下面讲解一下正方体制作，长方体也是一样的操作。

在讲解正方体之间，给大家复习一下小学学过的画立体图形的方法：斜二测画法。

|docx090|

图 20‑7 斜二测画法示意图

斜二测画法的口诀是：平行改斜垂依旧，横等纵半竖不变。我们学习斜二测画法，主要是为了做坐标的计算。emXGUI没有集成绘制3D图形库，因此，如果我们需要绘制3D图形时，就需要自己计算坐标。图
20‑7，是一个2*2*2的正方体，由口诀的第一句话，可以知道角OBB’等于45°，第二句话说明了AA’和BB’的长度等于原来的长度的二分之一。由此，我们就可以计算出整个正方体各个顶点的坐标值。将所得的坐标值存放到pt数组中，利用FillPolygon函数，就可以绘制出来正方体了。

另外，由于光源与立方体的位置，决定了三个面颜色的不同。例程的图 20‑6中，是用Excel软件绘制的，再利用网页工具“在线取色器”，就可以得到每个面的颜色，见代码清单
20‑24。Win10用户，可以使用画图3D工具的取色器来获取颜色值。获取的颜色值为16进值码，通过网页工具“RGB颜色值与十六进制颜色码转换工具”最终转换为RGB颜色值。

代码清单 20‑24 正方体的颜色值

1 //正方体

2 #define FillCube_col RGB888(50,150,250) //正面

3 #define FillCubeside_col RGB888(40,121,201) //侧面

4 #define FillCubetop_col RGB888(90,171,251) //顶部

.. _实验结果-3:

实验结果
''''

最后得到的结果如图 20‑8。大致上和我们的设计要求一模一样，而且利用上面的方法画出来的立体图形的空间观感好。

|docx091|

图 20‑8 实验结果

绘制带外边框的图形
~~~~~~~~~

InflateRect函数
^^^^^^^^^^^^^

代码清单 20‑25 InflateRect函数（文件emXGUI.h）

BOOL InflateRect(RECT \*lprc，int dx，int dy);

1) lprc：指向矩形数据结构。

2) dx： 左边和右边各增加的坐标数，为负数时，将缩小矩形。

3) dy：上边和下边各增加的坐标数，为负数时，将缩小矩形。

利用这个函数，我们就可以画出任意大小的外边框了。

绘制带外边框的图形实验
^^^^^^^^^^^

.. _设计要求-12:

设计要求
''''

前面我们提到过，emXGUI暂时不提供设置画笔画大小的API函数。本小节，主要介绍一种画任意宽度的外边框的图形。这里以矩形为例，在实验20.3的基础上，显示一个带外边框的矩形，如图 20‑9。

|docx092|

图 20‑9 实验要求

.. _代码分析-12:

代码分析
''''

代码清单 20‑26 实现过程（文件GUI_DEMO_DrawTest.c）

1 RECT rc_borrect = {25, 330, 220, 100};

2 SetBrushColor(hdc, MapRGB888(hdc, FillRect_borcol));//设置矩形的外边框颜色

3 FillRect(hdc, &rc_borrect);

4

5 InflateRect(&rc_borrect, -5, -5);//将矩形四条边的位置减少5个坐标值

6 SetBrushColor(hdc, MapRGB888(hdc, FillborRect_col));//设置矩形的颜色

7 FillRect(hdc, &rc_borrect);

在Fill_Func函数中，添加代码清单
20‑26的代码。先调用SetBrushColor以及FillRect绘制一个矩形作为背景，颜色设置为需要的边框颜色。使用InflateRect函数，将这个矩形四条边的位置分别减少5个坐标值，也就是说矩形的外边框为5px。接着在上一个矩形的区域内，再绘制一个矩形。这就得到一个带5px外边框的矩形。

另外，如果想要实现1px外边框的矩形除了可以使用上面的方法，还可以使用DrawRect以及SetPenColor函数来实现，具体实现步骤：先用DrawRect以及SetPenColor函数来绘制矩形的外边框，接着调用InflateRect函数，将这个矩形四条边的位置分别减少1个坐标值，调用SetBr
ushColor以及FillRect来绘制矩形。第二种方法，较为简单，读者可以尝试自己编程实现。

.. _实验结果-4:

实验结果
''''

图 20‑10处的矩形就是我们所绘制的外边框矩形。其他图形，如圆，椭圆，多边形，也可以采用同样的方式来绘制。

|docx093|

图 20‑10 实验结果

显示BMP图片
-------

emXGUI 支持的 BMP 图片显示，有两种方式：一、从内部存储器读取数据来显示图片，显示速度较快，但需要的内存空间较多；二、直接从外部存储器（SD卡）读取数据并显示。

|docx094|

图 21‑1 BMP图片

图 21‑1的BMP 图片0.bmp存放在工程目录下的User\app\GUI_Demo\fish中，文件大小为66.1KB，颜色格式为32位，大小是92*184。这些图片参数，是如何在BMP 图片文件中体现的？在学习如何显示BMP 图片之前，我们需要了解一下BMP 图片文件的格式。

BMP图片格式
~~~~~~~

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
^^^^^^

见图 21‑2，阴影部分处是文件头部信息，具体说明参考表格 21‑1。

|docx095|

图 21‑2文件头部信息

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

3到14字节的意义可以用一个结构体来描述,见代码清单 21‑1。

代码清单 21‑1 BMP文件信息数据结构体

1 typedef struct tagBITMAPFILEHEADER

2 {

3 //attention: sizeof(DWORD)=4 sizeof(WORD)=2

4 DWORD bfSize; //文件大小

5 WORD bfReserved1; //保留字，不考虑

6 WORD bfReserved2; //保留字，同上

7 DWORD bfOffBits; //实际位图数据的偏移字节数，即前三个部分长度之和

8 } BITMAPFILEHEADER,tagBITMAPFILEHEADER;

位图信息头
^^^^^

剩下的部分就是位图信息头，也就是图 21‑3的处，具体说明参考表格 21‑2。

|docx096|

图 21‑3 位图信息头

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

位图信息头结构体，见代码清单 21‑2。

代码清单 21‑2位图信息头内容

1 typedef struct tagBITMAPINFOHEADER

2 {

3 //attention: sizeof(DWORD)=4 sizeof(WORD)=2

4 DWORD biSize; //指定此结构体的长度，为40

5 LONG biWidth; //位图宽，说明本图的宽度，以像素为单位

6 LONG biHeight; //位图高，指明本图的高度，像素为单位

7 WORD biPlanes; //平面数，为1

8 WORD biBitCount; //采用颜色位数，可以是1，2，4，8，16，24新的可以是32

9 DWORD biCompression; //压缩方式，可以是0，1，2，其中0表示不压缩

10 DWORD biSizeImage; //实际位图数据占用的字节数

11 LONG biXPelsPerMeter; //X方向分辨率

12 LONG biYPelsPerMeter; //Y方向分辨率

13 DWORD biClrUsed; //使用的颜色数，如果为0，则表示默认值(2^颜色位数)

14 DWORD biClrImportant; //重要颜色数，如果为0，则表示所有颜色都是重要的

15 } BITMAPINFOHEADER,tagBITMAPINFOHEADER;

由于使用的是24位的位图，所以没有调色板。而且位图的大小为92*184，和开头提到的一致。

图像像素数据
^^^^^^

本章节章节使用的是24位真彩色,则54字节之后就是像素部分，如图 21‑4的阴影部分处。

|docx097|

图 21‑4 像素数据

以上内容就是对BMP图像文件的介绍。想要了解更多的读者，可以上网搜索相关的内容。

生成图片数组
~~~~~~

上面的图片都是b i n文件格式，如何转换成 C数组。这就需要我们的工具：bin2c（工程目录\\ emxgui\tools中），界面图如图 21‑5所示。

|docx098|

图 21‑5 软件界面

它的使用方法如图 21‑6所示，非常的简单。

|docx099|

图 21‑6 使用方法

单击处的按钮，选择图片所在的路径；生成图片C数组，是一个.c文件，单击处的按钮，选择文件存放的位置。最后单击处的按钮，等待文件生成，如图 21‑7。

|docx100|

图 21‑7生成文件的内容

tagBITMAP结构体
~~~~~~~~~~~~

emXGUI使用tagBITMAP结构体来存放位图的相关信息，见代码清单 21‑3。

代码清单 21‑3 tagBITMAP结构体（文件emXGUI.h）

1 typedef struct tagBITMAP

2 {

3 U32 Format; // 位图格式。

4 U32 Width; // 位图宽度(行)。

5 U32 Height; // 位图高度(列)。

6 U32 WidthBytes;// 位图图像每一行的字节数。

7 LPVOID Bits; // 指向位图数据。

8 COLORREF \*LUT; // 颜色表,只有索引位图,BM_ALPHA4,BM_ALPHA8格式时才用到。

9 } BITMAP;

1) Format：位图的格式，对应位图文件的biBitCount（1C~1Dh），可以是BM_ARGB8888、BM_RGB888、BM_RGB565等等。

2) Width：位图的宽度，对应位图文件的biWidth（12~15h）

3) Height：位图的高度，对应位图文件的biHeight（16~19h）

4) WidthBytes：位图图像每一行的字节数，该值与位图的宽度和颜色格式有关系。假设位图使用的颜色格式为BM_ARGB8888，也就是说一个像素是占4个字节，乘上图片的宽度，就是图像每一行的字节数。

5) Bits：指向位图像素数据

6) LUT：颜色查找表，本章节没有使用到，赋值为NULL即可。

DrawBitmap函数
~~~~~~~~~~~~

emXGUI使用DrawBitmap函数可以在当前窗口中的指定位置绘制位图图像。函数的原型见代码清单 21‑4。

代码清单 21‑4 DrawBitmap函数

1 BOOL DrawBitmap(HDC hdc,int x,int y,const BITMAP \*bitmap,const RECT \*lpRect);

1) hdc：绘图上下文；

2) x，y：绘制图片的起始坐标；

3) bitmap：BITMA位图数据结构体参数，存放位图的大小，格式等信息；

4) lpRect：要绘制的位图区域，如果该值为NULL， 则绘制整个位图。

显示位图实验（图片在内部FLASH）
~~~~~~~~~~~~~~~~~~

下面介绍emXGUI第一种显示图片的方式：从内部存储器中读取数据来显示图片。

.. _设计要求-13:

设计要求
^^^^

调用DrawBitmap函数，使0.
bmp的图像铺满整个屏幕，如图 21‑8。

|docx101|

图 21‑8 设计要求

.. _代码分析-13:

代码分析
^^^^

(1) 创建父窗口

代码清单 21‑5 GUI_DEMO_Drawbitmap函数（文件GUI_DEMO_Drawbitmap.c）

1 void GUI_DEMO_Drawbitmap(void)

2 {

3 HWND hwnd;

4 WNDCLASS wcex;

5 MSG msg;

6

7 /////

8 wcex.Tag = WNDCLASS_TAG;

9

10 wcex.Style = CS_HREDRAW \| CS_VREDRAW;

11 wcex.lpfnWndProc = WinProc; //设置主窗口消息处理的回调函数.

12 wcex.cbClsExtra = 0;

13 wcex.cbWndExtra = 0;

14 wcex.hInstance = NULL;//hInst;

15 wcex.hIcon = NULL;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);

16 wcex.hCursor = NULL;//LoadCursor(NULL, IDC_ARROW);

17

18 //创建主窗口

19 hwnd =CreateWindowEx( NULL,

20 &wcex,

21 \_T("DrawBitmap(ARGB8888 Format)"),

22 WS_CLIPCHILDREN,

23 0,0,GUI_XSIZE,GUI_YSIZE,

24 NULL,NULL,NULL,NULL);

25

26 //显示主窗口

27 ShowWindow(hwnd,SW_SHOW);

28

29 //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。

30 while(GetMessage(&msg,hwnd))

31 {

32 TranslateMessage(&msg);

33 DispatchMessage(&msg);

34 }

35 }

创建父窗口，标题栏为“DrawBitmap(ARGB8888 Format)”，设置winProc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

代码清单 21‑6 WM_CREATE消息响应（文件GUI_DEMO_Drawbitmap.c）

1 static BITMAP bm_0;

2 case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口

3 {

4 //设置位图结构参数

5 bm_0.Format = BM_ARGB8888; //位图格式

6 bm_0.Width = 92; //宽度

7 bm_0.Height = 184; //高度

8 bm_0.WidthBytes =bm_0.Width*4; //每行字节数

9 bm_0.LUT =NULL; //查找表(RGB/ARGB格式不使用该参数)

10 bm_0.Bits =(void*)gImage_0; //位图数据

11 return TRUE;

12 }

定义一个BITMAP 类型的结构体变量bm_0，前面我们讲过图 21‑1是32位的位图，因此，使用的颜色格式为BM_ARGB8888，宽和高为92和184，每行的字节数为宽度*4。32位色的位图，没有调试板，所以不使用查找表参数。位图像素数据则是采用之前软件生成图片数组。注意，Bits存放的是位图的
像素数据，也就是54个字节后的内容。因此，生成图像数组需要去掉前54个字节的数据。

2. WM_ERASEBKGND

代码清单 21‑7 WM_ERASEBKGND消息（文件GUI_DEMO_Drawbitmap.c）

1 //清除背景

2 case WM_ERASEBKGND:

3 {

4 HDC hdc=(HDC)wParam;

5 GetClientRect(hwnd,&rc);

6 SetBrushColor(hdc,MapRGB(hdc,0,30,130));

7 FillRect(hdc,&rc);

8 return TRUE;

9 }

这里使用WM_ERASEBKGND消息，来绘制窗口的背景：以RGB为(0,30,130)的颜色来填充背景。

3. WM_PAINT

代码清单 21‑8 WM_PAINT消息（文件GUI_DEMO_Drawbitmap.c）

1 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5 RECT rc0;

6 int x,y;

7 hdc =BeginPaint(hwnd,&ps);

8 //获取客户区的位置和大小

9 GetClientRect(hwnd,&rc0);

10 SetPenColor(hdc,MapRGB(hdc,200,200,220));

11 for(y=0; y<rc0.h; y+=bm_0.Height)

12 {

13 for(x=0; x<rc0.w; x+=bm_0.Width)

14 {

15 //绘制图片

16 DrawBitmap(hdc,x,y,&bm_0,NULL);

17 rc.x=x;

18 rc.y=y;

19 rc.w=bm_0.Width;

20 rc.h=bm_0.Height;

21 DrawRect(hdc,&rc);//绘制矩形

22 }

23 }

24 EndPaint(hwnd,&ps);

25 break;

26 }

在WM_PAINT消息，调用BeginPaint函数开始绘图。变量x和y用来记录窗口可以显示的图片张数。利用DrawBitmap函数绘制图片，且使用DrawRect给图片绘制一个外边框。

最后，将GUI_DEMO_Drawbitmap函数加入到GUI_AppMain函数即可。

.. _实验结果-5:

实验结果
^^^^

实验结果如图 21‑9所示，和设计要求一模一样，每一张小图都有一个“画框”。

|docx102|

图 21‑9实验结果

显示外部BMP图片实验（图片在SD卡）
~~~~~~~~~~~~~~~~~~~

上一节，我们实现了将内部FLASH的图片数组显示到屏幕上， 92*184的32位图片，需要92*184*4=67712个字节的空间来存放，已经是相当大了。这一讲，我们介绍另一种方式：显示外部BMP图片，图片存放在SD卡中。

绘制位图API
^^^^^^^

BMP_GetInfoEx
'''''''''''''

emXGUI提供一个API：BMP_GetInfoEx，用来读取BMP图片的信息，函数原型见代码清单 21‑9。

代码清单 21‑9 BMP_GetInfoEx函数（文件emXGUI.h）

1 BOOL BMP_GetInfoEx(BITMAPINFO \*bm_info,GUI_GET_DATA \*read_data);

1) bm_info ：输出BMP图片信息结构体，存放BMP图片的大小、格式；

2) read_data： GUI_GET_DATA结构体类型，该结构体有两个结构体成员，一个是 lParam，用户自定义的参数，该参数会作为实参传入pfReadData回调函数；另一个是pfReadData，存放用来读取数据的回调函数指针。

BMP_DrawEx
''''''''''

使用BMP_DrawEx函数来绘制BMP图像，函数原型见代码清单 21‑10。

代码清单 21‑10 BMP_DrawEx（文件emXGUI.h）

1 BOOL BMP_DrawEx(HDC hdc,int x,int y,GUI_GET_DATA \*read_data,const RECT \*lprc);

1) hdc：绘图上下文；

2) x， y：起始的绘制坐标；

3) read_data： 指向读取BMP数据源的回调函数；

4) lprc：要绘制的BMP图像矩形区域，如果设置该参数为NULL，则绘制整个BMP图像区域。

.. _设计要求-14:

设计要求
^^^^

SD卡内有一张图片（ 图 21‑10）。使用上述的API，将它显示在屏幕上。

|docx103|

图 21‑10 设计要求

.. _代码分析-14:

代码分析
^^^^

(1) 创建父窗口

代码清单 21‑11 GUI_DEMO_Drawbitmap_Extern函数（文件GUI_DEMO_Drawbitmap_Extern.c）

1 void GUI_DEMO_Drawbitmap_Extern(void)

2 {

3 HWND hwnd;

4 WNDCLASS wcex;

5 MSG msg;

6

7 wcex.Tag = WNDCLASS_TAG;

8 wcex.Style = CS_HREDRAW \| CS_VREDRAW;

9 wcex.lpfnWndProc = WinProc; //设置主窗口消息处理的回调函数.

10 wcex.cbClsExtra = 0;

11 wcex.cbWndExtra = 0;

12 wcex.hInstance = NULL;//hInst;

13 wcex.hIcon = NULL;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);

14 wcex.hCursor = NULL;//LoadCursor(NULL, IDC_ARROW);

15

16 //创建主窗口

17 hwnd =CreateWindowEx( NULL,

18 &wcex,

19 \_T("DrawBitmap_Extern"),

20 /*WS_MEMSURFACE|*/WS_CAPTION|WS_BORDER|WS_CLIPCHILDREN,

21 0,0,GUI_XSIZE,GUI_YSIZE,

22 NULL,NULL,NULL,NULL);

23

24 //显示主窗口

25 ShowWindow(hwnd,SW_SHOW);

26

27 //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。

28 while(GetMessage(&msg,hwnd))

29 {

30 TranslateMessage(&msg);

31 DispatchMessage(&msg);

32 }

33 }

创建父窗口，标题栏为“DrawBitmap_Extern”，设置winProc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

代码清单 21‑12 WM_CREATE消息（文件GUI_DEMO_Drawbitmap_Extern.c）

1 case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口

2 {

3 HWND wnd;

4 GetClientRect(hwnd,&rc); //获得窗口的客户区矩形

5 /\* 读取文件系统中的图片信息*/

6 PIC_BMP_GetInfo_FS(&bm_0, DEMO_BMP_NAME);

7 CreateWindow(BUTTON,L"OK",WS_VISIBLE,

8 rc.w-70,rc.h-40,68,32,hwnd,ID_OK,NULL,NULL);

9

10 /\* 创建内存对象 \*/

11 hdc_mem =CreateMemoryDC(SURF_SCREEN,bm_0.Width,bm_0.Height);

12 /\* 绘制至内存对象 \*/

13 PIC_BMP_Draw_FS(hdc_mem,0,0,DEMO_BMP_NAME,NULL);

14 return TRUE;

15 }

在WM_CREATE消息中，创建了一个BUTTON按键。创建MemoryDC，大小为图片的大小。使用MemoryDC，可以绘制图片到缓冲区，肉眼看不到绘制的过程，不会出现“闪屏”。调用PIC_BMP_GetInfo_FS函数来获取图片的消息，存放在bm_0结构体中，具体的实现方式，见代码清单
21‑13。

代码清单 21‑13 PIC_BMP_GetInfo_FS（文件gui_picture_port.c）

1 /*\*

2 \* @brief 获得BMP图像的信息(文件系统)

3 \* @param bm_info（输出）：存储得到的图像信息

4 \* @param file_name（输入）: 绘制到目标的坐标

5 \* @retval FALSE:失败; TRUE:成功

6 \*/

7 BOOL PIC_BMP_GetInfo_FS(BITMAPINFO \*bm_info, char \*file_name)

8 {

9 /\* file objects \*/

10 FIL \*file;

11 FRESULT fresult;

12 BOOL res = TRUE;

13 GUI_GET_DATA get_data;

14

15 file =(FIL*)GUI_VMEM_Alloc(sizeof(FIL));

16

17 /\* 打开文件 \*/

18 fresult = f_open(file, file_name, FA_OPEN_EXISTING \| FA_READ );

19 if (fresult != FR_OK)

20 {

21 GUI_ERROR("Open Pic failed!");

22 GUI_VMEM_Free(file);

23 return FALSE;

24 }

25 /\* 把文件指针作为lParam参数*/

26 get_data.lParam = (LPARAM)file;

27 /\* 读取数据的回调函数 \*/

28 get_data.pfReadData = bmp_read_data_fs;

29 /\* 获取图片信息 \*/

30 res = BMP_GetInfoEx(bm_info,&get_data);

31 f_close(file);

32

33 /\* 释放空间 \*/

34 GUI_VMEM_Free(file);

35

36 return res;

37 }

调用GUI_VMEM_Alloc函数，在VMEM申请内存，并将申请到内存地址转换为FIL指针类型。使用文件之前，必须使用f_open函数打开文件，不再使用文件必须使用f_close函数关闭文件，f_close函数运行可以确保缓冲区完全写入到文件内。定义一个GUI_GET_DATA类型的结构体变量，把
文件指针作为lParam参数，读取数据的回调函数设置为bmp_read_data_fs。最后调用emXGUI提供的API：BMP_GetInfoEx来获取图片信息。bmp_read_data_fs函数，代码清单 21‑14。

代码清单 21‑14 bmp_read_data_fs\ **（文件gui_picture_port.c）**

1 /*\*

2 \* @brief 从流媒体加载内容的回调函数(文件系统)

3 \* @param buf[out] 存储读取到的数据缓冲区

4 \* @param offset 要读取的位置

5 \* @param size 要读取的数据大小

6 \* @param lParam 调用函数时的自定义参数（用户参数）

7 \* @retval 读取到的数据大小

8 \*/

9 static int bmp_read_data_fs(void \*buf,int offset,int size,LPARAM lParam)

10 {

11 int rw;

12

13 /\* 本回调函数中lParam是对应的文件指针*/

14 FIL \*p_file = (FIL*)lParam;

15

16 /\* 偏移到指定位置 \*/

17 f_lseek(p_file, offset);

18 /\* 读取数据到缓冲区 \*/

19 f_read(p_file, buf, (UINT)size, (UINT \*)&rw);

20 /\* 返回读取到的数据大小 \*/

21 return rw;

22 }

bmp_read_data_fs函数的形参lParam是用户自定义的参数，这里传递的是文件指针。使用文件系统函数f_lseek偏移到指定位置offset，从SD卡中读取数据到缓冲区，最后返回读取到的数据大小。

调用PIC_BMP_Draw_FS函数将图片绘制到MemoryDC，见代码清单 21‑15。

代码清单 21‑15 PIC_BMP_Draw_FS（文件gui_picture_port.c）

1 /*\*

2 \* @brief 显示文件系统中的BMP图片(文件系统)

3 \* @param hdc（输入）：绘图上下文

4 \* @param x，y（输入）: 绘制到目标的坐标

5 \* @param lprc（输入）:

6 要绘制的BMP图像矩形区域，如果设置该参数为NULL，则绘制整个BMP图像区域。

7 \* @retval FALSE:失败; TRUE:成功

8 \*/

9 BOOL PIC_BMP_Draw_FS(HDC hdc, int x, int y, char \*file_name, const RECT \*lprc)

10 {

11 /\* file objects \*/

12 FIL \*file;

13 FRESULT fresult;

14 BOOL res = TRUE;

15 GUI_GET_DATA get_data;

16

17 file =(FIL*)GUI_VMEM_Alloc(sizeof(FIL));

18

19 /\* 打开文件 \*/

20 fresult = f_open(file, file_name, FA_OPEN_EXISTING \| FA_READ );

21 if (fresult != FR_OK)

22 {

23 GUI_ERROR("Open Pic failed!");

24 GUI_VMEM_Free(file);

25 return FALSE;

26 }

27

28 /\* 把文件指针作为lParam参数*/

29 get_data.lParam = (LPARAM)file;

30 /\* 读取数据的回调函数 \*/

31 get_data.pfReadData = bmp_read_data_fs;

32 /\* 显示图片 \*/

33 res = BMP_DrawEx(hdc,x,y,&get_data,lprc);

34

35 /\* 关闭文件 \*/

36 f_close(file);

37

38 /\* 释放空间 \*/

39 GUI_VMEM_Free(file);

40

41 return res;

42 }

在PIC_BMP_Draw_FS函数中，在VMEM申请内存，并将申请到内存地址转换为FIL指针类型。调用BMP_DrawEx函数来显示图片，BMP数据源通过bmp_read_data_fs回调函数获得，最后释放申请的内存。

2. WM_NOTIFY

代码清单 21‑16 WM_NOTIFY消息（文件GUI_DEMO_Drawbitmap_Extern.c）

1 wParam低16位为发送该消息的控件ID,高16位为通知码;lParam指向了一个NMHDR结构体

2 case WM_NOTIFY:

3 {

4 u16 code,id;

5 code =HIWORD(wParam); //获得通知码类型.

6 id =LOWORD(wParam); //获得产生该消息的控件ID.

7 if(id==ID_OK && code==BN_CLICKED)

8 {

9 PostCloseMessage(hwnd); //产生WM_CLOSE消息关闭窗口

10 }

11 break;

12 }

WM_NOTIFY消息中的wParam低16位为发送该消息的控件ID，高16位为通知码。单击OK按键，则发送WM_CLOSE消息关闭窗口。

3. WM_ERASEBKGND

代码清单 21‑17 WM_ERASEBKGND消息（文件GUI_DEMO_Drawbitmap_Extern.c）

1 case WM_ERASEBKGND:

2 {

3 HDC hdc=(HDC)wParam;

4 GetClientRect(hwnd,&rc);

5 SetBrushColor(hdc,MapRGB(hdc,0,30,130));

6 FillRect(hdc,&rc);

7 return TRUE;

8 }

在客户区绘制一个矩形，大小为整个客户区的大小，填充颜色设置为RGB(0，30，130)。

4. WM_PAINT

代码清单 21‑18 WM_PAINT（文件GUI_DEMO_Drawbitmap_Extern.c）

1 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5 RECT rc0;

6 int x,y;

7 hdc =BeginPaint(hwnd,&ps);//开始绘制

8 ////用户的绘制内容...

9 GetClientRect(hwnd,&rc0);

10 SetPenColor(hdc,MapRGB(hdc,200,200,220));

11 for(y=0; y<rc0.h; y+=bm_0.Height)

12 {

13 for(x=0; x<rc0.w; x+=bm_0.Width)

14 {

15 /\* 显示文件系统中的图片文件 \*/

16 BitBlt(hdc,x,y,bm_0.Width,bm_0.Height,hdc_mem,0,0,SRCCOPY); //将MEMDC输出到窗口中。

17 rc.x=x;

18 rc.y=y;

19 rc.w=bm_0.Width;

20 rc.h=bm_0.Height;

21 DrawRect(hdc,&rc);

22 }

23 }

24 EndPaint(hwnd,&ps);

25 break;

26 }

在WM\_ CREATE中，已经将图片绘制到MemoryDC中，因此，我们只需要将MemoryDC中的图形拷贝到hdc中即可。调用BitBlt函数将MEMDC的（0，0）处的内容输出到窗口的（x，y）中，数据的数目由图片的大小决定。使用DrawRect函数给图片画个“画框”。

.. _实验结果-6:

实验结果
^^^^

绘制出来的界面截图如图 21‑11所示。

|docx104|

图 21‑11 实验结果

显示jpeg图片
--------

JPEG是Joint Photographic Experts Group(联合图像专家组)的缩写，文件后辍名为"．jpg"或"．jpeg"，是最常用的图像文件格式，能够将图像压缩在很小的储存空间，图像中重复或不重要的资料会被丢失，压缩比率通常在10：1到40：1之间，压缩比越大，品质就越低；相反地
，压缩比越小，品质就越好，可以把1.37Mb的BMP位图文件压缩至20.3KB，是目前最流行的图像格式。

图 22‑1就是一张jpeg格式的图片，本章的重点在于，将这张图片显示到屏幕上，和上一节的B M P显示一样，也有两种方式：从内部存储器读取数据来显示图片和直接从外部存储器读取数据并显示图片。

|docx105|

图 22‑1虎啸山林图

显示jpeg图片（数据在内部存储空间）
~~~~~~~~~~~~~~~~~~~

.. _绘图api-2:

绘图API
^^^^^

emXGUI提供了一些JPEG的函数（位于emXGUI_JPEG.h文件），见表格 22‑1。

表格 22‑1 emXGUI提供的JPEG的函数

================== ===============
函数名             描述
================== ===============
JPG_Open()         获取JPG_DEC句柄
JPG_GetImageSize() 获取图片的宽高
JPG_Draw()         绘制图片
JPG_Close()        释放绘图句柄
================== ===============

JPG_Open（）
''''''''''

JPG_Open函数用于获取图片句柄，调用该函数后，会生成一个JPG_DEC句柄，之后的所有操作，都可以利用该句柄来实现。函数声明，见代码清单 22‑1。

代码清单 22‑1 JPG_Open函数（文件emXGUI_JPEG.h）

1 JPG_DEC\* JPG_Open(const void \*dat,int cbSize);

1) dat：图片所在的缓冲区，一般是使用软件生成图片数组的数组名；

2) cbSize：图片数组的大小，可以使用sizeof()函数获得；

JPG_GetImageSize（）
''''''''''''''''''

JPG_GetImageSize函数用于获取图片的宽高，函数声明，见代码清单 22‑2。

代码清单 22‑2 JPG_GetImageSize函数（文件emXGUI_JPEG.h）

1 BOOL JPG_GetImageSize(U16 \*width,U16 \*height,JPG_DEC\* jdec);

1) width、height：图片的宽度、高度

2) jdec：图片的句柄，通过JPG_Open函数生成。

JPG_Draw（）
''''''''''

JPG_Draw函数用于绘制图片，函数声明，见代码清单 22‑3。

代码清单 22‑3 JPG_Draw函数（文件emXGUI_JPEG.h）

1 BOOL JPG_Draw(HDC hdc,int x,int y,JPG_DEC \*jdec);

1) hdc：绘图上下文，类似于图层；为了实现更好视觉效果，通常将图片绘制到MemoryDC中，再使用BitBlt位块传输函数绘制至屏幕图层。

2) x、y：图片的显示坐标；

3) jdec：图片的句柄，通过JPG_Open函数生成。

JPG_Close（）
'''''''''''

JPG_Close函数用于释放绘图句柄，函数声明，见代码清单 22‑4。

代码清单 22‑4 JPG_Close函数（文件emXGUI_JPEG.h）

1 void JPG_Close(JPG_DEC \*jdec);

1) jdec：图片的句柄，通过JPG_Open函数生成。

显示jpeg图片实验（数据在内部FLASH）
^^^^^^^^^^^^^^^^^^^^^^

.. _代码分析-15:

代码分析
''''

-  窗口回调函数

-  WM_CREATE

代码清单 22‑5 WM_CREATE消息（文件GUI_DEMO_DrawJPEG.c）

1 case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口

2 {

3 JPG_DEC \*dec;

4 GetClientRect(hwnd,&rc); //获得窗口的客户区矩形

5 /\* 根据图片数据创建JPG_DEC句柄 \*/

6 dec = JPG_Open(tiger_jpg, tiger_jpg_size());

7 /\* 读取图片文件信息 \*/

8 JPG_GetImageSize(&pic_width, &pic_height,dec);

9 /\* 创建内存对象 \*/

10 hdc_mem =CreateMemoryDC(SURF_SCREEN,pic_width,pic_height);

11 /\* 绘制至内存对象 \*/

12 JPG_Draw(hdc_mem, 0, 0, dec);

13 /\* 关闭JPG_DEC句柄 \*/

14 JPG_Close(dec);

15 CreateWindow(BUTTON,L"OK",WS_VISIBLE,

16 rc.w-70,rc.h-40,68,32,hwnd,ID_OK,NULL,NULL);

17 return TRUE;

18 }

定义一个JPG_EDC变量，存放图片句柄。例程的图片数据的数组名为tiger_jpg，且定义函数tiger_jpg_size来获取数组的大小，见代码清单 22‑7。

代码清单 22‑6 tiger_jpg_size函数（文件tiger_jpg.c）

1 unsigned int tiger_jpg_size(void)

2 {

3 return sizeof(tiger_jpg);

4 }

tiger_jpg_size函数使用sizeof函数，直接返回tiger_jpg数组的大小。

调用JPG_Open创建一个图片句柄。使用CreateMemoryDC函数创建MemoryDC，这样肉眼看不到绘制的过程，也就不会“闪屏”。它的大小为图片的大小，通过JPG_GetImageSize函数读取图片文件的信息。调用JPG_Draw函数将图片数据绘制至MemoryDC中，完成后，释放图片句
柄。

-  WM_PAINT

代码清单 22‑7 WM_PAINT消息（文件GUI_DEMO_DrawJPEG.c）

1 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5 RECT rc0;

6 int x=0,y=0;

7 hdc =BeginPaint(hwnd,&ps);

8 ////用户的绘制内容...

9 GetClientRect(hwnd,&rc0);

10 for(y=0; y<rc0.h; y+=pic_height)

11 {

12 for(x=0; x<rc0.w; x+=pic_width)

13 {

14 /\* 把内存对象绘制至屏幕 \*/

15 BitBlt(hdc,x,y,pic_width,pic_height,hdc_mem,0,0,SRCCOPY);//将MEMDC输出到窗口中。

16 rc.x=x;

17 rc.y=y;

18 rc.w=pic_width;

19 rc.h=pic_height;

20 DrawRect(hdc,&rc);

21 }

22 }

23 EndPaint(hwnd,&ps);

24 break;

25 }

在WM_Create消息中，将图片绘制到MemoryDC中，因此，需要显示图片时，只需要将MemoryDC的内容绘制到屏幕hdc即可。WM_PAINT消息，调用BeginPaint函数开始绘图，绘图结束需调用EndPaint函数。使用BitBlt块传输函数，将内存对象绘制至屏幕。调用DrawRect
函数给图片绘制一个“画框”。

最后，将绘制的界面函数GUI_DEMO_DrawJPEG添加到AppMain中即可。

.. _实验结果-7:

实验结果
''''

实验结果如图 22‑2所示，单击右下角的OK键，则会退出该窗口。

|docx106|

图 22‑2 实验结果

显示外部JPEG图片
~~~~~~~~~~

读取图片函数
^^^^^^

代码清单 22‑8 图片位置宏定义（文件GUI_DEMO_DrawJPEG_Extern.c）

1 /\* 为1时显示RES FLASH资源文件，为0时显示SD卡的文件 \*/

2 #define RES_PIC_DEMO 1

3

4 #if(RES_PIC_DEMO)

5 /\* FLASH资源文件加载 \*/

6 #define DEMO_JPEG_FILE_NAME "tiger.jpg"

7 #else

8 /\* SD文件系统加载 \*/

9 #define DEMO_JPEG_FILE_NAME "0:srcdata/tiger.jpg"

10 #endif

RES_PIC_DEMO决定从什么位置读取图片数据，为1时，则显示FLASH内的图片数据，为0则显示SD卡的文件。在gui_resource_port.c文件中，提供了从SPI_FLASH或者SD卡读取图片数据的函数。

RES_Load_Content
''''''''''''''''

RES_Load_Content函数是从SPI_FLASH中读取图片数据，函数声明，见代码清单 22‑9。

代码清单 22‑9 RES_Load_Content函数（文件gui_resource_port.c）

1 /*\*

2 \* @brief 从资源设备加载内容

3 \* @param file_name[in]: 文件名

4 \* @param buf[out]：加载后得到的缓冲区

5 \* @param size[out]：内容的大小

6 \* @note buf是根据内容的大小动态从VMEM中申请的，

7 \* 使用完毕buf后，需要调用h文件中的Release_Content函数释放buf的空间

8 \* @retval FALSE:失败; TRUE:成功

9 \*/

10

11 BOOL RES_Load_Content(char \*file_name, char*\* buf, u32\* size)

12 {

13 int content_offset;

14 CatalogTypeDef dir;

15 BOOL result = TRUE;

16

17 content_offset = RES_GetInfo_AbsAddr(file_name, &dir);

18 if(content_offset > 0)

19 {

20 /\* 文件内容空间 \*/

21 \*buf = (char \*)GUI_VMEM_Alloc(dir.size);

22 if(*buf != NULL)

23 {

24 /\* 加载数据*/

25 RES_DevRead((u8 \*)*buf,content_offset,dir.size);

26

27 \*size = dir.size;

28 }

29 else

30 result = FALSE;

31 }

32 else

33 result = FALSE;

34

35 return result;

36 }

RES_Load_Content函数有三个形参：file_name是图片的文件名；buf是读取的图片数据存放缓冲区，是根据内容的大小，调用GUI_VMEM_Alloc函数，动态从VMEM中申请的，使用完毕buf后，需要调用Release_Content函数释放buf的空间。Size用来存放数据的大小
。

数据在SPI_FLASH存放格式在第四章已经讲解过了，这里就不进行讲解。调用RES_GetInfo_AbsAddr函数来查找相应资源的信息，然后使用RES_DevRead将数据加载到数据缓冲区中，见代码清单 22‑10。

代码清单 22‑10 RES_DevRead函数（文件gui_resource_port.c）

1 /*\*

2 \* @brief 从设备中读取内容

3 \* @param buf 存储读取到的内容

4 \* @param addr 读取的目标地址

5 \* @param size 读取的数据量

6 \* @retval 是否读取正常

7 \*/

8 BOOL RES_DevRead(u8 \*buf,u32 addr,u32 size)

9 {

10 GUI_MutexLock(mutex_lock,5000);

11

12 SPI_FLASH_BufferRead(buf,addr,size);

13 GUI_MutexUnlock(mutex_lock);

14 return TRUE;

15 }

FS_Load_Content
'''''''''''''''

FS_Load_Content是用于从SD卡中加载内容，函数声明，见代码清单 22‑11。

代码清单 22‑11 FS_Load_Content函数（文件gui_resource_port.c）

1 /*\*

2 \* @brief 从文件系统加载内容

3 \* @param file_name[in]: 文件路径

4 \* @param buf[out]：加载后得到的缓冲区

5 \* @param size[out]：内容的大小

6 \* @note buf是根据内容的大小动态从VMEM中申请的，

7 \* 使用完毕buf后，需要调用h文件中的Release_Content函数释放buf的空间

8 \* @retval FALSE:失败; TRUE:成功

9 \*/

10 BOOL FS_Load_Content(char \*file_name, char*\* buf, u32\* size)

11 {

12 /\* file objects \*/

13 FIL \*file;

14 FRESULT fresult;

15 BOOL result = TRUE;

16 UINT br;

17

18 /\* 文件句柄空间 \*/

19 file =(FIL*)GUI_VMEM_Alloc(sizeof(FIL));

20

21 /\* 打开文件 \*/

22 fresult = f_open(file, file_name, FA_OPEN_EXISTING \| FA_READ );

23 if (fresult != FR_OK)

24 {

25 GUI_ERROR("Open file failed!");

26 GUI_VMEM_Free(file);

27 return FALSE;

28 }

29

30 \*size = f_size(file);

31 /\* 文件内容空间 \*/

32 \*buf = (char \*)GUI_VMEM_Alloc(*size);

33 if(*buf != NULL)

34 {

35 /\* 加载整个图片文件 \*/

36 fresult = f_read(file, \*buf, \*size, &br);

37 /\* 关闭文件 \*/

38 f_close(file);

39 }

40 else

41 result = FALSE;

42

43 /\* 释放空间 \*/

44 GUI_VMEM_Free(file);

45

46 return result;

47 }

FS_Load_Content函数也有三个形参，作用与SPI_FLASH一样。使用GUI_VMEM_Alloc申请内存，并强制转换为FIL指针类型，用来存放文件句柄。

使用f_open函数打开打开文件，根据内容的大小，动态申请内存，存放文件内容。加载完成后，调用f_close函数关闭文件，同时释放文件句柄。

显示外部JPEG图片实验
^^^^^^^^^^^^

.. _代码分析-16:

代码分析
''''

-  WM_CREATE

代码清单 22‑12 WM_CREATE消息（文件GUI_DEMO_DrawJPEG_Extern.c）

1 case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口

2 {

3 u8 \*jpeg_buf;

4 u32 jpeg_size;

5 JPG_DEC \*dec;

6 GetClientRect(hwnd,&rc); //获得窗口的客户区矩形

7 #if(RES_PIC_DEMO)

8 /\* 资源设备中加载 \*/

9 res = RES_Load_Content(DEMO_JPEG_FILE_NAME, (char \**)&jpeg_buf, &jpeg_size);

10 #else

11 /\* SD文件系统加载 \*/

12 res = FS_Load_Content(DEMO_JPEG_FILE_NAME, (char \**)&jpeg_buf, &jpeg_size);

13 #endif

14 if(res)

15 {

16 /\* 根据图片数据创建JPG_DEC句柄 \*/

17 dec = JPG_Open(jpeg_buf, jpeg_size);

18 /\* 读取图片文件信息 \*/

19 JPG_GetImageSize(&pic_width, &pic_height,dec);

20

21 /\* 创建内存对象 \*/

22 hdc_mem =CreateMemoryDC(SURF_SCREEN,pic_width,pic_height);

23

24 /\* 绘制至内存对象 \*/

25 JPG_Draw(hdc_mem, 0, 0, dec);

26

27 /\* 关闭JPG_DEC句柄 \*/

28 JPG_Close(dec);

29 }

30 /\* 释放图片内容空间 \*/

31 RES_Release_Content((char \**)&jpeg_buf);

32 CreateWindow(BUTTON,L"OK",WS_VISIBLE,

33 rc.w-70,rc.h-40,68,32,hwnd,ID_OK,NULL,NULL);

34 return TRUE;

35 }

WM_CREATE中，调用RES_Load_Content函数从外部设备读取图片数据，保存到数组jpeg_buf中。 JPG_Open函数用于创建JPG_DEC句柄。创建MemoryDC，大小为图片的大小
，图片的大小通过JPG_GetImageSize函数获得。最后，将图片数据绘制到MemoryDC中，并释放图片占用的内存空间，关闭JPG_DEC句柄。

-  WM_PAINT

代码清单 22‑13 WM_PAINT消息（文件GUI_DEMO_DrawJPEG_Extern.c）

1 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5 RECT rc0;

6 int x=0,y=0;

7 hdc =BeginPaint(hwnd,&ps);

8 ////用户的绘制内容...

9 GetClientRect(hwnd,&rc0);

10 /\* 若正常加载了图片 \*/

11 if(res)

12 {

13 for(y=0; y<rc0.h; y+=pic_height)

14 {

15 for(x=0; x<rc0.w; x+=pic_width)

16 {

17 /\* 把内存对象绘制至屏幕 \*/

18 BitBlt(hdc,x,y,pic_width,pic_height,hdc_mem,0,0,SRCCOPY);//将MEMDC输出到窗口中。

19 rc.x=x;

20 rc.y=y;

21 rc.w=pic_width;

22 rc.h=pic_height;

23 DrawRect(hdc,&rc);

24 }

25 }

26 }

27 EndPaint(hwnd,&ps);

28 break;

29 }

WM_PAINT消息用来绘制图片，利用BitBlt函数将MEMDC输出到窗口中。在绘制的时候，要先调用BeginPaint函数，结束时调用EndPaint函数。

-  WM_DESTROY

代码清单 22‑14 WM_DESTROY消息（文件GUI_DEMO_DrawJPEG_Extern.c）

1 case WM_DESTROY: //窗口销毁时，会自动产生该消息，在这里做一些资源释放的操作.

2 {

3 DeleteDC(hdc_mem);

4 return PostQuitMessage(hwnd); //调用PostQuitMessage，使用主窗口结束并退出消息循环.

5 }

窗口销毁时，会自动产生消息WM_DESTROY，窗口退出时，注意，要将MemoryDC释放掉。

最后，将设计好的窗口函数GUI_DEMO_DrawJPEG_Extern加入GUI_AppMain函数中。

.. _实验结果-8:

实验结果
''''

图 22‑3加载的图片数据是存放在SPI_FLASH中，显示的效果和从内部存储空间读取（图 22‑2）是一样的。读者也可以尝试将宏定义RES_PIC_DEMO改为0，从SD卡加载图片的效果。

|docx107|

图 22‑3 实验结果

显示png图片
-------

PNG（Portable Network Graphics）是一种新兴的网络图像格式。1999年，Unisys公司进一步中止了对自由软件和非商用软件开发者的GIF专利免费许可，从而使PNG格式获得了更多的关注。PNG是目前保证最不失真的格式，采用LZ77算法的派生算法进行压缩，能把图像文件压缩到极限
以利于网络传输，但又能保留所有与图像品质有关的信息。 PNG同样支持透明图片的制作，图 23‑1就是一种透明的png格式的图片。

|docx108|

图 23‑1 png图片

显示png图片（数据在内部存储空间）
~~~~~~~~~~~~~~~~~~

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
^^^^^^^^^

PNG_Open
''''''''

PNG_Open来获取PNG_DEC句柄，函数原型见代码清单 23‑1。

代码清单 23‑1 PNG_Open函数（文件emxgui_png.h）

1 PNG_DEC\* PNG_Open(const u8 \*png_dat,int png_size);

1) png_dat：图片所在的缓冲区，使用软件生成的图片数组的数组名；

2) png_size：图片数组的大小，可以使用sizeof获取数组的大小。

PNG_GetBitmap
'''''''''''''

emXGUI显示PNG图片的方式，是通过将PNG格式的图片，转换成BMP格式，利用显示位图的API函数来显示图片，函数原型，见代码清单 23‑2。

代码清单 23‑2 PNG_GetBitmap函数（文件emxgui_png.h）

1 BOOL PNG_GetBitmap(PNG_DEC \*png_dec,BITMAP \*bm);

1) png_dec：PNG_DEC句柄，由PNG_Open函数生成；

2) bm：位图结构体，存放着位图数据的大小，格式、图像数据等；

PNG_Close
'''''''''

PNG_Close用来释放绘图句柄，函数原型见代码清单 23‑3。

代码清单 23‑3 PNG_Close函数（文件emxgui_png.h）

1 void PNG_Close(PNG_DEC \*png_dec);

1) png_dec：要释放的PNG_DEC句柄。

注意，这个函数操作与JPG的释放绘图句柄有所不同，只有当读者不再使用与PNG_DEC句柄相关的操作，包括不再使用PNG_GetBitmap函数生成的位图结构体，才可以释放绘图句柄，因此，该函数只有在窗口退出时进行调用，即放在WM_DESTROY消息中使用。

显示png图片实验
^^^^^^^^^

学习了绘制上述的PNG图片绘制API之后，我们开始编写代码，将图 23‑1显示在屏幕上。

.. _代码分析-17:

代码分析
''''

(1) 窗口回调函数

-  WM_CREATE

代码清单 23‑4 WM_CREATE消息（文件GUI_DEMO_DrawPNG.c）

1 case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口

2 {

3 u8 \*jpeg_buf;

4 u32 jpeg_size;

5 JPG_DEC \*dec;

6

7 GetClientRect(hwnd,&rc); //获得窗口的客户区矩形

8 /\* 根据图片数据创建PNG_DEC句柄 \*/

9 png_dec = PNG_Open((u8 \*)redfish, redfish_size());

10 /\* 把图片转换成bitmap \*/

11 PNG_GetBitmap(png_dec, &png_bm);

12

13

14

15 res = FS_Load_Content(DEMO_JPEG_FILE_NAME, (char \**)&jpeg_buf, &jpeg_size);

16 if(res)

17 {

18 /\* 根据图片数据创建JPG_DEC句柄 \*/

19 dec = JPG_Open(jpeg_buf, jpeg_size);

20 /\* 读取图片文件信息 \*/

21 JPG_GetImageSize(&pic_width, &pic_height,dec);

22

23 /\* 创建内存对象 \*/

24 hdc_mem =CreateMemoryDC(SURF_SCREEN,pic_width,pic_height);

25

26 /\* 绘制至内存对象 \*/

27 JPG_Draw(hdc_mem, 0, 0, dec);

28

29 /\* 关闭JPG_DEC句柄 \*/

30 JPG_Close(dec);

31 }

32 /\* 释放图片内容空间 \*/

33 RES_Release_Content((char \**)&jpeg_buf);

34 return TRUE;

35 }

在WM_CREATE消息中，调用PNG_Open创建PNG_DEC句柄，以后的一切操作都可以使用PNG_DEC句柄来实现，同时通过PNG_GetBitmap将图片转换成bitmap，存放在png_bm结构体变量中。这里我们使用JPG图片作为背景，更好地突出图
23‑1是张带透明度的图片。使用FS_Load_Content函数从SD卡读取sea.jpg的图片数据。JPG_Open创建一个新的图片句柄，同时绘制图片数组到MemoryDC中。

-  WM_ERASEBKGND

代码清单 23‑5 WM_ERASEBKGND消息（文件GUI_DEMO_DrawPNG.c）

1 case WM_ERASEBKGND:

2 {

3 HDC hdc=(HDC)wParam;

4 BitBlt(hdc,0,0,pic_width,pic_height,hdc_mem,0,0,SRCCOPY); //将MEMDC输出到窗口中。

5 return TRUE;

6 }

WM_ERASEBKGND消息中，使用BitBlt块传输函数将背景图片，绘制到屏幕HDC上。

-  WM_PAINT

代码清单 23‑6 WM_PAINT消息（文件GUI_DEMO_DrawPNG.c）

1 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5 RECT rc0;

6 int x=0,y=0;

7 hdc =BeginPaint(hwnd,&ps);

8 ////用户的绘制内容...

9 GetClientRect(hwnd,&rc0);

10 for(y=0; y<rc0.h; y+=png_bm.Height)

11 {

12 for(x=0; x<rc0.w; x+=png_bm.Width)

13 {

14 /\* 显示图片 \*/

15 DrawBitmap(hdc, x, y, &png_bm, NULL);

16 }

17 }

18 EndPaint(hwnd,&ps);

19 break;

20 }

WM_CREATE消息里面，我们使用PNG_GetBitmap函数将图片转换成位图，存放在png_bm结构体变量中，因此，在WM_PAINT中，调用DrawBitmap就可以完成显示PNG格式的图片。

-  WM_DESTROY

代码清单 23‑7 WM_DESTROY消息（文件GUI_DEMO_DrawPNG.c）

1 case WM_DESTROY: //窗口销毁时，会自动产生该消息，在这里做一些资源释放的操作.

2 {

3 /\* 关闭PNG_DEC句柄 \*/

4 PNG_Close(png_dec);

5 DeleteDC(hdc_mem);

6 return PostQuitMessage(hwnd); //调用PostQuitMessage，使用主窗口结束并退出消息循环.

7 }

当窗口关闭时，意味着我们不再使用PNG_DEC句柄和png_bm结构体变量，此时就可以调用PNG_Close函数，将PNG_DEC句柄释放，同时释放MEMDC的内存空间，如代码清单 23‑7。

.. _实验现象-10:

实验现象
''''

图 23‑2就是我们绘制的结果，用户可以在WM_ERASEBKGND消息替换背景图片。

|docx109|

图 23‑2 实验结果

显示外部png图片
~~~~~~~~~

由于png图片是调用位图的API来进行绘制的，本节的知识点与绘制外部bmp的内容大同小异，这里就不讲解绘图的API了，有疑问的话，可以查看绘制外部bmp图片的章节。

显示外部png图片实验
^^^^^^^^^^^

.. _代码分析-18:

代码分析
''''

(1) 窗口回调函数

-  WM_CREATE

代码清单 23‑8 WM_CREATE消息（文件GUI_DEMO_DrawPNG_Extern.c）

1 case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口

2 {

3 u8 \*png_buf;

4 u32 png_size;

5 u8 \*jpg_buf;

6 u32 jpg_size;

7 GetClientRect(hwnd,&rc); //获得窗口的客户区矩形

8 #if(RES_PIC_DEMO)

9 /\* 资源设备中加载 \*/

10 res = RES_Load_Content(DEMO_PNG_FILE_NAME, (char \**)&png_buf, &png_size);

11 #else

12 /\* SD文件系统加载 \*/

13 res = FS_Load_Content(DEMO_PNG_FILE_NAME, (char \**)&png_buf, &png_size);

14 #endif

15 if(res)

16 {

17 /\* 根据图片数据创建PNG_DEC句柄 \*/

18 png_dec = PNG_Open(png_buf, png_size);

19 /\* 把图片转换成bitmap \*/

20 PNG_GetBitmap(png_dec, &png_bm);

21 }

22 /\* 释放图片内容空间 \*/

23 RES_Release_Content((char \**)&png_buf);

24

25 res = FS_Load_Content(DEMO_JPEG_FILE_NAME, (char \**)&jpg_buf, &jpg_size);

26 if(res)

27 {

28 jdec = JPG_Open(jpg_buf, jpg_size);

29 JPG_GetImageSize(&pic_width, &pic_height, jdec);

30 hdc_mem = CreateMemoryDC(SURF_SCREEN,pic_width,pic_height);

31 JPG_Draw(hdc_mem,0,0,jdec);

32 JPG_Close(jdec);

33 }

34 /\* 释放图片内容空间 \*/

35 RES_Release_Content((char \**)&jpg_buf);

36

37 return TRUE;

38 }

RES_PIC_DEMO宏定义决定程序从什么位置读取PNG图片，代码中的RES_PIC_DEMO为0，即从SD卡读取图片数据。根据读取成功的图片数据，调用PNG_Open函数创建图片句柄，通过PNG_GetBitmap转换为位图格式，存放在png_bm结构体中，完成之后释放PNG图片句柄。

这里也使用sea.jpg作为窗口背景，使用FS_Load_Content读取SD卡中的sea.jpg图片数据，存放在jpg_buf中。创建一个MemoryDC，大小为图片的尺寸，将图片数据绘制到MemoryDC中，最后释放图片所占用的内存和JPG图片句柄。

-  WM_PAINT

代码清单 23‑9 WM_PAINT 消息（文件GUI_DEMO_DrawPNG_Extern.c）

1 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5 RECT rc0;

6 int x=0,y=0;

7 hdc =BeginPaint(hwnd,&ps);

8 ////用户的绘制内容...

9 GetClientRect(hwnd,&rc0);

10 /\* 若正常加载了图片 \*/

11 if(res)

12 {

13 for(y=0; y<rc0.h; y+=png_bm.Height)

14 {

15 for(x=0; x<rc0.w; x+=png_bm.Width)

16 {

17 /\* 显示图片 \*/

18 DrawBitmap(hdc, x, y, &png_bm, NULL);

19 }

20 }

21 }

22 EndPaint(hwnd,&ps);

23 break;

24 }

WM_PAINT消息中， PNG图片已经转换成位图，存放在png_bm结构体中，调用DrawBitmap来显示图片。WM_PAINT消息绘制前，需要调用BeginPaint函数，结束时需要使用EndPaint函数。

-  WM_DESTROY

代码清单 23‑10 WM_DESTROY消息（文件GUI_DEMO_DrawPNG_Extern.c）

1 case WM_DESTROY: //窗口销毁时，会自动产生该消息，在这里做一些资源释放的操作.

2 {

3 /\* 关闭PNG_DEC句柄 \*/

4 PNG_Close(png_dec);

5 return PostQuitMessage(hwnd); //调用PostQuitMessage，使用主窗口结束并退出消息循环.

6 }

退出窗口时，需要调用PNG_Close来释放PNG_DEC句柄。

最后，将设计的主窗口函数加入到GUI_AppMain函数中。

.. _实验结果-9:

实验结果
''''

实验现象如图 23‑3，与上一节的实验结果一模一样。

|docx109|

图 23‑3 实验结果

显示gif图片
-------

GIF(Graphics Interchange
Format)的原义是“图像互换格式”，是CompuServe公司开发的图像文件格式。GIF文件的数据，是一种基于LZW算法的连续色调的无损压缩格式。其压缩率一般在50%左右。GIF格式可以存多幅彩色图像，如果把存于一个文件中的多幅图像数据逐幅读出并显示到屏幕上，就可构成一种最简单的动画，如图
24‑1。

|docx110|

图 24‑1 GIF图片

GIF图片显示原理
~~~~~~~~~

GIF动态图片是由多张静态图片组合而成，按照一定的顺序和时间进行播放。GIF图片有多少帧，就有多少张静态图片。\ **错误!未找到引用源。**\
是本章节要显示的GIF图片，每一个箭头代表一个延时值。显示第一张静态图，延时delay1时长后，显示第二张，共有16张静态图片，则需要显示16次，这样就实现了动态图的效果。

|docx111|

图 24‑2 GIF图片分解图

显示gif图片（数据在内部存储空间）
~~~~~~~~~~~~~~~~~~

gif图片绘制API
^^^^^^^^^^

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

代码清单 24‑1 GIF_Open函数（文件emXGUI.h）

1 HGIF GIF_Open(const void \*dat);

1) dat：图片所在的缓冲区，使用软件生成的图片数组

GIF_GetInfo
'''''''''''

GIF_GetInfo函数来获取GIF图片信息，函数原型见代码清单 24‑2。

代码清单 24‑2 GIF_GetInfo函数（文件emXGUI.h）

1 BOOL GIF_GetInfo(HGIF hGIF,IMAGE_INFO \*Info);

1) hGIF：HGIF句柄，由函数GIF_Open创建；

2) Info：GIF图片信息结构体，存放GIF的图片信息。

代码清单 24‑3 IMAGE_INFO结构体（文件emXGUI.h）

1 typedef struct tagIMAGE_INFO

2 {

3 U8 Tag[7]; //图像类型的标识

4 U8 Bpp;//图像颜色位宽

5 U16 Width; //图片宽度

6 U16 Height;//图片高度

7 }IMAGE_INFO;

这个结构体主要存放了GIF图片的一些信息， Tag参数里记录的图像的类型; 比如打开的数据是JPG图像, Tag参数里就是'J','P','G'字符标识; 如果是GIF图像,Tag参数里就是'G','I','F'。具体实现过程是由GIF_GetInfo函数来完成的，这里简单了解一下即可。

GIF_GetFrameCount
'''''''''''''''''

GIF_GetFrameDelay函数来获取GIF图片的总帧数，也就是说我们需要显示多少张图片，函数原型见代码清单 24‑4。

代码清单 24‑4 GIF_GetFrameCount函数（文件emXGUI.h）

1 UINT GIF_GetFrameCount(HGIF hGIF);

1) hGIF：HGIF句柄

前面提到过， GIF图片是将多幅图像保存为一个图像文件，从而形成动画，调用GIF_GetFrameCount函数就可以得到有多少张图片，在调用下面的GIF_GetFrameDelay函数得到的延时值，进行延时，就是实现“动画”的效果了。

GIF_GetFrameDelay
'''''''''''''''''

GIF_GetFrameDelay函数用于获取GIF图片中某一帧播放时需要延时的时间，见代码清单 24‑5。

代码清单 24‑5 GIF_GetFrameDelay函数（文件emXGUI.h）

1 GIF_DELAY GIF_GetFrameDelay(HGIF gif_dec,UINT frame_idx);

1) hGIF：HGIF句柄

2) frame_idx：GIF图片的某一帧的帧数值；

GIF_DrawFrame
'''''''''''''

GIF_DrawFrame函数用来绘制GIF图片的某一帧，代码原型见代码清单 24‑6。

代码清单 24‑6 GIF_DrawFrame函数（文件emXGUI.h）

1GIF_DELAY GIF_DrawFrame(HDC hdc,int x,int y,COLORREF bk_color,HGIF hGIF,UINT frame_idx);

1) hdc：绘图上下文

2) x、y：显示GIF图片的起点坐标；

3) bk_color：GIF图片的背景颜色；

4) hGIF：HGIF句柄

5) frame_idx：当前的帧数值

GIF_Close
'''''''''

当我们不再使用图片句柄时，调用GIF_Close函数来释放图片句柄，函数原型见代码清单 24‑7。

代码清单 24‑7 GIF_Close函数（文件emXGUI.h）

1 void GIF_Close(HGIF hGIF);

1) hGIF：HGIF句柄

显示gif图片实验
^^^^^^^^^

实验要求
''''

图 24‑3是GIF图片的第一帧，使用上述的API函数，在emXGUI实现动态图的显示。

|docx112|

图 24‑3 实验要求

.. _代码分析-19:

代码分析
''''

emXGUI通过在WM_PAINT中显示GIF图片的每一帧，延时一定时间，如此循环，最后实现显示GIF图片的动态效果，我们日常生活看到的GIF图片，也是这样的。

(1) 窗口回调函数

-  WM_CREATE

代码清单 24‑8 WM_CREATE消息（文件GUI_DEMO_DrawGIF.c）

1 case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口

2 {

3 GetClientRect(hwnd,&rc);

4 /\* 获取HGIF句柄 \*/

5 hgif = GIF_Open(king);

6 /\* 获取GIF的图片信息 \*/

7 GIF_GetInfo(hgif,&img_info);

8 /\* 获取GIF的帧数 \*/

9 frame_num = GIF_GetFrameCount(hgif);

10 CreateWindow(BUTTON,L"OK",WS_VISIBLE,rc.w-70,rc.h-40,68,32,hwnd,ID_OK,NULL,NULL);

11 SetTimer(hwnd,0,0,TMR_SINGLE,NULL);

12 return TRUE;

13 }

代码清单 24‑8，调用GIF_Open函数来获取HGIF句柄，参数king是使用软件生成的图像数组。使用GIF_GetInfo函数来得到图片的消息，存放在img_info结构体中。GIF_GetFrameCount函数用来得到GIF图片的总帧数，作为循环显示的依据。最后，创建一个定时器，用来作为图
片的显示延时，选择单次触发。这里设置定时时间为0，则定时器暂停工作。

-  WM_PAINT

代码清单 24‑9 WM_PAINT消息（文件GUI_DEMO_DrawGIF.c）

1 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5 hdc =BeginPaint(hwnd,&ps);

6 GetClientRect(hwnd,&rc);

7 if(hgif)

8 {

9 /\* 创建MemoryDC \*/

10 hdc_mem = CreateMemoryDC(SURF_SCREEN,img_info.Width,img_info.Height);

11 /\* 清除屏幕显示 \*/

12 ClrDisplay(hdc_mem,NULL,MapRGB(hdc_mem,255,255,255));

13 if(i>=frame_num)

14 {

15 i=0;

16 }

17 /\* 绘制图片至MemoryDC \*/

18 GIF_DrawFrame(hdc_mem,0,0,MapRGB(hdc_mem,255,255,255),hgif,i);

19 BitBlt(hdc,rc.x,rc.y,img_info.Width,img_info.Height,hdc_mem,0,0,SRCCOPY); //将MEMDC输出到窗口中。

20 /\* 获取当前帧的延时值 \*/

21 delay=GIF_GetFrameDelay(hgif,i);

22 i++;

23 }

24 /\* 释放MemoryDC \*/

25 DeleteDC(hdc_mem);

26

27 ResetTimer(hwnd,0,delay,TMR_SINGLE|TMR_START,NULL);

28 EndPaint(hwnd,&ps);

29 break;

30 }

代码清单 24‑9负责绘制GIF图片的每一帧，CreateMemoryDC函数创建MemoryDC，调用GIF_DrawFrame将每一帧图片绘制到MemoryDC，然后使用BitBlt块传输输出到窗口HDC，绘制完成后，释放MemoryDC。调用GIF_GetFrameDelay获取GIF当前帧需
要延时的时间，使用ResetTimer函数，来重新设置延时时间，以及定时器的功能。

-  WM_TIMER

代码清单 24‑10 WM_TIMER消息（文件GUI_DEMO_DrawGIF.c）

1 case WM_TIMER:

2 InvalidateRect(hwnd,NULL,FALSE);

3 break;

WM_TIMER消息中，当超过延时时间时，调用InvalidateRect函数重绘窗口，实际上就是给窗口发送WM_PAINT消息。

最后，设计的GUI_DEMO_DrawGIF界面函数加入到GUI_AppMain函数中即可。

.. _实验结果-10:

实验结果
''''

实验结果如图 24‑4所示，这是GIF图片中的某一帧。具体的实验效果，读者可以下载本章的例程进行观看。

|docx113|

图 24‑4 实验结果

显示外部gif图片
~~~~~~~~~

从外部读取图片数据，使用RES_Load_Content函数或者是FS_Load_Content函数。RES_Load_Content函数是从SPI_FLASH中读取图片，读取之前需要将图片烧写至SPI_FLASH中；而FS_Load_Content则是从SD卡中读取图片数据。这两个在前面章节已经讲
解过了，这里不进行过多的描述。使用两者中哪一个，由宏定义RES_PIC_DEMO决定。

代码清单 24‑11 宏定义RES_PIC_DEMO（文件GUI_DEMO_DrawGIF_Extern.c）

1 /\* 为1时显示RES FLASH资源文件，为0时显示SD卡的文件 \*/

2 #define RES_PIC_DEMO 0

3

4 #if(RES_PIC_DEMO)

5 /\* FLASH资源文件加载 \*/

6 #define DEMO_GIF_FILE_NAME "king.gif"

7 #else

8 /\* SD文件系统加载 \*/

9 #define DEMO_GIF_FILE_NAME "0:srcdata/king.gif"

10 #endif

显示外部gif图片实验
^^^^^^^^^^^

.. _实验要求-1:

实验要求
''''

实验要求和上一小节一样，区别在于上一小节图片是存放在内部FLASH中，而本节实验的图片数据是存放在SPI_FLASH或者是SD卡中，使用RES_Load_Content或者是FS_Load_Content函数来获得图片数据。

.. _代码分析-20:

代码分析
''''

(1) 窗口回调函数

-  WM_CREATE

代码清单 24‑12 WM_CREATE消息（文件GUI_DEMO_DrawGIF_Extern.c）

1 case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口

2 {

3 GetClientRect(hwnd,&rc);

4 #if(RES_PIC_DEMO)

5 /\* 资源设备中加载 \*/

6 res = RES_Load_Content(DEMO_GIF_FILE_NAME, (char \**)&gif_buf, &gif_size);

7 #else

8 /\* SD文件系统加载 \*/

9 res = FS_Load_Content(DEMO_GIF_FILE_NAME, (char \**)&gif_buf, &gif_size);

10 #endif

11 /\* 获取GIF句柄 \*/

12 hgif = GIF_Open(gif_buf);

13 /\* 获取GIF图片信息 \*/

14 GIF_GetInfo(hgif,&img_info);

15 /\* 获取GIF图片的帧数 \*/

16 frame_num = GIF_GetFrameCount(hgif);

17 CreateWindow(BUTTON,L"OK",WS_VISIBLE,rc.w-70,rc.h-40,68,32,hwnd,ID_OK,NULL,NULL);

18 SetTimer(hwnd,0,0,TMR_SINGLE,NULL);

19 return TRUE;

20 }

代码清单 24‑12 WM_CREATE消息（文件GUI_DEMO_DrawGIF_Extern.使用FS_Load_Content函数从SD卡中读取图片数据，存放在数组gif_buf中。调用GIF_Open函数来创建一个GIF图片句柄，图片数组gif_buf作为函数的实参。通过GIF_GetInf
o函数来得到图片的尺寸，存放在img_info变量中，这里尺寸大小主要用于创建MemoryDC的大小。调用GIF_GetFrameCount函数来得到GIF图片的总帧数，读者可以将frame_num通过串口打印出来，可以看到刚刚好是16帧。创建定时器，定时时间设置为0，定时器主要用于实现GIF图片的
每一帧图片的延时，也就是图 24‑2的箭头。当超过设定时间时，就会发送WM_TIMER消息。在WM_TIMER消息中，调用InvalidateRect函数来实现窗口重绘，也就是绘制下一帧图片。

-  WM_PAINT

代码清单 24‑13 WM_PAINT消息（文件GUI_DEMO_DrawGIF_Extern.c）

1 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5 hdc =BeginPaint(hwnd,&ps);

6 GetClientRect(hwnd,&rc);

7 if(hgif)

8 {

9 /\* 创建MemoryDC \*/

10 hdc_mem = CreateMemoryDC(SURF_SCREEN,img_info.Width,img_info.Height);

11 /\* 清除窗口显示内容 \*/

12 ClrDisplay(hdc_mem,NULL,MapRGB(hdc_mem,255,255,255));

13 if(i>=frame_num)

14 {

15 i=0;

16 }

17 /\* 绘制GIF图片 \*/

18 GIF_DrawFrame(hdc_mem,0,0,MapRGB(hdc_mem,255,255,255),hgif,i);

19 BitBlt(hdc,rc.x,rc.y,img_info.Width,img_info.Height,hdc_mem,0,0,SRCCOPY); //将MEMDC输出到窗口中。

20 /\* 获取GIF图片的延时值 \*/

21 delay=GIF_GetFrameDelay(hgif,i);

22 i++;

23 }

24 /\* 释放MemoryDC \*/

25 DeleteDC(hdc_mem);

26 /*设置延时值，开启定时器 \*/

27 ResetTimer(hwnd,0,delay,TMR_SINGLE|TMR_START,NULL);

28 EndPaint(hwnd,&ps);

29 break;

30 }

CreateMemoryDC函数用于创建MemoryDC，将GIF图片的每一帧绘制到MemoryDC，使用BitBlt函数将MEMDC输出到窗口HDC中，最后需要释放MemoryDC。图
24‑1帧与帧之间存在一些重叠的内容，这里调用ClrDisplay函数，将上一帧的内容清除，再绘制下一帧。GIF_GetFrameDelay得到当前帧的延时值，使用ResetTimer来设置定时器的延时值，开启定时器。对于例程的GIF图来说， 这个过程需要执行16次。

-  WM_DESTROY

代码清单 24‑14 WM_DESTROY消息（文件GUI_DEMO_DrawGIF_Extern.c）

1 case WM_DESTROY: //窗口销毁时，会自动产生该消息，在这里做一些资源释放的操作.

2 {

3 GIF_Close(hgif);

4 return PostQuitMessage(hwnd); //调用PostQuitMessage，使用主窗口结束并退出消息循环.

5 }

当窗口退出时，调用GIF_Close函数来释放GIF图片句柄。

最后，将设计好的GUI_DEMO_DrawGIF_Extern函数加入到GUI_AppMain中即可。

.. _实验结果-11:

实验结果
''''

图 24‑5是GIF图片中的某一帧，具体的实验效果，读者可以下载本章的例程进行观看。

|docx114|

图 24‑5 实验结果

字符编码
----

由于计算机只能识别0和1，文字也只能以0和1的形式在计算机里存储，所以我们需要对文字进行编码才能让计算机处理，编码的过程就是规定特定的01数字符串来表示特定的文字，最简单的字符编码例子是ASCII码。

ASCII编码
~~~~~~~

学习C语言时，我们知道在程序设计中使用ASCII编码表约定了一些控制字符、英文及数字。它们在存储器中，本质也是二进制数，只是我们约定这些二进制数可以表示某些特殊意义，如以ASCII编码解释数字“0x41”时，它表示英文字符“A”。ASCII码表分为两部分，第一部分是控制字符或通讯专用字符，它们的数字
编码从0~31，见表格 25‑21，它们并没有特定的图形显示，但会根据不同的应用程序，而对文本显示有不同的影响。ASCII码的第二部分包括空格、阿拉伯数字、标点符号、大小写英文字母以及“DEL（删除控制）”，这部分符号的数字编码从32~127，除最后一个DEL符号外，都能以图形的方式来表示，它们属于
传统文字书写系统的一部分。

表格 25‑1 ASCII码中的控制字符或通讯专用字符

====== ======== =========================== ============
十进制 十六进制 缩写/字符                   解释
====== ======== =========================== ============
0      0        NUL(null)                   空字符
1      1        SOH(start of headline)      标题开始
2      2        STX (start of text)         正文开始
3      3        ETX (end of text)           正文结束
4      4        EOT (end of transmission)   传输结束
5      5        ENQ (enquiry)               请求
6      6        ACK (acknowledge)           收到通知
7      7        BEL (bell)                  响铃
8      8        BS (backspace)              退格
9      9        HT (horizontal tab)         水平制表符
10     0A       LF (NL line feed, new line) 换行键
11     0B       VT (vertical tab)           垂直制表符
12     0C       FF (NP form feed, new page) 换页键
13     0D       CR (carriage return)        回车键
14     0E       SO (shift out)              不用切换
15     0F       SI (shift in)               启用切换
16     10       DLE (data link escape)      数据链路转义
17     11       DC1 (device control 1)      设备控制1
18     12       DC2 (device control 2)      设备控制2
19     13       DC3 (device control 3)      设备控制3
20     14       DC4 (device control 4)      设备控制4
21     15       NAK (negative acknowledge)  拒绝接收
22     16       SYN (synchronous idle)      同步空闲
23     17       ETB (end of trans. block)   传输块结束
24     18       CAN (cancel)                取消
25     19       EM (end of medium)          介质中断
26     1A       SUB (substitute)            替补
27     1B       ESC (escape)                换码(溢出)
28     1C       FS (file separator)         文件分割符
29     1D       GS (group separator)        分组符
30     1E       RS (record separator)       记录分离符
31     1F       US (unit separator)         单元分隔符
====== ======== =========================== ============

表格 25‑2 ASCII码中的字符及数字

====== ======== =========== ====== ======== =================
十进制 十六进制 缩写/字符    十进制 十六进制 缩写/字符
====== ======== =========== ====== ======== =================
32     20       (space)空格  80     50       P
33     21       !            81     51       Q
34     22       "            82     52       R
35     23       #            83     53       S
36     24       $            84     54       T
37     25       %            85     55       U
38     26       &            86     56       V
39     27       '            87     57       W
40     28       (            88     58       X
41     29       )            89     59       Y
42     2A       \*           90     5A       Z
43     2B       +            91     5B       [
44     2C       ,            92     5C       \\
45     2D       -            93     5D       ]
46     2E       .            94     5E       ^
47     2F       /            95     5F       \_
48     30       0            96     60       \`
49     31       1            97     61       a
50     32       2            98     62       b
51     33       3            99     63       c
52     34       4            100    64       d
53     35       5            101    65       e
54     36       6            102    66       f
55     37       7            103    67       g
56     38       8            104    68       h
57     39       9            105    69       i
58     3A       :            106    6A       j
59     3B       ;            107    6B       k
60     3C       <            108    6C       l
61     3D       =            109    6D       m
62     3E       >            110    6E       n
63     3F       ?            111    6F       o
64     40       @            112    70       p
65     41       A            113    71       q
66     42       B            114    72       r
67     43       C            115    73       s
68     44       D            116    74       t
69     45       E            117    75       u
70     46       F            118    76       v
71     47       G            119    77       w
72     48       H            120    78       x
73     49       I            121    79       y
74     4A       J            122    7A       z
75     4B       K            123    7B       {
76     4C       L            124    7C       \|
77     4D       M            125    7D       }
78     4E       N            126    7E       ~
79     4F       O            127    7F       DEL (delete) 删除
====== ======== =========== ====== ======== =================

后来，计算机引进到其它国家的时候，由于他们使用的不是英语，他们使用的字母在ASCII码表中没有定义，所以他们采用127号之后的位来表示这些新的字母，还加入了各种形状，一直编号到255。从128到255这些字符被称为ASCII扩展字符集。至此基本存储单位Byte(char)能表示的编号都被用完了。

中文编码
~~~~

由于英文书写系统都是由26个基本字母组成，利用26个字母组可合出不同的单词，所以用ASCII码表就能表达整个英文书写系统。而中文书写系统中的汉字是独立的方块，若参考单词拆解成字母的表示方式，汉字可以拆解成部首、笔画来表示，但这样会非常复杂(可参考五笔输入法编码)，所以中文编码直接对方块字进行编码，一
个汉字使用一个号码。

由于汉字非常多，常用字就有6000多个，如果像ASCII编码表那样只使用1个字节最多只能表示256个汉字，所以我们使用2个字节来编码。

GB2312标准
^^^^^^^^

我们首先定义的是GB2312标准。它把ASCII码表127号之后的扩展字符集直接取消掉，并规定小于127的编码按原来ASCII标准解释字符。当2个大于127的字符连在一起时，就表示1个汉字，第1个字节使用 (0xA1-0xFE) 编码，第2个字节使用(0xA1-0xFE)编码，这样的编码组合起来可以
表示了7000多个符号，其中包含6763个汉字。在这些编码里，我们还把数学符号、罗马字母、日文假名等都编进表中，就连原来在ASCII里原本就有的数字、标点以及字母也重新编了2个字节长的编码，这就是平时在输入法里可切换的“全角”字符，而标准的ASCII码表中127号以下的就被称为“半角”字符。

表格 25‑3说明了GB2312是如何兼容ASCII码的，当我们设定系统使用GB2312标准的时候，它遇到一个字符串时，会按字节检测字符值的大小，若遇到连续两个字节的数值都大于127时就把这两个连续的字节合在一起，用GB2312解码，若遇到的数值小于127，就直接用ASCII把它解码。

表格 25‑3 GB2312兼容ASCII码的原理

======= ======= ========== ===========================================
第1字节 第2字节 表示的字符 说明
======= ======= ========== ===========================================
0x68    0x69    (hi)       两个字节的值都小于127(0x7F)，使用ASCII解码
0xB0    0xA1    (啊)       两个字节的值都大于127(0x7F)，使用GB2312解码
======= ======= ========== ===========================================

区位码


在GB2312编码的实际使用中，有时会用到区位码的概念，见\ **错误!未找到引用源。**\ 。GB2312编码对所收录字符进行了“分区”处理，共94个区，每区含有94个位，共8836个码位。而区位码实际是GB2312编码的内部形式，它规定对收录的每个字符采用两个字节表示，第一个字节为“高字节”，对
应94个区；第二个字节为“低字节”，对应94个位。所以它的区位码范围是：0101-9494。为兼容ASCII码，区号和位号分别加上0xA0偏移就得到GB2312编码。在区位码上加上0xA0偏移，可求得GB2312编码范围：0xA1A1－0xFEFE，其中汉字的编码范围为0xB0A1-0xF7FE，第
一字节0xB0-0xF7（对应区号：16－87），第二个字节0xA1-0xFE（对应位号：01－94）。

例如，“啊”字是GB2312编码中的第一个汉字，它位于16区的01位，所以它的区位码就是1601，加上0xA0偏移，其GB2312编码为0xB0A1。其中区位码为0101的码位表示的是“空格”符。

|docx115|

图 25‑1 GB2312 的部分区位码

GBK编码
^^^^^

据统计，GB2312编码中表示的6763个汉字已经覆盖中国大陆99.75%的使用率，单看这个数字已经很令人满意了，但是我们不能因为那些文字不常用就不让它进入信息时代，而且生僻字在人名、文言文中的出现频率是非常高的。为此我们在GB2312标准的基础上又增加了14240个新汉字(包括所有后面介绍的Big
5中的所有汉字)和符号，这个方案被称为GBK标准。增加这么多字符，按照GB2312原来的格式来编码，2个字节已经没有足够的编码，我们聪明的程序员修改了一下格式，不再要求第2个字节的编码值必须大于127，只要第1个字节大于127就表示这是一个汉字的开始，这样就做到了兼容ASCII和GB2312标准。

表格 25‑4说明了GBK是如何兼容ASCII和GB2312标准的，当我们设定系统使用GBK标准的时候，它按顺序遍历字符串，按字节检测字符值的大小，若遇到一个字符的值大于127时，就再读取它后面的一个字符，把这两个字符值合在一起，用GBK解码，解码完后，再读取第3个字符，重新开始以上过程，若该字符值
小于127，则直接用ASCII解码。

表格 25‑4 GBK兼容ASCII和GB2312的原理

========= ========= ========= ========== ========================================================================================
第1字节   第2字节   第3字节   表示的字符 说明
========= ========= ========= ========== ========================================================================================
0x68(<7F) 0xB0(>7F) 0xA1(>7F) (h啊)      第1个字节小于127，使用ASCII解码，每2个字节大于127，直接使用GBK解码，兼容GB2312
0xB0(>7F) 0xA1(>7F) 0x68(<7F) (啊h)      第1个字节大于127，直接使用GBK码解释，第3个字节小于127，使用ASCII解码
0xB0(>7F) 0x56(<7F) 0x68(<7F) (痴h)      第1个字节大于127，第2个字节虽然小于127，直接使用GBK解码，第3个字节小于127，使用ASCII解码
========= ========= ========= ========== ========================================================================================

GB18030
^^^^^^^

随着计算机技术的普及，我们后来又在GBK的标准上不断扩展字符，这些标准被称为GB18030，如GB18030-2000、GB18030-2005等(“-”号后面的数字是制定标准时的年号)，GB18030的编码使用4个字节，它利用前面标准中的第2个字节未使用的“0x30-0x39”编码表示扩充四字节的
后缀，兼容GBK、GB2312及ASCII标准。

GB18030-2000主要在GBK基础上增加了“CJK(中日韩)统一汉字扩充A”的汉字。加上前面GBK的内容，GB18030-2000一共规定了27533个汉字（包括部首、部件等）的编码，还有一些常用非汉字符号。

GB18030-2005的主要特点是在GB18030-2000基础上增加了“CJK(中日韩)统一汉字扩充B”的汉字。增加了42711个汉字和多种我国少数民族文字的编码（如藏、蒙古、傣、彝、朝鲜、维吾尔文等）。加上前面GB18030-2000的内容，一共收录了70244个汉字。

GB2312、GBK及GB18030是汉字的国家标准编码，新版向下兼容旧版，各个标准简要说明见\ **错误!未找到引用源。**\ ，目前比较流行的是GBK编码，因为每个汉字只占用2个字节，而且它编码的字符已经能满足大部分的需求，但国家要求一些产品必须支持GB18030标准。

表格 25‑5汉字国家标准

============ ================= ================= ========== ==========================================================================================================================================================================================
类别         编码范围          汉字编码范围      扩充汉字数 说明
============ ================= ================= ========== ==========================================================================================================================================================================================
GB2312       第一字节0xA1-0xFE 第一字节0xB0-0xF7 6763       除汉字外，还包括拉丁字母、希腊字母、日文平假名及片假名字母、俄语西里尔字母在内的682个全角字符

             第二字节0xA1-0xFE 第二字节0xA1-0xFE            \ GBK          第一字节0x81-0xFE 第一字节0x81-0xA0 6080       包括部首和构件,中日韩汉字,包含了BIG5编码中的所有汉字,加上GB2312的原内容，一共有21003个汉字

             第二字节0x40-0xFE 第二字节0x40-0xFE            \ \                              第一字节0xAA-0xFE 8160

                               第二字节0x40-0xA0            \ GB18030-2000 第一字节0x81-0xFE 第一字节0x81-0x82 6530       在GBK基础上增加了中日韩统一汉字扩充A的汉字，加上GB2312、GBK的内容，一共有27533个汉字

             第二字节0x30-0x39 第二字节0x30-0x39

             第三字节0x81-0xFE 第三字节0x81-0xFE

             第四字节0x30-0x39 第四字节0x30-0x39            \ \ \ GB18030-2005 第一字节0x81-0xFE 第一字节0x95-0x98 42711
             在GB18030-2000的基础上增加了42711中日韩统一汉字扩充B中的汉字和多种我国少数民族文字的编码（如藏、蒙古、傣、彝、朝鲜、维吾尔文等），加上前面GB2312、GBK、GB18030-2000的内容，一共70244个汉字

             第二字节0x30-0x39 第二字节0x30-0x39

             第三字节0x81-0xFE 第三字节0x81-0xFE

             第四字节0x30-0x39 第四字节0x30-0x39            \ \ \ ============ ================= ================= ========== =============================================
             =============================================================================================================================================

Big5编码
^^^^^^

在台湾、香港等地区，使用较多的是Big5编码，它的主要特点是收录了繁体字。而从GBK编码开始，已经把Big5中的所有汉字收录进编码了。即对于汉字部分，GBK是Big5的超集，Big5能表示的汉字，在GBK都能找到那些字相应的编码，但他们的编码是不一样的，两个标准不兼容，如GBK中的“啊”字编码是“0
xB0A1”，而Big5标准中的编码为“0xB0DA”。

Unicode字符集和编码
~~~~~~~~~~~~~

由于各个国家或地区都根据使用自己的文字系统制定标准，同一个编码在不同的标准里表示不一样的字符，各个标准互不兼容，而又没有一个标准能够囊括所有的字符，即无法用一个标准表达所有字符。国际标准化组织(ISO)为解决这一问题，它舍弃了地区性的方案，重新给全球上所有文化使用的字母和符号进行编号，对每个字符指定
一个唯一的编号(ASCII中原有的字符编号不变)，这些字符的号码从0x000000到0x10FFFF，该编号集被称为Universal Multiple-Octet Coded Character
Set，简称UCS，也被称为Unicode。最新版的Unicode标准还包含了表情符号(聊天软件中的部分emoji表情)，可访问Unicode官网了解：\ http://www.unicode.org\ 。

Unicode字符集只是对字符进行编号，但具体怎么对每个字符进行编码，Unicode并没指定，因此也衍生出了如下几种unicode编码方案(Unicode Transformation Format)。

UTF-32
^^^^^^

对Unicode字符集编码，最自然的就是UTF-32方式了。编码时，它直接对Unicode字符集里的每个字符都用4字节来表示，转换方式很简单，直接将字符对应的编号数字转换为4字节的二进制数。如表格
25‑6，由于UTF-32把每个字符都用要4字节来存储，因此UTF-32不兼容ASCII编码，也就是说ASCII编码的文件用UTF-32标准来打开会成为乱码。

表格 25‑6 UTF-32编码示例

==== ======= =========== ===================
字符 GBK编码 Unicode编号 UTF-32编码
==== ======= =========== ===================
A    0x41    0x0000 0041 大端格式0x0000 0041
啊   0xB0A1  0x0000 554A 大端格式0x0000 554A
==== ======= =========== ===================

对UTF-32数据进行解码的时候，以4个字节为单位进行解析即可，根据编码可直接找到Unicode字符集中对应编号的字符。

UTF-32的优点是编码简单，解码也很方便，读取编码的时候每次都直接读4个字节，不需要加其它的判断。它的缺点是浪费存储空间，大量常用字符的编号只需要2个字节就能表示。其次，在存储的时候需要指定字节顺序，是高位字节存储在前(大端格式)，还是低位字节存储在前(小端格式)。

UTF-16
^^^^^^

针对UTF-32的缺点，人们改进出了UTF-16的编码方式，它采用2字节或4字节的变长编码方式(UTF-32定长为4字节)。对Unicode字符编号在0到65535的统一用2个字节来表示，将每个字符的编号转换为2字节的二进制数，即从0x0000到0xFFFF。而由于Unicode字符集在0xD800
-0xDBFF这个区间是没有表示任何字符的，所以UTF-16就利用这段空间，对Unicode中编号超出0xFFFF的字符，利用它们的编号做某种运算与该空间建立映射关系，从而利用该空间表示4字节扩展，感兴趣的读者可查阅相关资料了解具体的映射过程。

表格 25‑7 UTF-16编码示例

==== =========== =========== ===================
字符 GB18030编码 Unicode编号 UTF-16编码
==== =========== =========== ===================
A    0x41        0x0000 0041 大端格式0x0041
啊   0xB0A1      0x0000 554A 大端格式0x554A
𧗌   0x9735 F832 0x0002 75CC 大端格式0xD85D DDCC
==== =========== =========== ===================

注：𧗌 五笔：TLHH(不支持GB18030码的输入法无法找到该字，感兴趣可搜索它的Unicode编号找到)

UTF-16解码时，按两个字节去读取，如果这两个字节不在0xD800到0xDFFF范围内，那就是双字节编码的字符，以双字节进行解析，找到对应编号的字符。如果这两个字节在0xD800到 0xDFFF之间，那它就是四字节编码的字符，以四字节进行解析，找到对应编号的字符。

UTF-16编码的优点是相对UTF-32节约了存储空间，缺点是仍不兼容ASCII码，仍有大小端格式问题。

UTF-8
^^^^^

UTF-8是目前Unicode字符集中使用得最广的编码方式，目前大部分网页文件已使用UTF-8编码，如使用浏览器查看百度首页源文件，可以在前几行HTML代码中找到如下代码：

1 <meta http-equiv=Content-Type content="text/html;charset=utf-8">

其中“charset”等号后面的“utf-8”即表示该网页字符的编码方式UTF-8。

UTF-8也是一种变长的编码方式，它的编码有1、2、3、4字节长度的方式，每个Unicode字符根据自己的编号范围去进行对应的编码，见表格 25‑8。它的编码符合以下规律：

-  对于UTF-8单字节的编码，该字节的第1位设为0(从左边数起第1位，即最高位)，剩余的位用来写入字符的Unicode编号。即对于Unicode编号从0x0000 0000-0x0000
  007F的字符，UTF-8编码只需要1个字节，因为这个范围Unicode编号的字符与ASCII码完全相同，所以UTF-8兼容了ASCII码表。

-  对于UTF-8使用N个字节的编码(N>1)，第一个字节的前N位设为1，第N+1位设为0，后面字节的前两位都设为10，这N个字节的其余空位填充该字符的Unicode编号，高位用0补足。

表格 25‑8 UTF-8编码原理(x的位置用于填充Unicode编号)

================= ============== ======== ======== ======== ========
Unicode(16进制)   UTF-8（2进制）
================= ============== ======== ======== ======== ========
编号范围          第一字节       第二字节 第三字节 第四字节 第五字节
00000000-0000007F 0xxxxxxx
00000080-000007FF 110xxxxx       10xxxxxx
00000800-0000FFFF 1110xxxx       10xxxxxx 10xxxxxx
00010000-0010FFFF 11110xxx       10xxxxxx 10xxxxxx 10xxxxxx
…                 111110xx       10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
================= ============== ======== ======== ======== ========

注：实际上utf-8编码长度最大为四个字节，所以最多只能表示Unicode编码值的二进制数为21位的Unicode字符。但是已经能表示所有的Unicode字符，因为Unicode的最大码位0x10FFFF也只有21位。

UTF-8解码的时候以字节为单位去看，如果第一个字节的bit位以0开头，那就是ASCII字符，以单字节进行解析。如果第一个字节的数据位以“110”开头，就按双字节进行解析，3、4字节的解析方法类似。

UTF-8的优点是兼容了ASCII码，节约空间，且没有字节顺序的问题，它直接根据第1个字节前面数据位中连续的1个数决定后面有多少个字节。不过使用UTF-8编码汉字平均需要3个字节，比GBK编码要多一个字节。

BOM
~~~

由于UTF系列有多种编码方式，而且对于UTF-16和UTF-32还有大小端的区分，那么计算机软件在打开文档的时候到底应该用什么编码方式去解码呢？有的人就想到在文档最前面加标记，一种标记对应一种编码方式，这些标记就叫做BOM(Byte Order Mark)，它们位于文本文件的开头，见表格
25‑9。注意BOM是对Unicode的几种编码而言的，ANSI编码没有BOM。

表格 25‑9 BOM标记

=================== ===============
BOM标记             表示的编码
=================== ===============
0xEF 0xBB 0xBF      UTF-8
0xFF 0xFE           UTF-16 小端格式
0xFE 0xFF           UTF-16 大端格式
0xFF 0xFE 0x00 0x00 UTF-32 小端格式
0x00 0x00 0xFE 0xFF UTF-32 大端格式
=================== ===============

但由于带BOM的设计很多规范不兼容，不能跨平台，所以这种带BOM的设计没有流行起来。Linux系统下默认不带BOM。

如何制作字库
------

熟悉字符的编码后，我们学习如何制作字库文件。emXGUI支持的字库文件为*.xft类型的文件，可以使用XBF字体制作工具X_GUI_SIM.exe（位于过程目录下\\ \\emxgui\tools），这里我们以simfang.ttf为例。

|docx116|

图 26‑1 文件目录

工具介绍
~~~~

|docx117|

图 26‑2 工具界面图

运行X_GUI_SIM.exe程序，会得到图 26‑2的界面图片。具体操作步骤：

1. 选择字体文件

这里我们以simfang.ttf文件为例，该文件存放在XBF字体制作工具\font目录下，见图 26‑3的处。单击处按键，选择simfang.ttf，如图 26‑3的处所示。

|docx118|

图 26‑3 选择字体文件

2. 生成的字体范围

假如现在只需要使用字母Q，W，E，R，我们可以只生成一个只含有字母Q，W，E，R的xft文件，具体做法：新建一个txt文件，内容为
QWER。注意，Q前面有一个空格，一般情况下，会保留空格的编码。另外，索引文件要使用ucs-2_little_edition编码。我们可以使用Notepad++来进行设置，如图 26‑5。最后在图 26‑2的处选择刚刚新建的txt文件。

本章使用的simfang.ttf，这里以所有的字符编码为例，其txt文档（位于XBF字体制作工具\font目录下），如图 26‑4所示，包含了所有的数字，字母还有中文等编码

|docx119|

图 26‑4 txt文档内容

|docx120|

图 26‑5设置编码

单击处的按键，选择生成的字体范围，如图 26‑6。

|docx121|

图 26‑6 选择生成的字体范围

3. 选择输出路径

点击图 26‑7的处，选择输出的xft文件的保存路径，注意，在处输入文件名时，需要手动输入.
xft后缀。

|docx122|

图 26‑7 选择路径

4. 设置输出的格式

点击图 26‑8的处，弹出选项框Setting。处用来设置字体的大小，处主要是设置字体抗锯齿度，emXGUI最高可提供8 BPP，我们通常选择4BPP，处都是些默认参数，不需要修改。Xoff和Yoff负责字体的偏移。DPI代表图像每英寸面积内的像素点数。

|docx123|

图 26‑8 选择字体格式

这里解释一下什么叫抗锯齿？在这之前，需要先知道什么叫锯齿现象。图 26‑9是图像的原始尺寸。当图像放大时，由于图像的像素点与图像的尺寸是相关的，因此就出现了锯齿现象，类似于楼梯的形状，如图 26‑10的下半部分。

|docx124|

图 26‑9 原始尺寸“印刷”

|docx125|

图 26‑10 放大的“印刷”

抗锯齿是一种消除图物边缘出现凹凸锯齿的技术，就是将图像边缘及其两侧的像素颜色进行混合得到的新点，用来替换原来位置上的点以达到平滑边缘，达到消除锯齿的效果。抗锯齿程度越高 ，计算时间越长，但是效果越好。如图 26‑11的下半部分，这是设置抗锯齿（边缘平滑化）之后放大的效果图。

|docx126|

图 26‑11 抗锯齿效果图

5. 开始生成

经过前四步的设置之后，单击图 26‑2的处，就可以生成xft文件了，操作成功的结果，如图 26‑12所示。在输出文件夹下，会有一个新的xft文件。这里我选择的输出路径是XBF字体制作工具\Out中，xft文件的名字为wildfire.xtf，注意输入xft文件时，一定要自己输入xft后缀。

|docx127|

图 26‑12 生成结果

6. 测试生成的字体

X_GUI_SIM.exe提供测试生成字体的功能，使用方法如图 26‑13所示。单击图 26‑13处的Test按键，在弹出的对话框中选择刚刚生成的xft文件。这里我们选择的上面生成的wildfire.
xft文件。测试的结果如图 26‑14所示，读者可以和图 26‑2对比一下。

|docx128|

图 26‑13 测试方法

|docx129|

图 26‑14测试结果

最后，将我们生成的xft文件，放到我们的SD卡中，如图 26‑15。这里统一放到根目录下的文件夹srcdata中。读者也可以选择其他的文件夹，但是程序需要进行修改，建议初学者依葫芦画瓢。

|docx130|

图 26‑15 添加字库文件至SD卡中

到这里为止，就完成字库的制作，接下来，我们看一下如何在emXGUI使用我们刚刚生成的字库。

使用字库
~~~~

相关函数API
^^^^^^^

SetFont
'''''''

SetFont函数用来设置显示的字体格式，我们通过调用这个函数，可以切换至我们生成的字体，函数原型见代码清单 26‑1 SetFont函数（文件emXGUI.h）。

代码清单 26‑1 SetFont函数（文件emXGUI.h）

1 HFONT SetFont(HDC hdc,HFONT hFont);

1) hdc：绘图上下文；

2) hFont：字体句柄。字体句柄是通过XFT_CreateFontEx函数来创建；

此外，该函数还会返回旧的字体句柄，我们可以利用这个返回值，进行两种字体的切换。

GetFont
'''''''

调用GetFont函数会返回当前正在使用的字体，函数原型，见代码清单 26‑2 GetFont函数（文件emXGUI.h）。

代码清单 26‑2 GetFont函数（文件emXGUI.h）

1 HFONT GetFont(HDC hdc);

1) hdc：绘图上下文；

XFT_CreateFont
''''''''''''''

代码清单 26‑3 XFT_CreateFont函数（文件GUI_Font_XFT.h）

1 HFONT XFT_CreateFont(const void \*xft_dat);

1) xft_dat：字体数据，可以使用bin2c工具可以将字库文件（.xtf后缀文件）生成C语言的数组，可以放在内部FLASH中。

font_read_data_SDCARD
'''''''''''''''''''''

font_read_data_SDCARD函数从SD卡读取字库文件，得到的字体数组存放在buf中。

代码清单 26‑4 font_read_data_SDCARD函数（文件gui_font_port.c）

BOOL font_read_data_SDCARD(char*\* buf, u32 size)

2 {

3 /\* file objects \*/

4 FIL \*file;

5 FRESULT fresult;

6 BOOL result = TRUE;

7 UINT br;

8 file =(FIL*)GUI_VMEM_Alloc(sizeof(FIL));

9

10 fresult = f_open(file, GUI_DEFAULT_SDCARD_FONT, FA_OPEN_EXISTING \| FA_READ );

11

12 size = f_size(file);

13 /\* 文件内容空间 \*/

14 \*buf = (char \*)GUI_VMEM_Alloc(size);

15 fresult = f_read(file, \*buf, size, &br);

16 /\* 关闭文件 \*/

17 f_close(file);

18

19

20 /\* 释放空间 \*/

21 GUI_VMEM_Free(file);

22

23 return result;

24 }

f_open函数的参数GUI_DEFAULT_SDCARD_FONT是我们的字库文件名字，见代码清单 26‑5。如果我们存放的字库文件不是这个文件的话， 则需要修改该宏定义。

代码清单 26‑5 GUI_DEFAULT_SDCARD_FONT宏定义（文件gui_drv_cfg.h）

1 #define GUI_DEFAULT_SDCARD_FONT "0:srcdata/GB2312_16_4BPP.xft"

调用f_read函数，读取字库文件数据，需要读取的数据大小，为整个文件的的大小，通过f_size函数可以得到文件的大小。最后f_close函数关闭文件，同时释放文件句柄的空间。

使用字库实验
^^^^^^

.. _实验要求-2:

实验要求
''''

本章节的例程代码与Textout类似，区别在于WM_PAINT消息的处理：在一个窗口中，同一个文本，使用两种字体进行显示，如图 26‑16 实验要求。

|docx131|

图 26‑16 实验要求

.. _代码分析-21:

代码分析
''''

(1) 创建字体句柄

代码清单 26‑6 GUI_Default_FontInit （文件gui_font_port.c）

1 HFONT GUI_Default_FontInit(void)

2 {

3

4 HFONT hFont=NULL;

5 //此处省略一些代码

6 #elif (GUI_USE_SDCARD_FONT)

7 {

8 /\* 指向缓冲区的指针 \*/

9 static u8 \*pFontData_XFT=NULL;

10 u32 fsize;

11

12 if(hFont==NULL)

13 {

14 res = font_read_data_SDCARD((char \**)&pFontData_XFT, fsize);

15 hFont_SDCARD = XFT_CreateFont(pFontData_XFT);

16 }

17

18 }

19 #endif

20 /\* 若前面的字体加载失败，使用内部FLASH中的数据（工程中的C语言数组）

21 \* 添加字体数据时，把数组文件添加到工程，在本文件头添加相应字体数组的声明，

22 \* 然后调用XFT_CreateFont函数创建字体即可

23 \*/

24 if(hFont==NULL)

25 {

26 /\* 从本地加载(本地数组数据) \*/

27 hFont =XFT_CreateFont(GUI_DEFAULT_FONT); /*ASCii字库,20x20,4BPP抗锯齿*/

28 /\* 中文字库存储占用空间非常大，不推荐放在内部FLASH \*/

29 //hFont =XFT_CreateFont(GB2312_16_2BPP); /*GB2312字库,16x16,2BPP抗锯齿*/

30 //hFont =XFT_CreateFont(GB2312_20_4BPP); /*GB2312字库,20x20,4BPP抗锯齿*/

31 }

32 return hFont;

33 }

这里使用了条件编译，只有打开GUI_USE_SDCARD_FONT这个宏，见代码清单 26‑7，emXGUI才会从SD卡读取字库文件。

代码清单 26‑7 GUI_USE_SDCARD_FONT宏定义（文件gui_drv_cfg.h）

1 #define GUI_USE_SDCARD_FONT 1

例程中创建了两种字体句柄，见代码清单 26‑8。默认的字体是由XFT_CreateFont函数创建的，而字体wildfire是由font_read_data_SDCARD函数从SD卡中读取的字库文件之后，调用XFT_CreateFont函数创建。

代码清单 26‑8 字体类型（文件gui_drv_cfg.h）

1 #define GUI_DEFAULT_SDCARD_FONT "0:srcdata/wildfire.xft"

2 /\* 默认内部字体数组名，USE_EXTERN_FONT为0或 外部字体加载失败时会采用的字体 \*/

3 #define GUI_DEFAULT_FONT ASCII_20_4BPP

(2) 窗口回调函数

-  WM_PAINT

代码清单 26‑9 WM_PAINT消息（文件GUI_DEMO_TextOut.c）

1 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5 RECT rc;

6 int i,t,y;

7 WCHAR wbuf[128];

8

9 GetClientRect(hwnd,&rc);

10

11 hdc =BeginPaint(hwnd,&ps); //开始绘图

12

13 ////用户的绘制内容...

14 SetTextColor(hdc,MapRGB(hdc,10,10,100));

15 t=GUI_GetTickCount();

16 y=24;

17 i=0;

18 while(y<rc.h)

19 {

20 if(i == 11)//11行的后面使用wildfire字体文件

21 {

22 old_hfont = SetFont(hdc, hFont_SDCARD);

23 }

24 TextOut(hdc,10,y,L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",-1);

25 y+=20;

26

27 i++;

28 }

29 t =GUI_GetTickCount()-t;

30

31 SetTextColor(hdc,MapRGB(hdc,250,10,10));

32 SetFont(hdc, old_hfont);

33 if(rc.w < 300)

34 {

35 x_wsprintf(wbuf,L"Time:%dms; %.1fms/line",t,(float)t/(float)i);

36 }

37 else

38 {

39 x_wsprintf(wbuf,L"TextOut Time used:%dms; %.1fms/line",t,(float)t/(float)i);

40 }

41 TextOut(hdc,10,4,wbuf,-1);

42 EndPaint(hwnd,&ps); //结束绘图

43 break;

44 }

WM_PAINT消息中，在客户区显示多行文字，内容为： “0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ”，使用宽字符型字符串。我们使用的字体高是20，所以使每行的文本的起点y坐标偏移20个像素。前11行，使用默认字体（ASCII_20_4BPP）显示文字，后面的所有行，使
用wildfire的字体格式。调用SetFont函数，hFont_SDCARD作为参数，实现字体的切换，同时将旧字体句柄存放在old_hfont中。显示消耗时间的文字使用默认字体进行显示，也就是调用SetFont函数，字体句柄选择旧字体句柄old_hfont。这样就可以实现一个窗口有两种文字格式的显
示。

最后，将GUI_DEMO_TextOutEX函数添加到GUI_AppMain函数中即可。

.. _实验结果-12:

实验结果
''''

实验结果如图 26‑17 实验结果所示，图 26‑17 实验结果的处使用的是ASCII_20_4BPP字体，处使用的是wildfire字体。

|docx132|

图 26‑17 实验结果

如何制作APP图标
---------

学会了如何制作字库后，制作APP图标就简单多了。只需要一个应用软件FontCreator，就可以做出各种各样的图标，如图 27‑1 APP图标。这是我们这一章的实验要求，下面以野火的logo为例，教大家怎么使用FontCreator这个工具。

|docx133|

图 27‑1 APP图标

工具使用方法
~~~~~~

FontCreator.exe位于例程目录\emxgui\tools\FontCreator_ha中，如图 27‑2，框框处就是我们的主角FontCreator。

|docx134|

图 27‑2文件路径

双击FontCreator，运行软件，软件的界面图如图 27‑3。

|docx135|

图 27‑3软件界面

下面我们开始创建我们的APP图标：

1. 新建一个tft文件

..

   在文件->新建，选择新建一个字体文件，命名为firelogo，然后点击“确定”，操作流程如图 27‑4。

   |docx136|

图 27‑4 新建文件

2. 选择替换的字符编码

所谓的APP图标，只是将该字库的某个字符编码替换为我们的图标，假如我们将A换成某个图标，当我们使用这个字库，显示字符A，就会显示我们的图标。我们切换会普通的字库，字符A就还是字符 A。下面我们将 A替换为野火的logo，双击图 27‑5的框框处，会出现一个新的界面，如图 27‑6。

|docx137|

图 27‑5 选择替换的字符 A

|docx138|

图 27‑6字符A的界面

|docx139|

图 27‑7 字体的设置

图 27‑7的处，用来设置字体的宽度，我们在设计的时候，尽量使每个图标都是等宽的。处是我们图标的设计区，从WinAscent到WinDescent。如果设计的图标超过这两条边线，则超出的部分不会显示，在设计图标的时候，最好使图标位于处的中间。

FontCreator提供两种设计方式：有图片加载方式以及手动绘制，图 27‑8的处是图片加载，支持多种格式，包括.gif，.jpg，.png，.ai等格式 ；处是手工绘制。这里就不讲手动绘制了，有兴趣的，绘画功底强的读者，可以尝试一下第二种绘制方式。

|docx140|

图 27‑8 绘制方式

点击图 27‑8的处，选择野火的logo，如图 27‑9所示，这里使用的是.ai格式的文件。（这里也可以选择一张普通格式的图片，没有什么影响）

|docx141|

图 27‑9 选择图标

打开之后，如图 27‑10所示，之后，我们就需要调整图标的位置，大小，使它位于WinAscent到WinDescent之间，调整后的结果如图 27‑11所示，图标位于两个阴影区域的交界区。

|docx142|

图 27‑10 选中图标

|docx143|

图 27‑11 调整之后的结果

点击图 27‑12的处，回到最开始的界面，我们可以看到A字符变成野火的logo了。这就说明我们的制作完成了。

|docx144|

图 27‑12 完成制作

3. 保存字库

点击图 27‑13的处，保存字库，在处选择保存的路径，最后点击“保存”按键保存。

|docx145|

图 27‑13 保存字库

4. 测试生成的字体

我们可以在电脑上使用刚刚生成的字体，具体的操作方法：双击刚刚生成的firelogo.ttf文件，安装该字体，如图 27‑14。

|docx146|

图 27‑14 安装字体

打开一个新建的word文档，在字体设置处，选择firelogo，然后输入A，就可以打出野火的logo了，是不是很神奇，如图 27‑15。

|docx147|

图 27‑15 测试结果

到此为止，制作APP图标就结束了。利用上一章的软件和方法，将刚刚生成的字体制作成emXGUI支持的格式xft即可。这样，我们就可以在emXGUI上使用我们刚刚的图标字体，下面我们一起学习如何在emXGUI上显示刚刚制作完成的图标。

显示APP图标实验
~~~~~~~~~

在emXGUI上显示APP图标，实际上就是切换到字体类型，然后显示图标对应的字符。使用的函数API与上一章相同。实验的设计要求如图 27‑16。处使用的是logo字体，主要为野火的图标；处为控制图标字体，是常见的一些图标，例如返回，上翻，下翻，保存等图标；处使用的图标字体。

|docx148|

图 27‑16 设计要求

.. _代码分析-22:

代码分析
^^^^

(1) 创建字体句柄

代码清单 27‑1 三种字体类型（文件gui_font_port.c）

1 #if(GUI_ICON_LOGO_EN)

2 /\* logo字体 \*/

3 HFONT logoFont =NULL;

4 /\* 图标字体 \*/

5 HFONT iconFont =NULL;

6 /\* 控制图标字体 \*/

7 HFONT controlFont =NULL;

8 #endif

创建三种字体类型，用来存放字体句柄。

代码清单 27‑2创建字体句柄（文件gui_font_port.c）

1 /*\*

2 \* @brief GUI默认字体初始化

3 \* @param 无

4 \* @retval 返回默认字体的句柄

5 \*/

6 HFONT GUI_Default_FontInit(void)

7 {

8 //省略一些代码

9 #if(GUI_ICON_LOGO_EN)

10 /\* 创建logo字体 \*/

11 logoFont = XFT_CreateFont(GUI_LOGO_FONT);

12 /\* 创建图标字体 \*/

13 iconFont = XFT_CreateFont(GUI_ICON_FONT);

14 /\* 创建控制图标字体 \*/

15 controlFont = XFT_CreateFont(GUI_CONTROL_FONT);

16

17 if(logoFont==NULL)

18 GUI_ERROR("logoFont create failed");

19

20 if(iconFont ==NULL)

21 GUI_ERROR("iconFont create failed");

22

23 if(controlFont ==NULL)

24 GUI_ERROR("controlFont create failed");

25 #endif

26

27 return defaultFont;

28 }

GUI_Default_FontInit函数中，调用XFT_CreateFont函数来创建字体，GUI_LOGO_FONT、GUI_ICON_FONT以及GUI_CONTROL_FONT是我们使用bin2c软件生成的图标字体数组，以logo图标字体为例，见代码清单
27‑3。就这样我们就在emXGUI上“安装”了三种字体，需要使用什么字体，只需要调用SetFont函数即可。

代码清单 27‑3 字库数组（文件LOGO_50_4BPP.c）

1 #define GUI_LOGO_FONT LOGO_50_4BPP

2 const char LOGO_50_4BPP[]={88,70,84,0,88,71,85,73,32,70,111,110,116,0,0,0,

3 0,0,0,0,232,19,0,0,232,51,0,0,64,0,0,0,

4 234,4,0,0,2,0,4,0,50,0,50,0,4,0,0,0,

5 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

6 0,42,0,0,25,4,0,0,0,0,0,0,0,0,0,0,

7 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

8 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

9 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

10 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

11 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

12 0,0,0,0,0,0,0,0,0,0,0,0,0,0,

(2) 窗口回调函数

-  WM_PAINT

代码清单 27‑4 WM_PAINT消息（文件GUI_DEMO_LogoIconFont.c）

1 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5

6 RECT rc0;

7

8 hdc =BeginPaint(hwnd,&ps);

9

10 ////用户的绘制内容...

11 GetClientRect(hwnd,&rc0);

12 SetPenColor(hdc,MapRGB(hdc,200,200,220));

13 SetTextColor(hdc,MapRGB(hdc,250,250,250));

14 /\* 使用图标字体*/

15 SetFont(hdc, logoFont);

16 DrawText(hdc,L" A B C ",-1,&rc0,DT_LEFT);

17 /\* 使用控制图标字体*/

18 SetFont(hdc, controlFont);

19 SetTextColor(hdc,MapRGB(hdc,0,0,0));

20 rc0.y += 80;

21 DrawText(hdc,L" A B C D E F G H \\r\n I J K L M N O P",-1,&rc0,DT_LEFT);

22 /\* 使用图标字体*/

23 SetFont(hdc, iconFont);

24 SetTextColor(hdc,MapRGB(hdc,238,142,0));

25 rc0.y += 120;

26 DrawText(hdc,L" A B C D E ",-1,&rc0,DT_LEFT);

27

28 SetTextColor(hdc,MapRGB(hdc,100,149,237));

29 rc0.y += 120;

30 DrawText(hdc,L" F G H I J",-1,&rc0,DT_LEFT);

31 /\* 恢复默认字体 \*/

32 SetFont(hdc, defaultFont);

33 SetTextColor(hdc,MapRGB(hdc,250,250,250));

34

35 EndPaint(hwnd,&ps);

36 break;

37 }

由于图标实际上就是字符，所以颜色受TextColor的影响，调用SetTextColor函数来选择图标的颜色，logoFont字体中的内容如图 27‑17所示。调用SetFont函数切换字体，使用DrawText函数来显示A B C对应的图标。

|docx149|

图 27‑17 logoFont字体

controlFont字体中的内容如图 27‑18， 图标是从字符A到P，设置图标的颜色为RGB(0,0,0)，调用DrawText显示字符串“A B C D E F G H \\r\n I J K L M N O P”，就可以显示相应的图标。

|docx150|

图 27‑18 控制图标字体

iconFont字体中的内容如图 27‑19，使用RGB(238,142,0)的颜色来显示头五个图标，矩形变量用来控制显示的位置，调用DrawText函数来显示前五个字符。设置颜色为RGB(100,149,237)，显示后五个字符，起点的y坐标偏移120个像素。

|docx151|

图 27‑19 图标字体

-  WM_ERASEBKGND

代码清单 27‑5 WM_ERASEBKGND消息（文件GUI_DEMO_LogoIconFont.c）

1 case WM_ERASEBKGND:

2 {

3 HDC hdc=(HDC)wParam;

4

5 GetClientRect(hwnd,&rc);

6 SetBrushColor(hdc,MapRGB(hdc,215,61,50));

7 FillRect(hdc,&rc);

8 return TRUE;

9 }

使用FillRect来绘制客户区的背景，颜色调用SetBrushColor函数来设置，此处为RGB(215,61,50)，最后要返回TRUE，这样在WM_PAINT消息，才不会重绘客户区背景。

最后，将GUI_DEMO_LogoIconFont函数添加到AppMain函数中。

.. _实验结果-13:

实验结果
^^^^

|docx152|

图 27‑20 实验结果

显示矢量字体
------

矢量字体(Vector font)的每一个字是通过数学关系来描述的，因此字体可以任意缩放而不变形、变色。矢量字体文件的后缀为.ttf，我们制作字库章节选择文件就是矢量字体。还有一种叫点阵字体，后缀是.fon，这种字体并不是以矢量描述的，放大以后会出现锯齿，如图 28‑1。

|docx153|

图 28‑1 点阵字体与矢量字体

我们以“火”字为例，给大家介绍一下，矢量字体的原理。

|docx154|

图 28‑2 “火”字

一个字可以使用多条线段来表示，对于这些线段，我们只需要保存它的端点值，如图 28‑2的白色空心圆所示，当我们想要显示某个字时，就取出这些关键点，通过贝塞尔曲线将这些点的坐标连接起来，最后进行填充。放大或缩小字体的时候，只需要按比例缩放改变这些端点值的相对位置就可以了。

前面我们提到在TTF文件中，每个字符都是以一系列的点存放的，其中有一些点是控制点，利用这些控制点来实现绘制抛物线的功能，如图 28‑3所示，p1是控制点，c1、c2是曲线的端点，因此曲线可以用下面的公式进行描述，这描述方式就是贝塞尔曲线。

:math:`p\left( t \right) = \ \left( 1 - t \right)^{2}p_{0}\  + \ 2t\left( 1 - t \right)p_{1}\  + \ t^{2}p_{2}\ ` （0 < t < 1 ）

|docx155|

图 28‑3 点绘制线

回过头，看图 28‑4，方框处是不是和上面说的原理是一样的，空心的点是线段的端点，实心的点是控制点，利用贝塞尔曲线，描绘出字体的轮廓，最后在进行黑色填充，就完成了。

|docx156|

图 28‑4 “火”

TTF文件格式
~~~~~~~

上面就是有关矢量字体是如何实现的。下面我们看一下ttf的文件内容，使用WinHex软件打开某个ttf文件，如\ **错误!未找到引用源。**\ 所示。

|docx157|

图 28‑5 文件内容

在讲解文件内容之前，需要先了解一下ttf文件使用的数据类型，见下表。

表格 28‑1 ttf文件的数据类型

============ ========================================
数据类型     描述
============ ========================================
shortFrac    16位有符号小数
Fixed        固定值，常用于版本号
Fword        16位有符号整型
uFWord       16位无符号整型
F2Dot14      16位带符号的固定值类型，低14位表示分数。
longDateTime 带符号的64位整数
============ ========================================

文件目录
^^^^

字体目录，是字体文件的第一个表，提供访问其他表中所需的信息。该目录由两部分组成：偏移子表和表目录。偏移子表记录字体中表的数量，并提供偏移信息，以便快速访问目录表。表目录由一系列表组成，每个表对应一个字体。

字体目录TableDirectory的c语言定义，见代码清单 28‑1。

代码清单 28‑1 TableDirectory结构体

1 typedef struct

2 {

3     Fixed sfntversion; //字体格式的版本号

4     USHORT numTables; //表的数目

5     USHORT searchRange; //快速搜索的范围

6     USHORT entrySelector; //搜索循环迭代次数

7     USHORT rangeShift; //范围偏移量

8     TableEntry entries[1];//数据表

9 }TableDirectory;

1) sfntversion：该参数用来确定从字体中提取字体的轮廓，对于矢量字体，在Windows操作系统下， 其值必须为0x00010000。

2) numTables：记录了表的个数；

3) searchRange：记录快速搜索的范围，起始位置为表的开头；

4) entrySelector：记录循环迭代的次数，即经过多少次循环后，可以将目标表项所在范围缩小二分之一。

5) rangeShift：快速搜索范围的偏移量，其值等于表的个数numTables减去快速搜索的范围值searchRange。

以上成员都是属于偏移子表的内容，假设某个TTF文件它共有800个表，searchRange的值为500，那么rangeShift的值等于300。当我们搜索某一个目标表项时，如果它的值小于300，就从表的开头开始搜索。它大于300，则直接从rangeShift处开始搜索。

6) entries：可变长度的TableEntry类型结构的数组，用于存放各种数据表，组成表目录，目录中的条目必须按标签按升序排序。见代码清单 28‑2。

代码清单 28‑2 TableEntry结构体

1 typedef sturct

2 {

3     char tag[4];

4     ULONG checkSum;

5     ULONG offset;

6     ULONG length;

7 }TableEntry;

1) tag：4个字节标识符，用来说明资源的类型；

2) checkSum：该表的校验和；

3) offset：偏移量；

4) length：该表的长度，以字节为单位。

TTF文件子表
^^^^^^^

表格 28‑2 标签tag类型——必选

====== ==============================
标识符 相关描述
====== ==============================
cmap   字符编码到字形数据的映射
glyf   字形数据
head   字体头，包含有关字体的全局信息
hhea   整个字体的一般信息
hmtx   水平参数
loca   存储字符的偏移量
maxp   字体的内存要求
name   名称表
post   打印的相关信息
====== ==============================

1. head

表格 28‑3 head表

============ ================== ============================================================================
数据类型     名字               描述
============ ================== ============================================================================
固定值       version            字体版本号，设置为0x00010000
固定值       fontRevision       修订版本号，由字体制造商决定
UINT32       checkSumAdjustment head表校验和的调节量，'head'表的计算校验和是错误的，需要用0xB1B0AFBA减去该值
UINT32       magicNumber        默认为0x5F0F3CF5
UINT16       flags              用来设置与字体有关的参数值
UINT16       unitsPerEm         每个EM正方形的单位font unit，范围从64到16384，字体设计人员设置
longDateTime created            international date
longDateTime modified           international date
FWORD        xMin               字体的x坐标最小值
FWORD        yMin               字体的y坐标最小值
FWORD        xMax               字体的x坐标最大值
FWORD        yMax               字体的y坐标最大值
UINT16       macStyle           第0位表示粗体

                                第1位表示斜体

                                第2位表示下划线

                                第3位表示大纲

                                第4位表示阴影

                                第5位表示浓缩（窄）

                                第6位表示扩展 UINT16       lowestRecPPEM      最小可读像素大小 INT16        fontDirectionHint  字体方向：

                                1：从左到右

                                -1：从右到左 INT16        indexToLocFormat   代表loca表的索引中使用的偏移格式的类型，0 为short型, 1为long型 INT16        glyphDataFormat    字形数据格式 ============
                                ================== ============================================================================

head表记录了字体版本号，创建和修改日期，修订号以及适用于整个字体的基本印刷数据等信息。xMin，yMin，xMax和yMax指定一个矩形EM，EM是字体设计者假想的矩形，是字体中所有字形的边界框。

2. cmap

camp表将字符编码（如Unicode编码）相应地转换为内部的字符ID。微软和MAC使用不同的编码，因此，camp表可以有多个映射表，每个映射表支持一种编码方案，图 28‑6，是cmap表的部分内容。

|docx158|

图 28‑6 cmap表

表格 28‑4 cmap表

======== ======== ================== ===========================
\        数据类型 名字               描述
======== ======== ================== ===========================
索引     UINT16   version            版本号，默认是0
\        UINT16   numberSubtables    编码子表的数量
编码子表 UINT16   platformID         平台标识符（微软-3；MAC-1）
\        UINT16   platformSpecificID 针对平台特定的编码标识符
\        UINT32   offset             映射表的偏移量
======== ======== ================== ===========================

不同的平台标识符，使用不同的编码标识符。Platform ID为0，代表unicode版本；为1，则是MAC；为3，表示微软公司。2是保留，未使用。

表格 28‑5 camp 各平台的特殊标识符

========== ================== ==================
platformID platformSpecificID 描述
========== ================== ==================
0          0                  默认参数
\          1                  版本1.1
\          2                  ISO 160646 1993
\          3                  Unicode 2.0（BMP）
\          4                  Unicode 2.0
\          5                  Unicode变体序列
\          6                  支持所有的Unicode
3          0                  符号
\          1                  UCS-2
\          2                  Shift_JIS
\          3                  PRC
\          4                  BigFive
\          5                  Johab
\          10                 UCS-4
========== ================== ==================

注：我们常用的emoji表情实际就是一种Unicode变体序列，它是由一个基准字符加256 个变体选择符组成，如图 28‑7 emoji编码。

|docx159|

图 28‑7 emoji编码

‘cmap’子表有九种可用的格式：格式0，格式2，格式4，格式6，格式8.0，格式10.0，格式12.0，格式13.0和格式14。

格式0用于支持MAC设备的映射关系。格式2用于日语，中文和韩语的映射。 格式4用于16位映射。 格式6用于十六进制16位映射。格式8，10和12，13和14支持使用Unicode 2.0及更高版本中的代理编码的文本。以最简单的格式0为例，这里主要介绍一下映射关系，其他格式，感兴趣的话，可以查阅《》

格式0主要用于字符编码和字形ID都是单个字节的字体，格式如表格 28‑6.

表格 28‑6 格式0

======== ===================== ============================================
数据类型 变量名                描述
======== ===================== ============================================
UINT16   格式                  设为0，使用的格式0
UINT16   长度                  子表的长度，以字节为单位，对于格式0，为262。
UINT16   语言                  只适用于MAC设备
UINT8    glyphIndexArray [256] 字符编码映射到字符ID的数组
======== ===================== ============================================

3. glyf

TTF文件的字体轮廓是用点和特定的数学关系生成的特定曲线。例如，字母i，分别是上面的圆点，和剩下的下半部分。glyf表中包含文字外观的数据，包括描述构成字形轮廓的点的说明和该字形网格拟合的指令。每个字符的外形都是由字符id决定，而字符ID是由cmap表来决定的。

表格 28‑7 glyf表

=============================== =======================================================================
名字                            详细描述
=============================== =======================================================================
numberOfContours                该值为正或零，则为单个字形；小于0，则为复合类型，即由其他字形组成的字形
xMIN                            字体边界x坐标最小值
yMIN                            字体边界y坐标最小值
xMAX                            字体边界x坐标最大值
yMAX                            字体边界y坐标最大值
endPtsOfContours [n]            存放每个轮廓的最后几个点的数组：n是轮廓的数量；数组条目是点ID值
instructionLength               指令所需的总字节数
instructions[instructionLength] 此字形的指令数组
flags[variable]                 标志数组
xCoordinates []                 x坐标数组; 第一个是相对于（0,0），其他是相对于前一个点
yCoordinates []                 y坐标数组; 第一个是相对于（0,0），其他是相对于前一个点
=============================== =======================================================================

表格 28‑7 指定了简单字形的格式。其中flag参数如表格 28‑8。

表格 28‑8 flag组参数

========== ============== ======================================================================
位（bits） 标志           描述
========== ============== ======================================================================
0          曲线上的点     为1，则在曲线上；为0，则不在
1          X坐标的字节数  1——1个字节

                          0——2个字节 2          Y坐标的字节数  1——1个字节

                          0——2个字节 3          重复次数       1——下一个字节指定重复该组标志的次数 4，5       X，Y的坐标长度 如果1（2）2位未设置，而4（5）位置1，则当前的x（y）坐标与前一个坐标相同 6，7       保留           设为0 ==========
                          ============== ======================================================================

4. hhea

'hhea'表包含布置字体水平书写字体所需的信息，即从左到右或从右到左。

表格 28‑9 hhea表

====== =================== ========================================================
类型   名称                描述
====== =================== ========================================================
固定值 版本号              设置为0x00010000
FWord  ascent              距离基线的最高距离
FWord  descent             距离基线的最低距离
FWord  lineGap             印刷线间隙
uFWord advanceWidthMax     必须与hmtx一致
FWord  minLeftSideBearing  必须与hmtx一致
FWord  minRightSideBearing 必须与hmtx一致
int16  caretSlopeRise      用于计算垂直插入符号的插入符号（上升/运行）的斜率设置为1
int16  caretSlopeRun       0表示垂直
FWord  caretOffset         对于非倾斜字体，将值设置为0
int16  保留值              将值设置为0
int16  保留值              将值设置为0
int16  保留值              将值设置为0
int16  保留值              将值设置为0
int16  metricDataFormat    0表示当前格式
uint16 numOfLongHorMetrics 指标表中的提前宽度数
====== =================== ========================================================

该表以版本号开头，ascent，descent和lineGap的值表示单个字形不可以超出的范围。 advanceWidthMax，minLeftSideBearing和minRightSideBearing分别表示最大前进宽度，最小的左侧方位以及最小的右侧方位，与‘hmtx’表一致。

|docx160|

图 28‑8 基准线

5. hmtx

‘hmtx’表包含字体中每个字形的水平布局的度量信息，即前进宽度和左侧方位。从字形的当前点到最左边点的水平距离，称为左侧方位。在绘制字体时候，为了方便确定下一个字体的位置，使用前进宽度，即当前点移动的水平距离作为下个字体的起点。

表格 28‑10 hmtx表

=================== ============================= ============================================================================
类型                名称                          描述
=================== ============================= ============================================================================
longHorMetric结构体 hMetrics[numOfLongHorMetrics] 值numOfLongHorMetrics来自‘hhea’表。如果字体等宽，则numOfLongHorMetrics的值为
FWord               leftSideBearing[]             用于等宽字体，数组长度等于字形总数减去numOfLongHorMetrics
=================== ============================= ============================================================================

代码清单 28‑3 longHorMetric结构体

1 struct {

2 uint16 advanceWidth;

3 int16 leftSideBearing;

4

5 }

更改前进宽度，会改变每个字的间距，而改变左侧方位，则会改变单个字体的位置，相对于字体边界矩形而言，见图 28‑9。

|docx161|

图 28‑9 前进宽度与左侧方位

6. loca

‘loca’表用于存储字体相对于glyf表开头的偏移量，方便查找某个字体，例如，在MAC标准字符排序中，字符A是第76个字符。偏移的大小取决于使用的格式。这在字体标题（ 'head' ）表中的indexToLocFormat参数进行指定 。

表格 28‑11 loca表内容示例

====== ====== ========
字符ID 偏移量 字形长度
====== ====== ========
0      0      100
1      100    150
2      250
…
n-1    1170   120
N      1290
====== ====== ========

7. maxp

‘maxp’表用来确定了字体的内存要求，以便在出来字体前分配合适大小的内存。

====== ===================== ===========================================
类型   名称                  描述
====== ===================== ===========================================
固定值 版本号                设置为0x00010000
UINT16 numGlyphs             字体中的字形数
UINT16 maxPoints             非复合字形中的点最大值
UINT16 maxContours           非复合字形轮廓最大值
UINT16 maxComponentPoints    复合字形中的点最大值
UINT16 maxComponentContours  复合字形轮廓最大值
UINT16 maxZones              设为2
UINT16 maxTwilightPoints     在Z0中使用的点
UINT16 maxStorage            存储区的数量
UINT16 maxFunctionDefs       函数数量
UINT16 maxInstructionDefs    指令数量
UINT16 maxStackElements      最大堆栈深度
UINT16 maxSizeOfInstructions 字形指令的字节数
UINT16 maxComponentElements  字形指令的字节数
UINT16 maxComponentDepth     递归级别，如果字体只有简单的字形，则设置为0
====== ===================== ===========================================

8. name

name表包含名称，版权声明，字体名称，样式名称以及与字体相关的其他信息。

表格 28‑12 name表

======== ================= ==================================
类型     名称              描述
======== ================= ==================================
UINT16   format            格式选择器，一般设为0。
UINT16   count             nameRecord的个数
UINT16   stringOffset      以字节为单位偏移到名称字符串的开头
UINT16   nameRecord[count] 名称记录数组
变量类型 name              字符串
======== ================= ==================================

nameRecord数组记录六个信息，分别是平台ID、特定平台的编码ID、语言ID、名称ID、名称字符串长度以及名字字符串的偏移量。

语言ID定义了为nameRecord数组中名称字符串的语言，下表仅列出部分：

表格 28‑13 语言ID

======== ==================== ======== ====================
语言ID值 语言                 语言ID值 语言
======== ==================== ======== ====================
0        英语                 59       普什图语
1        法国                 60       Kurdish
2        德国                 61       克什米尔
3        意大利               62       Sindhi
4        荷兰                 63       藏语
5        瑞典                 64       尼泊尔
6        西班牙语             65       梵语
…
57       蒙古语（蒙古语）     149      格陵兰
58       蒙古语（西里尔文字） 150      阿塞拜疆（罗马文字）
======== ==================== ======== ====================

nameID 记录名称字符串相关的描述。编号0到19是预定义的。编号20到255是保留的。编号256到32767保留用于变体，nameID ID在下表中给出部分值：

表格 28‑14 nameID

========= ================
ID值      描述
========= ================
0         版权声明
1         字体系列
……
20~22     由OpenType定义。
23~255    保留
256~32767 用于变体
========= ================

假如nameID 的值为1，且name的值为“黑体”，则表示该字体属于黑体。

9. post

post表包含在打印机上使用TrueType字体所需的信息，还包含FontInfo字典条目所需的数据以及字体中所有字形的PostScript名称，以及PostScript驱动程序进行内存管理所需的内存使用信息。

表格 28‑15 post表

====== ================== ====================================================
类型   名称               描述
====== ================== ====================================================
固定值 Format             post表的格式
固定值 italicAngle        斜体角度
FWord  underlinePosition  下划线位置
FWord  underlineThickness 下划线厚度
uint32 isFixedPitch       字体是等宽的; 如果字体是等宽的则设置为1，否则设置为0
uint32 minMemType42       将TrueType字体作为Type 42字体下载时的最小内存使用量
uint32 maxMemType42       将TrueType字体作为Type 42字体下载时的最大内存使用量
uint32 minMemType1        将TrueType字体作为Type 1字体下载时的最小内存使用量
uint32 maxMemType1        将TrueType字体作为Type 1字体下载时的最大内存使用量
====== ================== ====================================================

下面列出的这些表都是可选的表格，简单了解一下即可。

10.
cvt

一些带有指令的字体可以使用该表，它包含一系列可通过指令访问的Fwords类型数组。

表格 28‑16 cvt表

===== ================ ================
类型  变量名           描述
===== ================ ================
FWORD controlValues [] 通过指令访问数组
===== ================ ================

11.
fpgm

首次使用字体时会执行一次该表的指令列表的所有指令，主要用来定义在不同字形程序使用的函数。

表格 28‑17 fpgm表

===== ============== ========
类型  名称           描述
===== ============== ========
UINT8 instructions[] 指令数组
===== ============== ========

12.
OS/2

“OS / 2”表提供了控制Windows 中行间距的字体范围指标，字体的样式和重量以及其整体外观。

表格 28‑18 OS/2表

================ =================== =======================================================================================================================================
类型             名称                描述
================ =================== =======================================================================================================================================
UINT16           版本号              当前表版本号（设置为0）
INT16            xAvgCharWidth       小写字母和空格的平均加权前进宽度
UINT16           usWeightClass       字形中的笔画粗细：

                                     1——超细

                                     2——特细

                                     …

                                     8——特粗体

                                     9——超大体 UINT16           usWidthClass        字体设计者为字体中的字形指定的正常宽高比（宽高比）的相对变化 INT16            fsType              2字节的位段。目前只定义1位，其余位为0.
                                     上下标的相关参数 INT16            ySubscriptXSize     下标的推荐水平尺寸（以像素为单位） INT16            ySubscriptYSize     下标的建议垂直大小（以像素为单位） INT16
                                     ySubscriptXOffset   下标的推荐水平偏移量 INT16            ySubscriptYOffset   建议的垂直偏移量构成下标的基线 INT16            ySuperscriptXSize   上标的推荐水平尺寸（以像素为单位） INT16
                                     ySuperscriptYSize   上标的建议垂直大小（以像素为单位） INT16            ySuperscriptXOffset 建议上标的水平偏移量 INT16            ySuperscriptYOffset 建议垂直偏离基线的上标 删除线的相关参数 INT16
                                     yStrikeoutSize      删除线的宽度 INT16            yStrikeoutPosition  删除线与基准线的偏差 INT16            sFamilyClass        字体所属分类 PANOSE           panose
                                     变体 UINT32           ulCharRange [4]     32位无符号长数组，被分成两个位字段，每个字段分别为96和32位。低96位用于指定字体文件包含的Unicode块，高32位用于指定字体文件所涵盖的字符集 INT8             achVendID [4]
                                     字体供应商的四个字符标识符 UINT16           fsSelection         2字节位字段，包含有关字体模式性质的信息，如斜体，删除线等 UINT16           fsFirstCharIndex    此字体中的最小Unicode索引 UINT16
                                     fsLastCharIndex     此字体中的最大Unicode索引 ================ ===================
                                     =======================================================================================================================================

显示字体API函数
~~~~~~~~~

表格 28‑19 API函数

======================== ======================
函数                     描述
======================== ======================
freetype_font_obj_new    创建矢量字体对象
freetype_font_obj_delete 释放矢量字体对象
freetype_font_set_size   设置矢量字体的大小参数
freetype_CreateFont      创建矢量字体句柄
======================== ======================

freetype_font_obj_new
^^^^^^^^^^^^^^^^^^^^^

freetype_font_obj_new函数用来创建矢量字体对象，用来存放ttf文件的数据，函数原型见代码清单 28‑4。

代码清单 28‑4 freetype_font_obj_new函数（文件GUI_Font_Freetype.h）

1 freetype_obj\* freetype_font_obj_new(int w,int h,int dpi_horz,int dpi_vert,const u8 \*pFontData);

1) w，h：设置字体的宽度，高度；

2) dpi_horz、dpi_vert：垂直和水平的dpi。dpi指的是屏幕一英尺显示的像素点数。某个字体的宽度为72px，高度为72px，以英尺为单位，它的宽，高都等于1英尺。

3) pFontData：ttf文件数据，通常从外部设备读取。一般的ttf文件都是超过6M，F429的SDRAM共有8M，前2M用于LCD显示屏，因此选择字库文件时，要注意文件的大小。例程中使用的字体为方正兰亭超细黑简体，大小约为1.7M。

freetype_font_obj_delete
^^^^^^^^^^^^^^^^^^^^^^^^

freetype_font_obj_delete函数用于释放ttf文件数据所使用的内存空间。函数原型见代码清单 28‑5。

代码清单 28‑5 freetype_font_obj_delete函数（文件GUI_Font_Freetype.h）

1 void freetype_font_obj_delete(freetype_obj \*ft_obj);

1) ft_obj：矢量字体对象

freetype_font_set_size
^^^^^^^^^^^^^^^^^^^^^^

freetype_font_set_size函数可以设置字体的显示大小，函数原型见代码清单 28‑6。

代码清单 28‑6 freetype_font_set_size函数（文件GUI_Font_Freetype.h）

1 BOOL freetype_font_set_size(freetype_obj \*ft,int w,int h,int dpi_horz,int dpi_vert);

1) ft：矢量字体对象，该对象是由freetype_font_obj_new生成；

2) w、h：字体显示的宽度、高度；

3) dpi_horz、dpi_vert：设置垂直、水平dpi。

freetype_CreateFont
^^^^^^^^^^^^^^^^^^^

freetype_CreateFont函数用来创建字体句柄，该函数会返回HFONT类型的变量，函数原型，见代码清单 28‑7。

代码清单 28‑7 freetype_CreateFont函数（文件GUI_Font_Freetype.h）

1 HFONT freetype_CreateFont(freetype_obj \*ft_obj);

1) ft_obj：矢量字体对象。

矢量字体实验
~~~~~~

.. _实验要求-3:

实验要求
^^^^

图 28‑10 实验要求是本章的实验要求，使用矢量字体，来显示文字。

|docx162|

图 28‑10 实验要求

.. _代码分析-23:

代码分析
^^^^

(1) 创建父窗口

代码清单 28‑8 创建父窗口（文件GUI_DEMO_TTF.c）

1 void GUI_DEMO_TTF(void)

2 {

3 HWND hwnd;

4 WNDCLASS wcex;

5 MSG msg;

6 int fsize;

7 FIL \*file;

8 FRESULT fresult;

9 UINT br;

10

11 /\* 文件句柄空间 \*/

12 file =(FIL*)GUI_VMEM_Alloc(sizeof(FIL));

13

14 /\* 打开文件 \*/

15 fresult = f_open(file, filename, FA_OPEN_EXISTING \| FA_READ );

16 GUI_DEBUG("%d",fresult);

17 fsize =f_size(file);

18 font_data_buf =(u8*)GUI_VMEM_Alloc(fsize);

19

20 if(font_data_buf!=NULL)

21 {

22 fresult = f_read(file,font_data_buf,fsize,&br); //将整个ttf文件读到内存

23 }

24 f_close(file);

25

26 if(font_data_buf==NULL)

27 { //内存不够

28 MSGBOX_OPTIONS ops;

29 const WCHAR \*btn[]={L"确定"};

30 int x,y,w,h;

31

32 ops.Flag =MB_BTN_WIDTH(60)|MB_ICONERROR;

33 ops.pButtonText =btn;

34 ops.ButtonCount =1;

35 w =300;

36 h =250;

37 x =(GUI_XSIZE-w)>>1;

38 y =(GUI_YSIZE-h)>>1;

39 MessageBox(hwnd,x,y,w,h,L"绯系统内存不足,\r\n请选择更小的字体文件...",L"消息",&ops);

40 return;

41 }

42

43 wcex.Tag = WNDCLASS_TAG;

44 wcex.Style = CS_HREDRAW \| CS_VREDRAW;

45 wcex.lpfnWndProc = WinProc; //设置主窗口消息处理的回调函数.

46 wcex.cbClsExtra = 0;

47 wcex.cbWndExtra = 0;

48 wcex.hInstance = NULL;

49 wcex.hIcon = NULL;

50 wcex.hCursor = NULL;

51

52 //创建主窗口

53 hwnd =CreateWindowEx( WS_EX_LOCKPOS, //窗口不可拖动

54 &wcex,

55 L"emxGUI矢量显示示例" , //窗口名称

56 WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,

57 0,0,GUI_XSIZE,GUI_YSIZE, //窗口位置和大小

58 NULL,NULL,NULL,NULL);

59

60 //显示主窗口

61 ShowWindow(hwnd,SW_SHOW);

62

63 //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。

64 while(GetMessage(&msg,hwnd))

65 {

66 TranslateMessage(&msg);

67 DispatchMessage(&msg);

68 }

69 GUI_VMEM_Free(font_data_buf);

70 }

在创建窗口前，调用f_open函数打开文件FZLTCXHJW.TTF，获取文件句柄，通过f_size函数得到文件的大小，同时调用GUI_VMEM_Alloc函数为字库文件数据分配空间，大小为FZLTCXHJW.TTF的大小fsize。使用f_read函数，将整个ttf文件读到内存中。这里的内存指的是
SDRAM，我们前面提到过，这个字库文件如果太大的话，会导致读取失败，这里使用一个消息框MessageBox，来通知用户。最后，使用f_close函数关闭文件。

这样，我们就完成了加载ttf文件过程。

(2) 窗口回调函数

-  WM_CREATE

代码清单 28‑9 WM_CREATE消息（文件GUI_DEMO_TTF.c）

1 case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口.

2 {

3 GetClientRect(hwnd,&rc); ////获得窗口的客户区矩形.

4 ft_obj =freetype_font_obj_new(16,16,72,72,font_data_buf); //创建一个freetype对象

5 CreateWindow(BUTTON,L"OK",WS_VISIBLE,

6 rc.w-80,8,68,32,hwnd,ID_OK,NULL,NULL); //创建一个按钮(示例).

7 return TRUE;

8 }

调用freetype_font_obj_new函数，来创建矢量字体对象。font_data_buf数组存放着字库文件的数据，这样之后，有个矢量字体的操作，都可以是该对象ft_obj。

-  WM_PAINT

代码清单 28‑10 WM_PAINT（文件GUI_DEMO_TTF.c）

1 case WM_PAINT: //窗口需要绘制时，会自动产生该消息.

2 {

3 PAINTSTRUCT ps;

4 HDC hdc;

5 HFONT hFont;

6 RECT rc0;

7

8 GetClientRect(hwnd,&rc0);

9

10 hdc =BeginPaint(hwnd,&ps); //开始绘图

11

12 ////用户的绘制内容...

13

14 hFont =freetype_CreateFont(ft_obj); //创建freetype字体

15

16 SetFont(hdc,hFont); //设置新的字体.

17

18 SetTextColor(hdc,MapRGB(hdc,10,10,10));

19

20 freetype_font_set_size(ft_obj,16,16,72,72); //设置freetype字体的大小参数

21 TextOut(hdc,10,10,L"矢量字体示例1234567890",-1);

22 SetTextColor(hdc,MapRGB(hdc,250,0,10));

23 freetype_font_set_size(ft_obj,32,32,72,72);

24 TextOut(hdc,10,30,L"矢量字体示例1234567890",-1);

25 SetTextColor(hdc,MapRGB(hdc,0,0,205));

26 freetype_font_set_size(ft_obj,64,64,72,72);

27 TextOut(hdc,10,80,L"矢量字体示例1234567890",-1);

28 SetTextColor(hdc,MapRGB(hdc, 255,255,255));

29 freetype_font_set_size(ft_obj,128,128,72,72);

30 TextOut(hdc,10,200,L"矢量字体示例1234567890",-1);

31

32

33

34 SetTextColor(hdc,MapRGB(hdc,200,50,50));

35 freetype_font_set_size(ft_obj,40,40,72,72);

36

37 rc.w =rc0.w;

38 rc.h =48;

39 rc.x =0;

40 rc.y =rc0.h-48;

41 DrawText(hdc,L"emXGUI,十年深度优化图像引擎",-1,&rc,DT_VCENTER|DT_RIGHT|DT_BORDER);

42

43 DeleteFont(hFont); //释放字体

44 EndPaint(hwnd,&ps); //结束绘图

45 break;

46 }

调用BeginPaint函数开始绘制，我们先调用freetype_CreateFont函数来创建字体句柄h
Font。在WM_CREATE消息中，创建矢量字体对象ft_obj指的是字体的数据，freetype_CreateFont函数则是利用这字体数据来创建字体句柄，这样我们才可以在emXGUI中使用。

调用SetFont函数，来设置字体为矢量字体。字体的大小可以通过freetype_font_set_size函数来修改，字体的颜色同样受TextColor的控制。显示文字，我们可以使用TextOut函数来实现。最后，调用EndPaint函数结束绘制，同时释放字体句柄。

-  WM_CLOSE

退出窗口时，需要调用函数freetype_font_obj_delete来释放矢量字体对象，如代码清单 28‑11。

代码清单 28‑11 WM_CLOSE消息

1 case WM_CLOSE: //窗口关闭时，会自动产生该消息.

2 {

3 freetype_font_obj_delete(ft_obj); //释放freetype对象

4 return DestroyWindow(hwnd); //调用DestroyWindow函数销毁窗口，该函数会使主窗口结束并退出消息循环;

5

6 }

.. _实验结果-14:

实验结果
^^^^

实验结果如图 28‑11所示，可以看到通过freetype_font_set_size函数设置字体的大小使每一行的文字都不一样。

|docx163|

图 28‑11 实验结果

第二部分 emXGUI综合例程实战
=================

音乐播放器
-----

视频播放器
-----

万年历
---

NES游戏
-----

二维码识别
-----

摄像头图像显示
-------

图片浏览器
-----

矢量字体测试
------

控件的滑动与旋转
--------

联系野火
====

**东莞野火电子技术有限公司**

官网：\ `www.embedfire.com <http://www#.embedfire.com>`__

|docx164|\ 论坛：www.firebbs.cn

淘宝：fire-stm32.taobao.com

邮箱：\ firege@embedfire.com

电话：0769-33894118

关注野火公众号，可下载野火全部产品的资料（书籍、视频、程序）

|docx165|

野火STM32系列图书，关注公众号即可下载电子版

.. |docx002| image:: media/docx002.png
   :width: 3.34328in
   :height: 3.08688in
.. |docx003| image:: media/docx003.png
   :width: 4.22388in
   :height: 3.07561in
.. |docx004| image:: media/docx004.png
   :width: 3.85821in
   :height: 2.78241in
.. |docx005| image:: media/docx005.png
   :width: 3.75373in
   :height: 2.79609in
.. |docx006| image:: media/docx006.png
   :width: 4.21642in
   :height: 3.0915in
.. |docx007| image:: media/docx007.png
   :width: 4.23896in
   :height: 2.58333in
.. |docx008| image:: media/docx008.png
   :width: 4.35943in
   :height: 2.11907in
.. |docx009| image:: media/docx009.png
   :width: 5.76806in
   :height: 3.94484in
.. |docx010| image:: media/docx010.png
   :width: 1.95833in
   :height: 2.25694in
.. |docx011| image:: media/docx011.png
   :width: 5.76806in
   :height: 1.92469in
.. |docx012| image:: media/docx012.png
   :width: 3.56698in
   :height: 1.63347in
.. |docx013| image:: media/docx013.png
   :width: 3.21382in
   :height: 2.23399in
.. |docx014| image:: media/docx014.png
   :width: 2.14185in
   :height: 2.04184in
.. |docx015| image:: media/docx015.png
   :width: 4.05671in
   :height: 3.43056in
.. |docx016| image:: media/docx016.png
   :width: 5.632in
   :height: 3.40792in
.. |docx017| image:: media/docx017.png
   :width: 4.52417in
   :height: 2.808in
.. |docx018| image:: media/docx018.jpg
   :width: 3.33333in
   :height: 3.83333in
.. |docx019| image:: media/docx019.jpeg
   :width: 3.62196in
   :height: 2.04167in
.. |docx020| image:: media/docx020.jpg
   :width: 5.76806in
   :height: 2.88403in
.. |docx021| image:: media/docx021.jpg
   :width: 5.76806in
   :height: 3.39444in
.. |docx022| image:: media/docx022.jpg
   :width: 4.00833in
   :height: 1.81667in
.. |docx023| image:: media/docx023.jpg
   :width: 5.76806in
   :height: 3.46111in
.. |docx024| image:: media/docx024.jpg
   :width: 2.92881in
   :height: 2.29167in
.. |docx025| image:: media/docx025.jpg
   :width: 0.75918in
   :height: 0.3in
.. |docx026| image:: media/docx026.jpg
   :width: 0.875in
   :height: 0.35in
.. |docx027| image:: media/docx027.jpg
   :width: 0.72941in
   :height: 0.3in
.. |docx028| image:: media/docx028.jpg
   :width: 5.54017in
   :height: 3.05757in
.. |docx020| image:: media/docx020.jpg
   :width: 5.76806in
   :height: 2.88403in
.. |docx029| image:: media/docx029.jpg
   :width: 5.76806in
   :height: 1.33472in
.. |docx030| image:: media/docx030.jpg
   :width: 4in
   :height: 1.84167in
.. |docx031| image:: media/docx031.jpg
   :width: 5.76806in
   :height: 3.45972in
.. |docx024| image:: media/docx024.jpg
   :width: 2.92881in
   :height: 2.29167in
.. |docx032| image:: media/docx032.jpg
   :width: 3.40833in
   :height: 1.51667in
.. |docx033| image:: media/docx033.jpg
   :width: 5.00284in
   :height: 2.81463in
.. |docx034| image:: media/docx034.jpg
   :width: 5.00394in
   :height: 2.81223in
.. |docx024| image:: media/docx024.jpg
   :width: 2.92881in
   :height: 2.29167in
.. |docx035| image:: media/docx035.jpg
   :width: 4.025in
   :height: 1.64167in
.. |docx036| image:: media/docx036.jpg
   :width: 4.875in
   :height: 2.73742in
.. |docx037| image:: media/docx037.jpg
   :width: 4.87402in
   :height: 2.73687in
.. |docx038| image:: media/docx038.jpg
   :width: 4.00833in
   :height: 2in
.. |docx039| image:: media/docx039.jpg
   :width: 4.00833in
   :height: 2in
.. |docx040| image:: media/docx040.jpg
   :width: 5.03141in
   :height: 3.01667in
.. |docx041| image:: media/docx041.jpg
   :width: 5.76806in
   :height: 0.93611in
.. |docx042| image:: media/docx042.jpg
   :width: 5.45833in
   :height: 2.8in
.. |docx043| image:: media/docx043.jpg
   :width: 4.01667in
   :height: 2.15833in
.. |docx044| image:: media/docx044.jpg
   :width: 5.56523in
   :height: 3.125in
.. |docx045| image:: media/docx045.jpg
   :width: 4.51042in
   :height: 1.30208in
.. |docx046| image:: media/docx046.jpg
   :width: 4.025in
   :height: 2.61667in
.. |docx047| image:: media/docx047.jpg
   :width: 4.37598in
   :height: 2.475in
.. |docx048| image:: media/docx048.jpg
   :width: 5.76806in
   :height: 4.58194in
.. |docx049| image:: media/docx049.jpg
   :width: 0.325in
   :height: 4.375in
.. |docx050| image:: media/docx050.jpg
   :width: 3.975in
   :height: 0.375in
.. |docx051| image:: media/docx051.jpg
   :width: 3.98333in
   :height: 1.7in
.. |docx052| image:: media/docx052.jpg
   :width: 4.225in
   :height: 2.45in
.. |docx053| image:: media/docx053.jpg
   :width: 2.89167in
   :height: 2.81667in
.. |docx054| image:: media/docx054.jpg
   :width: 5.76806in
   :height: 3.25347in
.. |docx055| image:: media/docx055.jpg
   :width: 1.025in
   :height: 0.75833in
.. |docx056| image:: media/docx056.jpg
   :width: 4.675in
   :height: 0.55in
.. |docx057| image:: media/docx057.jpg
   :width: 5.76806in
   :height: 1.78889in
.. |docx058| image:: media/docx058.jpg
   :width: 4.15in
   :height: 2.725in
.. |docx059| image:: media/docx059.jpg
   :width: 5.76806in
   :height: 1.65486in
.. |docx060| image:: media/docx060.jpg
   :width: 2.25833in
   :height: 1.85in
.. |docx061| image:: media/docx061.jpg
   :width: 4.90833in
   :height: 2.75082in
.. |docx062| image:: media/docx062.png
   :width: 2.20459in
   :height: 5.05217in
.. |docx063| image:: media/docx063.png
   :width: 2.24051in
   :height: 2.98735in
.. |docx064| image:: media/docx064.png
   :width: 5.76806in
   :height: 4.02569in
.. |docx063| image:: media/docx063.png
   :width: 2.24051in
   :height: 2.98735in
.. |docx065| image:: media/docx065.png
   :width: 5.76806in
   :height: 1.21597in
.. |docx066| image:: media/docx066.png
   :width: 3.48693in
   :height: 1.96472in
.. |docx067| image:: media/docx067.png
   :width: 4.62943in
   :height: 5.57582in
.. |docx068| image:: media/docx068.png
   :width: 5.76806in
   :height: 2.50903in
.. |docx069| image:: media/docx069.png
   :width: 5.76806in
   :height: 2.95694in
.. |docx070| image:: media/docx070.png
   :width: 2.02454in
   :height: 3.26456in
.. |docx071| image:: media/docx071.png
   :width: 5.9957in
   :height: 3.1913in
.. |docx072| image:: media/docx072.png
   :width: 3.97937in
   :height: 3.08003in
.. |docx073| image:: media/docx073.png
   :width: 3.71093in
   :height: 2.84775in
.. |docx074| image:: media/docx074.png
   :width: 3.79932in
   :height: 4.23478in
.. |docx075| image:: media/docx075.png
   :width: 4.34783in
   :height: 6.2313in
.. |docx076| image:: media/docx076.png
   :width: 4.10277in
   :height: 3.11386in
.. |docx077| image:: media/docx077.png
   :width: 2.79132in
   :height: 0.61451in
.. |docx078| image:: media/docx078.png
   :width: 1.86739in
   :height: 2.48985in
.. |docx079| image:: media/docx079.png
   :width: 2.04345in
   :height: 5.13913in
.. |docx080| image:: media/docx080.png
   :width: 3.04348in
   :height: 2.98063in
.. |docx081| image:: media/docx081.jpg
   :width: 4.025in
   :height: 2.63333in
.. |docx082| image:: media/docx082.jpg
   :width: 5.76806in
   :height: 3.23889in
.. |docx083| image:: media/docx083.jpg
   :width: 5.76806in
   :height: 3.46111in
.. |docx084| image:: media/docx084.jpg
   :width: 4.36667in
   :height: 3.48333in
.. |docx085| image:: media/docx085.jpg
   :width: 5.76806in
   :height: 3.46111in
.. |docx086| image:: media/docx086.jpg
   :width: 1.44167in
   :height: 1.28333in
.. |docx087| image:: media/docx087.jpg
   :width: 2.78877in
   :height: 1.49167in
.. |docx088| image:: media/docx088.jpg
   :width: 4.2in
   :height: 2.29167in
.. |docx089| image:: media/docx089.jpg
   :width: 5.76806in
   :height: 3.07986in
.. |docx090| image:: media/docx090.jpg
   :width: 1.95833in
   :height: 1.14178in
.. |docx091| image:: media/docx091.jpg
   :width: 5.2593in
   :height: 3.15583in
.. |docx092| image:: media/docx092.jpg
   :width: 5.76806in
   :height: 3.07222in
.. |docx093| image:: media/docx093.jpg
   :width: 5.76806in
   :height: 3.46111in
.. |docx094| image:: media/docx094.png
   :width: 1.27762in
   :height: 2.55524in
.. |docx095| image:: media/docx095.jpg
   :width: 5.36667in
   :height: 0.83333in
.. |docx096| image:: media/docx096.jpg
   :width: 4.88333in
   :height: 1.18333in
.. |docx097| image:: media/docx097.jpg
   :width: 4.09167in
   :height: 4.125in
.. |docx098| image:: media/docx098.jpg
   :width: 4.35in
   :height: 2.04167in
.. |docx099| image:: media/docx099.jpg
   :width: 4.35in
   :height: 2.04167in
.. |docx100| image:: media/docx100.jpg
   :width: 5.76797in
   :height: 2.73472in
.. |docx101| image:: media/docx101.jpg
   :width: 5.76806in
   :height: 3.03194in
.. |docx102| image:: media/docx102.jpg
   :width: 5.76806in
   :height: 3.45625in
.. |docx103| image:: media/docx103.bmp
   :width: 5.76806in
   :height: 3.46111in
.. |docx104| image:: media/docx104.jpg
   :width: 5.76806in
   :height: 3.24236in
.. |docx105| image:: media/docx105.jpg
   :width: 5.76806in
   :height: 4.34167in
.. |docx106| image:: media/docx106.jpg
   :width: 5.76806in
   :height: 3.45833in
.. |docx107| image:: media/docx107.jpg
   :width: 5.76806in
   :height: 3.46111in
.. |docx108| image:: media/docx108.png
   :width: 1.27762in
   :height: 1.27762in
.. |docx109| image:: media/docx109.jpg
   :width: 5.76806in
   :height: 3.46111in
.. |docx109| image:: media/docx109.jpg
   :width: 5.76806in
   :height: 3.46111in
.. |docx110| image:: media/docx110.jpg
   :width: 5.76806in
   :height: 3.33264in
.. |docx111| image:: media/docx111.jpg
   :width: 5.76806in
   :height: 3.49583in
.. |docx112| image:: media/docx112.jpg
   :width: 3.63333in
   :height: 1.55in
.. |docx113| image:: media/docx113.jpg
   :width: 5.76806in
   :height: 3.25694in
.. |docx114| image:: media/docx114.jpg
   :width: 5.76806in
   :height: 3.24792in
.. |docx115| image:: media/docx115.jpg
   :width: 5.76806in
   :height: 4.05486in
.. |docx116| image:: media/docx116.jpg
   :width: 5.76806in
   :height: 2.86389in
.. |docx117| image:: media/docx117.jpg
   :width: 5.76781in
   :height: 3.68403in
.. |docx118| image:: media/docx118.jpg
   :width: 5.76806in
   :height: 4.7498in
.. |docx119| image:: media/docx119.jpeg
   :width: 5.76806in
   :height: 1.87107in
.. |docx120| image:: media/docx120.jpg
   :width: 5.76806in
   :height: 3.12014in
.. |docx121| image:: media/docx121.jpg
   :width: 5.76806in
   :height: 3.68322in
.. |docx122| image:: media/docx122.jpg
   :width: 5.76806in
   :height: 5.74375in
.. |docx123| image:: media/docx123.jpg
   :width: 5.76781in
   :height: 3.68403in
.. |docx124| image:: media/docx124.jpeg
   :width: 1.73785in
   :height: 0.925in
.. |docx125| image:: media/docx125.jpg
   :width: 5.76806in
   :height: 3.07009in
.. |docx126| image:: media/docx126.jpg
   :width: 5.76806in
   :height: 3.05764in
.. |docx127| image:: media/docx127.jpg
   :width: 5.76806in
   :height: 4.52986in
.. |docx128| image:: media/docx128.jpg
   :width: 5.76806in
   :height: 4.61111in
.. |docx129| image:: media/docx129.jpg
   :width: 5.7in
   :height: 4.58333in
.. |docx130| image:: media/docx130.jpg
   :width: 5.76806in
   :height: 2.86042in
.. |docx131| image:: media/docx131.jpg
   :width: 3.85833in
   :height: 2.425in
.. |docx132| image:: media/docx132.jpg
   :width: 5.76806in
   :height: 3.38958in
.. |docx133| image:: media/docx133.jpg
   :width: 5.17816in
   :height: 3.12847in
.. |docx134| image:: media/docx134.jpg
   :width: 5.76791in
   :height: 3.76597in
.. |docx135| image:: media/docx135.jpeg
   :width: 5.76806in
   :height: 2.88403in
.. |docx136| image:: media/docx136.jpeg
   :width: 5.76806in
   :height: 3.09444in
.. |docx137| image:: media/docx137.jpeg
   :width: 5.75in
   :height: 1.53333in
.. |docx138| image:: media/docx138.jpeg
   :width: 5.76806in
   :height: 2.88403in
.. |docx139| image:: media/docx139.jpg
   :width: 5.76806in
   :height: 4.2875in
.. |docx140| image:: media/docx140.jpg
   :width: 3.03333in
   :height: 0.79167in
.. |docx141| image:: media/docx141.jpg
   :width: 5.76806in
   :height: 2.86597in
.. |docx142| image:: media/docx142.jpg
   :width: 5.76806in
   :height: 2.49236in
.. |docx143| image:: media/docx143.jpg
   :width: 5.76806in
   :height: 2.92569in
.. |docx144| image:: media/docx144.jpg
   :width: 5.76806in
   :height: 1.60069in
.. |docx145| image:: media/docx145.jpg
   :width: 5.76806in
   :height: 3.81597in
.. |docx146| image:: media/docx146.jpeg
   :width: 5.76806in
   :height: 2.99306in
.. |docx147| image:: media/docx147.jpg
   :width: 5.76806in
   :height: 2.97431in
.. |docx148| image:: media/docx148.jpg
   :width: 5.76806in
   :height: 3.48472in
.. |docx149| image:: media/docx149.jpg
   :width: 2.08333in
   :height: 0.75in
.. |docx150| image:: media/docx150.jpeg
   :width: 5.76806in
   :height: 0.52431in
.. |docx151| image:: media/docx151.jpg
   :width: 5.76806in
   :height: 0.57569in
.. |docx152| image:: media/docx152.jpg
   :width: 5.76806in
   :height: 3.26875in
.. |docx153| image:: media/docx153.jpg
   :width: 5.76806in
   :height: 2.7in
.. |docx154| image:: media/docx154.jpg
   :width: 3.48019in
   :height: 3.46499in
.. |docx155| image:: media/docx155.jpg
   :width: 2.675in
   :height: 2.75833in
.. |docx156| image:: media/docx156.jpeg
   :width: 2.71184in
   :height: 2.7in
.. |docx157| image:: media/docx157.jpg
   :width: 4.27568in
   :height: 4.5in
.. |docx158| image:: media/docx158.jpg
   :width: 5.48333in
   :height: 2.925in
.. |docx159| image:: media/docx159.jpg
   :width: 5.76806in
   :height: 0.66528in
.. |docx160| image:: media/docx160.jpg
   :width: 5.00833in
   :height: 2.93281in
.. |docx161| image:: media/docx161.jpg
   :width: 5.35in
   :height: 3.16667in
.. |docx162| image:: media/docx162.jpg
   :width: 5.30833in
   :height: 3.00833in
.. |docx163| image:: media/docx163.jpg
   :width: 5.76806in
   :height: 3.23611in
.. |docx164| image:: media/docx164.jpg
   :width: 1.38611in
   :height: 1.38611in
.. |docx165| image:: media/docx165.png
   :width: 5.76806in
   :height: 2.01615in
