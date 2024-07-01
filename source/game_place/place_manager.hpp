//
// Created by qingzhixing on 24-7-1.
//

#ifndef UNDERPANTS_PLACE_MANAGER_HPP
#define UNDERPANTS_PLACE_MANAGER_HPP
#include "abstract_place.hpp"
#include <memory>

namespace underpants {

    class PlaceManager {
    public:
        explicit PlaceManager(std::shared_ptr<AbstractPlace> place);
        explicit PlaceManager();

    public:
        void HandlePlace();

    private:
        std::shared_ptr<AbstractPlace> currentPlace;
        std::shared_ptr<AbstractPlace> lastPlace;
    };
}// namespace underpants


#endif//UNDERPANTS_PLACE_MANAGER_HPP