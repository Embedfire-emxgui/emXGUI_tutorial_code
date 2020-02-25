.. vim: syntax=rst


绘图函数
------------

emXGUI提供了各种绘图API，下表主要列出了一些常用的绘图API，用于绘制基本的图形，有关的详细描述，可以参阅后面的内容。更多的API函数说明，请阅读《emXGUI API 编程手册》章节：绘图API。

.. list-table:: 表格 20‑1 常用的API函数
    :widths: 15 25
    :header-rows: 1
    :name: 表20-1

    * - API函数
      - 描述
    * - 颜色API
      - \
    * - MapRGB (hdc, U8 r, U8 g, U8 b)
      - 以r，g，b三基色方式设置颜色值，返回目标颜色
    * - MapARGB(HDC hdc,U8 a,U8 r,U8 g,U8 b);
      - 以a，r，g，b三基色方式设置颜色值，返回目标颜色
    * - MapRGB565(HDC hdc,U16 rgb565);
      - 将RGB565格式转化为与hdc相同的颜色格式。
    * - MapXRGB8888(HDC hdc,U32 xrgb8888);
      - 将XRGB8888格式转化为与hdc相同的颜色格式。
    * - MapARGB8888(HDC hdc,U32 argb8888);
      - 将ARGB8888格式转化为与hdc相同的颜色格式。
    * - SetTextColor(HDC hdc,COLORREF color);
      - 设置字体的颜色，返回旧字体的颜色
    * - SetPenColor(HDC hdc,COLORREF color);
      - 设置画笔颜色，返回旧的画笔颜色
    * - SetBrushColor(HDC hdc,COLORREF color);
      - 设置画刷颜色，返回旧的画刷颜色
    * - 绘图API
      - \
    * - Line(HDC hdc,int sx,int sy,int ex,int ey);
      - 画一条大小为一个像素的线
    * - DrawRect(HDC hdc,const RECT \*lpRect);
      - 画空心矩形
    * - DrawRoundRect(HDC hdc,const RECT \*lpRect,int r);
      - 画空心圆角矩形
    * - DrawCircle(HDC hdc,int cx,int cy,int r);
      - 画空心圆
    * - DrawEllipse(HDC hdc,int cx, int cy, int rx, int ry);
      - 画空心椭圆
    * - FillRect(HDC hdc,const RECT \*lpRect);
      - 填充矩形
    * - GradientFillRect(HDC hdc,const RECT \*lpRect,COLORREF Color0,COLORREF Color1,BOOL bVert);
      - 渐变色填充矩形
    * - FillRoundRect(HDC hdc,const RECT \*lpRect,int r);
      - 填充圆角矩形
    * - FillCircle(HDC hdc,int cx,int cy,int r);
      - 画实心圆
    * - FillEllipse(HDC hdc,int cx, int cy, intrx,int ry);
      - 画实心椭圆
    * - FillPolygon(HDC hdc,int xOff,int yOff,const POINT \*pt,int count);
      - 画实心多边形

颜色API
~~~~~~~~~~

emXGUI设置颜色，通常有两种方式：一、使用MapRGB函数以r，g，b三基色方式设置颜色值；二、使用MapRGBxxx函数（xxx表示颜色格式），将某种颜色格式，转化为与hdc相同的颜色格式。MapRGBxxx函数有两个形参，一个是绘图上下文HDC，另一个是相应的颜色格式，见 代码清单20_1_。

.. code-block:: c
    :caption: 代码清单 20‑1 设置颜色值（文件emXGUI.h）
    :linenos:
    :name: 代码清单20_1

     #define RGB332(r,g,b) ((r&0x7)<<5)|((g&0x7)<<2)|(b&0x3)
     #define RGB565(r,g,b) ((r&0x1F)<<11)|((g&0x3F)<<5)|(b&0x1F)
     #define XRGB1555(r,g,b) ((r&0x1F)<<10)|((g&0x1F)<<5)|(b&0x1F)
     #define ARGB1555(a,r,g,b) ((a<<15)|(r&0x1F)<<10)|((g&0x1F)<<5)|(b&0x1F)
     #define ARGB4444(a,r,g,b) ((a<<12)|((r&0xF)<<8)|((g&0xF)<<4)|(b&0xF))
     #define RGB888(r,g,b) ((r&0xFF)<<16)|((g&0xFF)<<8)|(b&0xFF)
     #define XRGB8888(r,g,b) ((r&0xFF)<<16)|((g&0xFF)<<8)|(b&0xFF)
     #define ARGB8888(a,r,g,b) ((a&0xFF)<<24)|((r&0xFF)<<16)|((g&0xFF)<<8)|(b&0xFF)

举个例子，假如我们现在要设置颜色，它RGB分量分别为R：0，G：0，B：255。

.. code-block:: c
    :caption: 代码清单 20‑2 使用MapRGB函数
    :linenos:
    :name: 代码清单20_2

     MapRGB(hdc,0,0,255)

代码清单20_2_ 使用MapRGB函数，将相应的RGB分量作为实参，完成颜色的设置。

.. code-block:: c
    :caption: 代码清单 20‑3 使用MapRGB888函数
    :linenos:
    :name: 代码清单20_3

     MapRGB888(hdc,RGB888(0,0,255))

以Map前缀开头的都是函数，代表颜色的映射关系，会返回一个COLORREF类型的值。COLORREF可以理解成是设备色，与 HDC相关，换句话说，就是所有用 COLORREF 的地方, 都要使用MapXXX 函数；而RGBxxx则是宏定义，表示某种颜色对应的RGB分量。

代码清单20_3_ 使用MapRGB888函数，将RGB888（0，0，255）转化为与hdc相同的颜色格式。比如在一个RGB565的HDC中，RGB888（0，0，255）得到的颜色值为0000FF，经过MapRGB888(hdc，0x0000FF)后，实际就变成了设备色：0x001F。RGB888每一个像素占3个字节，R、G、B各8位。而RGB565的R是5位，G是6位，B是5位。转换公式，参考代码清单 20‑4。注意，在使用MapRGB888函数时，后面的颜色格式必须为RGB888。

.. code-block:: c
    :caption: 代码清单 20‑4 RGB888toRGB565转换公式
    :linenos:
    :name: 代码清单20_4

     cRed = (n888Color & 0x00ff0000) >> 19;
     cGreen = (n888Color & 0x0000ff00) >> 10;
     cBlue = (n888Color & 0x000000ff) >> 3;

     n565Color = (cRed << 11) + (cGreen << 5) + (cBlue << 0);

至于带透明度的颜色，则使用MapARGB、MapARGB8888和MapXRGB8888等函数，具体使用方法可以参考上面的内容。

介绍完颜色的格式之后，下面学习如何设置文字、画笔和画刷的颜色。

.. code-block:: c
    :caption: 代码清单 20_5 设置文字、画笔和画刷的颜色API （文件emXGUI.h）
    :linenos:
    :name: 代码清单20_5

     COLORREF SetPenColor(HDC hdc,COLORREF color);
     COLORREF SetBrushColor(HDC hdc,COLORREF color);
     COLORREF SetTextColor(HDC hdc,COLORREF color);

1) hdc：绘图上下文；

2) color：颜色值。这里使用的是COLORREF类型的颜色值。因此，这里的实参应该是经过MapRGBxxx函数后得到的颜色值。

调用 代码清单20_5_ 的函数，就可以设置文字、画笔和画刷的颜色值。

绘制图形外框
~~~~~~~~~~~~~~~~~~

绘图API
^^^^^^^^^^^^^^^

Line()
''''''''''''

绘制一条线宽为1个像素的直线。起点和终点可以由用户决定，线条的颜色由PenColor控制。

.. code-block:: c
    :caption: 代码清单 20‑6 函数原型
    :linenos:
    :name: 代码清单20_6

     void Line(HDC hdc,int sx,int sy,int ex,int ey);

1) hdc：绘图上下文；

2) sx，sy：直线起始点的坐标；

3) ex，ey：直线终点的坐标；

DrawRect()
''''''''''''''''''''

绘制一个空心矩形，大小及位置由结构体rc决定，线条的颜色由PenColor控制。目前的emXGUI不支持修改矩形的线宽。

.. code-block:: c
    :caption: 代码清单 20‑7 函数原型
    :linenos:
    :name: 代码清单20_7

     void DrawRect(HDC hdc,const RECT *lpRect);

1) hdc：绘图上下文；

2) lpRect：矩形参数指针，决定矩形的显示位置和它的大小。

DrawRoundRect()
''''''''''''''''''''''''''''''

绘制一个空心圆角矩形，大小及位置由结构体rc决定，用户可以自己定义圆角的半径。线条的颜色由PenColor控制。目前的emXGUI不支持修改矩形的线宽。

.. code-block:: c
    :caption: 代码清单 20‑8 函数原型
    :linenos:
    :name: 代码清单20_8

     void DrawRoundRect(HDC hdc,const RECT *lpRect,int r);

1) hdc：绘图上下文；

2) lpRect：矩形参数指针，决定矩形的显示位置和它的大小。

3) r：圆角半径，一般不能超过某个值，该值取决于矩形的宽和高这两者中的最小值的一半。

DrawCircle()
''''''''''''''''''''''''

绘制一个空心圆，用户可以决定圆的圆心和半径 。线条的颜色由PenColor控制。目前的emXGUI不支持修改矩形的线宽。

.. code-block:: c
    :caption: 代码清单 20‑9 函数原型
    :linenos:
    :name: 代码清单20_9

     void DrawCircle(HDC hdc,int cx,int cy,int r);

1) hdc：绘图上下文；

2) cx，cy：圆心的位置坐标；

3) r：圆的半径。

DrawEllipse()
''''''''''''''''''''''''''

绘制一个空心椭圆，用户可以决定椭圆的中心，水平半径以及以及垂直半径。线条的颜色由PenColor控制。目前的emXGUI不支持修改矩形的线宽。

.. code-block:: c
    :caption: 代码清单 20‑10 函数原型
    :linenos:
    :name: 代码清单20_10

     void DrawEllipse(HDC hdc,int cx, int cy, int rx, int ry);

1) hdc：绘图上下文；

2) cx，cy：椭圆的中心位置坐标；

3) rx：椭圆的水平半径；

4) ry：椭圆的垂直半径。

以上的这些函数，我们通常可以用来绘制一个图形的边框，但是由于改变不了线宽，一旦我们对图形的外边框有大小要求，则需要采用另一种方法，这个方法在下一小节进行讲解。

绘制图形外观实验
^^^^^^^^^^^^^^^^^^^^^^^^

.. _设计要求-10:

设计要求
''''''''''''

使用上面的几个绘图API，绘制出 图20_1_ 的界面。

.. image:: /media/docx084.jpg
   :align: center
   :alt: 图 20‑1 设计要求
   :name: 图20_1

图 20‑1 设计要求

.. _代码分析-10:

代码分析
''''''''''''

(1) 创建父窗口

.. code-block:: c
    :caption: 代码清单 20‑11 GUI_DEMO_DrawTest函数（文件GUI_DEMO_DrawTest.c）
    :linenos:
    :name: 代码清单20_11

     void GUI_DEMO_DrawTest(void)
     {
      HWND hwnd;
      WNDCLASS wcex;
      MSG msg;
      wcex.Tag = WNDCLASS_TAG;

      wcex.Style = CS_HREDRAW | CS_VREDRAW;
      wcex.lpfnWndProc = WinProc; //设置主窗口消息处理的回调函数.

      wcex.cbClsExtra = 0;
      wcex.cbWndExtra = 0;
      wcex.hInstance = NULL;
      wcex.hIcon = NULL;
      wcex.hCursor = NULL;

      //创建主窗口
      hwnd =CreateWindowEx(NULL,
      &wcex,
      _T("emXGUI Window"), //窗口名称
      WS_CLIPCHILDREN,
      0,0,GUI_XSIZE,GUI_YSIZE, //窗口位置和大小
      NULL,NULL,NULL,NULL);

      //显示主窗口
      ShowWindow(hwnd,SW_SHOW);

      //开始窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。
      while(GetMessage(&msg,hwnd))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
     }

创建父窗口，标题栏为“GUI_DEMO_DrawTest”，设置winProc作为窗口回调函数。

(2) 窗口回调函数

.. code-block:: c
    :caption: 代码清单 20‑12 窗口回调函数winProc（文件GUI_DEMO_DrawTest.c）
    :linenos:
    :name: 代码清单20-12

     static LRESULT WinProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
     {
		RECT rc;
		switch(msg)
		{
		//窗口创建时,会自动产生该消息,
		//在这里做一些初始化的操作或创建子窗口.
			case WM_CREATE:
			{

				GetClientRect(hwnd,&rc); //获得窗口的客户区矩形.
				CreateWindow(BUTTON,L"OK",WS_VISIBLE,
				rc.w-80,8,68,32,hwnd,ID_OK,NULL,NULL); //创建一个按钮(示例).
				return TRUE;
			}
			//WM_NOTIFY消息:wParam低16位为发送该消息的控件ID,
			//高16位为通知码;lParam指向了一个NMHDR结构体
			case WM_NOTIFY:
			{
				u16 code,id;

				code =HIWORD(wParam); //获得通知码类型.
				id =LOWORD(wParam); //获得产生该消息的控件ID.

				if(id==ID_OK && code==BN_CLICKED) // 按钮“单击”了.
				{
				PostCloseMessage(hwnd); //使产生WM_CLOSE消息关闭窗口.
				}
				break;
			}
			case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
			{
				PAINTSTRUCT ps;
				HDC hdc;
				RECT rc;
				hdc =BeginPaint(hwnd,&ps); //开始绘图
				GetClientRect(hwnd,&rc);
				SetBrushColor(hdc, MapRGB(hdc, 0, 0, 0));
				FillRect(hdc, &rc);
				Draw_Func(hwnd, hdc);

				EndPaint(hwnd,&ps); //结束绘图
				break;
			}
			default: //用户不关心的消息,由系统处理.
			{
				return DefWindowProc(hwnd,msg,wParam,lParam);
			}

			}
			return WM_NULL;
     }

例程的窗口函数相对简单一点，有不明白的地方，可以查阅前面的章节，这里就进行展开讲解，重点看WM_PAINT消息。

在WM_PAINT消息中，使用GetClientRect函数获取客户区的位置和大小，并使用SetBrushColor和FillRect函数将桌面背景颜色设置为黑色。绘制外观的函数Draw_Func，见 代码清单20_13_。

.. code-block:: c
    :caption: 代码清单 20‑13 Draw_Func函数（文件GUI_DEMO_DrawTest.c）
    :linenos:
    :name: 代码清单20_13

     void Draw_Func(HWND hwnd, HDC hdc)
     {
		RECT rc;
		//设置矩形参数
		rc.x =50;
		rc.y =80;
		rc.w =140;
		rc.h =75;
		SetPenColor(hdc,MapRGB888(hdc, DrawRect_col)); //设置画笔颜色(用于画线，框).

		DrawRect(hdc,&rc); //绘制一个空心矩形
		//绘制一个空心圆.

		SetPenColor(hdc,MapRGB888(hdc,DrawCir_col));
		DrawCircle(hdc,80,100,50);
		//画斜线
		SetPenColor(hdc,MapRGB888(hdc,DrawLine_col));
		Line(hdc,30,160,200,230);
		//画椭圆
		SetPenColor(hdc,MapRGB888(hdc,DrawEllipse_col));
		DrawEllipse(hdc, 150, 155, 65, 40);
     }

代码清单20_13_ 中，Drawxxx每绘制一种图形，都调用一次SetPenColor函数来改变图形的颜色，这些颜色值采用RGB888的颜色格式，采用宏定义的形式，方便修改，见 代码清单20_14_。

.. code-block:: c
    :caption: 代码清单 20‑14 颜色值的宏定义
    :linenos:
    :name: 代码清单20_14

     //空心图形颜色
     #define DrawRect_col RGB888(250,250,250) //矩形
     #define DrawCir_col RGB888(79,129,189) //圆
     #define DrawEllipse_col RGB888(247,186,0) //椭圆
     #define DrawLine_col RGB888(146,208,80) //线

最后，将绘制的窗口加入到GUI_AppMain函数中，如 代码清单20_15_。

.. code-block:: c
    :caption: 代码清单 20‑15 GUI_AppMain函数（文件GUI_AppMain.c）
    :linenos:
    :name: 代码清单20_15

     void GUI_AppMain(void)
     {
		while(1)
		{
			GUI_DEMO_Button();
			GUI_DEMO_Checkbox();
			GUI_DEMO_Radiobox();
			GUI_DEMO_Textbox();
			GUI_DEMO_Progressbar();

			GUI_DEMO_Scrollbar();
			GUI_DEMO_Listbox();
			GUI_DEMO_TextOut();
			GUI_DEMO_Messagebox();
			GUI_DEMO_DrawTest();
		}
     }

.. _实验结果-2:

实验结果
''''''''''''

实验结果如 图20_2_ 所示，本实验只是让读者熟悉绘制API的使用，比较简单。

.. image:: /media/docx085.jpg
   :align: center
   :alt: 图 20‑2实验结果
   :name: 图20_2

图 20‑2实验结果

绘制实心图形
~~~~~~~~~~~~~~~~~~

.. _绘图api-1:

绘图API
^^^^^^^^^^^^^^^

FillRect()
''''''''''''''''''''

绘制一个实心矩形，其位置大小由结构体RECT决定，填充颜色由BrushColor控制。

.. code-block:: c
    :caption: 代码清单 20‑16 函数原型
    :linenos:
    :name: 代码清单20_16

     void FillRect(HDC hdc,const RECT *lpRect);

1) hdc：绘图上下文；

2) lpRect：矩形参数，控制矩形的位置和大小。

GradientFillRect()
''''''''''''''''''''''''''''''''''''

绘制一个实心矩形，其位置大小由结构体RECT决定，填充颜色采用渐变色填充。

.. code-block:: c
    :caption: 代码清单 20‑17 函数原型
    :linenos:
    :name: 代码清单20_17

     void GradientFillRect(HDC hdc,const RECT *lpRect,

     COLORREF Color0,COLORREF Color1, BOOL bVert);

1) hdc：绘图上下文；

2) lpRect：矩形参数。控制矩形的位置和大小；

3) Color0：起始颜色；

4) Color1：结束颜色

5) bVert：TURE——以垂直方向渐变填充； FALSE——以水平方向渐变填充。

注意，当填充的两种颜色间隔较大，会出现明显的断层。建议要么修改屏幕(或HDC)的颜色格式为XRGB888，或者修改颜色值，减下颜色的间隔。

FillRoundRect()
''''''''''''''''''''''''''''''

绘制一个圆角矩形，其位置大小由结构体RECT决定，用户可以自定义圆角半径，填充颜色由BrushColor控制。

.. code-block:: c
    :caption: 代码清单 20‑18 函数原型
    :linenos:
    :name: 代码清单20_18

     void DrawRoundRect(HDC hdc,const RECT *lpRect,int r);

1) hdc：绘图上下文；

2) lpRect：矩形参数。控制矩形的位置和大小；

3) r：圆角的半径值

FillCircle()
''''''''''''''''''''''''

绘制一个实心圆，用户可以决定圆的圆心和半径 。颜色由BrushColor控制。

.. code-block:: c
    :caption: 代码清单 20‑19 函数原型
    :linenos:
    :name: 代码清单20_19

     void DrawCircle(HDC hdc,int cx,int cy,int r);

1) hdc：绘图上下文；

2) cx、cy：圆心的位置坐标；

3) r：圆的半径。

FillEllipse()
''''''''''''''''''''''''''

绘制一个实心椭圆，用户可以决定椭圆的中心，水平半径以及以及垂直半径。颜色由BrushColor控制。

.. code-block:: c
    :caption: 代码清单 20‑20 函数原型
    :linenos:
    :name: 代码清单20_20

     void DrawEllipse(HDC hdc,int cx, int cy, int rx, int ry);

1) hdc：绘图上下文；

2) cx、cy：椭圆的中心位置坐标；

3) rx：椭圆的水平半径；

4) ry：椭圆的垂直半径；

FillPolygon()
'''''''''''''

绘制一个实心多边形，用户只需要给出多边形各个顶点的坐标就可以了。颜色由BrushColor控制。

.. code-block:: c
    :caption: 代码清单 20‑21 函数原型
    :linenos:
    :name: 代码清单20_21

     void FillPolygon(HDC hdc,int xOff,int yOff,const POINT *pt,int count);

1) hdc：绘图上下文；

2) xOff，yOff：绘制到目标的偏移坐标位置；

3) pt：多边形各顶点坐标数组缓冲区，数组元素的排列顺序应该是各个顶点的逆时钟排序。图 20‑3，以五边形为例，若要绘制图中的五边形，pt数组中存放的坐标应该对应A，B，C，D，E。

4) count：多边顶点数。

.. image:: /media/docx086.jpg
   :align: center
   :alt: 图 20‑3 绘图顺序说明
   :name: 图20_3

图 20‑3 绘图顺序说明

这里补充一下：xOff以及yOff的用法。如果不使用的话，直接给0即可。

.. image:: /media/docx087.jpg
   :align: center
   :alt: 图 20‑4 xOff和yOff说明
   :name: 图20_4

图 20‑4 xOff和yOff说明

以 图20_4_ 为例，进行讲解。我们要在客户区绘制这样的四边形。以A点为原点，即xOff等于A点的横坐标，yOff等于 A的纵坐标，得到如 图20_5_ 所示的坐标值，这样可以减少计算量。

.. image:: /media/docx088.jpg
   :align: center
   :alt: 图 20‑5 得到的坐标
   :name: 图20_5

图 20‑5 得到的坐标

绘制填充图形实验
^^^^^^^^^^^^^^^^^^^^^^^^

.. _设计要求-11:

设计要求
''''''''''''

在上一个实验的基础上，使用上述的绘图API，绘制如下界面，见 图20_6_。

.. image:: /media/docx089.jpg
   :align: center
   :alt: 图 20‑6 设计要求
   :name: 图20_6

图 20‑6 设计要求

.. _代码分析-11:

代码分析
''''''''

代码与上一节的实验相同，重点看WM_PAINT消息，

.. code-block:: c
    :caption: 代码清单 20‑22 WM_PAINT消息响应（文件GUI_DEMO_DrawTest.c）
    :linenos:
    :name: 代码清单20_22

     case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
     {
        PAINTSTRUCT ps;
        HDC hdc;
        RECT rc;
        hdc =BeginPaint(hwnd,&ps); //开始绘图
        GetClientRect(hwnd,&rc);
        SetBrushColor(hdc, MapRGB(hdc, 0, 0, 0));
        FillRect(hdc, &rc);

        Draw_Func(hwnd, hdc);
        Fill_Func(hwnd, hdc);
        EndPaint(hwnd,&ps); //结束绘图
        break;
     }

代码清单20_22_ 中，调用了Fill_Func函数，来绘制图形，见 代码清单20_23_。

.. code-block:: c
    :caption: 代码清单 20‑23 Fill_Func函数（文件GUI_DEMO_DrawTest.c）
    :linenos:
    :name: 代码清单20_23

    void Fill_Func(HWND hwnd, HDC hdc)
    {
        POINT pt_RTri[3]={{35, 200},
                        {35, 300},
                        {235, 300}
    };
    //绘制直角三角形
    SetBrushColor(hdc, MapRGB888(hdc, FillRTri_col)); //设置颜色， 使用BrushColor。
    FillPolygon(hdc, 10, 30, &pt_RTri[0],3); //填充多边形。

    //绘制等边三角形
    POINT pt_EqTri[3]={{220, 120},{320, 120},{270, 13}};
    SetBrushColor(hdc, MapRGB888(hdc, FillEqTri_col)); //设置颜色， 使用BrushColor。
    FillPolygon(hdc, 10, 30, &pt_EqTri[0],3); //填充多边形。
    //绘制圆
    SetBrushColor(hdc, MapRGB888(hdc, FillCir_col));
    FillCircle(hdc, 320, 250, 60);
    //绘制矩形
    RECT rc_rect = {280, 320, 165, 55};
    SetBrushColor(hdc, MapRGB888(hdc, FillRECT_col));
    FillRect(hdc, &rc_rect);
    //绘制圆角矩形
    RECT rc_Roundrect = {390, 160, 55, 150};
    SetBrushColor(hdc, MapRGB888(hdc, FillRoundRECT_col));
    FillRoundRect(hdc, &rc_Roundrect,14);
    //绘制椭圆
    SetBrushColor(hdc, MapRGB888(hdc, FillEllipse_col));
    FillEllipse(hdc, 500, 80, 90, 55);
    //绘制渐变色正方形
    RECT rc_square = {470, 235, 140, 140};
    GradientFillRect(hdc, &rc_square, MapRGB888(hdc, Fillsquare_col0),
    MapRGB888(hdc, Fillsquare_col1), FALSE);
    //绘制正方体顶部
    RECT Cube = {630, 120, 100, 100};
    SetBrushColor(hdc, MapRGB888(hdc, FillCube_col));
    FillRect(hdc, &Cube);
    //绘制正方体侧面
    POINT pt_SidePolygon[4]={{730, 120}, {730, 220},
    {765, 185}, {765, 85}};
    SetBrushColor(hdc, MapRGB888(hdc, FillCubeside_col));
    FillPolygon(hdc, 0, 0, &pt_SidePolygon[0],4); //填充多边形。
    //绘制正方体正面
    POINT pt_TopPolygon[4]={{665, 85}, {630, 120},
    {730, 120}, {765, 85}};
    SetBrushColor(hdc, MapRGB888(hdc, FillCubetop_col));
    FillPolygon(hdc, 0, 0, &pt_TopPolygon[0],4); //填充多边形。
    //绘制长方体
    RECT cuboid = {650, 280, 60, 165};
    SetBrushColor(hdc, MapRGB888(hdc, Fillcuboid_col));
    FillRect(hdc, &cuboid);
    //绘制长方体侧面
    POINT pt_cuboidSide[4]={{710, 280}, {710, 445},
    {731, 424}, {731, 259}};
    SetBrushColor(hdc, MapRGB888(hdc, Fillcuboidside_col));
    FillPolygon(hdc, 0, 0, &pt_cuboidSide[0],4); //填充多边形。
    //绘制长方体正面
    POINT pt_cuboidTop[4]={{671, 259}, {650, 280},
    {710, 280}, {731, 259}};
    SetBrushColor(hdc, MapRGB888(hdc, Fillcuboidtop_col));
    FillPolygon(hdc, 0, 0, &pt_cuboidTop[0],4); //填充多边形。
    }

使用SetBrushColor函数来设置填充的颜色，调用Fillxxxx函数进行填充。下面讲解一下正方体制作，长方体也是一样的操作。

在讲解正方体之间，给大家复习一下小学学过的画立体图形的方法：斜二测画法。

.. image:: /media/docx090.jpg
   :align: center
   :alt: 图 20‑7 斜二测画法示意图
   :name: 图20_7

图 20‑7 斜二测画法示意图

斜二测画法的口诀是：平行改斜垂依旧，横等纵半竖不变。我们学习斜二测画法，主要是为了做坐标的计算。emXGUI没有集成绘制3D图形库，因此，如果我们需要绘制3D图形时，就需要自己计算坐标。图20_7_，
是一个2*2*2的正方体，由口诀的第一句话，可以知道角OBB’等于45°，第二句话说明了AA’和BB’的长度等于原来的长度的二分之一。由此，我们就可以计算出整个正方体各个顶点的坐标值。将所得的坐标值存放到pt数组中，利用FillPolygon函数，就可以绘制出来正方体了。

另外，由于光源与立方体的位置，决定了三个面颜色的不同。例程的 图20_6_ 中，是用Excel软件绘制的，再利用网页工具“在线取色器”，就可以得到每个面的颜色，见 代码清单20_24_。
Win10用户，可以使用画图3D工具的取色器来获取颜色值。获取的颜色值为16进值码，通过网页工具“RGB颜色值与十六进制颜色码转换工具”最终转换为RGB颜色值。

.. code-block:: c
    :caption: 代码清单 20‑24 正方体的颜色值
    :linenos:
    :name: 代码清单20_24

     //正方体
     #define FillCube_col RGB888(50,150,250) //正面
     #define FillCubeside_col RGB888(40,121,201) //侧面
     #define FillCubetop_col RGB888(90,171,251) //顶部

.. _实验结果-3:

实验结果
''''''''''''

最后得到的结果如 图20_8_。大致上和我们的设计要求一模一样，而且利用上面的方法画出来的立体图形的空间观感好。

.. image:: /media/docx091.jpg
   :align: center
   :alt: 图 20‑8 设计要求
   :name: 图20_8

图 20‑8 实验结果

绘制带外边框的图形
~~~~~~~~~~~~~~~~~~~~~~~~~~~

InflateRect函数
^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c
    :caption: 代码清单 20‑25 InflateRect函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单20_25

    BOOL InflateRect(RECT * lprc，int dx，int dy);

1) lprc：指向矩形数据结构。

2) dx： 左边和右边各增加的坐标数，为负数时，将缩小矩形。

3) dy：上边和下边各增加的坐标数，为负数时，将缩小矩形。

利用这个函数，我们就可以画出任意大小的外边框了。

绘制带外边框的图形实验
^^^^^^^^^^^^^^^^^^^^^^

.. _设计要求-12:

设计要求
''''''''''''

前面我们提到过，emXGUI暂时不提供设置画笔画大小的API函数。本小节，主要介绍一种画任意宽度的外边框的图形。这里以矩形为例，在实验20.3的基础上，显示一个带外边框的矩形，如 图20_9_。

.. image:: /media/docx092.jpg
   :align: center
   :alt: 图 20‑9 实验要求
   :name: 图20_9

图 20‑9 实验要求

.. _代码分析-12:

代码分析
''''''''''''

.. code-block:: c
    :caption: 代码清单 20‑26 实现过程（文件GUI_DEMO_DrawTest.c）
    :linenos:
    :name: 代码清单20_26

     RECT rc_borrect = {25, 330, 220, 100};
     SetBrushColor(hdc, MapRGB888(hdc, FillRect_borcol));//设置矩形的外边框颜色
     FillRect(hdc, &rc_borrect);

     InflateRect(&rc_borrect, -5, -5);//将矩形四条边的位置减少5个坐标值
     SetBrushColor(hdc, MapRGB888(hdc, FillborRect_col));//设置矩形的颜色
     FillRect(hdc, &rc_borrect);

在Fill_Func函数中，添加 代码清单20_26_ 的代码。先调用SetBrushColor以及FillRect绘制一个矩形作为背景，颜色设置为需要的边框颜色。
使用InflateRect函数，将这个矩形四条边的位置分别减少5个坐标值，也就是说矩形的外边框为5px。接着在上一个矩形的区域内，再绘制一个矩形。这就得到一个带5px外边框的矩形。

另外，如果想要实现1px外边框的矩形除了可以使用上面的方法，还可以使用DrawRect以及SetPenColor函数来实现，具体实现步骤：
先用DrawRect以及SetPenColor函数来绘制矩形的外边框，接着调用InflateRect函数，将这个矩形四条边的位置分别减少1个坐标值，调用SetBrushColor以及FillRect来绘制矩形。
第二种方法，较为简单，读者可以尝试自己编程实现。

.. _实验结果-4:

实验结果
''''''''''''

图20_10_ 处的矩形就是我们所绘制的外边框矩形。其他图形，如圆，椭圆，多边形，也可以采用同样的方式来绘制。

.. image:: /media/docx093.jpg
   :align: center
   :alt: 图 20‑10 实验结果
   :name: 图20_10

图 20‑10 实验结果
