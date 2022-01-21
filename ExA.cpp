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


using namespace std;

int main(int argc, char** argv) {

    ifstream ifs(argv[1]);
    string line;
    string allLines;
    map<char,int> histMap;

    ofstream ofs (argv[2], ios::out | ios::binary);
    
    while(!ifs.fail()){
        getline(ifs,line);
        allLines.append(line);
    }
    for( int i = 0; i < allLines.size(); ++i) {
        histMap[allLines[i]] ++;
    }
    //histogram

    ofstream hist("hist.txt");

    map<char, int>::iterator itr;
    for (itr = histMap.begin(); itr != histMap.end(); ++itr) {
        hist << itr->first << "\t ----> \t" << itr->second << endl;
    }
    hist.close();
    return 0;
}
