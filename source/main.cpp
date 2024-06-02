#include "main.hpp"
#include "game_management/game_controller.hpp"
using namespace underpants;


inline static void init() {
    GameController::game_init();
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
    logger.log_msg("Hello, Underpants!", LogLevel::LOG_DEBUG);
    console.clear_screen();

    init();

    GameController::game_loop();

    GameController::game_end();

    return 0;
}