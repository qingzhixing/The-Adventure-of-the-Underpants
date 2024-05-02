#pragma once
#ifndef __EXPORTABLE_DATA_HPP_
#define __EXPORTABLE_DATA_HPP_

#include "../lib/include/rapidjson/document.h"

using rapidjson::Value;

__interface IExportableData
{
    virtual Value export_data() = 0;
};

#endif // !__EXPORTABLE_DATA_HPP_