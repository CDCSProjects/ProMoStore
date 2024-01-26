#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include <gtkmm/filechooser.h>
#include <pthread.h>
#include "filterwindow.h"
#include "codewindow.h"
#include "global_variables.h"
#include "assistants.h"
#include "helper.h"

using namespace tinyxml2;

class Asset_Columns : public Gtk::TreeModel::ColumnRecord {
	public:
		Asset_Columns() {
			add(col_id);

        } 

		~Asset_Columns() {}

		Gtk::TreeModelColumn<std::string> col_id;
//		Gtk::TreeModelColumn<Glib::ustring> col_name;

};

static struct ThreadArgs{
    SciStore::Storage<> * t_storage;
    CreateAssistant * t_create_assistant;
} ThreadArgsI;

class StoreChoiceWindow : public Gtk::Window
{
    public:
        StoreChoiceWindow();
        ~StoreChoiceWindow();
    
    protected:
        void on_button_clicked();
        void on_button_cancel_clicked();
        
        Gtk::Button m_OkB;
        Gtk::Button m_CancelB;
        Gtk::Button m_InB;
        Gtk::Button m_OutB;
        Gtk::Label m_TextL;
        Gtk::Label m_inL;
        Gtk::Label m_outL;
        Gtk::Label m_dir_inL;
        Gtk::Label m_dir_outL;
        Gtk::Grid m_grid;
        Gtk::FileChooserDialog * m_input;
        Gtk::FileChooserDialog * m_output;
        Gtk::Label m_prefixL;
        Gtk::CheckButton m_prefix;
        Gtk::Label m_charcountL;
        Gtk::SpinButton m_charcount;
        Gtk::Label m_portableL;
        Gtk::CheckButton m_portable;
        Gtk::FileChooserDialog * m_dir_inD;
        Gtk::FileChooserDialog * m_dir_outD;
        Gtk::Label m_nameL;
        Gtk::Entry m_name;
        Gtk::Label m_scanrecursiveL;
        Gtk::CheckButton m_scanrecursive;
        
        std::string m_dir_in;
        std::string m_dir_out;
                
        std::string get_name();
        bool get_recursivescan();
        bool get_includeprefix();
        int get_charcount();
        bool get_portable();
        
        void on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog);
        void on_select_folder_in();
        void on_select_folder_out();
};

class MainWindow : public Gtk::Window
{

public:
  MainWindow();
  virtual ~MainWindow();
  

protected:
    XMLDocument* xmlConfig;
  //Signal handlers:
    void on_button_clicked_select();
    void on_button_clicked_create();
    void on_button_clicked_filter();
    void on_button_clicked_code();
    void on_open_assistant_apply();
    void on_create_assistant_apply();
    void on_selection_changed();
    bool on_timeout();
    void on_asset_saved();
    sigc::connection m_connection_timeout;
    std::string m_active_store;

    //Menu
    Gtk::Grid m_grid_all;
    Gtk::Grid m_grid_menu;
    Gtk::Button m_button_select;
    Gtk::Button m_button_create;
    Gtk::Button m_button_filter;
    Gtk::Button m_button_code;
    Gtk::Button m_button_preferences;
    
    
    Gtk::Grid m_grid_data;//contains all frames
    
    //Asset list
    Gtk::Frame m_Frame1;
    Gtk::Box m_Box1;
    
    Gtk::ScrolledWindow m_assets_scrollWindow;
	Gtk::TreeView m_assets_treeView;
	Glib::RefPtr<Gtk::ListStore> m_assets;
    Asset_Columns m_assets_cols;
    std::vector<std::string> m_asset_list;
        
    //Meta data   
    Gtk::Frame m_Frame2;
    Gtk::Box m_Box2;
    Gtk::Separator m_separator;
    
    Gtk::Label m_info;
    Gtk::ProgressBar m_ProgressBar;
    Gtk::Label m_auto_metaL;
    Gtk::Label m_user_metaL;
    Gtk::Label m_auto_meta;
    Gtk::Label m_user_meta;
    
    Gtk::Separator m_meta_sep;
    
    //Asset preview
    Gtk::Image m_image;
    Gtk::Label m_asset;
    Gtk::Frame m_Frame3;
    Gtk::Box m_Box3;
    Gtk::ScrolledWindow m_scroll_window;
    Gtk::ScrolledWindow m_scroll_window_meta;
    Gtk::Button m_saveAsset;
    Gtk::Label m_assetSaved;

    //The assistants to open and create an asset store   
    OpenAssistant m_open_assistant;
    CreateAssistant m_create_assistant;
    
    FilterWindow * m_filterW;
    CodeWindow * m_codeW;
    
    StoreChoiceWindow* m_importW;
    
    //Some variables to hold states
    int created_open;
    int created_create;
    std::string m_selected_ID;
    std::string m_selected_Extension;

};



#endif
