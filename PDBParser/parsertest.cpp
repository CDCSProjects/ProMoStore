// A simple program counting residues with an OXT atom

#include <filesystem>
#include <iostream>
#include <storage.h>

#include <cif++.hpp>

namespace fs = std::filesystem;
namespace sci = SciStore;

void createTables(sci::Storage<> * st){
    //Create additional metadata tables
    st->add_meta_table("audit_conform", "PDBID", "PDBID TEXT, dict_name TEXT, dict_version FLOAT, dict_location TEXT");
    st->add_meta_table("database_2", "PDBID", "PDBID TEXT, database_id TEXT, database_code TEXT, pdbx_database_accession TEXT, pdbx_DOI TEXT");
    st->add_meta_table("pdbx_database_status", "PDBID", "PDBID TEXT, statuscode TEXT, status_code_sf TEXT, status_code_mr TEXT, entry_id TEXT, recvd_initial_deposition_date DATE, SG_entry TEXT, deposit_site TEXT, process_site TEXT, status_code_cs TEXT, status_code_nmr_data TEXT, methods_development_category TEXT, pdb_format_compatible TEXT");
    st->add_meta_table("audit_author", "PDBID", "PDBID TEXT, name TEXT, pdbx_ordinal INT, identifier_ORCID TEXT");
    st->add_meta_table("citation", "PDBID", "PDBID TEXT, abstract TEXT, abstract_id_CAS TEXT, book_id_ISBN TEXT, book_publisher TEXT, book_publisher_city TEXT, book_title TEXT, coordinate_linkage TEXT, country TEXT, database_id_Medline TEXT, details TEXT, id TEXT, journal_abbrev TEXT, journal_id_ASTM TEXT, journal_id_CSD TEXT, journal_id_ISSN TEXT, journal_full TEXT, journal_issue TEXT, journal_volume TEXT, language TEXT, page_first TEXT, page_last TEXT, title TEXT, year TEXT, database_id_CSD TEXT, pdbx_database_id_DOI TEXT, pdbx_database_id_PubMed TEXT, pdbx_database_id_patent TEXT, unpublished_flag TEXT");
    st->add_meta_table("citation_author", "PDBID", "PDBID TEXT, citation_id TEXT, name TEXT, ordinal INT, identifier_ORCID TEXT");
  
}

void add(sci::Storage<> * st, cif::file file){    

    // Take the first datablock in the file
    cif::datablock &db = file.front();
    
  
    std::string pdb_id;
  auto &status = db["pdbx_database_status"];
    for (const auto &[statuscode, codesf,codemr,pdbid,initdepdate,sgentry,depsite,processsite,codecs,codenmrdata,devcat,formatcomp] :
            status.find<std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string>(
                cif::key("entry_id") != "",
                "status_code","status_code_sf", "status_code_mr", "entry_id", "recvd_initial_deposition_date", "SG_entry", "deposit_site", "process_site", "status_code_cs", "status_code_nmr_data", "methods_development_category","pdb_format_compatible"))
    {
        //std::cout << statuscode << " - " << codesf<< " - " << codemr<< " - " << pdbid<< " - " << initdepdate<< " - " << sgentry<< " - " << depsite<< " - " << processsite<< " - " << codecs<< " - " << codenmrdata<< " - " << devcat<< " - " << formatcomp<< " - " << std::endl;
        st->insert_new_meta_row("'"+pdbid+"'");
        pdb_id=pdbid;
        st->insert_new_meta_row("'"+pdbid+"','"+statuscode+"','"+codesf+"','"+codemr+"','"+pdbid+"','"+initdepdate+"','"+sgentry+"','"+depsite+"','"+processsite+"','"+codecs+"','"+codenmrdata+"','"+devcat+"','"+formatcomp+"'","pdbx_database_status");
    }
    
    status = db["audit_conform"];
    for (const auto &[dict_name, dict_version, dict_location] :
            status.find<std::string,float,std::string>(
                cif::key("dict_name") != "BLUBB",
                "dict_name","dict_version", "dict_location"))
    {
            st->insert_new_meta_row("'"+pdb_id+"','"+dict_name+"',"+std::to_string(dict_version)+",'"+dict_location+"'","audit_conform");
    }
    
    status = db["database_2"];
    for (const auto &[database_id, database_code, pdbx_database_accession, pdbx_DOI] :
            status.find<std::string,std::string,std::string,std::string>(
                cif::key("database_id") != "BLUBB",
                "database_id","database_code", "pdbx_database_accession", "pdbx_DOI"))
    {
            st->insert_new_meta_row("'"+pdb_id+"','"+database_id+"','"+ database_code +"','"+pdbx_database_accession+"','"+ pdbx_DOI + "'","database_2");
    }
    
    status = db["audit_author"];
    for (const auto &[name, pdbx_ordinal, identifier_ORCID] :
            status.find<std::string,int,std::string>(
                cif::key("name") != "BLUBB",
                "name","pdbx_ordinal", "identifier_ORCID"))
    {
            st->insert_new_meta_row("'"+pdb_id+"','"+name+"',"+ std::to_string(pdbx_ordinal) +",'"+identifier_ORCID+"'", "audit_author");
    }
    
    status = db["citation"];
    for (const auto &[abstract, abstract_id_CAS, book_id_ISBN, book_publisher, book_publisher_city, book_title, coordinate_linkage, country, 
            database_id_Medline, details, id, journal_abbrev, journal_id_ASTM, journal_id_CSD, journal_id_ISSN, journal_full, journal_issue, 
            journal_volume, language, page_first, page_last, title, year, database_id_CSD, pdbx_database_id_DOI, pdbx_database_id_PubMed, 
            pdbx_database_id_patent, unpublished_flag] :
            status.find<std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,
            std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,
            std::string,std::string,std::string,std::string,std::string,std::string,std::string>(
                cif::key("abstract") != "BLUBB",
                "abstract", "abstract_id_CAS", "book_id_ISBN", "book_publisher", "book_publisher_city", "book_title", "coordinate_linkage", "country", 
            "database_id_Medline", "details", "id", "journal_abbrev", "journal_id_ASTM", "journal_id_CSD", "journal_id_ISSN", "journal_full", "journal_issue", 
            "journal_volume", "language", "page_first", "page_last", "title", "year", "database_id_CSD", "pdbx_database_id_DOI", "pdbx_database_id_PubMed", 
            "pdbx_database_id_patent", "unpublished_flag"))
    {
            st->insert_new_meta_row("'"+pdb_id+"','"+ abstract + "','" + abstract_id_CAS+"','"+ book_id_ISBN+"','"+ book_publisher+"','"+ book_publisher_city+"','"+ book_title+"','"+ 
            coordinate_linkage+"','"+ country+"','"+database_id_Medline+"','"+ details+"','"+ id+"','"+ journal_abbrev+"','"+ journal_id_ASTM+"','"+ journal_id_CSD
            +"','"+ journal_id_ISSN+"','"+ journal_full+"','"+ journal_issue+"','"+ journal_volume+"','"+ language+"','"+ page_first+"','"+ page_last+"','"+ title
            +"','"+ year+"','"+ database_id_CSD+"','"+ pdbx_database_id_DOI+"','"+ pdbx_database_id_PubMed+"','"+pdbx_database_id_patent+"','"+ unpublished_flag+"'", "citation");
    }
    
    status = db["citation_author"];
    for (const auto &[citation_id, name, ordinal,identifier_ORCID] :
            status.find<std::string,std::string,int,std::string>(
                cif::key("citation_id") != "BLUBB",
                "citation_id","name", "ordinal", "identifier_ORCID"))
    {
            st->insert_new_meta_row("'"+pdb_id+"','"+citation_id+"','"+name+"',"+ std::to_string(ordinal) +",'"+identifier_ORCID+"'", "citation_author");
    }
   /* std::vector<std::string> ids = st->get_IDs_by_constraint("pdbx_database_status.process_site='RCSB'");
    std::cout << "ID: " << ids[0] << std::endl;
    
    st->get_by_constraint("pdbx_database_status.SG_entry='N'");*/
        

    
   /* auto &audit_conform = db["audit_conform"];
    for (const auto &[nam, ver, loc] :
            audit_conform.find<std::string, float, std::string>(
                cif::key("dict_name") != "",
                "dict_name", "dict_version", "dict_location"))
    {
        std::cout << nam << ' ' << ver << ' ' << loc << std::endl;
    }
    
    // Use the atom_site category
    auto &atom_site = db["atom_site"];
    // Count the atoms with atom-id "OXT"
    //auto n = atom_site.count(cif::key("label_atom_id") == "OXT");
    auto n = atom_site.count(cif::key("label_atom_id") == "OG");
    std::cout << "File contains " << atom_site.size() << " atoms of which "
              << n << (n == 1 ? " is" : " are") << " OG" << std::endl
              << "residues with an OXT are:" << std::endl;

    // Loop over all atoms with atom-id "OXT" and print out some info.
    // That info is extracted using structured binding in C++
    for (const auto &[asym, comp, seqnr] :
            atom_site.find<std::string, std::string, int>(
                cif::key("label_atom_id") == "OG",
                "label_asym_id", "label_comp_id", "label_seq_id"))
    {
        std::cout << asym << ' ' << comp << ' ' << seqnr << std::endl;
    }*/


}

int main(int argc, char *argv[])
{
    if (argc != 2)
        exit(1);

    // Read file, can be PDB or mmCIF and can even be compressed with gzip.

    
    const fs::path path = argv[1];
    std::cout << "path: " << path << std::endl;

    //Create/Open a SciFi storage   
    sci::Storage<> * st = new sci::Storage<>("PDB_Data","PDB_Meta");
    st->create_empty_metadata_table("PDBID TEXT", 0);
    createTables(st);
      
    if (!fs::is_directory(path)){
        //Add data to meta store 
        cif::file file = cif::pdb::read(argv[1]);
        add(st,file);
        if (file.empty())
        {
            std::cerr << "Empty file" << std::endl;
            exit(1);
        }
    }else{
        for (fs::recursive_directory_iterator i(path), end; i != end; ++i) {
        if (!fs::is_directory(i->path())){
            std::cout << i->path()<< "\n";
            cif::file file;
            try{
              file =cif::pdb::read((i->path()).generic_string());
              add(st,file);
            }catch(...){
                std::cerr << "Error in file " << i->path()<< "\n";
                continue;
            }
          }
        }
    }
    return 0;
}


