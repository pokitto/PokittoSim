#include "Pokitto.h"

Pokitto::Core game;

int main () {
game.begin();
while (game.isRunning()) {
    if (game.update()) {
        game.display.print("Hello World!");
    }
}

return 1;
}
