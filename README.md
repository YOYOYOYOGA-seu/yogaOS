# **yogaOS**
一个玩具内核特性如下：  
  1、支持优先级、时间片调度  
  2、一个采用POSIX标准的系统（仅有很少部分的接口。。。）  
  3、采用页式虚拟内存管理  
  4、文件系统（还未设计。。。）  
  5、目前是在x86上运行的，希望能够多架构支持（至少在设计上是这么考虑的，虽然不一定有时间移植）  




# 开发日志
2020.2.01 - 2020.2.22   
完成x86架构下系统由MBR -> loader -> 载入系统 的内容  

* 2020.2.22  
x86 架构下的线性地址映射方式：  
  1、用户程序一律从线性地址4M处开始  
  2、用户堆栈与系统堆栈都放在线性地址0x0000处   
  3、用户页表中系统内核区域（0x1000至1M，2M-4M）为物理地址一一对应的映射方式  
  4、进程页表目录、页表与系统内核使用的页表统一映射到同一线性地址处（1M处）  
  5、系统内核页表采用与物理地址一一映射的方式（无效的物理地址不做线性地址映射，最物理内存支持为1023*1024 = 1G ）  
  6、初步完成PCB结构体架构无关成员的初始化   

* 2020.2.22 - 25  
  1、完成了PCB初始化与简单的页式内存管理  
  2、重新组织了内存分布  
  3、抛弃了段式内存管理，仅在初始化时简单使用   
  4、地址分布可能还需要更改，将实际的物理空间全部映射到高地址处（系统线性地址基址改到1G处，并附带映射整个物理空间）,这样可以去除内核页表，在进入内核态时（比如管理物理空间，分配物理内存等）可直接使用任务页表，不需要切换到内核表   

* 2020.2.26  
  1、最终定稿（也许并不是最终）了x86架构下线性地址空间的分布  
  2、完成了系统任务初始化中的页表与线性地址初始化  

* 2020/3/1  
  1、第一次提交仓库  
  2、终于完成了历史性的多任务按时间片调度功能  
  3、事实上现在仅仅能够实现基本的任务调度，和仅仅实现页分配（还不能回收与换页）的内存管理  
  4、在地址空间的分配上花了很多时间，才最终暂时确定了现在的物理内存空间和线性地址空间的布局结构  
  5、之前从没接触过x86,不过还是觉得x86并不是一个简单的漂亮的架构，相比于arm显得比较脏乱，在弯弯绕架构上花费了绝大部分的时间(保护模式与段式内存管理处理除了向下兼容，还有什么具体的意义？)   

* 2020.3.8 - 3.9
  1、加入了任务延时挂起功能（suspend list）  
  2、完成了系统调用的框架雏形（x86下使用0x80号中断）  
  3、添加完成了sleep()、getpid()两个POSIX接口api（通过系统调用）  

* 2020.3.21 - 3.22
  1、加入的键盘驱动（刚刚实现键盘的简单输入（字母键与数字等），与回显）  
  2、为了测试将显卡显存段的dpl改为了3（方便在应用中直接显示）  
  3、现在的tty测试进程写在了main.c中，后期考虑单独弄成可执行文件或放在server文 件夹中  
  4、修改了一处bug，./arch/x86/lib/asm.S 中进入系统调用中断的函数没有对传参的寄存器进行保存与恢复，导致返回进程后寄存器值丢失发生错误  
  5、**整理代码！！！整理代码！！**      

* 2020.3.26
  1、解决了键盘读buff的bug（循环赋值时没有递增接收buff指针，导致丢键）  
  2、加入了特殊键的识别（ESC、SHIFT、ALT等）  
