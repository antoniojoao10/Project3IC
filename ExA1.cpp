#include"FCM.h"

using namespace std;

int main(int argc, char** argv) {
  FCM fc;
  double res1 = fc.main(argv[1],atoi(argv[2]), (double)atoi(argv[3])/100 );
  
  cout << "Entropy\t\t-->\t" << res1 << endl;
  
  return 0;
}