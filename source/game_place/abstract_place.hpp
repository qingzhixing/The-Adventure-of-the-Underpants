//
// Created by qingzhixing on 24-6-3.
//

#ifndef UNDERPANTS_ABSTRACT_PLACE_HPP
#define UNDERPANTS_ABSTRACT_PLACE_HPP
#include "selection.hpp"
#include <memory>
#include <string>
#include <vector>

namespace underpants {

    class AbstractPlace {
    public:
        // constructors & destructor
        AbstractPlace(const std::string &place_name, const std::string &description);
        AbstractPlace(const AbstractPlace &other);
        AbstractPlace(AbstractPlace &&other) noexcept;
        AbstractPlace &operator=(const AbstractPlace &other);
        AbstractPlace &operator=(AbstractPlace &&other) noexcept;

        virtual ~AbstractPlace() = default;

    public:
        // getter & setter
        [[nodiscard]] const std::string &get_place_name() const;
        void set_place_name(const std::string &name);
        [[nodiscard]] bool is_place_changed() const;
        [[nodiscard]] const std::string &get_description() const;
        void set_description(const std::string &_description);
        void set_next_place(AbstractPlace &place);
        [[nodiscard]] std::shared_ptr<AbstractPlace> get_next_place();
        void set_place_changed(bool changed);
        [[nodiscard]] int get_place_id() const;

    public:
        virtual void enter(std::shared_ptr<AbstractPlace> last_place);

    protected:
        /**
         *
         * @brief 前往下一个地点
         * @param place 下一个地点
         * @note 与PlaceManager通信，基于place_changed改变和get_next_place().
         */
        void goto_place(AbstractPlace &place);
        static int generate_new_place_id();

    protected:
        int place_id;
        std::string place_name;
        std::string description;
        std::vector<Selection> selection_list = {};
        bool place_changed = false;
        std::shared_ptr<AbstractPlace> next_place = nullptr;
    };

}// namespace underpants

#endif//UNDERPANTS_ABSTRACT_PLACE_HPP