
#include "MainWindow.hpp"

#include <iostream>
#include <vector>

namespace ccb {
    struct Person {
        int id;
        std::string name;
        std::vector<Person> children;
    };


    std::vector<Person> getPersons() {
        return {
            Person {
                1, "Billy Bob", {
                    Person{11, "Billy Bob Junior"}, 
                    Person{12, "Sue Bob"}, 
                }

            }, 
            Person {
                2, "Joey Jojo"
            }, 
            Person {
                3, "Rob McRoberts", {
                    Person{31, "Xavier McRoberts"}
                }
            }
        };
    }


    void MainWindow::setupTreeModelRow(Gtk::TreeModel::Row &row, const Person &person) {
        row[m_Columns.m_col_id] = person.id;
        row[m_Columns.m_col_name] = person.name;

        for (const Person &childPerson : person.children) {
            auto childRow = *(m_refTreeModel->append(row.children()));

            this->setupTreeModelRow(childRow, childPerson);
        }
    }


    void MainWindow::setupTreeModel(const std::vector<Person> &persons) {
        m_refTreeModel = Gtk::TreeStore::create(m_Columns);

        for (const Person &person : persons) {
            Gtk::TreeModel::Row row = *(m_refTreeModel->append());

            this->setupTreeModelRow(row, person);
        }

        m_TreeView.set_model(m_refTreeModel);
    }


    MainWindow::MainWindow() 
            : m_VBox(Gtk::ORIENTATION_VERTICAL)
            , m_ButtonQuit("Quit") {
        
        // setup layout
        set_title("");
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

        //Create the Tree model:
        this->setupTreeModel(getPersons());
        
        //Add the TreeView's view columns:
        m_TreeView.append_column("ID", m_Columns.m_col_id);
        m_TreeView.append_column("Name", m_Columns.m_col_name);

        //Connect signal:
        m_TreeView.signal_row_activated().connect(sigc::mem_fun(*this, &MainWindow::on_treeview_row_activated) );

        show_all_children();
    }


    MainWindow::~MainWindow() {}


    void MainWindow::on_button_quit() {
        hide();
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
