#pragma once
#include "Ex.h"
#include <map>

class IniParser {
public:
	IniParser() = delete;
	explicit IniParser(const std::string& filename);
	IniParser(std::istream& stream);
	~IniParser() = default;

	void ShowAll() const noexcept;
	bool IsHaveSection(const std::string& sectionName) const noexcept;
	bool IsHaveParam(const std::string& sectionName, const std::string& param)
		throw (SectionException);
	template<typename T>
	T GetValue(const std::string& sectionName, const std::string& param)
		throw (ParamException);
private:
	std::istream& MakeStream(const std::string& filename);
	void Initialize();
	void CleanString(std::string& line);
	void Parse(std::string& line);
	void MakeSection(std::string line);
	void RemoveSpaces(std::string& line);
	void RemoveComments(std::string& line);
	void CheckStreamIfOpen() const throw (StreamException);
	void FindParamAndValue(const std::string &line);
	void Insert(const std::string &param, const std::string &value);
	std::string activeSection = "";
	std::map<std::string, std::map<std::string, std::string>> data;
	std::istream& contentStream;
};