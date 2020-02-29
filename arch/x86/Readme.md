
# 组织结构

image:最终生成的包含MBR、引导程序与内核和文件系统的软盘镜像
include:头文件
kernel:内核功能与架构有关的底层实现
      |___ irq:中断有关
      |___ sched: 调度器有关

lib：库文件的架构相关实现
loader: MBR与引导程序loader
mm: 内存管理有关
output:内核编译中生成的各output文件
