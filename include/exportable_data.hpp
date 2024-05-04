#pragma once
#ifndef EXPORTABLE_DATA_HPP_
#define EXPORTABLE_DATA_HPP_

#include "../lib/include/rapidjson/document.h"
#include <iostream>
#include <string>
#include <utility>

class ExportableData {
public:
    explicit ExportableData(std::string data_name) : data_name(std::move(data_name)) {}

public:
    std::string data_name;

    virtual rapidjson::Value export_data(rapidjson::Document::AllocatorType &allocator) const {
        printf("%s: export_data() is not implemented\n", data_name.c_str());
        return {};
    }

    virtual void import_data(const rapidjson::Value &object_data) {
        printf("%s: import_data() is not implemented\n", data_name.c_str());
    }

    virtual void print_data() const {
        printf("%s: print_data() is not implemented\n", data_name.c_str());
    }

    rapidjson::Value get_data_name_value(rapidjson::Document::AllocatorType &allocator) const {
        rapidjson::Value name_value;
        name_value.SetString(data_name.c_str(), data_name.length(), allocator);
        return name_value;
    }
};

inline const char *bool_2_string(bool value) {
    return value ? "TRUE" : "FALSE";
}

#define MEMBER_2_STR(member) #member

#define PARSE_STRING_VALUE(member)                                                 \
    do {                                                                           \
        if (object_data.HasMember(MEMBER_2_STR(member))) {                         \
            member = object_data[MEMBER_2_STR(member)].GetString();                \
        } else {                                                                   \
            DEBUG(printf("parse string value %s failed\n", MEMBER_2_STR(member))); \
            member = "undefined";                                                  \
        }                                                                          \
    } while (0)

#define PARSE_INT_VALUE(member)                                                 \
    do {                                                                        \
        if (object_data.HasMember(MEMBER_2_STR(member))) {                      \
            member = object_data[MEMBER_2_STR(member)].GetInt();                \
        } else {                                                                \
            member = -1;                                                        \
            DEBUG(printf("parse int value %s failed\n", MEMBER_2_STR(member))); \
        }                                                                       \
    } while (0)

#define PARSE_BOOL_VALUE(member)                                                 \
    do {                                                                         \
        if (object_data.HasMember(MEMBER_2_STR(member))) {                       \
            member = object_data[MEMBER_2_STR(member)].GetBool();                \
        } else {                                                                 \
            DEBUG(printf("parse bool value %s failed\n", MEMBER_2_STR(member))); \
            member = false;                                                      \
        }                                                                        \
    } while (0)

#endif// !EXPORTABLE_DATA_HPP_