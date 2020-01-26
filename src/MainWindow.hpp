
#ifndef __ccb_mainwindow_hpp__
#define __ccb_mainwindow_hpp__

#include <gtkmm.h>

namespace ccb {
    struct CodeElement;

    class MainWindow : public Gtk::ApplicationWindow {
    public:
        MainWindow();

        ~MainWindow();

    private:
        void on_button_quit();

        void on_treeview_row_activated(const Gtk::TreeModel::Path &path, Gtk::TreeViewColumn *column);

    public:
        class ModelColumns : public Gtk::TreeModel::ColumnRecord {
        public:
            ModelColumns() {
                add(m_col_id);
                add(m_col_name);
            }

            Gtk::TreeModelColumn<int> m_col_id;
            Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        };

    private:
        void setupTreeModelRow(Gtk::TreeModel::Row &row, const CodeElement &person);

        void setupTreeModel(const std::vector<CodeElement> &elements);

        void on_file_open();
   
    private:
        ModelColumns m_Columns;

        Gtk::Box m_VBox;
        Gtk::ScrolledWindow m_ScrolledWindow;
        Gtk::TreeView m_TreeView;
        Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;

        Gtk::ButtonBox m_ButtonBox;
        Gtk::Button m_ButtonQuit;
    };
}

#endif
