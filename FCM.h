#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include <bitset>
#include <type_traits>
#include<climits>
#include<vector>  
#include<stdio.h>
#include<string.h>
#include <map>
#include <iterator>
#include<sstream>
#include<bits/stdc++.h>
#include<sys/stat.h>
#include <unistd.h>


using namespace std;

class FCM{
    public:
        map<char,int> histMap;
        map<string,int> histMapCtx;
        map<string,int> histMapCtxChar;
        double nBits;
        
        int global_ctx_count;

        
        string print_queue(queue<char> q)
        {   
            string res = "";
            while (!q.empty())
            {
                res += q.front();
                q.pop();
            }
            return res;
        }

        double main(string file, int k, double a) {
            ifstream ifs(file);
            string line;
            string allLines;
            map<string,double> symbol_prob;
            map<string,double> context_prob;

            int total_ctx_count = 0;

            
            while(getline(ifs,line)){
                allLines.append(line);
            }

            ifs.close();

            queue<char> q ;

            for(int i = 0 ; i < k ; i++){
                q.push(' ');
            }

            for( int i = 0; i < allLines.size(); ++i) {
                histMap[tolower(allLines[i])] ++;
                q.pop();
                q.push(tolower(allLines[i]));
                if (i >= k-1 ) {
                    histMapCtx[print_queue(q)] ++;
                    if(i + 1 != allLines.size()){
                        char s = tolower(allLines[i+1]);
                        histMapCtxChar[print_queue(q)+" " + s ]++;
                    }
                }
            }
            //histogram

            map<char, int>::iterator itr;
            map<string, int>::iterator itrCtx;
            for (itrCtx = histMapCtx.begin(); itrCtx != histMapCtx.end(); ++itrCtx) {
                total_ctx_count += itrCtx->second;
                context_prob[itrCtx->first] = ( (double)itrCtx->second / (double)histMapCtx.size() ) * 100;
                for (itr = histMap.begin(); itr != histMap.end(); ++itr) {
                    string tmp = itrCtx->first;
                    symbol_prob[tmp + " " + itr->first] = ( (double)(histMapCtxChar[tmp + " " + itr->first] + a) / (double)(itrCtx->second + ( a * histMap.size())) ) * 100;
                }
            }
            map<string,double> context_entropy;

            map<string, double>::iterator itrSymbol;
            for (itrSymbol = symbol_prob.begin(); itrSymbol != symbol_prob.end(); ++itrSymbol) {
                string tmp = itrSymbol->first;
                context_entropy[tmp.substr(0,k)] += (itrSymbol->second/100) * -( log2(itrSymbol->second/100) );
                nBits += (-( log2(itrSymbol->second/100))) ;
            }

            double entropy = 0;

            map<string, double>::iterator itrContext;
            for (itrContext = context_prob.begin(); itrContext != context_prob.end(); ++itrContext) {
                entropy += (double)(histMapCtx[itrContext->first])/ total_ctx_count * context_entropy[itrContext->first];
            }

            global_ctx_count = total_ctx_count;

            return entropy;
        }


        double lang(string file, int k, double a){
            ifstream ifs(file);
            string line;
            string allLines;
            map<char,int> histMapLang;
            map<string,int> histMapCtxLang;
            map<string,int> histMapCtxCharLang;
            map<string,double> symbol_probLang;
            map<string,double> context_probLang;
            map<string,double> context_entropyLang;
            

            int alph = 27;
            
            while(getline(ifs,line)){
                allLines.append(line);
            }

            ifs.close();

            queue<char> q ;

            for(int i = 0 ; i < k ; i++){
                q.push(' ');
            }

            for( int i = 0; i < allLines.size(); ++i) {
                histMapLang[tolower(allLines[i])] ++;
                q.pop();
                q.push(tolower(allLines[i]));
                if (i >= k-1 ) {
                    histMapCtxLang[print_queue(q)] ++;
                    if(i + 1 != allLines.size()){
                        char s = tolower(allLines[i+1]);
                        histMapCtxCharLang[print_queue(q)+" " + s ]++;
                    }
                }
            }
            
            map<char, int>::iterator itr;
            map<string, int>::iterator itrCtx;
            for (itrCtx = histMapCtxLang.begin(); itrCtx != histMapCtxLang.end(); ++itrCtx) {
                for (itr = histMapLang.begin(); itr != histMapLang.end(); ++itr) {
                    string tmp = itrCtx->first;
                    symbol_probLang[tmp + " " + itr->first] = ( (double)(histMapCtxChar[tmp + " " + itr->first] + a) / (double)(histMapCtx[itrCtx->first] + ( a * histMap.size())) ) * 100;
                }
            }

            map<string, double>::iterator itrSymbol;
            for (itrSymbol = symbol_probLang.begin(); itrSymbol != symbol_probLang.end(); ++itrSymbol) {
                string tmp = itrSymbol->first;
                context_entropyLang[tmp.substr(0,k)] += (itrSymbol->second/100) * -( log2(itrSymbol->second/100) );
                nBits += (-( log2(itrSymbol->second/100))) ;
            }

            double entropy = 0;

            map<string, int>::iterator itrContext;
            for (itrContext = histMapCtxLang.begin(); itrContext != histMapCtxLang.end(); ++itrContext) {
                entropy += (double)(histMapCtx[itrContext->first])/ global_ctx_count * context_entropyLang[itrContext->first];
            }

            return entropy;
        }

        void readLang(string lang, int k){
            bool ext = exists("./savedLang/" + lang + to_string(k) + "_histChar.txt");
            if(ext){
                histMap.clear();
                histMapCtx.clear();
                histMapCtxChar.clear();
                global_ctx_count = 0;
                nBits = 0;
                ifstream ifs("./savedLang/" + lang + to_string(k) + "_histChar.txt");
                string line;
                while(getline(ifs,line)){
                    size_t pos = 0;
                    string key;
                    string val;
                    string delimiter = "\t";
                    while ((pos = line.find("\t")) != string::npos) {
                        key = line.substr(0, pos);
                        line.erase(0, pos + delimiter.length());
                        val = line;
                        break;
                    }
                    char* char_arr = &key[0];
                    histMap[char_arr[0]] = stoi(val);
                }
                ifs.close();

                ifstream ifs1("./savedLang/" + lang + to_string(k) + "_histCtx.txt");
                while(getline(ifs1,line)){
                    size_t pos = 0;
                    string key;
                    string val;
                    string delimiter = "\t";
                    while ((pos = line.find("\t")) != string::npos) {
                        key = line.substr(0, pos);
                        line.erase(0, pos + delimiter.length());
                        val = line;
                        break;
                    }
                    global_ctx_count += stoi(val);
                    histMapCtx[key] = stoi(val);
                }
                ifs1.close();

                ifstream ifs2("./savedLang/" + lang + to_string(k) + "_histCtxChar.txt");
                while(getline(ifs2,line)){
                    size_t pos = 0;
                    string key;
                    string val;
                    string delimiter = "\t";
                    while ((pos = line.find("\t")) != string::npos) {
                        key = line.substr(0, pos);
                        line.erase(0, pos + delimiter.length());
                        val = line;
                        break;
                    }
                    histMapCtxChar[key] = stoi(val);
                }
                ifs2.close();
            }
            else throw invalid_argument("Language with K does not exist");
        }

        void saveLang(string lang, string file, int k, double a){
            bool ext = exists("./savedLang/" + lang + to_string(k) + "_histChar.txt");
            if(!ext){
                double ent = main(file,k,a);

                cout << "Entropy\t\t-->\t" << ent << endl;

                ofstream hist("./savedLang/" + lang + to_string(k) + "_histChar.txt");
                map<char, int>::iterator itr;
                for (itr = histMap.begin(); itr != histMap.end(); ++itr) {
                    hist << itr->first << "\t" << itr->second << endl;
                    
                }
                hist.close();

                ofstream histCtx("./savedLang/" + lang + to_string(k) + "_histCtx.txt");
                map<string, int>::iterator itrCtx;
                for (itrCtx = histMapCtx.begin(); itrCtx != histMapCtx.end(); ++itrCtx) {
                    histCtx << itrCtx->first << "\t" << itrCtx->second << endl;
                }
                histCtx.close();

                ofstream histCtxChar("./savedLang/" + lang + to_string(k) +"_histCtxChar.txt");
                map<string, int>::iterator itrCtxChar;
                for (itrCtxChar = histMapCtxChar.begin(); itrCtxChar != histMapCtxChar.end(); ++itrCtxChar) {
                    histCtxChar << itrCtxChar->first << "\t" << itrCtxChar->second << endl;
                }
                histCtxChar.close();

                ofstream knowLang ("./savedLang/lang.txt", ios_base::app);
                knowLang << lang + "_k" + to_string(k) << endl;
                knowLang.close();
            }
            else throw invalid_argument("Language already exists");
        }

        inline bool exists (const std::string& name) {
            struct stat buffer;   
            return (stat (name.c_str(), &buffer) == 0); 
        }
};
