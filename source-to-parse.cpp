
#include "source-to-parse.hpp"

namespace XE {
    Painter::Painter(Renderer *renderer) {
        // std::cout << "Constructing a Painter!" << std::endl;
        this->setRenderer(renderer);
    }

    void Painter::setRenderer(Renderer *renderer) {
        this->renderer = renderer;
    }
}
