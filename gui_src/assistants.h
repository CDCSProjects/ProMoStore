#ifndef ASSISTANTS_H
#define ASSISTANTS_H

#include <gtkmm.h>
#include <gtkmm/filechooser.h>
#include "global_variables.h"


class CreateAssistant : public Gtk::Assistant
{
  public:
        CreateAssistant();
        virtual ~CreateAssistant();

        void get_result(bool& check_state, Glib::ustring& entry_text);
        void create_window();
        void set_labels();
        void set_initial_state();
        void on_assistant_apply();
        std::string m_datadir;
        std::string m_metadir;
        std::string m_data_basename;
        std::string m_meta_basename;
        std::filesystem::path m_meta_basename_woext;
        bool get_recursivescan();
        bool get_includeext();
        bool get_includeprefix();
        int get_dircount();
        int get_charcount();
        bool get_portable();
        std::string get_name();
        std::string get_keycol();
        


    
  private:

        void on_assistant_cancel();
        void on_assistant_close();
        void on_assistant_prepare(Gtk::Widget* widget);
        void on_entry_changed();
        void on_prefix_toggled();
     //   bool on_show_tooltip(int x, int y, bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip>& tooltip);
        
        void on_button_close();

        Gtk::Entry m_entry;


  protected:
    
        void on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog);
        void on_select_folder();
        void on_select_file();
        
        Gtk::Box m_box;
        //intro
        Gtk::Label m_intro;
        
        //summary
        Gtk::Grid m_confirm;
        Gtk::Label m_confirmL1;
        Gtk::Label m_confirmL2;
        
        //source data
        Gtk::Grid m_data;
        Gtk::Label m_dataL;
        Gtk::Label m_datadirL;
        Gtk::Button m_dataB;
        
        Gtk::Label m_scanrecursiveL;
        Gtk::CheckButton m_scanrecursive;
        Gtk::Label m_metaL;
        Gtk::Button m_metaB;
        Gtk::Label m_metafileL;
        
        
        //key preferences
        Gtk::Grid m_key;
        Gtk::Label m_key_descr;
        Gtk::Label m_includeextL;
        Gtk::CheckButton m_includeext;
        Gtk::Label m_dircountL;
        Gtk::SpinButton m_dircount;
        Gtk::Label m_prefixL;
        Gtk::CheckButton m_prefix;
        Gtk::Label m_charcountL;
        Gtk::SpinButton m_charcount;
        Gtk::Label m_keycolL;
        Gtk::Entry m_keycol;
        
        //asset store preferences
        Gtk::Grid m_store;
        Gtk::Label m_portableL;
        Gtk::CheckButton m_portable;
       // Gtk::Tooltip m_portable_TT;
        Gtk::Label m_nameL;
        Gtk::Entry m_name;
        
        Gtk::FileChooserDialog * m_files;
        

        

};
   
class ConfigColumns : public Gtk::TreeModel::ColumnRecord
{
public:
  ConfigColumns()
  { add(namecol);add(datacol);add(metacol);}

  Gtk::TreeModelColumn<Glib::ustring> namecol;
  Gtk::TreeModelColumn<Glib::ustring> datacol;
  Gtk::TreeModelColumn<Glib::ustring> metacol;

};

class OpenAssistant : public Gtk::Assistant
{
  public:
      OpenAssistant();
      virtual ~OpenAssistant();

      void get_result(bool& check_state, Glib::ustring& entry_text);
      void create_window();
      void set_labels();

      std::string m_datadir;
      std::string m_metadir;
      std::string m_data_basename;
      std::string m_meta_basename;
      bool m_data_isdirectory;
    
  private:
      void on_assistant_apply();
      void on_assistant_cancel();
      void on_assistant_close();
      void on_assistant_prepare(Gtk::Widget* widget);
      void on_entry_changed();
      void on_select_import();
      void on_method_selected();
      void on_store_selected();
      Gtk::Entry m_entry;
      int dialog_id; //0: select data store, 1: select meta store
      std::vector<StoreConfig> readConfigsFromXML();
      Glib::RefPtr<Gtk::ListStore> m_storeModel;
      ConfigColumns m_store_config;
      Gtk::TreeView m_store_treeView;


  protected:
      void on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog);
      void on_select_folder();
      void on_select_dir();
      
      Gtk::Box m_box;
      Gtk::Grid m_intro;
      Gtk::Label m_introL;
      Gtk::Grid m_confirm;
      Gtk::Grid m_data;
      Gtk::Grid m_meta;
      Gtk::Label m_dataL;
      Gtk::Label m_datadirL;
      Gtk::Label m_metadirL;
      Gtk::Label m_metaL;
      Gtk::Label m_confirmL1;
      Gtk::Label m_confirmL2;
      Gtk::Button m_dataB;
      Gtk::Button m_data_importB;
      Gtk::Button m_metaB;
      Gtk::FileChooserDialog * m_files;
      Gtk::Label m_methodL;
      Gtk::CheckButton m_method;
};

#endif
