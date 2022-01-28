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

bool cmp(pair<string, int>& a,
         pair<string, int>& b)
{
    return a.second > b.second;
}
  
// Function to sort the map according
// to value in a (key-value) pairs
map<string,int> sort(map<string, int>& M)
{
  
    // Declare vector of pairs
    vector<pair<string, int> > A;

    map<string,int> res;
  
    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : M) {
        A.push_back(it);
    }
  
    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);

    for (auto& it : A) {
  
        res[it.first]=  it.second ;
    }

    return res;

}


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

int main(int argc, char** argv) {

    ifstream ifs(argv[1]);
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

    stringstream str;
     
    str << argv[2]; int x; str >> x;
    int k =  x;

    stringstream ar;

    ar << argv[3]; int p; ar >> p;
    int a = p;

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
    histMapCtx = sort(histMapCtx);
    histMapCtxChar = sort(histMapCtxChar);

    

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
        symbol_prob[tmp] = ( (double)(itrCtxChar->second + p) / (double)(histMapCtx[tmp.substr(0,3)] + ( p * alph)) ) * 100;
    }
    histCtxChar.close();

    ofstream symbol("symbol_prob.txt");

    double context_entropy = 0;

    map<string, double>::iterator itrSymbol;
    for (itrSymbol = symbol_prob.begin(); itrSymbol != symbol_prob.end(); ++itrSymbol) {
        symbol << itrSymbol->first << "\t ----> \t" << itrSymbol->second << endl;
        context_entropy += (itrSymbol->second/100) * -( log2(itrSymbol->second /100) );
    }
    symbol.close();

    cout << context_entropy << endl;

    ofstream context("context_prob.txt");

    map<string, double>::iterator itrContext;
    for (itrContext = context_prob.begin(); itrContext != context_prob.end(); ++itrContext) {
        context << itrContext->first << "\t ----> \t" << itrContext->second << endl;
    }
    context.close();

    return 0;
}
