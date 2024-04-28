#include <iostream>//damn! the stream is really I/O stream!
#include <fstream>
#include <string>
#include <vector>
#include <json.hpp>
#include <sstream>
#include <ios>

#define VERSION_MOD 4294967296

using json = nlohmann::json;

struct Output {
  int amount;
  std::string scriptPubKey;
  std::string scriptPubKeyAsm;
  std::string scriptPubKeyType;
  std::string scriptPubKeyAddress;
};

struct Input {
  std::string txId;
  int vOut;
  std::string scriptSig;
  int sequence;
  std::vector<std::string> witness;
  Output prevout;
  std::string scriptSigAsm;
  bool isCoinbase;
};

struct Txn {
  int version;
  int locktime;
  std::vector<Input> vin;
  std::vector<Output> vout;
  bool is_segwit;
};

void from_json(const json& j, Output& p) {
  j.at("scriptpubkey").get_to(p.scriptPubKey);
  j.at("scriptpubkey_asm").get_to(p.scriptPubKeyAsm);
  j.at("scriptpubkey_type").get_to(p.scriptPubKeyType);
  if (j.contains("scriptpubkey_address")) {
    j.at("scriptpubkey_address").get_to(p.scriptPubKeyAddress);
  }
  j.at("value").get_to(p.amount);
}

void from_json(const json& j, Input& p) {
  j.at("txid").get_to(p.txId);
  j.at("vout").get_to(p.vOut);
  j.at("prevout").get_to(p.prevout);
  j.at("scriptsig").get_to(p.scriptSig);
  j.at("scriptsig_asm").get_to(p.scriptSigAsm);
  if (j.contains("witness")) {
    j.at("witness").get_to(p.witness);
  }
  j.at("is_coinbase").get_to(p.isCoinbase);
  j.at("sequence").get_to(p.sequence);
}

void from_json(const json& j, Txn& p) {
  j.at("version").get_to(p.version);
  j.at("locktime").get_to(p.locktime);
  j.at("vin").get_to(p.vin);
  j.at("vout").get_to(p.vout);
}

std::string big_to_little(std::string s, int len) {
  std::string little;
  for (int i=len-1;i>=0;i-=2) {
    little +=s[i-1];
    little +=s[i];
  }
  return little;
}

std::string serialise(Txn t) {
  std::string serialised;

  //version
  int version = t.version%(VERSION_MOD);
  std::stringstream ss;
  ss<<std::setfill('0')<<std::setw(8)<<std::hex<<version;
  serialised+= big_to_little(ss.str(),8);
  ss.str("");

  //input
  int in_sz = t.vin.size();
  int temp=in_sz;
  int exp=1;
  while (true) {
    temp=temp/256;
    if (temp==0) {
      break;
    }
    else {
      exp++;
    }
  }
  ss<<std::setfill('0')<<std::setw(2*exp)<<in_sz;
  serialised+=ss.str();

  return serialised;
}

int main() {

  freopen("output.txt","w",stdout);
  std::ifstream myfile("txns.txt");
  std::string filename;
  std::vector<std::string> txns;

  while (myfile.good()) {
    getline(myfile,filename);
    txns.push_back(filename);
  }

  myfile.close();

  for (std::string txn: txns) {//man this outer loop is running approx 8000 times!
    std::string path = "mempool/" + txn;
    myfile.open(path);
    json data = json::parse(myfile);
    Txn t;
    from_json(data , t);
    std::cout<<serialise(t)<<std::endl;
    
    myfile.close();
  }


  return 0;
}