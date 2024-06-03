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
        virtual void enter();
    };

}// namespace underpants

#endif//UNDERPANTS_LOBBY_HPP