#include "main.hpp"

extern GlobalDataManager global;

static PlayerData &player = global.player_data;

static GameSetting &setting = global.game_setting;

extern Console console;

inline static void init() {
    global.load_game_data();
    player.print_data();
    setting.print_data();
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

    console.slow_print("Please enter your name: ", HIGH_SPEED, {30, 8})
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

    console.slow_print("Hello, ", {30, 10})
            .slow_print(player.name, TextColorPreset::INTENSITY_RED)
            .slow_print(" !");
    player.print_data();
    Sleep(1.5_s);
}

inline static void not_first_enter() {

    console.slow_print("underpants!", HIGH_SPEED, {5, 10});
    Sleep(1.5_s);
    console.clear_screen();

    console.slow_print("Hello, ", {30, 10})
            .slow_print(player.name, TextColorPreset::INTENSITY_RED)
            .slow_print(" !")
            .slow_print("Welcome back to Underpants' World!", HIGH_SPEED, {30, 12})
            .slow_print("Now! Start your adventure!", HIGH_SPEED, {30, 16});
    Sleep(1.5_s);
    console.clear_screen();

    HALT();

    Sleep(1.5_s);
}

void handle_args(int argc, const char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Usage: %s [OPTION]\n", argv[0]);
            printf("Options:\n");
            printf("  -h, --help     Show this help message and exit\n");
            printf("  -v, --version  Show version information and exit\n");
            exit(0);
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            printf("Underpants' World v1.0\n");
            exit(0);
        } else {
            printf("Unknown option: %s\n", argv[i]);
            exit(1);
        }
    }
}

int main(int argc, const char **argv) {
    handle_args(argc, argv);
    printf("Hello, Underpants!\n");
    init();

    console.clear_screen();
    //    HALT();

    if (setting.first_enter) {
        first_enter();
        setting.first_enter = false;
        global.save_game_data();
    } else {
        not_first_enter();
    }

    while (true) {
    }
    return 0;
}