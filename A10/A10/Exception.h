#pragma once
#include <exception>
#include <string>

class ValidationException : public std::exception {
private:
    std::string message;
public:
    explicit ValidationException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class RepositoryException : public std::exception {
private:
    std::string message;
public:
    explicit RepositoryException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};