#include "mainwindow.h"
#include <iostream>

std::vector<std::string> FilterWindow::getFilters(){
    
    std::vector<std::string> filternames = storage->get_all_filters();
    
    filternames.insert(filternames.begin(), "<new filter>");
    
    return filternames;
}

std::string FilterWindow::buildQuery(){
    std::stringstream query;
    
    query << (*(m_comboV[0]->get_active()))[m_attr_col.col] << " ";
    switch(m_attr_types[0]){    
        case 0: query << (*(m_comboOpV[0]->get_active()))[m_opNumber_col.col] << " " << m_valueV[0]->get_text() << " "; break;
        case 1: {
                if ((*(m_comboOpV[0]->get_active()))[m_opText_col.col] == "equals") 
                    query << " = '" << m_valueV[0]->get_text() << "' "; 
                if ((*(m_comboOpV[0]->get_active()))[m_opText_col.col] == "contains") 
                    query << " LIKE '%" << m_valueV[0]->get_text() << "%' "; 
                if ((*(m_comboOpV[0]->get_active()))[m_opText_col.col] == "starts with") 
                    query << " LIKE '" << m_valueV[0]->get_text() << "%' ";  
                if ((*(m_comboOpV[0]->get_active()))[m_opText_col.col] == "ends with") 
                    query << " LIKE '%" << m_valueV[0]->get_text() << "' "; 
                if ((*(m_comboOpV[0]->get_active()))[m_opText_col.col] == "is not equal") 
                    query << " != '" << m_valueV[0]->get_text() << "' "; 
                break;
                }
    }
    
    for (int i=1; i < m_comboV.size(); i++){
        query << (*(m_boolV[i-1]->get_active()))[m_attr_col.col] << " ";
        query << (*(m_comboV[i]->get_active()))[m_attr_col.col] << " ";
        switch(m_attr_types[i]){    
            case 0: query << (*(m_comboOpV[i]->get_active()))[m_opNumber_col.col] << " " << m_valueV[i]->get_text() << " "; break;
            case 1: {
                    if ((*(m_comboOpV[i]->get_active()))[m_opText_col.col] == "equals") 
                        query << " = '" << m_valueV[i]->get_text() << "' "; 
                    if ((*(m_comboOpV[i]->get_active()))[m_opText_col.col] == "contains") 
                        query << " LIKE '%" << m_valueV[i]->get_text() << "%' "; 
                    if ((*(m_comboOpV[i]->get_active()))[m_opText_col.col] == "starts with") 
                        query << " LIKE '" << m_valueV[i]->get_text() << "%' ";  
                    if ((*(m_comboOpV[i]->get_active()))[m_opText_col.col] == "ends with") 
                        query << " LIKE '%" << m_valueV[i]->get_text() << "' "; 
                    if ((*(m_comboOpV[0]->get_active()))[m_opText_col.col] == "is not equal") 
                        query << " != '" << m_valueV[0]->get_text() << "' "; 
                    break;
                    }
            }
    }

    return query.str();
}

std::string FilterWindow::buildReadableQuery(){
    std::stringstream query;
       
    query << (*(m_comboV[0]->get_active()))[m_attr_col.col] << " " << (*(m_comboOpV[0]->get_active()))[m_opNumber_col.col] << " " << m_valueV[0]->get_text() << std::endl;
    
    for (int i=1;i<m_comboV.size();i++){
        query << (*(m_boolV[i-1]->get_active()))[m_attr_col.col] << " " << (*(m_comboV[i]->get_active()))[m_attr_col.col] << " " << (*(m_comboOpV[i]->get_active()))[m_opNumber_col.col] << " " << m_valueV[i]->get_text() << std::endl;
    }

    return query.str();
}

void FilterWindow::update_filter_list(){
    std::vector<std::string> filters = getFilters();
    
    
    m_filterModel->clear();
    Gtk::TreeModel::Row rowfilter;
    for (int i=0; i<filters.size(); i++){
        rowfilter = *(m_filterModel->append());
        rowfilter[m_filter_col.col]=filters[i];
    }
    m_filter.set_model(m_filterModel);
    m_filter.pack_start(m_filter_col.col);
}

void FilterWindow::on_filter_saved(){
    std::string name = m_newfiltername.get_text();
    storage->store_filter(buildQuery(), name, buildReadableQuery());
 //   update_filter_list();
}

void FilterWindow::on_filter_selected(){
    std::stringstream fname;
    fname << (*(m_filter.get_active()))[m_filter_col.col];
    
    if ((*(m_filter.get_active()))[m_filter_col.col] == "<new filter>"){
        m_button_add.set_sensitive(true);
        m_save.set_sensitive(true);
        m_filtertextL.set_label("");
    }else{
        m_button_add.set_sensitive(false);
        std::string text=storage->get_filter_text(fname.str());
        m_filtertextL.set_label(text);
        m_button_ok.set_sensitive(true);
        m_save.set_sensitive(false);
    }
    
}

void FilterWindow::on_asset_saved(){

    storage->get(m_selected_ID, 1, m_selected_Extension, 1, ".txt");
    m_assetSaved.override_color (Gdk::RGBA("green"), Gtk::STATE_FLAG_NORMAL);
    m_assetSaved.set_label("Saved");
}

void FilterWindow::prepareWindow(){
// Sets the border width of the window.
    set_border_width(10);

    m_button_ok.add_label("Apply filter");
    m_button_add.add_label("+ Add constraint");
  //  m_button_add.set_markup("<b>+</b>");
    m_attr.set_label("Attribute");
    m_op.set_label("");
    m_value.set_label("Value");
    m_button_ok.signal_clicked().connect(sigc::mem_fun(*this, &FilterWindow::on_button_clicked));
    m_button_add.signal_clicked().connect(sigc::mem_fun(*this, &FilterWindow::on_add_filter));
    m_placeholder.set_label("\t");

    add(m_grid);
    
    std::vector<std::string> filters = getFilters();

    Gtk::TreeModel::Row rowfilter;
    m_filterModel = Gtk::ListStore::create(m_filter_col);
    for (int i=0; i<filters.size(); i++){
        rowfilter = *(m_filterModel->append());
        rowfilter[m_filter_col.col]=filters[i];
    }
    m_filter.set_model(m_filterModel);
    m_filter.pack_start(m_filter_col.col);
    
    m_filternameL.set_label("Filter: ");
    m_grid.add(m_filternameL);
    m_grid.add(m_filter);
    m_filter.signal_changed().connect(sigc::mem_fun(*this, &FilterWindow::on_filter_selected));

    m_filtertextL.set_line_wrap(true);
    m_filtertextL.set_halign(Gtk::ALIGN_CENTER);
    m_filtertextL.set_margin_top(10);
    m_grid.attach_next_to(m_filtertextL,m_filternameL,Gtk::POS_BOTTOM,3,1);
    
    m_grid.attach_next_to(m_placeholder,m_filtertextL,Gtk::POS_BOTTOM);
    m_button_add.set_margin_top(10);
    m_grid.attach_next_to(m_button_add,m_placeholder,Gtk::POS_BOTTOM);
    m_button_ok.set_margin_top(10);
    m_grid.attach_next_to(m_button_ok,m_button_add,Gtk::POS_RIGHT);
    m_button_add.set_sensitive(false);
    m_button_ok.set_sensitive(false);
    
    //Models for the ComboBoxes
    
    std::vector<std::string> tablenames=storage->meta_store->get_all_meta_tables();
    std::vector<std::string> formentries;
    //find all meta tables and their attributes
    for (int i=0;i<tablenames.size();i++){
        //if (tablenames[i]!="metadata"){
            storage->meta_store->execQuery("SELECT idcolname FROM metainfo WHERE tablename='" + tablenames[i] + "'");
            std::vector<std::string> cols=storage->meta_store->get_user_meta_column_names(tablenames[i]);    
            for (int j=0; j<cols.size(); j++){
                formentries.push_back(tablenames[i]+"."+cols[j]);      
            }
    }
    
    
    m_attrModel = Gtk::ListStore::create(m_attr_col);
    //std::vector<std::string> m_attr_list = this->storage->meta_store->get_user_meta_column_names();
    Gtk::TreeModel::Row row;
    for (int i=0; i<formentries.size();i++){
        row = *(m_attrModel->append());
        //row[m_attr_col.col]=m_attr_list[i];
        row[m_attr_col.col]=formentries[i];
    }
    
    m_opModelText = Gtk::ListStore::create(m_opText_col);
    std::vector<std::string> m_opText_list;
    m_opText_list.push_back("equals");
    m_opText_list.push_back("contains");
    m_opText_list.push_back("starts with");
    m_opText_list.push_back("ends with");
    m_opText_list.push_back("is not equal");
    for (int i=0; i<m_opText_list.size();i++){
        row = *(m_opModelText->append());
        row[m_opText_col.col]=m_opText_list[i];
    }    
    
    m_opModelNumber = Gtk::ListStore::create(m_opNumber_col);
    std::vector<std::string> m_opNumber_list;
    m_opNumber_list.push_back("==");
    m_opNumber_list.push_back("!=");
    m_opNumber_list.push_back("<");
    m_opNumber_list.push_back(">");
    m_opNumber_list.push_back("<=");
    m_opNumber_list.push_back(">=");
    m_opNumber_list.push_back("between");
    for (int i=0; i<m_opNumber_list.size();i++){
        row = *(m_opModelNumber->append());
        row[m_opNumber_col.col]=m_opNumber_list[i];
    }  
    
    m_boolModel = Gtk::ListStore::create(m_bool_col);
    std::vector<std::string> m_bool_list;
    m_bool_list.push_back("AND");
    m_bool_list.push_back("OR");
    for (int i=0; i<m_bool_list.size();i++){
        row = *(m_boolModel->append());
        row[m_bool_col.col]=m_bool_list[i];
    } 
    
    m_newfiltername.set_margin_top(10);
    m_grid.attach_next_to(m_newfiltername, m_button_add, Gtk::POS_BOTTOM);
    m_save.add_label("Save filter");
    m_save.set_margin_top(10);
    m_grid.attach_next_to(m_save,m_newfiltername,Gtk::POS_RIGHT);
    
    m_assetBox.set_border_width(10);
    m_assetFrame.set_margin_top(10);
    m_assetFrame.set_margin_end(10);
    m_assetFrame.set_label("Results");
    m_assetFrame.set_label_align(0.02);     

    
    //List with assets
    m_assets_treeView.set_model(m_assets = Gtk::ListStore::create(m_assets_cols));
    m_assets_treeView.append_column("Asset ID", m_assets_cols.col);
    m_assets_treeView.signal_cursor_changed().connect(sigc::mem_fun(*this, &FilterWindow::on_selection_changed));
    m_assets_scrollWindow.add(m_assets_treeView);
	m_assets_scrollWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    
    m_assets_scrollWindow.set_min_content_width(300);
    m_assets_scrollWindow.set_min_content_height(300);
    m_assetBox.add(m_assets_scrollWindow);
    
    m_assetFrame.add(m_assetBox);
    
    m_Box2.set_border_width(10);
    m_Frame2.set_margin_top(10);
    m_Frame2.set_margin_end(10);
    m_Frame2.set_label("Meta Data");
    m_Frame2.set_label_align(0.02);
    m_Frame2.add(m_Box2);
    
    m_Box2.set_orientation(Gtk::ORIENTATION_VERTICAL);
    m_Box2.set_valign(Gtk::ALIGN_FILL);
    m_Box2.set_halign(Gtk::ALIGN_START);
    m_Box2.add(m_auto_metaL);
    m_auto_metaL.set_label("Auto-Detected");
    m_auto_metaL.set_markup("<b>Auto-Detected</b>");
    m_Box2.add(m_auto_meta);
    m_Box2.add(m_meta_sep);
    m_user_metaL.set_label("User-Defined");
    m_user_metaL.set_markup("<b>User-Defined</b>");
    m_Box2.add(m_user_metaL);
    m_Box2.add(m_scroll_window_meta);
    m_scroll_window_meta.add(m_user_meta);

    m_auto_meta.set_halign(Gtk::ALIGN_START);
    m_user_meta.set_halign(Gtk::ALIGN_START);

    m_user_metaL.set_margin_top(10);
    
    m_Box3.set_border_width(10);
    m_Frame3.set_margin_top(10);
    m_Frame3.set_label("Preview");
    m_Frame3.set_label_align(0.02);
    m_Frame3.add(m_Box3);
    m_Box3.add(m_image);
    m_Box3.add(m_scroll_window);
    m_scroll_window.add(m_asset);
    
    m_save.signal_clicked().connect(sigc::mem_fun(*this, &FilterWindow::on_filter_saved));
    m_grid.attach_next_to(m_Frame2, m_save, Gtk::POS_BOTTOM, 2, 1);
    m_grid.attach_next_to(m_Frame3, m_Frame2, Gtk::POS_BOTTOM, 2, 1);
    m_grid.attach_next_to(m_assetFrame, m_Frame2, Gtk::POS_LEFT, 1, 2);
    
  //  m_grid.attach_next_to(m_saveAsset, m_Frame3, Gtk::POS_BOTTOM);
  //  m_grid.attach_next_to(m_saveAsset, m_Box3, Gtk::POS_BOTTOM);
    m_grid.attach_next_to(m_saveAsset,m_assetFrame,Gtk::POS_BOTTOM);
    m_assetSaved.set_label("    ");
    m_grid.attach_next_to(m_assetSaved,m_saveAsset, Gtk::POS_BOTTOM);

    m_saveAsset.set_sensitive(false);
    m_saveAsset.set_label("Save Asset");
    m_saveAsset.set_margin_top(10);
    m_saveAsset.signal_clicked().connect(sigc::mem_fun(*this, &FilterWindow::on_asset_saved));
    m_saveAsset.set_border_width(10);
    m_selected_ID = "";
    m_selected_Extension = "";
}

FilterWindow::FilterWindow(SciStore::Storage<> * p_storage)

{
    rowcounter=0;
    this->storage = p_storage;
    prepareWindow();
    show_all_children();
}


FilterWindow::~FilterWindow()
{
}

void FilterWindow::on_button_clicked()
{
    std::stringstream fname;
    fname << (*(m_filter.get_active()))[m_filter_col.col];

    
    if ( fname.str() == "<new filter>"){
      std::string whereclause = buildQuery();
      //m_results = storage->get_IDs_by_constraint(whereclause);
      m_results = storage->get_by_constraint_dont_join_metatables(whereclause,0,"",0,"",true);
    }else{
        m_results = storage->apply_filter(fname.str());
    }
      
      auto sel = m_assets_treeView.get_selection();
      sel->unselect_all();
      m_assets->clear();
      Gtk::TreeModel::Row row;
        for (int i=0; i<m_results.size();i++){
                row = *(m_assets->append());
                row[m_assets_cols.col]=m_results[i];
    }
    
    m_saveAsset.set_margin_top(10);
    m_saveAsset.set_size_request(200,100);
    std::stringstream l; 
    l<< "Results: " << m_results.size() << " assets found";
    m_assetFrame.set_label(l.str());
    show_all();
}

void FilterWindow::on_remove_attribute(int counter){
    int combosize = m_comboV.size();
    int valuesize = m_valueV.size();
    int opsize = m_comboOpV.size();
    
    m_grid.remove(m_assetFrame);
    m_grid.remove(m_Frame2);
    m_grid.remove(m_Frame3);
    
    m_grid.remove(m_button_add);
    
    m_grid.remove(m_button_ok);
    m_grid.remove(m_newfiltername);
    m_grid.remove(m_save);
      
    int last =combosize-1;
    //remove last line
    if (combosize>opsize) {
        m_grid.remove(*(m_removefilterV[combosize-1]));
        m_grid.remove(*(m_comboV[combosize-1]));
        if (combosize>1) m_grid.remove(*(m_boolV[combosize-2]));
        last = combosize-2;

    }
    
    //remove all other lines
    for (int i=last; i>=0; i--){
        m_grid.remove(*(m_removefilterV[i]));
        m_grid.remove(*(m_valueV[i]));
        m_grid.remove(*(m_comboOpV[i]));
        m_grid.remove(*(m_comboV[i]));
        if (i>0) m_grid.remove(*(m_boolV[i-1]));

    }
     
    //remove widgets from vectors
    m_comboV.erase(m_comboV.begin()+counter);
    if (combosize>1) m_boolV.erase(m_boolV.begin()+counter-1);
    m_removefilterV.erase(m_removefilterV.begin()+counter);
    if (combosize==valuesize && counter == combosize-1){    
        m_comboOpV.erase(m_comboOpV.begin()+counter);
        m_valueV.erase(m_valueV.begin()+counter);
    }

    
    
    for (int i=0; i<combosize-3; i++){
    
        if (i==0){
            m_grid.attach_next_to(*(m_comboV[i]),m_placeholder,Gtk::POS_RIGHT);
        }else{
            if (i==1) m_grid.attach_next_to(*(m_boolV[i-1]),m_placeholder,Gtk::POS_BOTTOM);
            else m_grid.attach_next_to(*(m_boolV[i-1]),*(m_boolV[i-2]),Gtk::POS_BOTTOM);
            
            m_grid.attach_next_to(*(m_comboV[i]),*(m_boolV[i-1]),Gtk::POS_RIGHT);
        }
        
        
        
        if (m_comboV.size()==2) {m_grid.attach_next_to(*(m_boolV.back()),m_placeholder,Gtk::POS_BOTTOM);}
        else {m_grid.attach_next_to(*(m_boolV.back()),*(m_boolV[m_boolV.size()-2]),Gtk::POS_BOTTOM);}
        
        m_grid.attach_next_to(*(m_comboV.back()),*(m_boolV.back()),Gtk::POS_RIGHT);
        m_grid.attach_next_to(*(m_removefilterV.back(),m_comboV.back()),Gtk::POS_RIGHT);
        
    }
    
    //add last line
        if (combosize-1 == 1){ m_grid.attach_next_to(*(m_comboV.back()),m_placeholder,Gtk::POS_RIGHT); }
        if (combosize-1 == 2 ){
            m_grid.attach_next_to(*(m_boolV.back()),m_placeholder,Gtk::POS_BOTTOM);
            m_grid.attach_next_to(*(m_comboV.back()),*(m_boolV.back()),Gtk::POS_RIGHT);
        }
        if (combosize-1 >2){
            m_grid.attach_next_to(*(m_boolV.back()),*(m_boolV[m_boolV.size()-2]),Gtk::POS_BOTTOM);
            m_grid.attach_next_to(*(m_comboV.back()),*(m_boolV.back()),Gtk::POS_RIGHT);
        }
    
    if (combosize-1 > 0) {
      if (combosize == valuesize || counter == combosize-1){
          m_grid.attach_next_to(*(m_comboOpV.back()),*(m_comboV.back()),Gtk::POS_RIGHT);
          m_grid.attach_next_to(*(m_valueV.back()),*(m_comboOpV.back()),Gtk::POS_RIGHT);
          m_grid.attach_next_to(*(m_removefilterV.back()),*(m_valueV.back()),Gtk::POS_RIGHT);
      }else{
          m_grid.attach_next_to(*(m_removefilterV.back()),*(m_comboV.back()),Gtk::POS_RIGHT);
      }
      m_grid.attach_next_to(m_button_add,*(m_comboV.back()),Gtk::POS_BOTTOM);
    }else{
        m_grid.attach_next_to(m_button_add,m_placeholder,Gtk::POS_BOTTOM);
    }

    
    
    
    m_grid.attach_next_to(m_button_ok,m_button_add,Gtk::POS_RIGHT);
    m_newfiltername.set_margin_top(10);
    m_grid.attach_next_to(m_newfiltername, m_button_add, Gtk::POS_BOTTOM);
    m_grid.attach_next_to(m_save,m_newfiltername,Gtk::POS_RIGHT);
    
    m_grid.attach_next_to(m_Frame2, m_save, Gtk::POS_BOTTOM, 2, 1);
    m_grid.attach_next_to(m_Frame3, m_Frame2, Gtk::POS_BOTTOM, 2, 1);
    m_grid.attach_next_to(m_assetFrame, m_Frame2, Gtk::POS_LEFT, 1, 2);
    
    if (m_comboOpV.size() == m_comboV.size()) {
        m_button_add.set_sensitive(true);
        m_button_ok.set_sensitive(true);
    }
    
    rowcounter--;
    show_all_children();
    resize(1, 1);
}

void FilterWindow::on_attribute_selected(int counter){
    int combosize = m_comboV.size();
    int valuesize = m_valueV.size();
    int opsize = m_comboOpV.size();
    
    if (opsize<combosize && counter==combosize-1){
        m_comboOpV.push_back(Glib::wrap((new Gtk::ComboBox())->gobj(),true));
        m_attr_types.push_back(0);
        
    }
    
    
    const auto iter = m_comboV[counter]->get_active();
    
    if(iter)
    {
      const auto row = *iter;
      if(row)
      {
        Glib::ustring name = row[m_attr_col.col];
        std::string name_table = name.substr(0, name.find('.'));
        std::string name_attr = name.substr(name.find('.')+1);
        m_comboOpV[counter]->unset_model();
        m_comboOpV[counter]->clear();
        if (storage->meta_store->get_isText_byAttr(name_attr, name_table)) {
            m_comboOpV[counter]->set_model(m_opModelText);
            m_comboOpV[counter]->pack_start(m_opText_col.col);
            m_attr_types[counter]=1;
        }
        if (storage->meta_store->get_isNumeric_byAttr(name_attr, name_table)) {
            m_comboOpV[counter]->set_model(m_opModelNumber);
            m_comboOpV[counter]->pack_start(m_opNumber_col.col);
            m_attr_types[counter]=0;
        }

      }
    }
    
    
    if (valuesize<combosize && counter==combosize-1){
        m_valueV.push_back(Glib::wrap((new Gtk::Entry())->gobj(),true));
    }
    
    if (opsize<combosize && counter==combosize-1){
        m_grid.attach_next_to(*(m_comboOpV.back()),*(m_comboV.back()),Gtk::POS_RIGHT);
    }
    
    if (valuesize<combosize && counter==combosize-1){
        m_grid.remove(*(m_removefilterV.back()));
        m_valueV.back()->signal_editing_done().connect( sigc::bind(sigc::mem_fun(*this, &FilterWindow::on_editing_done), opsize-1));
        m_grid.attach_next_to(*(m_valueV.back()),*(m_comboOpV.back()),Gtk::POS_RIGHT);
        m_grid.attach_next_to(*(m_removefilterV.back()),*(m_valueV.back()),Gtk::POS_RIGHT);
    }
    
    if (opsize==0) {
        m_comboOpV.back()->set_margin_top(10);
        m_valueV.back()->set_margin_top(10);
    }
    
    on_editing_done(counter);
    show_all_children();
    resize(1, 1);
}

void FilterWindow::on_editing_done(int counter){
    if (m_valueV.size() == m_comboV.size()){
        m_button_add.set_sensitive(true);
        m_button_ok.set_sensitive(true);
    }
}

void FilterWindow::on_add_filter(){
    //drop_down menü erstellen
    m_grid.remove(m_assetFrame);
    m_grid.remove(m_Frame2);
    m_grid.remove(m_Frame3);
    
    m_comboV.push_back(Glib::wrap((new Gtk::ComboBox())->gobj(),true));

    m_comboV.back()->set_model(m_attrModel);
    m_comboV.back()->pack_start(m_attr_col.col);
  //  m_comboV.back()->set_size_request(-1,50);

    m_comboV.back()->signal_changed().connect( sigc::bind(sigc::mem_fun(*this, &FilterWindow::on_attribute_selected), rowcounter));
    
    m_grid.remove(m_button_ok);
    m_grid.remove(m_newfiltername);
    m_grid.remove(m_save);
       
    m_removefilterV.push_back(Glib::wrap((new Gtk::Button())->gobj(),true));
    m_removefilterV.back()->set_label(" X ");
    m_removefilterV.back()->set_margin_top(10);
    m_removefilterV.back()->signal_clicked().connect( sigc::bind(sigc::mem_fun(*this, &FilterWindow::on_remove_attribute), rowcounter));

    if (m_comboV.size() >1){
        m_boolV.push_back(Glib::wrap((new Gtk::ComboBox())->gobj(),true));
        m_boolV.back()->set_model(m_boolModel);
        m_boolV.back()->pack_start(m_bool_col.col);
        m_boolV.back()->set_active(0);

        
        if (m_comboV.size()==2) {m_grid.attach_next_to(*(m_boolV.back()),m_placeholder,Gtk::POS_BOTTOM);}
        else {m_grid.attach_next_to(*(m_boolV.back()),*(m_boolV[m_boolV.size()-2]),Gtk::POS_BOTTOM);}
        
        m_grid.attach_next_to(*(m_comboV.back()),*(m_boolV.back()),Gtk::POS_RIGHT);
        
    }else{
        m_comboV.back()->set_margin_top(10);
        m_grid.attach_next_to(*(m_comboV.back()),m_placeholder,Gtk::POS_RIGHT);
    }
    
    m_grid.attach_next_to(*(m_removefilterV.back()),*(m_comboV.back()),Gtk::POS_RIGHT);
    
    m_grid.remove(m_button_add);
    m_grid.attach_next_to(m_button_add,*(m_comboV.back()),Gtk::POS_BOTTOM);
    m_grid.attach_next_to(m_button_ok,m_button_add,Gtk::POS_RIGHT);
    m_newfiltername.set_margin_top(10);
    m_grid.attach_next_to(m_newfiltername, m_button_add, Gtk::POS_BOTTOM);
    m_grid.attach_next_to(m_save,m_newfiltername,Gtk::POS_RIGHT);
    
    m_grid.attach_next_to(m_Frame2, m_save, Gtk::POS_BOTTOM, 2, 1);
    m_grid.attach_next_to(m_Frame3, m_Frame2, Gtk::POS_BOTTOM, 2, 1);
    m_grid.attach_next_to(m_assetFrame, m_Frame2, Gtk::POS_LEFT, 1, 2);
    
    m_button_add.set_sensitive(false);
    m_button_ok.set_sensitive(false);
    rowcounter++;
    show_all_children();
    
    resize(1, 1);

}

void FilterWindow::on_selection_changed(){
    auto sel = m_assets_treeView.get_selection();
    auto seliter = sel->get_selected();
    std::string s;
    if(seliter) //If anything is selected
    {
      Gtk::TreeModel::Row selrow = *seliter;
      s=selrow.get_value(m_assets_cols.col);
    }
    
    storage->meta_store->execQuery("Select * FROM filedata WHERE key = '" + s + "'");
    m_auto_meta.set_label(storage->meta_store->crop_result(storage->meta_store->getResultAsString()));
    std::vector<std::string> ameta = storage->meta_store->crop_and_split_result(storage->meta_store->getResultAsString());
    std::string auto_label = "";
    if (ameta.size()>=5){
      auto_label = auto_label + "Compressed: " + ameta[2] + "\n";
      auto_label = auto_label + "Original path: " + ameta[3] + "\n";
      auto_label = auto_label + "Original file extension: " + ameta[4] + "\n";
    }else{
        auto_label = "No auto-detectd meta-data available\n";
    }
    
    m_auto_meta.set_label(auto_label);
    
    storage->meta_store->execQuery("Select * FROM metadata WHERE " + storage->meta_store->idcolumn + " = '" + s + "'");
    std::vector<std::string> umeta = storage->meta_store->crop_and_split_result(storage->meta_store->getResultAsString());
    std::vector<std::string> cols = storage->meta_store->get_user_meta_column_names();
    std::string user_label = "";
    for (int i=0;i<umeta.size();i++) {
        user_label = user_label + cols[i] + ": " + umeta[i] + "\n";
    }
    
    std::vector<std::string> tablenames=storage->meta_store->get_all_meta_tables();

    for (int i=0;i<tablenames.size();i++){
        if (tablenames[i]!="metadata"){
            storage->meta_store->execQuery("SELECT idcolname FROM metainfo WHERE tablename='" + tablenames[i] + "'");
            std::string joincol=storage->meta_store->crop_single_result(storage->meta_store->getResultAsString());
            int idx=0;
            for (int k=0;k<cols.size();k++){
                if (cols[k]==joincol){
                    idx=k;
                    break;
                }
            }
            storage->meta_store->execQuery("Select * FROM "+ tablenames[i] +" WHERE " + joincol + " = '" + umeta[idx] + "'");
            std::vector<std::string> u2meta = storage->meta_store->crop_and_split_result(storage->meta_store->getResultAsString());
            std::vector<std::string> metacols = storage->meta_store->get_user_meta_column_names(tablenames[i]);
            
 //           std::cout << "u2size: " << u2meta.size() << ", metacols.size: " << metacols.size() << std::endl;
            for (int j=0; j<u2meta.size(); j++){
                
                user_label = user_label + tablenames[i]+"."+metacols[j%metacols.size()] + ": " + u2meta[j] + "\n";
//                std::cout << "user meta 2: "<< u2meta[j] << std::endl;
            }
        }
    }
    
    m_user_meta.set_label(user_label);

    //See if our asset was an image
    std::string type = "none";
    if (ameta.size()>=5){ 
        type = ameta[4];
        type.erase(0,1);
    }
    auto *contains = std::find(std::begin(picture_formats), std::end(picture_formats), type);
    
    //If our asset was an image load data into a pixel buffer and show the image
    if (type=="jpg" || contains != std::end(picture_formats)) {
        //get the asset from the storage
        auto imagedata = storage->get(s,0,"",0,"",1);
        
        //load the image
        MyImageLoader* loader = new MyImageLoader(type=="jpg" ? "jpeg" : type);
        loader->write(reinterpret_cast<const unsigned char*>(imagedata.data()),imagedata.size());
        loader->close();
        auto pix = loader->get_pixbuf();
        
        //scale pictures small enough to not exceed 500px
        int width=pix->get_width();
        int height=pix->get_height();
        float scale = 1;
        if (width>500) {
            scale = width/500;
        }
        if (height/scale > 500){
            scale = height/500;
        }

        auto pix_scaled = pix->scale_simple(width/scale, height/scale, Gdk::INTERP_BILINEAR);
        
        //hide label with text
        m_scroll_window.hide();
        
        //display the image
        m_image.set(pix_scaled);
        m_image.show();
        

    }else//Show asset as text if it is not a picture
    {
        //Hide image
        m_image.hide();
        
        //get the text from the storage
        std::string textdata = storage->get(s,0,"",0,"",1);
        
        //Make the label multi line
        m_asset.set_line_wrap(true);
        m_asset.set_width_chars(80);
        
        //show text
        m_asset.set_label(textdata);
        m_scroll_window.set_size_request(800,300);
        m_scroll_window.show();
    }
    
    if (type!="none"){
        m_saveAsset.set_sensitive(true);
    }else{
        m_saveAsset.set_sensitive(false);
    }
    
    m_selected_ID = s;
    if (ameta.size()>=5) m_selected_Extension = ameta[4];
    else m_selected_Extension = "";
    m_assetSaved.set_label("    ");
    
    m_scroll_window_meta.set_size_request(800,300);
    //resize the main window to fit the contents. This isn't done automatically in case the contents become smaller
    resize(1, 1);
}
