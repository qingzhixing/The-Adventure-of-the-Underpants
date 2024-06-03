//
// Created by qingzhixing on 24-6-3.
//

#include "selection.hpp"

namespace underpants {

    Selection::Selection(const std::string &display_name, SelectionCallback callback, const std::string &description) {
        this->display_name = display_name;
        this->description = description;
        this->callback = callback;
        selection_id = generate_new_selection_id();
    }

    Selection::Selection(const Selection &selection) {
        display_name = selection.display_name;
        description = selection.description;
        callback = selection.callback;
        selection_id = generate_new_selection_id();
    }

    Selection::Selection(Selection &&selection) noexcept {
        display_name = std::move(selection.display_name);
        description = std::move(selection.description);
        callback = selection.callback;
        selection_id = selection.get_selection_id();
    }

    Selection &Selection::operator=(const Selection &selection) {
        display_name = selection.display_name;
        description = selection.description;
        callback = selection.callback;
        selection_id = generate_new_selection_id();
        return *this;
    }

    Selection &Selection::operator=(Selection &&selection) noexcept {
        display_name = std::move(selection.display_name);
        description = std::move(selection.description);
        callback = selection.callback;
        selection_id = selection.get_selection_id();
        return *this;
    }

    int Selection::generate_new_selection_id() {
        static int id_counter = 0;
        return id_counter++;
    }

    const std::string &Selection::get_display_name() const {
        return display_name;
    }

    void Selection::set_display_name(const std::string &displayName) {
        display_name = displayName;
    }

    const std::string &Selection::get_description() const {
        return description;
    }

    void Selection::set_description(const std::string &description) {
        Selection::description = description;
    }
    int Selection::get_selection_id() const {
        return selection_id;
    }
    SelectionCallback Selection::get_callback() const {
        return callback;
    }
}// namespace underpants