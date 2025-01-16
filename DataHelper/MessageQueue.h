#pragma once
#include <mutex>
#include <queue>
#include <string>
#include "ObjectType.h"
#include "MessagePacket.h"

class MessageQueue {
public:
	void Enqueue(const MessagePacket& message);
	MessagePacket Dequeue();
	bool IsEmpty();
	int GetQueueDstMacAddress();
	int GetQueueSrsMacAddress();

	MessageQueue() = default;
	~MessageQueue() = default;
	MessageQueue(const MessageQueue& obj) = default;

private:
	std::mutex m_mtx;
	std::queue<MessagePacket> m_queue;
	std::condition_variable m_cv;
};