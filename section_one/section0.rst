.. vim: syntax=rst

前言
----

如何学习本书
~~~~~~~~~~~~~~

本书是首本系统讲解emXGUI应用的中文书籍，共分为两个部分，第一部分为“emXGUI控件应用开发”，即重点讲解emXGUI的每个控件如何使用，并将控件的显示效果在野火STM32开发板上面的液晶显示出来，让你有客观的视觉感受，而不单单是停留在代码层面。

第二部分是综合例程实战，即在第一部分学会了如何使用emXGUI控件的基础上，利用这些控件制作各种界面，控制开发板上面的外设，比如制作音乐播放器、视频播放器、万年历和图片浏览器等具有实际项目意义的实战例程。

由于第一部分是第二部分的基础，所以学习的时候，必须先学习第一部分，然后再学习第二部分，不能进行跳跃式的阅读。如果第一部分的知识没有掌握好，贸贸然就进入第二部分的实战，出现问题了，定会让你焦头烂额，正所谓基础不牢，地动山摇。

本书的参考资料
~~~~~~~~~~~~~~

1. emXGUI 官方作者刘巍手把手指导

2. emXGUI API编程手册（电子版）

3. 《STM32库开发实战指南》（电子版）

本书的配套硬件
~~~~~~~~~~~~~~

本书支持野火STM32开发板全套系列，具体型号见表格 表0-1_，具体图片见 图0-1_、图0-2_、图0-3_、图0-4_ 和 图0-5_ 。
学习的时候如果配套这些硬件平台做实验，学习必会达到事半功倍的效果，可以省去中间硬件不一样时移植遇到的各种问题。

.. list-table:: 表格 0‑1 野火STM32开发板型号汇总.
    :widths: auto
    :header-rows: 1
    :name: 表0-1

    * - 型号
      - 区别
      - \
      - \
      - \
    * - \
      - 内核
      - 引脚
      - RAM
      - ROM
    * - MINI
      - Cortex-M3
      - 64
      - 48KB
      - 256KB
    * - 指南者
      - Cortex-M3
      - 100
      - 64KB
      - 512KB
    * - 霸道
      - Cortex-M3
      - 144
      - 64KB
      - 512KB
    * - 霸天虎
      - Cortex-M4
      - 144
      - 192KB
      - 1MB
    * - 挑战者
      - Cortex-M4
      - 176
      - 256KB
      - 1MB

.. image:: /media/docx002.png
   :align: center
   :alt: 图 0‑1 野火【MINI】STM32F103RCT6 开发板
   :name: 图0-1

野火【MINI】STM32F103RCT6 开发板

.. image:: /media/docx003.png
   :align: center
   :alt: 图 0‑2 野火【指南者】STM32F103VET6 开发板
   :name: 图0-2

野火【指南者】STM32F103VET6 开发板

.. image:: /media/docx004.png
   :align: center
   :alt: 图 0‑3 野火【霸道】STM32F103ZET6 开发板
   :name: 图0-3

野火【霸道】STM32F103ZET6 开发板

.. image:: /media/docx005.png
   :align: center
   :alt: 图 0‑4 野火【霸天虎】STM32F407ZGT6 开发板
   :name: 图0-4

野火【霸天虎】STM32F407ZGT6 开发板

.. image:: /media/docx006.png
   :align: center
   :alt: 图 0‑5 野火【挑战者】STM32F429IGT6 开发板
   :name: 图0-5

野火【挑战者】STM32F429IGT6 开发板

本书的技术论坛
~~~~~~~~~~~~~~

如果在学习过程中遇到问题，可以到野火电子论坛emXGUI专区： `http://www.firebbs.cn/forum.php?mod=forumdisplay&fid=149\ 发帖交流 <http://www.firebbs.cn>`__ ，开源共享，共同进步。

鉴于水平有限，本书难免有纰漏，热心的读者也可把勘误发到论坛好让我们改进做得更好，祝您学习愉快，emXGUI的世界，野火与您同行。
