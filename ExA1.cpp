#include"FCM.h"

using namespace std;

inline bool exists (const std::string& name) {
            struct stat buffer;   
            return (stat (name.c_str(), &buffer) == 0); 
}

int main(int argc, char** argv) {
  bool ext = exists(argv[1]);
  if(!ext) throw invalid_argument("File does not exist");
  FCM fc;
  double res1 = fc.main(argv[1],atoi(argv[2]), (double)atoi(argv[3])/100 );
  
  cout << "Entropy\t\t-->\t" << res1 << endl;
  cout << "Numbers of bits\t-->\t" << fc.nBits << endl;
  cout << "Number of symbols\t-->\t" << fc.histMap.size() << endl;
  double bits_symbol = fc.nBits / fc.histMap.size() ;
  cout << "Estimated number of bits per symbol: " << bits_symbol << endl;
  
  return 0;
}