#include "mainwindow.h"
#include <iostream>

StoreChoiceWindow::StoreChoiceWindow(){
    
    m_TextL.set_label("Lorem Ipsum\n");
    m_OkB.add_label("Start");
    m_CancelB.add_label("Cancel");
    m_OkB.signal_clicked().connect(sigc::mem_fun(*this, &StoreChoiceWindow::on_button_clicked));
    m_CancelB.signal_clicked().connect(sigc::mem_fun(*this, &StoreChoiceWindow::on_button_cancel_clicked));
    m_inL.set_label("Select the folder containing your assets");   
    m_inL.set_halign(Gtk::ALIGN_START);
    m_InB.add_label("Select");
    m_dir_inL.set_label("No directory selected\n");
    m_outL.set_label("Where do you want the local DataStore to be created?");  
    m_outL.set_halign(Gtk::ALIGN_START); 
    m_OutB.add_label("Select");    
    m_dir_outL.set_label("No directory selected\n");
    m_nameL.set_label("Chose a name for the DataStore");
    m_scanrecursiveL.set_label("Scan directory recursively?");
    m_prefixL.set_label("Does the filename have a prefix?");
    m_charcountL.set_label("How many characters?");
    m_charcountL.set_visible(false);
    m_charcount.set_visible(false);
    m_portableL.set_label("Create portable Asset Store?");
    m_nameL.set_label("Provide a name for your Asset store: ");
    
    m_charcount.set_increments (1, 1);
    m_charcount.set_range(1, 9);
    m_charcount.set_value(1);
        
    //Add all gui elements
    add(m_grid);
    m_grid.add(m_TextL);
    m_grid.attach_next_to(m_inL,m_TextL,Gtk::POS_BOTTOM,2,1);
    m_grid.attach_next_to(m_InB,m_inL,Gtk::POS_BOTTOM,2,1);
    m_grid.attach_next_to(m_dir_inL,m_InB,Gtk::POS_BOTTOM,2,1);
    m_grid.attach_next_to(m_outL,m_dir_inL,Gtk::POS_BOTTOM,2,1);
    m_grid.attach_next_to(m_OutB,m_outL,Gtk::POS_BOTTOM,2,1);
    m_grid.attach_next_to(m_dir_outL,m_OutB,Gtk::POS_BOTTOM,2,1);
    m_grid.attach_next_to(m_portableL,m_dir_outL,Gtk::POS_BOTTOM);
    m_grid.attach_next_to(m_portable,m_portableL,Gtk::POS_RIGHT);
    m_grid.attach_next_to(m_prefixL,m_portableL,Gtk::POS_BOTTOM);
    m_grid.attach_next_to(m_prefix,m_prefixL,Gtk::POS_RIGHT);
    m_grid.attach_next_to(m_charcountL,m_prefixL,Gtk::POS_BOTTOM);
    m_grid.attach_next_to(m_charcount,m_charcountL,Gtk::POS_RIGHT);
    m_grid.attach_next_to(m_nameL,m_charcountL,Gtk::POS_BOTTOM);
    m_grid.attach_next_to(m_name,m_nameL,Gtk::POS_RIGHT);
    
   // m_grid.attach_next_to(m_CancelB,m_charcountL,Gtk::POS_BOTTOM); 
    m_grid.attach_next_to(m_OkB,m_nameL,Gtk::POS_BOTTOM);  
    
    m_charcountL.set_visible(false);
    m_charcount.set_visible(false);  
}

StoreChoiceWindow::~StoreChoiceWindow(){

}

void StoreChoiceWindow::on_button_clicked(){

}

void StoreChoiceWindow::on_button_cancel_clicked(){

}

void StoreChoiceWindow::on_select_folder_in(){
}

void StoreChoiceWindow::on_select_folder_out(){

}

void StoreChoiceWindow::on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog){
}

bool StoreChoiceWindow::get_recursivescan(){
    return m_scanrecursive.get_active();
}

bool StoreChoiceWindow::get_includeprefix(){
    return m_prefix.get_active();
}

bool StoreChoiceWindow::get_portable(){
    return m_portable.get_active();
}

int StoreChoiceWindow::get_charcount(){
    return m_charcount.get_value();
}

std::string StoreChoiceWindow::get_name(){
    return m_name.get_text();
}



MainWindow::MainWindow()

{
    m_active_store="";
    //storage= new SciStore::Storage<>("assets","meta");
    set_border_width(10);
    
    m_button_select.add_label("Open Store");
    m_button_select.set_margin_end(20);
    m_button_select.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked_select));
        
    m_button_create.add_label("Create Store");
    m_button_create.set_margin_end(20);
    m_button_create.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked_create));

    m_button_filter.add_pixlabel("filter.png", "Filter data");
    m_button_filter.set_margin_end(20);
    m_button_filter.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked_filter));
        
    m_button_code.add_label("<> Code"); 
    m_button_code.set_margin_end(20);
    m_button_code.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked_code));
    
    m_button_preferences.add_pixlabel("preferences.png","");
    m_button_preferences.set_tooltip_text("Preferences");
 
    add(m_grid_all);
    m_grid_all.add(m_grid_menu);
    m_grid_all.attach_next_to(m_grid_data, m_grid_menu, Gtk::POS_BOTTOM);
    
    m_grid_menu.add(m_button_select);
    m_grid_menu.add(m_button_create);
    m_grid_menu.add(m_button_filter);
    m_grid_menu.add(m_button_code);
    //m_grid_menu.add(m_button_preferences);

    m_Box1.set_border_width(10);
    m_Frame1.set_margin_top(10);
    m_Frame1.set_margin_end(10);
    m_Frame1.set_label("Assets");
    m_Frame1.set_label_align(0.02);
    m_Frame1.add(m_Box1);
    

    
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
    
    m_grid_data.add(m_Frame2);
    m_grid_data.attach_next_to(m_Frame1, m_Frame2, Gtk::POS_LEFT, 1, 2);
    
    m_Box3.set_border_width(10);
    m_Frame3.set_margin_top(10);
    m_Frame3.set_label("Preview");
    m_Frame3.set_label_align(0.02);
    m_Frame3.add(m_Box3);
    m_Box3.add(m_image);
    m_Box3.add(m_scroll_window);
    m_scroll_window.add(m_asset);
    
    m_grid_data.attach_next_to(m_Frame3, m_Frame2, Gtk::POS_BOTTOM);

    m_grid_data.attach_next_to(m_saveAsset, m_Frame3, Gtk::POS_BOTTOM);
    m_saveAsset.set_sensitive(false);
    m_saveAsset.set_label("Save Asset");
    m_saveAsset.set_margin_top(10);
    m_saveAsset.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_asset_saved));
    m_assetSaved.set_label("    ");
    m_grid_data.attach_next_to(m_assetSaved,m_saveAsset, Gtk::POS_BOTTOM);
    
    m_separator.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    m_separator.set_margin_top(10);
    m_info.override_color (Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
    m_info.set_label("No Store selected");
    m_info.set_margin_top(5);
    m_grid_all.attach_next_to(m_separator,m_grid_data,Gtk::POS_BOTTOM);
    m_grid_all.attach_next_to(m_info,m_separator,Gtk::POS_BOTTOM);
    
    m_open_assistant.signal_apply().connect(sigc::mem_fun(*this, &MainWindow::on_open_assistant_apply));
    m_create_assistant.signal_apply().connect(sigc::mem_fun(*this, &MainWindow::on_create_assistant_apply));
    
    //List with assets
    m_assets_treeView.set_model(m_assets = Gtk::ListStore::create(m_assets_cols));
    m_assets_treeView.append_column("Asset ID", m_assets_cols.col_id);
    m_assets_treeView.signal_cursor_changed().connect(sigc::mem_fun(*this, &MainWindow::on_selection_changed));
    m_assets_scrollWindow.add(m_assets_treeView);
	m_assets_scrollWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    m_assets_scrollWindow.set_min_content_width(300);
    m_assets_scrollWindow.set_min_content_height(300);
   // m_assets_treeView.get_column(0)->set_min_width(500);
    m_Box1.add(m_assets_scrollWindow);
        

    
    m_selected_ID = "";
    m_selected_Extension = "";
    
    show_all_children();
    m_open_assistant.hide();
    m_create_assistant.hide();
    created_open=0; 
    created_create=0;
}

void MainWindow::on_asset_saved(){

    storage->get(m_selected_ID, 1, m_selected_Extension, 1, ".txt");
    m_assetSaved.override_color (Gdk::RGBA("green"), Gtk::STATE_FLAG_NORMAL);
    m_assetSaved.set_label("Saved");
}

MainWindow::~MainWindow()
{
    delete storage;
}

void MainWindow::on_selection_changed(){
    auto sel = m_assets_treeView.get_selection();
    auto seliter = sel->get_selected();
    std::string s;
    if(seliter) //If anything is selected
    {
      Gtk::TreeModel::Row selrow = *seliter;
      s=selrow.get_value(m_assets_cols.col_id);
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
//        std::cout << "user meta: "<< umeta[i] << std::endl;
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
            storage->meta_store->execQueryAndPrint("Select * FROM "+ tablenames[i] +" WHERE " + joincol + " = '" + umeta[idx] + "'");
            std::vector<std::string> u2meta = storage->meta_store->crop_and_split_result(storage->meta_store->getResultAsString());
            std::vector<std::string> metacols = storage->meta_store->get_user_meta_column_names(tablenames[i]);
            
            std::cout << "u2size: " << u2meta.size() << ", metacols.size: " << metacols.size() << std::endl;
            for (int j=0; j<u2meta.size(); j++){
                
                user_label = user_label + tablenames[i]+"."+metacols[j%metacols.size()] + ": " + u2meta[j] + "\n";
  //              std::cout << "user meta 2: "<< u2meta[j] << std::endl;
            }
        }
    }

    m_user_meta.set_label(user_label);
    
    //See if our asset was an image
    std::string type = "none";
    if (ameta.size()>=5){ 
        type = ameta[4];
        type.erase(0, 1);
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
        m_scroll_window.set_size_request(/*m_meta_sep.get_width()*/800,300);
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
    //resize the main window to fit the contents. This isn't done automatically in case the contents become smaller
    resize(1, 1);
}

void MainWindow::on_button_clicked_select()
{


    m_open_assistant.create_window();
    created_open=1;

    m_open_assistant.set_labels();

    m_scroll_window_meta.set_size_request(800,300);
    m_open_assistant.show_all();
    
}

bool MainWindow::on_timeout()
{
   m_ProgressBar.pulse();
   return true;
}

void *import(void *arg)
{
        struct ThreadArgs *ta = (ThreadArgs*) arg;
        auto p_create_assistant = ta->t_create_assistant;
        auto p_storage = ta->t_storage;
        std::cout << "in thread dir: " << p_create_assistant->m_datadir << std::endl;
        storage->load_assets_from_directory(p_create_assistant->m_datadir, p_create_assistant->get_portable() ? 1 : 0, p_create_assistant->get_recursivescan() ? 1 : 0, p_create_assistant->get_dircount(), p_create_assistant->get_includeext() ? 1 : 0, p_create_assistant->get_includeprefix() ? p_create_assistant->get_charcount() : 0);
        pthread_exit(NULL);
}

void MainWindow::on_create_assistant_apply()
{
    ///progress bar

    m_grid_all.attach_next_to(m_ProgressBar,m_info,Gtk::POS_BOTTOM);
    m_ProgressBar.set_margin_end(5);
    m_ProgressBar.set_halign(Gtk::ALIGN_CENTER);
    m_ProgressBar.set_valign(Gtk::ALIGN_CENTER);
    m_ProgressBar.set_size_request(100, 10);
    m_ProgressBar.set_text("some text");
    m_connection_timeout = Glib::signal_timeout().connect(sigc::mem_fun(*this,&MainWindow::on_timeout), 50 );
    m_ProgressBar.pulse();
    show_all();
    resize(1, 1);
    /////////////
    
    std::cout << m_create_assistant.m_meta_basename_woext << std::endl;
    std::filesystem::create_directory(std::filesystem::current_path().string() +"/"+ m_create_assistant.get_name());
    storage = new SciStore::Storage<>(std::filesystem::current_path().string() +"/"+ m_create_assistant.get_name() + "/" + m_create_assistant.m_data_basename + "_datastore", std::filesystem::current_path().string() +"/"+ m_create_assistant.get_name() + "/" + m_create_assistant.m_meta_basename_woext.string()+"_metastore.db");
    storage->asset_store->portablefile = std::filesystem::current_path().string() +"/"+ m_create_assistant.get_name() + "/" + "portable_data_store.sst";
    
    //Let import be done in a separate Thread
    pthread_t import_thread;
    ThreadArgs ta;
    ta.t_storage = storage;
    ta.t_create_assistant = &m_create_assistant;
    pthread_create(&import_thread, NULL, &import, (void*) &ta);
    int res;
    pthread_join(import_thread, (void **)&res);
//    storage->load_assets_from_directory(m_create_assistant.m_datadir, m_create_assistant.get_portable() ? 1 : 0, m_create_assistant.get_recursivescan() ? 1 : 0, m_create_assistant.get_dircount(), m_create_assistant.get_includeext() ? 1 : 0, m_create_assistant.get_includeprefix() ? m_create_assistant.get_charcount() : 0);


    storage->load_metadata_from_file(m_create_assistant.m_metadir,m_create_assistant.get_keycol());
    

    if (m_create_assistant.get_portable()){
        storage->import_asset_store(storage->asset_store->portablefile);
    }
    

      storage->meta_store->execQuery("Select count(*) from filedata");
      std::string nrassets=storage->meta_store->crop_single_result(storage->meta_store->getResultAsString());
      std::cout << "Found " << nrassets << " assets." << std::endl;
      m_asset_list = storage->get_all_assets(0,storage->afe,0,storage->mfe,1);
      std::cout << "Elements in asset list: " << m_asset_list.size() << std::endl;
      
      m_assets->clear();
      Gtk::TreeModel::Row row;
      for (int i=0; i<m_asset_list.size();i++){
              row = *(m_assets->append());
              row[m_assets_cols.col_id]=m_asset_list[i];
      }
          
    m_info.override_color (Gdk::RGBA("black"), Gtk::STATE_FLAG_NORMAL);
    m_info.set_label("Data Store: " + m_create_assistant.m_data_basename + "\t Meta Store: " + m_create_assistant.m_meta_basename + "\t #Assets: " + nrassets);

    m_active_store=m_create_assistant.get_name();
    
    //Write a configuration file so we can easily open this store again
    xmlConfig = new XMLDocument;
    XMLNode * root;
    
    if (fs::exists(XMLFileName)){
        xmlConfig->LoadFile(XMLFileName.c_str());
        root = xmlConfig->FirstChild();
    }
    else{
        root = xmlConfig->NewElement("AssetStores");
        xmlConfig->InsertFirstChild(root);
    }
    
    XMLElement * el = xmlConfig->NewElement("store");
    
    XMLElement * el_name = xmlConfig->NewElement("name");
    el_name->SetText(m_create_assistant.get_name().c_str());
    el->InsertEndChild(el_name);
    
    XMLElement * el_meta = xmlConfig->NewElement("meta");
    el_meta->SetText((std::filesystem::current_path().string() +"/"+ m_create_assistant.get_name() + "/" + m_create_assistant.m_meta_basename_woext.string()+"_metastore.db").c_str());
    el->InsertEndChild(el_meta);
    XMLElement * el_data = xmlConfig->NewElement("data");
    el_data->SetText((std::filesystem::current_path().string() +"/"+ m_create_assistant.get_name() + "/" + m_create_assistant.m_data_basename + "_datastore").c_str());
    el->InsertEndChild(el_data);
    
    root->InsertEndChild(el);
    
    XMLError eResult = xmlConfig->SaveFile(XMLFileName.c_str());
    

   // m_grid_all.remove(m_ProgressBar);
}


void MainWindow::on_open_assistant_apply()
{
    if (storage != nullptr){
        if (storage->asset_store != nullptr)storage->asset_store->close();
    }
        if (m_open_assistant.m_data_isdirectory){
            std::cout << "open data store from directory " << m_open_assistant.m_datadir << std::endl;
            storage = new SciStore::Storage<>(m_open_assistant.m_datadir,m_open_assistant.m_metadir);
        }else{
            std::cout << "import data store from file " << m_open_assistant.m_metadir << std::endl;
            storage = new SciStore::Storage<>("datastore","metastore.db");
            storage->import_asset_store(m_open_assistant.m_datadir);
            storage->open_meta_store(m_open_assistant.m_metadir);
        }

        storage->meta_store->execQuery("show tables");
       // std::cout << storage->meta_store->getResultAsString();
        storage->meta_store->execQuery("Select count(*) from metadata");
        std::string nrassets=storage->meta_store->crop_single_result(storage->meta_store->getResultAsString());
        std::cout << "Found " << nrassets << " assets." << std::endl;
        m_asset_list = storage->get_all_assets(0,storage->afe,0,storage->mfe,1);
        std::cout << "Elements in asset list: " << m_asset_list.size() << std::endl;
        m_assets->clear();
        
        Gtk::TreeModel::Row row;
        for (int i=0; i<m_asset_list.size();i++){
            row = *(m_assets->append());
            row[m_assets_cols.col_id]=m_asset_list[i];
        }
        
        m_info.override_color (Gdk::RGBA("black"), Gtk::STATE_FLAG_NORMAL);
        m_info.set_label("Data Store: " + m_open_assistant.m_data_basename + "\t Meta Store: " + m_open_assistant.m_meta_basename + "\t #Assets: " + nrassets);


}

void MainWindow::on_button_clicked_create()
{

    m_importW = new StoreChoiceWindow;
    m_importW->show_all();

  /*  if (created_create==0){
        m_create_assistant.create_window();
        created_create=1;
    }else m_create_assistant.set_labels();
    m_create_assistant.show_all();
    m_create_assistant.set_initial_state();*/


}

void MainWindow::on_button_clicked_filter()
{
    m_filterW = new FilterWindow(storage);
    m_filterW->show();
}

void MainWindow::on_button_clicked_code()
{
    m_codeW = new CodeWindow(storage);
    m_codeW->show();
}
