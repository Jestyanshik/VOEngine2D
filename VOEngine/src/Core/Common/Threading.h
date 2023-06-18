#pragma once

namespace VOEngine {
	class Task {
	public:
		Task(const std::function<bool(void)>& task) : m_Task(task) {}
		~Task();
		void Start();
		void Stop();
		bool IsExecuting();
		UUID uuid;
		bool Paused = false;
	private:
		void Execute();
		std::function<bool(void)> m_Task;
		std::thread m_Thread;
		bool m_IsExecuting = false;
	public:
		bool operator==(const Task& other) const {
			return uuid == other.uuid;
		}
	};

	class Scheduler {
	public:
		//task should return false when it wants to stop
		std::weak_ptr<Task> AddTask(std::function<bool(void)> task);
		void StartAllTasks();
		void RemoveTask(UUID uuid);
	private:
		std::unordered_map<UUID, std::shared_ptr<Task>> m_Tasks;
	};
}