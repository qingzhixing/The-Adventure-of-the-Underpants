//
// Created by qingzhixing on 24-5-19.
//

#include "types.hpp"
namespace underpants {
    DWORD operator"" _s(long double seconds) {
        return u_int(seconds * 1000);
    }
}// namespace underpants