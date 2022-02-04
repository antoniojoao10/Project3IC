#include"FCM.h"

using namespace std;

int main(int argc, char** argv) {
  FCM fc;
  double res1 = fc.main(argv[1],atoi(argv[2]), (double)atoi(argv[3])/100 );
  
  cout << "Entropy\t\t-->\t" << res1 << endl;
  double bits_symbol = fc.nBits / fc.histMap.size() ;
  cout << "Estimated number of bits per symbol: " << bits_symbol << endl;
  
  return 0;
}