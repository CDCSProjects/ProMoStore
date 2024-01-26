#include "codewindow.h"

void CodeWindow::prepareWindow(){
    add(m_grid);
    
    m_filterL.set_label("Filter");
    m_filterModel = Gtk::ListStore::create(m_filter_col);
    Gtk::TreeModel::Row row;
    std::vector<std::string> filters = storage->get_all_filters();
    Gtk::TreeModel::Row rowfilter;
    m_filterModel = Gtk::ListStore::create(m_filter_col);
    for (int i=0; i<filters.size(); i++){
        rowfilter = *(m_filterModel->append());
        rowfilter[m_filter_col.col]=filters[i];
    }
    m_filter.set_model(m_filterModel);
    m_filter.pack_start(m_filter_col.col);
    
    m_langToolL.set_label("Language/Tool");
    m_langModel = Gtk::ListStore::create(m_lang_col);
    Gtk::TreeModel::Row rowlang;
    rowlang = *(m_langModel->append());
    rowlang[m_lang_col.col]="C++";
    rowlang = *(m_langModel->append());
    rowlang[m_lang_col.col]="Python";
    rowlang = *(m_langModel->append());
    rowlang[m_lang_col.col]="Pytorch";
    m_langTool.set_model(m_langModel);
    m_langTool.pack_start(m_lang_col.col);
    
    m_grid.add(m_filterL);
    m_grid.add(m_langToolL);
    m_filterL.set_margin_top(10);
    m_langToolL.set_margin_top(10);
    m_grid.attach_next_to(m_filter,m_filterL, Gtk::POS_BOTTOM);
    m_grid.attach_next_to(m_langTool,m_langToolL, Gtk::POS_BOTTOM);
    
    m_apply.set_label("Apply");
    m_grid.attach_next_to(m_apply, m_filter, Gtk::POS_BOTTOM, 2, 1);
    m_apply.signal_clicked().connect(sigc::mem_fun(*this, &CodeWindow::on_apply));
    
    m_codeL.set_label("Code");
    m_codeL.set_margin_top(10);
    m_grid.attach_next_to(m_codeL, m_apply, Gtk::POS_BOTTOM, 2, 1);
    
    m_codeBox.set_border_width(10);
    m_grid.attach_next_to(m_codeBox,m_codeL, Gtk::POS_BOTTOM,2,1);
    m_code_scroll_window.set_size_request(800,300);
    m_codeBox.add(m_code_scroll_window);
    //m_code.set_wrap_mode(Gtk::WRAP_WORD);
    m_code_scroll_window.add(m_code);
    
    m_codeBuffer = Gtk::TextBuffer::create();
    m_codeBuffer->set_text("Select a language to generate code");
    m_code.set_buffer(m_codeBuffer);
    
    m_buildL.set_label("Build/Link/Run info");
    m_build_scroll_window.add(m_build);
    m_build_scroll_window.set_size_request(800,150);
    m_buildBox.set_border_width(10);
    m_buildBox.add(m_build_scroll_window);
    m_grid.attach_next_to(m_buildL, m_codeBox, Gtk::POS_BOTTOM,2,1);
    m_grid.attach_next_to(m_buildBox, m_buildL, Gtk::POS_BOTTOM,2,1);
    
    m_buildBuffer = Gtk::TextBuffer::create();
    m_buildBuffer->set_text("build info");
    m_build.set_buffer(m_buildBuffer);
}

CodeWindow::CodeWindow(SciStore::Storage<> * p_storage){
    this->storage = p_storage;
    prepareWindow();
    show_all_children();
}

void CodeWindow::on_apply(){

    //auto filter = (*(m_filter.get_active()))[m_filter_col.col];
    //auto lang = (*(m_langTool.get_active()))[m_lang_col.col];

    std::stringstream code;
    std::stringstream buildinfo;
    
    auto fa = m_filter.get_active();
    auto la = m_langTool.get_active();
    
    auto fc = m_filter_col.col;
    auto lc = m_lang_col.col;
    
    std::cout << (*fa)[fc] << " " << (*la)[lc] << std::endl;
    
    
    if ((*la)[lc] == "C++"){
        code << create_cpp_header();
        code << create_cpp_template((*fa)[fc]);
        code << create_cpp_end();
        buildinfo << create_cpp_build();
    }
    if ((*la)[lc] == "Python"){
        code << create_python_template((*fa)[fc]);
        buildinfo << "The python wrapper can currently not use the storage class.\nHence, using the python code still ooks quite ugly and is not as neat as the C++ code.";
    }
    if ((*la)[lc] == "Pytorch"){
       code << create_pytorch_template((*fa)[fc]);
       buildinfo << "-";
    }
    
     
    m_codeBuffer->set_text(code.str());
    m_buildBuffer->set_text(buildinfo.str());
}

std::string CodeWindow::create_cpp_end(){
    std::stringstream code;
    code << "\treturn 0;\n}\n";
    return code.str();
}

std::string CodeWindow::create_cpp_header(){
    std::stringstream code;
    code << "#include <storage.h>\n\n";
    code << "int main(int argc, char *argv[]){\n";
    return code.str();
}

std::string CodeWindow::create_cpp_template(Glib::ustring p_filter){
  std::stringstream code;
  code << "\tSciStore::Storage<> * st = new SciStore::Storage<>(\"";
  code << storage->m_asset_path;
  code << "\", \"";
  code << storage->m_meta_path;
  code << "\");\n\n"; 
  
  code << "\t//Apply the filter\n";
  code << "\tstd::vector<std::string> results = storage->apply_filter(\"" << p_filter << "\");\n\n";
  
  code << "\t//Show the results\n";
  code << "\tfor (int i=0; i<results.size(); i++) std::cout << results[i] << std::endl;\n\n";
  
  return code.str();
  
}

std::string CodeWindow::create_cpp_build(){
    std::stringstream code;
    code << "#!/bin/bash\n";
    code << "export CPLUS_INCLUDE_PATH=./:<path to SciFi storage.h>:<your own include path>\n";
 /*   code << m_assettype;
    code << ">/include/:<path to ";
    code << m_metatype;
    code << ">/src/include:<your own include path>\n";*/
    
    code << "export LIBRARY_PATH=./:<path to SciFi>\n";
    
    code << "g++ -std=c++17 -O3 main.cpp -L. -o SciFi4PDB  -lscifi";
    return code.str();
}

std::string CodeWindow::create_python_template(Glib::ustring p_filter){
    std::stringstream code;
    code << "#!/usr/bin/env python3\n";
    code << "import scifi\n\n";
    
    code << "#We need a helper function to format our output string\n";
    code << "def crop_result(res):\n";
    code << "\tres = res.split(']',1)[1]\n";
    code << "\tres = res.split(\"\\n\")\n";
    code << "\tres[0] = res[0].replace(\"\\n\", '')\n";
    code << "\tres = list(filter(None,res))\n";
    code << "\treturn res\n\n";
    
    code << "#Open the meta store and the data store\n";
    code << "duck = scifi.PyDuckStore(\"" << storage->m_meta_path << "\".encode('utf-8'))\n";
    code << "rocks = scifi.PyRocksStore(\"" << storage->m_asset_path << "\".encode('utf-8'))\n";
    code << "rocks.open()\n\n";
    
    code << "#Apply the filter and format the output";
    code << "duck.execQuery(\"SELECT * FROM "<< p_filter << "\".encode('utf-8'))\n";
    code << "result = duck.getResultAsString().decode(\"utf-8\").rstrip()\n";
    code << "res = crop_result(result)\n\n";
    
    code << "#Iterate our results\n\n";
    code << "for i in res:\n";
    code << "\tprint(i)\n";
    code << "\titem = rocks.getSingle(i.encode('utf-8'))\n";
    code << "\t#Do something with item here or...\n";
    code << "\t#Write it out to a file:\n";
    code << "\t#Get the file extension\n";
    code << "\tduck.execQuery(\"SELECT fileextension FROM filedata WHERE key == '\".encode('utf-8') + i.encode('utf-8') + \"'\".encode('utf-8'))\n";
    code << "\tresult = duck.getResultAsString().decode(\"utf-8\").rstrip()\n";
    code << "\text = crop_result(result)\n";
    code << "\twith open(str(i)+str(ext[0]), 'wb') as f:\n";
    code << "\t\tf.write(item)\n";
    
    return code.str();
}

std::string CodeWindow::create_pytorch_template(Glib::ustring p_filter){
    std::stringstream code;
    
    code << "#!/usr/bin/env python3\n";
    code << "from SciFiDataset import SciFiDataset\n\n";
    
    code << "#Create a dataset\n";
    code << "scifi_dataset = SciFiDataset(datasetname=\""<< storage->m_asset_path << "\", metaname=\"" << storage->m_meta_path << "\")\n\n";
    
    code << "#Apply the filter\n";
    code << "list = scifi_dataset.getIDsFromFilter(\"" << p_filter << "\")\n\n";
    
    code << "#Iterate our results\n";
    code << "for i in list:\n";
    code << "\tprint(i)\n";
    code << "\tsample = scifi_dataset[i]\n";
    code << "\t#Do something with the sample here\n";


    return code.str();
}

CodeWindow::~CodeWindow(){

}
