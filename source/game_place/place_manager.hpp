//
// Created by qingzhixing on 24-6-9.
//

#ifndef UNDERPANTS_PLACE_MANAGER_HPP
#define UNDERPANTS_PLACE_MANAGER_HPP

#include "place_extend.hpp"
#include <vector>

namespace underpants {

    typedef std::vector<PlaceExtend> PlaceExtendList;
    class PlaceManager {
    public:
        PlaceManager(const PlaceExtendList *_places);
        PlaceManager(PlaceExtendList &&_places);
        ~PlaceManager() = default;

    private:
        /**
        * @brief 显示与输入的循环
        * @return 是否继续显示
        * */
        bool display_input_loop();

    private:
        PlaceExtendList places;
    };

}// namespace underpants

#endif//UNDERPANTS_PLACE_MANAGER_HPP