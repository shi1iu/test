#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>


typedef struct
{
	uint32_t Header_frame;
	uint32_t Msg;
	uint64_t start_addr;
	uint64_t data_size;
	uint32_t end_frame;
} rece_Header_t;

int main()
{
rece_Header_t rece_Header;
rece_Header_t fasong;
int lfd=socket(AF_INET,SOCK_STREAM,0);
if(lfd==-1)
{
	perror("error");
	exit(0);
}
struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_port=htons(10001);
//addr.sin_addr.s_addr = INADDR_ANY; 
inet_pton(AF_INET,"192.168.6.100",&addr.sin_addr.s_addr);
    int ret = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1)
    {
        perror("bind");
        exit(0);
    }

    // 3. 设置监听
    ret = listen(lfd, 128);
    if(ret == -1)
    {
        perror("listen");
        exit(0);
    }

    // 4. 阻塞等待并接受客户端连接
    struct sockaddr_in cliaddr;
    int clilen = sizeof(cliaddr);
    int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &clilen);
    if(cfd == -1)
    {
        perror("accept");
        exit(0);
    }
    // 打印客户端的地址信息
    char ip[24] = {0};
    printf("客户端的IP地址: %s, 端口: %d\n",
           inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, sizeof(ip)),
           ntohs(cliaddr.sin_port));

while(1)
{
int zanting_flag = 0;  //暂停标志
int stop_flag = 0;  //暂停标志

char buf[1024];
ret=read(cfd,buf,sizeof(buf));
if(ret==-1)
{
perror("send");
return -1;
}
memcpy(&rece_Header, &buf, sizeof(rece_Header));

if(rece_Header.Header_frame==0xAAAAAAAA)
switch(rece_Header.Msg)
{
case 1:perror("kai shi cai ji "); 
			break;
case 2:perror("chuanshu ");zanting_flag=0;stop_flag=0;break; 
case 3:perror("3");zanting_flag=0;break;
case 4:perror("4");zanting_flag=0;break;
case 5:perror("5");zanting_flag=1;break;
case 6:perror("6");break;
case 7:perror("7");break;

default:("jie shou zhi lin shi bai ");
}
char buf1[1024];

if(zanting_flag==1)
fasong.Msg=99;
if(stop_flag==1)
fasong.Msg=88;
memcpy(&buf1, &fasong, sizeof(rece_Header));
write(cfd,buf1,sizeof(buf1));



}

close(cfd);
close(lfd);

return 0;
}
