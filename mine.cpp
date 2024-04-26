#include <iostream>//damn! the stream is really I/O stream!
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct Output {
  int Amount;
  string ScriptPubKey;
}

struct Input {
  string txId;
  int vOut;
  string scriptSig;
  string sequence;
  vector<string> witness;
  vector<Output> prevout;
  string scriptSigAsm;
  bool isCoinbase;
}

struct Txn {
  int version;
  int locktime;
  vector<Input> vin;
  vector<Output> vout;

}

string serialise(string content) {
    string serialised;
    int sz = content.size();
    return serialised;
}

int main() {

    freopen("output.txt","w",stdout);

    ifstream myfile;
    myfile.open("txns.txt");
    string filename;
    vector<string> txns;

    while (myfile.good()) {
        getline(myfile,filename);
        txns.push_back(filename);
    }
    myfile.close();

    for (string txn: txns) {//man this outer loop is running approx 8000 times!
      string path = "mempool/" + txn;
      myfile.open(path);
      string content;
      while (myfile.good()) {
        string line;
        getline(myfile,line);
        content+=line;
      }
      serialise(content);

      myfile.close();
    }
    return 0;
}