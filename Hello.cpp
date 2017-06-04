#include "Pokitto.h"

Pokitto::Core game;

int main () {
game.begin();
game.display.loadRGBPalette(paletteCGA);
game.display.setFont(fontAdventurer);
game.display.persistence = true;
while (game.isRunning()) {

    if (game.update()) {
        game.display.color=random(2)+1;
        game.display.setCursor(random(game.display.width),random(game.display.height));
        game.display.print("Hello World!");
    }

}

return 1;
}
