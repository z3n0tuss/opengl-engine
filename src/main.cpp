#include <stdio.h>
#include <cstring>
#include "window/window.hpp"

const int WIDTH = 1600;
const int HEIGHT = 900;

int main(int, char**) {
    Window window{};

    bool windowInitOK = window.initialise(WIDTH, HEIGHT, "Test Window");

    if(!windowInitOK) {
        return 1;
    }

    window.run();

    return 0;
}
