#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <openssl/evp.h>

bool computeHash(const std::string& unhashed, std::string& hashed) {
    bool success =false;
    EVP_MD_CTX* context = EVP_MD_CTX_new();

    if (context != NULL) {
        if (EVP_DigestInit_ex(context, EVP_sha256(),NULL)) {
            if (EVP_DigestUpdate(context, unhashed.c_str(), unhashed.length())) {
                unsigned char hash[EVP_MAX_MD_SIZE];
                unsigned int lengthOfHash = 0;
                if (EVP_DigestFinal_ex(context, hash, &lengthOfHash)) {
                    std::stringstream ss;
                    for (unsigned int i=0; i<lengthOfHash; i++) {
                        ss<<std::hex << std::setw(2)<<std::setfill('0')<< (int)hash[i];
                    }
                    hashed = ss.str();
                    success = true;
                }
            }
        }
        EVP_MD_CTX_free(context);
    }
    return success;
}

int main() {
    std::string pw1= "020000000164ca1941edef34b690dd6672c7d395c60882067f7f3fc396e64d88e39c1da5b40000000000fdffffff012ea91450feb99697a4901d3fe082eca341204fb6711b9487",pw1hashed;
    computeHash(pw1, pw1hashed);

    std::cout<<pw1hashed<<std::endl;

    return 0;
}