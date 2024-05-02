#pragma once
#ifndef __EXPORTABLE_DATA_HPP_
#define __EXPORTABLE_DATA_HPP_

#include "../lib/include/rapidjson/document.h"

class ExportableData
{
public:
    virtual rapidjson::Value export_data(rapidjson::CrtAllocator &allocator) const = 0;
};

#endif // !__EXPORTABLE_DATA_HPP_