#include <iostream>//damn! the stream is really I/O stream!
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//create a serialise function to serialise txns

int main() {

    freopen("output.txt","w",stdout);

    ifstream myfile;
    myfile.open("txns.txt");
    string mystring;
 
    vector<string> txns;

    while (myfile.good()) {
        getline(myfile,mystring);
        txns.push_back(mystring);
    }
    myfile.close();

    for (string txn: txns) {
      string filename = "mempool/" + txn;
      myfile.open(filename);
      //getline(myfile,mystring);
      //cout<<mystring<<'\n';
    }
    return 0;
}