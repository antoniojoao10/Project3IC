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


using namespace std;

class FCM{
    public:
        map<char,int> histMap;
        map<string,int> histMapCtx;
        map<string,int> histMapCtxChar;
        map<string,double> symbol_prob;
        map<string,double> context_prob;
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
            }

            double entropy = 0;

            map<string, int>::iterator itrContext;
            for (itrContext = histMapCtx.begin(); itrContext != histMapCtx.end(); ++itrContext) {
                cout << (double)(histMapCtx[itrContext->first])/ total_ctx_count << endl;
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
            int total_ctx_count = 0;
            map<char, int>::iterator itr;
            map<string, int>::iterator itrCtx;
            for (itrCtx = histMapCtxLang.begin(); itrCtx != histMapCtxLang.end(); ++itrCtx) {
                total_ctx_count += itrCtx->second;
                for (itr = histMapLang.begin(); itr != histMapLang.end(); ++itr) {
                    string tmp = itrCtx->first;
                    symbol_probLang[tmp + " " + itr->first] = ( (double)(histMapCtxChar[tmp + " " + itr->first] + a) / (double)(itrCtx->second + ( a * histMapLang.size())) ) * 100;
                }
            }

            map<string, double>::iterator itrSymbol;
            for (itrSymbol = symbol_probLang.begin(); itrSymbol != symbol_probLang.end(); ++itrSymbol) {
                string tmp = itrSymbol->first;
                context_entropyLang[tmp.substr(0,k)] += (itrSymbol->second/100) * -( log2(itrSymbol->second/100) );
            }

            double entropy = 0;

            map<string, int>::iterator itrContext;
            for (itrContext = histMapCtxLang.begin(); itrContext != histMapCtxLang.end(); ++itrContext) {
                entropy += (double)(histMapCtx[itrContext->first])/ global_ctx_count * context_entropyLang[itrContext->first];
            }

            return entropy;
        }
};
