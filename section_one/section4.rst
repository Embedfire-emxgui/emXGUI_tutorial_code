.. vim: syntax=rst

移植emXGUI到STM32
-------------------------------------

要使emXGUI在特定的硬件平台上运行，需要为emXGUI提供与底层硬件操作相关的函数接口，主要为液晶驱动接口、触摸屏接口以及内存管理接口。

本章以配套例程“emXGUI工程模板（RTT+emXGUI）”为例，对emXGUI的执行过程和移植步骤进行解构，阅读时请打开该工程配套学习。

emXGUI的初始化过程
~~~~~~~~~~~~~~~~~~~~~~~~

在移植emXGUI前，需要了解它的初始化过程以及它依赖的硬件接口。在示例代码中，emXGUI通过GUI_Startup函数初始化依赖的设备，以初始化emXGUI运行所需要的环境，在这个GUI_Startup函数里，调用了emXGUI底层的配置函数，具体见表格
4‑1，完成了存储器分配、屏幕类型配置及初始化液晶驱动的工作。

表格 4‑1 GUI_Startup调用到的初始化函数

====================  ===================  =====================================  ========
       函数名              所在文件                        功能                   是否必须
====================  ===================  =====================================  ========
GUI_MEM_Init          gui_mem_port.c       初始化GUI内核使用的内存空间            是
GUI_DisplayInit       gui_lcd_port.c       初始化液晶屏及GUI的绘图表面            是
GUI_Default_FontInit  gui_font_port.c      初始化GUI使用的默认字体                是
GUI_Log_Init          gui_log_port.c       初始化日志输出接口，一般使用串口       是
GUI_VMEM_Init         gui_mem_port.c       初始化GUI提供给用户的VMEM内存空间      否
GUI_InputInit         gui_input_port.c     初始化输入设备，如鼠标、键盘、触摸屏   否
RES_DevInit           gui_resource_port.c  初始化资源设备，如外部SPI-FLASH、SD卡  否
====================  ===================  =====================================  ========

GUI_Startup函数的示例代码具体见 代码清单4_0_ 。

.. code-block:: c
    :caption: 代码清单 5-0 GUI_Startup示例代码（gui_startup.c文件）
    :linenos:
    :name: 代码清单4_0

    /***********************第1部分*************************/
    /**
    * @brief  GUI低级别的初始化,这是GUI的第一个初始化函数
    * @param  无
    * @retval TRUE:成功; FALSE：失败.
    */
    static BOOL GUI_LowLevelInit(void)
    {
    
        //GUI Core内存管理初始化
        GUI_MEM_Init();
    
    #if(GUI_VMEM_EN)
        //vmem内存管理初始化
        GUI_VMEM_Init();
    #endif
    
        //初始化日志接口
        if (GUI_Log_Init() != TRUE) {

        }

        /* 直接返回TRUE，为了部分设备初始化不正常不影响后续运行 */
        return TRUE;
    }
    /**********************第2部分**************************/
    /**
    * @brief  启动GUI，包含各种内存、液晶、输入设备的初始化
    * @param  无
    * @retval 无
    */
    void  GUI_Startup(void)
    {
        SURFACE *pSurf=NULL;
        HFONT hFont=NULL;
        /**********************第3部分**************************/
        if (!GUI_LowLevelInit()) { //GUI低级初始化.
            GUI_ERROR("GUI_LowLevelInit Failed.");
            return;
        }
        /**********************第4部分**************************/
        if (!GUI_Arch_Init()) { //GUI架构适配层初始化.
            GUI_ERROR("GUI_Arch_Init Failed.");
            return;
        }
        
        if (!X_GUI_Init()) {  //GUI内核初始化.
            GUI_ERROR("X_GUI_Init Failed.");
            return;
        }
        /**********************第5部分**************************/
        pSurf =GUI_DisplayInit(); //显示设备初始化
        if (pSurf==NULL) {
            GUI_ERROR("GUI_DisplayInit Failed.");
            return;
        }
        GUI_SetScreenSurface(pSurf); //设置屏幕Surface对象
        /**********************第6部分**************************/
    #if(GUI_RES_DEV_EN)
        //资源设备初始化（FLASH）
        if (RES_DevInit() != TRUE) {
            GUI_ERROR("RES_DevInit Failed.");
        }
    #endif
        /**********************第7部分**************************/
    #if(GUI_INPUT_DEV_EN)
        //初始化输入设备
        if (GUI_InputInit() != TRUE) {
            GUI_ERROR("GUI_InputInit Failed.");
        }
        GL_CursorInit(pSurf,pSurf->Width>>1,pSurf->Height>>1); //初始化光标
    #endif
        /**********************第8部分**************************/
        hFont =GUI_Default_FontInit(); //初始化默认的字体
        if (hFont==NULL) {
            GUI_ERROR("GUI_Default_FontInit Failed.");
            return;
        }
        GUI_SetDefFont(hFont);  //设置默认的字体
        /**********************第9部分**************************/
        GUI_DesktopStartup(); //启动桌面窗口(该函数不会返回).
    }

在这段代码中条件编译中的内容如“#if(GUI_VMEM_EN) …#endif”、“#if(GUI_RES_DEV_EN) …#endif”是可以通过gui_drv_cfg.h头文件配置的宏，可以根据自己的应用需要决定是否加入这些接口。

下面对这段代码的各个部分进行讲解，下面的描述中，“接口”一般指需要用户自行编写的具体驱动，“库函数”一般是指GUI中提供API：

-  第1部分。GUI_LowLevelInit函数，它包含最基础的初始化内容，是GUI_Startup函数第一个调用的初始化函数，它包含内存管理接口GUI_MEM_Init、GUI_VMEM_Init和日志输出接口GUI_Log_Init的初始化。

1) 其中GUI_MEM_Init管理的内存是后续GUI_Arch_Init、X_GUI_Init等GUI库函数使用到的内存空间，所以这段内存初始化必须在调用任何一个GUI API函数之前完成。

2) GUI_VMEM_Init初始化的是提供给用户使用的VMEM和GMEM内存，应用中没有使用的话可以不初始化。

3) GUI_Log_Init初始化的是日志输出接口，提前初始化以便后续代码运行时能正常输出调试信息。

-  第2部分。内容是GUI_Startup函数的主体；

-  第3部分。调用了前面的GUI_LowLevelInit函数初始化基础设备。

-  第4部分。调用库函数GUI_Arch_Init初始化GUI的架构层，它主要包含适配不同类型液晶屏的绘图引擎；调用X_GUI_Init函数初始化GUI内核。

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
~~~~~~~~~~~~~~~~

使用操作系统时，需要给emXGUI提供操作系统的接口，emXGUI的内核使用这些接口管理系统资源，便于适配不同的操作系统。

在emXGUI资料的如下目录提供了常用的操作系统接口范例：

操作系统接口范例目录：emxgui\arch\OS_Options

.. image:: /media/docx010.png
   :align: center
   :alt: 图 4_1 常用操作系统的emXGUI接口示例文件

图 4_1 常用操作系统的emXGUI接口示例文件

以本教程配套的RT-Thread系统为例，它的操作系统接口示例文件为X_GUI_RTT.c，具体见 代码清单4_1_ 。

.. code-block:: c
    :caption: 代码清单 4_1 配置操作系统接口（X_GUI_RTT.c文件）
    :linenos:
    :name: 代码清单4_1

    /*
    函数功能: 创建一个互斥(该互斥锁必须支持嵌套使用)
    返回: 互斥对象句柄(唯一标识)
    说明: 互斥对象句柄按实际OS所定,可以是指针,ID号等...
    */
    GUI_MUTEX*  GUI_MutexCreate(void)
    {
        return (GUI_MUTEX*)rt_mutex_create(NULL,RT_IPC_FLAG_FIFO);
    }
    /*
    函数功能: 互斥锁定
    参数: hMutex(由GUI_MutexCreate返回的句柄);
        time 最长等待毫秒数,0立既返回,0xFFFFFFFF,一直等待
    返回: TRUE:成功;FALSE:失败或超时
    说明: .
    */
    BOOL  GUI_MutexLock(GUI_MUTEX *hMutex,U32 time)
    {

    if (rt_mutex_take((rt_mutex_t)hMutex,rt_tick_from_millisecond(time))==RT_EOK) {
            return TRUE;
        }
        return  FALSE;
    }
    /*
    函数功能: 互斥解锁
    参数: hMutex(由GUI_MutexCreate返回的句柄);
    返回: 无
    说明: .
    */
    void  GUI_MutexUnlock(GUI_MUTEX *hMutex)
    {
        rt_mutex_release((rt_mutex_t)hMutex);
    }
    /*
    函数功能: 互斥删除
    参数: hMutex(由GUI_MutexCreate返回的句柄);
    返回: 无
    说明: .
    */
    void  GUI_MutexDelete(GUI_MUTEX *hMutex)
    {
        rt_mutex_delete((rt_mutex_t)hMutex);
    }
    /*
    函数功能: 创建一个信号量
    参数: init: 信号量初始值; max: 信号量最大值
    返回: 信号量对象句柄(唯一标识)
    说明: 信号量对象句柄按实际OS所定,可以是指针,ID号等...
    */
    GUI_SEM*  GUI_SemCreate(int init,int max)
    {
        return (GUI_SEM*)rt_sem_create(NULL,init,RT_IPC_FLAG_FIFO);
    }
    /*
    函数功能: 信号量等待
    参数: hsem(由GUI_SemCreate返回的句柄);
        time 最长等待毫秒数,0立既返回,0xFFFFFFFF,一直等待
    返回: TRUE:成功;FALSE:失败或超时
    说明: .
    */
    BOOL  GUI_SemWait(GUI_SEM *hsem,U32 time)
    {
        if (rt_sem_take((rt_sem_t)hsem,rt_tick_from_millisecond(time))== RT_EOK) {
            return TRUE;
        }
        return FALSE;
    }
    /*
    函数功能: 信号量发送
    参数: hsem(由GUI_SemCreate返回的句柄);
    返回: 无
    说明: .
    */
    void  GUI_SemPost(GUI_SEM *hsem)
    {
        rt_sem_release((rt_sem_t)hsem);
    }
    /*
    函数功能: 信号量删除
    参数: hsem(由GUI_SemCreate返回的句柄);
    返回: 无
    说明: .
    */
    void  GUI_SemDelete(GUI_SEM *hsem)
    {
        rt_sem_delete((rt_sem_t)hsem);
    }

    /*
    函数功能: 获得当前线程句柄(唯一标识)
    参数: 无
    返回: 当前线程唯一标识,按实际OS所定,可以是指针,ID号等...
    说明: .
    */
    HANDLE  GUI_GetCurThreadHandle(void)
    {
        return  (HANDLE)rt_thread_self();
    }
    
    /*
    函数功能: 获得当前系统时间(单位:毫秒)
    参数: 无
    返回: 当前系统时间
    说明: .
    */
    U32 GUI_GetTickCount(void)
    {
        U32 i;
    
        i=rt_tick_get();
    
        return (i*1000)/RT_TICK_PER_SECOND;
    
    }
    
    /*
    函数功能: 最短时间内让出CPU
    参数: 无
    返回: 无
    说明: 按具体OS情况而定,最简单的方法是:OS Delay 一个 tick 周期.
    */
    void  GUI_Yield(void)
    {
        rt_thread_delay(2);
    }
    
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

示例代码就是针对具体的操作系统进行封装，它封装的操作系统接口总结如表格 5‑2，主要包括互斥信号量、信号量的创建、删除、等待和释放的操作，还包含有获取任务句柄、当前系统时间戳以及延时相关的操作。

表格 4_2 需要提供给emXGUI的操作系统接口

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
~~~~~~~~~~~~~~~~

GUI_MEM_Init和GUI_VMEM_Init接口是GUI_Startup调用的第一个初始化函数，它们的示例代码位于gui_mem_port.c文件。

在本示例代码中，使用了两段内存空间，具体见 图4_2_ 和 表格4_3_ 。

.. image:: /media/docx011.png
   :align: center
   :alt: 图 4_2 内存管理接口示意图
   :name: 图4_2

图 4_2 内存管理接口示意图

表格 4_3 示例代码的内存管理接口

.. _表格4_3:

==============  ==================================  ========
 内存管理接口                  说明                 是否必须
==============  ==================================  ========
GUI_MEM_Init    初始化emXGUI内核对象使用的内存空间  是
GUI_MEM_Alloc   emXGUI内核对象申请内存的接口        是
GUI_MEM_Free    emXGUI内核对象释放内存的接口        是
GUI_VMEM_Init   初始化提供给用户使用的内存空间      否
GUI_VMEM_Alloc  从用户内存块申请空间                否
GUI_VMEM_Free   释放空间回用户内存块                否
GUI_GRAM_Alloc  申请空间作为液晶显存                否
GUI_GRAM_Free   释放液晶显存                        否
==============  ==================================  ========

此处我们分别把这三类管理接口相关的内存分别称为MEM、VMEM以及GRAM，说明如下：

-  MEM是emXGUI内核对象申请内存的区域，即GUI内核都通过GUI_MEM_Alloc接口申请空间。创建的GUI对象越多，就需要越大的MEM空间，推荐这部分内存空间至少为8KB。

-  VMEM是提供给用户使用的内存空间，若用户的应用程序没有从VMEM申请空间，可以不实现该接口。

-  GRAM用于动态申请液晶显存的空间，如STM32F429的LTDC外设需要一块内存区域存储液晶像素数据。在本示例中液晶驱动使用固定的内存空间，不需要从GRAM中分配，并且为方便起见，直接让GRAM与VMEM使用同一块内存区域进行管理。

MEM内存接口
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

示例代码中的MEM内存直接封装了RT-Thread系统的rt_malloc和rt_free接口，具体见下 。

.. code-block:: c
    :caption: 代码清单 4_3 MEM内存管理接口（gui_mem_port.c文件）
    :linenos:
    :name: 代码清单4_3

    /**
    * @brief  创建一个内存堆（用于GUI内核对象）,可参考vmem配置
    * @retval 无
    */
    void  GUI_MEM_Init(void)
    {
        /* 本示例中的GUI内核对象使用 rt_malloc ，
        它已由rtt系统初始化*/
        return ;
    }

    /**
    * @brief  动态内存申请(用于GUI内核对象)
    * @param  size 要申请的内存大小
    * @retval 申请到的内存指针
    */
    void* GUI_MEM_Alloc(U32 size)
    {
        void *p=NULL;

        p =rt_malloc(size);
        if (p==NULL) {
            GUI_ERROR("GUI_MEM_Alloc.");
        }

        return p;
    }

    /**
    * @brief  释放内存(用于GUI内核对象)
    * @param  p:需要释放的内存首址
    * @retval 无
    */
    void  GUI_MEM_Free(void *p)
    {
        rt_free(p);
    }

由于使用RT-Thread系统接口管理，初始化已经由系统实现，这段代码的GUI_MEM_Init为空，在RT-Thread系统启动前就完成了内存堆的初始化。而配置该空间的大小则是在gui_drv_cfg.h和board.c文件中实现的，具体见 代码清单4_4_ 。

.. code-block:: c
    :caption: 代码清单 4_4 RT-Thread内存空间的初始化（gui_drv_cfg.h和board.c文件）
    :linenos:
    :name: 代码清单4_4

    /***********************************************/
    /**gui_drv_cfg.h文件**/
    /* GUI内核使用的存储区大小，推荐最小值为8KB */
    #define  GUI_CORE_MEM_SIZE  (32*1024)                (1)
    /***********************************************/
    /**board.c文件**/
    #define RT_HEAP_SIZE (GUI_CORE_MEM_SIZE)             (1)
    /* 从内部SRAM里面分配一部分静态内存来作为rtt的堆空间，这里配置为4KB */
    static uint8_t rt_heap[RT_HEAP_SIZE];		(2)		
    RT_WEAK void *rt_heap_begin_get(void) 	     (3)
    {
        return rt_heap;
    }
    
    RT_WEAK void *rt_heap_end_get(void) 			(4)
    {
        return rt_heap + RT_HEAP_SIZE;
    }

这段代码中的第1部分定义了MEM存储区大小的宏GUI_CORE_MEM_SIZE，第2部分利用该宏定义了一个静态大小为GUI_CORE_MEM_SIZE的数组rt_heap，第3部分是RT-Thread内存堆管理的接口，用于获取内存空间的边界，即数组rt_heap的起始和结束地址。

用户可通过gui_drv_cfg.h中的宏GUI_CORE_MEM_SIZE改变MEM区域的大小，本示例中的大小为32KB。

若使用其它没有提供内存堆管理接口的操作系统，可以参考下面VMEM接口的配置方式定制MEM内存空间。

VMEM和GRAM内存接口
^^^^^^^^^^^^^^^^^^^^^^^^^^

使用emXGUI的x_libc中的x_heap可管理多个内存堆，示例代码正是使用x_heap对VMEM和GRAM内存堆进行管理，具体见  代码清单4_5_  。

.. code-block:: c
    :caption: 代码清单 4_5 VMEM和GRAM内存接口（gui_drv_cfg.h和gui_mem_port.c文件）
    :linenos:
    :name: 代码清单4_5

    /***********************第1部分*************************/
    /**gui_drv_cfg.h文件**/
    /* 配置vmem的基地址，大小以及分配粒度 */
    /* 是否使能VMEM内存堆 */
    #define  GUI_VMEM_EN      1
    /* 内存堆的基地址，可以为内部SRAM、外扩的SDRAM等 */
    #define VMEM_BASE         0xD0200000  // 本SDRAM前2MB给LCD控制器作为显存了 
    /* 内存堆的总大小，单位为字节 */
    #define VMEM_SIZE         (6<<20)     // 6MB 
    /* 最小分配粒度，单位为字节*/
    #define VMEM_ALLOC_UNIT   (64)         //64字节   
    /*..gui_mem_port.c文件..*/
    /***********************第2部分*************************/
    #if(GUI_VMEM_EN)
    /* VMEM内存管理 */
    /* 互斥信号量 */
    static GUI_MUTEX *mutex_vmem = NULL;
    /* 内存堆管理句柄 */
    static  heap_t heap_vmem;
    /* VMEM缓冲区 */
    static uint8_t buff_vmem[VMEM_SIZE] __attribute__((at(VMEM_BASE)));
    #endif
    /***********************第3部分*************************/
    /**
    * @brief  创建一个内存堆
    * @note  使用vmalloc前必须调用本函数初始化内存堆句柄
    * @retval 无
    */
    void GUI_VMEM_Init(void)
    {
    #if(GUI_VMEM_EN)
        mutex_vmem = GUI_MutexCreate();
        x_heap_init(&heap_vmem,
                    (void*)buff_vmem,
                    VMEM_SIZE,
                    VMEM_ALLOC_UNIT);  /* 创建一个内存堆 */
    #endif
    }
    
    /**
    * @brief  从内存堆里申请空间
    * @param  size 要申请的内存大小
    * @retval 申请到的内存指针
    */
    void* GUI_VMEM_Alloc(u32 size)
    {
    #if(GUI_VMEM_EN)
        u8 *p;
        GUI_MutexLock(mutex_vmem,5000);
        p =x_heap_alloc(&heap_vmem,size);
        GUI_MutexUnlock(mutex_vmem);
        return p;
    #endif
    }
    
    /**
    * @brief  释放内存
    * @param  p:需要释放的内存首址
    * @retval 无
    */
    void GUI_VMEM_Free(void *p)
    {
    #if(GUI_VMEM_EN)
        GUI_MutexLock(mutex_vmem,5000);
        x_heap_free(&heap_vmem,p);
        GUI_MutexUnlock(mutex_vmem);
    #endif
    }

    /***********************第4部分*************************/
    /**
    * @brief  显示动态内存申请(用于GUI显示器缓存)
    * @param  size 要申请的内存大小
    * @retval 申请到的内存指针
    */
    void* GUI_GRAM_Alloc(U32 size)
    {
        return GUI_VMEM_Alloc(size);
    }

    /**
    * @brief  显示动态内存申请(用于GUI显示器缓存)
    * @param  p:需要释放的内存首址
    * @retval 无
    */
    void  GUI_GRAM_Free(void *p)
    {
        GUI_VMEM_Free(p);
    }

这段代码说明如下：

-  第1部分。这是gui_drv_cfg.h文件中的配置内容，它包含是否使能VMEM内存堆、内存堆的基地址、大小以及最小分配粒度的配置。示例中VMEM使用外部SDRAM所在的存储空间。

-  第2部分。定义内存堆管理用到的静态变量，如互斥信号量指针mutex_vmem、内存堆管理句柄heap_vmem以及缓冲区数组buff_vmem，其中缓冲区数组的基地址和大小是由第1部分中的宏配置的。

-  第3部分。在x_libc库函数x_heap_init/alloc/free之上添加互斥信号量的创建、申请以及释放的操作，封装得到GUI_VMEM_Init/Alloc/Free接口。

-  第4部分。直接把GUI_VMEM_Alloc和GUI_VMEM_Free封装成GRAM使用的GUI_GRAM_Alloc和GUI_GRAM_Free接口，所以示例代码中VMEM和GRAM使用相同的内存空间。

本示例只是粗略地分配外部SDRAM的空间作为VMEM使用，实际应用中请根据需要修改gui_drv_cfg.h文件重新定制，提供SDRAM空间的利用率。有需要也可以参考VMEM的接口管理其它内存堆。

配置日志接口
~~~~~~~~~~~~~~~~~~

在emXGUI的内核中使用了日志输出函数GUI_Printf，所以即使是不希望有输出，也要提供一个空的GUI_Printf函数。本示例中使用RT-Thread系统的rt_kprintf进行输出，具体见 代码清单4_6_ 。

.. code-block:: c
    :caption: 代码清单 4_6 日志接口（gui_log_port.c文件）
    :linenos:
    :name: 代码清单4_6

    /**
    * @brief  初始化GUI日志接口
    * @param  无
    * @retval 是否初始化正常
    */
    BOOL  GUI_Log_Init(void)
    {
        /* 本例子在board.c文件中 rtt系统启动时就已初始化，此处不再重复 */
        /* 初始化串口 */
    //  Debug_USART_Config();
        return TRUE;
    }

    /**
    * @brief  格式化字符串输出
    * @param  可变参数
    * @note   如果不用输出GUI调试信息,这个函数可以为空
    * @retval 无
    */
    void  GUI_Printf(const char *fmt,...)
    {
    #if 0
        x_va_list ap;
        char *buf;
        static  char str_buf[256];
        static  GUI_MUTEX *mutex_gui_printf=NULL;
        ////
        buf =str_buf/*(char*)GUI_MEM_Alloc(256)*/;
        if (buf) {

            if (GUI_MutexLock(mutex_gui_printf,0xFFFFFFFF)) {
                x_va_start(ap,fmt);
                x_vsprintf(buf,fmt,ap);
                /* 底层需要提供DebugPuts接口进行输出 */
                DebugPuts(buf);
                //DebugOutput(buf);

                GUI_MutexUnlock(mutex_gui_printf);
                x_va_end(ap);
            }

            //GUI_MEM_Free(buf);
        }
    #else

        rt_kprintf(fmt);
    #endif

    }

代码中的GUI_Log_Init是GUI_Startup函数会调用的日志初始化接口，可在此处初始化串口作为日志输出，本示例中在RT-Thread系统正式运行前就已经在board.c文件的rt_hw_board_init函数初始化了，此处不再重复。

示例中的GUI_Printf直接封装了RT-Thread系统的rt_kprintf输出函数，若不使用rt_kprintf，可以使用代码中条件编译 的另一个分支，底层提供DebugPuts接口即可，DebugPuts函数以buf作为输入参数进行输出。

在gui_log_port.h文件中还对GUI_Printf函数进行了封装，得到GUI_INFO、GUI_ERROR、GUI_DEBUG、GUI_DEBUG_ARRAY和GUI_DEBUG_FUNC函数，这些函数预定义了一些输出信息，或可通过宏来设置是否进行输出，使用的时候比较方便，具体见 代码清单4_7_ 。

.. code-block:: c
    :caption: 代码清单 4_7 其它日志输出接口（gui_log_port.h文件）
    :linenos:
    :name: 代码清单4_7

    /* INFO和ERROR在任何情况下都会输出 */
    /* 信息输出 */
    #define GUI_INFO(fmt,arg...)           GUI_Printf("<<-GUI-INFO->> "fmt"\n",##arg)
    /* 错误输出 */
    #define GUI_ERROR(fmt,arg...)          GUI_Printf("<<-GUI-ERROR->> "fmt"\n",##arg)
    /* 调试输出，受GUI_DEBUG_EN控制 */
    #define GUI_DEBUG(fmt,arg...)          do{\
                                            if(GUI_DEBUG_EN)\
        GUI_Printf("<<-GUI-DEBUG->> [%s] [%d]"fmt"\n",__FILE__,__LINE__, ##arg);\
                                            }while(0)
    /* 数组输出，受GUI_DEBUG_ARRAY_EN控制 */
    #define GUI_DEBUG_ARRAY(array, num)    do{\
                                            int32_t i;\
                                            uint8_t* a = array;\
                                            if(GUI_DEBUG_ARRAY_EN)\
                                            {\
                                                GUI_Printf("<<-GUI-DEBUG-ARRAY->>\n");\
                                                for (i = 0; i < (num); i++)\
                                                {\
                                                    GUI_Printf("%02x   ", (a)[i]);\
                                                    if ((i + 1 ) %10 == 0)\
                                                    {\
                                                        GUI_Printf("\n");\
                                                    }\
                                                }\
                                                GUI_Printf("\n");\
                                            }\
                                            }while(0)
    
    /* 进入函数输出，受GUI_DEBUG_FUNC_EN控制
    一般在需要调试的函数开头进行调用，
    调试时可通过输出信息了解运行了什么函数或运行顺序
    */
    #define GUI_DEBUG_FUNC()               do{\
                                            if(GUI_DEBUG_FUNC_EN)\
                    GUI_Printf("<<-GUI-FUNC->> Func:%s@Line:%d\n",__func__,__LINE__);\
                                            }while(0)

其中GUI_INFO和GUI_ERROR函数默认都会进行输出，主要用于输出提示信息和错误信息，而GUI_DEBUG、GUI_DEBUG_ARRAY和GUI_DEBUG_FUNC函数一般用于调试输出，可以在gui_drv_cfg.h文件设置它们是否进行输出，具体见 代码清单4_8_ 。

.. code-block:: c
    :caption: 代码清单 4_8 是否开启调试、数组及进行函数的输出功能（gui_drv_cfg.h文件）
    :linenos:
    :name: 代码清单4_8

    /* 是否开启调试输出、数组输出、进入函数的输出功能 */
    #define GUI_DEBUG_EN                1
    #define GUI_DEBUG_ARRAY_EN          0
    #define GUI_DEBUG_FUNC_EN            0

配置显示驱动接口
~~~~~~~~~~~~~~~~

emXGUI的显示驱动接口主要包含绘图引擎、绘图表面以及底层液晶驱动的内容，移植时主要是针对gui_lcd_port.c文件进行修改。

先来了解显示驱动接口GUI_DisplayInit的初始化流程，它会在GUI_Startup函数中被调用，具体见 代码清单4_9_ 。

.. code-block:: c
    :caption: 代码清单 4_9 GUI_DisplayInit接口（gui_lcd_port.c文件）
    :linenos:
    :name: 代码清单4_9

    /***********************第1部分*************************/
    /**
    * @brief  初始化显示设备接口，并创建SURFACE表面
    * @param  无
    * @retval 显示设备Surface对象指针，创建得到的绘图表面
    */
    SURFACE* GUI_DisplayInit(void)
    {
        /* 绘图表面 */
        SURFACE *pSurf;
        /***********************第2部分*************************/
    #if (LCD_FORMAT == COLOR_FORMAT_RGB565)
    
        //创建绘图表面
        /* 动态申请的方式  */
    // pSurf = GUI_CreateSurface(SURF_RGB565,
    //                              LCD_XSIZE,LCD_YSIZE,
    //                              LCD_XSIZE*2,
    //                              NULL);
    
        /* 直接指定地址的方式， 显存地址，*/
        pSurf = GUI_CreateSurface(SURF_RGB565,
                                LCD_XSIZE,LCD_YSIZE,
                                LCD_XSIZE*2,
                                (void*)LCD_FRAME_BUFFER);
    
    #endif
        
    #if (LCD_FORMAT == COLOR_FORMAT_XRGB8888)
        //动态申请的方式，初始化LCD Surface结构数据(XRGB8888格式)
        //lcd_buffer =(u8*)GUI_GRAM_Alloc(LCD_XSIZE,LCD_YSIZE*4);
    
        /* 直接指定地址的方式， 显存地址，*/
        /* 动态申请的方式  */
    // pSurf = GUI_CreateSurface(SURF_XRGB8888,
    //                              LCD_XSIZE,LCD_YSIZE,
    //                              LCD_XSIZE*4,
    //                              NULL);
    
        pSurf = GUI_CreateSurface(SURF_XRGB8888,
                                LCD_XSIZE,LCD_YSIZE,
                                LCD_XSIZE*4,
                                (void*)LCD_FRAME_BUFFER);
    
    #endif
        /***********************第3部分*************************/
        if (pSurf == NULL) {
            GUI_Printf("#Error: GUI_CreateSurface Failed.\r\n");
        }
    
        //LCD硬件初始化
        LCD_HardInit((u32)pSurf->Bits);
        /***********************第4部分*************************/
        //清屏
        pSurf->GL->FillArea(pSurf,0,0,LCD_XSIZE,LCD_YSIZE,pSurf->CC->MapRGB(0,0,0));
        //打开背光
        LCD_BkLight(TRUE);
        /***********************第5部分*************************/
        return pSurf;
    }

该代码的说明如下：

-  第1部分。GUI_DisplayInit作为显示设备的驱动接口，它初始化了液晶屏硬件并创建emXGUI绘图表面Surface，执行完毕把绘图表面的指针返回，然后由库函数GUI_SetScreenSurface设置为屏幕的绘图表面，emXGUI的所有绘制操作将在该表面展开。

-  第2部分。根据宏LCD_FORMAT的定义调用GUI_CreateSurface函数，创建格式为RGB565和XRGB8888的绘图表面，调用时输入的参数为绘图表面格式、液晶屏的宽高、一行像素数据
   占多少字节以及显存空间的首地址，示例中输入使用的这些宏都定义在bsp_lcd.h和gui_drv_cfg.h头文件中，具体见 代码清单4_10_ 。

.. code-block:: c
    :caption: 代码清单 4_10 液晶屏相关的宏定义（bsp_lcd.h和gui_drv_cfg.h文件）
    :linenos:
    :name: 代码清单4_10

    /** bsp_lcd.h文件 **/
    /* LCD Size (Width and Height) */
    #define  LCD_PIXEL_WIDTH          ((uint16_t)800)
    #define  LCD_PIXEL_HEIGHT         ((uint16_t)480)

    #define  LCD_BUFFER         ((uint32_t)0xD0000000)

    /** gui_drv_cfg.h文件 **/
    //野火5.0 / 7.0TFT,800x480
    /* 显存基地址 */
    #define  LCD_FRAME_BUFFER   LCD_BUFFER

    /* 使用的显示格式 */
    #define LCD_FORMAT    COLOR_FORMAT_RGB565
    //#define LCD_FORMAT    COLOR_FORMAT_XRGB8888

    /* 液晶宽高 */
    #define LCD_XSIZE     LCD_PIXEL_WIDTH
    #define LCD_YSIZE     LCD_PIXEL_HEIGHT

特别地，若调用GUI_CreateSurface时显存地址指定为NULL时，函数执行时会从GRAM中分配显存空间（代码清单4_9_ 第2部分中注释掉的调用方式即从GRAM中分配显存）。

-  代码清单4_9_ 的第3部分。调用液晶初始化接口LCD_HardInit初始化液晶屏硬件，它接受显存地址作为输入参数，本示例中以前面创建的绘图表面pSurf->Bits作为显存。移植时用户需要根据液晶屏配置LCD_HardInit接口。

-  代码清单4_9_ 的第4部分。调用绘图表面的矩形绘图函数pSurf->GL->FillArea把整个屏幕清除为黑色，并且调用液晶背光控制接口LCD_BkLight使能屏幕的背光。移植时用户需要配置LCD_BkLight接口。

-  代码清单4_9_ 的第5部分，返回执行GUI_CreateSurface函数得到的pSurf，GUI_Startup函数中会利用它设置屏幕的绘图表面。

配置绘图表面（Surface）
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

代码清单4_9_ 中调用GUI_CreateSurface函数创建了绘图表面，所谓绘图表面是对绘图设备的描述，其内容记录了绘图设备的颜色格式，物理像素大小，显示缓冲区，以及绘图引擎，GUI所有的绘图目标，最终都是在绘图表面上进行。每个绘图表面都是一个独立的绘图设备，可以由用户自由创建，它的类型定义具体见 代码清单4_11_ 。

.. code-block:: c
    :caption: 代码清单 4_11 绘图表面的类型定义（emXGUI_Arch.h文件）
    :linenos:
    :name: 代码清单4_11

    typedef struct  tagSURFACE    SURFACE;
    
    /**
    * @brief  绘图表面，包含格式、宽高、显存地址等内容
    */
    struct tagSURFACE {
        U32      Format;            //绘图表面的格式
        U32      Width;             //绘图表面的宽
        U32      Height;            //绘图表面的高
        U32      WidthBytes;        //一行像素点占多少字节
        LPVOID   Bits;              //所在的显存地址
        const COLOR_CONVERT *CC;    //颜色转换函数指针
        const GL_OP *GL;            //绘图引擎指针
        const void  *pdata;         //附加数据
        u32 Flags;                  //标志
    };

该结构体的类型说明如下：

-  Format：绘图表面的像素格式，如RGB565/XRGB888/ARGB8888等，通常把它配置为与底层液晶驱动一致的格式，具体枚举值见 代码清单4_12_ 。

.. code-block:: c
    :caption: 代码清单 4_12 绘图表面的像素格式（emXGUI.h文件）
    :linenos:
    :name: 代码清单4_12
    
    typedef enum {
        SURF_SCREEN      = 0,
        SURF_RGB332      = COLOR_FORMAT_RGB332,
        SURF_RGB565      = COLOR_FORMAT_RGB565,
        SURF_ARGB4444    = COLOR_FORMAT_ARGB4444,
        SURF_XRGB8888    = COLOR_FORMAT_XRGB8888,
        SURF_ARGB8888    = COLOR_FORMAT_ARGB8888,

    } SURF_FORMAT;

-  Width和Height：分别表示绘图表面的宽和高。

-  WidthBytes：表示绘图表面一行像素占多少个字节，计算方式为“Width*每个像素点的字节数”。

-  Bits：绘图表面对应的显存地址，如STM32F429中通常会把它赋值为液晶层的显存地址，绘制操作就是在显存中写入像素数据。

-  CC和GL：分别是颜色转换和绘图引擎（GAL）的函数指针。

-  pdata：附加数据。

-  Flags：包含指示绘图表面特性的某些标志，如可使用宏SURF_FLAG_GRAM表示绘图表面的显存空间是否从GRAM中分配得来的。

在emXGUI中提供了SurfaceInit_RGB332/ RGB565/ARGB4444/ XRGB8888/ ARGB8888等库函数用于初始化绘图表面，函数的声明形如 代码清单4_13_。

.. code-block:: c
    :caption: 代码清单 4_13 初始化绘图表面的函数声明（emXGUI_Arch.h文件）
    :linenos:
    :name: 代码清单4_13

    /**
    * @brief  初始化绘图表面
    * @param  pSurf[out] 根据其它参数对pSurf进行初始化
    * @param  gdraw[in] 绘图引擎对象，如GL_MEM_8PP、GL_MEM_16PP、GL_MEM_32PP
    * @param  w h 绘图表面的宽和高
    * @param  line_bytes 一行像素占多少个字节
    * @param  bits[in] 显存指针
    */
    void  SurfaceInit_RGB332(SURFACE *pSurf,
                                const GL_OP *gdraw,
                                int w,int h,
                                int line_bytes,
                                void *bits);

这些函数会根据输入参数配置绘图表面指针pSurf，为方便应用，在gui_lcd_port.c文件中把这些函数封装成了GUI_CreateSurface接口，具体见 代码清单4_14_。

.. code-block:: c
    :caption: 代码清单 4_14 GUI_CreateSurface接口（gui_lcd_port.c文件）
    :linenos:
    :name: 代码清单4_14

    /**
    * @brief  创建SURFACE表面
    * @param  Format 绘图表面格式
    * @param  Width Height 绘图表面宽高
    * @param  LineBytes 绘图表面每行像素占多少字节
    * @param  bits 显存地址，若为NULL，则会使用GUI_GMEM_Alloc申请动态显存
    * @retval 显示设备Surface对象指针，创建得到的绘图表面
    */
    SURFACE*  GUI_CreateSurface(SURF_FORMAT Format,
                                int Width,int Height,
                                int LineBytes,
                                void *bits)
    {
        SURFACE *pSurf;
        switch (Format) {
        case  SURF_RGB332:
            pSurf = (SURFACE*)GUI_MEM_Alloc(sizeof(SURFACE));
            pSurf->Flags =0;
            if (LineBytes <= 0) {
                LineBytes = Width;
            }
            if (bits==NULL) {
                bits = (void*)GUI_GRAM_Alloc(Height*LineBytes);
                pSurf->Flags |= SURF_FLAG_GRAM;
            }
            SurfaceInit_RGB332(pSurf,&GL_MEM_8PP,Width,Height,LineBytes,bits);
            break;
        ////
    
        case  SURF_RGB565:
            pSurf = (SURFACE*)GUI_MEM_Alloc(sizeof(SURFACE));
            pSurf->Flags =0;
            if (LineBytes <= 0) {
                LineBytes = Width*2;
            }
            if (bits==NULL) {
                bits = (void*)GUI_GRAM_Alloc(Height*LineBytes);
                pSurf->Flags |= SURF_FLAG_GRAM;
            }
            SurfaceInit_RGB565(pSurf,&GL_MEM_16PP,Width,Height,LineBytes,bits);
            break;
            ////
            /*...后面省略其它像素格式的配置内容...*/
        }
    }

代码中根据输入的像素格式调用不同的绘图表面初始化函数，利用GUI_MEM_Alloc接口从MEM分配绘图表面变量的空间，并且当显存地址输入为NULL的时候，通过GUI_GRAM_Alloc从GRAM分配显存空间。

代码中加粗显示的GL_MEM_8PP和GL_MEM_16PP是下面要介绍的内存型绘图引擎。

emXGUI的绘图引擎（GAL）
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

emXGUI能适配不同的液晶屏，按照适配的驱动接口主要把液晶屏分为两类：

-  内存型液晶屏：类似STM32F429这类自带LTDC液晶控制器的MCU，只要初始化好LTDC控制器，GUI控制液晶屏绘制操作时直接往显存写入像素数据即可，非常简单、通用。

-  MPU型液晶屏：类似STM32F103/407这类不自带液晶控制器的MCU，控制液晶屏绘制操作往往需要与外部的液晶控制器通讯，如发送命令、数据等操作，控制起来不如内存型液晶屏简便。

针对不同类型的液晶屏，emXGUI在资料目录“emxgui\arch\GAL”中提供了不同的绘图引擎，具体见 图4_3_。

.. image:: /media/docx012.png
   :align: center
   :alt: 图 5‑3 emXGUI提供的不同类型绘图引擎示例
   :name: 图4_3

图 4_3 emXGUI提供的不同类型绘图引擎示例

所谓绘图引擎，就是提供给emXGUI控制液晶显示操作的接口，它包含一系列基础绘制函数，而对于像素格式宽度不同的绘制操作，底层是有差异的。示例代码中针对内存型绘图引擎提供了8/16/32位格式的接口，针对MPU型绘图引擎提供了最常用的16位格式接口。

绘图引擎涉及到的绘制操作具体见 代码清单4_15_。

.. code-block:: c
    :caption: 代码清单 4_15 绘图引擎结构体类型定义（emXGUI_Arch.h文件）
    :linenos:
    :name: 代码清单4_15

    /**
    * @brief  绘图对象，包含相应的绘图操作函数指针
    */
    typedef struct  tagGL_OP {
    
        FN_GL_SetPos    *SetPos;
        FN_GL_SetPixel    *SetPixel;
        FN_GL_GetPixel    *GetPixel;
        FN_GL_XorPixel    *XorPixel;
        FN_GL_HLine     *HLine;
        FN_GL_VLine     *VLine;
        FN_GL_Line      *Line;
        FN_GL_FillArea    *FillArea;
        FN_GL_CopyBits    *CopyBits;
    
        FN_GL_DrawBitmap_LUT1 *DrawBitmap_LUT1;
        FN_GL_DrawBitmap_LUT2 *DrawBitmap_LUT2;
        FN_GL_DrawBitmap_LUT4 *DrawBitmap_LUT4;
        FN_GL_DrawBitmap_LUT8 *DrawBitmap_LUT8;
    
        FN_GL_DrawBitmap_RGB  *DrawBitmap_RGB332;
        FN_GL_DrawBitmap_RGB  *DrawBitmap_RGB565;
        FN_GL_DrawBitmap_RGB  *DrawBitmap_XRGB1555;
        FN_GL_DrawBitmap_RGB  *DrawBitmap_ARGB1555;
        FN_GL_DrawBitmap_RGB  *DrawBitmap_ARGB4444;
        FN_GL_DrawBitmap_RGB  *DrawBitmap_RGB888;
        FN_GL_DrawBitmap_RGB  *DrawBitmap_XRGB8888;
        FN_GL_DrawBitmap_RGB  *DrawBitmap_ARGB8888;
    
        FN_GL_DrawBitmap_AL1  *DrawBitmap_AL1;
        FN_GL_DrawBitmap_AL2  *DrawBitmap_AL2;
        FN_GL_DrawBitmap_AL4  *DrawBitmap_AL4;
        FN_GL_DrawBitmap_AL8  *DrawBitmap_AL8;
    
        FN_GL_ScaleBitmap  *ScaleBitmap;
        FN_GL_RotateBitmap *RotateBitmap;
    
    } GL_OP;

这个结构体中的内容全是函数指针，包含如获取坐标、绘制像素点、获取像素点、像素点异或运算、绘制各种线段和矩形等操作。以16位内存型绘图引擎GL_MEM_16BPP.c为例，具体见 代码清单4_16_。

.. code-block:: c
    :caption: 代码清单4_16 16位内存型绘图引擎的部分代码（GL_MEM_16BPP.c文件）
    :linenos:
    :name: 代码清单4_16

    /* 像素点类型 */
    #define COLOR16 U16
    
    /**
    * @brief  根据坐标计算像素点的地址
    * @param  pSurf 绘图表面
    * @param  x y 坐标
    * @retval 坐标在绘图表面对应的地址
    */
    #define __set_addr(pSurf,x,y)   (COLOR16*)((U8*)pSurf->Bits + (x*2) + ((y)*pSurf->WidthBytes))
    
    /**
    * @brief  绘制单个像素点
    * @param  pSurf 绘图表面
    * @param  x y 坐标
    * @param  要绘制的颜色
    * @retval 坐标在绘图表面对应的地址
    */
    void  GL16_set_pixel(const SURFACE *pSurf,int x,int y,COLORREF c)
    {
        COLOR16 *addr;
    
        addr = __set_addr(pSurf,x,y);
        *addr =c;
    }
    
    COLORREF  GL16_get_pixel(const SURFACE *pSurf,int x,int y)
    {
        COLOR16 *addr;

        addr = __set_addr(pSurf,x,y);
        return *addr;
    }

    void GL16_draw_hline(const SURFACE *pSurf,int x0,int y0,int x1,COLORREF c)
    {
        COLOR16 *addr;

        addr = __set_addr(pSurf,x0,y0);
        GUI_memset16(addr,c,x1-x0);
    }

    /* ...省略大部分内容... */
    /* 给绘图引擎结构体赋值为具体函数 */
    void GL_MEM_16BPP_Init(GL_OP *gd)
    {
        gd->SetPos       =GL16_set_addr;
        gd->SetPixel  =GL16_set_pixel;
        gd->GetPixel  =GL16_get_pixel;
        gd->XorPixel  =GL16_xor_pixel;
        gd->HLine     =GL16_draw_hline;
        gd->VLine   =GL16_draw_vline;
        gd->FillArea    =GL16_fill_rect;
        gd->CopyBits    =GL16_copy_bits;

        gd->DrawBitmap_LUT1 =GL16_draw_bitmap_LUT1;
        gd->DrawBitmap_LUT2 =GL16_draw_bitmap_LUT2;
        gd->DrawBitmap_LUT4 =GL16_draw_bitmap_LUT4;
        gd->DrawBitmap_LUT8 =GL16_draw_bitmap_LUT8;
        gd->DrawBitmap_RGB332 =GL16_draw_bitmap_RGB332;
        gd->DrawBitmap_RGB565 =GL16_draw_bitmap_RGB565;
        gd->DrawBitmap_XRGB1555 =GL16_draw_bitmap_XRGB1555;
        gd->DrawBitmap_ARGB1555 =GL16_draw_bitmap_ARGB1555;
        gd->DrawBitmap_ARGB4444 =GL16_draw_bitmap_ARGB4444;
        gd->DrawBitmap_RGB888 =GL16_draw_bitmap_RGB888;
        gd->DrawBitmap_XRGB8888 =GL16_draw_bitmap_XRGB8888;
        gd->DrawBitmap_ARGB8888 =GL16_draw_bitmap_ARGB8888;

        gd->DrawBitmap_AL1  =GL16_draw_bitmap_AL1;
        gd->DrawBitmap_AL2  =GL16_draw_bitmap_AL2;
        gd->DrawBitmap_AL4  =GL16_draw_bitmap_AL4;
        gd->DrawBitmap_AL8  =GL16_draw_bitmap_AL8;

        gd->ScaleBitmap     =GL16_scale_bitmap;
        gd->RotateBitmap        =GL16_rotate_bitmap;
    }

在这段代码中，先定义了一个__set_addr宏，根据输入的绘图表面、像素点xy坐标计算显存地址，其后的绘制像素点函数GL16_set_pixel、获取像素点函数GL16_get_pixel以及绘制水平线函数GL16_draw_hline则针对具体的地址和颜色赋予像素数据值。其余的绘制操作也类似，具
体可直接查看源码了解。本段代码的最后通过GL_MEM_16BPP_Init函数对输入的绘图引擎结构体gd赋值，赋值内容为以上具体的16位绘制操作函数。在GUI_Startup函数通过调用GUI_Arch_Init会完成这部分绘图引擎的初始化，具体见 代码清单4_17_ 。

.. code-block:: c
    :caption: 代码清单 4_17 GUI_Arch_Init函数的内容（GUI_Arch.c文件）
    :linenos:
    :name: 代码清单4_17

    GL_OP GL_MEM_8PP;
    GL_OP GL_MEM_16PP;
    GL_OP GL_MEM_32PP;
    /**
    * @brief  GUI架构适配层初始化.
    */
    BOOL  GUI_Arch_Init(void)
    {
        _RectLL_Init();   //初始化GUI内核矩形链表，用于窗口叠加时的Z序管理
    
        GL_MEM_8BPP_Init(&GL_MEM_8PP);   //初始化8位内存型绘图对象.
        GL_MEM_16BPP_Init(&GL_MEM_16PP); //初始化16位内存型绘图对象.
        GL_MEM_32BPP_Init(&GL_MEM_32PP); //初始化32位内存型绘图对象.
    
        return TRUE;
    }

若不是有特殊的应用需求，在移植时通常不需要修改绘图引擎相关的内容，直接根据液晶屏的类型把相应的绘图引擎文件添加到工程即可。

如果有硬件加速器，则可根据具体的平台进行定制，例如STM32F429具有DMA2D外设，可以加速直线、矩形以及部分颜色转换的操作，那么可通过修改绘图引擎接口提升emXGUI的绘制性能。

配置液晶驱动
^^^^^^^^^^^^^^^^^^

由于绘图引擎已包含丰富的绘制接口，所以液晶驱动主要是提供液晶初始化和背光控制的内容，具体见 代码清单4_18_。

.. code-block:: c
    :caption: 代码清单4_18 液晶驱动接口（gui_lcd_port.c文件）
    :linenos:
    :name: 代码清单4_18

    /**
    * @brief  液晶屏初始化接口
    * @param  fb_addr 要使用的显存地址
    */
    void LCD_HardInit(u32 fb_addr)
    {
        /* 初始化液晶屏 */
    #if (LCD_FORMAT == COLOR_FORMAT_RGB565)
        LCD_Init(fb_addr, 33, LTDC_Pixelformat_RGB565);
    #endif
    
    #if (LCD_FORMAT == COLOR_FORMAT_XRGB8888)
        LCD_Init(fb_addr, 21, LTDC_Pixelformat_ARGB8888);
    #endif
    
    }
    
    /**
    * @brief  液晶背光控制接口
    * @param  on 1为亮，其余值为灭
    */
    void LCD_BkLight(int on)
    {
        LCD_BackLed_Control(on);
    }

代码中的液晶初始化接口LCD_HardInit接收参数fb_addr作为显存地址，函数的内部根据gui_drv_cfg.h文件中的宏LCD_FORMAT使用不同的参数初始化STM32的LTDC外设，分为RGB565和XRGB8888格式，不同格式的主要区别是LTDC层的像素格式和像素时钟频率的差异，
初始化时调用了底层驱动文件bsp_lcd.c中的LCD_Init函数，该函数的函数声明见 代码清单4_19_，具体源码请直接在工程中查看。

.. code-block:: c
    :caption: 代码清单4_19 LCD_Init函数（bsp_lcd.c文件）
    :linenos:
    :name: 代码清单4_19

    /**
    * @brief LCD初始化
    * @param fb_addr 显存首地址
    * @param  lcd_clk_mhz 像素时钟频率，
                RGB565格式推荐为30~33，
                XRGB8888格式推荐为20~22
                极限范围为15~52，其余值会超出LTDC时钟分频配置范围
    * @param pixel_format 像素格式，如LTDC_Pixelformat_ARGB8888 、
                            LTDC_Pixelformat_RGB565等
    * @retval  None
    */
    void LCD_Init(uint32_t fb_addr,
                int lcd_clk_mhz,
                uint32_t pixel_format );

LCD_Init函数主要是根据具体的液晶屏时序配置不同的LTDC参数，关于LTDC的驱动原理请参考野火的《零死角玩转STM32》教程，STM32F429的LTDC支持使用两个液晶层进行混合效果显示，不过使用多层时数据量太大，驱动液晶屏时像素时钟无法调高，导致存在闪屏现象（特别是ARGB8888双层显
示时），而且emXGUI并不需要使用到双层混合效果的功能，所以本示例都只使用了LTDC的单层显示。

配置默认字体
~~~~~~~~~~~~

emXGUI推荐使用XFT作为默认字体显示字符，可通过gui_font_port.c文件进行配置。在emXGUI的目录“emxgui\resource\xft_font”提供了部分示例字体资源文件，具体见 图4_4_。

.. image:: /media/docx013.png
   :align: center
   :alt: 图 4_4 XFT字体示例数据
   :name: 图4_4

图 4_4 XFT字体示例数据

示例文件中的命名格式为“编码库_字体宽度_平滑度”，如 图4_4_ 包含ASCII和GB2312两种字体编码；字体宽度值表示字符横向占据的像素个数；平滑度越高，字体边沿的锯齿越不明显，显示的字符效果越好。

这些字体资源文件是使用配套的字体生成器得到的（目前还没有发布），以ASCII_20_4BPP.c文件文件为例，它的内容具体见 代码清单4_20_。

.. code-block:: c
    :caption: 代码清单4_20 ASCII_20_4BPP字体资源文件的内容（ASCII_20_4BPP.c文件）
    :linenos:
    :name: 代码清单4_20

    const char ASCII_20_4BPP[]= {
        88,70,84,0,88,71,85,73,32,70,111,110,116,0,0,0,
        0,0,0,0,16,83,0,0,16,115,0,0,64,0,0,0,
        212,0,0,0,10,0,100,0,20,0,20,0,4,0,0,0,
        /*..省略大部分内容..*/
    }

可以看到，字体资源就是一个超大数组，使用时把需要的字体资源的添加到工程，然后调用库函数XFT_CreateFont创建字体句柄，即可使用该字体进行显示，下面以创建默认字体的GUI_Default_FontInit函数为例进行说明，具体见 代码清单4_21_。

.. code-block:: c
    :caption: 代码清单4_21创建默认字体（gui_font_port.c文件）
    :linenos:
    :name: 代码清单4_21

    extern const char ASCII_20_4BPP[];
    /**
    * @brief  GUI默认字体初始化
    * @param  无
    * @retval 返回默认字体的句柄
    */
    HFONT GUI_Default_FontInit(void)
    {
        HFONT hFont=NULL;
        /*..此处省略从外部SPI-FLASH加载字体数据的方式..*/
        /* 使用内部FLASH中的数据（工程中的C语言数组）
        *  添加字体数据时，把数组文件添加到工程，在本文件头添加相应字体数组的声明，
        *  然后调用XFT_CreateFont函数创建字体即可
        */
        if (hFont==NULL) {
            /* 从本地加载(本地数组数据) */
    hFont =XFT_CreateFont(ASCII_20_4BPP);  /*ASCii字库,20x20,4BPP抗锯齿*/

            /* 中文字库存储占用空间非常大，不推荐放在内部FLASH */
    //hFont =XFT_CreateFont(GB2312_16_2BPP); /*GB2312字库,16x16,2BPP抗锯齿*/
    //hFont =XFT_CreateFont(GB2312_20_4BPP); /*GB2312字库,20x20,4BPP抗锯齿*/
        }
        return hFont;
    }

在这段代码的开头，声明了在ASCII_20_4BPP.c定义的外部变量ASCII_20_4BPP，然后把它作为输入参数调用库函数XFT_CreateFont，函数执行后返回字体句柄hFont，在GUI_Startup函数内再通过库函数GUI_SetDefFont以hFont作为输入参数设置为默认字体
。

注意ASCII编码不支持中文，而支持中文的任何一个GB2312编码字体资源文件都非常大，不建议直接以数组的方式添加到工程，这样会占用宝贵的MCU内部FLASH空间，在后续的教程中我们会讲解增加外部资源接口，把字体资源文件放置在外部SPI-FLASH，节省MCU的内部FLASH空间。

扩展触摸屏支持
~~~~~~~~~~~~~~

emXGUI支持使用鼠标、键盘及触摸屏作为输入设备，本示例以触摸屏进行讲解。

输入设备接口
^^^^^^^^^^^^

在gui_drv_cfg.h文件包含有输入设备的配置宏，具体见 代码清单4_22_。

.. code-block:: c
    :caption: 代码清单4_22 输入设备配置（gui_drv_cfg.h文件）
    :linenos:
    :name: 代码清单4_22

    /* 是否使用输入设备 */
    #define  GUI_INPUT_DEV_EN               1
    
    /* 是否使能键盘、鼠标、触摸屏 */
    #define GUI_TOUCHSCREEN_EN              1
    #define GUI_KEYBOARD_EN                 0
    #define GUI_MOUSE_EN                    0
    
    /* 是否需要触摸校准-电阻屏才需要 */
    #define GUI_TOUCHSCREEN_CALIBRATE       0

以上的宏会影响gui_input_port.c文件中的条件编译，使用电容触摸屏时，需要使能宏GUI_INPUT_DEV_EN和GUI_TOUCHSCREEN_EN，gui_input_port.c文件的内容具体见 代码清单4_23_。

.. code-block:: c
    :caption: 代码清单4_23 输入设备初始化与处理接口（gui_input_port.c文件）
    :linenos:
    :name: 代码清单4_23

    /**
    * @brief  GUI输入设备的初始化
    * @param  无
    * @retval 是否初始化正常
    */
    BOOL GUI_InputInit(void)
    {
        BOOL state = FALSE;
    #if(GUI_KEYBOARD_EN)
        {
            state = KeyBoardDev_Init();
        }
    #endif

    #if(GUI_TOUCHSCREEN_EN)
        {
            state = TouchDev_Init();
            if (state) { /*触摸屏设备初始化*/
    #if(GUI_TOUCHSCREEN_CALIBRATE)
                TS_CFG_DATA ts_cfg;
                if (TouchDev_LoadCfg(&ts_cfg)) { /*加载校正数据(电阻屏需要)*/
            TouchPanel_TranslateInit(&ts_cfg); /*初始化坐标转换函数(电阻屏需要)*/
                }
    #endif
            }

        }
    #endif

    #if(GUI_MOUSE_EN)
        {
            state = MouseDev_Init();
        }
    #endif
        return state;
    }

    /*=========================================================

    /**
    * @brief  GUI输入设备的定时处理函数
    * @note   该函数需要被定时执行，
    *         如使用独立的线程调用 或 在桌面的定时器消息中调用
    *
    * @param  无
    * @retval 无
    */
    void GUI_InputHandler(void)
    {

    #if(GUI_KEYBOARD_EN)
        {
            if (KeyBoardDev_IsActive())
            {
                KeyBoardDev_Handler();
            }
        }
    #endif

    #if(GUI_TOUCHSCREEN_EN)
        {
            GUI_TouchHandler(); //调用触摸屏处理函数
        }
    #endif

    #if(GUI_MOUSE_EN)
        {
            if (MouseDev_IsActive())
            {
                MouseDev_Handler();
            }
        }
    #endif
    }

本文件是输入设备的统一接口，只是简单地调用了鼠标、键盘及触摸屏相应的初始化和处理函数，需要针对具体的设备定制驱动接口。

代码中的GUI_InputInit接口用于初始化输入设备，初始化触摸设备时调用了TouchDev_Init接口。

GUI_InputHandler接口用于处理输入设备传回的信息，需要定时调用，可以创建一个独立的操作系统任务调用该接口，也可以在emXGUI桌面的回调函数中通过定时器定时处理。其中触摸设备的信息处理通过调用GUI_TouchHandler接口实现。
见 代码清单4_24_ 

.. code-block:: c
    :caption: 代码清单4_24 示例代码中在桌面回调函数定时处理输入设备信息（gui_desktop.c文件）
    :linenos:
    :name: 代码清单4_24

    /**
    * @brief  桌面回调函数
    * @param  hwnd 当前处理该消息的窗口对象句柄
    * @param  msg 消息类型值，用以标识和区分当前产生的消息
    * @param  wParam 消息参数值，根据msg消息代码值不同
    * @param  lParam 消息参数值，根据msg消息代码值不同
    * @retval 返回给SendMessage的值
    */
    static   LRESULT    desktop_proc(HWND hwnd,
                                    UINT msg,
                                    WPARAM wParam,
                                    LPARAM lParam)
    {
        switch (msg) {
        /* 桌面创建时,会产生该消息,可以在这里做一些初始化工作. */
        case  WM_CREATE:
            ////创建1个20ms定时器，处理循环事件.
            SetTimer(hwnd,1,20,TMR_START,NULL);
            /*..省略部分内容..*/
            break;

        /* 定时处理输入设备的信息 */
        case  WM_TIMER: {
            u16 id;
            id =LOWORD(wParam);
            if (id==1)
                GUI_InputHandler(); //处理输入设备
        }
        break;
        /*..省略部分内容..*/

        /* 用户不关心的信息，由系统处理 */
        default:
            return  DefDesktopProc(hwnd,msg,wParam,lParam);
        }
        return WM_NULL;
    }

这个回调函数与输入设备相关的主要是WM_CREATE和WM_TIMER处理分支，WM_CREATE是桌面窗口创建时会执行的分支，此处创建了一个20ms的定时器，每20ms时间到后会进入WM_TIMER分支，在该分支下我们直接调用GUI_InputHandler处理输入设备的信息。实际应用中可根据需要
调整定时间隔。

触摸设备接口
^^^^^^^^^^^^^^^^^^^^^^^^

以上触摸设备控制相关的接口位于gui_touch_port.c文件，具体见 代码清单4_25_ 。

.. code-block:: c
    :caption: 代码清单4_25 触摸设备的控制接口（gui_touch_port.c文件）
    :linenos:
    :name: 代码清单4_25

    /**
    * @brief  触摸初始化接口,会被gui_input_port.c文件的GUI_InputInit函数调用
    * @note  需要在本函数初始化触摸屏相关硬件
    * @retval 是否初始化正常
    */
    BOOL TouchDev_Init(void)
    {
        /* 初始化配套的5/7寸屏 */
        if (GTP_Init_Panel() == 0)
            return TRUE;
        else
            return FALSE;
    }
    
    /**
    * @brief  获取触摸状态及坐标，不需要用户修改
    * @note  本函数依赖GTP_Execu接口，该接口需要返回触摸坐标和是否被按下的状态，
    *        本例子在bsp_touch_gt9xx.c文件实现
    * @param  pt[out] 存储获取到的x y坐标
    * @retval 触摸状态
    *    @arg  TS_ACT_DOWN  触摸按下
    *    @arg  TS_ACT_UP    触摸释放
    *    @arg  TS_ACT_NONE  无触摸动作
    */
    BOOL TouchDev_GetPoint(POINT *pt)
    {
        static int ts_state=TS_ACT_NONE;
    
        /* 通过GTP_Execu获取触摸坐标和状态 */
        if (GTP_Execu(&pt->x,&pt->y) > 0)
            ts_state =TS_ACT_DOWN;
        else {
            if (ts_state==TS_ACT_DOWN)
                ts_state =TS_ACT_UP;
            else
                ts_state =TS_ACT_NONE;
        }
        return ts_state;
    }
    
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

这部分代码说明如下：

-  TouchDev_Init函数，其功能为初始化触摸设备，它通过调用bsp_touch_gt9xx.c文件提供的触摸屏初始化函数GTP_Init_Panel实现。

-  TouchDev_GetPoint函数，它的功能为读取触摸坐标，并返回触摸屏的状态（按下、释放、无操作），它通过调用bsp_touch_gt9xx.c文件中的GTP_Execu函数初始，GTP_Execu函数根
   据原驱动中的Goodix_TS_Work_Func函数修改而来，只读取一个触摸点，并且按
   照emXGUI接口的要求返回状态，关于触摸屏的控制原理请参考《零死角玩转STM32》教程。

-  GUI_TouchHandler函数，它会被代码清单4_23的GUI_InputHandler函数调用，定时处理触摸屏的信息。该函数调用前面的TouchDev_GetPoint获取触摸状态和坐标，若是触摸按下
   状态，那么调用emXGUI库函数MouseInput传入最新的触摸坐标，并且使用参数MK
   _LBUTTON表示点击鼠标的左键；若是触摸释放状态，则调用库函数GetCursorPos获取当前鼠标的坐标，然后再调用MouseInput传入当前鼠标的坐标，并使用输入参数“0”表示鼠标按键的释放。

配置触摸驱动时需要注意，原bsp_touch_gt9xx.c文件中使用了中断读取触摸坐标，而本示例中emXGUI定时通过定时调用GUI_TouchHandler函数处理触摸信息，所以触摸驱动中需要关闭触摸中断。

扩展外部资源设备
~~~~~~~~~~~~~~~~~~~~~~~~

图形界面应用常常需要字体、图片等非常大的数据资源，而MCU宝贵的内部FLASH空间通常用于存储程序，所以推荐扩展外部资源设备的接口为emXGUI提供数据内容，常用的外部资源设备有SPI-FLASH和SD卡。

外部资源设备接口
^^^^^^^^^^^^^^^^^^^^^

本示例以SPI-FLASH作为外部资源设备进行讲解，其接口具体见 代码清单4_26_。

.. code-block:: c
    :caption: 代码清单4_26资源设备访问接口（gui_resource_port.c文件）
    :linenos:
    :name: 代码清单4_26

    /*访问资源设备的互斥信号量*/
    static GUI_MUTEX *mutex_lock=NULL;

    /**
    * @brief  初始化资源设备（外部FLASH）
    * @param  无
    * @retval 是否初始化正常
    */
    BOOL RES_DevInit(void)
    {
        mutex_lock=GUI_MutexCreate();

        if (SPI_FLASH_Init() == 0)
            return TRUE;
        else
            return FALSE;
    }

    /**
    * @brief  向设备写入内容
    * @param  buf 要写入的内容
    * @param  addr 写入的目标地址
    * @param  size 写入的数据量（size不应超过BLOCK大小）
    * @retval 是否写入正常
    */
    BOOL RES_DevWrite(u8 *buf,u32 addr,u32 size)
    {
        GUI_MutexLock(mutex_lock,5000);
        SPI_FLASH_SectorErase(addr&0xFFFFF000);
        SPI_FLASH_BufferWrite(buf,addr,size);
        GUI_MutexUnlock(mutex_lock);
        return TRUE;
    }
    
    /**
    * @brief  从设备中读取内容
    * @param  buf 存储读取到的内容
    * @param  addr 读取的目标地址
    * @param  size 读取的数据量
    * @retval 是否读取正常
    */
    BOOL RES_DevRead(u8 *buf,u32 addr,u32 size)
    {
        GUI_MutexLock(mutex_lock,5000);
    
        SPI_FLASH_BufferRead(buf,addr,size);
        GUI_MutexUnlock(mutex_lock);
        return TRUE;
    }
    
    /**
    * @brief  擦除扇区
    * @param  addr 要擦除的扇区地址
    * @retval 扇区的字节数
    */
    int RES_DevEraseSector(u32 addr)
    {
        GUI_MutexLock(mutex_lock,5000);
        SPI_FLASH_SectorErase(addr&0xFFFFF000);
        GUI_MutexUnlock(mutex_lock);
        return SPI_FLASH_SectorSize;
    }

代码中包含了函数RES_DevInit、RES_DevWrite、RES_DevRead、RES_DevEraseSector，分别用于初始化资源设备、写入数据、读取数据以及擦除扇区，它们都是简单地调用了底层驱动文件bsp_spi_flash.c中相关的函数，实现对外部SPI-FLASH的访问。

外部资源存储结构
^^^^^^^^^^^^^^^^^^^^^

为了提高访问速度，示例中的SPI-FLASH没有使用文件系统管理资源文件，它们都是直接以二进制数据的方式写入到FLASH中的，而只存储二进制数据由不便于管理，所以我们增加了资源目录以便对FLASH内的资源文件进行定位寻址，具体资源分配如 表格4_4_ 所示。

表格 4_4 资源的目录管理

.. _表格4_4:

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

也就是说，假如资源设备上存储了A/B/C文件，那么可以在资源基地址开头的目录中找到A/B/C文件的文件名、文件大小以及文件数据在资源设备的偏移地址，方便检索信息。目录中的每一项都是由 代码清单4_27_ 中的结构体CatalogTypeDef组成。

.. code-block:: c
    :caption: 代码清单4_27 目录项的结构体类型（gui_resource_port.h文件）
    :linenos:
    :name: 代码清单4_27

    /* 目录信息类型 */
    typedef struct {
        char  name[24];  /* 资源的名字 */
        u32   size;      /* 资源的大小 */
        u32   offset;    /* 资源相对于基地址的偏移 */
    } CatalogTypeDef;

以上信息是往SPI-FLASH中写入资源文件时记录到目录中的，目录中每一项大小为24+4+4=32字节，在查找资源文件时，我们每次从FLASH的目录中读取一项，把目标资源文件名与目录信息中的“name”进行比对，若一致的话，再查看相应的“offset”计算出资源所在的地址，具体的实现见 代码清单4_28_。

.. code-block:: c
    :caption: 代码清单4_28 获取资源信息_绝对地址（gui_drv_cfg.h和gui_resource_port.c文件）
    :linenos:
    :name: 代码清单4_28

    /***********************第1部分*************************/
    /*..gui_drv_cfg.h文件..*/
    /* 是否使用资源设备 */
    #define GUI_RES_DEV_EN            1
    /* 资源所在的基地址 */
    #define GUI_RES_BASE             4096
    /* 存储在FLASH中的资源目录大小 */
    #define GUI_CATALOG_SIZE         4096
    
    /***********************第2部分*************************/
    /*..gui_resource_portc文件..*/
    /**
    * @brief  从FLASH中的目录查找相应资源的信息
    * @param  res_base 目录在FLASH中的基地址
    * @param  res_name[in] 要查找的资源名字
    * @param  dir[out] 要查找的资源名字
    * @note   此处dir.offset会被赋值为资源的绝对地址！！
    * @retval -1表示找不到，其余值表示资源在FLASH中的基地址
    */
    s32 RES_GetInfo_AbsAddr(const char *res_name, CatalogTypeDef *dir)
    {
        int i,len;
    
        len =x_strlen(res_name);
        /***********************第3部分*************************/
        /* 根据名字遍历目录 */
        for (i=0; i<GUI_CATALOG_SIZE; i+=32) {
            RES_DevRead((u8*)dir,GUI_RES_BASE+i,32);
            if (x_strncasecmp(dir->name,res_name,len)==0) {
                /***********************第4部分*************************/
                /* dir.offset是相对基地址的偏移，此处返回绝对地址 */
                dir->offset += GUI_RES_BASE;
                return dir->offset ;
            }
        }
        return -1;
    }

这段代码说明如下：

-  第1部分。这是在gui_drv_cfg.h头文件定义的宏，宏GUI_RES_DEV_EN用于设置是否使用外部资源设备；宏GUI_RES_BASE设置资源所在的基地址，也就是目录在FLASH中的首地址，此处配置为4096，是
   由烧录资源数据的程序决定的；宏GUI_CATALOG_SIZE设置目录的大小
   ，它也是由烧录资源数据的程序决定的，此处的值为4096，即最多记录4096/32=128项资源文件。

-  第2部分。函数RES_GetInfo_AbsAddr，其功能是根据输入的资源名res_name，在FLASH中查找资源的大小、绝对地址信息，若返回
   值小于0，说明找不到资源，若大于0，则输入的dir指向的目录结构会包含该资源的信息。

-  第3部分。函数RES_GetInfo_AbsAddr内部通过for循环每次读取FLASH中目录的32字节，并把读取到的资源名字dir->name与输入的res_name进行对比。

-  第4部分。若资源名字与输入的res_name匹配，那么给读取到的dir->offset加上基地址GUI_RES_BASE并返回。函数执行结束时dir->offset包含的即是资源文件在FLASH中的绝对地址。

后面将会介绍利用RES_GetInfo_AbsAddr函数获取字体资源文件的地址，并加载外部字体的示例。

烧录数据到资源设备
^^^^^^^^^^^^^^^^^^^^^


我们提供了一个示例工程“刷外部FLASH程序（烧录emXGUI资源文件）”，它用于从SD卡拷贝数据到FLASH，并且拷贝时会生成 表格4_4_ 中的目录，使用该程序时，可配置res_mgr.h文件修改资源目录的首地址和目录的大小。

.. code-block:: c
    :caption: 代码清单4_29 烧录资源的配置（res_mgr.h文件）
    :linenos:
    :name: 代码清单4_29

    /* 资源在SD卡中的路径 */
    #define RESOURCE_DIR         "0:/srcdata"
    /* 资源烧录到的FLASH基地址（目录地址） */
    #define RESOURCE_BASE_ADDR    4096
    /* 存储在FLASH中的资源目录大小 */
    #define CATALOG_SIZE           4096

使用该工程时，需要准备一张SD卡，使用电脑在SD卡的根目录下建立一个文件夹“srcdata”，把需要拷贝的资源文件放置到该目录，这个“srcdata”就是资源文件的数据来源，即res_mgr.h文件中宏RESOURCE_DIR表示的路径。

而拷贝到FLASH的目录基地址和目录大小则由宏RESOURCE_BASE_ADDR和CATALOG_SIZE进行配置，以上代码配置均为4096，表示资源目录在FLASH的起始地址为4096，大小也为4096。前面 代码清单4_29_ 中的资源基地址和目录地址就是根据这个设置的。

下面以烧录中文字体为例，我们在SD卡的srcdata目录下存放GB2312_16_4BPP.xft、GB2312_20_4BPP.xft、GB2312_24_4BPP.xft字体文件，注意使用字体资源时不要使用“C”后缀的数组文件。

.. image:: /media/docx014.png
   :align: center
   :alt: 图 4_5 示例资源文件
   :name: 图4_5

图 4_5 示例资源文件

复制完毕后把SD卡插到开发板，然后下载“刷外部FLASH程序（烧录emXGUI资源文件）”程序运行，打开串口调试助手可看到开发板返回的信息，提示按按键“KEY1”开始烧录，并且包含具体文件的烧录信息。

.. image:: /media/docx015.png
   :align: center
   :alt: 图 4_6 示例资源文件
   :name: 图4_6

图 4_6 程序运行的输出信息

烧录完成时串口会输出校验正常的提示，此时SPI-FLASH中包含带目录的字体资源文件。

使用外部字体文件
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

扩展了外部资源设备接口并烧录了字体资源文件后，emXGUI即可利用这些字体显示字符。使用外部字体文件主要有两种方式：

-  初始化字体时把整个字体文件加载到RAM（内部SRAM、外部SDRAM等），显示字符时从RAM得到字体数据进行显示；

-  通过流设备加载字体，在显示字符时emXGUI根据需要从资源设备中加载。

简单来说，整体加载方式在初始化的时候就把整个字体文件从FLASH加载到RAM，然后显示的时候从RAM中读取具体的字符数据；而流设备加载的方式则是显示的时候才从FLASH中读取具体的字符数据。

由于资源设备如SPI-FLASH或SD卡的读取速度明显慢于RAM设备，所以使用流设备加载字体的方式显示的速度稍慢，但好处是节省了宝贵的RAM空间，应用时请根据需求进行取舍。

加载整个字体文件到RAM
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

加载整个字体文件到RAM的方式比较简单，相比前面小节中使用数组文件创建默认字体，只是增加了字体文件的读取过程，它们都采用库函数XFT_CreateFont创建字体句柄。

本示例在创建默认字体时包含有整体加载方式的演示，具体见 代码清单4_30_。

.. code-block:: c
    :caption: 代码清单4_30 整体加载字体文件到RAM（gui_font_port.c文件）
    :linenos:
    :name: 代码清单4_30

    /**
    * @brief  GUI默认字体初始化
    * @param  无
    * @retval 返回默认字体的句柄
    */
    HFONT GUI_Default_FontInit(void)
    {
        /* 整个字体文件加载至RAM */

        int font_base;

        /* 指向缓冲区的指针 */
        static u8 *pFontData_XFT=NULL;
        CatalogTypeDef dir;

        /* RES_GetInfo读取到的dir.offset是资源的绝对地址 */
        font_base =RES_GetInfo_AbsAddr("GB2312_24_4BPP.xft", &dir);

        if (font_base > 0) {
            pFontData_XFT =(u8*)GUI_VMEM_Alloc(dir.size);
            if (pFontData_XFT!=NULL) {
                RES_DevRead(pFontData_XFT, font_base, dir.size);

                hFont = XFT_CreateFont(pFontData_XFT);
            }
        }

        /*..省略部分内容..*/
        return hFont;
    }

这是初始化默认字体GUI_Default_FontInit函数中的流设备加载部分，它的执行过程如下：

(1) 调用外部资源接口RES_GetInfo_AbsAddr读取字体“GB2312_24_4BPP.xft”的目录信息，主要是为了得到该字体文件在FLASH的基地址font_base和整个字体文件的大小dir.size；

(2) 根据字体文件的大小，调用GUI_VMEM_Alloc从VMEM申请dir.size大小的空间，使用指针pFontData_XFT指向该空间；

(3) 调用外部资源接口RES_DevRead读取整个字体文件数据，读取数据的基地址为前面得到的字体基地址font_base，要读取的数据大小为dir.size表示整个字体文件，读取得的数据存储在申请得到的pFontData_XFT指向的空间。

(4) 调用库函数XFT_CreateFont创建字体，直接把字体文件在VMEM的基地址pFontData_XFT作为输入参数即可。

(5) 调用XFT_CreateFont创建得到的字体句柄hFont被返回，可在GUI_Startup函数中设置为默认字体。由于步骤（3）中读取整个字体文件到RAM的过程比较长，所以这种方式在初始化的时候需要等上一会儿，其后显示时直接访问RAM的数据，速度非常快。示例字体数据的大小超过2MB，所以用这种方式要注意RAM空间是否足够。

使用流设备方式加载字体
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

使用流设备方式加载字体需要使用到库函数XFT_CreateFontEx（Ex表示extern）实现，该函数接受两个输入参数，分别是读取外部设备数据的回调函数以及自定义的输入参数，具体见 代码清单4_31_。

.. code-block:: c
    :caption: 代码清单4_31 XFT_CreateFontEx和它使用的回调函数（gui_font_port.h文件）
    :linenos:
    :name: 代码清单4_31

    /**
    * @brief   XFT_CreateFontEx使用的回调函数指针定义
    * @param  buf[out] 存储读取到的数据缓冲区
    * @param  offset 要读取的位置
    * @param  size 要读取的数据大小
    * @param  lParam 调用函数时的自定义参数（用户参数）
    * @retval 读取到的数据大小
    */
    typedef int (FN_XFT_GetData)(void *buf,int offset,int size,LONG lParam);

    /**
    * @brief  XFT_CreateFontEx使用外部字体
    * @param  FN_XFT_GetData 加载数据的函数指针
    * @param  lParam 调用函数FN_XFT_GetData时传入自定义参数（用户参数）
    * @retval 创建得到的字体句柄
    */
    HFONT XFT_CreateFontEx(FN_XFT_GetData *pfnGetData,LONG lParam);

通过XFT_CreateFontEx创建字体后，在显示字符时它会调用创建字体句柄时XFT_CreateFontEx输入的FN_XFT_GetData型函数指针，并向该函数传入buf、offset、size以及lParam参数，FN_XFT_GetData型函数指针根据输入参数从外部FLASH中读取数
据存储至buf，然后字符显示函数根据读取得的buf数据处理显示。

本示例在创建默认字体时包含有流设备加载方式的演示，具体见 代码清单4_32_。

.. code-block:: c
    :caption: 代码清单4_32 使用流设备加载默认字体（gui_font_port.c文件）
    :linenos:
    :name: 代码清单4_32

    /***********************第1部分*************************/
    /**
    * @brief  从流媒体加载内容的回调函数
    * @param  buf[out] 存储读取到的数据缓冲区
    * @param  offset 要读取的位置
    * @param  size 要读取的数据大小
    * @param  lParam 调用函数时的自定义参数（用户参数）
    * @retval 读取到的数据大小
    */
    static int font_read_data_exFlash(void *buf,int offset,int size,LONG lParam)
    {
        /* 本例子中offset是具体字符数据在字体文件中的偏移
        * lParam 是字体文件在FLASH中的基地址
        */
        offset += lParam;
    
        /* 读取具体的字模数据内容 */
        RES_DevRead(buf,offset,size);
        return size;
    }
    /***********************第2部分*************************/
    /**
    * @brief  GUI默认字体初始化
    * @param  无
    * @retval 返回默认字体的句柄
    */
    HFONT GUI_Default_FontInit(void)
    {
        HFONT hFont=NULL;
        /*..省略部分内容..*/
        /* 使用流设备加载字体，按需要读取 */
        if (hFont==NULL) {
            int font_base;
            CatalogTypeDef dir;
            /* 从外部资源查找字体相关的目录信息 */
            font_base=RES_GetInfo_AbsAddr("GB2312_24_4BPP.xft", &dir);
            if (font_base> 0) {
                hFont =XFT_CreateFontEx(font_read_data_exFlash, font_base);
            }
        }
        /*..省略部分内容..*/
        return hFont;
    }

-  第1部分。定义了font_read_data_exFlash 函数，它是FN_XFT_GetData型函数指针的实例，用于流式加载字体数据。其中参数offset是具体字符数据在字体文件中的偏移，而lPara
   m参数则是字体文件在FLASH设备中的基地址，所以在读取具体数据前，我们对offset加上l
   Param得到具体字符数据在FLASH中的绝对地址，最后通过外部资源设备接口RES_DevRead从绝对地址offset中读取size大小的字体数据，存储到buf指向的空间中。

-  第2部分。这是初始化默认字体GUI_Default_FontInit函数中的流设备加载部分，首先调用外部资源接口RES_GetInfo_AbsAddr读取字体“
   B2312_24_4BPP.xft”的目录信息，主要是为了得到该字体文件在FLASH的基地址font_base，然后调用库函数XFT_C
   reateFontEx创建字体，以第一部分的font_read_data_exFlash
   作为回调函数，并且以font_base作为自定义参数lParam，所以在font_read_data_exFlash函数中offset加上lParam就可以得到具体字符在FLASH中的“GB2312_24_4BPP.xft”字体数据了。

-  调用XFT_CreateFontEx创建得到的字体句柄hFont被返回，可在GUI_Startup函数中设置为默认字体。

下面以具体的实例进行说明字体数据的加载过程，假设我们创建了字体A和B，字体A在FLASH中的基地址是X，字体B在FLASH中的基地址为Y，它们使用同一个读取字体数据的函数指针R，现在分别使用字体A和字体B显示字符“野火”，那么它们的执行过程如下：

(1) 调用XFT_CreateFontEx创建字体A和B的句柄，给它们输入同样的FN_XFT_GetData函数指针R，而lParam参数不同，创建A时lParam输入的值为它在FLASH中的基地址X，创建B时lParam输入的值为它的基地址Y。

(2) 调用字符显示库函数TextOut，该函数的输入参数包含有显示的坐标和要显示的字符“野火”，若当前使用的字体为A，那么在该函数内部执行时会根据字体的大小、编码计算出“野”字在字体A文件中的偏移offset，以及单个字体数据的大小size，并且给出要接收该字体数据的缓冲区指针buf，创建字体A时
得到的lParam基地址X，把这四个参数传入到函数指针R，获取到“野”字的字体数据，然后进行显示处理；若当前使用的字体为B，执行过程类似，计算出相应的offset、size，并给出缓冲区指针buf，以及字体B的lParam基地址Y，作为参数输入并调用函数指针R得到“野”字的字体数据然后处理；然后再使
用同样的方式显示“火”字。

默认字体配置
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

前面为了方便讲解，GUI_Default_FontInit函数被分成整体加载、流设备加载以及数组加载三部分分别讲解，下面把
该函数的完整版列出重新说明，具体见 代码清单4_33_ 。

.. code-block:: c
    :caption: 代码清单4_33 完整版的GUI_Default_FontInit函数（gui_font_port.c文件）
    :linenos:
    :name: 代码清单4_33

    /**
    * @brief  GUI默认字体初始化
    * @param  无
    * @retval 返回默认字体的句柄
    */
    HFONT GUI_Default_FontInit(void)
    {
        HFONT hFont=NULL;
    
    #if (GUI_FONT_LOAD_TO_RAM  )
        {
            /* 整个字体文件加载至RAM */
    
            /* 指向缓冲区的指针 */
            static u8 *pFontData_XFT=NULL;
            CatalogTypeDef dir;
    
            /* RES_GetInfo读取到的dir.offset是资源的绝对地址 */
            if (RES_GetInfo_AbsAddr(GUI_DEFAULT_EXTERN_FONT, &dir) > 0) {
                pFontData_XFT =(u8*)GUI_VMEM_Alloc(dir.size);
                if (pFontData_XFT!=NULL) {
                    RES_DevRead(pFontData_XFT, dir.offset, dir.size);
    
                    hFont = XFT_CreateFont(pFontData_XFT);
                }
            }
        }
    #elif (GUI_USE_EXTERN_FONT)
        {
            /* 使用流设备加载字体，按需要读取 */
            if (hFont==NULL) {
                int offset;
                CatalogTypeDef dir;
    
                offset =RES_GetInfo_AbsAddr(GUI_DEFAULT_EXTERN_FONT, &dir);
                if (offset > 0) {
                    hFont =XFT_CreateFontEx(font_read_data_exFlash,offset);
                }
            }
        }
    #endif
    
        /* 若前面的字体加载失败，使用内部FLASH中的数据（工程中的C语言数组）
        *  添加字体数据时，把数组文件添加到工程，在本文件头添加相应字体数组的声明，
        *  然后调用XFT_CreateFont函数创建字体即可
        */
        if (hFont==NULL) {
            /* 从本地加载(本地数组数据) */
    hFont =XFT_CreateFont(GUI_DEFAULT_FONT);  /*ASCii字库,20x20,4BPP抗锯齿*/
    
    /* 中文字库存储占用空间非常大，不推荐放在内部FLASH */
    //hFont =XFT_CreateFont(GB2312_16_2BPP); /*GB2312字库,16x16,2BPP抗锯齿*/
    //hFont =XFT_CreateFont(GB2312_20_4BPP); /*GB2312字库,20x20,4BPP抗锯齿*/
        }
        return hFont;
    }

相对前面的代码，完整版的主要是增加了条件编译以及使用宏来设置默认字体，这些宏可在gui_drv_cfg.h文件进行配置，具体见 代码清单4_34_。

.. code-block:: c
    :caption: 代码清单4_34 默认字体配置（gui_drv_cfg.h文件）
    :linenos:
    :name: 代码清单4_34
    
    /* 是否使用外部FLASH中的字体
    *  流设备和整体加载方式都要把这个宏设置为1
    */
    #define GUI_USE_EXTERN_FONT       1
    
    /*
    * 是否把整个外部字体数据加载至VMEM区域，初始化加载时需要较长时间，
    * 加载后可大幅提高字符显示的速度
    * 若设置为真，则使用整体加载方式，否则使用流设备方式
    */
    #define GUI_FONT_LOAD_TO_RAM     (0 && GUI_USE_EXTERN_FONT)
    
    /* 要使用的外部默认字体文件，USE_EXTERN_FONT为1时生效 */
    #define GUI_DEFAULT_EXTERN_FONT   "GB2312_24_4BPP.xft"
    
    /* 默认内部字体数组名，USE_EXTERN_FONT为0或 外部字体加载失败时会采用的字体 */
    #define GUI_DEFAULT_FONT          ASCII_20_4BPP

使用外部SPI-FLASH的字体数据文件时，需要把宏GUI_USE_EXTERN_FONT设置为真值，当宏GUI_FONT_LOAD_TO_RAM设置为真值时，则使用整体加载的方式，否则使用流设备加载方式。而外部字体数据文件的文件名可通过宏GUI_DEFAULT_EXTERN_FONT设置。

若GUI_USE_EXTERN_FONT设置为假或外部数据字体设置失败时，会采用GUI_DEFAULT_FONT配置的数组作为默认字体。
