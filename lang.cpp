#include"FCM.h"

using namespace std;

int main(int argc, char** argv) {
  FCM fc;
  double res1 = fc.main(argv[1],atoi(argv[2]), (double)atoi(argv[3])/100 );

  double res2 = fc.lang(argv[4],atoi(argv[2]), (double)atoi(argv[3])/100 );
  
  cout << "Entropy\t\t-->\t" << res1 << endl;
  cout << "Entropy using table from previous\t-->\t" << res2 << endl;
  
  return 0;
}