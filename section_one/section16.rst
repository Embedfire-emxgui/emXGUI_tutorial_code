.. vim: syntax=rst

emXGUI扩展功能移植
------------------------------------

* * 注意！！！！！！* *

* * 本章教程里介绍的代码都是针对旧版的，新版本配套的说明后续会持续更新。* *

* * 目前霸道开发板使用的emXGUI例程改进了不少，但大体的原理还是和旧版类似的，所以本部分内容保留，阅读源码的时候使用新版代码即可。* *

* * 当前各开发板均已配套好emXGUI的基础例程，即基础的工程模板已经搭建完成，可以根据自己的需要直接着手开发APP了。* *

在前面的教程中已经完成了emXGUI基本功能的移植，已经可以用它来做绝大部分的应用了，但在制作显示图片、中文字体等应用时，需要用到文件系统，对内存空间消耗较大的应用需要扩展外部SRAM，这些在windows不需要操心的事情，在嵌入式平台上都需要我们亲自去完善。

添加文件系统
~~~~~~~~~~~~~~~~~~

实验描述及工程文件清单
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

实验描述
''''''''''''

emXGUI有文件系统的支持后，可以显示SD卡内的图片、文件数据，以及使用SD卡内的字库文件。在这个小节我们在emXGUI_touch工程上添加fatfs文件系统，具体操作其实只是把以前移植到STM32平台的文件添加到这个工程中，非常简单。

硬件连接
''''''''''''

需要为板子接上液晶屏，液晶屏与板子的连接原理图见工程文档 ，给板子接入FAT格式的SD卡(支持32G以下的SD卡)。

主要工程文件
''''''''''''''''''

================== ========================================================================================
   工程名称         emXGUI_fatfs
emXGUI库文件        STemXGUI522/STemXGUI522_CM3_Keil.lib
     \               STemXGUI522/GUIConf.c
      \             STemXGUI522/LCDConf_FlexColor_Template.c
      \             STemXGUI522/\ GUI_X.c
      \             STemXGUI522/\ GUI_X_Touch_Analog.c 
用户编写的文件      USER/\ main.c
      \             USER/\ stm32f10x_it.c
     \              USER/bsp_led.c
      \             USER/\ bsp_ili9341_lcd.c
      \             USER/bsp_usart1.c
      \             USER/\ bsp_SysTick.c
      \             USER/bsp_touch.c
      \             USER/bsp_gpio_spi.c
      \             USER/bsp_sdio_sdcard.c 
GUI应用文件         Demo/\ GUIDEMO_Touch.c
      \             Demo/\ GUIDEMO_Fatfs.c
ST固件库            所有ST3.5版本标准库文件
文件系统            ff9/diskio.c
     \              ff9/ff.c
     \              ff9/ccbcs.c 
================== ========================================================================================

配置工程环境
''''''''''''''''''

以emWin的例程为基础，我们往该工程目录中添加fatfs文件系统相关的库文件，这些文件可以从野火STM32-ISO的例程中找到，具体fatfs移植的教程在《STM32库开发实战指南》中已有讲解。有点小区别的是，在本工程中我们使用的bsp_sdio_sdcard.c驱动是
ST官方的5.0.1版本，这个版本相对于以前使用的4.5.0版本要稳定一点，图16_1_。

.. image:: /media/docx062.png
   :align: center
   :alt: 图 16‑1 emXGUI_fatfs工程目录
   :name: 图16_1

图 16‑1 emXGUI_fatfs工程目录

测试文件系统
^^^^^^^^^^^^^^^^^^

添加了fatfs相关的bsp_sdio_sdcard.c、diskio.c、ff.c及ccbcs.c文件后，要注意在stm32f10x_it.c文件中添加sd相关的中断服务函数，见 代码清单16_1_。

.. code-block:: c
    :caption: 代码清单 16‑1要添加到stm32f10x_it.c文件的中断服务函数
    :linenos:
    :name: 代码清单16_1

<<<<<<< HEAD
       /*
       * 函数名：SDIO_IRQHandler
       * 描述 ：在SDIO_ITConfig(）这个函数开启了sdio中断 ，
       * 数据传输结束时产生中断
       * 输入 ：无
       * 输出 ：无
       */
       void SDIO_IRQHandler(void)

       {
       /* Process All SDIO Interrupt Sources */
       SD_ProcessIRQSrc();
       }


       void SD_SDIO_DMA_IRQHANDLER(void)
       {
       /* Process DMA2 Stream3 or DMA2 Stream6 Interrupt Sources */
       SD_ProcessDMAIRQ();
       }

=======
    /*
    * 函数名：SDIO_IRQHandler
    * 描述  ：在SDIO_ITConfig(）这个函数开启了sdio中断 ，
    *         数据传输结束时产生中断
    * 输入  ：无
    * 输出  ：无
    */
    void SDIO_IRQHandler(void)
        {
        /* Process All SDIO Interrupt Sources */
        SD_ProcessIRQSrc();
        }

    void SD_SDIO_DMA_IRQHANDLER(void)
        {
        /* Process DMA2 Stream3 or DMA2 Stream6 Interrupt Sources */
        SD_ProcessDMAIRQ();
        }
>>>>>>> dev

完成了以上的步骤，就可以编写测试程序了，本工程的main文件内容见 代码清单16_2_。

.. code-block:: c
    :caption: 代码清单 16‑2emXGUI_fatfs工程的main文件
    :linenos:
    :name: 代码清单16_2

<<<<<<< HEAD
      #include "stm32f10x.h"
      #include "bsp_led.h"
      #include "GUI.h"
      #include "diskio.h"
      #include "bsp_touch.h"
      #include "bsp_SysTick.h"
      #include "bsp_usart1.h"
      #include "bsp_sdio_sdcard.h"

       extern void Touch_MainTask(void);
       extern void Fatfs_MainTask(void);

       /**
       * @brief 主函数
       * @param 无
       * @retval 无
       */
       int main(void)
       {
       /* LED 端口初始化 */
       LED_GPIO_Config();

       /* 初始化触屏 */
       Touch_Init();

       /* 初始化定时器 */
       SysTick_Init();

       /* 初始化sd卡 */
       disk_initialize(0);

       /*CRC和emXGUI没有关系，只是他们为了库的保护而做的，
       这样STemXGUI的库只能用在ST的芯片上面，别的芯片是无法使用的。 */
       RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

       /* 初始化GUI */
       GUI_Init();

       /* 初始化串口*/
       USART1_Config();

       DEBUG("\r\n wildfire ISO board emXGUI test \r\n");

       GUI_Delay (20);

       #if 0
       /* 触摸校准demo */
       Touch_MainTask();
       #else
       Fatfs_MainTask();
       #endif

       }


       /END OF FILE/
=======
    #include "stm32f10x.h"
    #include "bsp_led.h"
    #include "GUI.h"
    #include "diskio.h"
    #include "bsp_touch.h"
    #include "bsp_SysTick.h"
    #include "bsp_usart1.h"
    #include "bsp_sdio_sdcard.h"

    extern void Touch_MainTask(void);
    extern void Fatfs_MainTask(void);

    /**
    * @brief  主函数
    * @param  无
    * @retval 无
    */
    int main(void)
        {
        /* LED 端口初始化 */
        LED_GPIO_Config();

        /* 初始化触屏 */
        Touch_Init();

        /* 初始化定时器 */
        SysTick_Init();

        /*初始化sd卡*/
        disk_initialize(0);

        /*CRC和emXGUI没有关系，只是他们为了库的保护而做的，
        这样STemXGUI的库只能用在ST的芯片上面，别的芯片是无法使用的。 */
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

        /* 初始化GUI */
        GUI_Init();

        /* 初始化串口*/
        USART1_Config();

        DEBUG("\r\n wildfire ISO board emXGUI test \r\n");

        GUI_Delay (20);

    #if 0
        /* 触摸校准demo */
        Touch_MainTask();
    #else
        Fatfs_MainTask();
    #endif

        }

    /**************************END OF FILE**********************/

>>>>>>> dev


在emXGUI_touch工程的基础上，初始化了各种外设用emXGUI后，在第32行添加了disk_initialize函数用于初始化SD卡及文件系统，在第52行，调用了自己编写的文件系统测试函数Fatfs_MainTask，其内容见 代码清单16_3_。

.. code-block:: c
    :caption: 代码清单 16‑3Fatfs_MainTask函数内容
    :linenos:
    :name: 代码清单16_3

<<<<<<< HEAD
       /**
       *
       * @file GUIDEMO_Fatfs.c
       * @author fire
       * @version V1.0
       * @date 2013-xx-xx
       * @brief 测试文件系统
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
       #include "bsp_sdio_sdcard.h"
       #include "bsp_usart1.h"
       #include "ff.h"
       #include "GUI.h"

       FIL fnew; /* file objects */
       FATFS fs; /* Work area (file system object) for logical drives */
       FRESULT res;
       UINT br, bw; /* File R/W count */
       BYTE buffer[4096]= {0}; /* file copy buffer */
       BYTE textFileBuffer[] = "Welcome to use Wildfire iso stm32 Development Board today is a good day";

       void Fatfs_MainTask(void)
       {
       /* 用于显示文件内容的窗口大小 */
       GUI_RECT file_content= {5,120,235,200};

       /* 给屏幕刷上背景颜色 */
       GUI_ClearRect(0,0,240,320);

       /* 设置字体颜色 */
       GUI_SetFont(&GUI_Font8x16);

       GUI_DispStringAt ("f_mount...",5,20);

       /* Register work area for each volume
       (Always succeeds regardless of disk status) */
       f_mount(0,&fs);

       /* function disk_initialize() has been called in f_open */

       GUI_DispStringAt ("f_open :newfile.txt ...",5,40);

       /* Create new file on the drive 0 */
       res = f_open(&fnew, "0:newfile.txt", FA_CREATE_ALWAYS | FA_WRITE );

       if ( res == FR_OK )
       {
       res = f_write(&fnew, textFileBuffer, sizeof(textFileBuffer), &bw);
       f_close(&fnew);
       }

       GUI_DispStringAt ("f_read :newfile.txt ...",5,60);

       res = f_open(&fnew, "0:newfile.txt", FA_OPEN_EXISTING | FA_READ);
       res = f_read(&fnew, buffer, sizeof(buffer), &br);

       printf("\r\n %s ", buffer);

       GUI_DispStringAt ("file content:",5,100);

       /* 设置前景颜色（字体颜色）*/
       GUI_SetColor(GUI_RED);

       /* 设置字体 */
       GUI_SetFont(GUI_FONT_COMIC18B_ASCII);

       /* 显示文本到屏幕上 */
       GUI_DispStringInRectWrap((const char*)buffer, &file_content,GUI_TA_LEFT,GUI_WRAPMODE_WORD) ;

       /* Close open files */
       f_close(&fnew);

       /* Unregister work area prior to discard it */
       f_mount(0, NULL);

       while (1);
       }




=======
    /**
    *********************************************
    * @file    GUIDEMO_Fatfs.c
    * @author  fire
    * @version V1.0
    * @date    2013-xx-xx
    * @brief   测试文件系统
    *********************************************
    * @attention
    *
    * 实验平台:野火 iSO STM32 开发板
    * 论坛    :http://www.chuxue123.com
    * 淘宝    :http://firestm32.taobao.com
    *
    *********************************************
    */

    #include "stm32f10x.h"
    #include "bsp_sdio_sdcard.h"
    #include "bsp_usart1.h"
    #include "ff.h"
    #include "GUI.h"

    FIL fnew;             /* file objects */
    FATFS fs;             /* Work area (file system object) for logical drives */
    FRESULT res;
    UINT br, bw;                  /* File R/W count */
    BYTE buffer[4096]= {0};           /* file copy buffer */
    BYTE textFileBuffer[] = "Welcome to use Wildfire iso stm32 Development 
    Board today is a good day";

    void Fatfs_MainTask(void)
        {
        /* 用于显示文件内容的窗口大小 */
        GUI_RECT file_content= {5,120,235,200};

        /* 给屏幕刷上背景颜色 */
        GUI_ClearRect(0,0,240,320);

        /* 设置字体颜色 */
        GUI_SetFont(&GUI_Font8x16);

        GUI_DispStringAt ("f_mount...",5,20);

        /* Register work area for each volume
        (Always succeeds regardless of disk status) */
        f_mount(0,&fs);

        /* function disk_initialize() has been called in f_open */

        GUI_DispStringAt ("f_open :newfile.txt ...",5,40);

        /* Create new file on the drive 0 */
        res = f_open(&fnew, "0:newfile.txt", FA_CREATE_ALWAYS | FA_WRITE );

        if ( res == FR_OK )
            {
            res = f_write(&fnew, textFileBuffer, sizeof(textFileBuffer), &bw);
            f_close(&fnew);
            }

        GUI_DispStringAt ("f_read :newfile.txt ...",5,60);

        res = f_open(&fnew, "0:newfile.txt", FA_OPEN_EXISTING | FA_READ);
        res = f_read(&fnew, buffer, sizeof(buffer), &br);

        printf("\r\n %s ", buffer);

        GUI_DispStringAt ("file content:",5,100);

        /* 设置前景颜色（字体颜色）*/
        GUI_SetColor(GUI_RED);

        /* 设置字体 */
        GUI_SetFont(GUI_FONT_COMIC18B_ASCII);

        /* 显示文本到屏幕上 */
        GUI_DispStringInRectWrap((const char*)buffer, 
    &file_content,GUI_TA_LEFT,GUI_WRAPMODE_WORD) ;

        /* Close open files */
        f_close(&fnew);

        /* Unregister work area prior to discard it */
        f_mount(0, NULL);

        while (1);
    }
>>>>>>> dev

本函数先在sd卡中创建一个空白的txt文件，并向txt文件写入句子“Welcome to use Wildfire iso stm32 Development Board today is a good
day”，关闭文件后重新打开，读取文件的内容，并把读到的内容使用emXGUI的库函数显示到液晶屏上。

实验步骤及现象
^^^^^^^^^^^^^^^^^^^^^

实验步骤
''''''''''''

直接把程序下载到STM32-ISO板子上，注意要给板子插入一张格式为FAT的SD卡(支持32G以下的SD卡)。

.. _实验现象-7:

实验现象
''''''''''''

液晶屏上显示出文件系统调用的函数流程f_mount、f_open、f_read等，在最后以红色字体显示从文件中读取到的文件内容，见 图16_2_。

.. image:: /media/docx063.png
   :align: center
   :alt: 图 16_2 emXGUI_fatfs实验截图
   :name: 图16_2

图 16_2 emXGUI_fatfs实验截图

使用外部SRAM
~~~~~~~~~~~~~~~~~~~~~~~~

.. _实验描述及工程文件清单-1:

实验描述及工程文件清单
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. _实验描述-1:

实验描述
''''''''''''

复杂的emXGUI应用场合对RAM空间消耗较大，而片上RAM空间的资源非常紧张，这时我们就会用到外部扩展的SRAM芯片了，当STM32平台上使用外部SRAM时，对emXGUI也需要进行一些配置。

.. _硬件连接-1:

硬件连接
''''''''''''

为板子接上液晶屏，液晶屏与板子的连接原理图见工程文档 ，给板子接入FAT格式的SD卡(支持32G以下的SD卡)，还需要接入配套的SRAM模块，野火使用的外部SRAM芯片型号为IS62WV51216BLL，其大小为1MB。野火外部SRAM模块实物见硬件文档。它与STM32芯片的连接见 图16_3_ 。

.. image:: /media/docx064.png
   :align: center
   :alt: 图 16‑3 SRAM模块原理图
   :name: 图16_3

图 16‑3 SRAM模块原理图

.. _主要工程文件-1:

主要工程文件
''''''''''''''''''

================== ========================================================================================
   工程名称         emXGUI_sram
 emXGUI库文件        STemXGUI522/STemXGUI522_CM3_Keil.lib

                   STemXGUI522/GUIConf.c

                   STemXGUI522/LCDConf_FlexColor_Template.c

                   STemXGUI522/\ GUI_X.c

                   STemXGUI522/\ GUI_X_Touch_Analog.c 
用户编写的文件       USER/main.c

                   USER/\ stm32f10x_it.c

                   USER/bsp_led.c

                   USER/\ bsp_ili9341_lcd.c

                   USER/bsp_usart1.c

                   USER/\ bsp_SysTick.c

                   USER/bsp_touch.c

                   USER/bsp_gpio_spi.c

                   USER/bsp_sdio_sdcard.c

                   USER/\ bsp_fsmc_sram.c 
GUI应用文件         Demo/GUIDEMO_Touch.c

                   Demo/\ GUIDEMO_Fatfs.c
ST固件库            所有ST3.5版本标准库文件 
文件系统            ff9/diskio.c

                   ff9/ff.c

                   ff9/ccbcs.c 
================== ========================================================================================

.. _配置工程环境-1:

配置工程环境
''''''''''''''''''

以emXGUI_sram中的例程为基础，我们往该工程目录中添加SRAM的驱动bsp_fsmc_sram.c文件。

初始化外部SRAM
^^^^^^^^^^^^^^^^^^^^^^^^^^^

我们先从emXGUI_sram这个工程的main文件来分析一下，相对于上一个工程，它的改动不大，仅是在第32行添加了对FSMC_SRAM_Init函数的调用，见 代码清单16_4_。

.. code-block:: c
    :caption: 代码清单 16‑4 emXGUI工程的main文件
    :linenos:
    :name: 代码清单16_4

     #include "stm32f10x.h"
     #include "bsp_led.h"
     #include "GUI.h"
     #include "diskio.h"
     #include "bsp_touch.h"
     #include "bsp_SysTick.h"
     #include "bsp_usart1.h"
     #include "bsp_sdio_sdcard.h"
     #include "bsp_fsmc_sram.h"

     extern void Touch_MainTask(void);
     extern void Fatfs_MainTask(void);

     /**
     * @brief 主函数
     * @param 无
     * @retval 无
     */
     int main(void)
     {
<<<<<<< HEAD
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

     /*CRC和emXGUI没有关系，只是他们为了库的保护而做的，
     这样STemXGUI的库只能用在ST的芯片上面，别的芯片是无法使用的。 */
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

     /* 初始化GUI */
     GUI_Init();

     /* 初始化串口*/
     USART1_Config();

     DEBUG("\r\n wildfire ISO board emXGUI test \\r\n");

     GUI_Delay (20);

     #if 0
     /* 触摸校准demo */
     Touch_MainTask();
     #else
     Fatfs_MainTask();
     #endif
=======
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

        /*CRC和emXGUI没有关系，只是他们为了库的保护而做的，
        这样STemXGUI的库只能用在ST的芯片上面，别的芯片是无法使用的。 */
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

        /* 初始化GUI */
        GUI_Init();

        /* 初始化串口*/
        USART1_Config();

        DEBUG("\r\n wildfire ISO board emXGUI test \\r\n");

        GUI_Delay (20);

    #if 0
        /* 触摸校准demo */
        Touch_MainTask();
    #else
        Fatfs_MainTask();
    #endif
>>>>>>> dev

     }

     /END OF FILE/

由于SRAM也是使用FSMC外设驱动的，所以它的初始化和液晶屏的很类似，主要过程是对使用到的的GPIO引脚初始化、配置FSMC的使用模式，在这里不对SRAM的初始化函数FSMC_SRAM_Init详细讲解。

给emXGUI分配外部SRAM空间
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

本章的重点在于给emXGUI分配外部SRAM空间，关于emXGUI 的内存空间配置，都会于GUIConf.c文件中，在不使用外部SRAM时，我们也需要配置该文件，前面章节已有介绍，在本工程中，该文件内容见 代码清单16_5_。

.. code-block:: c
    :caption: 代码清单 16‑5 emXGUI_sram工程的GUIConf.c文件内容
    :linenos:
    :name: 代码清单16_5

     #include "GUI.h"
     #include "bsp_fsmc_sram.h"

     /*
     *
     * Defines
     *
     *
     */

     //
     // Define the available number of bytes available for the GUI
     //
     #define GUI_NUMBYTES 1024*53 //modify by fire 原值为 0x200000

     #define GUI_BLOCKSIZE 0x80
     /*
     *
     * Public code
     *
     *
     *
     *
     *
     * GUI_X_Config
     *
     * Purpose:
     * Called during the initialization process in order to set up the
     * available memory for the GUI.
     */
     void GUI_X_Config(void)
     {
<<<<<<< HEAD
     #if 0
     //
     // 32 bit aligned memory area
     //
     static U32 aMemory[GUI_NUMBYTES / 4];
     //
     // Assign memory to emXGUI
     //
     GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES);

     GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);
     //
     // Set default font
     //
     GUI_SetDefaultFont(GUI_FONT_6X8);
     #else
     //
     // 32 bit aligned memory area
     //
     //
     // Assign memory to emXGUI
     //
     GUI_ALLOC_AssignMemory((U32 *)Bank1_SRAM3_ADDR, 1024*1024);

     GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);
     //
     // Set default font
     //
     GUI_SetDefaultFont(GUI_FONT_6X8);
     #endif
=======
    #if 0
        //
        // 32 bit aligned memory area
        //
        static U32 aMemory[GUI_NUMBYTES / 4];
        //
        // Assign memory to emXGUI
        //
        GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES);

        GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);
        //
        // Set default font
        //
        GUI_SetDefaultFont(GUI_FONT_6X8);
    #else
        //
        // 32 bit aligned memory area
        //
        //
        // Assign memory to emXGUI
        //
        GUI_ALLOC_AssignMemory((U32 *)Bank1_SRAM3_ADDR, 1024*1024);

        GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);
        //
        // Set default font
        //
        GUI_SetDefaultFont(GUI_FONT_6X8);
    #endif
>>>>>>> dev
     }

     /* End of file */


在本文件中修改的内容为GUI_X_Config函数中调用的GUI_ALLOC_AssignMemory文件的输入参数(请对比第40行及第54行)。我们知道GUI_ALLOC_AssignMemory库函数是用于给emXGUI分配内存空间的，其中第一个输入参数为分配给它的内存空间首地址，第二个参数为内
存空间大小。

原来没有使用外部SRAM的时候，我们定义了一个大小为1024*53字节大小的数组aMemory，并把它作为GUI_ALLOC_AssignMemory函数的输入参数，作为分配给emXGUI。

在使用外部SRAM时，我们把外部SRAM的首地址Bank1_SRAM3_ADDR作为emXGUI内存空间的首地址，大小为1024*1024字节(1MB)，即我们简单粗暴地把整个外部SRAM芯片的空间都分配给了emXGUI使用。其中Bank1_SRAM3_ADDR参数是一个宏，它是一个指向外部SRAM
的首地址，使用原理就和FSMC驱动ILI9341液晶屏一样，宏定义如下：

.. code-block:: c
    :caption: Bank1_SRAM3_ADDR
    :linenos:

    #define Bank1_SRAM3_ADDR ((uint32_t)0x68000000)

完成了emXGUI的内存分配之后，就没有之后了，添加外部SRAM的支持就是这么简单。

.. _实验步骤及现象-1:

实验步骤及现象
^^^^^^^^^^^^^^^^^^^^^

.. _实验步骤-1:

实验步骤
''''''''''''

直接把程序下载到STM32-ISO板子上，注意要给板子插入一张格式为FAT的SD卡(支持32G以下的SD卡)，给STM32-ISO板子接入外部SRAM模块。

.. _实验现象-8:

实验现象
''''''''''''

正常的实验现象跟上一个章节一样。液晶屏上显示出文件系统调用的函数流程f_mount、f_open、f_read等，在最后以红色字体显示从文件中读取到的文件内容，见 图16_2_。

.. image:: /media/docx063.png
   :align: center
   :alt: 图 16‑4emXGUI_fatfs实验截图
   :name: 图16_4

图 16‑4 emXGUI_fatfs实验截图
