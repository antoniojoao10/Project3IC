#include"FCM.h"
#include<vector>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
using namespace std;

inline bool exists (const std::string& name) {
            struct stat buffer;   
            return (stat (name.c_str(), &buffer) == 0); 
        }

void checkLang(){
    ifstream ifs("./savedLang/lang.txt");
    string line;
    while(getline(ifs,line)){
        cout << line << endl;
    }
}

void saveLang(){
    FCM fc;
    string lg;
    string file;
    string k;
    string a;

    cout << "Language(example:pt):";
    cin >> lg;
    cout << "File:";
    cin >> file;
    bool ext = exists(file);
    while(!ext){
        cout<< "File does not exist"<<endl;
        cout << endl;
        cout << "File:";
        cin >> file;
        ext = exists(file);
    }
    cout << "K value:";
    cin >> k;
    cout << "a:";
    cin >> a;
    fc.saveLang(lg,file,stoi(k), (double)stoi(a)/100 );
    double bits_symbol = fc.nBits / fc.histMap.size() ;
    cout << "Estimated number of bits per symbol: " << bits_symbol << endl;
}

void readLang(){
    vector<string> lang;
    ifstream ifs("./savedLang/lang.txt");
    string line;
    while(getline(ifs,line)){
        lang.push_back(line.substr(0,line.find("_")));
    }
    lang.erase( unique( lang.begin(), lang.end() ), lang.end() );
    int first = 0;
    double bestRes = 0;
    int best = 0;
    int i = 0;
    string file;
    string k;
    string a;
    cout << "File to guess language:";
    cin >> file;
    bool ext = exists(file);
    while(!ext){
        cout<< "File does not exist"<<endl;
        cout << endl;
        cout << "File:";
        cin >> file;
        ext = exists(file);
    }
    cout << "K value:";
    cin >> k;
    cout << "a:";
    cin >> a;

    for( i = 0; i <lang.size() ; i++){
        FCM fc;
        fc.readLang(lang[i], stoi(k));
        double res2 = fc.lang(file,stoi(k), (double)stoi(a)/100 );

        if (first == 0){
            bestRes = res2;
            best = i;
        }else if (bestRes < res2)
        {
            bestRes = res2;
            best = i;
        }
        cout << "Testing language:\t" << lang[i] << endl;
        cout << "Entropy using table from lang\t-->\t" << res2 << endl;
        double bits_symbol = fc.nBits / fc.histMap.size() ;
        cout << "Estimated number of bits per symbol: " << bits_symbol << endl;
        first++;
    }
    cout << "Language is:\t" << lang[best]<< endl;
}

int main(int argc, char** argv) {
    string lang[] = {"./txt/bg/ep-11-06-23-014.txt","./txt/cs/ep-11-06-23-014.txt","./txt/da/ep-11-06-23-014.txt","./txt/de/ep-11-06-23-014.txt","./txt/el/ep-11-06-23-014.txt","./txt/en/ep-11-06-23-014.txt","./txt/es/ep-11-06-23-014.txt","./txt/et/ep-11-06-23-014.txt","./txt/fi/ep-11-06-23-014.txt","./txt/fr/ep-11-06-23-014.txt","./txt/hu/ep-11-06-23-014.txt","./txt/it/ep-11-06-23-014.txt","./txt/pt/ep-11-06-23-014.txt"};
    string langName[] ={ "bg","cs","da","de","el","en","es","et","fi","fr","hu","it","pt"};
    

    int prog = 1;
    while(prog != 0){
        cout << "Programs:" << endl;
        cout << "Press 1 : Check known languages" << endl;
        cout << "Press 2 : Learn new language" << endl;
        cout << "Press 3 : Guess file language" << endl;
        cout << "Press 0 : LEAVE" << endl;
        cout << "Enter ---->";
        cin >> prog;
        switch(prog){
            case 1:
                cout << endl;
                cout << endl;
                checkLang();
                cout << endl;
                cout << endl;
                break;
            case 2:
                cout << endl;
                cout << endl;
                saveLang();
                cout << endl;
                cout << endl;
                break;
            case 3:
                cout << endl;
                cout << endl;
                readLang();
                cout << endl;
                cout << endl;
                break;
            case 0:
                break;
            default:
                cout << "Invalid input" << endl;
                cout << "Programs:" << endl;
                cout << "Press 1 : Check known languages" << endl;
                cout << "Press 2 : Learn new language" << endl;
                cout << "Press 3 : Check file language" << endl;
                cout << "Press 0 : LEAVE" << endl;
                cout << "Enter ---->";
                cin >> prog;
        }
    }
    
    return 0;
}