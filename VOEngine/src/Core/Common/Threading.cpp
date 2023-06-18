#include "vopch.h"
#include "Threading.h"

namespace VOEngine {
	std::weak_ptr<Task> Scheduler::AddTask(std::function<bool(void)> task) {
		auto _task = std::make_shared<Task>(task);
		m_Tasks.emplace(_task->uuid, _task);
		return std::weak_ptr(_task);
	}

	void Scheduler::StartAllTasks() {
		for (auto it = m_Tasks.begin(); it != m_Tasks.end(); it++) {
			it->second->Start();
		}
	}

	void Scheduler::RemoveTask(UUID uuid) {
		m_Tasks.erase(uuid);
	}

	Task::~Task() {
		Stop();
	}

	void Task::Start() {
		m_IsExecuting = true;
		m_Thread = std::thread([this]() { Execute(); });
	}

	void Task::Execute() {
		while (m_IsExecuting && m_Thread.native_handle() != 0) {
			if (Paused) 
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			else
				m_IsExecuting = m_Task();
		}
	}

	void Task::Stop() {
		m_IsExecuting = false;
		Paused = false;
		if (m_Thread.joinable())
			m_Thread.detach();
	}

	bool Task::IsExecuting() {
		return m_IsExecuting;
	}
}
