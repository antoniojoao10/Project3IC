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

        double main(string file, int k, int a) {
            ifstream ifs(file);
            string line;
            string allLines;
            map<char,int> histMap;
            map<string,int> histMapCtx;
            map<string,int> histMapCtxChar;
            map<string,double> symbol_prob;
            map<string,double> context_prob;

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
                histMap[allLines[i]] ++;
                q.pop();
                q.push(allLines[i]);
                if (i >= k-1 ) {
                    histMapCtx[print_queue(q)] ++;
                    if(i + 1 != allLines.size()){
                        histMapCtxChar[print_queue(q)+" "+allLines[i+1]]++;
                    }
                }
            }
            //histogram

            ofstream hist("histChar.txt");

            map<char, int>::iterator itr;
            for (itr = histMap.begin(); itr != histMap.end(); ++itr) {
                hist << itr->first << "\t ----> \t" << itr->second << endl;
                //hist << itr->first << "\t ----> \t" << itr->second/(double)allLines.size() * 100 << endl;
            }
            hist.close();

            ofstream histCtx("histCtx.txt");

            map<string, int>::iterator itrCtx;
            for (itrCtx = histMapCtx.begin(); itrCtx != histMapCtx.end(); ++itrCtx) {
                histCtx << itrCtx->first << "\t ----> \t" << itrCtx->second << endl;
                context_prob[itrCtx->first] = ( (double)itrCtx->second / (double)histMapCtx.size() ) * 100;
            }
            histCtx.close();

            ofstream histCtxChar("histCtxChar.txt");

            map<string, int>::iterator itrCtxChar;
            for (itrCtxChar = histMapCtxChar.begin(); itrCtxChar != histMapCtxChar.end(); ++itrCtxChar) {
                histCtxChar << itrCtxChar->first << "\t ----> \t" << itrCtxChar->second << endl;
                string tmp = itrCtxChar->first;
                symbol_prob[tmp] = ( (double)(itrCtxChar->second + a) / (double)(histMapCtx[tmp.substr(0,k)] + ( a * histMap.size())) ) * 100;
            }
            histCtxChar.close();

            ofstream symbol("symbol_prob.txt");

            map<string,double> context_entropy;

            map<string, double>::iterator itrSymbol;
            for (itrSymbol = symbol_prob.begin(); itrSymbol != symbol_prob.end(); ++itrSymbol) {
                symbol << itrSymbol->first << "\t ----> \t" << itrSymbol->second << endl;
                string tmp = itrSymbol->first;
                context_entropy[tmp.substr(0,k)] += (itrSymbol->second/100) * -( log2(itrSymbol->second/100) );
            }
            symbol.close();

            ofstream context("context_prob.txt");

            double entropy = 0;

            map<string, double>::iterator itrContext;
            for (itrContext = context_prob.begin(); itrContext != context_prob.end(); ++itrContext) {
                context << itrContext->first << "\t ----> \t" << itrContext->second << endl;
                entropy += (itrContext->second/100) * context_entropy[itrContext->first];
            }
            context.close();

            return entropy;
        }
};

int main(int argc, char** argv) {
  FCM fc;
  double res = fc.main(argv[1],atoi(argv[2]), atoi(argv[3]));
  
  cout << res << endl;
  
  return 0;
}