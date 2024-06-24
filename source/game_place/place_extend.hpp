//
// Created by qingzhixing on 24-6-4.
//

#ifndef UNDERPANTS_PLACE_EXTEND_HPP
#define UNDERPANTS_PLACE_EXTEND_HPP

#include "abstract_place.hpp"
namespace underpants {

    // TODO:正在完成继承中，正在写enter等函数来将数据与控制分离
    class PlaceExtend : public AbstractPlace {

    public:
        virtual void enter(const PlaceExtend *last_place);

    protected:
        AbstractPlace *place{};
    };

}// namespace underpants

#endif//UNDERPANTS_PLACE_EXTEND_HPP