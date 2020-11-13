# MySScom
一个自创的串口通信助手和调试助手

本程序仅为个人兴趣开发，有需要者可以免费使用，但是请不要在网络上进行恶意传播



# 功能说明

待添加



# 使用说明

待添加



# 升级日志

## V4.0.0_20120203

1、改用文件句柄方式实现串口驱动，收发效果均不错。能在没有安装VC的XP系统和win7系统上使用；



## V3.0.0_20120131

1、删除原用的串口通信控件，改用网上下载的自定义类，但是数据接收速度过慢，仍待改进；



## V2.4.0_20111213

1、在状态栏增加行数的显示，并以该值作为自动清空时的判断标准(之前是通过获取编辑框提供的API来判断当前行数，实际使用中发现该接口返回的值有问题，经常数据收到一半就被清空了)；

2、字符模式下，以接收到的行数作为清空标准；16进制模式下，以接收到的字符数作为清空标准；

3、状态栏的显示内容根据窗口大小而变化，窗口比较窄时显示比较少，窗口比较宽时显示比较多；



## V2.3.0_20110629

1、在清空窗口内容时增加对显示时间的判断，实现清空之后的第一行能正确显示时间；



## V2.2.0_20110422

1、增加波特率选项值，新增600，1200，921600等不常用的值，以尽可能满足各种场合需求；



## V2.1.0_20110310

1、增加时间显示功能的使用开关。目前在16进制显示模式下不支持同时显示接收时间；

2、增加校验位的选择功能，目前支持None、Odd、Even、Mark、Space四种校验方式；

3、优化程序界面，在托盘菜单中增加一个对话框显示使用帮助和升级说明相关信息；

4、优化程序对普通发送模式和高级发送模式的切换显示，实现精确定位对话框大小；

5、调整数据接收方式，由事件触发改为定时触发，避免频繁接收时CPU占用率过高；



## V2.0.0_20110125

1、接收编辑框换成RichEdit控件；

2、删除多余的控件，简化稳定程序功能；

3、换行时自动在行头位置显示时间，方便查看；

4、通过转移编辑框焦点的方式，彻底解决屏幕闪烁的问题；

5、增加托盘图标，关闭程序时不退出，而是隐藏到托盘，点击托盘菜单才会退出；



## V1.6.0_20101014

1、修改由于长度限制导致程序在启动时自动载入高级发送区域的数据丢失字节的Bug；



## V1.5.0_20100801

1、增加接收区自动清屏时最大行数的自定义设置功能，即接收数据超过最大行数时自动清屏；



## V1.4.0_20100631

1、修正更新数据时屏幕闪烁非常厉害的问题，每次等数据全部接收完毕后再统一刷新显示；



## V1.3.0_20100406

1、新增高级发送功能，多达20条自定义字符串，可选择Hex格式发送，并能定时自动循环发送；

2、增加所有参数的自动保存和读取功能，程序退出时会保存所有参数，程序启动时同步读取；



## V1.2.0_20100206

1、完善了对串口的各项属性的设置功能，能够完整的提供对波特率、数据位和停止位的全部设置；

2、采用EasySize头文件，实现了窗体的完美大小缩放功能；

3、同时，更换了状态栏的实现机制，能够适应窗体的变化而实时更新，效果很好；

4、完善了其他几个机制，包括各种状态机的切换和人性化提示等



## V1.1.0_20100105

1、加入状态栏功能，对串口的实时状态、所接收和发送的字节数以及其他相关信息进行显示；

2、考虑到状态栏的位置没法实时更改，因此取消了窗口的大小可变及最大化功能，只能固定尺寸；

3、加入了发送文本文件的功能，读取到文件之后在发送窗口显示，并按指定大小分批发送；

4、其实，完全能够再加入一个发送进度的指示条，但是没有合适的地方可以放置，暂时不处理；



## V1.0.0_20091203

1、创建该项目，采用串口枚举机制，实现串口数据的基本收发和显示；

2、提供接收数据的清空和保存功能，包括手动实现和自动实现两种方式；

3、同时对所接收和发送的数据，提供16进制形式和字符形式两种格式进行切换；

