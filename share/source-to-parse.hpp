
#pragma once

// #include <iostream>

namespace XE {
    class Renderer {
    public:

    };


    class Painter {
    public:
        explicit Painter(Renderer *renderer);

        Renderer *renderer = nullptr;

        Renderer* getRenderer() const {
            return renderer;
        }

        void setRenderer(Renderer *renderer);
    };
}
