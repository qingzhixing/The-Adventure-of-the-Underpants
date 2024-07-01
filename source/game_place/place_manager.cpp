//
// Created by qingzhixing on 24-7-1.
//

#include "place_manager.hpp"

#include <utility>
namespace underpants {
    PlaceManager::PlaceManager(std::shared_ptr<AbstractPlace> place) {
        currentPlace = std::move(place);
        lastPlace = currentPlace;
    }
    void PlaceManager::HandlePlace() {
        if (currentPlace == nullptr) return;
        do {
            currentPlace->enter(lastPlace);
            if (currentPlace->is_place_changed()) {
                auto newPlace = currentPlace->get_next_place();
                if (newPlace == nullptr)
                    throw std::runtime_error("currentPlace->get_next_place() returns a nullptr");

                lastPlace = currentPlace;
                currentPlace = std::move(newPlace);
            }
        } while (true);
    }
    PlaceManager::PlaceManager() : PlaceManager(nullptr) {
    }
}// namespace underpants