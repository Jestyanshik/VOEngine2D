#include "vopch.h"

namespace VOEngine {
	class SettingsManager {
	public:
		//� ���� ����� ��������� ����� ���� ��������� � ���������� ������ ������������
		//���� ����� ����� ��������������� ��� ������� ��� � ������ 
		SettingsManager(const std::string& filename) {
			m_FileNames.push_back(filename);
		}
		//
		virtual ~SettingsManager() = 0;
		// ���������� ������� �� ����� e.g ������ ����� SomeSetting: i'm black � ���� GetValue("SomeSetting") ������ "i'm black"
		// ��� ���������� ����� � ����� ������� ������ ������
		virtual std::string GetValue(const std::string& filename, const std::string& key) = 0;
		//��������� ���� ���� �������� � ����
		virtual void AddPair(const std::string& filename, const std::pair<std::string&, std::string&> pair) = 0;

		//���������� ��� ����� � ������� ��������� ������� value
		virtual std::vector<std::string> GetKeyByValue(const std::string& filename, const std::string& value) = 0;

	private:
		std::vector<std::string> m_FileNames;
	};
}