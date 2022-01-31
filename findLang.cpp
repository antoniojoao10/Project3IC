#include"FCM.h"

using namespace std;

int main(int argc, char** argv) {
    string lang[] = {"./txt/bg/ep-11-06-23-014.txt","./txt/cs/ep-11-06-23-014.txt","./txt/da/ep-11-06-23-014.txt","./txt/de/ep-11-06-23-014.txt","./txt/el/ep-11-06-23-014.txt","./txt/en/ep-11-06-23-014.txt","./txt/es/ep-11-06-23-014.txt","./txt/et/ep-11-06-23-014.txt","./txt/fi/ep-11-06-23-014.txt","./txt/fr/ep-11-06-23-014.txt","./txt/hu/ep-11-06-23-014.txt","./txt/it/ep-11-06-23-014.txt","./txt/pt/ep-11-06-23-014.txt"};
    string langName[] ={ "bg","cs","da","de","el","en","es","et","fi","fr","hu","it","pt"};
    int first = 0;
    double bestRes = 0;
    int best = 0;
    int i = 0;
    
    for( i = 0; i <sizeof(lang)/sizeof(lang[0]) ; i++){
        FCM fc;
        double res1 = fc.main(lang[i],atoi(argv[2]), (double)atoi(argv[3])/100 );

        double res2 = fc.lang(argv[1],atoi(argv[2]), (double)atoi(argv[3])/100 );

        if (first == 0){
            bestRes = abs(res1 - res2);
            best = i;
        }else if (bestRes > abs(res1 - res2))
        {
            bestRes = abs(res1 - res2);
            best = i;
        }
        cout << "Testing language:\t" << langName[i] << endl;
        cout << "Entropy\t\t-->\t" << res1 << endl;
        cout << "Entropy using table from previous\t-->\t" << res2 << endl;
        first++;
    }
    cout << "Language is:\t" << langName[best]<< endl;
    return 0;
}