/*
#include <gtkmm.h>

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    Gtk::Window window;
    window.set_default_size(200, 200);

    return app->run(window);
}
*/

#include <clang-c/Index.h>

int main(int argc, char *argv[]) {
    CXIndex index = clang_createIndex(0, 0);
    
    return 0;
}