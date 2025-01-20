#include "RFCommunication.h"

MessageQueue RFCommunication::m_messageQueue;

void RFCommunication::SendPacket(const MessagePacket& message)
{
	
	//std::cout << "RF Communication: Sending Data - " << message << std::endl;
	m_messageQueue.Enqueue(message);
}

MessagePacket RFCommunication::ReceivePacket()
{
	//std::string data = "Sensor triggered message";
	//std::cout << "RF Communication : Receiving data - " << data << std::endl;
	if (!m_messageQueue.IsEmpty())
	{
		return m_messageQueue.Dequeue();
	}
}

bool RFCommunication::HasMessage()
{
	return !m_messageQueue.IsEmpty();
}

int RFCommunication::GetMessageDstMacAdress()
{
	return m_messageQueue.GetQueueDstMacAddress();
}

int RFCommunication::GetMessageSrsMacAdress()
{
	return m_messageQueue.GetQueueSrsMacAddress();
}