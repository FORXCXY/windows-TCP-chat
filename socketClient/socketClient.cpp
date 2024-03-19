#include <iostream>

#include <WinSock2.h>

#include <WS2tcpip.h>

#pragma comment(lib,"WS2_32.Lib") //指定动态库lib文件

using namespace std;


//创建套接字
//套接字绑定
//监听套接字
//向服务端发起连接请求
//发送和接收服务端数据
//关闭套接字

int main() {

	WSADATA wd; //获取socket相关信息的类

	if ((WSAStartup(MAKEWORD(2, 2), &wd)) != 0) { //初始化函数
		cout << "Failed to create WSA" << endl;
		return 0;
	}

	// 1.创建套接字TCP
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		cout << "Failed to create socket" << endl;
		return 0;
	}

	// 2.绑定发送建立连接的套接字实例到一个IP和发送建立连接的端口
	sockaddr_in addr;

	// 网络字节序
	// 以确保在不同计算机之间进行数据传输时，能够使用统一的网络字节序进行通信
	// host to network short将一个无符号短整型（16位）的主机字节序值转换为网络字节序值
	addr.sin_port = htons(8000);
	// 将IPv4 地址的字符串表示转换为二进制形式，并将结果存储在 addr.sin_addr.s_addr 中
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

	// 指定地址簇
	addr.sin_family = AF_INET;

	int len = sizeof(sockaddr_in);
	if (connect(s, (sockaddr*)&addr, len)!= 0) {
		cout << "connect error" << endl;
		return 0;
	}

	// 3.发送接收消息
	int ret = 0;
	do {
		// 向客户端发送信息
		ret = send(s, "I am client", strlen("I am client"), 0);
		// 接收客户端消息
		char buffer[64] = { '\0' };
		// memset(&buffer, '\0', sizeof(buffer));
		ret = recv(s, buffer, 64, 0);
		cout << "recv:" << buffer << endl;
	} while (ret != SOCKET_ERROR && ret != 0);

	// 4.关闭套接字
	closesocket(s);
	WSACleanup();
	return 0;



}