//
// Created by qingzhixing on 24-6-3.
//

#include "abstract_place.hpp"

#include <utility>

namespace underpants {
    AbstractPlace::AbstractPlace(const std::string &place_name, const std::string &description) {
        this->place_name = place_name;
        this->description = description;
        place_id = generate_new_place_id();
    }

    AbstractPlace::AbstractPlace(const AbstractPlace &other) {
        place_name = other.place_name;
        description = other.description;
        place_changed = false;
        next_place = nullptr;
        selection_list.assign(other.selection_list.begin(), other.selection_list.end());
        place_id = generate_new_place_id();
    }

    AbstractPlace::AbstractPlace(AbstractPlace &&other) noexcept {
        place_name = std::move(other.place_name);
        description = std::move(other.description);
        place_changed = false;
        next_place = nullptr;
        selection_list.swap(other.selection_list);
        place_id = other.get_place_id();
    }

    AbstractPlace &AbstractPlace::operator=(const AbstractPlace &other) {
        if (this == &other) return *this;
        place_name = other.place_name;
        description = other.description;
        place_changed = false;
        place_id = generate_new_place_id();
        return *this;
    }

    AbstractPlace &AbstractPlace::operator=(AbstractPlace &&other) noexcept {
        place_name = std::move(other.place_name);
        description = std::move(other.description);
        place_changed = false;
        place_id = other.get_place_id();
        return *this;
    }

    void AbstractPlace::goto_place(const AbstractPlace &place) {
        next_place.reset(&place);
        place_changed = true;
    }

    int AbstractPlace::generate_new_place_id() {
        static int place_id_counter = 0;
        return place_id_counter++;
    }

    const std::string &AbstractPlace::get_place_name() const {
        return place_name;
    }

    void AbstractPlace::set_place_name(const std::string &name) {
        this->place_name = name;
    }

    const std::string &AbstractPlace::get_description() const {
        return description;
    }

    void AbstractPlace::set_description(const std::string &_description) {
        AbstractPlace::description = _description;
    }

    bool AbstractPlace::is_place_changed() const {
        return place_changed;
    }
    void AbstractPlace::set_place_changed(bool changed) {
        place_changed = changed;
    }
    PlacePtr AbstractPlace::get_next_place() const {
        return next_place;
    }
    void AbstractPlace::set_next_place(const AbstractPlace &place) {
        next_place.reset(&place);
    }
    int AbstractPlace::get_place_id() const {
        return place_id;
    }
    const SelectionList &AbstractPlace::get_selection_list() const {
        return selection_list;
    }
}// namespace underpants