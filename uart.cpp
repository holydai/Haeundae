// uart.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include <stdio.h> 
#include <conio.h> 

int _tmain(int argc, _TCHAR* argv[])
{
	char COM[9] = "12344321";  //点亮
	char ACK[10]="";
						//创建串口
	HANDLE hDevice = CreateFile(L"\\\\.\\COM12",  //注意COM1~COM10与COM10以上的窗口的命名规则
		GENERIC_READ | GENERIC_WRITE,   //使用读写方式
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,//普通文件属性
		0);
	if (hDevice != INVALID_HANDLE_VALUE)
	{
		printf("Port opened!\n");
		DCB lpTest;
		GetCommState(hDevice, &lpTest);  //获取当前的参数设置
		lpTest.BaudRate = CBR_9600;       //设置波特率
		lpTest.ByteSize = 8;              //数据位数为8
		lpTest.Parity = NOPARITY;         //无校验
		lpTest.StopBits = ONESTOPBIT;   //1位停止位
		SetCommState(hDevice, &lpTest);  //设置通信参数
		DWORD btsIO;
		for(int i=0;i<3;i++)
		{
			WriteFile(hDevice, COM, strlen(COM), &btsIO, NULL);    //发送数据
			Sleep(20);//等待接收
			printf("start rx!\n");
			ReadFile(hDevice, ACK, 10, &btsIO, NULL);
			ACK[8] = '\0';
			printf("%s\n", ACK);
		}
		CloseHandle(hDevice);    //关闭串口 
	}
	return 0;
}
