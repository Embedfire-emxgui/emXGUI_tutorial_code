.. vim: syntax=rst

野火GUI例程介绍
---------------------------

* * 注意！！！！！！* *

* * 本章教程里介绍的代码都是针对旧版的，新版本配套的说明后续会持续更新。* *

* * 目前霸道开发板使用的emXGUI例程改进了不少，但大体的原理还是和旧版类似的，所以本部分内容保留，阅读源码的时候使用新版代码即可。* *

* * 当前各开发板均已配套好emXGUI的基础例程，即基础的工程模板已经搭建完成，可以根据自己的需要直接着手开发APP了。* *

目前，野火基于STM32-ISO开发板设计完成了一个GUI例程，该例程使用emXGUI模仿PDA界面，它具有浏览图片、阅读文字、发送短信、打电话等多种功能。在本章中，将对该例程的整体框架进行介绍。

野火GUI初体验
~~~~~~~~~~~~~~~~~~~~~~~~

为了让读者有更直观的感受，这里先介绍一下野火GUI的使用方法及主要功能。请读者先把野火GUI例程烧录到板子运行体验一下。

.. _实验步骤-2:

实验步骤
^^^^^^^^^^^^

把野火GUI例程(工程名称为wildfire_gui)下载到STM32-ISO板子上，给STM32-ISO板子接入外部SRAM模块，注意还要给板子插入一张格式为FAT的SD卡(支持32G以下的SD卡)，SD卡内需要事先从电脑中拷贝野火GUI例程目录下的“SD卡备份内容”到SD卡的根目录，见 图17_1_ ，例程中会使用到SD卡里的字库、图片等内容。

.. image:: /media/docx065.png
   :align: center
   :alt: 图 17‑1 wildfire_gui例程中的SD卡根目录
   :name: 图17_1

图 17‑1 wildfire_gui例程中的SD卡根目录

实验现象说明
^^^^^^^^^^^^^^

给板子上电后，会看到第一页桌面，见 图17_2_ 的左侧。为了方便管理，我们把整个屏幕分为三栏，分别为状态窗口、主窗口、及页面控制窗口。

.. image:: /media/docx066.png
   :align: center
   :alt: 图 17‑2 野火GUI第一页桌面及页面说明
   :name: 图17_2

图 17‑2 野火GUI第一页桌面及页面说明

状态窗口
''''''''''''

目前主要包含一个野火Logo及一个实时时钟，点击状态窗口左侧的野火Logo，会弹出野火GUI的版本号，而点击状态窗口右侧的时间文字，则会在主窗口弹出一个时间调整界面，见 图17_3_。后期我们还可以往状态窗口添加手机、蓝牙、GPS等信号。

.. image:: /media/docx067.png
   :align: center
   :alt: 图 17‑3 野火GUI状态窗口相关操作
   :name: 图17_3

图 17‑3 野火GUI状态窗口相关操作

控制窗口
''''''''''''

在屏幕最底部的是控制窗口，它主要是显示页面索引及返回按键，见 图17_4_，它分别为第一页桌面、第二页桌面及在应用程序界面时的截图，注意控制窗口显示内容的变化：在桌面时，它以较大的圆点来表示当前页数，在应用程序界面时，圆点会被隐藏，而在屏幕的左下角会出现一个返回键，用于关闭当前应用程序。

.. image:: /media/docx068.png
   :align: center
   :alt: 图 17‑4 野火GUI控制窗口在不同情况显示的状态
   :name: 图17_4

图 17‑4 野火GUI控制窗口在不同情况显示的状态

主窗口
'''''''''

主窗口是野火GUI的核心显示界面，在桌面状态时，它显示的是各种应用图标，点击图标即可打开相关的应用，而所有应用在运行时均在主窗口显示。由于功能庞杂，这里有些应用的功能还有待开发，有些bug还有待解决，希望有兴趣的读者与我们慢慢完善这些应用，下面我们对它一一介绍。

-  SD卡文件浏览器(Browser)

野火GUI的SD卡文件浏览器应用具有查看SD卡内文件的功能，它以树形图的格式显示SD卡内的文件，如果点击本系统支持的文件格式，它会调用相关应用程序来打开阅读，如jpg、png、bmp、gif、txt等文件，图片会以缩放的形式显示出来，而文本文件则以电子书的格式打开，见 图17_5_。

.. image:: /media/docx069.png
   :align: center
   :alt: 图 17‑5 野火GUI SD文件浏览器应用界面
   :name: 图17_5

图 17‑5 野火GUI SD文件浏览器应用界面

需要改善的问题：在emXGUI5.22版本中，官方推出了一个文件浏览器控件，使用该控件可更方便高效地浏览SD卡文件，后期我们会采用它改进文件浏览器。

-  实时时钟应用

点击时钟的应用图标后，会弹出时间调整界面，见 图17_6_。该应用使用STM32的RTC外设记录时间，所以如果给STM32-ISO开发板的电池座接上锂电池，调整了一次时间后，野火GUI的时间在主电源掉电的情况下也会保持正常。如果还没有调整过时间，野火GUI默认从2014年1月1日0时0分0秒开始计时，
在时间调整界面中，有6个分别为年月日时分秒的滚轮，通过上下滑动滚轮选择当前时间，然后点击OK按钮就可以设置时间了。

.. image:: /media/docx070.png
   :align: center
   :alt: 图 17‑6 野火GUI时钟应用界面
   :name: 图17_6

图 17‑6 野火GUI时钟应用界面

-  温度计应用

野火GUI的温度计应用是实时曲线图形式的，见 图17_7_。在温度曲线界面还可以调节x、y轴量程、暂停、是否使用网格、全屏显示等多种选项。

在野火STM32-ISO板子上，预留了温度传感器的接口，可以接入DHT11及DS18B20传感器，为了适应不同的硬件环境，温度计应用程序在初始化时，会检测硬件环境，根据不同的传感器调用不同的驱动程序。在应用程序窗口的左上角会显示当前使用的传感器。如果板子上两种传感器都没有接入时，则会使用STM32芯
片的片上温度传感器，这时检测的是STM32芯片的温度，一般情况下会比环境温度高。

.. image:: /media/docx071.png
   :align: center
   :alt: 图 17‑7 野火GUI温度计应用界面
   :name: 图17_7

图 17‑7 野火GUI温度计应用界面

-  图片浏览器

野火GUI的图片浏览器可以显示SD卡内的bmp、jpg、png及gif格式图片，它以缩放居中的形式显示到主窗口中，在主窗口的右下角有两个按钮分别用来控制查看上一张和下一张图片，见 图17_8_。

.. image:: /media/docx072.png
   :align: center
   :alt: 图 17‑8 野火GUI图片浏览器
   :name: 图17_8

图 17‑8 野火GUI图片浏览器

-  文本阅读器

野火GUI文本阅读器，可以用来打开txt等文本文件。点击应用图标后，会弹出SD目录，目录下仅显示txt格式的文件，点选文件即可打开阅读器，见 图17_9_。

.. image:: /media/docx073.png
   :align: center
   :alt: 图 17‑9 野火GUI图片浏览器
   :name: 图17_9

图 17‑9野火GUI文本阅读器

需要改善的问题：阅读器加载文件时一次过把整个文件都加载到SRAM，当文件较大时就会出错，可改为分段读取文本的内容。野火GUI已经移植了中文字库，可显示中文，但文本阅读器应用还没处理中文文本显示。

-  短信应用

给STM32-ISO开发板接入野火的GSM模块后(接入到ISO板子右下角的串口排针上，并把ISO板子左侧的两个跳帽“485R-A3”、“485D-A2”拔掉)，可以与野火GUI配合使用发送短信、拨打电话。野火GSM模块实物见 图17_10_。

.. image:: /media/docx074.png
   :align: center
   :alt: 图 17‑10 野火GUI图片浏览器
   :name: 图17_10

图 17‑10 野火GSM模块实物

运行野火GUI程序，点击短信及电话应用时它会先检测板子有没有接入GSM模块，如果没有它会弹出提示，见 图17_11_。

接入GSM模块后(并在GSM模块中接入SIM卡)，通过硬件检测，主窗口会显示三个应用图标，分别表示收件箱(In box)、发件箱(Out box)及草稿箱(Draft
box)，点击发件箱，会出现已发信息列表，而列表中的第一栏则为“新建信息”功能，点击它会出现编写信息界面，在对话框中输入号码，短信内容 (点击键盘里的“C/E”、“123”可切换中英文及数字输入)，最后点击界面左下角的“Send”按钮，即可发送短信。见 图17_11_。

.. image:: /media/docx075.png
   :align: center
   :alt: 图 17‑11野火GUI短信应用
   :name: 图17_11

图 17‑11野火GUI短信应用：

从左至右,从上至下    (a)未接入GSM模块时的提示 (b)功能选择 (c)发件箱 (d)发送短信

需要改善的问题：短信应用里的T9输入法还不够人性化，如还没有实现退格、输入标点等功能，在中英文、数字输入切换时还没有添加提示。

-  电话应用

运行野火GUI中的电话应用也需要给STM32-ISO板子接入野火GSM模块。点击电话应用图标后，会出现电话拨号界面，输入要拨打的电话号码后点击“Call”按键即可拨打电话，然后主窗口会进入通话中的界面，见 图17_12_，在GSM模块中接入耳麦，就可以进行通话了。

.. image:: /media/docx076.png
   :align: center
   :alt: 图 17‑12 野火GUI电话应用
   :name: 图17_12

图 17‑12 野火GUI电话应用

-  摄像机、地图、计算器应用

主窗口中的摄像机及桌面第二页的地图、计算器等应用没有实现，仅创建了图标，方便以后添加应用，见 图17_13_。

.. image:: /media/docx077.png
   :align: center
   :alt: 图 17‑13 野火GUI还没实现的应用
   :name: 图17_13

图 17‑13 野火GUI还没实现的应用

-  关于截图

..

   野火GUI还具有屏幕截图功能，在本教程中的示例图片都是这样得来的。按下STM32-ISO板子上的KEY1按键，程序就会开始截图，同时板子上的LED1会亮，截图完成时，LED1会熄灭，同时屏幕上会弹出一个截图成功的提示，见图
   17‑14。截得的图片都保存在SD卡的：0：WF_OS\Snapshot路径中。

.. image:: /media/docx078.png
   :align: center
   :alt: 图 17‑14 野火GUI截图
   :name: 图17_14

图 17‑14 野火GUI截图

野火GUI例程框架
~~~~~~~~~~~~~~~~~~

野火GUI例程比较庞大，为引导读者学习使用本例程，在这里向大家介绍该程序的框架。

.. _主要工程文件-2:

主要工程文件
^^^^^^^^^^^^^^^^^^

野火GUI例程是在前面小节中的emXGUI 使用外部SRAM工程的基础上开发的，它包含了触摸、文件系统、及使用外扩SRAM的功能。在它的基础上，我们添加了各种应用，而每个应用都有独立的文件，修改非常方便，其工程文件目录见 图17_15_。
主要添加了bsp文件组、wildfireGUI文件组、PNGlib文件组及t9py文件组，其说明见 表17_1_ 。

.. _表17_1:

表 17‑1 野火GUI例程主要文件列表

================ ========================= ============================
工程名称            emXGUI_WildfireOS
bsp文件组           bsp_usart1.c            串口驱动，调试时使用
\                   bsp_SysTick.c           Systick驱动，提供系统时钟
\                   bsp_sdio_sdcard.c       SD卡底层驱动
\                   bsp_led.c               LED灯驱动
\                   bsp_gpio_spi.c          触摸屏用到的GPIO模拟SPI驱动
\                   bsp_ili9341_lcd.c       液晶屏控制器驱动
\                   bsp_touch.c             触摸屏控制器驱动
\                   bsp_fsmc_sram.c         外部SRAM驱动
\                   bsp_calendar.c          万年历算法
\                   bsp_date.c              日期算法
\                   bsp_rtc.c               实时时钟驱动
\                   bsp_ov7725.c            摄像头驱动
\                   bsp_sccb.c              模拟SCCB总线驱动
\                   bsp_exti.c              外部中断驱动
\                   bsp_dht11.c             DHT11温湿度传感器驱动
\                   bsp_Timbase.c           温湿度传感器提供的定时器驱动
\                   bsp_ds18b20.c           DS18B20温度传感器
\                   bsp_internal_temp.c     STM32内部温度传感器驱动
\                   sim900a.c               GSM模块驱动
\                   bsp_usart2.c            为GSM模拟提供的usart2驱动
GUI应用文件         GUIDEMO_Touch.c         emXGUI触摸校准应用
\                   WFGUI_DeskTop.c         emXGUI桌面控制文件
\                   WFGUI_Icon.c            EmXGUI图标资源文件
\                   WFGUI_SDView.c          SD卡文件浏览器应用
\                   WFGUI_TextReader.c      文件阅读器应用
\                   WFGUI_ImageReader.c     图片浏览器应用
\                   WFGUI_Time.c            实时时钟应用
\                   WFGUI_Message.c         短信应用
\                   WFGUI_Keypad.c          T9拼音键盘界面程序
\                   WFGUI_Phone.c           电话应用
\                   WFGUI_Camera.c          摄像头应用
\                   WFGUI_Snapshot.c        GUI截屏程序
\                   WFGUI_Temperature.c     温度计应用
\                   WFGUI_APPLinkedList.c   应用程序链表程序
\                   WFGUI_UserAPP.c         提供给用户扩展应用的接口
t9py文件组           t9py.c                  T9拼音输入法主程序
PNGlib文件组         PNG.lib                 PNG图片解码库
================ ========================= ============================

.. image:: /media/docx079.png
   :align: center
   :alt: 图 17‑15 野火GUI程文件目录
   :name: 图17_15

图 17‑15 野火GUI程文件目录

初始化板载外设
^^^^^^^^^^^^^^^^^^^^^

我们先从main文件入手开始分析，main文件中主要包括板子的初始化函数BSP_Init及程序主函数main，见 代码清单17_1_。

.. code-block:: c
    :caption: 代码清单 17‑1野火GUI的main文件
    :linenos:
    :name: 代码清单17_1

     /**
     *
     * @file main.c
     * @author fire
     * @version V1.0
     * @date 2013-xx-xx
     * @brief 测试led
     *
     * @attention

     *
     * 实验平台:野火 iSO STM32 开发板
     * 论坛 :http://www.chuxue123.com
     * 淘宝 :http://firestm32.taobao.com
     *
     *
     */

     #include "stm32f10x.h"
     #include "GUI.h"
     #include "diskio.h"
     #include "ff.h"

     #include "bsp_led.h"
     #include "bsp_touch.h"
     #include "bsp_SysTick.h"
     #include "bsp_usart1.h"
     #include "bsp_sdio_sdcard.h"
     #include "bsp_fsmc_sram.h"
     #include "bsp_rtc.h"
     #include "bsp_exti.h"

     #include "WFGUI_DeskTop.h"
     #include "WFGUI_Common.h"

     extern void Touch_MainTask(void);

     /* 时间结构体 */
     struct rtc_time systmtime;


     void BSP_Init(void)
     {

        static FATFS fsys;

        /* LED 端口初始化 */
        LED_GPIO_Config();

        /* 初始化触屏 */
        Touch_Init();

        /* 初始化定时器 */
        SysTick_Init();

        /* 配置 FSMC Bank1 NOR/SRAM3 */
        FSMC_SRAM_Init();

        /* 初始化sd卡 */
        disk_initialize(0);

        f_mount(0,&fsys); //注册文件系统工作区 // TBD 增加sd卡检测

        /*CRC和emXGUI没有关系，只是他们为了库的保护而做的，
        这样STemXGUI的库只能用在ST的芯片上面，别的芯片是无法使用的。 */
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

        /* 初始化GUI */
        GUI_Init();

        /* 初始化串口*/
        USART1_Config();

        /* 配置RTC秒中断优先级 */
        RTC_NVIC_Config();

        RTC_CheckAndConfig(&systmtime);

        EXTI_Key_Config();

        DEBUG("\r\n wildfire ISO board emXGUI test \r\n");

     }


     /**
     * @brief 主函数
     * @param 无
     * @retval 无
     */
     int main(void)
     {

        BSP_Init();

        GUI_Delay (20);

        #if 0
        /* 触摸校准demo */
        Touch_MainTask();

        #else

        WFGUI_MainTask();

        while (1) {

            GUI_Delay(50); //窗口在gui delay期间自动重绘，必须要有gui_delay
            }
        #endif

     }


     /END OF FILE/


我们看到，main函数调用了BSP_Init函数初始化了板子的各种外设，包括LED、液晶触摸屏、Systick时钟、外部SRAM、SD卡、文件系统、GUI、RTC时钟、串口和按键等等，然后就调用了野火GUI的主函数WFGUI_MainTask，野火GUI的所有操作从它开始。

.. _创建桌面-2:

创建桌面
^^^^^^^^^^^^

WFGUI_MainTask函数的定义位于WFGUI_DeskTop.c文件，它在调用emXGUI库函数WM_MOTION_Enable使能emXGUI的滑动操作后，调用了我们编写的CreatDeskTop函数。在这里提一下如何区分emXGUI库函数和野火编写的函数，如果在程序代码中无法找到函数定义的，它都是emXGUI的库函数，这是因为emXGUI的库函数都编译成了库文件，无法查看源代码了。

.. code-block:: c
    :caption: 代码清单 17‑2创建桌面
    :linenos:
    :name: 代码清单17_2


     /**
     * @brief CreatDeskTop，创建gui桌面
     * @param none
     * @retval none
     */
     static void CreatDeskTop(void)
     {
        /* 准备建立3个窗口，以下是使用到的用户定义参数，
        方便在回调函数中使用 */
        WinPara.xSizeLCD = LCD_GetXSize(); //LCD屏幕尺寸
        WinPara.ySizeLCD = LCD_GetYSize(); //LCD屏幕尺寸
        WinPara.xSizeWin = WinPara.xSizeLCD; //窗口尺寸
        WinPara.ySizeWin = WinPara.ySizeLCD -20*2; //窗口尺寸
        //屏幕大小减去状态栏和控制栏
        WinPara.xPosWin = 0; //窗口的起始位置
        WinPara.yPosWin = 20; //窗口的起始位置
        WinPara.xSizeWinVirtual = WinPara.xSizeWin * VIRTUAL_WIN_NUM;
        //虚拟窗口尺寸，用于桌面

        /* 设置默认皮肤 */
        SetDefaultSkin();


        WM_EnableMemdev(WM_HBKWIN);

        /* 设置背景桌面的回调函数 */
        WM_SetCallback(WM_HBKWIN, _cbBKWin);

        /* 创建三个窗口 状态栏、控制栏、主窗口*/
        CreatStatusWin();
        CreatCtrlWin();
        CreatMainWin();

        /* 初始化app链表 */
        hAPPLinkedList_Init();
     }


     /*
     *
     * Public routines
     * 公有函数
     *
     *
     */

     /**
     * @brief WFGUI_MainTask,WFGUI主函数
     * @param none
     * @retval none
     */
     void WFGUI_MainTask(void)
     {
        WM_MOTION_Enable(1);
        WM_MOTION_SetDefaultPeriod(1000);

        CreatDeskTop(); //创建gui桌面

        while (1) {

            GUI_Delay(50);

        }
     }


初始化窗口大小
'''''''''''''''''''''

在CreatDeskTop 函数中，初始化了一个全局结构体变量WinPara，它用于记录屏幕尺寸以及主窗口的位置及大小，通过这些参数，可以推算出状态窗口及控制窗口的大小，见 代码清单17_3_。

.. code-block:: c
    :caption: 代码清单 17‑3 WIN_PARA结构体
    :linenos:
    :name: 代码清单17_3

     typedef struct WIN_PARA {
        //窗口使用到的用户定义参数，方便在回调函数中使用
        int xSizeLCD, ySizeLCD; //LCD屏幕尺寸
        int xPosWin, yPosWin; //窗口的起始位置
        int xSizeWin, ySizeWin; //窗口尺寸
        int xSizeWinVirtual; //虚拟窗口尺寸

        unsigned char ctr_index; //记录icorn窗口的索引
        unsigned char isDesktop; //记录桌面窗口是否在最前 0：桌面窗口不在最前  1：桌面窗口在最前
        
        WM_HWIN hWinCtrl; //控制窗口的句柄（底部）
        WM_HWIN hWinMain; //主显示窗的句柄（中部）
        WM_HWIN hWinStatus; //状态窗口的句柄（顶部）
        WM_HWIN hWinTime;
        
        WM_HWIN hApp[20]; //记录正在运行的App句柄
    
     } WIN_PARA;

-  xSizeLCD和 ySizeLCD

xSizeLCD和 ySizeLCD参数分别用于记录液晶屏的X、Y方向分辨率。在CreatDeskTop 函数初始化时，是使用库函数LCD_GetXSize、LCD_GetYSize来获取的，而不是直接固定分配240*320，使用库函数来获取屏幕大小有利于应用程序使用不同屏幕的移植。

-  xSizeWin和ySizeWin

xSizeWin和ySizeWin分别用于记录主窗口的X、Y方向的分辨率。按照我们的设计，整个液晶屏分为三个窗口，见 图17_2_，
三个窗口在X方向均占满整个屏幕，所以xSizeWin被配置为xSizeLCD的值，即等于屏幕X宽度。而状态窗口及控制窗口的Y方向均为20像素分辨率，要预留位置给这两个窗口，所以主窗口的ySizeWin大小设置为屏幕的Y宽度减去20*2的像素。

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
'''''''''''''''''''''''''''

CreatDeskTop设置完各个窗口的大小后，调用了SetDefaultSkin函数设置各种控件的皮肤和SD卡外部字体，SetDefaultSkin函数定义见 代码清单17_4_。

.. code-block:: c
    :caption: 代码清单 17‑4 SetDefaultSkin函数内容
    :linenos:
    :name: 代码清单17_4

     /**
     * @brief SetDefaultSkin,设置gui的默认皮肤
     *
     * @param none
     * @retval none
     */
     static void SetDefaultSkin(void)
     {

        /* 设置各种控件的皮肤为类win7的皮肤 */
        BUTTON_SetDefaultSkin (BUTTON_SKIN_FLEX);
        CHECKBOX_SetDefaultSkin (CHECKBOX_SKIN_FLEX);
        DROPDOWN_SetDefaultSkin (DROPDOWN_SKIN_FLEX);
        FRAMEWIN_SetDefaultSkin (FRAMEWIN_SKIN_FLEX);
        HEADER_SetDefaultSkin (HEADER_SKIN_FLEX);
        PROGBAR_SetDefaultSkin (PROGBAR_SKIN_FLEX);
        RADIO_SetDefaultSkin (RADIO_SKIN_FLEX);
        SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
        SLIDER_SetDefaultSkin (SLIDER_SKIN_FLEX);

        /* 设置滑动条 */
        SCROLLBAR_SetDefaultWidth(15); //宽度
        SCROLLBAR_SetThumbSizeMin(10); //滑块最小size

        /* 创建sd卡外部字体 */
        CreateFont(&SDFont);

        /* 设置默认字体 */
        TEXT_SetDefaultFont(&SDFont.XFont);

        /* 设置framwin */
        FRAMEWIN_SetDefaultTitleHeight(20); //标题栏高度
        FRAMEWIN_SetDefaultFont(GUI_FONT_8X16); //默认字体
        FRAMEWIN_SetDefaultTextColor(1,GUI_BLACK); //设置激活状态时的标题文字颜色
        WM_SetDesktopColor(GUI_BLACK);
     }

在SetDefaultSkin函数中，调用了各种emXGUI控件的皮肤设置函数，它们的作用是把野火GUI里使用到的控件皮肤都设置为Win7风格，这样的控件比较好看。另外，还调用了CreateFont函数初始化外部SD卡字体，emXGUI自带的字体只包含英文字库，当需要显示中文的时候，就需要用到SD卡
里的外部字体库文件。该字体的字库文件保存在SD卡的WF_OS\Font文件夹内，它是由emXGUI提供的字库生成工具生成的。

创建状态窗口
''''''''''''''''''

设置完控件皮肤及字体后，CreatDeskTop函数依次创建了状态窗口、控制窗口以及主窗口，其中创建状态窗口的函数CreatStatusWin定义见 代码清单17_5_。

.. code-block:: c
    :caption: 代码清单 17‑5 CreatStatusWin函数内容
    :linenos:
    :name: 代码清单17_5

     /**
     * @brief CreatStatusWin，创建顶部的状态栏
     * @param none
     * @retval none
     */
     static void CreatStatusWin(void)
     {
        WM_HWIN hText;
        WM_HWIN hButton;


        WinPara.hWinStatus = WM_CreateWindowAsChild(
        0, //窗口位置、大小
        0,
        WinPara.xSizeLCD,
        WinPara.yPosWin,
        WM_HBKWIN, WM_CF_SHOW | WM_CF_MEMDEV, _cbStatusWin, sizeof(WIN_PARA *)
        );

        /* 顶部的 "wildfire OS "文本 */
        hText = TEXT_CreateEx(0, 0, WinPara.xSizeWin , 20,
        nPara.hWinStatus, WM_CF_SHOW,
        GUI_TA_HCENTER|TEXT_CF_VCENTER, GUI_ID_TEXT1, "Wildfire OS");
        TEXT_SetFont(hText, GUI_FONT_16B_ASCII);
        TEXT_SetTextColor(hText, 0xFF4040);

        /* 状态栏的时间显示文本 */
        hText = TEXT_CreateEx(WinPara.xSizeLCD-55,5,55,20,
        nPara.hWinStatus,WM_CF_SHOW,TEXT_CF_LEFT,
        GUI_ID_TEXT0,"");
        TEXT_SetBkColor(hText,GUI_INVALID_COLOR);
        TEXT_SetTextColor(hText,GUI_WHITE);
        TEXT_SetFont(hText,GUI_FONT_13B_ASCII);

        /* 野火Logo 按钮 */
        hButton = BUTTON_CreateEx(2,0,40,20,
        nPara.hWinStatus,WM_CF_SHOW,0,GUI_ID_BUTTON0);
        BUTTON_SetBitmap(hButton,BUTTON_BI_UNPRESSED,&bmWF_Logo);
        BUTTON_SetBitmap(hButton,BUTTON_BI_PRESSED,&bmWF_LogoPr);

     }


在CreatStatusWin中，调用了比较多的emXGUI库函数，而且库函数的输入参数非常多，在这里我们不对细节具体展开，对输入参数有疑问的读者可以在《emXGUI用户手册》搜索相关的库函数说明。首先，调用WM_CreateWindowAsChild库函数，以背景窗口(emXGUI默认具有一个背景
窗口)为父窗口，在屏幕的顶部创建了状态窗口，并指定了状态窗口的回调函数_cbStatusWin，注意WM_CreateWindowAsChild的返回值赋给了全局变量WinPara.hWinStatus，即前面提到记录状态窗口句柄的变量，就是在这个时候初始化的。

紧接着，在创建完状态窗口后，马上在它上面创建了顶部显示“wildfire OS”的文本控件，实时时钟的文本以及野火Logo按钮，在创建这些控件时，由于要设置它所在的父窗口，都使用到了WinPara.hWinStatus句柄来访问状态窗口。

窗口的回调函数是用户定制emXGUI应用的核心，用户通过回调函数来处理各种事件、响应，函数中通过消息ID来 区分不同的事件，方便用户进行处理。状态窗口的回调函数_cbStatusWin见 代码清单17_6_。

.. code-block:: c
    :caption: 代码清单 17‑6_cbStatusWin
    :linenos:
    :name: 代码清单17_6

    /**
    * @brief  _cbStatusWin,状态栏回调函数
    * @param  none
    * @retval none
    */
    static void _cbStatusWin(WM_MESSAGE * pMsg)
    {
        char text_buffer[20];
        WM_HWIN hText;
        int        NCode;
        int        Id;

        switch (pMsg->MsgId) {

        case WM_NOTIFY_PARENT:                    //通知父窗口

            Id    = WM_GetId(pMsg->hWinSrc);      // 控件的ID
            NCode = pMsg->Data.v;                 // 通知代码

            if (NCode == WM_NOTIFICATION_RELEASED) {  //触摸释放消息
                if (Id == GUI_ID_BUTTON0) {           //野火Logo按键
                    /* 显示消息提示框 */
                    MESSAGEBOX_Create("\n\n  Wildfire OS 1.0  \n\n","About",0);

                } else if (Id == GUI_ID_TEXT0) {      //时间文本框
                    /* 执行WFGUI_Time应用 */
                    WFGUI_Time();
                }
            }
            break;
    
        case WM_PAINT:                          //重绘背景
            GUI_SetColor(GUI_BLACK);
            GUI_FillRect(0,0,WinPara.xSizeLCD ,WinPara.yPosWin);
    
            break;
    
        case MY_MESSAGE_RTC:                    
        //处理时间显示的信息，每秒钟修改一次时间
    
            /* 获取text句柄 */
            hText = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0);
    
            /* 转换rtc值至北京时间 */
            RTC_TimeCovr(&systmtime);
    
            /* 转换成字符串 */
            sprintf(text_buffer,"%02d:%02d:%02d",systmtime.tm_hour,systmtime.tm_min,systmtime.tm_sec);
            /* 输出时间 */
            TEXT_SetText(hText,text_buffer);
            break;
        default:
            WM_DefaultProc(pMsg);
    
        }
    }

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
的RTC驱动通知时间显示控件而定义的，在每次RTC的秒中断触发时，它会向状态窗口发送MY_MESSAGE_RTC消息，而状态窗口接收到该消息后，就在回调函数这里对显示时间的文本进行更新。其中RTC的秒中断函数见 代码清单17_7_，它除了发送消息到状态窗口，在时间应用被激活的时候，还会把该消息发送到时间应用窗口。

.. code-block:: c
    :caption: 代码清单 17‑7 RTC秒中断服务函数
    :linenos:
    :name: 代码清单17_7

    /**
    * @brief  This function handles RTC interrupt request.
    * @param  None
    * @retval None
    */
    void RTC_IRQHandler(void)
    {

        if (RTC_GetITStatus(RTC_IT_SEC) != RESET) {
            /* Clear the RTC Second interrupt */
            RTC_ClearITPendingBit(RTC_IT_SEC);

            /* Enable time update */
            TimeDisplay = 1;

            /* 判断窗口是否有效 */
            if (WM_IsWindow(WinPara.hWinStatus)) {
                /*  发送 */
                WM_SendMessageNoPara(WinPara.hWinStatus,MY_MESSAGE_RTC);
            }
            if (WM_IsWindow(WinPara.hWinTime)) {
                WM_SendMessageNoPara(WinPara.hWinTime,MY_MESSAGE_RTC);
            }

        /* Wait until last write operation on RTC registers has finished */
            RTC_WaitForLastTask();
        }
    }

创建控制窗口
''''''''''''''''''

控制窗口的创建跟状态窗口是类似的，其函数CreatCtrlWin内容见 代码清单17_8_。

.. code-block:: c
    :caption: 代码清单 17‑8 CreatCtrWin函数定义
    :linenos:
    :name: 代码清单17_8

     /**
     * @brief CreatCtrlWin，创建底部的控制栏
     * @param none
     * @retval none
     */
     static void CreatCtrlWin(void)
     {
     WM_HWIN hButtonWin;

     WinPara.hWinCtrl = WM_CreateWindowAsChild(
                                                0,
                                                WinPara.yPosWin +WinPara.ySizeWin , //底部位置
                                                WinPara.xSizeLCD,
                                                WinPara.ySizeLCD -(WinPara.yPosWin +WinPara.ySizeWin),
                                                //底部剩余宽度
                                                WM_HBKWIN, WM_CF_SHOW | WM_CF_MEMDEV, _cbCtrlWin, sizeof(WIN_PARA *) );

     /* 创建索引窗口 (以小圆点表示当前的图标页面)*/
     WM_CreateWindowAsChild( 0,
                            0,
                            WM_GetWindowSizeX(WinPara.hWinCtrl),
                            WM_GetWindowSizeY(WinPara.hWinCtrl),
                            WinPara.hWinCtrl,WM_CF_SHOW,_cbIndexWin,0);

     /* 创建按键button窗口(该button在应用程序状态下 会显示返回按钮) */
     hButtonWin = WM_CreateWindowAsChild(0,
                                        0,
                                        WM_GetWindowSizeX(WinPara.hWinCtrl),
                                        WM_GetWindowSizeY(WinPara.hWinCtrl),
                                        WinPara.hWinCtrl,WM_CF_SHOW,_cbButtonWin,0);
     /* 默认隐藏button窗口 */
     GUI_Delay(10);
     WM_HideWindow(hButtonWin);
     GUI_Delay(10);

     }


在CreatCtrWin中调用库函数WM_CreateWindowAsChild在屏幕的下文创建一个窗口，作为控制窗口，并设置其回调函数为_cbCtrlWin。接着又在控制窗口中创建了小圆点索引窗口及返回键窗口，并默认隐藏返回键窗口。

这三个窗口都有对应的回调函数，分别为_cbCtrlWin、_cbIndexWin和_cbButtonWin。先来看看_cbCtrlWin的代码，见 代码清单17_9_。

.. code-block:: c
    :caption: 代码清单 17_9 控制窗口回调函数_cbCtrlWin
    :linenos:
    :name: 代码清单17_9
 
    /**
    * @brief  _cbCtrlWin,控制栏回调函数
    * @param  none
    * @retval none
    */
    static void _cbCtrlWin(WM_MESSAGE * pMsg)
        {
        WM_HWIN hItem;
        WM_HWIN hItemNext;
    
        switch (pMsg->MsgId)
            {
    
            case WM_PAINT:                               //重绘背景
    
                GUI_SetColor(GUI_BLACK);
                GUI_FillRect(0,0,WM_GetWindowSizeX(pMsg->hWin),
    WM_GetWindowSizeY(pMsg->hWin));
                break;
    
            case MY_MESSAGE_CTRLCHANGE:
                if (hAPPLinkedList_GetAppTop()==NULL)     
                //如果没有app窗口，则控制栏显示桌面索引
                    {
                    hItem = WM_GetFirstChild(WinPara.hWinCtrl);
                    hItemNext = WM_GetNextSibling(hItem);
    
                    /* 根据回调函数来区分窗口 */
                    if (WM_GetCallback(hItem) == _cbIndexWin  && 
    WM_GetCallback(hItemNext) == _cbButtonWin)
                    
                        {
                        /* 显示index窗口，隐藏button窗口 */
                        WM_ShowWindow(hItem);
                        WM_HideWindow(hItemNext);
                        WM_Paint(hItem);               //要重绘索引窗口，更新索引
    
                        }
                    else if (WM_GetCallback(hItemNext) == _cbIndexWin  && 
    WM_GetCallback(hItem) ==_cbButtonWin) 
                    
                        {
                        /* 显示index窗口，隐藏button窗口 */
                        WM_ShowWindow(hItemNext);
                        WM_HideWindow(hItem);
    
                        WM_Paint(hItemNext);          //要重绘索引窗口，更新索引
    
                        }
    
                    }
                else                    //如果存在app窗口，显示控制按钮索引
                    {
                    hItem = WM_GetFirstChild(WinPara.hWinCtrl);
                    hItemNext = WM_GetNextSibling(hItem);
    
                    /* 根据回调函数来区分窗口 */
                    if (WM_GetCallback(hItem) == _cbIndexWin  && 
    WM_GetCallback(hItemNext) == _cbButtonWin)
                    
                        {
                        /* 显示button窗口，隐藏index窗口 */
                        WM_ShowWindow(hItemNext);
                        WM_HideWindow(hItem);
                        }
                    else if (WM_GetCallback(hItemNext) == _cbIndexWin  && 
    WM_GetCallback(hItem) == _cbButtonWin)
                    
                        {
                        /* 显示button窗口，隐藏index窗口 */
                        WM_ShowWindow(hItem);
                        WM_HideWindow(hItemNext);
                        }
                    }
                break;
            default:
                WM_DefaultProc(pMsg);
                break;
            }
        }

控制窗口的回调函数主要处理了一个我们自宝义的消息MY_MESSAGE_CTRLCHANGE ，每当打开或关闭了应用程序，我们都会给控制窗口发送这个消息。

控制窗口收到该消息后，使用函数hAPPLinkedList_GetAppTop 来查询应用程序链表，如果查得目前没有打开应用(主窗口为桌面)，则在控制窗口显示小圆点索引窗口，如果查得目前有打开应用，则在控制窗口显示返回键窗口。索引窗口及返回键窗口的回调函数见 代码清单17_10_。

.. code-block:: c
    :caption: 代码清单 17‑10索引窗口及返回键窗口的回调函数
    :linenos:
    :name: 代码清单17_10
 
    /**
    * @brief  _cbIndexWin,索引窗口回调函数
    * @param  none
    * @retval none
    */
    static void _cbIndexWin(WM_MESSAGE * pMsg)
        {
    
        switch (pMsg->MsgId)
            {
            case WM_PAINT:                    //重绘背景
    
                GUI_SetColor(GUI_BLACK);
                GUI_FillRect(0,0,WM_GetWindowSizeX(pMsg->hWin) ,
    WM_GetWindowSizeY(pMsg->hWin));
    
    
                /* 绘制索引窗口 */
                GUI_SetColor(GUI_LIGHTGRAY);
    
                    {
                    char i,r;
    
                    for (i=0; i<VIRTUAL_WIN_NUM; i++)
                        {
                        if (i == WinPara.ctr_index)
                            r=5;                    //当前窗口的圆点半径大
                        else
                            r=2;                    //非当前窗口的圆点半径小
    
                        if (i< VIRTUAL_WIN_NUM/2) //绘制圆点
                            {
                            /* 绘制索引窗口 */
                        GUI_FillCircle(WM_GetWindowSizeX(pMsg->hWin)/2-10*i,
    WM_GetWindowSizeY(pMsg-> hWin)/2,r);
                            
                            }
                        else
                            {
                            /* 绘制索引窗口 */
                    GUI_FillCircle(WM_GetWindowSizeX(pMsg->hWin)/2+10*i,
    WM_GetWindowSizeY(pMsg-> hWin)/2,r);
                            
                            }
                        }
                    }
                break;
            default:
                break;
    
            }
    
        }
    
    /**
    * @brief  _cbButtonWin,控制按钮窗口回调函数
    * @param  none
    * @retval none
    */
    static void _cbButtonWin(WM_MESSAGE * pMsg)
        {
        int Id,NCode;
        WM_HWIN hItem;
    
        switch (pMsg->MsgId)
            {
    
            case WM_PAINT:                      //重绘窗口
                GUI_SetColor(GUI_BLACK);
                GUI_FillRect(0,0,WM_GetWindowSizeX(pMsg->hWin) ,
    WM_GetWindowSizeY(pMsg->hWin));
    
                break;
    
            case WM_CREATE:                   //创建窗口
    
                /*返回键*/
                hItem = BUTTON_CreateEx(0,0,40, 20,
                                        pMsg->hWin, WM_CF_SHOW|WM_CF_MEMDEV , 
    0, GUI_ID_BUTTON0);
                BUTTON_SetText(hItem, "<");
                break;
            case WM_NOTIFY_PARENT:              //处理子窗口消息
                Id    = WM_GetId(pMsg->hWinSrc);
                NCode = pMsg->Data.v;
    
                if (NCode == WM_NOTIFICATION_RELEASED)
                    {
                    if (Id == GUI_ID_BUTTON0)
                        {

                        HANDLE_LIST *hAPPOnTop;

                        /* 获取最上层的窗口句柄 */
                        hAPPOnTop = hAPPLinkedList_GetAppTop();
                        if (hAPPOnTop != NULL)
                            {
                            WM_DeleteWindow(hAPPOnTop->hAPP);     //  关闭窗口
    
                            }
    
                        }
                    else if (Id == GUI_ID_BUTTON1)              
                    //button1可以制作home键，现在没有实现
                        {
    
                        }
    
                    }
    
                break;
    
            default:
                break;
    
            }
    
        } 

索引窗口在它的重绘消息处理中绘制了大小不同的圆点，它根据全局变量WinPara.ctr_index来绘制半径不同的圆点。而返回窗口的回调函数则在返回键被按下时处理关闭最上层应用程序的操作。

创建主窗口
'''''''''''''''

最后我们要创建主窗口，见 代码清单17_11_。它调用库函数WM_CreateWindowAsChild创建主窗口并指定其回调函数，接着在主窗口中创建一个图标窗口。

.. code-block:: c
    :caption: 代码清单 17‑11 创建主窗口函数内容
    :linenos:
    :name: 代码清单17_11

     /**
     * @brief CreatMainWin，创建主显示窗口
     * @param none
     * @retval none
     */
     static void CreatMainWin(void)
     {
        WinPara.hWinMain = WM_CreateWindowAsChild(
        WinPara.xPosWin ,
        WinPara.yPosWin , //位置
        WinPara.xSizeWin,
        WinPara.ySizeWin, //底部剩余宽度
        WM_HBKWIN, WM_CF_SHOW | WM_CF_MEMDEV, _cbMainWin, sizeof(WIN_PARA *)
     );
     /* 创建icon图标窗口 */
     WM_CreateWindowAsChild( 0 ,
                            0 , //位置
                            WinPara.xSizeWin * VIRTUAL_WIN_NUM,
                            WinPara.ySizeWin, //高
                            WinPara.hWinMain,
                            WM_CF_SHOW | WM_CF_MEMDEV|WM_CF_MOTION_X,
                            _cbIconWin,
                            0
     );
     }


由于主窗口仅仅作为一个相当于背景的媒介，它需要处理的消息并不多，它的回调函数也相对简单，见 代码清单17_12_。

.. code-block:: c
    :caption: 代码清单 17‑12主窗口的回调函数
    :linenos:
    :name: 代码清单17_12

    /**
    * @brief  _cbMainWin,主窗口回调函数
    * @param  none
    * @retval none
    */
    static void _cbMainWin(WM_MESSAGE * pMsg)
        {
        switch (pMsg->MsgId)
            {
            case WM_NOTIFY_PARENT:

                break;

            case MY_MESSAGE_SNAPSHOT:       //处理截图消息

                /* 调用截图应用 */
                WFGUI_Snapshot() ;

                break;

            case WM_PAINT:                //重绘背景
                GUI_SetColor(GUI_BLACK);
                GUI_FillRect(0,0,WinPara.xSizeWin ,WinPara.ySizeWin);

                break;

            default:
                WM_DefaultProc(pMsg);
            }
        }

在回调函数中，主要处理的为WM_PAINT重绘消息以及自定义的截图消息MY_MESSAGE_SNAPSHOT，它通过调用函数WFGUI_Snapshot函数保存截图到SD卡。截图消息是由按键中断服务函数发出的，当我们按下开发板的KEY1键时，就会触发截图中断，按键截图中断服务函数见 代码清单17_13_。

.. code-block:: c
    :caption: 代码清单 17‑13 按键截图中断服务函数
    :linenos:
    :name: 代码清单17_13

     void EXTI0_IRQHandler(void)
     {

        if (EXTI_GetITStatus(EXTI_Line0) != RESET) //确保是否产生了EXTI Line中断
        {

        if (WM_IsWindow(WinPara.hWinMain))
        {
        WM_SendMessageNoPara(WinPara.hWinMain ,MY_MESSAGE_SNAPSHOT);

        }

        EXTI_ClearITPendingBit(EXTI_Line0); //清除中断标志位
        }
     }


中断服务函数中，调用库函数WM_IsWindow检测窗口是否有效，若主窗口有效，则向它发送截图消息MY_MESSAGE_SNAPSHOT。

接下来我们看主窗口中的图标窗口的回调函数，图标窗口连接着野火GUI的所有应用，它的回调函数内容见 代码清单17_14_。

.. code-block:: c
    :caption: 代码清单 17‑14主窗口的图标控件回调函数
    :linenos:
    :name: 代码清单17_14

    /**
    * @brief  Icon窗口回调函数
    * @param  none
    * @retval none
    */
    static void _cbIconWin(WM_MESSAGE * pMsg)
    {
        WM_HWIN hWin;
        WM_HWIN hItem;
        WM_HWIN hParent;

        WM_MOTION_INFO * pInfo;

        int        NCode;
        int        Id;
        int        Sel;

        unsigned char i,j;
        hParent = pMsg->hWin;

        switch (pMsg->MsgId) {

        case WM_CREATE:

            for (i=0; i<VIRTUAL_WIN_NUM; i++) {
                /*
                * 创建图标控件
                */

                hWin = ICONVIEW_CreateEx(i*240, 5, WinPara.xSizeWin,  
    WinPara.ySizeWin, hParent, WM_CF_SHOW | WM_CF_HASTRANS,
                        0, GUI_ID_ICONVIEW0+i, 55, 70);                 
                                        
    
                /* 设置选定图标的颜色 */
        ICONVIEW_SetBkColor(hWin, ICONVIEW_CI_SEL, GUI_BLUE | 0xC0000000);
                /* 设置图标的字体 */
                ICONVIEW_SetFont(hWin, &GUI_Font13B_ASCII);
    
                /* 设置初始选择的图标为 -1 (表示尚未选择)*/
                ICONVIEW_SetSel(hWin,-1);
            }
            /* 设置当前索引 */
            WinPara.ctr_index = 0;
            /* 显示第一个图标页 */
            hWin = WM_GetDialogItem(pMsg->hWin,GUI_ID_ICONVIEW0);
            /*
            * 添加图标到图标控件
            */
    for (j = 0 ; j < ICON_PAGE_NUM  && j < GUI_COUNTOF(_aBitmapItem); j++) {
                ICONVIEW_AddBitmapItem(hWin, _aBitmapItem[j].pBitmap, 
    _aBitmapItem[j].pText);
            }
    
            /* 显示第二个图标页 */
            hWin = WM_GetDialogItem(pMsg->hWin,GUI_ID_ICONVIEW1);
    
            /*
            * 添加图标到图标控件
            */
    for (j = 0 ; j < ICON_PAGE_NUM  && j < GUI_COUNTOF(_aBitmapItem2); j++) {
                ICONVIEW_AddBitmapItem(hWin, _aBitmapItem2[j].pBitmap, 
    _aBitmapItem2[j].pText);
            }
    
            break;
    
        case WM_NOTIFY_PARENT:
    
            Id    = WM_GetId(pMsg->hWinSrc);      // 控件的ID
            NCode = pMsg->Data.v;                 // 通知代码
    
            switch (Id) {
    
            case GUI_ID_ICONVIEW0:                // 图标控件0
    
                switch (NCode) {
                case WM_NOTIFICATION_RELEASED:
                    //case WM_NOTIFICATION_SEL_CHANGED:
                    /*
                    * 获取当前选中的图标
                    */
                    Sel   = ICONVIEW_GetSel(pMsg->hWinSrc);
    
                    switch (Sel) {
                    case 0:
                        GUI_Delay(500);               //短暂延时以显示触摸效果
                        ShowTips(pMsg->hWin);         //提示让用户等待
                        WFGUI_SDView();
                        break;
    
                    case 1:
                        GUI_Delay(500);               //短暂延时以显示触摸效果
                        ShowTips(pMsg->hWin);         //提示让用户等待
                        WFGUI_Time();
                        break;

                    case 2:
                        GUI_Delay(500);
                        ShowTips(pMsg->hWin);         //提示让用户等待
                        WFGUI_Temperature();
                        break;
    
                    case 3:
                        GUI_Delay(500);
                        ShowTips(pMsg->hWin);         //提示让用户等待
                        WFGUI_ImageReader();
    
                        break;
    
                    case 4:
                        GUI_Delay(500);
                        ShowTips(pMsg->hWin);         //提示让用户等待
                        WFGUI_TextReader();
                        break;
    
                    case 5:
                        GUI_Delay(500);               //短暂延时以显示触摸效果
                        ShowTips(pMsg->hWin);         //提示让用户等待
                        WFGUI_Message();
                        break;
    
                    case 6:
                        GUI_Delay(500);               //短暂延时以显示触摸效果
                        ShowTips(pMsg->hWin);         //提示让用户等待
                        WFGUI_Phone();
                        break;
    
                    case 7:
                        GUI_Delay(500);
                        ShowTips(pMsg->hWin);         //提示让用户等待
                        WFGUI_Camera();
                        break;
                    default:
                        break;
                    }
    
                    /* 获取ICON的句柄 */
                    hItem = WM_GetDialogItem(hParent, GUI_ID_ICONVIEW0);
                    /* 设置初始选择的图标为 -1 (表示尚未选择)*/
                    ICONVIEW_SetSel(hItem,-1);
                    break;//WM_NOTIFICATION_RELEASED
                }       //NCODE
    
                break;      //ICONVIEW0
    
            case GUI_ID_ICONVIEW1:                // 图标控件1
    
                if (NCode == WM_NOTIFICATION_RELEASED) {
    
                    /*
                    * 获取当前选中的图标
                    */
                    Sel   = ICONVIEW_GetSel(pMsg->hWinSrc);
    
                    switch (Sel) {
                    case 0:
                    case 1:
                    case 2:
                        GUI_Delay(500);
                        ShowTips(pMsg->hWin);         //提示让用户等待
                        WFGUI_UserAPP();
                        break;
                    default:
                        break;
                    }
    
                    /* 获取ICON的句柄 */
                    hItem = WM_GetDialogItem(hParent, GUI_ID_ICONVIEW1);
                    /* 设置初始选择的图标为 -1 (表示尚未选择)*/
                    ICONVIEW_SetSel(hItem,-1);
                }
                break;
    
            default:
                break;
            }         //ID
    
            break;        //NOTIFYPARENT
    
        case WM_MOTION:
            pInfo = (WM_MOTION_INFO *)pMsg->Data.p;
            if (pInfo) {
                switch (pInfo->Cmd) {
                case WM_MOTION_INIT:
                    pInfo->SnapX = 240;   //像素对齐
                    pInfo->SnapY = 0;
                    pInfo->Period = 500;
    
                    break;
    
                case WM_MOTION_MOVE:
                    /* 禁止图标控件 ，防止误触发*/
                    for (i=0; i<VIRTUAL_WIN_NUM; i++) {
                    hWin = WM_GetDialogItem(pMsg->hWin,GUI_ID_ICONVIEW0+i);
                        WM_DisableWindow(hWin);
                    }
                    break;
    
                default:
                    break;
                }
                /* 移动结束 */
                if (pInfo->FinalMove) {
                    /* 移动结束，使能图标控件 */
                    for (i=0; i<VIRTUAL_WIN_NUM; i++) {
                    hWin = WM_GetDialogItem(pMsg->hWin,GUI_ID_ICONVIEW0+i);
                        WM_EnableWindow(hWin);
                    }
                    //xpos指向窗口移动的距离，向左移动为负。
                    //一般第一窗口移动结束时xpos=-1
                    if (pInfo->xPos >= -120 && pInfo->xPos ) {
                        WinPara.ctr_index = 0;      //第一个窗口
                        
    WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);
                    //WM_Paint(WinPara.hWinCtrl); //重绘ctrl窗口，刷新index
    
                    } else if (pInfo->xPos < -120) {  
    //一般第二窗口移动结束时xpos=-239
                        WinPara.ctr_index = 1;      //第二个窗口
                        
    WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);
                //  WM_Paint(WinPara.hWinCtrl); //重绘ctrl窗口，刷新index
                    }
    
    
                }
            }
    
            break;
    
        case WM_PAINT:  //重绘背景
            GUI_SetColor(GUI_BLACK);
    GUI_FillRect(0,0,WinPara.xSizeWin *VIRTUAL_WIN_NUM  ,WinPara.ySizeWin);
            break;        //WM_PAINT
    
        default:
            WM_DefaultProc(pMsg);
    
        }
    
    
    }

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
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

在野火GUI中，为了管理应用程序，使用了双向链表来记录应用程序的句柄，该链表的源代码由Linux双向链表修改而来。Linux链表是以头文件的形式给出的，都是宏定义，它的链表实现方式非常巧妙，有兴趣的读者可以参考这个网址的博文来学习一下：\
http://www.cnblogs.com/Anker/archive/2013/12/15/3475643.html\ 。为了使用方便，我们对Linux链表进行了封装，封装后的链表代码保存在WFGUI_APPLinkedList.c文件中，下面我们来分析链表相关的函数。

初始化链表
'''''''''''''''

Linux的链表在使用前需要进行初始化， 也就是给它一个头部结点，见 代码清单17_15_。

.. code-block:: c
    :caption: 代码清单 17‑15 初始化链表
    :linenos:
    :name: 代码清单17_15

    typedef struct {
    struct list_head listNode;
    WM_HWIN hAPP;
    } HANDLE_LIST;
    static HANDLE_LIST hAppHead; //链表头部
    
     /**
     * @brief hAPPLinkedlist_Init初始化hAPP链表
     * @param none
     * @retval none
     */
     void hAPPLinkedList_Init(void)
     {

     INIT_LIST_HEAD(&hAppHead.listNode );

     }

代码中我们定义了一个结构体类型HANDLE_LIST，它包含Linux链表的指针域list_head类型以及我们自定义的数据域类型WM_HWIN hAPP，从这里可以看出我们建立链表的目的，就是为了把各个应用程序的句柄以链表的形式串起来。

链表初始化函数hAPPLinkedList_Init是调用Linux链表的宏INIT_LIST_HEAD把全局变量hAppHead初始化为头部结点。在我们的野火GUI工程中，链表的初始化是在创建GUI桌面时在CreatDeskTop函数完成的，大家可以回头去看看 代码清单17_2_，它在函数的最后调用了hAPPLinkedList_Init。链表只要初始化一次即可，在后面读者自己添加应用程序时无需再处理。

新建并添加结点到链表
''''''''''''''''''''''''''''''

新建并添加结点到链表的封装见 代码清单17_16_。

.. code-block:: c
    :caption: 代码清单 17‑16 新建并添加结点到链表
    :linenos:
    :name: 代码清单17_16

     /**
     * @brief hAPPLinkedlist_NewNode为创建一个新的hAPP结点，分配空间
     * @param none
     * @retval 指向新结点的指针
     */
     HANDLE_LIST* hAPPLinkedList_NewNode(void)
     {
     HANDLE_LIST *app = (HANDLE_LIST *)malloc(sizeof(HANDLE_LIST));

     if (app == NULL) {
     DEBUG("\r\n hAPP linkedList malloc error\r\n ");
     return NULL;
     }
     return app;
     }

     /**
     * @brief hAPPLinkedList_AddTail增加结点到链表
     * @param none
     * @retval none
     */
     void hAPPLinkedList_AddTail(HANDLE_LIST *node)
     {
     list_add_tail(&node->listNode,&hAppHead.listNode);
     }


hAPPLinkedList_NewNode函数采用malloc来给新的结点分配空间，并把结点指针以函数返回值给出。

创建了新的结点后通常我们会把该结点添加到链表结尾，我们把新建的结点指针作为参数调用我们封装好的hAPPLinkedList_AddTail即可。

在实际的使用中，我们先使用hAPPLinkedList_NewNode函数新建一个结点，然后在创建应用程序时把应用程序窗口的句柄赋值给该结点的数据域，然后把该结点添加到链表中，这样就可以使用链表来管理应用程序句柄了。在野火GUI中，每个新建的应用程序窗口都有这样的操作，在这里，以WFGUI_Temp
erature.c文件中的温度传感器应用为例，见 代码清单17_17_。

.. code-block:: c
    :caption: 代码清单 17‑17 WFGUI_Temperature函数内容
    :linenos:
    :name: 代码清单17_17

    /**
    * @brief  WFGUI_Temperature 温度计主函数
    *
    * @param  none
    * @retval none
    */
    void WFGUI_Temperature(void)
    {
        WM_HWIN  hGraph = 0;
    
        HANDLE_LIST *hDlg = hAPPLinkedList_NewNode();
    
        WM_SetCreateFlags(WM_CF_MEMDEV);
    
        /* 根据资源表，创建温度计窗口 */
        hDlg->hAPP = GUI_CreateDialogBox(_aDialogCreate, 
        GUI_COUNTOF(_aDialogCreate), &_cbTEMPWin,
                    WinPara.hWinMain , 0, 0);
    
        /* 添加结点到链表 */
        hAPPLinkedList_AddTail(hDlg);
        /* 向ctrl窗口发送消息 */
        WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);
    
        InitTEMPSensor();
    
        /* 如果本窗口有效，则一直更新数据 */
        while (WM_IsWindow( hDlg->hAPP)) {
            if (!_Stop) {
                GUI_Delay(10);
                if (!hGraph) {
                    hGraph = WM_GetDialogItem( hDlg->hAPP, GUI_ID_GRAPH0);
                }
                //_AddValues(hGraph);
                GetTEMPData();
            }
            GUI_Delay(50);
        }
    }

我们看代码中的13~22行，先是调用了hAPPLinkedList_NewNode函数新建了一个结点，结点指针为hDlg，接着调用emXGUI的库函数GUI_CreateDialogBox创建一个温度计使用的窗口，并把函数的返回值(即温度计窗口句柄)赋值给了结点的数据域hDlg->hAPP变量，最后
调用hAPPLinkedList_AddTail函数把该结点添加到了链表尾，方便后面管理应用程序。

获取当前显示的应用句柄
'''''''''''''''''''''''''''''''''

在用户按下控制窗口的返回键时，我们会把显示在最上层的应用程序窗口关闭，而要关闭窗口，必须获得该应用程序的句柄，这时我们精心准备的应用程序链表就派上用场了，获取当前显示的应用程序句柄的函数hAPPLinkedList_GetAppTop内容见 代码清单17_18_。

.. code-block:: c
    :caption: 代码清单 17‑18 获取当前显示的应用程序
    :linenos:
    :name: 代码清单17_18

     /**
     * @brief hAPPLinkedList_GetAppTop获取显示在最上层的窗口(即链表最后一个结点)
     * @param none
     * @retval app结点句柄，没有的话返回NULL
     */
     HANDLE_LIST* hAPPLinkedList_GetAppTop(void)
     {
        HANDLE_LIST *node;


        if (!list_empty(&hAppHead.listNode)) { //若链表非空

            /* hAppHead.listNode.prev 头结点的前一个结点，即尾部结点*/
            node = list_entry(hAppHead.listNode.prev,HANDLE_LIST,listNode);

            DEBUG("\r\n node.app =%ld \\r\n ",node->hAPP);

            return node;

        } else
            return NULL;

     }

在hAPPLinkedList_GetAppTop函数中，先使用Linux链表的宏list_empty检测到链表非空时(即有至少有记录一个应用程序句柄)，调用宏list_entry来获取链表的尾部结点并存储到node指针变量中。

在野火GUI工程中，控制窗口返回键的回调函数应用了hAPPLinkedList_GetAppTop，见 代码清单17_19_。

.. code-block:: c
    :caption: 代码清单 17‑19 返回键的回调函数
    :linenos:
    :name: 代码清单17_19

    /**
    * @brief  _cbButtonWin,控制按钮窗口回调函数
    * @param  none
    * @retval none
    */
    static void _cbButtonWin(WM_MESSAGE * pMsg)
    {
        int Id,NCode;
        WM_HWIN hItem;
    
        switch (pMsg->MsgId) {
    
        case WM_PAINT:                      //重绘窗口
            GUI_SetColor(GUI_BLACK);
            GUI_FillRect(0,0,WM_GetWindowSizeX(pMsg->hWin) ,
    WM_GetWindowSizeY(pMsg->hWin));
            break;
    
        case WM_CREATE:                   //创建窗口
            /*返回键*/
            hItem = BUTTON_CreateEx(0,0,40, 20,
                                    pMsg->hWin, WM_CF_SHOW|WM_CF_MEMDEV , 0, 
                                    GUI_ID_BUTTON0);
            BUTTON_SetText(hItem, "<");
            break;
    
        case WM_NOTIFY_PARENT:              //处理子窗口消息
            Id    = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
    
            if (NCode == WM_NOTIFICATION_RELEASED) {
                if (Id == GUI_ID_BUTTON0) {
                    HANDLE_LIST *hAPPOnTop;
                    /* 获取最上层的窗口句柄 */
                    hAPPOnTop = hAPPLinkedList_GetAppTop();
                    if (hAPPOnTop != NULL) {
                        WM_DeleteWindow(hAPPOnTop->hAPP);     //  关闭窗口
                    }
                } else if (Id == GUI_ID_BUTTON1) {            
                //button1可以制作home键，现在没有实现
                }
            }
            break;
    
        default:
            break;
        }
    }

当用户按下返回键时，触发进入它的回调函数，它会运行至代码第25~37行，在处理这个返回键消息时，我们使用hAPPLinkedList_GetAppTop函数从链表中获取了正在显示的应用程序句柄结点，接着通过结点的数据域找到相应的句柄，调用emXGUI的库函数WM_DeleteWindow关闭应用程序
窗口。

删除及遍历链表结点
'''''''''''''''''''''''''''

在上面的程序处理中，关闭了应用程序，但还没有把记录应用程序句柄的结点从链表中删除，在后续的使用链表时，必然会导致错误，删除及遍历链表结点的函数见 代码清单17_20_。

.. code-block:: c
    :caption: 代码清单 17‑20 删除及遍历链表结点的函数封装
    :linenos:
    :name: 代码清单17_20

    /**
    * @brief  hAPPLinkedList_Del删除链表中的结点，并释放malloc空间
    * @param  none
    * @retval none
    */
    void hAPPLinkedList_Del(HANDLE_LIST *node)
    {
        /* TBD node在释放时没有被设置为NULL */
        if (node == NULL || (node->listNode.next == NULL && 
    node->listNode.prev == NULL)) {
            DEBUG("\r\n hAPP linkedList free error\r\n ");
            return ;
        }
    
        /* 删除在链表里的记录 */
        list_del(&node->listNode);
        /* 释放结点的malloc空间 */
        free(node);
    }
    
    /**
    * @brief  hAPPLinkedList_GetAppNode根据APP句柄获取链表结点
    * @param  none
    * @retval app结点句柄，没有的话返回NULL
    */
    HANDLE_LIST* hAPPLinkedList_GetAppNode(WM_HWIN hAPP)
    {
        struct list_head *pos;
        HANDLE_LIST *node;
    
        list_for_each(pos,&hAppHead.listNode) {
            /* TBD 这里有个warning，不知道影响大不大*/
            node = list_entry(pos,HANDLE_LIST,listNode);
            DEBUG("\r\n node.app =%ld \r\n ",node->hAPP);
    
            /* 返回与输入app句柄相同的结点 */
            if (node->hAPP == hAPP) {
                return node;
            }
        }
    
        /* 找不到与输入app句柄相同的结点 */
        if (pos == &hAppHead.listNode)
            return NULL;
    
        return NULL;
    }

在hAPPLinkedList_Del函数删除链表操作时，检查将要删除的结点是否为空，若不为空，仅需要调用Linux链表宏list_del，并把要删除的链表结点作为参数输入宏中即可，删除了链表结点后，我们还需要调用free函数释放结点的空间。

由于在我们的应用中，有时会需要使用应用程序的句柄来查找它在链表中的结点，所以我们需要遍历链表，链表遍历函数hAPPLinkedList_GetAppNode正是实现了这个功能。它以窗口句柄作为输入参数，然后调用Linux宏list_for_each遍历结点中的每一个元素，遍历时把结点中的数据域如输入
参数进行对比，如果相同，则返回该结点的指针，如果不同，则返回NULL。

当窗口关闭后，emXGUI机制会在窗口正式关闭前向该窗口发送一条WM_DELETE的消息，以使我们处理空间释放之类的事情。在野火GUI中，点击返回键关闭窗口(它的回调函数中调用WM_DeleteWindow关闭窗口)或者直接点击应用窗口右上角的关闭按钮后，emXGUI都会向该窗口发关WM_DELETE消息，见 图17_16_。

.. image:: /media/docx080.png
   :align: center
   :alt: 图 17_16 两种关闭应用程序窗口的方式
   :name: 图17_16

图 17_16 两种关闭应用程序窗口的方式

正是由于有多种关闭应用窗口的方式，在野火GUI工程中，我们统一在每个应用窗口回调函数的WM_DELETE消息中处理关闭窗口前的工作，而不会在返回键窗口调用了WM_DeleteWindow函数后，立即删除该窗口的链表结点，具体代码见前面的  代码清单17_19_。

在本教程中，我们以温度计窗口的回调函数为例，它的函数内容见 代码清单17_21_。

.. code-block:: c
    :caption: 代码清单 17‑21温度计窗口的回调函数
    :linenos:
    :name: 代码清单17_21

     /**
     * @brief _cbCallback 温度计窗口回调函数
     *
     * @param pMsg
     * @retval none
     */
     static void _cbTEMPWin(WM_MESSAGE * pMsg)
     {

        int i, NCode, Id, Value;
        WM_HWIN hDlg, hItem;
        HANDLE_LIST *appNode;

        hDlg = pMsg->hWin;

        switch (pMsg->MsgId) {

        /* ...源代码这里还有很多消息，
        由于篇幅问题在此省略了，具体可查看工程源代码...*/

        case WM_DELETE:
            /* 获取app句柄对应的链表结点 */
            appNode = hAPPLinkedList_GetAppNode(pMsg->hWin);
            if (appNode != NULL) {
            /* 删除app句柄链表里的记录 */
            hAPPLinkedList_Del(appNode);
            /* 发送消息通知ctrl窗口*/
            WM_SendMessageNoPara(WinPara.hWinCtrl,MY_MESSAGE_CTRLCHANGE);
            }
            break;

        default:
            WM_DefaultProc(pMsg);
        }
     }


在处理WM_DELETE消息时，先以pMsg->hWin(本窗口的句柄，即温度计窗口句柄)作为输入参数，调用了hAPPLinkedList_GetAppNode获取温度计窗口所在链表的结点appNode，判断appNode非空后即调用hAPPLinkedList_Del释放链表，完成链表的更新。

至此，野火GUI的框架已经讲解完毕，读者可继续阅读我们的源代码熟悉了本工程的框架，只有熟悉了工程框架，才能方便地在它之上开发出自己的应用。
