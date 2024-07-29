#include "MessageQueue.h"

void MessageQueue::Send(const MessagePacket& message)
{
	std::unique_lock<std::mutex> lock(m_mtx);
		m_queue.push(message);
		m_cv.notify_one();
}

MessagePacket MessageQueue::Receive()
{
	std::unique_lock<std::mutex> lock(m_mtx);
		m_cv.wait(lock, [this] { return !m_queue.empty(); });
		MessagePacket message = m_queue.front();
		m_queue.pop();
		return message;
}

bool MessageQueue::IsEmpty()
{
	std::lock_guard<std::mutex> lock(m_mtx);
		return m_queue.empty();
}

int MessageQueue::GetQueueDstMacAddress()
{
	return m_queue.front().GetDstMacAddress();
}