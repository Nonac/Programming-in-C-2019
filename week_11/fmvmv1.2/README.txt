测试系统：centos7
valgrind版本 3.14

该版fmvm主文件只有78 bytes没有释放，具体可运行后查阅。

我更新了更大范围的测试，发现生成了新的内存泄漏错误，这是testfmvm不曾检测到的区域。
具体代码都在 ./更多测试/目录下

homophones程序是通过读取cmudict.txt字典，生成单词与读音的索引表格。
样例是我写的程序，里面规范了mvm方法，函数原型和fmvm完全一样，在环境下测试通过，
，而且无内存溢出。所以不用担心是homophones.c有问题。

样例测试命令：
make -f hom.mk run
make -f hom.mk memleaks


与./更多测试/测试包中提供了测试fmvm的homophones make文件、homophones.c和字典文件。
与样例的区别为：

homophones.c：
#include<mvm.h>     ->>>>>>>     #include<fmvm.h>

hom.mk:
INCS = mvm.h     ->>>>>>>     INCS = fmvm.h
SOURCES =  $(TESTBASE).c mvm.c     ->>>>>>>    SOURCES =  $(TESTBASE).c mvm.c    