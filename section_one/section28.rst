.. vim: syntax=rst

显示矢量字体
------------

矢量字体(Vector font)的每一个字是通过数学关系来描述的，因此字体可以任意缩放而不变形、变色。矢量字体文件的后缀为.ttf，我们制作字库章节选择文件就是矢量字体。还有一种叫点阵字体，后缀是.fon，这种字体并不是以矢量描述的，放大以后会出现锯齿，如 图28_1_。

.. image:: /media/docx153.jpg
   :align: center
   :alt: 图 28‑1 点阵字体与矢量字体
   :name: 图28_1

图 28‑1 点阵字体与矢量字体

我们以“火”字为例，给大家介绍一下，矢量字体的原理。

.. image:: /media/docx154.jpg
   :align: center
   :alt: 图 28‑2 “火”字
   :name: 图28_2

图 28‑2 “火”字

一个字可以使用多条线段来表示，对于这些线段，我们只需要保存它的端点值，如 图28_2_ 的白色空心圆所示，当我们想要显示某个字时，就取出这些关键点，通过贝塞尔曲线将这些点的坐标连接起来，最后进行填充。放大或缩小字体的时候，只需要按比例缩放改变这些端点值的相对位置就可以了。

前面我们提到在TTF文件中，每个字符都是以一系列的点存放的，其中有一些点是控制点，利用这些控制点来实现绘制抛物线的功能，如 图28_3_ 所示，p1是控制点，c1、c2是曲线的端点，因此曲线可以用下面的公式进行描述，这描述方式就是贝塞尔曲线。

:math:`p\left( t \right) = \ \left( 1 - t \right)^{2}p_{0}\  + \ 2t\left( 1 - t \right)p_{1}\  + \ t^{2}p_{2}\ ` （0 < t < 1 ）

.. image:: /media/docx155.jpg
   :align: center
   :alt: 图 28‑3 点绘制线
   :name: 图28_3

图 28‑3 点绘制线

回过头，看 图28_4_，方框处是不是和上面说的原理是一样的，空心的点是线段的端点，实心的点是控制点，利用贝塞尔曲线，描绘出字体的轮廓，最后在进行黑色填充，就完成了。

.. image:: /media/docx156.jpeg
   :align: center
   :alt: 图 28‑4 “火”
   :name: 图28_4

图 28‑4 “火”

TTF文件格式
~~~~~~~~~~~~~~

上面就是有关矢量字体是如何实现的。下面我们看一下ttf的文件内容，使用WinHex软件打开某个ttf文件，如图所示。

.. image:: /media/docx157.jpg
   :align: center
   :alt: 图 28‑5 文件内容
   :name: 图28_5

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
^^^^^^^^

字体目录，是字体文件的第一个表，提供访问其他表中所需的信息。该目录由两部分组成：偏移子表和表目录。偏移子表记录字体中表的数量，并提供偏移信息，以便快速访问目录表。表目录由一系列表组成，每个表对应一个字体。


字体目录TableDirectory的c语言定义，见 代码清单28_1_ 。

.. code-block:: c
    :caption: 代码清单 28‑1 TableDirectory结构体
    :linenos:
    :name: 代码清单28_1

     typedef struct
     {
         Fixed sfntversion; //字体格式的版本号
         USHORT numTables; //表的数目
         USHORT searchRange; //快速搜索的范围
         USHORT entrySelector; //搜索循环迭代次数
         USHORT rangeShift; //范围偏移量
         TableEntry entries[1];//数据表
     }TableDirectory;

1) sfntversion：该参数用来确定从字体中提取字体的轮廓，对于矢量字体，在Windows操作系统下， 其值必须为0x00010000。

2) numTables：记录了表的个数；

3) searchRange：记录快速搜索的范围，起始位置为表的开头；

4) entrySelector：记录循环迭代的次数，即经过多少次循环后，可以将目标表项所在范围缩小二分之一。

5) rangeShift：快速搜索范围的偏移量，其值等于表的个数numTables减去快速搜索的范围值searchRange。

以上成员都是属于偏移子表的内容，假设某个TTF文件它共有800个表，searchRange的值为500，那么rangeShift的值等于300。当我们搜索某一个目标表项时，如果它的值小于300，就从表的开头开始搜索。它大于300，则直接从rangeShift处开始搜索。

6) entries：可变长度的TableEntry类型结构的数组，用于存放各种数据表，组成表目录，目录中的条目必须按标签按升序排序。见 代码清单28_2_。

.. code-block:: c
    :caption: 代码清单 28‑2 TableEntry结构体
    :linenos:
    :name: 代码清单28_2

     typedef sturct
     {
         char tag[4];
         ULONG checkSum;
         ULONG offset;
         ULONG length;
     }TableEntry;

1) tag：4个字节标识符，用来说明资源的类型；

2) checkSum：该表的校验和；

3) offset：偏移量；

4) length：该表的长度，以字节为单位。

TTF文件子表
^^^^^^^^^^^^^^

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

                                -1：从右到左 INT16        indexToLocFormat   代表loca表的索引中使用的偏移格式的类型，0 为short型, 1为long型 INT16        glyphDataFormat    字形数据格式 
============ ================== ============================================================================

head表记录了字体版本号，创建和修改日期，修订号以及适用于整个字体的基本印刷数据等信息。xMin，yMin，xMax和yMax指定一个矩形EM，EM是字体设计者假想的矩形，是字体中所有字形的边界框。

2. cmap

camp表将字符编码（如Unicode编码）相应地转换为内部的字符ID。微软和MAC使用不同的编码，因此，camp表可以有多个映射表，每个映射表支持一种编码方案，图28_6_，是cmap表的部分内容。

.. image:: /media/docx158.jpg
   :align: center
   :alt: 图 28‑6 cmap表
   :name: 图28_6

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

注：我们常用的emoji表情实际就是一种Unicode变体序列，它是由一个基准字符加256 个变体选择符组成，如 图28_7_ emoji编码。

.. image:: /media/docx159.jpg
   :align: center
   :alt: 图 28‑7 emoji编码
   :name: 图28_7

图 28‑7 emoji编码

‘cmap’子表有九种可用的格式：格式0，格式2，格式4，格式6，格式8.0，格式10.0，格式12.0，格式13.0和格式14。

格式0用于支持MAC设备的映射关系。格式2用于日语，中文和韩语的映射。 格式4用于16位映射。 
格式6用于十六进制16位映射。格式8，10和12，13和14支持使用Unicode 2.0及更高版本中的代理编码的文本。
以最简单的格式0为例，这里主要介绍一下映射关系，其他格式，感兴趣的话，可以查阅相关资料。

格式0主要用于字符编码和字形ID都是单个字节的字体，格式如 表格28_6_.

.. _表格28_6:

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

表格 28‑7 指定了简单字形的格式。其中flag参数如 表格28_8_。

.. _表格28_8:

表格 28‑8 flag组参数

==========  ==============  ======================================================================
位（bits）       标志                                        描述
==========  ==============  ======================================================================
0           曲线上的点      为1，则在曲线上；为0，则不在
1           X坐标的字节数   1——1个字节
\            \               0——2个字节
2           Y坐标的字节数   1——1个字节
 \           \                0——2个字节
3           重复次数        1——下一个字节指定重复该组标志的次数
4，5        X，Y的坐标长度  如果1（2）2位未设置，而4（5）位置1，则当前的x（y）坐标与前一个坐标相同
6，7        保留            设为0
==========  ==============  ======================================================================

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

.. image:: /media/docx160.jpg
   :align: center
   :alt: 图 28‑8 基准线
   :name: 图28_8

图 28‑8 基准线

5. hmtx

‘hmtx’表包含字体中每个字形的水平布局的度量信息，即前进宽度和左侧方位。从字形的当前点到最左边点的水平距离，称为左侧方位。在绘制字体时候，为了方便确定下一个字体的位置，使用前进宽度，即当前点移动的水平距离作为下个字体的起点。

表格 28‑10 hmtx表

===================  =============================  ============================================================================
       类型                      名称                                                   描述
===================  =============================  ============================================================================
longHorMetric结构体  hMetrics[numOfLongHorMetrics]  值numOfLongHorMetrics来自‘hhea’表。如果字体等宽，则numOfLongHorMetrics的值为
FWord                leftSideBearing[]              用于等宽字体，数组长度等于字形总数减去numOfLongHorMetrics
===================  =============================  ============================================================================

.. code-block:: c
    :caption: 代码清单 28‑3 longHorMetric结构体
    :linenos:
    :name: 代码清单28_3

     struct {
<<<<<<< HEAD
     uint16 advanceWidth;
     int16 leftSideBearing;

=======
          uint16 advanceWidth;
          int16 leftSideBearing;
>>>>>>> dev
     }

更改前进宽度，会改变每个字的间距，而改变左侧方位，则会改变单个字体的位置，相对于字体边界矩形而言，见 图28_9_。

.. image:: /media/docx161.jpg
   :align: center
   :alt: 图 28‑9 前进宽度与左侧方位
   :name: 图28_9

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

================ ==================== =======================================================================================================================================
类型              名称                 描述
================ ==================== =======================================================================================================================================
UINT16           版本号                 当前表版本号（设置为0）
INT16            xAvgCharWidth          小写字母和空格的平均加权前进宽度
UINT16           usWeightClass          字形中的笔画粗细\：
\                   \                   1——超细
\                   \                   2——特细
\                    \                  …
\                    \                  8——特粗体
\                    \                  9——超大体 
UINT16           usWidthClass           字体设计者为字体中的字形指定的正常宽高比（宽高比）的相对变化 
INT16            fsType                 字节的位段。目前只定义1位，其余位为0.
上下标的相关参数            \                 \                     
INT16            ySubscriptXSize        下标的推荐水平尺寸（以像素为单位） 
INT16            ySubscriptYSize        下标的建议垂直大小（以像素为单位） 
INT16            SubscriptXOffset       下标的推荐水平偏移量 
INT16            ySubscriptYOffset      建议的垂直偏移量构成下标的基线 
INT16            ySuperscriptXSize      上标的推荐水平尺寸（以像素为单位） 
INT16            ySuperscriptYSize      上标的建议垂直大小（以像素为单位） 
INT16            ySuperscriptXOffset    建议上标的水平偏移量 
INT16            ySuperscriptYOffset    建议垂直偏离基线的上标 删除线的相关参数 
int16            yStrikeoutSize         删除线的宽度 
INT16            yStrikeoutPosition     删除线与基准线的偏差 
INT16            sFamilyClass           字体所属分类 
PANOSE           panose                 变体 
UINT32           ulCharRange [4]        2位无符号长数组，被分成两个位字段，每个字段分别为96和32位。低96位用于指定字体文件包含的Unicode块，高32位用于指定字体文件所涵盖的字符集 
INT8             achVendID [4]           字体供应商的四个字符标识符 
UINT16           fsSelection            字节位字段，包含有关字体模式性质的信息，如斜体，删除线等 
UINT16           fsFirstCharIndex       此字体中的最小Unicode索引 
UINT16             fsLastCharIndex      此字体中的最大Unicode索引 
================ ==================== =======================================================================================================================================

显示字体API函数
~~~~~~~~~~~~~~~~~~

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
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

freetype_font_obj_new函数用来创建矢量字体对象，用来存放ttf文件的数据，函数原型见 代码清单28_4_。

.. code-block:: c
    :caption: 代码清单 28‑4 freetype_font_obj_new函数（文件GUI_Font_Freetype.h）
    :linenos:
    :name: 代码清单28_4

     freetype_obj* freetype_font_obj_new(int w,int h,int dpi_horz,int dpi_vert,const u8 *pFontData);

1) w，h：设置字体的宽度，高度；

2) dpi_horz、dpi_vert：垂直和水平的dpi。dpi指的是屏幕一英尺显示的像素点数。某个字体的宽度为72px，高度为72px，以英尺为单位，它的宽，高都等于1英尺。

3) pFontData：ttf文件数据，通常从外部设备读取。一般的ttf文件都是超过6M，F429的SDRAM共有8M，前2M用于LCD显示屏，因此选择字库文件时，要注意文件的大小。例程中使用的字体为方正兰亭超细黑简体，大小约为1.7M。

freetype_font_obj_delete
^^^^^^^^^^^^^^^^^^^^^^^^

freetype_font_obj_delete函数用于释放ttf文件数据所使用的内存空间。函数原型见 代码清单28_5_。

.. code-block:: c
    :caption: 代码清单 28‑5 freetype_font_obj_delete函数（文件GUI_Font_Freetype.h）
    :linenos:
    :name: 代码清单28_5

     void freetype_font_obj_delete(freetype_obj *ft_obj);

1) ft_obj：矢量字体对象

freetype_font_set_size
^^^^^^^^^^^^^^^^^^^^^^

freetype_font_set_size函数可以设置字体的显示大小，函数原型见 代码清单28_6_。

.. code-block:: c
    :caption: 代码清单 28‑6 freetype_font_set_size函数（文件GUI_Font_Freetype.h）
    :linenos:
    :name: 代码清单28_6

     BOOL freetype_font_set_size(freetype_obj *ft,int w,int h,int dpi_horz,int dpi_vert);

1) ft：矢量字体对象，该对象是由freetype_font_obj_new生成；

2) w、h：字体显示的宽度、高度；

3) dpi_horz、dpi_vert：设置垂直、水平dpi。

freetype_CreateFont
^^^^^^^^^^^^^^^^^^^

freetype_CreateFont函数用来创建字体句柄，该函数会返回HFONT类型的变量，函数原型，见 代码清单28_7_。

.. code-block:: c
    :caption: 代码清单 28‑7 freetype_CreateFont函数（文件GUI_Font_Freetype.h）
    :linenos:
    :name: 代码清单28_7

     HFONT freetype_CreateFont(freetype_obj *ft_obj);

1) ft_obj：矢量字体对象。

矢量字体实验
~~~~~~~~~~~~

.. _实验要求-3:

实验要求
^^^^^^^^^^^^

图 28‑10 实验要求是本章的实验要求，使用矢量字体，来显示文字。

.. image:: /media/docx162.jpg
   :align: center
   :alt: 图 28‑10 实验要求
   :name: 图28_10

图 28‑10 实验要求

.. _代码分析-23:

代码分析
^^^^^^^^^^^^

(1) 创建父窗口

.. code-block:: c
    :caption: 代码清单 28‑8 创建父窗口（文件GUI_DEMO_TTF.c）
    :linenos:
    :name: 代码清单28_8

     void GUI_DEMO_TTF(void)
     {
<<<<<<< HEAD
     HWND hwnd;
     WNDCLASS wcex;
     MSG msg;
     int fsize;
     FIL *file;
     FRESULT fresult;
     UINT br;


     /* 文件句柄空间 */
     file =(FIL*)GUI_VMEM_Alloc(sizeof(FIL));

     /* 打开文件 */
     fresult = f_open(file, filename, FA_OPEN_EXISTING | FA_READ );
     GUI_DEBUG("%d",fresult);
     fsize =f_size(file);
     font_data_buf =(u8*)GUI_VMEM_Alloc(fsize);

     if(font_data_buf!=NULL)
     {
     fresult = f_read(file,font_data_buf,fsize,&br); //将整个ttf文件读到内存
     }
     f_close(file);

     if(font_data_buf==NULL)
     { //内存不够
     MSGBOX_OPTIONS ops;
     const WCHAR *btn[]={L"确定"};
     int x,y,w,h;

     ops.Flag =MB_BTN_WIDTH(60)|MB_ICONERROR;
     ops.pButtonText =btn;
     ops.ButtonCount =1;
     w =300;
     h =250;
     x =(GUI_XSIZE-w)>>1;
     y =(GUI_YSIZE-h)>>1;
     MessageBox(hwnd,x,y,w,h,L"绯系统内存不足,\r\n请选择更小的字体文件...",L"消息",&ops);
     return;
     }

     wcex.Tag = WNDCLASS_TAG;
     wcex.Style = CS_HREDRAW | CS_VREDRAW;
     wcex.lpfnWndProc = WinProc; //设置主窗口消息处理的回调函数.
     wcex.cbClsExtra = 0;
     wcex.cbWndExtra = 0;
     wcex.hInstance = NULL;
     wcex.hIcon = NULL;
     wcex.hCursor = NULL;

     //创建主窗口
     hwnd =CreateWindowEx( WS_EX_LOCKPOS, //窗口不可拖动
     &wcex,
     L"emxGUI矢量显示示例" , //窗口名称
     WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,
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
     GUI_VMEM_Free(font_data_buf);
=======
          HWND hwnd;
          WNDCLASS wcex;
          MSG msg;
          int fsize;
          FIL *file;
          FRESULT fresult;
          UINT br;


          /* 文件句柄空间 */
          file =(FIL*)GUI_VMEM_Alloc(sizeof(FIL));

          /* 打开文件 */
          fresult = f_open(file, filename, FA_OPEN_EXISTING | FA_READ );
          GUI_DEBUG("%d",fresult);
          fsize =f_size(file);
          font_data_buf =(u8*)GUI_VMEM_Alloc(fsize);

          if(font_data_buf!=NULL)
          {
               fresult = f_read(file,font_data_buf,fsize,&br); //将整个ttf文件读到内存
          }
          f_close(file);

          if(font_data_buf==NULL)
          { //内存不够
               MSGBOX_OPTIONS ops;
               const WCHAR *btn[]={L"确定"};
               int x,y,w,h;

               ops.Flag =MB_BTN_WIDTH(60)|MB_ICONERROR;
               ops.pButtonText =btn;
               ops.ButtonCount =1;
               w =300;
               h =250;
               x =(GUI_XSIZE-w)>>1;
               y =(GUI_YSIZE-h)>>1;
               MessageBox(hwnd,x,y,w,h,L"绯系统内存不足,\r\n请选择更小的字体文件...",L"消息",&ops);
               return;
          }

          wcex.Tag = WNDCLASS_TAG;
          wcex.Style = CS_HREDRAW | CS_VREDRAW;
          wcex.lpfnWndProc = WinProc; //设置主窗口消息处理的回调函数.
          wcex.cbClsExtra = 0;
          wcex.cbWndExtra = 0;
          wcex.hInstance = NULL;
          wcex.hIcon = NULL;
          wcex.hCursor = NULL;

          //创建主窗口
          hwnd =CreateWindowEx( WS_EX_LOCKPOS, //窗口不可拖动
          &wcex,
          L"emxGUI矢量显示示例" , //窗口名称
          WS_CAPTION|WS_DLGFRAME|WS_BORDER|WS_CLIPCHILDREN,
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
          GUI_VMEM_Free(font_data_buf);
>>>>>>> dev
     }

在创建窗口前，调用f_open函数打开文件FZLTCXHJW.TTF，获取文件句柄，通过f_size函数得到文件的大小，同时调用GUI_VMEM_Alloc函数为字库文件数据分配空间，大小为FZLTCXHJW.TTF的大小fsize。使用f_read函数，将整个ttf文件读到内存中。
这里的内存指的是SDRAM，我们前面提到过，这个字库文件如果太大的话，会导致读取失败，这里使用一个消息框MessageBox，来通知用户。最后，使用f_close函数关闭文件。

这样，我们就完成了加载ttf文件过程。

(2) 窗口回调函数

-  WM_CREATE

<<<<<<< HEAD
.. image:: /media/docx153.jpg
   :align: center
   :alt: 代码清单 28‑9 WM_CREATE消息（文件GUI_DEMO_TTF.c）
   :name: 图28_9

     case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口.
     {
     GetClientRect(hwnd,&rc); ////获得窗口的客户区矩形.
     ft_obj =freetype_font_obj_new(16,16,72,72,font_data_buf); //创建一个freetype对象
     CreateWindow(BUTTON,L"OK",WS_VISIBLE,
     rc.w-80,8,68,32,hwnd,ID_OK,NULL,NULL); //创建一个按钮(示例).
     return TRUE;
=======
.. code-block:: c
   :caption: 代码清单 28‑9 WM_CREATE消息（文件GUI_DEMO_TTF.c）

     case WM_CREATE: //窗口创建时,会自动产生该消息,在这里做一些初始化的操作或创建子窗口.
     {
          GetClientRect(hwnd,&rc); ////获得窗口的客户区矩形.
          ft_obj =freetype_font_obj_new(16,16,72,72,font_data_buf); //创建一个freetype对象
          CreateWindow(BUTTON,L"OK",WS_VISIBLE,
          rc.w-80,8,68,32,hwnd,ID_OK,NULL,NULL); //创建一个按钮(示例).
          return TRUE;
>>>>>>> dev
     }

调用freetype_font_obj_new函数，来创建矢量字体对象。font_data_buf数组存放着字库文件的数据，这样之后，有个矢量字体的操作，都可以是该对象ft_obj。

-  WM_PAINT

<<<<<<< HEAD
.. image:: /media/docx153.jpg
   :align: center
   :alt: 代码清单 28‑10 WM_PAINT（文件GUI_DEMO_TTF.c）
   :name: 图28_10

     case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
     {
     PAINTSTRUCT ps;
     HDC hdc;
     HFONT hFont;
     RECT rc0;

     GetClientRect(hwnd,&rc0);


     hdc =BeginPaint(hwnd,&ps); //开始绘图

     ////用户的绘制内容...

     hFont =freetype_CreateFont(ft_obj); //创建freetype字体

     SetFont(hdc,hFont); //设置新的字体.

     SetTextColor(hdc,MapRGB(hdc,10,10,10));

     freetype_font_set_size(ft_obj,16,16,72,72); //设置freetype字体的大小参数
     TextOut(hdc,10,10,L"矢量字体示例1234567890",-1);
     SetTextColor(hdc,MapRGB(hdc,250,0,10));
     freetype_font_set_size(ft_obj,32,32,72,72);
     TextOut(hdc,10,30,L"矢量字体示例1234567890",-1);
     SetTextColor(hdc,MapRGB(hdc,0,0,205));
     freetype_font_set_size(ft_obj,64,64,72,72);
     TextOut(hdc,10,80,L"矢量字体示例1234567890",-1);
     SetTextColor(hdc,MapRGB(hdc, 255,255,255));
     freetype_font_set_size(ft_obj,128,128,72,72);
     TextOut(hdc,10,200,L"矢量字体示例1234567890",-1);



     SetTextColor(hdc,MapRGB(hdc,200,50,50));
     freetype_font_set_size(ft_obj,40,40,72,72);

     rc.w =rc0.w;
     rc.h =48;
     rc.x =0;
     rc.y =rc0.h-48;
     DrawText(hdc,L"emXGUI,十年深度优化图像引擎",-1,&rc,DT_VCENTER|DT_RIGHT|DT_BORDER);

     DeleteFont(hFont); //释放字体
     EndPaint(hwnd,&ps); //结束绘图
     break;
=======
.. code-block:: c
   :caption: 代码清单 28‑10 WM_PAINT（文件GUI_DEMO_TTF.c）

     case WM_PAINT: //窗口需要绘制时，会自动产生该消息.
     {
          PAINTSTRUCT ps;
          HDC hdc;
          HFONT hFont;
          RECT rc0;

          GetClientRect(hwnd,&rc0);


          hdc =BeginPaint(hwnd,&ps); //开始绘图

          ////用户的绘制内容...

          hFont =freetype_CreateFont(ft_obj); //创建freetype字体

          SetFont(hdc,hFont); //设置新的字体.

          SetTextColor(hdc,MapRGB(hdc,10,10,10));

          freetype_font_set_size(ft_obj,16,16,72,72); //设置freetype字体的大小参数
          TextOut(hdc,10,10,L"矢量字体示例1234567890",-1);
          SetTextColor(hdc,MapRGB(hdc,250,0,10));
          freetype_font_set_size(ft_obj,32,32,72,72);
          TextOut(hdc,10,30,L"矢量字体示例1234567890",-1);
          SetTextColor(hdc,MapRGB(hdc,0,0,205));
          freetype_font_set_size(ft_obj,64,64,72,72);
          TextOut(hdc,10,80,L"矢量字体示例1234567890",-1);
          SetTextColor(hdc,MapRGB(hdc, 255,255,255));
          freetype_font_set_size(ft_obj,128,128,72,72);
          TextOut(hdc,10,200,L"矢量字体示例1234567890",-1);

          SetTextColor(hdc,MapRGB(hdc,200,50,50));
          freetype_font_set_size(ft_obj,40,40,72,72);

          rc.w =rc0.w;
          rc.h =48;
          rc.x =0;
          rc.y =rc0.h-48;
          DrawText(hdc,L"emXGUI,十年深度优化图像引擎",-1,&rc,DT_VCENTER|DT_RIGHT|DT_BORDER);

          DeleteFont(hFont); //释放字体
          EndPaint(hwnd,&ps); //结束绘图
          break;
>>>>>>> dev
     }

调用BeginPaint函数开始绘制，我们先调用freetype_CreateFont函数来创建字体句柄h
Font。在WM_CREATE消息中，创建矢量字体对象ft_obj指的是字体的数据，freetype_CreateFont函数则是利用这字体数据来创建字体句柄，这样我们才可以在emXGUI中使用。

调用SetFont函数，来设置字体为矢量字体。字体的大小可以通过freetype_font_set_size函数来修改，字体的颜色同样受TextColor的控制。显示文字，我们可以使用TextOut函数来实现。最后，调用EndPaint函数结束绘制，同时释放字体句柄。

-  WM_CLOSE

退出窗口时，需要调用函数freetype_font_obj_delete来释放矢量字体对象，如代码清单 28‑11。

.. code-block:: c
    :caption: 代码清单 28‑11 WM_CLOSE消息
    :linenos:
    :name: 代码清单28_11

     case WM_CLOSE: //窗口关闭时，会自动产生该消息.
     {
<<<<<<< HEAD
     freetype_font_obj_delete(ft_obj); //释放freetype对象
     return DestroyWindow(hwnd); //调用DestroyWindow函数销毁窗口，该函数会使主窗口结束并退出消息循环;

=======
          freetype_font_obj_delete(ft_obj); //释放freetype对象
          return DestroyWindow(hwnd); //调用DestroyWindow函数销毁窗口，该函数会使主窗口结束并退出消息循环;
>>>>>>> dev
     }

.. _实验结果-14:

实验结果
^^^^^^^^^^^^

实验结果如 图28_11_ 所示，可以看到通过freetype_font_set_size函数设置字体的大小使每一行的文字都不一样。

.. image:: /media/docx163.jpg
   :align: center
   :alt: 图 28‑11 实验结果
   :name: 图28_11

图 28‑11 实验结果
