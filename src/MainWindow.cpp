
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

    void fillTreeModelRow(Gtk::TreeModel::Row &row, MainWindow::ModelColumns &columns, const Person &person) {
        row[columns.m_col_id] = person.id;
        row[columns.m_col_name] = person.name;
    }


    Gtk::TreeModel::Row MainWindow::createTreeRow(Gtk::TreeModel::Row &parent, const Person &person) {
        return {};
    }


    Glib::RefPtr<Gtk::TreeStore> MainWindow::createTreeModel(const std::vector<Person> &persons) {
        Glib::RefPtr<Gtk::TreeStore> refTreeModel = Gtk::TreeStore::create(m_Columns);

        // setup treeview model
        Gtk::TreeModel::Row row = *(refTreeModel->append());
        row[m_Columns.m_col_id] = 1;
        row[m_Columns.m_col_name] = "Billy Bob";

        Gtk::TreeModel::Row childrow = *(refTreeModel->append(row.children()));
        childrow[m_Columns.m_col_id] = 11;
        childrow[m_Columns.m_col_name] = "Billy Bob Junior";

        childrow = *(refTreeModel->append(row.children()));
        childrow[m_Columns.m_col_id] = 12;
        childrow[m_Columns.m_col_name] = "Sue Bob";

        row = *(refTreeModel->append());
        row[m_Columns.m_col_id] = 2;
        row[m_Columns.m_col_name] = "Joey Jojo";

        row = *(refTreeModel->append());
        row[m_Columns.m_col_id] = 3;
        row[m_Columns.m_col_name] = "Rob McRoberts";

        childrow = *(refTreeModel->append(row.children()));
        childrow[m_Columns.m_col_id] = 31;
        childrow[m_Columns.m_col_name] = "Xavier McRoberts";

        return refTreeModel;
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
        m_refTreeModel = this->createTreeModel({});
        m_TreeView.set_model(m_refTreeModel);

        //Add the TreeView's view columns:
        m_TreeView.append_column("ID", m_Columns.m_col_id);
        m_TreeView.append_column("Name", m_Columns.m_col_name);

        //Connect signal:
        m_TreeView.signal_row_activated().connect(sigc::mem_fun(*this, &MainWindow::on_treeview_row_activated) );

        show_all_children();
    }

    MainWindow::~MainWindow() {

    }

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
