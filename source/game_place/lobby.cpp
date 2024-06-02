//
// Created by qingzhixing on 24-6-2.
//

#include "lobby.hpp"
#include "../game_management/console.hpp"
#include "../game_management/game_controller.hpp"
#include "../utilities/string_util.hpp"
#include <format>
#include <string>

namespace underpants {
    void Lobby::enter() {
        console.clear_screen();
        console.slow_print("-> Lobby <-", 0, {30, 10}, INTENSITY_CYAN)
                .slow_print("======== Selections ========", 0, {30, 15})
                .slow_print("[i] Game Info.  [e] Exit", 0, {30, 20}, BLUE)
                .slow_print("======== End Selections ========", 0, {30, 25})
                .slow_print_then("Input your choice: ", 0, {30, 30}, YELLOW)
                .set_console_text_attr(DEFAULT)
                .enable_cursor_display(true);

        std::string input;
        getline(std::cin, input);

        console.enable_cursor_display(false);

        input = standardize_string(input);

        if (input == "i") {
            console.clear_screen()
                    .slow_print("-> Game Info <-", 0, {50, 10}, INTENSITY_CYAN)
                    .slow_print("======== Game Info ========", 0, {50, 15})
                    .slow_print(std::format("Game Version: Underpants! %s"), 0, {50, 20})
                    .slow_print("======== End Game Info ========", 0, {50, 25});
        } else if (input == "e") {
            console.clear_screen()
                    .slow_print("Goodbye!", 0, {50, 35}, INTENSITY_YELLOW);
            exit(0);// 使用GameController提供的接口(未定义未实现）
        } else {
            console.slow_print_then("Invalid input!", 0, {30, 35}, RED);
        }
    }
}// namespace underpants