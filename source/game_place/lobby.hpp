//
// Created by qingzhixing on 24-6-2.
//
#pragma once
#ifndef UNDERPANTS_LOBBY_HPP
#define UNDERPANTS_LOBBY_HPP

#include "abstract_place.hpp"
namespace underpants {

    class Lobby : AbstractPlace {
    public:
        Lobby();

    public:
        void enter(const AbstractPlace *const last_place) override;

    private:
        /**
         * @brief 显示与输入的循环
         * @return 是否继续显示
         * */
        bool display_input_loop();
    };

}// namespace underpants

#endif//UNDERPANTS_LOBBY_HPP