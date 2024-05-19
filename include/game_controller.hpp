//
// Created by qingzhixing on 24-5-19.
//

#ifndef UNDERPANTS_GAME_CONTROLLER_HPP
#define UNDERPANTS_GAME_CONTROLLER_HPP


class GameController {
public:
    static void game_init();
    static void game_update();
    static void game_loop();
    static void game_end();

public:
    static GameController &getInstance();

private:
    // 声明，不分配空间
    static GameController *instance;
    static bool exit_game;
};


#endif//UNDERPANTS_GAME_CONTROLLER_HPP