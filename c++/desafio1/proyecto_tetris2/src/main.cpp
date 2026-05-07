#include "game.h"
#include <iostream>
using namespace std;

int main() {
    cout << "=========================================================\n";
    cout << "    TETRIS By  nicolas anacona       \n";
    cout << "=========================================================\n\n";

    if (iniciar_juego()) {
        ejecutar_juego();
    }

    destruir_juego();

    cout << "\nGracias por jugar!\n";
    return 0;
}
