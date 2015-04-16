http://blog.sina.com.cn/s/blog_a6fb6cc90101gks5.html


svn checkout svn://svn.code.sf.net/p/qwt/code/branches/qwt-6.1 


designer目录：存放QWT插件的源码
doc目录：存放帮助文档
examples目录：存放QWT的示例（源码、可执行程序）
src目录：存放QWT的源码
textengines目录：存放数学指标语言的文本驱动引擎代码
还包含一些pro等工程文件等。



4.开始编译
    cd E:\QWT
    qmake qwt.pro  
    nmake  
    ----------漫长的等待-----------  
  
    cd designer  
    qmake designer.pro  
    nmake  
    ----------漫长的等待-----------  
    cd ..  
    cd examples  
    qmake examples.pro  
    nmake 
    ----------漫长的等待-----------  


也可以使用VS2010直接打开pro进行编译更为简单。

5.配置
（1）将E:\QWT\lib下的qwtd.dll、qwt.dll拷贝到D:\Software\Qt\Qt5.1.0\5.1.0\msvc2010\bin下，
   将qwtd.lib、qwt.lib拷贝D:\Software\Qt\Qt5.1.0\5.1.0\msvc2010\lib下（以qt安装目录D:\Software\Qt\Qt5.1.0\5.1.0\msvc2010为例）。
（2）将E:\QWT\designer\plugins\designer目录下的qwt_designer_plugin.dll和qwt_designer_plugin.lib拷贝到D:\Software\Qt\Qt5.1.0\5.1.0\msvc2010\plugins\designer目录下。
（3）将E:\QWT\src目录下的所有.h和.cpp放入一个空文件夹QWT中，再将该文件夹拷贝到D:\Software\Qt\Qt5.1.0\5.1.0\msvc2010\include目录下。

6.使用
    新建项目，然后进行配置：
（1）属性->配置属性->C/C++->常规，附加包含目录：$(QTDIR)\include\QWT
（2）属性->配置属性->链接器->输入，附加依赖项：qwtd.lib
（3）属性->配置属性->C/C++->预处理器，预处理器定义：QWT_DLL

所有工作准备完成之后，写一个demo，测试一下：