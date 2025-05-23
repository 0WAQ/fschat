#include "ConfigManager.h"

ConfigManager::ConfigManager()
{
	boost::filesystem::path current_path = boost::filesystem::current_path();
	boost::filesystem::path config_path = current_path / "config.ini";

	debug("config path: {}", config_path.string());

	boost::property_tree::ptree pt;
	boost::property_tree::read_ini(config_path.string(), pt);

	for (const auto& [name, tree] : pt) {
		SectionInfo section;
		for (const auto& [key, value] : tree) {
			section._section_datas.insert({ key, value.get_value<std::string>() });
		}
		_config[name] = section;
	}

	for (const auto& [name, info] : _config) {
		debug("[{}]", name);
		for (const auto& [k, v] : info._section_datas) {
			debug("{} {}", k, v);
		}
	}
}

ConfigManager::ConfigManager(const ConfigManager& config)
{
	_config = config._config;
}

ConfigManager& ConfigManager::operator=(const ConfigManager& config)
{
	if (this == &config) {
		return *this;
	}
	_config = config._config;
	return *this;
}

SectionInfo ConfigManager::operator[](const std::string& section)
{
	if (_config.find(section) == _config.end()) {
		return { };
	}
	return _config[section];
}

ConfigManager::~ConfigManager()
{
	_config.clear();
}
