//
// Created by qingzhixing on 24-6-2.
//

#include "lobby.hpp"
#include "../game_data/game_info.hpp"
#include "../game_data/global_data_manager.hpp"
#include "../game_management/console.hpp"
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

        console.flush_input_buffer();

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

            if (key_code == 224) {
                const int next_key_code = _getch();

                // Right Arrow
                if (next_key_code == 77) {
                    input_success = true;
                    focus_on_selection++;
                }

                // Left Arrow
                if (next_key_code == 75) {
                    input_success = true;
                    focus_on_selection--;
                }
            }


            // Enter
            if (key_code == 13) {
                input_success = true;
                select_success = true;
            }

            focus_on_selection = focus_on_selection < 0 ? int(selection_list.size() - 1) : focus_on_selection;
            focus_on_selection = focus_on_selection >= int(selection_list.size()) ? 0 : focus_on_selection;

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
    static const Selection player_info_selection{
            "Player Info",

            [](int source_id) -> void {
                static PlayerData &player = global.player_data;
                console.clear_screen()
                        .slow_print("-> Player Info <-", 0, {30, 10}, true, INTENSITY_CYAN)
                        .slow_print("======== Player Info ========", 0, {30, 12})
                        .slow_print(std::format("Name: {0}", player.name), 0, {30, 14}, true, MAGENTA)
                        .slow_print(std::format("Level: {0}", player.level), 0, {30, 15}, true, INTENSITY_BLUE)
                        .slow_print(std::format("Exp: {0}", player.experience), 0, {30, 16}, true, INTENSITY_BLUE)
                        .slow_print(std::format("Blood: {0}/{1}", player.blood, player.max_blood), 0, {30, 17}, true, INTENSITY_BLUE)
                        .slow_print(std::format("Magic: {0}/{1}", player.magic, player.max_magic), 0, {30, 18}, true, INTENSITY_BLUE)
                        .slow_print(std::format("Cleanliness: {0}/{1}", player.cleanliness, player.max_cleanliness), 0, {30, 19}, true, INTENSITY_BLUE)
                        .slow_print(std::format("Attack: {0}", player.attack), 0, {30, 20}, true, INTENSITY_BLUE)
                        .slow_print(std::format("Defense: {0}", player.defense), 0, {30, 21}, true, INTENSITY_BLUE)
                        .slow_print("======== End Player Info ========", 0, {30, 23});
                Sleep(1.5_s);
            },
            "Display Player Character Info",
    };

    Lobby::Lobby() : AbstractPlace("Lobby", "Game Start Menu") {
        selection_list.push_back(player_info_selection);
        selection_list.push_back(game_info_selection);
        selection_list.push_back(exit_selection);
    }
}// namespace underpants