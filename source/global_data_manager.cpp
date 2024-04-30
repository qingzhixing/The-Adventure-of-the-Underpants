#include "global_data_manager.hpp"

#include <iostream>
#include <fstream>
#include "rapidjson/document.h"

using namespace rapidjson;

GlobalDataManager global;

void GlobalDataManager::load_player_data()
{
    printf("Unimplemented: load_player_data\n");
}

void GlobalDataManager::save_player_data()
{
    printf("Unimplemented: save_player_data\n");
    Document doc;
    doc.SetObject();

    // FIXME!
    Value value(kObjectType);
    value.AddMember("Author", "qingzhixing sama!", doc.GetAllocator());

    doc.AddMember("Object", value, doc.GetAllocator());

    FILE *file = fopen("test.json", "w");
    fprintf(file, "%s", doc.GetString());
    fclose(file);
}