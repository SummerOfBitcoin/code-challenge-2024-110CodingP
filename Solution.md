# Sources consulted
Bitcoin Stack Exchange (Bitcoin related resources)
Odin Project (Web related resources)
LeftAsExercise
bitcoin repo

# Thinking Process
First, we need to parse the json files to get the required info.//done

Second, we need to validate the transactions using that info, but then how do we order the transactions?
//serialise
//dp problem (recursively build utxo)



Third,build the block
Fourth, we need to find the nonce which passes difficulty and hence the hash
We need to output the coinbase txn also


// since cpp doesn't have a function for iterating over files in a directory had to make "txns.txt".

//not all have witness
//not all have scriptpubkey_address

needed
Your script must generate an output file named `output.txt` with the following structure:
- First line: The block header.
- Second line: The serialized coinbase transaction.
- Following lines: The transaction IDs (txids) of the transactions mined in the block, in order. The first txid should be that of the coinbase transaction

//Credits: Dane
You have to:
serialize the transaction as per the input address type (scriptpubkey_type in the prevout)
append the sighash_type (present at the end of the signature you are verifying) at the end of the trimmed tx byte sequence 
double hash 256(trimmed_tx)
parse the signature, publickey, tx_hash into SIGNATURE, PUBLIC KEY and MESSAGE objects using Secp256k1 libraries,
then verify the message against the public key and signature  using ecdsa verification functions

basic procedure is this, you have do research for the whole thing. 