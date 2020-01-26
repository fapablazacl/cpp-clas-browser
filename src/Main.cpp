
#include "MainWindow.hpp"
#include <clang-c/Index.h>

int main(int argc, char *argv[]) {
    CXIndex index = clang_createIndex(0, 0);
    clang_disposeIndex(index);
    
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    ccb::MainWindow window;

    return app->run(window);
}

/*
#include <iostream>
#include <string>
#include <vector>

struct CodeElement {
    std::string kind;
    std::string name;
    std::vector<CodeElement> children;
};


int main(int argc, char *argv[]) {
    // create a Index
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit unit = clang_parseTranslationUnit(index, 0, argv, argc, 0, 0, CXTranslationUnit_None);

    if (! unit) {
        std::cout << "Unable to parse supplied translation unit" << std::endl;

        return EXIT_FAILURE;
    }

    CXCursor cursor = clang_getTranslationUnitCursor(unit);

    clang_visitChildren(cursor, [](CXCursor c, CXCursor parent, CXClientData clientData) {
        std::cout 
            << "Cursor '" <<  (clang_getCString(clang_getCursorSpelling(c))) << "' "
            << "of kind '" << (clang_getCString(clang_getCursorKindSpelling(clang_getCursorKind(c)))) << "'"
            << std::endl;

        std::cout 
            << "Parent Cursor '" <<  (clang_getCString(clang_getCursorSpelling(parent))) << "' "
            << "of kind '" << (clang_getCString(clang_getCursorKindSpelling(clang_getCursorKind(parent)))) << "'"
            << std::endl;

        std::cout << std::endl;

        return CXChildVisit_Continue;
    }, nullptr);

    // 
    // for (unsigned i=0; i<clang_getNumDiagnostics(unit); i++) {
    //     CXDiagnostic diagnostic = clang_getDiagnostic(unit, i);
    //     CXString string = clang_formatDiagnostic(diagnostic, clang_defaultDiagnosticDisplayOptions());
    // 
    //     std::fprintf(stderr, "%s\n", clang_getCString(string));
    // 
    //     clang_disposeString(string);
    // }
    //

    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);

    return 0;
}
*/
