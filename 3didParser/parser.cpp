#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "duckdb.hpp"
#include <algorithm>
#include <regex>

using namespace duckdb;

class Parser{
    public:

        ~Parser(){;} 
        std::string filename;
        size_t delimsize=1;
        DuckDB * db;
        Connection * con;
        
        Parser(std::string p_fn){ 
            filename=p_fn;        
            db = new DuckDB("normalized.db");           
        }
        

        std::vector<std::string> splitstring(std::string p_in){
            
            int i=0;
            
            std::vector<std::string> v;

            if (!p_in.empty()) {
                int start = 0;
                do {
                    
                    // Find the index of occurrence
                    int idx = p_in.find("\t", start);
                    
                    if (idx == std::string::npos) {
                        break;
                    }
         
                    // If found add the substring till that
                    // occurrence in the vector

                    int length = idx - start;
                    v.push_back(p_in.substr(start, length));
                    start += (length + delimsize);

                } while (true);
                

                v.push_back(p_in.substr(start));

            }
                   
            return v;
        }
        
        void read(){
            Connection conn(*db); 
            conn.Query("drop table if exists ddi");
            conn.Query("drop table if exists ppi");
            conn.Query("create table ddi(DDI_ID INT, Domain1 TEXT, Domain2 TEXT, Pfam1 TEXT, Pfam2 TEXT)");
            conn.Query("create table ppi(DDI_ID INT, PDB TEXT, chain1 TEXT, chain2 TEXT, start1 INT, start1suffix CHAR, end1 INT, end1suffix CHAR, start2 INT, start2suffix CHAR, end2 INT, end2suffix CHAR, score FLOAT, zscore FLOAT, topology1 INT, topology2 INT, res1 TEXT[], res2 TEXT[], pos1 INT[], pos1suffix CHAR[], pos2 INT[], pos2suffix CHAR[], type TEXT[])");
           
           std::ifstream file(filename); 
           std::stringstream buffer;
           buffer << file.rdbuf();
           std::string text=buffer.str();
           std::cout << "Found text with " << text.size() << " characters." << std::endl;
           
           std::vector<std::string> textV = splitstring(text);
               
            std::cout << "Split into vector with " << textV.size() << " words." << std::endl;

                std::cout << "size: " << textV.size() << std::endl;
                
                std::vector<std::string> domain1;
                std::vector<std::string> domain2;
                std::vector<std::string> pfam1;
                std::vector<std::string> pfam2;
                
                std::vector<int> domainID;
                std::vector<std::string> PDB;
                std::vector<std::string> chain1;
                std::vector<std::string> chain2;
                std::vector<std::string> start1;
                std::vector<std::string> end1;
                std::vector<std::string> start2;
                std::vector<std::string> end2;
                std::vector<std::string> start1s;
                std::vector<std::string> end1s;
                std::vector<std::string> start2s;
                std::vector<std::string> end2s;
                std::vector<float> score;
                std::vector<float> zscore;
                std::vector<std::string> topo1;
                std::vector<std::string> topo2;
                std::vector<std::vector<std::string>> res1;
                std::vector<std::vector<std::string>> res2;
                std::vector<std::vector<std::string>> pos1;
                std::vector<std::vector<std::string>> pos2;
                std::vector<std::vector<std::string>> type;
                std::vector<std::vector<std::string>> pos1s;
                std::vector<std::vector<std::string>> pos2s;
                bool residue;
                std::regex capitals ("[A-Za-z]");
                std::smatch m;
                
            for (int i=0;i<textV.size();i++) {
                
                residue = true;                
                
                if (textV[i].find("//")!=std::string::npos){
                	continue;
                }
                if (textV[i].find("#=ID")!=std::string::npos){
                    domain1.push_back(textV[i+1]);
                    domain2.push_back(textV[i+2]);
                    size_t s1=textV[i+3].find("(")+1;
                    size_t e1=textV[i+3].find("@");
                    pfam1.push_back(textV[i+3].substr(s1,e1-s1));
                    size_t s2=textV[i+4].find("P");
                    size_t e2=textV[i+4].find("@");
                    pfam2.push_back(textV[i+4].substr(s2,e2-s2));
                    i+=4;
                    residue=false;
                }
                
                if (textV[i].find("#=3D")!=std::string::npos && residue){
                    domainID.push_back(domain1.size()-1);
                    PDB.push_back(textV[i+1]);
                    
                    size_t delim1 = textV[i+2].find(":");
                    size_t delim2 = textV[i+2].find("-");
                    if (delim2-delim1 == 1) delim2=textV[i+2].find("-",delim2+1);
                    chain1.push_back(textV[i+2].substr(delim1-1,1));
                    
                    
                    std::string s1=textV[i+2].substr(delim1+1,delim2-delim1-1);
                    std::string e1=textV[i+2].substr(delim2+1,textV[i+2].size()-(delim2));
                    
                    std::regex_search(s1,m,capitals);
                    if (m.empty()) {
                    	start1.push_back(s1);
                    	start1s.push_back("");
                    }
                    else {
                    	start1.push_back(m.prefix());
                    	start1s.push_back(m[0]);
                    }
                    	
                    std::regex_search(e1,m,capitals);
                    if (m.empty()) {
                    	end1.push_back(e1);
                      	end1s.push_back("");
                    }
                    else {
                    	end1.push_back(m.prefix());
                    	end1s.push_back(m[0]);
                    }
                    
                    delim1 = textV[i+3].find(":");
                    delim2 = textV[i+3].find("-");
                    if (delim2-delim1 == 1) delim2=textV[i+3].find("-",delim2+1);
                    chain2.push_back(textV[i+3].substr(delim1-1,1));
                    
                    std::string s2 = (textV[i+3].substr(delim1+1,delim2-delim1-1));
                    std::string e2 = (textV[i+3].substr(delim2+1,textV[i+3].size()-(delim2)));
                    
                    std::regex_search(s2,m,capitals);
                    if (m.empty()) {
                    	start2.push_back(s2);
                        start2s.push_back("");
                    }
                    else {
                    	start2.push_back(m.prefix());
                    	start2s.push_back(m[0]);
                    }
                    
                    std::regex_search(e2,m,capitals);
                    if (m.empty()) {
                    	end2.push_back(e2);
                        end2s.push_back("");
                    }
                    else {
                    	end2.push_back(m.prefix());
                    	end2s.push_back(m[0]);
                    }
                    
                    score.push_back(stof(textV[i+4]));
                    zscore.push_back(stof(textV[i+5]));
                    delim1 = textV[i+6].find(":");
                    if (delim1 != std::string::npos){
                        topo1.push_back((textV[i+6].substr(0,delim1)));
                        topo2.push_back((textV[i+6].substr(delim1+1,textV[i+6].size()-(delim1))));
                        i+=6;
                    }else{
                        topo1.push_back("");
                        topo2.push_back("");
                        i+=5;
                    }
                    std::vector<std::string> p1;
                    pos1.push_back(p1);
                    std::vector<std::string> p2;
                    pos2.push_back(p2);
                    std::vector<std::string> p1s;
                    pos1s.push_back(p1s);
                    std::vector<std::string> p2s;
                    pos2s.push_back(p2s);
                    std::vector<std::string> c1;
                    res1.push_back(c1);
                    std::vector<std::string> c2;
                    res2.push_back(c2);
                    std::vector<std::string> t1;
                    type.push_back(t1);
                    
                    residue=false;
                }
                

                
                if (residue==true){

                    if (textV[i].find("#")!=std::string::npos){	i--;  	continue; }
                    
                    res1[res1.size()-1].push_back(textV[i]);
                    if (textV[i+1].find("#")!=std::string::npos){ 
                    	res2[res2.size()-1].push_back("");
                    	pos1[pos1.size()-1].push_back("");
                    	pos2[pos2.size()-1].push_back("");
                    	type[type.size()-1].push_back("");
                    	continue;
					}
					
                    res2[res2.size()-1].push_back(textV[i+1]);
                    if (textV[i+2].find("#")!=std::string::npos){ 
                    	i+=1;
                    	pos1[pos1.size()-1].push_back("");
                    	pos2[pos2.size()-1].push_back("");
                    	type[type.size()-1].push_back("");
                    	continue;
					}
			
		
					std::regex_search(textV[i+2],m,capitals);
                    if (m.empty()) pos1[pos1.size()-1].push_back((textV[i+2]));
                    	else {
                    		for (int j=pos1s[pos1s.size()-1].size();j<pos1[pos1.size()-1].size();j++) 
                    			pos1s[pos1s.size()-1].push_back("");
                    		
                    		pos1s[pos1s.size()-1].push_back(m[0]);
                    		pos1[pos1.size()-1].push_back(m.prefix());
                    	}
                    if (textV[i+3].find("#")!=std::string::npos){ 
                    	i+=2;
                    	pos2[pos2.size()-1].push_back("");
                    	type[type.size()-1].push_back("");
                    	continue;
					}		

                    std::regex_search(textV[i+3],m,capitals);
                    if (m.empty()) pos2[pos2.size()-1].push_back((textV[i+3]));
                    	else {
                    		for (int j=pos2s[pos2s.size()-1].size();j<pos2[pos2.size()-1].size();j++) 
                    			pos2s[pos2s.size()-1].push_back("");
            
                    		pos2[pos2.size()-1].push_back(m.prefix());
                    		pos2s[pos2s.size()-1].push_back(m[0]);
                    	}
                    if (textV[i+4].find("#")!=std::string::npos){ 
                    	i+=3;
                    	type[type.size()-1].push_back("");
                    	continue;
					}
					
                    type[type.size()-1].push_back(textV[i+4]);
                    i+=4;
                }
            }

             
            
            
            for (int i=0;i<domain1.size();i++){
                std::stringstream query;
                query << "INSERT INTO ddi VALUES(" << i <<",'" << domain1[i]<<"','" << domain2[i]<<"','" << pfam1[i]<<"','" <<  pfam2[i]+"')";
                conn.Query(query.str());
            }
            
            Appender appender(conn, "ppi");
            for (int i=0;i<domainID.size();i++){
                std::stringstream res1a;
                res1a << "[";
                for (int j=0;j<res1[i].size()-1;j++) {res1a << ""<< res1[i][j] << ",";}
                res1a <<""<<  res1[i][res1[i].size()-1] <<"]";
                
                std::stringstream res2a;
                res2a << "[";
                for (int j=0;j<res2[i].size()-1;j++) {res2a << ""<< res2[i][j] << ",";}
                res2a << ""<< res2[i][res2[i].size()-1] <<"]";
                
                std::stringstream pos1a;
                pos1a << "[";
                for (int j=0;j<pos1[i].size()-1;j++) {pos1a << ""<< pos1[i][j] << ",";}
                pos1a << ""<< pos1[i][pos1[i].size()-1] <<"]";
                
                std::stringstream pos2a;
                pos2a << "[";
                for (int j=0;j<pos2[i].size()-1;j++) {pos2a << ""<< pos2[i][j] << ",";}
                pos2a << ""<< pos2[i][pos2[i].size()-1] <<"]";
                
                std::stringstream typea;
                typea << "[";
                for (int j=0;j<type[i].size()-1;j++) {typea << ""<< type[i][j] << ",";}
                typea << ""<< type[i][type[i].size()-1] <<"]";
                
                std::stringstream pos2sa;
                if (pos2s[i].size()>0){
		            pos2sa << "[";
		            for (int j=0;j<pos2s[i].size()-1;j++) {pos2sa << ""<< pos2s[i][j] << ",";}
					for (int j=pos2s[i].size()-1;j<pos2[i].size()-1;j++) {pos2sa << ",";}
		            if (pos2s[i].size()==pos2[i].size()) pos2sa << pos2s[i][pos2s[i].size()-1] <<"]";
		            	else pos2sa <<"]";
		         }else pos2sa << "";
		         
		        std::stringstream pos1sa;
                if (pos1s[i].size()>0){
		            pos1sa << "[";
		            for (int j=0;j<pos1s[i].size()-1;j++) {pos1sa << ""<< pos1s[i][j] << ",";}
					for (int j=pos1s[i].size()-1;j<pos1[i].size()-1;j++) {pos1sa << ",";}
		            if (pos1s[i].size()==pos1[i].size()) pos1sa << pos1s[i][pos1s[i].size()-1] <<"]";
		            	else pos1sa <<"]";
		         }else pos1sa << "";
		         
                
                std::stringstream query;
               	query << domainID[i] <<"|" << PDB[i]+"|" << chain1[i]<<"|" << chain2[i]<<"|";
               	query << start1[i] << "|" << start1s[i] << "|" ;
               	query << end1[i] << "|" << end1s[i] << "|";
               	query << start2[i] << "|" << start2s[i] << "|";
               	query << end2[i] << "|" << end2s[i] << "|";
               	query << score[i] << "|" << zscore[i] << "|";
				topo1[i].length()==0 ? query << "|" : query << topo1[i] << "|";
				topo2[i].length()==0 ? query << "| " : query << topo2[i] << "|"; 
				res1[i].size()==0 ? query << "|" : query << res1a.str() << "|"; 
				res2[i].size()==0 ? query << "|" : query << res2a.str() <<"|"; 
				pos1[i].size()==0 ? query << "|" : query << pos1a.str() <<"|"; 
				pos1s[i].size()==0 ? query << "|" : query << pos1sa.str() <<"|";
				pos2[i].size()==0 ? query << "|" : query << pos2a.str() <<"|"; 
				pos2s[i].size()==0 ? query << "|" : query << pos2sa.str() <<"|";
				type[i].size()==0 ? query << "" : query << typea.str();
				std::string q=query.str();
                
                std::cerr << q << std::endl;                
                
                //Unfortunately the appender crashes without any useful error message
                /*std::vector<int32_t> pos1int;
                for (int j=0;j<pos1[i].size();j++) pos1int.push_back(stoi(pos1[i][j]));
				std::vector<int32_t> pos2int;
                for (int j=0;j<pos2[i].size();j++) pos2int.push_back(stoi(pos2[i][j]));

                std::stringstream query2;
                appender.BeginRow();
                appender.Append<int32_t>(domainID[i]);
                appender.Append<string>(PDB[i]);
                appender.Append<std::string>(chain1[i]); 
                appender.Append<std::string>(chain2[i]);
               	appender.Append<int32_t>(stoi(start1[i])); 
               	appender.Append<std::string>(start1s[i]);
               	appender.Append<int32_t>(stoi(end1[i]));
               	appender.Append<std::string>(end1s[i]);
               	appender.Append<int32_t>(stoi(start2[i])); 
               	appender.Append<std::string>(start2s[i]);
               	appender.Append<int32_t>(stoi(end2[i]));
               	appender.Append<std::string>(end2s[i]);
               	appender.Append<float>(score[i]);
               	appender.Append<float>(zscore[i]);
				appender.Append<int32_t>(stoi(topo1[i]));
				appender.Append<int32_t>(stoi(topo2[i])); 
				appender.Append<std::vector<std::string>>(res1[i]); 
				appender.Append<std::vector<std::string>>(res2[i]); 
				appender.Append<std::vector<int32_t>>(pos1int); 
				appender.Append<std::vector<std::string>>(pos1s[i]);
				appender.Append<std::vector<int32_t>>(pos2int); 
				appender.Append<std::vector<std::string>>(pos2s[i]);
				appender.Append<std::vector<std::string>>(type[i]);
				std::string q2=query2.str();
				std::cerr << q2 << std::endl; 
				
				appender.EndRow();*/
				

            }
        
    }//end function
};//end class

int main (int argc, const char * argv[]) {
    Parser *p = new Parser("3did_flat");
    p->read();
    return 0;
}



