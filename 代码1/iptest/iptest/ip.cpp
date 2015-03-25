#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/*将十六进制参数转换成点分十进制 
例如：0x8002c2f2  ->128.2.194.242
*/
int my_htonl(char *argv)
{
	struct in_addr inaddr;//网络字节序
	unsigned int addr;//点分十进制

	sscanf(argv, "%x", &addr);
	inaddr.s_addr = htonl(addr);
	printf("%s/n", inet_ntoa(inaddr));

	return 0;
}


/*将点分十进制参数转换成十六进制
例如： 128.2.194.242->0x8002c2f2
*/
int my_ntohl(char * argv)
{
	struct in_addr inaddr;//网络字节序
	unsigned int addr;//点分十进制

	if(inet_aton(argv, &inaddr) != 0){
		addr = ntohl(inaddr.s_addr);
		printf("0x%x/n", addr);
	}
	return 0;
}



int main( )
{
	char * test_arry1  = "0xcb00a8c0";

          
	return 0;
}