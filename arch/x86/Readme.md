
# x86下镜像

* 目前采用的是软盘镜像加载系统的  
* 首先顶层makefile依次调用根目录文件夹下的makefile编译**架构无关**的源文件，放在./output文件夹中（lib文件则单独放在./lib下）
* 然后进入arch/x86下的makefile，开始编译**x86**架构相关的资源文件
  1、首先执行loader文件夹的makefile,一是直接生成loader.bin、mbr.bin，二是生成一个空的软盘镜像a.img，并将mbr写入前512字节，移动到image文件夹下
  2、编译其他文件夹下的文件
  3、库文件单独链接成lib.a，并放在output下
  4、将output下所有的.o文件链接成kernel.bin，如果定义了DEBUG = 1,则再连接一份kernel.elf文件以供GDB调试
  5、调用creatImage.sh，挂载image文件夹下的a.img将kernel.bin复制到软盘镜像中