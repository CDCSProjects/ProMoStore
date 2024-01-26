#ifndef CODEWINDOW_H
#define CODEWINDOW_H

#include <gtkmm.h>
#include "global_variables.h"

class ComboBoxColumns : public Gtk::TreeModel::ColumnRecord
{
public:
  ComboBoxColumns()
    { add(col); }

    Gtk::TreeModelColumn<Glib::ustring> col;

};

class CodeWindow : public Gtk::Window
{
    public:
        CodeWindow(SciStore::Storage<> * p_storage);
        ~CodeWindow();
        
    protected:
        SciStore::Storage<> * storage;
        void prepareWindow();
        std::string create_cpp_template(Glib::ustring filter);
        std::string create_python_template(Glib::ustring p_filter);
        std::string create_pytorch_template(Glib::ustring p_filter);
        std::string create_cpp_header();
        std::string create_cpp_end();
        std::string create_cpp_build();
        void on_apply();
        
        Gtk::Grid m_grid;
        
        Gtk::Label m_filterL;
        Gtk::ComboBox m_filter;
        Glib::RefPtr<Gtk::ListStore> m_filterModel;
        ComboBoxColumns m_filter_col;
        
        Gtk::Label m_langToolL;
        Gtk::ComboBox m_langTool;
        Glib::RefPtr<Gtk::ListStore> m_langModel;
        ComboBoxColumns m_lang_col;
        
        Gtk::Button m_apply;
        
        Gtk::Label m_codeL;
        Gtk::TextView m_code;
        Gtk::Box m_codeBox;
        Gtk::ScrolledWindow m_code_scroll_window;
        Glib::RefPtr<Gtk::TextBuffer> m_codeBuffer;
        
        Gtk::Label m_buildL;
        Gtk::TextView m_build;
        Gtk::Box m_buildBox;
        Gtk::ScrolledWindow m_build_scroll_window;
        Glib::RefPtr<Gtk::TextBuffer> m_buildBuffer;
        
        std::string m_assettype = "rocksDB";
        std::string m_metatype = "duckDB";
};

#endif
