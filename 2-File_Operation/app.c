#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
int fd;//定义一个句柄
char buf[64] = {0};
fd = open("/dev/hello_misc",O_RDWR);//打开设备节点
if(fd < 0)
{
perror("open error \n");
return fd;
} /
/read(fd,buf,sizeof(buf));
write(fd,buf,sizeof(buf));
close(fd);
return 0;
}