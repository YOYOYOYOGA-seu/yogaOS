
# x86下镜像  

* 目前采用的是软盘镜像加载系统的    
* 首先顶层makefile依次调用根目录文件夹下的makefile编译**架构无关**的源文件，放在./output文件夹中（lib文件则单独放在./lib下）  
* 然后进入arch/x86下的makefile，开始编译**x86**架构相关的资源文件  
  1、首先执行loader文件夹的makefile,一是直接生成loader.bin、mbr.bin，二是生成一个空的软盘镜像a.img，并将mbr写入前512字节，移动到image文件夹下  
  2、编译其他文件夹下的文件  
  3、库文件单独链接成lib.a，并放在output下  
  4、将output下所有的.o文件链接成kernel.bin，如果定义了DEBUG = 1,则再连接一份kernel.elf文件以供GDB调试  
  5、调用creatImage.sh，挂载image文件夹下的a.img将kernel.bin复制到软盘镜像中  


# x86的页式内存管理  
  1、线性地址空间分布策略：低1G空间分配给用户使用，包括可访问的5大数据区和不可访问的进程有关信息区；2G空间用于线性映射整个物理内存，包括系统使用的区域（物理内存低地址处）与高低址空闲的用于动态分配的区域，及系统只支持最大1G的物理内存；最高的2G空间暂时保留  
  2、虚拟内存空间的分布见include/address.h  
  3、采用二级页表的管理方法，首先在系统刚运行时，会立刻初始化页表：首先建立一个连续的包括所有物理内存的二级页表；之后在一级页表中映射两份，一份是从0x0000000开始，第二份是从0x40000000开始，指向同一片物理空间，其中低地址的映射是为了保证在跳转前程序可以继续运行（线性地址和物理地址相同）。之后立马跳转到高地址（即进入内核线性地址空间），之后低地址0x0000000后的一级页表映射就完成了他的使命  
