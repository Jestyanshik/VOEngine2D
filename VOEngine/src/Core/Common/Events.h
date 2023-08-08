#pragma once
#include "UUID.h"

namespace VOEngine {
	enum EventType {
		RenderUpdate, //Unit added, deleted, modified, etc.
		SoundUpdate,  //Sound started, stopped, paused
		Resize
	};

	struct ResizeEventInfo {
		glm::uvec2 Size;
	};

	struct Event {
		UUID UUID{};
		EventType Type;
		void* Info;
		Event(EventType type, void* info): Type(type), Info(info) {

		}
		~Event() { }
	};

	class EventCallback
	{
	public:
		std::function<void(void*)> Callback;
		std::string Receiver;
		EventCallback(std::function<void(void*)> callback, const std::string& receiver) { 
			Receiver = receiver; 
			Callback = callback;
		};
		~EventCallback() {};
	};

	class EventNotifier {
	public:
		void Subscribe(EventType type, EventCallback callback);
		void Unsubscribe(const std::string& notifier, EventType type);
		void GenerateEvent(Event event, bool notifyImmediately = true);
		void Notify(EventType type, void* info);
	private:
		std::vector<Event> m_Events{};
		std::unordered_map<EventType, std::vector<EventCallback>> m_NotifyList{};
	public:
	};
}
