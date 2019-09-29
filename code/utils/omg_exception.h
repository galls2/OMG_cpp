//
// Created by galls2 on 26/09/19.
//

#pragma once
#include <exception>

class OmgException : public std::runtime_error {
public:
    explicit OmgException(const char* message) : std::runtime_error(message) {}
    const char* what() const noexcept override {
        auto base_msg = std::runtime_error::what();
        return base_msg;
    }

};