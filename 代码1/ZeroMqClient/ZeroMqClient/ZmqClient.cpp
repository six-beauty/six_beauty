//2014-4-2  programed by sixbeauty
//zeromp 通讯测试client 端
#include "zmq.h"
#include "zmq_utils.h"            //Zeromq 函数的导入在这里帮我们实现了
#include <iostream>
#pragma comment(lib,"libzmq-v100-mt-4_0_4.lib")
int main()
{
	std::cout << "-------------------Zeromq REB style-----------------------" <<std::endl;
	std::cout << "---------------------Author:SanYue------------------------" <<std::endl;

	void* context=zmq_init(1);    //指定zmq 处理I/0事件的thread pool 为1
	void* z_socket=zmq_socket(context,ZMQ_PUSH);
//	zmq_setsockopt(z_socket,ZMQ_SUBSCRIBE,"",0);
	zmq_connect(z_socket,"tcp://localhost:5555");    // accept connections on a socket

	for(int i=0;i<9;i++)    //循环工作
	{
		system("pause");    //暂停

		//发送部分
		zmq_msg_t send_msg;
		zmq_msg_init_size(&send_msg,6);
		memcpy(zmq_msg_data(&send_msg),"hello",6);
		zmq_msg_send(&send_msg,z_socket,0);
		zmq_msg_close(&send_msg);
/*
		//接受部分
		zmq_msg_t recv_msg;
		zmq_msg_init(&recv_msg);
		zmq_msg_recv(&recv_msg,z_socket,0);                    //0表示非阻塞
		printf("收到Server端回答:\t");
		std::cout<<(char*)zmq_msg_data(&recv_msg)<<std::endl;
		zmq_msg_close(&recv_msg);
*/

	}
  
	zmq_close(z_socket);
	zmq_term(context);

	return 0;
}