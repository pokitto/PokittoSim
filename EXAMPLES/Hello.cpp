#include "Pokitto.h"

Pokitto::Core game;

int main () {
game.begin();
game.display.setFont(fontC64);
while (game.isRunning()) {
    if (game.update()) {
        game.display.print("Hello World!");
    }
}

return 1;
}
