/******************************************************************************\
* Copyright (C) 2012-2013 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/
#include <windows.h>//如果嫌刷屏太快打开这个定义1（一共2处）

#include "Leap.h"
#include<sstream>
#include <stdio.h>
#include<iostream>

#pragma comment(lib,"WS2_32.lib")
using namespace Leap;
using namespace std;
char buff[50];


void GetHandDirection(const Controller& controller);
void getfingerposition(const Controller& controller);
int main() {

	Controller controller;

	WSADATA wsd;
    SOCKET sockClient;                                            //客户端socket
    SOCKADDR_IN addrSrv;


    sockClient=socket(AF_INET,SOCK_STREAM,0);                    //创建socket
    addrSrv.sin_addr.S_un.S_addr=inet_addr("192.168.1.1");
    addrSrv.sin_family=AF_INET;
    addrSrv.sin_port=htons(8080);
    connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));    //连接服务器端

	while(1)
	{
		//getfingerposition(controller);

		/*
	    for(int x=0;x<4;x++){
		send(sockClient,data[x],sizeof(data[x]),0);
		std::cout<<data[x]<<std::endl;

				Sleep(500);
		}
		*/
		GetHandDirection(controller);
		send(sockClient,buff,sizeof(buff),0);
		cout<<buff<<endl;
		Sleep(100);
	
	}

    closesocket(sockClient);                                    //关闭连接
    WSACleanup();





	return 0;
}
void getfingerposition(const Controller& controller){
 
	const Frame frame = controller.frame();
	if (!frame.hands().isEmpty()) {
		// 得到第一只手[hands()返回HandList结构，可以向操作容器一样操作]
		const Hand hand = frame.hands()[0];

		 //检查下手是否有手指[握拳的话，是找不到手指的]
		const FingerList fingers = hand.fingers();
		if (!fingers.isEmpty()) {
			// 计算指尖尖端平均位置坐标
			Vector avgPos;
			for (int i = 0; i < fingers.count(); ++i) {
				avgPos += fingers[i].tipPosition();
			}
			avgPos /= (float)fingers.count();

			sprintf_s(buff,"%d %d %d \r\n",int(avgPos.x)*8,int(avgPos.y)*8,int(avgPos.z)*8);//将avgPos的x,y,z存储为到buff中,以空格分开
			
		}
	}

}
void GetHandDirection(const Controller& controller){
			
	    const Frame frame=controller.frame();
		if (!frame.hands().isEmpty()) {
			const Hand hand=frame.hands()[0];
			const Vector direction = hand.direction();
            float Radius=hand.sphereRadius();//this is the ball's radius hold in hand
			
			
    // Calculate the hand's pitch, roll, and yaw angles
        std::cout << "Hand pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
          << "roll: " << hand.palmNormal().roll() * RAD_TO_DEG << " degrees, "
          << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl << std::endl;
		  sprintf_s(buff,"%d %d %d %d \r\n",int(direction.pitch() * RAD_TO_DEG),int(hand.palmNormal().roll() * RAD_TO_DEG),int(direction.yaw() * RAD_TO_DEG),int(Radius));
		  cout<<buff<<endl;
		}


}