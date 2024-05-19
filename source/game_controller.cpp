//
// Created by qingzhixing on 24-5-19.
//

#include "game_controller.hpp"
#include "console.hpp"
#include "game_data/game_setting.hpp"
#include "game_data/global_data_manager.hpp"
#include "game_data/player_data.hpp"
#include "game_place/game_place_lobby.hpp"
#include "game_place/game_place_manager.hpp"
#include "types.hpp"

static PlayerData &player = global.player_data;

static GameSetting &setting = global.game_setting;

static GamePlaceManager place_manager;

extern Console console;

// 定义，分配空间
GameController *GameController::instance;
bool GameController::exit_game;

GameController &GameController::getInstance() {
    if (instance == nullptr) {
        instance = new GameController();
    }
    return *instance;
}


inline static void first_enter() {
    /**
        @brief: loading into game
    */
    console.slow_print("underpants!", MID_SPEED, {5, 10})
            .slow_print("I used wanna use Chinese but failed, anyway.", HIGH_SPEED, {5, 11});
    Sleep(1.5_s);
    console.clear_screen();

    /**
        @brief: Introduction
    */
    console.slow_print("Welcome to Underpants' World!", LOW_SPEED, {30, 8})
            .slow_print("You are an UNDERPANTS, the resident of this world.", MID_SPEED, {25, 10})
            .slow_print("You are selected to gain the EVOLUTION.", MID_SPEED, {30, 12})
            .slow_print("Now! Start your adventure!", HIGH_SPEED, {30, 15});
    Sleep(1.5_s);
    console.clear_screen();

    /**
     * @brief Get Player Data
     */

    console.slow_print_then("Please enter your name: ", HIGH_SPEED, {30, 8})
            .set_console_text_attr(TextColorPreset::INTENSITY_YELLOW);

    /**
     * @brief read a line of name
     */
    std::getline(std::cin, player.name);
    console.set_console_text_attr(TextColorPreset::DEFAULT);

    /**
     * @brief save data
    */
    global.save_game_data();

    console.slow_print_then("Hello, ", {30, 10})
            .slow_print_then(player.name, TextColorPreset::INTENSITY_RED)
            .slow_print(" !");
    player.log_data();
    Sleep(1.5_s);
}

inline static void not_first_enter() {

    console.slow_print("underpants!", HIGH_SPEED, {5, 10});
    Sleep(1.5_s);
    console.clear_screen();

    console.slow_print_then("Hello, ", {30, 10})
            .slow_print_then(player.name, TextColorPreset::INTENSITY_RED)
            .slow_print(" !")
            .slow_print("Welcome back to Underpants' World!", HIGH_SPEED, {30, 12})
            .slow_print("Now! Start your adventure!", HIGH_SPEED, {30, 16});
    Sleep(1.5_s);

    console.clear_screen();
}

inline void game_place_manager_init() {
    GamePlacePtr lobby(new GamePlaceLobby());
    place_manager.runtime_player_pos_place = lobby->place_name;

    place_manager.game_places.push_back(std::move(lobby));
}

void GameController::game_init() {
    game_place_manager_init();

    global.load_game_data();
    player.log_data();
    setting.log_data();

    if (setting.first_enter) {
        first_enter();
        setting.first_enter = false;
        global.save_game_data();
    } else {
        not_first_enter();
    }
    exit_game = false;
}

void GameController::game_update() {
    if (!place_manager.display_game_place()) {
        exit_game = true;
        logger.flog_msg_fatal("Game Place Display Failed!!!!!\n");
        console.set_console_cur_pos(0, 0);
        console.set_console_text_attr(TextColorPreset::INTENSITY_RED);
        for (int i = 1; i <= 10; i++) {
            printf("[PANIC]!!! Game Place Display Failed !!!\n");
        }
        Sleep(3.0_s);
        return;
    }
    place_manager.handle_input();
}

void GameController::game_end() {
    logger.flog_msg_info("Game End");
    console.clear_screen();
    console.slow_print_then("Goodbye, ", {30, 10})
            .slow_print_then(player.name, TextColorPreset::INTENSITY_BLUE)
            .slow_print(" !");
    Sleep(1.5_s);
}

void GameController::game_loop() {
    while (!exit_game) {
        game_update();
    }
}