#include "vopch.h"
#include "Events.h"

void VOEngine::EventNotifier::Subscribe(EventType type, EventCallback callback) {
	if (auto vec = m_NotifyList.find(type);vec != m_NotifyList.end()) {
		vec->second.push_back(callback);
	}
	else {
		std::vector<EventCallback> newvec = {callback};
		m_NotifyList.emplace(std::pair(type, newvec));
	}
}

void VOEngine::EventNotifier::Unsubscribe(const std::string& receiver, EventType type) {
	for (size_t i = m_NotifyList.count(type) - 1; i > 0; i--) {
		std::vector<EventCallback> vec = m_NotifyList[type];
		for (size_t j = vec.size() - 1; j > 0; j--) {
			if (vec[j].Receiver == receiver) {
				vec.erase(vec.begin() + j);
				goto nestedloopend; //Oh no using goto is bad i should replace it, hhahah, NO!
			}
		}
	}
nestedloopend:;
}

void VOEngine::EventNotifier::GenerateEvent(Event event, bool notifyImmediately) {
	m_Events.push_back(event);
	if (notifyImmediately)
		Notify(event.Type, event.Info);
}

bool VOEngine::EventNotifier::EventExists(EventType type) {
	for (size_t i = m_Events.size() - 1; i > 0; i--) {
		if (m_Events[i].Type == type) {
			return true;
		}
	}

	return false;
}

void VOEngine::EventNotifier::Notify(EventType type, void* info) {
	std::vector<EventCallback> vec = m_NotifyList[type];
	for (size_t j = 0; j < vec.size(); j++) {
		vec[j].Callback(info);
	}
	
	for (size_t i = m_Events.size() - 1; i > 0; i--) {
		if (m_Events[i].Type == type) 
			m_Events.erase(m_Events.begin() + i);
	}
}

void VOEngine::EventNotifier::Notify(EventType type) {
	void* info{};
	bool eventFound = false;
	for (size_t i = m_Events.size() - 1; i > 0; i--) {
		if (m_Events[i].Type == type) {
			info = m_Events[i].Info;
			eventFound = true;
		}
	}
	if (not eventFound) 
		return;

	std::vector<EventCallback> vec = m_NotifyList[type];
	for (size_t j = 0; j < vec.size(); j++) {
		vec[j].Callback(info);
	}

	for (size_t i = m_Events.size() - 1; i > 0; i--) {
		if (m_Events[i].Type == type)
			m_Events.erase(m_Events.begin() + i);
	}
}
