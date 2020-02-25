.. vim: syntax=rst

如何制作APP图标
------------------

学会了如何制作字库后，制作APP图标就简单多了。只需要一个应用软件FontCreator，就可以做出各种各样的图标，如 图27_1_ APP图标。这是我们这一章的实验要求，下面以野火的logo为例，教大家怎么使用FontCreator这个工具。

.. image:: /media/docx133.jpg
   :align: center
   :alt: 图 27‑1 APP图标
   :name: 图27_1

图 27‑1 APP图标

工具使用方法
~~~~~~~~~~~~~~~~~~

FontCreator.exe位于例程目录\emxgui\tools\FontCreator_ha中，如 图27_2_，框框处就是我们的主角FontCreator。

.. image:: /media/docx134.jpg
   :align: center
   :alt: 图 27‑2文件路径
   :name: 图27_2

图 27‑2文件路径

双击FontCreator，运行软件，软件的界面图如 图27_3_。

.. image:: /media/docx135.jpeg
   :align: center
   :alt: 图 27‑3软件界面
   :name: 图27_3

图 27‑3软件界面

下面我们开始创建我们的APP图标：

1. 新建一个tft文件



   在文件->新建，选择新建一个字体文件，命名为firelogo，然后点击“确定”，操作流程如 图27_4_。

.. image:: /media/docx136.jpeg
   :align: center
   :alt: 图 27‑4 新建文件
   :name: 图27_4

图 27‑4 新建文件

2. 选择替换的字符编码

所谓的APP图标，只是将该字库的某个字符编码替换为我们的图标，假如我们将A换成某个图标，当我们使用这个字库，显示字符A，就会显示我们的图标。我们切换会普通的字库，字符A就还是字符 A。下面我们将 A替换为野火的logo，双击 图27_5_ 的框框处，会出现一个新的界面，如 图27_6_。

.. image:: /media/docx137.jpeg
   :align: center
   :alt: 图 27‑5 选择替换的字符 A
   :name: 图27_5

图 27‑5 选择替换的字符 A

.. image:: /media/docx138.jpeg
   :align: center
   :alt: 图 27‑6字符A的界面
   :name: 图27_6

图 27‑6字符A的界面

.. image:: /media/docx139.jpg
   :align: center
   :alt: 图 27‑7 字体的设置
   :name: 图27_7

图 27‑7 字体的设置

图27_7_ 的 1 处，用来设置字体的宽度，我们在设计的时候，尽量使每个图标都是等宽的。处是我们图标的设计区，从WinAscent到WinDescent。如果设计的图标超过这两条边线，则超出的部分不会显示，在设计图标的时候，最好使图标位于处的中间。

FontCreator提供两种设计方式：有图片加载方式以及手动绘制，图27_8_ 的处是图片加载，支持多种格式，包括.gif，.jpg，.png，.ai等格式 ；处是手工绘制。这里就不讲手动绘制了，有兴趣的，绘画功底强的读者，可以尝试一下第二种绘制方式。

.. image:: /media/docx140.jpg
   :align: center
   :alt: 图 27‑8 绘制方式
   :name: 图27_8

图 27‑8 绘制方式

点击 图27_8_ 的处，选择野火的logo，如 图27_9_ 所示，这里使用的是.ai格式的文件。（这里也可以选择一张普通格式的图片，没有什么影响）

.. image:: /media/docx141.jpg
   :align: center
   :alt: 图 27‑9 选择图标
   :name: 图27_9

图 27‑9 选择图标

打开之后，如 图27_10_ 所示，之后，我们就需要调整图标的位置，大小，使它位于WinAscent到WinDescent之间，调整后的结果如 图27_11_ 所示，图标位于两个阴影区域的交界区。

.. image:: /media/docx142.jpg
   :align: center
   :alt: 图 27‑10 选中图标
   :name: 图27_10

图 27‑10 选中图标

.. image:: /media/docx143.jpg
   :align: center
   :alt: 图 27‑11 调整之后的结果
   :name: 图27_11

图 27‑11 调整之后的结果

点击 图27_12_ 的处，回到最开始的界面，我们可以看到A字符变成野火的logo了。这就说明我们的制作完成了。

.. image:: /media/docx144.jpg
   :align: center
   :alt: 图 27‑12 完成制作
   :name: 图27_12

图 27‑12 完成制作

3. 保存字库

点击图 27‑13的处，保存字库，在处选择保存的路径，最后点击“保存”按键保存。

.. image:: /media/docx145.jpg
   :align: center
   :alt: 图 27‑13 保存字库
   :name: 图27_13

图 27‑13 保存字库

4. 测试生成的字体

我们可以在电脑上使用刚刚生成的字体，具体的操作方法：双击刚刚生成的firelogo.ttf文件，安装该字体，如 图27_14_。

.. image:: /media/docx146.jpeg
   :align: center
   :alt: 图 27‑14 安装字体
   :name: 图27_14

图 27‑14 安装字体

打开一个新建的word文档，在字体设置处，选择firelogo，然后输入A，就可以打出野火的logo了，是不是很神奇，如 图27_15_。

.. image:: /media/docx147.jpg
   :align: center
   :alt: 图 27‑15 测试结果
   :name: 图27_15

图 27‑15 测试结果

到此为止，制作APP图标就结束了。利用上一章的软件和方法，将刚刚生成的字体制作成emXGUI支持的格式xft即可。这样，我们就可以在emXGUI上使用我们刚刚的图标字体，下面我们一起学习如何在emXGUI上显示刚刚制作完成的图标。

显示APP图标实验
~~~~~~~~~~~~~~~~~~

在emXGUI上显示APP图标，实际上就是切换到字体类型，然后显示图标对应的字符。使用的函数API与上一章相同。实验的设计要求如 图27_16_。处使用的是logo字体，主要为野火的图标；处为控制图标字体，是常见的一些图标，例如返回，上翻，下翻，保存等图标；处使用的图标字体。

.. image:: /media/docx148.jpg
   :align: center
   :alt: 图 27‑16 设计要求
   :name: 图27_16

图 27‑16 设计要求

.. _代码分析-22:

代码分析
^^^^^^^^

(1) 创建字体句柄

.. code-block:: c
    :caption: 代码清单 27‑1 三种字体类型（文件gui_font_port.c）
    :linenos:
    :name: 代码清单27_1

     #if(GUI_ICON_LOGO_EN)
     /* logo字体 */
     HFONT logoFont =NULL;
     /* 图标字体 */
     HFONT iconFont =NULL;
     /* 控制图标字体 */
     HFONT controlFont =NULL;
     #endif

创建三种字体类型，用来存放字体句柄。

.. code-block:: c
    :caption: 代码清单 27‑2创建字体句柄（文件gui_font_port.c）
    :linenos:
    :name: 代码清单27_2

     /**
     * @brief GUI默认字体初始化
     * @param 无
     * @retval 返回默认字体的句柄
     */
     HFONT GUI_Default_FontInit(void)
     {
<<<<<<< HEAD
     //省略一些代码
     #if(GUI_ICON_LOGO_EN)

     /* 创建logo字体 */
     logoFont = XFT_CreateFont(GUI_LOGO_FONT);
     /* 创建图标字体 */
     iconFont = XFT_CreateFont(GUI_ICON_FONT);
     /* 创建控制图标字体 */
     controlFont = XFT_CreateFont(GUI_CONTROL_FONT);

     if(logoFont==NULL)
     GUI_ERROR("logoFont create failed");

     if(iconFont ==NULL)
     GUI_ERROR("iconFont create failed");

     if(controlFont ==NULL)
     GUI_ERROR("controlFont create failed");
     #endif

     return defaultFont;
=======
        //省略一些代码
    #if(GUI_ICON_LOGO_EN)

        /* 创建logo字体 */
        logoFont = XFT_CreateFont(GUI_LOGO_FONT);
        /* 创建图标字体 */
        iconFont = XFT_CreateFont(GUI_ICON_FONT);
        /* 创建控制图标字体 */
        controlFont = XFT_CreateFont(GUI_CONTROL_FONT);

        if(logoFont==NULL)
            GUI_ERROR("logoFont create failed");

        if(iconFont ==NULL)
            GUI_ERROR("iconFont create failed");

        if(controlFont ==NULL)
            GUI_ERROR("controlFont create failed");
    #endif

        return defaultFont;
>>>>>>> dev
     }

GUI_Default_FontInit函数中，调用XFT_CreateFont函数来创建字体，GUI_LOGO_FONT、GUI_ICON_FONT以及GUI_CONTROL_FONT是我们使用bin2c软件生成的图标字体数组，以logo图标字体为例，
见 代码清单27_3_ 。就这样我们就在emXGUI上“安装”了三种字体，需要使用什么字体，只需要调用SetFont函数即可。

.. code-block:: c
    :caption: 代码清单 27‑3 字库数组（文件LOGO_50_4BPP.c）
    :linenos:
    :name: 代码清单27_3

    #define GUI_LOGO_FONT LOGO_50_4BPP
    const char LOGO_50_4BPP[]={88,70,84,0,88,71,85,73,32,70,111,110,116,0,0,0,
    0,0,0,0,232,19,0,0,232,51,0,0,64,0,0,0,
    234,4,0,0,2,0,4,0,50,0,50,0,4,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,42,0,0,25,4,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,

(2) 窗口回调函数

-  WM_PAINT

.. code-block:: c
    :caption: 代码清单 27‑4 WM_PAINT消息（文件GUI_DEMO_LogoIconFont.c）
    :linenos:
    :name: 代码清单27_4

     case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
     {
<<<<<<< HEAD
     PAINTSTRUCT ps;
     HDC hdc;

     RECT rc0;

     hdc =BeginPaint(hwnd,&ps);

     ////用户的绘制内容...
     GetClientRect(hwnd,&rc0);
     SetPenColor(hdc,MapRGB(hdc,200,200,220));
     SetTextColor(hdc,MapRGB(hdc,250,250,250));
     /* 使用图标字体*/
     SetFont(hdc, logoFont);
     DrawText(hdc,L" A B C ",-1,&rc0,DT_LEFT);
     /* 使用控制图标字体*/
     SetFont(hdc, controlFont);
     SetTextColor(hdc,MapRGB(hdc,0,0,0));
     rc0.y += 80;
     DrawText(hdc,L" A B C D E F G H \\r\n I J K L M N O P",-1,&rc0,DT_LEFT);
     /* 使用图标字体*/
     SetFont(hdc, iconFont);
     SetTextColor(hdc,MapRGB(hdc,238,142,0));
     rc0.y += 120;
     DrawText(hdc,L" A B C D E ",-1,&rc0,DT_LEFT);

     SetTextColor(hdc,MapRGB(hdc,100,149,237));
     rc0.y += 120;
     DrawText(hdc,L" F G H I J",-1,&rc0,DT_LEFT);
     /* 恢复默认字体 */
     SetFont(hdc, defaultFont);
     SetTextColor(hdc,MapRGB(hdc,250,250,250));

     EndPaint(hwnd,&ps);
     break;
=======
        PAINTSTRUCT ps;
        HDC hdc;

        RECT rc0;

        hdc =BeginPaint(hwnd,&ps);

        ////用户的绘制内容...
        GetClientRect(hwnd,&rc0);
        SetPenColor(hdc,MapRGB(hdc,200,200,220));
        SetTextColor(hdc,MapRGB(hdc,250,250,250));
        /* 使用图标字体*/
        SetFont(hdc, logoFont);
        DrawText(hdc,L" A B C ",-1,&rc0,DT_LEFT);
        /* 使用控制图标字体*/
        SetFont(hdc, controlFont);
        SetTextColor(hdc,MapRGB(hdc,0,0,0));
        rc0.y += 80;
        DrawText(hdc,L" A B C D E F G H \\r\n I J K L M N O P",-1,&rc0,DT_LEFT);
        /* 使用图标字体*/
        SetFont(hdc, iconFont);
        SetTextColor(hdc,MapRGB(hdc,238,142,0));
        rc0.y += 120;
        DrawText(hdc,L" A B C D E ",-1,&rc0,DT_LEFT);

        SetTextColor(hdc,MapRGB(hdc,100,149,237));
        rc0.y += 120;
        DrawText(hdc,L" F G H I J",-1,&rc0,DT_LEFT);
        /* 恢复默认字体 */
        SetFont(hdc, defaultFont);
        SetTextColor(hdc,MapRGB(hdc,250,250,250));

        EndPaint(hwnd,&ps);
        break;
>>>>>>> dev
     }

由于图标实际上就是字符，所以颜色受TextColor的影响，调用SetTextColor函数来选择图标的颜色，logoFont字体中的内容如 图27_17_ 所示。
调用SetFont函数切换字体，使用DrawText函数来显示A B C对应的图标。

.. image:: /media/docx149.jpg
   :align: center
   :alt: 图 27‑17 logoFont字体
   :name: 图27_17

图 27‑17 logoFont字体

controlFont字体中的内容如 图27_18_， 图标是从字符A到P，设置图标的颜色为RGB(0,0,0)，调用DrawText显示字符串“A B C D E F G H \\r\n I J K L M N O P”，就可以显示相应的图标。

.. image:: /media/docx150.jpeg
   :align: center
   :alt: 图 27‑18 控制图标字体
   :name: 图27_18

图 27‑18 控制图标字体

iconFont字体中的内容如 图27_19_，使用RGB(238,142,0)的颜色来显示头五个图标，矩形变量用来控制显示的位置，调用DrawText函数来显示前五个字符。设置颜色为RGB(100,149,237)，显示后五个字符，起点的y坐标偏移120个像素。

.. image:: /media/docx151.jpg
   :align: center
   :alt: 图 27‑19 图标字体
   :name: 图27_19

图 27‑19 图标字体

-  WM_ERASEBKGND

.. code-block:: c
    :caption: 代码清单 27‑5 WM_ERASEBKGND消息（文件GUI_DEMO_LogoIconFont.c）
    :linenos:
    :name: 代码清单27_5

     case WM_ERASEBKGND:
     {
<<<<<<< HEAD
     HDC hdc=(HDC)wParam;

     GetClientRect(hwnd,&rc);
     SetBrushColor(hdc,MapRGB(hdc,215,61,50));
     FillRect(hdc,&rc);
     return TRUE;
=======
        HDC hdc=(HDC)wParam;

        GetClientRect(hwnd,&rc);
        SetBrushColor(hdc,MapRGB(hdc,215,61,50));
        FillRect(hdc,&rc);
        return TRUE;
>>>>>>> dev
     }

使用FillRect来绘制客户区的背景，颜色调用SetBrushColor函数来设置，此处为RGB(215,61,50)，最后要返回TRUE，这样在WM_PAINT消息，才不会重绘客户区背景。

最后，将GUI_DEMO_LogoIconFont函数添加到AppMain函数中。

.. _实验结果-13:

实验结果
^^^^^^^^

.. image:: /media/docx152.jpg
   :align: center
   :alt: 图 27‑20 实验结果
   :name: 图27_20

图 27‑20 实验结果

