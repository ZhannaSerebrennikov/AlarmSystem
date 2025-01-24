#include "MessageQueue.h"

void MessageQueue::Enqueue(const MessagePacket& message)
{
	std::unique_lock<std::mutex> lock(m_mtx);
	//m_cv.wait(lock, [this] { return !m_queue.empty(); });
		m_queue.push(message);
		m_cv.notify_one();
}

MessagePacket MessageQueue::Dequeue()
{
	std::unique_lock<std::mutex> lock(m_mtx);
		m_cv.wait(lock, [this] { return !m_queue.empty(); });
		MessagePacket message = m_queue.front();
		m_queue.pop();
		///m_cv.notify_one();
		return message;
}

bool MessageQueue::IsEmpty()
{
	std::lock_guard<std::mutex> lock(m_mtx);
		return m_queue.empty();
}

int MessageQueue::GetQueueDstMacAddress()
{
	std::lock_guard<std::mutex> lock(m_mtx);
		if (!m_queue.empty())
		{
			return m_queue.front().GetDstMacAddress();
		}
		throw std::runtime_error("Queue is empty");
}

int MessageQueue::GetQueueSrsMacAddress()
{
	std::lock_guard<std::mutex> lock(m_mtx);
		if (!m_queue.empty())
		{
			return m_queue.front().GetSensorData().macAddress;
		}
		throw std::runtime_error("Queue is empty");
}