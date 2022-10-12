#include "GundamException.h"
#include <sstream>

GundamException::GundamException(int line, const char* file) noexcept : line(line), file(file) {}

const char* GundamException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* GundamException::GetType() const noexcept
{
	return "Gundam Exception";
}

const std::string& GundamException::GetFile() const noexcept
{
	return file;
}

std::string GundamException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}