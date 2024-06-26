#pragma once
#ifndef GAME_SETTING_HPP_
#define GAME_SETTING_HPP_

#include "../utilities/debug.hpp"
#include "exportable_data.hpp"

#define SKIP_LEADING true

namespace underpants {

    class GameSetting : public ExportableData {
    public:
        GameSetting();

    public:
        rapidjson::Value export_data(rapidjson::Document::AllocatorType &allocator) const override;
        void import_data(const rapidjson::Value &object_data) override;
        void log_data() const override;

    public:
        bool first_enter = true;
        bool is_debug = DEBUG_ENABLED;
        bool skip_leading = SKIP_LEADING;
    };
}// namespace underpants

#endif// !GAME_SETTING_HPP_