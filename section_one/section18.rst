.. vim: syntax=rst


野火GUI应用
---------------------

野火计划后续会推出基于STM32-ISO的emXGUI小程序，以独立的小程序讲解emXGUI的使用方式，让读者更加熟悉emXGUI，敬请期待。

RTT系统初始化
~~~~~~~~~~~~~~~~~~~~~~~~

RT-Thread在进行main函数前，在component.c文件中的rtthread_startup函数通过调用rt_hw_board_init初始化了systick、SDRAM、LED以及串口等外设。

初始化GUI
~~~~~~~~~~~~~~~~~~

操作系统运行后创建一个GUI专用任务，任务中调用GUI_Startup函数，它的执行流程如下：

GUI低级初始化GUI_LowLevelInit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GUI_LowLevelInit函数主要初始化分配给x_heap的堆空间、位置以及分配内存时的最小粒度，初始化后GUI可从x_heap中分配内存空间。用来管理SDRAM的空间

GUI架构层初始化GUI_Arch_Init
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GUI_Arch_Init初始化GUI架构相关的内容，包含内核动态矩形链表初始化，它用于多窗口叠加时的Z序管理；还包含了不同的绘图对象，如使用8/16/32位像素格式时都有专门的内存操作函数。

GUI内核初始化X_GUI_Init
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

X_GUI_Init会初始化GUI内核，在使用GUI前必须调用它。

初始化液晶硬件GUI_DisplayInit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GUI_DisplayInit函数初始化显示屏，用户需要自己根据外接的液晶屏初始化相应的硬件，并且需要在该函数内初始化绘图表面，初始化后把SURFACE返回。

设置绘图表面GUI_SetScreenSurface
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GUI_SetScreenSurface使用GUI_DisplayInit函数返回的绘图表面SURFACE进行初始化，设置屏幕对象。

初始化字体GUI_FontInit和GUI_SetDefFont
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GUI_FontInit函数初始化字体，使用初始化字体得到的HFONT作为函数GUI_SetDefFont的输入，可设置为默认字体。在GUI_FontInit函数中，可以设置字体的来源，如主控芯片的内部FLASH、外部的SPI-FLASH或SD卡等。

创建桌面GUI_DesktopStartup
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

以上一切准备就绪后，可通过调用GUI_DesktopStartup创建桌面。

在桌面回调函数的示例代码进行了如下操作：

-  WM_CREATE：初始化输入设备，如触摸屏、鼠标等；创建定时器；创建APP线程，APP线程包含各个应用。

-  WM_TIMER：定时器的处理消息，它会根据WM_CREATE中设置的定时器周期执行此处的内容，示例代码中在此处理触摸信息。

-  WM_ERASEBKGND：擦除背景，当需要绘制桌面背景时会进入此消息处理，示例代码中通过_EraseBackgnd绘制该背景。
