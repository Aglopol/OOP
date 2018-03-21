#include "IniParser.h"
#include "Ex.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <iostream>

IniParser::IniParser(std::istream& stream) : contentStream(stream) {
	Initialize();
}

IniParser::IniParser(const std::string& filename) : contentStream(MakeStream(filename)) {
	Initialize();
}

std::istream& IniParser::MakeStream(const std::string &filename) {
	std::ifstream stream(filename);
	return stream;
}

void IniParser::CheckStreamIfOpen() const throw (StreamException) {
	if (!contentStream) {
		throw FileException("The stream does not exist");
	}
}

void IniParser::Initialize() {
	CheckStreamIfOpen();
	std::string line;
	while (std::getline(contentStream, line)) {
		Parse(line);
	}
}

void IniParser::Parse(std::string& line) {
	CleanString(line);
	if (line.empty())
		return;
	if (line[0] == '[')
		MakeSection(line);
	else FindParamAndValue(line);

}

bool IniParser::IsHaveSection(const std::string& sectionName) const noexcept {
	return data.count(sectionName) != 0;
}

bool IniParser::IsHaveParam(const std::string& sectionName, const std::string& param)
throw (SectionException) {
	if (!IsHaveSection(sectionName))
		throw SectionException(sectionName);
	auto it = data.find(sectionName);
	auto pit = it->second.find(param);
	if (pit != it->second.end())
		return true;
	return false;
}

void IniParser::FindParamAndValue(const std::string &line) {
	size_t p = line.find('=');
	if (p != std::string::npos) {
		std::string param = line.substr(0, p);
		std::string value = line.substr(p + 1, line.length() - 1 - p);
		Insert(param, value);
	}
}

void IniParser::Insert(const std::string &param, const std::string &value) {
	data[activeSection][param] = value;
}

void IniParser::MakeSection(std::string line) {
	activeSection = line.substr(1, line.length() - 2);
}

void IniParser::RemoveSpaces(std::string& line) {
	line.erase(std::remove_if(line.begin(), line.end(), [](char x) {return std::isspace(x); }), line.end());
}

void IniParser::RemoveComments(std::string& line) {
	auto p = std::find(line.cbegin(), line.cend(), ';');
	line.erase(p, line.cend());
}

void IniParser::CleanString(std::string& line) {
	if (line.empty())
		return;
	RemoveComments(line);
	RemoveSpaces(line);
}

void IniParser::ShowAll() const noexcept {
	for (auto it = data.begin(); it != data.end(); it++) {
		std::cout << it->first << std::endl;
		for (auto jt = it->second.begin(); jt != it->second.end(); jt++)
			std::cout << jt->first << " " << jt->second << std::endl;
	}
}

template <>
std::string IniParser::GetValue<std::string>(const std::string& sectionName, const std::string& param)
throw (ParamException) {
	if (!IsHaveParam(sectionName, param)) {
		throw ParamException(param);
	}
	return data.at(sectionName).at(param);
}

template <>
int IniParser::GetValue<int>(const std::string& sectionName, const std::string& param)
throw (ParamException) {
	if (!IsHaveParam(sectionName, param)) {
		throw ParamException(param);
	}
	return stoi(data.at(sectionName).at(param));
}

template <>
double IniParser::GetValue<double>(const std::string& sectionName, const std::string& param)
throw (ParamException) {
	if (!IsHaveParam(sectionName, param)) {
		throw ParamException(param);
	}
	return stod(data.at(sectionName).at(param));
}