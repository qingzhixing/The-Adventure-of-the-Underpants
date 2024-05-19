//
// Created by qingzhixing on 24-5-19.
//

#pragma once
#ifndef UNDERPANTS_GAME_PLACE_HPP
#define UNDERPANTS_GAME_PLACE_HPP

#include "logger.hpp"
#include <format>
#include <string>
#include <utility>
#include <vector>

std::string trim(const std::string &str);
std::string lower(const std::string &str);

class GamePlace;

typedef void (*SelectionCallback)(const GamePlace &);

struct Selection {
    std::string selection_name;
    std::string keyboard_key;
    SelectionCallback callback;

    Selection(std::string selection_name, const std::string &keyboard_key, SelectionCallback callback) {
        this->selection_name = std::move(selection_name);
        this->keyboard_key = lower(trim(keyboard_key));
        this->callback = callback;
    }

    std::string selection_string() const {
        return std::format("[%s] %s", keyboard_key, selection_name);
    }
};

class GamePlace {
public:
    /**
     * @brief handle input and execute corresponding callback
     * @param keyboard_input selection (can be not trimmed),will be lower cased
     * @return true if handled, false otherwise
     */
    bool handle_selection(const std::string &keyboard_input) const;

public:
    /**
     * @brief display this place
     * @return true if displayed success, false otherwise
     */
    virtual bool display() const {
        logger.flog_msg_error("Called uncompleted func %s at {%s}\n", __func__, place_name.c_str());
        return false;
    }

public:
    std::string place_name = "The Void";
    std::vector<Selection> selections;
    const GamePlace *previous_place;
};


#endif//UNDERPANTS_GAME_PLACE_HPP