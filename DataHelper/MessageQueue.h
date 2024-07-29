#pragma once
#include <mutex>
#include <queue>
#include <string>
#include "ObjectType.h"
#include "MessagePacket.h"

class MessageQueue {
public:
	void Send(const MessagePacket& message);
	MessagePacket Receive();
	bool IsEmpty();
	int GetQueueDstMacAddress();

	MessageQueue() = default;
	~MessageQueue() = default;
	MessageQueue(const MessageQueue& obj) = default;

private:
	std::mutex m_mtx;
	std::queue<MessagePacket> m_queue;
	std::condition_variable m_cv;
};