#include "assistants.h"

SciStore::Storage<> * storage;

CreateAssistant::CreateAssistant(){
}

CreateAssistant::~CreateAssistant()
{
}

void CreateAssistant::set_labels(){
      //Set Labels  
        m_intro.set_label("To create an Asset Store, please choose the folder containing the data and answer the questions");
        set_page_title(m_intro, "Intro"); 

        m_dataL.set_label("Select folder");
        m_dataL.set_halign(Gtk::ALIGN_START);
        m_dataB.set_label("Browse");
        set_page_title(m_data, "Select folder");
        m_datadirL.set_label("No folder selected");
        m_datadirL.set_halign(Gtk::ALIGN_START);
        m_confirmL1.set_label("Nothing selected\n");
        m_confirmL1.set_halign(Gtk::ALIGN_START);
        set_page_title(m_confirm, "Confirm");
        
        m_scanrecursiveL.set_label("Scan directory recursively?");
        m_scanrecursiveL.set_halign(Gtk::ALIGN_START);
        
        m_metaL.set_label("Select a csv/tsv file containing the meta data.");
        m_metaL.set_halign(Gtk::ALIGN_START);
        m_metaB.set_label("Browse");
        m_metafileL.set_label("No file selected");
        m_metafileL.set_halign(Gtk::ALIGN_START);
        
        set_page_title(m_key, "Key preferences");
        m_key_descr.set_label("A key uniquely identifies an asset. We use the file name as a key. To match it with your meta data, you can modify how your keys are created.");
        m_key_descr.set_line_wrap(true);
        m_key_descr.set_width_chars(50);
        m_includeextL.set_label("Include the file extension in the key.");
        m_includeextL.set_halign(Gtk::ALIGN_START);
        m_dircountL.set_label("How many directories are part of the key? 0 if only file name is used as a key.");
        m_dircountL.set_halign(Gtk::ALIGN_START);
        m_prefixL.set_label("Does the filename have a prefix?");
        m_prefixL.set_halign(Gtk::ALIGN_START);
        m_charcountL.set_label("How many characters?");
        m_charcountL.set_halign(Gtk::ALIGN_START);
        m_keycolL.set_label("Which column contains the key? Provide the name.");
        m_keycolL.set_halign(Gtk::ALIGN_START);
        
        
        m_portableL.set_label("Create portable Asset Store?");
        m_portableL.set_halign(Gtk::ALIGN_START);
        m_nameL.set_label("Provide a name for your Asset store: ");
        m_nameL.set_halign(Gtk::ALIGN_START);
        m_portableL.set_tooltip_text("Creates a portable data store additionally to a local data store. The meta store is always portable.");
      //  m_portable_TT.set_text("Creates a portable data store additionally to a local data store. The meta store is always portable.");
        
        set_page_title(m_store, "Storage preferences");
              
        m_dircount.set_increments (1, 1);
        m_dircount.set_range(0, 9);
        m_dircount.set_value(0);
        
        m_charcount.set_increments (1, 1);
        m_charcount.set_range(1, 9);
        m_charcount.set_value(1);
}

void CreateAssistant::set_initial_state(){
        m_charcountL.set_visible(false);
        m_charcount.set_visible(false);
}

void CreateAssistant::create_window()
{

      set_title("Create an Asset Store");
      set_default_size(800, 200);
      
    append_page(m_intro);
    append_page(m_data);
    append_page(m_key);
    append_page(m_store);
    append_page(m_confirm);
    
    //Intro page

        set_page_complete(m_intro, true);

        set_page_type(m_intro, Gtk::ASSISTANT_PAGE_INTRO);
    //Choose Data Store
        set_page_type(m_data, Gtk::ASSISTANT_PAGE_CONTENT);
        set_page_complete(m_data, true);
        m_data.add(m_dataL);

        m_data.attach_next_to(m_dataB,m_dataL,Gtk::POS_BOTTOM,1,1);
        set_page_type(m_data, Gtk::ASSISTANT_PAGE_CONTENT);
        set_page_complete(m_data, true);
        m_dataB.signal_clicked().connect(sigc::mem_fun(*this,&CreateAssistant::on_select_folder));
        m_datadirL.override_color (Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
        m_data.attach_next_to(m_datadirL,m_dataB,Gtk::POS_BOTTOM,2,1);
                
        m_metafileL.override_color (Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
        m_data.attach_next_to(m_metaL,m_datadirL,Gtk::POS_BOTTOM,2,1);
        m_metaL.set_margin_top(20);
        m_data.attach_next_to(m_metaB,m_metaL,Gtk::POS_BOTTOM,2,1);
        m_metaB.signal_clicked().connect(sigc::mem_fun(*this,&CreateAssistant::on_select_file));
        m_data.attach_next_to(m_metafileL,m_metaB,Gtk::POS_BOTTOM,2,1);
      
        m_data.attach_next_to(m_scanrecursiveL,m_metafileL,Gtk::POS_BOTTOM,1,1);
        m_scanrecursiveL.set_margin_top(20);
        m_data.attach_next_to(m_scanrecursive,m_scanrecursiveL,Gtk::POS_RIGHT,1,1);
        m_scanrecursive.set_margin_top(20);

 
    //Set key preferences
        set_page_complete(m_key, true);
        set_page_type(m_key, Gtk::ASSISTANT_PAGE_CONTENT);
        m_key.attach(m_key_descr,1,1,2,1);
        
        m_includeextL.set_margin_top(20);
        m_includeext.set_margin_top(20);
        m_key.attach_next_to(m_includeextL, m_key_descr,Gtk::POS_BOTTOM);
        m_key.attach_next_to(m_includeext, m_includeextL,Gtk::POS_RIGHT);
        
        m_dircountL.set_margin_top(20);
        m_dircount.set_margin_top(20);
        m_key.attach_next_to(m_dircountL,m_includeextL, Gtk::POS_BOTTOM);
        m_key.attach_next_to(m_dircount, m_dircountL,Gtk::POS_RIGHT);
        
        m_key.attach_next_to(m_keycolL,m_dircountL,Gtk::POS_BOTTOM);
        m_key.attach_next_to(m_keycol,m_keycolL,Gtk::POS_RIGHT);
        m_keycolL.set_margin_top(20);
        m_keycol.set_margin_top(20);
       
        m_prefixL.set_margin_top(20);
        m_prefix.set_margin_top(20);
        m_key.attach_next_to(m_prefixL,m_keycolL,Gtk::POS_BOTTOM);
        m_key.attach_next_to(m_prefix, m_prefixL,Gtk::POS_RIGHT);
        m_prefix.signal_toggled().connect(sigc::mem_fun(*this,&CreateAssistant::on_prefix_toggled));
        
        m_key.attach_next_to(m_charcountL,m_prefixL,Gtk::POS_BOTTOM);
        m_key.attach_next_to(m_charcount,m_charcountL,Gtk::POS_RIGHT);
        m_charcountL.set_visible(false);
        m_charcount.set_visible(false);
        
    //set store preferences
        set_page_complete(m_store,true);
        m_store.add(m_portableL);
        m_store.add(m_portable);
        m_store.attach_next_to(m_nameL,m_portableL,Gtk::POS_BOTTOM);
        m_store.attach_next_to(m_name,m_nameL,Gtk::POS_RIGHT);
        m_nameL.set_margin_top(20);
        m_name.set_margin_top(20);
        
        
    //Confirm page 
      
        m_confirm.attach(m_confirmL1,1,1,2,1);
        m_confirm.attach_next_to(m_confirmL2,m_confirmL1,Gtk::POS_BOTTOM);

        
        set_page_complete(m_confirm, true);
        set_page_type(m_confirm, Gtk::ASSISTANT_PAGE_CONFIRM);

        signal_apply().connect(sigc::mem_fun(*this,&CreateAssistant::on_assistant_apply));
        signal_cancel().connect(sigc::mem_fun(*this,&CreateAssistant::on_assistant_cancel));
        signal_close().connect(sigc::mem_fun(*this, &CreateAssistant::on_assistant_close));
        signal_prepare().connect(sigc::mem_fun(*this, &CreateAssistant::on_assistant_prepare));
      
    
    set_labels();
    
    append_page(m_intro);
    append_page(m_data);
    append_page(m_key);
    append_page(m_store);
    append_page(m_confirm);
}

void CreateAssistant::on_prefix_toggled(){

    if (m_prefix.get_active()) {
        m_charcountL.set_visible(true);
        m_charcount.set_visible(true);
    }else{
        m_charcountL.set_visible(false);
        m_charcount.set_visible(false);
    }

}

void CreateAssistant::on_select_folder(){
    m_files= new Gtk::FileChooserDialog("Please select the folder containing your assets", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    m_files->add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    m_files->add_button("_Open", Gtk::RESPONSE_OK);
    m_files->set_transient_for(*this);
    m_files->set_modal(true);
    m_files->signal_response().connect(sigc::bind(sigc::mem_fun(*this, &CreateAssistant::on_file_dialog_response), m_files));
    m_files->show();
}

void CreateAssistant::on_select_file(){
   
    m_files= new Gtk::FileChooserDialog("Please select the file containing your meta data", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);
    m_files->add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    m_files->add_button("_Open", Gtk::RESPONSE_OK);
    m_files->set_transient_for(*this);
    m_files->set_modal(true);
    m_files->signal_response().connect(sigc::bind(sigc::mem_fun(*this, &CreateAssistant::on_file_dialog_response), m_files));

    m_files->show();
}

void CreateAssistant::on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog)
{

  //Handle the response:
  switch (response_id)
  {
    case Gtk::RESPONSE_OK:
    {
        auto filename = dialog->get_file()->get_path();
        std::cout << "Folder or File selected: " <<  filename << std::endl;
        break;
    }
    case Gtk::RESPONSE_CANCEL:
    {
      //std::cout << "Cancel clicked." << std::endl;
       // delete dialog;
        break;
    }
    default:
    {
        //std::cout << "Unexpected button clicked." << std::endl;
       // delete dialog;
        break;
    }
  }

    if (dialog->get_action()!=Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN){
        auto filename = dialog->get_file()->get_path();
        m_data_basename=dialog->get_file()->get_basename();
        m_datadir=filename;
        m_datadirL.set_label("Asset folder selected: " + filename);
        m_datadirL.override_color (Gdk::RGBA("black"), Gtk::STATE_FLAG_NORMAL);
        m_confirmL1.set_label("Asset folder\n"+ m_datadir + "\nand Meta data:\n" + m_metadir);
        if (m_metadir.length()<1) {
            m_confirmL1.set_label("Asset folder:\n"+ m_datadir);
            m_confirmL2.set_label("No meta data selected");
            m_confirmL2.override_color (Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
        }else{
            m_confirmL2.override_color (Gdk::RGBA("black"), Gtk::STATE_FLAG_NORMAL);
            m_confirmL1.override_color (Gdk::RGBA("black"), Gtk::STATE_FLAG_NORMAL);
            m_confirmL2.set_label("");
        }
      }
    else{
        auto filename=dialog->get_file()->get_path();
        m_meta_basename=dialog->get_file()->get_basename();
        m_metadir=filename;
        
        m_meta_basename_woext = dialog->get_file()->get_path();
        m_meta_basename_woext = m_meta_basename_woext.stem();
        m_metafileL.set_label("Meta data selected: " + filename);
        m_metafileL.override_color (Gdk::RGBA("black"), Gtk::STATE_FLAG_NORMAL);
        m_confirmL1.set_label("Asset folder:\n"+ m_datadir + "\nand Meta data:\n" + m_metadir);
        if (m_datadir.length()<1) {
            m_confirmL1.set_label("No asset folder selected\n");
            m_confirmL2.set_label("Meta data\n"+ m_metadir);
            m_confirmL1.override_color (Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
        }else{
            m_confirmL1.override_color (Gdk::RGBA("black"), Gtk::STATE_FLAG_NORMAL);
            m_confirmL2.set_label("");
        }
      }

 delete dialog;
}

bool CreateAssistant::get_recursivescan(){
    return m_scanrecursive.get_active();
}

bool CreateAssistant::get_includeext(){
    return m_includeext.get_active();
}

bool CreateAssistant::get_includeprefix(){
    return m_prefix.get_active();
}

int CreateAssistant::get_dircount(){
    return m_dircount.get_value();
}

int CreateAssistant::get_charcount(){
    return m_charcount.get_value();
}

std::string CreateAssistant::get_keycol(){
    return m_keycol.get_text();
}

bool CreateAssistant::get_portable(){
    return m_portable.get_active();
}

std::string CreateAssistant::get_name(){
    return m_name.get_text();
}

void CreateAssistant::get_result(bool& check_state, Glib::ustring& entry_text)
{

}


void CreateAssistant::on_assistant_apply()
{
   hide();
}

void CreateAssistant::on_assistant_cancel()
{
    hide();
}

void CreateAssistant::on_assistant_close()
{
    hide();
}

void CreateAssistant::on_assistant_prepare(Gtk::Widget* /* widget */)
{
    set_title(Glib::ustring::compose("Gtk::Assistant example (Page %1 of %2)",
    get_current_page() + 1, get_n_pages()));
}

void CreateAssistant::on_entry_changed()
{

}

OpenAssistant::OpenAssistant()
{

   // m_entry.signal_changed().connect(sigc::mem_fun(*this,&OpenAssistant::on_entry_changed));
}

void OpenAssistant::set_labels(){

      //Set Labels  
      m_introL.set_label("You can open an asset store from an existing configuration or select individual data stores and meta stores.");
      set_page_title(m_intro, "Intro"); 

      m_dataL.set_label("Select a local Data Store or import a portable Data Store");
      m_dataB.set_label("Open local storage");
      m_data_importB.set_label("Import portable storage");
      set_page_title(m_data, "Select Data Store");
      m_datadirL.set_label("No Data Store selected");
      set_page_title(m_meta, "Select Meta Store");
      m_metaB.set_label("Browse");
      m_metaL.set_label("Select Meta Store");
      m_metadirL.set_label("No Meta Store selected");
      m_confirmL1.set_label("Nothing selected\n");
      set_page_title(m_confirm, "Confirm");
      m_methodL.set_label("Use existing configuration?");

}

void OpenAssistant::create_window()
{
    set_title("Open Asset Store");
    set_default_size(800, 200);

    append_page(m_intro);
    append_page(m_data);
    append_page(m_meta);
    append_page(m_confirm);
     

//Intro page

      set_page_complete(m_intro, true);
        m_intro.attach(m_introL,1,1,2,1);
        m_intro.attach_next_to(m_methodL, m_introL, Gtk::POS_BOTTOM,1,1);
        m_intro.attach_next_to(m_method, m_methodL, Gtk::POS_RIGHT,1,1);
        m_method.signal_toggled().connect(sigc::mem_fun(*this,&OpenAssistant::on_method_selected));
        m_method.set_active(false);
        
        m_storeModel = Gtk::ListStore::create(m_store_config);
        m_store_treeView.set_model(m_storeModel);
        m_store_treeView.remove_all_columns();
        m_store_treeView.append_column("Configuration", m_store_config.namecol);
        m_store_treeView.append_column("Data Store", m_store_config.datacol);
        m_store_treeView.append_column("Meta Store", m_store_config.metacol);
        m_store_treeView.signal_cursor_changed().connect(sigc::mem_fun(*this, &OpenAssistant::on_store_selected));
        
      set_page_type(m_intro, Gtk::ASSISTANT_PAGE_INTRO);
  //Choose Data Store

      m_data.add(m_dataL);

      m_data.attach_next_to(m_dataB,m_dataL,Gtk::POS_BOTTOM);
      m_data.attach_next_to(m_data_importB,m_dataB,Gtk::POS_BOTTOM);
      set_page_type(m_data, Gtk::ASSISTANT_PAGE_CONTENT);
      set_page_complete(m_data, true);
      m_dataB.signal_clicked().connect(sigc::mem_fun(*this,&OpenAssistant::on_select_folder));
      m_data_importB.signal_clicked().connect(sigc::mem_fun(*this,&OpenAssistant::on_select_import));
      m_datadirL.set_margin_top(20);

      m_datadirL.override_color (Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
      m_data.attach_next_to(m_datadirL,m_data_importB,Gtk::POS_BOTTOM);
 
  //Choose Meta Store
      m_meta.add(m_metaL);
      m_meta.attach_next_to(m_metaB,m_metaL,Gtk::POS_BOTTOM);
      
      set_page_type(m_meta, Gtk::ASSISTANT_PAGE_CONTENT);
      set_page_complete(m_meta, true);
      m_metaB.signal_clicked().connect(sigc::mem_fun(*this,&OpenAssistant::on_select_dir));

      m_metadirL.set_margin_top(20);
      m_metadirL.override_color (Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
      m_meta.attach_next_to(m_metadirL,m_metaB,Gtk::POS_BOTTOM);

  //Confirm page 
      
      m_confirm.add(m_confirmL1);
      m_confirm.attach_next_to(m_confirmL2,m_confirmL1,Gtk::POS_BOTTOM);

      
      set_page_complete(m_confirm, true);
      set_page_type(m_confirm, Gtk::ASSISTANT_PAGE_CONFIRM);

      signal_apply().connect(sigc::mem_fun(*this,&OpenAssistant::on_assistant_apply));
      signal_cancel().connect(sigc::mem_fun(*this,&OpenAssistant::on_assistant_cancel));
      signal_close().connect(sigc::mem_fun(*this, &OpenAssistant::on_assistant_close));
      signal_prepare().connect(sigc::mem_fun(*this, &OpenAssistant::on_assistant_prepare));
      
    set_labels();
    
    //Gtk::Grid * m_data_copy= Glib::wrap(m_data.gobj(), true);

    resize(1, 1);
}

OpenAssistant::~OpenAssistant()
{
}

void OpenAssistant::on_method_selected(){
    if (m_method.get_active()) {
        remove_page(3);
        remove_page(2);
        remove_page(1);

        std::vector<StoreConfig> cfgs = readConfigsFromXML();
        m_storeModel->clear();
        Gtk::TreeModel::Row row;
        for (int i=0; i<cfgs.size();i++){
            row = *(m_storeModel->append());
            row[m_store_config.namecol]=cfgs[i].name;
            row[m_store_config.datacol]=cfgs[i].dataPath;
            row[m_store_config.metacol]=cfgs[i].metaPath;
        }
    
        m_intro.attach_next_to(m_store_treeView,m_methodL,Gtk::POS_BOTTOM,2,1);
        set_page_type(m_intro, Gtk::ASSISTANT_PAGE_CONFIRM);
        
    }else{
        //Gtk::Grid * m_data_copy= Glib::wrap(m_data.gobj(), true);
        //append_page(*m_data_copy);
        append_page(m_data);
        append_page(m_meta);
        append_page(m_confirm);
        m_intro.remove(m_store_treeView);
        set_page_type(m_intro, Gtk::ASSISTANT_PAGE_INTRO);
    }
    
    show_all();
}

void OpenAssistant::on_store_selected(){

    auto sel = m_store_treeView.get_selection();
    auto seliter = sel->get_selected();
    std::string d;
    std::string m;
    if(seliter) //If anything is selected
    {
      Gtk::TreeModel::Row selrow = *seliter;
      d=selrow.get_value(m_store_config.datacol);
      m=selrow.get_value(m_store_config.metacol);
    }
    
    //auto filename = fs::path(d);
    //m_data_basename = filename.filename();
    m_datadir=d;
    m_data_isdirectory = true;
    
    auto filename = fs::path(m);
    m_meta_basename=filename.filename();
    m_metadir=m;
    
    set_page_complete(m_intro, true);
}

std::vector<StoreConfig> OpenAssistant::readConfigsFromXML(){
    
    std::vector<StoreConfig> result;
    
    tinyxml2::XMLDocument * xmlConfig = new tinyxml2::XMLDocument();
    tinyxml2::XMLNode * root;

    
    if (fs::exists(XMLFileName)){
        xmlConfig->LoadFile(XMLFileName.c_str());
        root = xmlConfig->FirstChild();
        tinyxml2::XMLElement * storeNode = root->FirstChildElement("store");
        
        while (storeNode != nullptr){
            StoreConfig sc;
            sc.name = storeNode->FirstChildElement("name")->GetText();
            sc.metaPath = storeNode->FirstChildElement("meta")->GetText();
            sc.dataPath = storeNode->FirstChildElement("data")->GetText();
            result.push_back(sc);
            storeNode = storeNode->NextSiblingElement();
        }
    }
    
    return result;
    
}

void OpenAssistant::on_select_folder(){
    dialog_id = 0;
    m_files= new Gtk::FileChooserDialog("Please select a Data Store", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    m_files->add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    m_files->add_button("_Open", Gtk::RESPONSE_OK);
    m_files->set_transient_for(*this);
    m_files->set_modal(true);
    m_files->signal_response().connect(sigc::bind(sigc::mem_fun(*this, &OpenAssistant::on_file_dialog_response), m_files));
    m_files->show();
}

void OpenAssistant::on_select_import(){
    dialog_id = 0;
    m_files= new Gtk::FileChooserDialog("Please select a Data Store", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);
    
    auto filter_sst = Gtk::FileFilter::create();
    filter_sst->set_name("sstfiles");
    filter_sst->add_pattern("*.sst");
    m_files->add_filter(filter_sst);
    
    m_files->add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    m_files->add_button("_Open", Gtk::RESPONSE_OK);
    m_files->set_transient_for(*this);
    m_files->set_modal(true);
    m_files->signal_response().connect(sigc::bind(sigc::mem_fun(*this, &OpenAssistant::on_file_dialog_response), m_files));
    m_files->show();
}

void OpenAssistant::on_select_dir(){
    dialog_id = 1;
    m_files= new Gtk::FileChooserDialog("Please select a Meta Store", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);
  
    auto filter_db = Gtk::FileFilter::create();
    filter_db->set_name("dbfiles");
    filter_db->add_pattern("*.db");
//    m_files->add_filter(filter_db);
  
    m_files->add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    m_files->add_button("_Open", Gtk::RESPONSE_OK);
    m_files->set_transient_for(*this);
    m_files->set_modal(true);
    m_files->signal_response().connect(sigc::bind(sigc::mem_fun(*this, &OpenAssistant::on_file_dialog_response), m_files));

    m_files->show();
}

void OpenAssistant::on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog)
{

  //Handle the response:
  switch (response_id)
  {
    case Gtk::RESPONSE_OK:
    {
        auto filename = dialog->get_file()->get_path();

        std::cout << "Folder or File selected: " <<  filename << std::endl;
        break;
    }
    case Gtk::RESPONSE_CANCEL:
    {
      //std::cout << "Cancel clicked." << std::endl;
       // delete dialog;
        break;
    }
    default:
    {
        //std::cout << "Unexpected button clicked." << std::endl;
       // delete dialog;
        break;
    }
  }

    if (dialog_id==0){
        auto filename = dialog->get_file()->get_path();
        m_data_basename=dialog->get_file()->get_basename();
        m_datadir=filename;
        m_data_isdirectory = std::filesystem::is_directory(filename);
        m_datadirL.set_label("Data Store Selected: " + filename);
        m_datadirL.override_color (Gdk::RGBA("black"), Gtk::STATE_FLAG_NORMAL);
        m_confirmL1.set_label("You chose to open a Data Store at\n"+ m_datadir + "\nand a Meta Store at\n" + m_metadir);
        if (m_metadir.length()<1) {
            m_confirmL1.set_label("You chose to open a Data Store at\n"+ m_datadir);
            m_confirmL2.set_label("No Meta Store Selected");
            m_confirmL2.override_color (Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
        }else{
            m_confirmL2.override_color (Gdk::RGBA("black"), Gtk::STATE_FLAG_NORMAL);
            m_confirmL1.override_color (Gdk::RGBA("black"), Gtk::STATE_FLAG_NORMAL);
            m_confirmL2.set_label("");
        }
      }
    else{

        auto filename=dialog->get_file()->get_path();

        m_meta_basename=dialog->get_file()->get_basename();
        m_metadir=filename;
        m_metadirL.set_label("Meta Store Selected: " + filename);
        m_metadirL.override_color (Gdk::RGBA("black"), Gtk::STATE_FLAG_NORMAL);
        m_confirmL1.set_label("You chose to open a Data Store at\n"+ m_datadir + "\nand a Meta Store at\n" + m_metadir);
        if (m_datadir.length()<1) {
            m_confirmL1.set_label("No Data Store selected\n");
            m_confirmL2.set_label("You chose to open a Meta Store at\n"+ m_metadir);
            m_confirmL1.override_color (Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
        }else{
            m_confirmL1.override_color (Gdk::RGBA("black"), Gtk::STATE_FLAG_NORMAL);
            m_confirmL2.set_label("");
        }
      }

 delete dialog;
}


        
void OpenAssistant::get_result(bool& check_state, Glib::ustring& entry_text)
{
 // check_state = m_check.get_active();
 // entry_text = m_entry.get_text();
}


void OpenAssistant::on_assistant_apply()
{
    hide();
   // delete_all_pages();
}

void OpenAssistant::on_assistant_cancel()
{
   // delete_all_pages();
    hide();
}

void OpenAssistant::on_assistant_close()
{
  //std::cout << "Assistant was closed";
   // delete_all_pages();
    hide();
}

void OpenAssistant::on_assistant_prepare(Gtk::Widget* /* widget */)
{
//  set_title(Glib::ustring::compose("Gtk::Assistant example (Page %1 of %2)", get_current_page() + 1, get_n_pages()));
}

void OpenAssistant::on_entry_changed()
{
  // The page is only complete if the entry contains text.
/*  if(m_entry.get_text_length())
    set_page_complete(m_box, true);
  else
    set_page_complete(m_box, false);*/
}
