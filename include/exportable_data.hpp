#pragma once
#ifndef __EXPORTABLE_DATA_HPP_
#define __EXPORTABLE_DATA_HPP_

#include <string>
#include "../lib/include/rapidjson/document.h"

class ExportableData
{
public:
    static std::string data_name;
    virtual rapidjson::Value export_data(rapidjson::Document::AllocatorType &allocator) const
    {
        return rapidjson::Value();
    }
};

#endif // !__EXPORTABLE_DATA_HPP_