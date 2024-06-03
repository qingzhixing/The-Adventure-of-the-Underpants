//
// Created by qingzhixing on 24-6-3.
//

#ifndef UNDERPANTS_SELECTION_HPP
#define UNDERPANTS_SELECTION_HPP
#include <string>

namespace underpants {
    typedef void (*SelectionCallback)(int selection_id);

    class Selection {
    public:
        Selection(const std::string &display_name, SelectionCallback callback, const std::string &description);
        Selection(const Selection &selection);
        Selection(Selection &&selection) noexcept;

    public:
        [[nodiscard]] const std::string &get_display_name() const;
        void set_display_name(const std::string &displayName);
        [[nodiscard]] const std::string &get_description() const;
        void set_description(const std::string &description);
        [[nodiscard]] int get_selection_id() const;
        [[nodiscard]] SelectionCallback get_callback() const;

    private:
        static int generate_selection_id();

    private:
        int selection_id;
        std::string display_name;
        std::string description;
        SelectionCallback callback;
    };

}// namespace underpants

#endif//UNDERPANTS_SELECTION_HPP