#pragma once
#include <string>
#include <iostream>
#include "../DataHelper/MessageQueue.h"

//In an actual system, RF communication would involve sending and receiving data packets between devices and the control panel. Here, we simulate RF communication with simple method calls

class RFCommunication {
public:
	static void SendPacket(const MessagePacket& message);
	static MessagePacket ReceivePacket();
	static bool HasMessage();
	static int GetMessageDstMacAdress();
	static int GetMessageSrsMacAdress();

private:
	static MessageQueue m_messageQueue;
};