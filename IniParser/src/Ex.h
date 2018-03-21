#pragma once
#include <exception>
#include <string>

class FileException : public std::exception {
public:
	explicit FileException(const std::string& name) noexcept
		: message("Can't rich file" + name) {
	}

	~FileException() noexcept override = default;

	const char* what() const noexcept override {
		return message.what();
	}

private:
	std::runtime_error message;
};

class SectionException : public std::exception {
public:
	explicit SectionException(const std::string& name) noexcept
		: message("Can't rich section" + name) {
	}

	~SectionException() noexcept override = default;

	const char* what() const noexcept override {
		return message.what();
	}

private:
	std::runtime_error message;
};

class ParamException : public std::exception {
public:
	explicit ParamException(const std::string& name) noexcept
		: message("Can't rich param" + name) {
	}

	~ParamException() noexcept override = default;

	const char* what() const noexcept override {
		return message.what();
	}

private:
	std::runtime_error message;
};

class InitiedException : public std::exception {
public:
	explicit InitiedException(const std::string& name) noexcept
		: message("Wrong type" + name) {
	}

	~InitiedException() noexcept override = default;

	const char* what() const noexcept override {
		return message.what();
	}

private:
	std::runtime_error message;
};

class StreamException : public std::exception {
public:
	explicit StreamException(const std::string& name) noexcept
		: message("Wrong stream" + name) {
	}

	~StreamException() noexcept override = default;

	const char* what() const noexcept override {
		return message.what();
	}

private:
	std::runtime_error message;
};