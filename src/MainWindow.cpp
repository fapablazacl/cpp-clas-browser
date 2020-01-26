
#include "MainWindow.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <clang-c/Index.h>


namespace ccb {
    typedef std::tuple<int, std::string> CodeElementKey;
    typedef std::map<CodeElementKey, std::vector<CodeElementKey>> CodeElementMap;

    struct CodeElement {
        int id;
        std::string name;
        std::vector<CodeElement> children;
    };

    std::vector<CodeElement> parseCodeElements(const std::string &filePath) {
        const char* argv[] = { "cpp-class-browser", filePath.c_str() };
        const int argc = 2;

        CXIndex index = clang_createIndex(0, 0);
        CXTranslationUnit unit = clang_parseTranslationUnit(index, 0, argv, argc, 0, 0, CXTranslationUnit_None);

        if (! unit) {
            std::cout << "Unable to parse supplied translation unit" << std::endl;
            return {};
        }

        CXCursor cursor = clang_getTranslationUnitCursor(unit);

        std::cout << "Root cursor: " << (clang_getCString(clang_getCursorSpelling(cursor))) << std::endl;
        std::cout << " Of Kind: " << (clang_getCString(clang_getCursorKindSpelling(clang_getCursorKind(cursor)))) << std::endl;
        std::cout << std::endl;

        CodeElementMap codeElementMap;

        clang_visitChildren(cursor, [](CXCursor c, CXCursor parent, CXClientData clientData) {
            auto codeElementMap = reinterpret_cast<CodeElementMap*>(clientData);

            const auto key = CodeElementKey{
                c.kind, 
                clang_getCString(clang_getCursorSpelling(c))
            };

            if (auto it = codeElementMap->find(key); it != codeElementMap->end()) {

            } else {

            }

            /*
            std::cout 
                << "Cursor '" << (clang_getCString(clang_getCursorSpelling(c))) << "' "
                << "of kind '" << (clang_getCString(clang_getCursorKindSpelling(clang_getCursorKind(c)))) << "'"
                << std::endl;

            std::cout 
                << "Parent Cursor '" <<  (clang_getCString(clang_getCursorSpelling(parent))) << "' "
                << "of kind '" << (clang_getCString(clang_getCursorKindSpelling(clang_getCursorKind(parent)))) << "'"
                << std::endl;

            std::cout << std::endl;
            */

            // return CXChildVisit_Continue;

            return CXChildVisit_Recurse;
        }, &codeElementMap);

        
        // for (unsigned i=0; i<clang_getNumDiagnostics(unit); i++) {
        //     CXDiagnostic diagnostic = clang_getDiagnostic(unit, i);
        //     CXString string = clang_formatDiagnostic(diagnostic, clang_defaultDiagnosticDisplayOptions());
        // 
        //     std::fprintf(stderr, "%s\n", clang_getCString(string));
        // 
        //     clang_disposeString(string);
        // }
        
        clang_disposeTranslationUnit(unit);
        clang_disposeIndex(index);

        return {};

        /*
        return {
            CodeElement {
                1, "Billy Bob", {
                    CodeElement{11, "Billy Bob Junior"}, 
                    CodeElement{12, "Sue Bob"}, 
                }
            }, 
            CodeElement {
                2, "Joey Jojo"
            }, 
            CodeElement {
                3, "Rob McRoberts", {
                    CodeElement{31, "Xavier McRoberts"}
                }
            }
        };
        */
    }


    void MainWindow::setupTreeModelRow(Gtk::TreeModel::Row &row, const CodeElement &person) {
        row[m_Columns.m_col_id] = person.id;
        row[m_Columns.m_col_name] = person.name;

        for (const CodeElement &childPerson : person.children) {
            auto childRow = *(m_refTreeModel->append(row.children()));

            this->setupTreeModelRow(childRow, childPerson);
        }
    }


    void MainWindow::setupTreeModel(const std::vector<CodeElement> &persons) {
        m_refTreeModel = Gtk::TreeStore::create(m_Columns);

        for (const CodeElement &person : persons) {
            Gtk::TreeModel::Row row = *(m_refTreeModel->append());

            this->setupTreeModelRow(row, person);
        }

        m_TreeView.set_model(m_refTreeModel);
    }


    MainWindow::MainWindow() 
            : m_VBox(Gtk::ORIENTATION_VERTICAL)
            , m_ButtonQuit("Quit") {
        
        // setup layout
        set_title("C++ Class Browser");
        set_border_width(5);
        set_default_size(400, 400);

        add(m_VBox);

        m_ScrolledWindow.add(m_TreeView);
        m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

        m_VBox.pack_start(m_ScrolledWindow);
        m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

        m_ButtonBox.pack_start(m_ButtonQuit, Gtk::PACK_SHRINK);
        m_ButtonBox.set_border_width(5);
        m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);

        m_ButtonQuit.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_quit));

        //Add the TreeView's view columns:
        m_TreeView.append_column("ID", m_Columns.m_col_id);
        m_TreeView.append_column("Name", m_Columns.m_col_name);

        //Connect signal:
        m_TreeView.signal_row_activated().connect(sigc::mem_fun(*this, &MainWindow::on_treeview_row_activated) );

        show_all_children();

        // remove later
        this->setupTreeModel(parseCodeElements("/home/fapablaza/Desktop/devwarecl/cpp-class-browser/share/source-to-parse.cpp"));
    }


    MainWindow::~MainWindow() {}


    void MainWindow::on_button_quit() {
        hide();
    }


    void MainWindow::on_file_open() {
        auto fileFilter = Gtk::FileFilter::create();
        fileFilter->set_name("Text files");
        fileFilter->add_mime_type("text/plain");

        Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Open", Gtk::RESPONSE_OK);
        dialog.set_transient_for(*this);
        dialog.add_filter(fileFilter);

        int result = dialog.run();

        if (result == Gtk::RESPONSE_OK) {
            const std::string filePath = dialog.get_filename();
            
            //Create the Tree model:
            this->setupTreeModel(parseCodeElements(filePath));
        }
    }


    void MainWindow::on_treeview_row_activated(const Gtk::TreeModel::Path &path, Gtk::TreeViewColumn *column) {
        Gtk::TreeModel::iterator it = m_refTreeModel->get_iter(path);

        if (it) {
            Gtk::TreeModel::Row row = *it;

            std::cout 
                << "Row Activated: " 
                << "ID: '" << row[m_Columns.m_col_id] << "' "
                << "Name '" << row[m_Columns.m_col_name] << "' "
                << std::endl;
        }
    }
}
