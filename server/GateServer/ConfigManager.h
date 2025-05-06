#ifndef _CONFIGMANAGER_H_
#define _CONFIGMANAGER_H_

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <unordered_map>

#include "ulti.h"
#include "singleton.h"

/**
 * @brief 配置文件节信息
 */
struct SectionInfo
{

	SectionInfo() { }

	SectionInfo(const SectionInfo& rhs) {
		_section_datas = rhs._section_datas;
	}

	SectionInfo& operator = (SectionInfo& rhs) {
		if (this == &rhs) {
			return *this;
		}

		_section_datas = rhs._section_datas;
		return *this;
	}

	~SectionInfo() {
		_section_datas.clear();
	}

	std::string operator[] (const std::string& key) {
		if (_section_datas.find(key) == _section_datas.end()) {
			return { };
		}
		return _section_datas[key];
	}

	std::unordered_map<std::string, std::string> _section_datas;
};

/**
 * @brief 配置管理类
 */
class ConfigManager : public Singleton<ConfigManager>
{
public:
	friend class Singleton<ConfigManager>;

private:
	ConfigManager();

public:
	ConfigManager(const ConfigManager& config);

	ConfigManager& operator = (const ConfigManager& config);

	std::unordered_map<std::string, SectionInfo>& config() { return _config; }

	SectionInfo operator[] (const std::string& section);

	~ConfigManager();

private:
	std::unordered_map<std::string, SectionInfo> _config;
};

#endif // _CONFIGMANAGER_H_