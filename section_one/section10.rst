.. vim: syntax=rst


进度条控件
---------------

计算机在处理任务时，任务的进度经常采用进度条来显示，还可以表示处理任务的速度，完成度，剩余未完成任务量和可能需要处理时间，一般以长方形条状显示。如 图10_1_。

.. image:: /media/docx041.jpg
   :align: center
   :alt: 图 10‑1 进度条示例
   :name: 图10_1

创建进度条控件
~~~~~~~~~~~~~~~~~~~~~

.. _标准消息类型及参数说明-5:

标准消息类型及参数说明
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

本章使用的消息类型常用的有WM_CREATE、WM_TIMER、WM_NOTIFY和WM_CTLCOLOR。WM_CREATE消息用于创建控件；这里使用WM_TIMER，是用了修改进度值。WM_NOTIFY消息用来处理
EXIT按钮消息。使用WM_CTLCOLOR消息来改变控件的外观颜色。下面介绍一个新的消息类型：

WM_CLOSE消息：之前讲过，当用户按下EXIT按钮后，会调用PostCloseMessage发送关闭主窗口消息，这个消息就是WM_CLOSE。默认情况下，是执行emXGUI的关闭操作，这样就会导致进度条的进度值没有清零，计数依然从上一次的计数值开始。所以我需要在关闭主窗口之前做清零操作。利用窗口
关闭时，会接收到WM_CLOSE消息。在该消息中，对变量进行清零。

进度条配置结构体
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

emXGUI使用PROGRESSBAR_CFG结构体来管理进度条。创建进度条完成后，需要发送PBM_SET_CFG消息，来初始化该结构体所有的参数。相关的成员变量，见 代码清单10_1_。

.. code-block:: c
    :caption: 代码清单 10_1 进度条配置结构体PROGRESSBAR_CFG（文件emXGUI.h）
    :linenos:
    :name: 代码清单10_1

<<<<<<< HEAD
     typedef struct{
     u16 cbSize; //结构体的大小
     u16 fMask; //功能选择
     u32 Rangle; //进度值的最大值
     u32 Value; //当前的进度值
     u32 TextFlag; //文字格式
     }PROGRESSBAR_CFG;
=======
    typedef struct{
        u16 cbSize;      //结构体的大小
        u16 fMask;       //功能选择
        u32 Rangle;      //进度值的最大值
        u32 Value;       //当前的进度值
        u32 TextFlag;    //文字格式
    }PROGRESSBAR_CFG;
>>>>>>> dev

1) cbSize：用来存放结构体的大小。用户提供的 PROGRESSBAR_CFG , 必须要将 cbSize 值设置成 sizeof(PROGRESSBAR_CFG)。

2) fMask：功能选择位。只有相应的 MASK 位置1，才会更新到 进度条控件的内部数据结构体。

3) Rangle：进度值的最大值。默认是100。

4) Value：当前的进度值。可以发送PBM_GET_VALUE，来获取当前的进度值。

5) TextFlag：文字格式。可以是DT_BOTTOM（垂直底部对齐）、DT_RIGHT（水平居右对齐）、DT_SINGLELINE（单行模式）等等。还有其他的参数，可以参考emXGUI.h的注释来使用。

创建进度条控件函数
^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c
    :caption: 代码清单 10_2 创建窗口函数（文件emXGUI.h）
    :linenos:
    :name: 代码清单10_2

<<<<<<< HEAD
     HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,
     U32 dwStyle, int x, int y, int nWidth, int nHeight,
     HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam);
=======
    HWND CreateWindowEx( U32 dwExStyle, LPCVOID lpClass, LPCWSTR lpWindowName,
            U32 dwStyle, int x, int y, int nWidth, int nHeight,
            HWND hwndParent, UINT WinId,HINSTANCE hInstance,LPVOID lpParam); 
>>>>>>> dev

1) lpClass：窗口类。进度条控件，这里选择PROGRESSBAR。

2) dwStyle：进度条的风格。进度条控件支持窗口风格参数，还可以使用以下参数：PBS_TEXT（显示文字）、PBS_3D（立体风格）、PBS_FLAT（平面风格）、PBS_ALIGN_LEFT（从左往右增长）、PBS_ALIGN_RIGHT（从右往左增长）、PBS_ALIGN_TOP（从上往下
增长）和PBS_ALIGN_BOTTOM（从下往上增长）

至于其他的参数，也是同样的用法，这里不作描述。我们创建控件调用的CreateWindow函数，实际上就是CreateWindowEx函数。

创建进度条控件实验
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. _设计要求-5:

设计要求
^^^^^^^^^^^^

图10_2_ 是本章节的设计要求，利用进度条实时显示进度条的进度值。下面看看，如何用代码实现该界面。

.. image:: /media/docx042.jpg
   :align: center
   :alt: 图 10‑2 设计要求
   :name: 图10_2

.. _代码分析-5:

代码分析
^^^^^^^^^^^^

(1) 创建父窗口

.. code-block:: c
    :caption: 代码清单 10‑3 GUI_DEMO_Progressbar函数（文件GUI_DEMO_Progressbar.c）
    :linenos:
    :name: 代码清单10_3

<<<<<<< HEAD
     void GUI_DEMO_Progressbar(void)
     {
     HWND hwnd;
     WNDCLASS wcex;
     MSG msg;
     ////第1部分：配置wcex参数。
     wcex.Tag = WNDCLASS_TAG;
     wcex.Style = CS_HREDRAW | CS_VREDRAW;
     wcex.lpfnWndProc = win_proc;

     wcex.cbClsExtra = 0;
     wcex.cbWndExtra = 0;
     wcex.hInstance = 0;//hInst;
     wcex.hIcon = 0;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);
     wcex.hCursor = 0;//LoadCursor(NULL, IDC_ARROW);
     //第2部分：创建主窗口
     hwnd =CreateWindowEx(NULL,
     &wcex,
     _T("GUI Demo - Progressbar"),
     WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,
     0,0,GUI_XSIZE,GUI_YSIZE,
     NULL,NULL,NULL,NULL);
     //第3部分：显示主窗口
     ShowWindow(hwnd,SW_SHOW);
     //窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。
     while(GetMessage(&msg,hwnd))
     {
     TranslateMessage(&msg);
     DispatchMessage(&msg);
     }
     }
=======
    void  GUI_DEMO_Progressbar(void)
    {
        HWND  hwnd;
        WNDCLASS  wcex;
        MSG msg;
        ////第1部分：配置wcex参数。
        wcex.Tag        = WNDCLASS_TAG;
        wcex.Style      = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc  = win_proc;
        wcex.cbClsExtra   = 0;
        wcex.cbWndExtra   = 0;
        wcex.hInstance    = 0;//hInst;
        wcex.hIcon      = 0;//LoadIcon(hInstance, (LPCTSTR)IDI_WIN32_APP_TEST);
        wcex.hCursor    = 0;//LoadCursor(NULL, IDC_ARROW);
        //第2部分：创建主窗口
        hwnd  =CreateWindowEx(NULL,
                    &wcex,
                    _T("GUI Demo - Progressbar"),
                    WS_CAPTION| WS_DLGFRAME| WS_BORDER| WS_CLIPCHILDREN,
                    0,0,GUI_XSIZE,GUI_YSIZE,
                    NULL,NULL,NULL,NULL);
        //第3部分：显示主窗口
        ShowWindow(hwnd,SW_SHOW);
        //窗口消息循环(窗口关闭并销毁时,GetMessage将返回FALSE,退出本消息循环)。   
        while(GetMessage(&msg,hwnd))
        {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        } 
    }
>>>>>>> dev

创建父窗口，标题栏为“GUI Demo - Progressbar”，带有大小边框，设置win_proc作为窗口回调函数。

(2) 窗口回调函数

1. WM_CREATE

.. code-block:: c
    :caption: 代码清单 10‑4 WM_CREATE消息响应（文件GUI_DEMO_Progressbar.c）
    :linenos:
    :name: 代码清单10_4

<<<<<<< HEAD
     case WM_CREATE:
     {
     GetClientRect(hwnd,&rc);
     if(1)
     {
     //PROGRESSBAR_CFG结构体的大小
     cfg.cbSize = sizeof(PROGRESSBAR_CFG);
     //开启所有的功能
     cfg.fMask = PB_CFG_ALL;

     //文字格式水平，垂直居中
     cfg.TextFlag = DT_VCENTER|DT_CENTER;
     // 创建自绘制的进度条VProgressbar
     wnd = CreateWindow(PROGRESSBAR,L"VProgressbar",
     WS_OWNERDRAW|PBS_ALIGN_BOTTOM|WS_VISIBLE,
     20,20,48,320,hwnd,ID_PROGBAR1,NULL,NULL);
     //初始化PROGRESSBAR_CFG结构体
     SendMessage(wnd,PBM_GET_CFG,TRUE,(LPARAM)&cfg);
     SendMessage(wnd,PBM_SET_CFG,TRUE,(LPARAM)&cfg);
     // 创建从右往左增长的进度条VProgressbar
     wnd = CreateWindow(PROGRESSBAR,L"PROGBAR2 & Right align",
     PBS_TEXT|PBS_ALIGN_RIGHT|WS_VISIBLE,
     100,100,280,48,hwnd,ID_PROGBAR2,NULL,NULL);
     SendMessage(wnd,PBM_GET_CFG,TRUE,(LPARAM)&cfg);
     SendMessage(wnd,PBM_SET_CFG,TRUE,(LPARAM)&cfg);
     //创建从左往右增长的进度条VProgressbar
     wnd = CreateWindow(PROGRESSBAR,L"PROGBAR3 & Left align",
     PBS_TEXT|PBS_ALIGN_LEFT|WS_VISIBLE,
     100,200,280,48,hwnd,ID_PROGBAR3,NULL,NULL);
     SendMessage(wnd,PBM_GET_CFG,TRUE,(LPARAM)&cfg);
     SendMessage(wnd,PBM_SET_CFG,TRUE,(LPARAM)&cfg);
     }
     //创建EXIT按钮
     CreateWindow(BUTTON,L"EXIT",WS_VISIBLE,rc.w-100,8,80,48,hwnd,ID_EXIT,NULL,NULL);
     //创建200ms定时器
     SetTimer(hwnd,1,200,TMR_START,NULL);
     return TRUE;
     }
=======
    case WM_CREATE:
    {     
        GetClientRect(hwnd,&rc);  
        if(1)
        {
            //PROGRESSBAR_CFG结构体的大小
            cfg.cbSize   = sizeof(PROGRESSBAR_CFG);
            //开启所有的功能
            cfg.fMask    = PB_CFG_ALL;
            //文字格式水平，垂直居中
            cfg.TextFlag = DT_VCENTER|DT_CENTER;  
            // 创建自绘制的进度条VProgressbar
            wnd = CreateWindow(PROGRESSBAR,L"VProgressbar",
                    WS_OWNERDRAW|PBS_ALIGN_BOTTOM|WS_VISIBLE,
                    20,20,48,320,hwnd,ID_PROGBAR1,NULL,NULL);
            //初始化PROGRESSBAR_CFG结构体
            SendMessage(wnd,PBM_GET_CFG,TRUE,(LPARAM)&cfg);
            SendMessage(wnd,PBM_SET_CFG,TRUE,(LPARAM)&cfg);
            // 创建从右往左增长的进度条VProgressbar
            wnd = CreateWindow(PROGRESSBAR,L"PROGBAR2 & Right align",
                    PBS_TEXT|PBS_ALIGN_RIGHT|WS_VISIBLE,
                    100,100,280,48,hwnd,ID_PROGBAR2,NULL,NULL);
            SendMessage(wnd,PBM_GET_CFG,TRUE,(LPARAM)&cfg);
            SendMessage(wnd,PBM_SET_CFG,TRUE,(LPARAM)&cfg);
            //创建从左往右增长的进度条VProgressbar
            wnd = CreateWindow(PROGRESSBAR,L"PROGBAR3 & Left align",
                    PBS_TEXT|PBS_ALIGN_LEFT|WS_VISIBLE,
                    100,200,280,48,hwnd,ID_PROGBAR3,NULL,NULL);
            SendMessage(wnd,PBM_GET_CFG,TRUE,(LPARAM)&cfg);
            SendMessage(wnd,PBM_SET_CFG,TRUE,(LPARAM)&cfg);
        }
        //创建EXIT按钮
        CreateWindow(BUTTON,L"EXIT",WS_VISIBLE,rc.w-100,8,80,48,hwnd,ID_EXIT,NULL,NULL);
        //创建200ms定时器
        SetTimer(hwnd,1,200,TMR_START,NULL);
        return TRUE;
    }
>>>>>>> dev

调用CreateWindow函数创建进度条控件，发送PBM_SET_CFG消息来配置进度条。cbSize的值必须为sizeof(PROGRESSBAR_CFG)。创建EXIT按钮，用来关闭窗口以及创建200ms定时器。

2. WM_TIMER

.. code-block:: c
    :caption: 代码清单 10‑5 WM_TIMER消息响应（文件GUI_DEMO_Progressbar.c）
    :linenos:
    :name: 代码清单10_5

<<<<<<< HEAD
     case WM_TIMER:
     {
     pb1_val +=1;
     if(pb1_val > 100)
     {
     pb1_val =0;
     }
     wnd =GetDlgItem(hwnd,ID_PROGBAR1);
     //设置进度值

     SendMessage(wnd,PBM_SET_VALUE,TRUE,pb1_val);
     pb2_val +=2;
     if(pb2_val > 100)
     {
     pb2_val =0;
     }
     //获取窗口句柄
     wnd =GetDlgItem(hwnd,ID_PROGBAR2);
     SendMessage(wnd,PBM_SET_VALUE,TRUE,pb2_val);

     wnd =GetDlgItem(hwnd,ID_PROGBAR3);
     SendMessage(wnd,PBM_SET_VALUE,TRUE,pb2_val);
     return TRUE;
     }
=======
    case WM_TIMER:
    {
        pb1_val +=1;
        if(pb1_val > 100)
        {
            pb1_val =0;
        }
        wnd =GetDlgItem(hwnd,ID_PROGBAR1);
        //设置进度值
        SendMessage(wnd,PBM_SET_VALUE,TRUE,pb1_val);
        pb2_val +=2;
        if(pb2_val > 100)
        {
            pb2_val =0;
        }
        //获取窗口句柄
        wnd =GetDlgItem(hwnd,ID_PROGBAR2);
        SendMessage(wnd,PBM_SET_VALUE,TRUE,pb2_val);
        
        wnd =GetDlgItem(hwnd,ID_PROGBAR3);
        SendMessage(wnd,PBM_SET_VALUE,TRUE,pb2_val);
        return TRUE;
    }
>>>>>>> dev

每当200ms计时结束时，就会将pb1_val值加1，pb2_val的值加2。调用GetDlgItem获取进度条控件的窗口句柄，同时将进度值发送给窗口，来实现实时更新进度条的进度值。

3. WM_CLOSE

.. code-block:: c
    :caption: 代码清单 10‑6 WM\_ CLOSE消息响应（文件GUI_DEMO_Progressbar.c）
    :linenos:
    :name: 代码清单10_6

     case WM_CLOSE:
     {
<<<<<<< HEAD
     pb1_val=0;
     pb2_val=0;
     break;
=======
        pb1_val=0;
        pb2_val=0;
        break;
>>>>>>> dev
     }

在WM_CLOSE中，对两个变量的值进行清零操作。

4. WM_CTLCOLOR

.. code-block:: c
    :caption: 代码清单 10‑7 WM\_ CTLCOLOR消息响应（文件GUI_DEMO_Progressbar.c）
    :linenos:
    :name: 代码清单10_7

     case WM_CTLCOLOR:
     {
<<<<<<< HEAD
     u16 id;
     CTLCOLOR *cr;

     id =wParam;
     cr =(CTLCOLOR*)lParam;
     if(id==ID_PROGBAR3)
     {

     cr->TextColor =RGB888(250,250,250);
     cr->BackColor =RGB888(0,0,0);
     cr->BorderColor =RGB888(130,30,130);
     cr->ForeColor =RGB888(200,0,200);
     return TRUE;
     }
     return FALSE;
=======
        u16 id;
        CTLCOLOR *cr;

        id =wParam;
        cr =(CTLCOLOR*)lParam;
        if(id==ID_PROGBAR3)
        {
            cr->TextColor =RGB888(250,250,250);
            cr->BackColor =RGB888(0,0,0);
            cr->BorderColor =RGB888(130,30,130);
            cr->ForeColor =RGB888(200,0,200);
            return TRUE;
        }
        return FALSE;
>>>>>>> dev
     }

在WM_CTLCOLOR消息中，改变进度条控件PROGBAR3 的外观颜色。

5. WM_NOTIFY

.. code-block:: c
    :caption: 代码清单 10‑8 WM\_ NOTIFY消息响应（文件GUI_DEMO_Progressbar.c）
    :linenos:
    :name: 代码清单10_8

     case WM_NOTIFY:
     {
<<<<<<< HEAD
     u16 code,id;
     id =LOWORD(wParam);
     code=HIWORD(wParam);
     if(id== ID_EXIT && code==BN_CLICKED)
     { // EXIT按钮弹起
     PostCloseMessage(hwnd); //产生WM_CLOSE消息关闭主窗口
     }
=======
        u16 code,id;
        id =LOWORD(wParam);
        code=HIWORD(wParam);
        if(id== ID_EXIT && code==BN_CLICKED)
        { // EXIT按钮弹起
        PostCloseMessage(hwnd); //产生WM_CLOSE消息关闭主窗口
        }
>>>>>>> dev
     }

按下EXIT按键，产生WM_CLOSE消息关闭主窗口。

6. WM_DRAWITEM

.. code-block:: c
    :caption: 代码清单 10‑9 WM_DRAWITEM消息响应（文件GUI_DEMO_Progressbar.c）
    :linenos:
    :name: 代码清单10_9

     case WM_DRAWITEM:
     {
<<<<<<< HEAD
     DRAWITEM_HDR *ds;

     ds =(DRAWITEM_HDR*)lParam;
     progressbar_owner_draw(ds);
     return TRUE;
=======
        DRAWITEM_HDR *ds;

        ds =(DRAWITEM_HDR*)lParam;
        progressbar_owner_draw(ds);
        return TRUE;
>>>>>>> dev
     }

进度条控件PROGBAR1拥有自定义绘制属性WS_OWNERDRAW，在绘制前都会给父窗口发送WM_DRAWITEM消息。在WM_DRAWITEM消息中，调用函数progressbar_owner_draw实现控件自定义，最后返回TURE。这里必须返回TURE，否则会按照默认方案进行配置。

.. code-block:: c
    :caption: 代码清单 10‑10 progressbar_owner_draw函数（文件GUI_DEMO_Progressbar.c）
    :linenos:
    :name: 代码清单10_10

<<<<<<< HEAD
     static void progressbar_owner_draw(DRAWITEM_HDR *ds)
     {
     HWND hwnd;
     HDC hdc;
     RECT rc,m_rc[2];
     // int range,val;
     WCHAR wbuf[128];
     PROGRESSBAR_CFG cfg;
     hwnd =ds->hwnd;
     hdc =ds->hDC;
     /* 第一步 */
     //获取客户区矩形位置，大小
     GetClientRect(hwnd,&rc);
     //设置进度条的背景颜色
     SetBrushColor(hdc,MapRGB(hdc,150,200,250));
     //填充进度条的背景
     FillRect(hdc,&ds->rc);
     //绘制进度条的背景边框
     DrawRect(hdc,&rc);
     /* 第二步 */
     cfg.cbSize =sizeof(cfg);
     cfg.fMask =PB_CFG_ALL;
     SendMessage(hwnd,PBM_GET_CFG,0,(LPARAM)&cfg);
     //生成进度条矩形
     MakeProgressRect(m_rc,&rc,cfg.Rangle,cfg.Value,PB_ORG_BOTTOM);
     //设置进度条的颜色
     SetBrushColor(hdc,MapRGB(hdc,250,10,10));
     //填充进度条
     FillRoundRect(hdc,&m_rc[0],2);
     //设置画笔颜色
     SetPenColor(hdc,MapRGB(hdc,100,10,10));
     //绘制进度条的边框，采用圆角边框
     DrawRoundRect(hdc,&m_rc[0],2);
     /* 显示进度值 */
     x_wsprintf(wbuf,L"%d",cfg.Value);
     //InflateRect(&rc,40,0);
     DrawText(hdc,wbuf,-1,&rc,DT_VCENTER|DT_CENTER);
     }
=======
    static void progressbar_owner_draw(DRAWITEM_HDR *ds)
    {
        HWND hwnd;
        HDC hdc;
        RECT rc,m_rc[2];
        // int range,val;
        WCHAR wbuf[128];
        PROGRESSBAR_CFG cfg;
        hwnd =ds->hwnd;
        hdc =ds->hDC;
        /* 第一步 */
        //获取客户区矩形位置，大小
        GetClientRect(hwnd,&rc);
        //设置进度条的背景颜色
        SetBrushColor(hdc,MapRGB(hdc,150,200,250));
        //填充进度条的背景
        FillRect(hdc,&ds->rc);
        //绘制进度条的背景边框
        DrawRect(hdc,&rc);
        /* 第二步 */
        cfg.cbSize =sizeof(cfg);
        cfg.fMask =PB_CFG_ALL;
        SendMessage(hwnd,PBM_GET_CFG,0,(LPARAM)&cfg);
        //生成进度条矩形
        MakeProgressRect(m_rc,&rc,cfg.Rangle,cfg.Value,PB_ORG_BOTTOM);
        //设置进度条的颜色
        SetBrushColor(hdc,MapRGB(hdc,250,10,10));
        //填充进度条
        FillRoundRect(hdc,&m_rc[0],2);
        //设置画笔颜色
        SetPenColor(hdc,MapRGB(hdc,100,10,10));
        //绘制进度条的边框，采用圆角边框
        DrawRoundRect(hdc,&m_rc[0],2);
        /* 显示进度值 */
        x_wsprintf(wbuf,L"%d",cfg.Value);
        //InflateRect(&rc,40,0);
        DrawText(hdc,wbuf,-1,&rc,DT_VCENTER|DT_CENTER);
    }
>>>>>>> dev

进度条，其实是由两个部分构成，如 图10_3_ ，是进度度条的背景，是已经完成的进度。只要我们可以绘制这样的两个矩形，同时将它俩叠加到一块的话，就可以得到处的进度条了。

.. image:: /media/docx043.jpg
   :align: center
   :alt: 图 10‑3 原理绘制原理
   :name: 图10_3

图 10‑3 原理绘制原理

代码清单10_10_ 中的第一步，就是绘制一个处的矩形框框。调用GetClientRect函数获取子控件的位置，大小。使用SetBrushColor和SetPenColor来设置背景和边框的颜色，最后调用FillRect和DrawRect来绘制成。

代码清单10_10_ 中的第二步，对应上图的处。发送消息PBM_GET_CFG，来获得进度条的配置参数，主要是当前的进度值。发送消息前，必须要将cbSize值设置成
sizeof(PROGRESSBAR_CFG)，同时将fMask设置为PB_CFG_ALL，才可以得到正确的参数值。调用MakeProgressRect函数，最终输出时，m_rc[0]为已完成的进度矩形 。调用SetBrushColor、FillRoundRect和DrawRoundRect来绘制的
矩形。处的叠加过程，实际上在调用MakeProgressRect函数的时候，就已经完成了。因为MakeProgressRect函数的第二个参数的作用是，使输出m_rc的矩形位置和大小限定在控件的范围中。关于MakeProgressRect函数的具体说明，请参考《emXGUI
API编程手册》的章节：位置及区域操作运算API。

最后，将GUI_DEMO_Progressbar加入到GUI_AppMain中，见 代码清单10_11_。

.. code-block:: c
    :caption: 代码清单 10‑11 GUI_AppMain函数（文件GUI_AppMain.c）
    :linenos:
    :name: 代码清单10_11

     void GUI_AppMain(void)
     {
<<<<<<< HEAD
     while(1)
     {
     GUI_DEMO_Hello();
     GUI_DEMO_Button();
     GUI_DEMO_Checkbox();
     GUI_DEMO_Radiobox();
     GUI_DEMO_Textbox();

     GUI_DEMO_Progressbar();

     }
=======
        while(1)
        {
            GUI_DEMO_Hello();
            GUI_DEMO_Button();
            GUI_DEMO_Checkbox();
            GUI_DEMO_Radiobox();
            GUI_DEMO_Textbox();

            GUI_DEMO_Progressbar();
        }
>>>>>>> dev
     }

.. _实验现象-5:

实验现象
^^^^^^^^^^^^

实验结果，如图 10‑4所示。最左边的是PROGBAR1，是在progressbar_owner_draw函数绘制的进度条。PROGBAR2和PROGBAR3是系统自带的进度条，它们的增长方式相反，同时我们还通过WM_CTLCOLOR消息改变了PROGBAR3的外观颜色。

.. image:: /media/docx044.jpg
   :align: center
   :alt: 图 10‑4 实验结果
   :name: 图10_4
