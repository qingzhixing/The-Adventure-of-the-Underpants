//
// Created by qingzhixing on 24-6-2.
//

#include "lobby.hpp"
#include "../game_management/console.hpp"
#include "../game_management/game_info.hpp"
#include "../utilities/logger.hpp"
#include "../utilities/types.hpp"
#include <conio.h>
#include <format>
#include <string>

namespace underpants {

    bool Lobby::display_input_loop() {
        if (selection_list.empty()) {
            logger.log_msg("Lobby::display_input_loop() - selection_list is empty!", LogLevel::LOG_ERROR);
            return false;
        }

        const int basic_x = 30;

        console.clear_screen();

        ConsoleCoord cursor_pos = {basic_x, 10};

        console.slow_print("-> " + place_name + " <-", 0, cursor_pos, true, INTENSITY_CYAN);
        cursor_pos.y += 2;
        console.slow_print("======== Selections Start ========", 0, cursor_pos);
        cursor_pos.y += 2;

        // display selections for shading

        int counter = 0;
        static int focus_on_selection = 0;
        for (unsigned long long index = 0; index < selection_list.size(); index++) {
            auto selection = selection_list[index];
            counter++;

            if (counter >= 4) {
                cursor_pos.y += 2;
                cursor_pos.x = basic_x;
                counter = 0;
            }

            int color_attr = TextColorPreset::DEFAULT;
            if (focus_on_selection == index) {
                color_attr = TextColorPreset::INTENSITY_MAGENTA | background_color(TextColorPreset::WHITE);
            }

            console.slow_print(selection.get_display_name(), 0, cursor_pos, true, color_attr);

            cursor_pos.x += int(selection.get_display_name().length() + 4);
        }

        cursor_pos.y += 2;
        cursor_pos.x = basic_x;
        console.slow_print("======== Selections End ========", 0, cursor_pos);

        // waiting for input

        //        FlushConsoleInputBuffer(console.get_std_output());
        while (_kbhit()) {
            _getch();
        }

        bool input_success = false;
        bool select_success = false;
        while (!input_success) {
            if (!_kbhit()) continue;

            /*
             * 获得上下左右键的键值时候，他们是双键值，会返回高八位和低八位的int型数值
             * 下键： key1=224，key2=80；
             * 左键： key1=224，key2=75；
             * 右键： key1=224，key2=77;
             * */

            const int key_code = _getch();

            logger.flog_msg_debug(
                    "Lobby::display_input_loop() - key_code: %d\n",
                    key_code);

            if (key_code == 224) {
                logger.log_msg("Getting next_key_code...\n");
                const int next_key_code = _getch();
                logger.flog_msg_debug("next_key_code: %d\n", next_key_code);

                // Right Arrow
                if (next_key_code == 77) {
                    input_success = true;
                    focus_on_selection++;
                    logger.flog_msg_debug("Right Arrow Detected.\n");
                }

                // Left Arrow
                if (next_key_code == 75) {
                    input_success = true;
                    focus_on_selection--;
                    logger.flog_msg_debug("Left Arrow Detected.\n");
                }
            }


            // Enter
            if (key_code == 13) {
                input_success = true;
                select_success = true;
                logger.flog_msg_debug("Enter Detected.\n");
            }

            focus_on_selection = focus_on_selection < 0 ? int(selection_list.size() - 1) : focus_on_selection;
            focus_on_selection = focus_on_selection >= int(selection_list.size()) ? 0 : focus_on_selection;

            logger.flog_msg_debug("focus_on_selection: %d\n", focus_on_selection);
        }//Lobby::display_input_loop()

        if (select_success) {
            selection_list[focus_on_selection].get_callback()(place_id);
            return false;
        }
        return true;
    }
    void Lobby::enter(std::shared_ptr<AbstractPlace> last_place) {
        while (display_input_loop())
            ;
    }

    static const Selection game_info_selection{
            "Game Info",
            [](int source_id) -> void {
                console.clear_screen()
                        .slow_print("-> Game Info <-", 0, {30, 10}, true, INTENSITY_CYAN)
                        .slow_print("======== Game Info ========", 0, {30, 12})
                        .slow_print(std::format("Game Version: Underpants! {}", GameInfo::version), 0, {30, 14}, true, MAGENTA)
                        .slow_print(std::format("Game Author: {}", GameInfo::author), 0, {30, 16}, true, INTENSITY_BLUE)
                        .slow_print("======== End Game Info ========", 0, {30, 18});
                Sleep(1.5_s);
            },
            "Game Info",
    };

    static const Selection exit_selection{
            "Exit",
            [](int source_id) -> void {
                console.clear_screen()
                        .slow_print("Goodbye!", MID_SPEED, {30, 15}, true, YELLOW);
                Sleep(0.5_s);
                exit(0);
            },
            "Exit",
    };

    Lobby::Lobby() : AbstractPlace("Lobby", "Game Start Menu") {
        selection_list.push_back(game_info_selection);
        selection_list.push_back(exit_selection);
    }
}// namespace underpants