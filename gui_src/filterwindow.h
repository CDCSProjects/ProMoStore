#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <gtkmm.h>
#include "global_variables.h"

class TextColumns : public Gtk::TreeModel::ColumnRecord
{
public:
  TextColumns()
    { add(col); }

    Gtk::TreeModelColumn<Glib::ustring> col;

};



class FilterWindow : public Gtk::Window
{

public:
  FilterWindow(SciStore::Storage<> * p_storage);
  ~FilterWindow();

protected:
    
    SciStore::Storage<> * storage;
    std::string m_active_store;
    int rowcounter;

    //Signal handlers:
    void on_button_clicked();
    void on_add_filter();
    void on_attribute_selected(int counter);
    void on_remove_attribute(int counter);
    void on_selection_changed();
    void on_filter_saved();
    void on_filter_selected();
    void on_editing_done(int counter);
    void on_asset_saved();
    
    std::vector<std::string> getFilters();
    std::string buildReadableQuery();
    void prepareWindow();
    std::string buildQuery();
    void update_filter_list();
    
    Gtk::Grid m_grid;
    Gtk::Button m_button_ok;
    Gtk::Button m_button_add;
    Gtk::Label m_attr;
    Gtk::Label m_op;
    Gtk::Label m_value;
    Gtk::Label m_placeholder;
    Gtk::Label m_filternameL;
    Gtk::Label m_newfilternameL;
    Gtk::Label m_filtertextL;
    Gtk::Button m_save;
    Gtk::Entry m_newfiltername;
    Gtk::ComboBox m_filter;
    Glib::RefPtr<Gtk::ListStore> m_filterModel;
    TextColumns m_filter_col;
    
    std::vector<int> m_attr_types; //! We store an ID indicating the type of each attribute in the statement. This wayy we only have to query the type once. 0: numbers, 1: text, 2: not in use, yet
   
    //Elements for constructing the filter mask
    Gtk::Grid m_g;
    std::vector<Gtk::Entry*> m_valueV;
    std::vector<Gtk::Grid*> m_filtergrid;
    std::vector<Gtk::ComboBox*> m_comboV;
    std::vector<Gtk::ComboBox*> m_comboOpV;
    std::vector<Gtk::ComboBox*> m_boolV;
    std::vector<Gtk::Button*> m_removefilterV;
    
    TextColumns m_attr_col;
    TextColumns m_opText_col;
    TextColumns m_opNumber_col;
    TextColumns m_bool_col;
    Glib::RefPtr<Gtk::ListStore> m_attrModel;
    Glib::RefPtr<Gtk::ListStore> m_opModelText;
    Glib::RefPtr<Gtk::ListStore> m_opModelNumber;
    Glib::RefPtr<Gtk::ListStore> m_boolModel;
    
   
    //Elements to show the results
    Gtk::Frame m_assetFrame;
    Gtk::Box m_assetBox;
    
    Gtk::ScrolledWindow m_assets_scrollWindow;
	Gtk::TreeView m_assets_treeView;
	Glib::RefPtr<Gtk::ListStore> m_assets;
    TextColumns m_assets_cols;
    std::vector<std::string> m_results;
    
    //Meta data   
    Gtk::Frame m_Frame2;
    Gtk::Box m_Box2;

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
    
    std::string m_selected_ID;
    std::string m_selected_Extension;
};

#endif
