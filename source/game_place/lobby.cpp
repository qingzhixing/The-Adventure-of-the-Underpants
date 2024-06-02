//
// Created by qingzhixing on 24-6-2.
//

#include "lobby.hpp"
#include "../game_management/console.hpp"
#include "../game_management/game_info.hpp"
#include "../utilities/string_util.hpp"
#include "../utilities/types.hpp"
#include <format>
#include <string>

namespace underpants {
    void Lobby::enter() {
        console.clear_screen();
        console.slow_print("-> Lobby <-", 0, {30, 10}, true, INTENSITY_CYAN)
                .slow_print("======== Selections ========", 0, {30, 12})
                .slow_print("[i] Game Info.  [e] Exit", 0, {30, 14}, true, BLUE)
                .slow_print("======== End Selections ========", 0, {30, 16})
                .slow_print_then("Input your choice: ", 0, {30, 18}, YELLOW)
                .set_console_text_attr(DEFAULT)
                .enable_cursor_display(true);

        std::string input;
        getline(std::cin, input);

        console.enable_cursor_display(false);

        input = standardize_string(input);

        if (input == "i") {
            console.clear_screen()
                    .slow_print("-> Game Info <-", 0, {30, 10}, true, INTENSITY_CYAN)
                    .slow_print("======== Game Info ========", 0, {30, 12})
                    .slow_print(std::format("Game Version: Underpants! {}", GameInfo::version), 0, {30, 14}, true, MAGENTA)
                    .slow_print(std::format("Game Author: {}", GameInfo::author), 0, {30, 16}, true, INTENSITY_BLUE)
                    .slow_print("======== End Game Info ========", 0, {30, 18});
            Sleep(1.5_s);
        } else if (input == "e") {
            console.clear_screen()
                    .slow_print("Goodbye!", MID_SPEED, {30, 15}, true, YELLOW);
            Sleep(0.5_s);
            exit(0);// 使用GameController提供的接口(未定义未实现）
        } else {
            console.slow_print_then("Invalid input!", 0, {30, 19}, RED);

            Sleep(0.5_s);
        }
    }
}// namespace underpants