#include "vopch.h"

namespace VOEngine {
	class SettingsManager {
	public:
		//Я хочу чтобы настройки можно было сохранять в нескольких файлах одновременно
		//Этот класс будет искпользоваться как движком так и юзером 
		SettingsManager(const std::string& filename) {
			m_FileNames.push_back(filename);
		}
		//
		virtual ~SettingsManager() = 0;
		// Возвращает значени по ключу e.g внутри файла SomeSetting: i'm black в коде GetValue("SomeSetting") вернет "i'm black"
		// При отсутствии ключа в файле вернуть пустую строку
		virtual std::string GetValue(const std::string& filename, const std::string& key) = 0;
		//Добавляет пару ключ значение в файл
		virtual void AddPair(const std::string& filename, const std::pair<std::string&, std::string&> pair) = 0;

		//Возвращает все ключи к которым присвоино значени value
		virtual std::vector<std::string> GetKeyByValue(const std::string& filename, const std::string& value) = 0;

	private:
		std::vector<std::string> m_FileNames;
	};
}