
#include "fscrypt.h"

int getNumBlocks(int bytes);
int getPadding(int bytes);
//BLOCKSIZE = 8



void *fs_encrypt(void *plaintext, int bufsize, char *keystr, int *resultlen){
	unsigned char* ptext = (unsigned char *)plaintext;
	cout << "bufsize: " << bufsize << endl;
	
 	int padding = getPadding(bufsize);
 	cout << "Padding: " << padding << endl;
  
 	int numBlocks = getNumBlocks(bufsize);
	cout << "numBlocks: " << numBlocks << endl;
	
	//Break up input into blocks and add padding as needed
  	vector<unsigned char *> *plainBlocks = new vector<unsigned char *>();
	for(int i = 0; i < numBlocks; i++){
		int startValue = i * sizeof(unsigned char) * BLOCKSIZE;
		for(int j = 0; j < BLOCKSIZE; j++){
			if(ptext[startValue + j] == '\0'){
				for(int k = 0; k <= padding; k++){
					ptext[startValue + j + k] = (unsigned char)(((int)'0') + padding);
				}
			}
		}
    	unsigned char* tmp = (unsigned char*)malloc(BLOCKSIZE);
    	strncpy((char *)tmp, (const char *)ptext + startValue, BLOCKSIZE);
    	plainBlocks->push_back(tmp);
	}

	//Set up the key
	BF_KEY* key = (BF_KEY*)malloc(sizeof(BF_KEY));
	BF_set_key(key, bufsize, (const unsigned char*)keystr);

	//Call the encryption function
	vector<unsigned char *> *cipherBlocks = new vector<unsigned char *>();
	for(int i = 0; i < plainBlocks->size(); i++){
		if(i == 0){
			unsigned char *tmp = (unsigned char *)malloc(BLOCKSIZE * sizeof(unsigned char));
			cipherBlocks->push_back(tmp);
			BF_ecb_encrypt(plainBlocks->at(i), cipherBlocks->at(i), key, BF_ENCRYPT);
		}
		else{
			unsigned char *cipher = cipherBlocks->at(i-1);
			unsigned char *plain = plainBlocks->at(i);
			unsigned char *xorVal = (unsigned char *)malloc(BLOCKSIZE * sizeof(unsigned char));
			unsigned char *tmp = (unsigned char *)malloc(BLOCKSIZE * sizeof(unsigned char));
			//XOR the value and call encryption
			for(int j = 0; j < BLOCKSIZE; j++){
				xorVal[j] = plain[j] ^ cipher[j];
			}
			cipherBlocks->push_back(tmp);
			BF_ecb_encrypt(xorVal, cipherBlocks->at(i), key, BF_ENCRYPT);
		}
	}

	//Set resultlen to length of the ciphertext
	int outputBytes = BLOCKSIZE * sizeof(unsigned char) * numBlocks;
	*resultlen = outputBytes;

	//Take ciphertext vector and convert to char*
	int current = 0;
	unsigned char *output = (unsigned char *)malloc(outputBytes);
	for(int i = 0; i < numBlocks; i++){
		unsigned char *ctext = cipherBlocks->at(i);
		for(int j = 0; j < BLOCKSIZE; j++){
			output[current] = ctext[j];
			current++;
		}
	}

	//Return output ciphertext
	return (void *)output;
}

void *fs_decrypt(void *ciphertext, int bufsize, char *keystr, int *resultlen){
	//Break up ciphertext into blocks
	unsigned char *ctext = (unsigned char *)ciphertext;
	int numBlocks = getNumBlocks(bufsize);

	vector<unsigned char *> *cipherBlocks = new vector<unsigned char *>();
	for(int i = 0; i < numBlocks; i++){
		int startValue = i * sizeof(unsigned char) * BLOCKSIZE;
		// for(int j = 0; j < BLOCKSIZE; j++){
		// 	if(ptext[startValue + j] == '\0'){
		// 		for(int k = 0; k <= padding; k++){
		// 			ptext[startValue + j + k] = (unsigned char)(((int)'0') + padding);
		// 		}
		// 	}
		// }
    	unsigned char* tmp = (unsigned char*)malloc(BLOCKSIZE);
    	strncpy((char *)tmp, (const char *)ctext + startValue, BLOCKSIZE);
    	cipherBlocks->push_back(tmp);
    	
    	int j = 0;
  		printf("ciphertext block %d = ", i);
  		for (j = 0; j < BLOCKSIZE; j++)
      		printf("%02x", tmp[j]);
  		printf("\n");
	}

	//Set up the key
	BF_KEY* key = (BF_KEY*)malloc(sizeof(BF_KEY));
	BF_set_key(key, bufsize, (const unsigned char*)keystr);

	//Decrypt the ciphertext blocks
	vector<unsigned char *> *plainBlocks = new vector<unsigned char *>();
	for(int i = 0; i < cipherBlocks->size(); i++){
		if(i == 0){
			unsigned char *tmp = (unsigned char *)malloc(BLOCKSIZE * sizeof(unsigned char));
			plainBlocks->push_back(tmp);
			BF_ecb_encrypt(cipherBlocks->at(i), plainBlocks->at(i), key, BF_DECRYPT);
		}
		else{
			unsigned char *currentCipher = cipherBlocks->at(i);
			unsigned char *previousCipher = cipherBlocks->at(i-1);

			unsigned char *decrypted = (unsigned char *)malloc(BLOCKSIZE * sizeof(unsigned char));
			BF_ecb_encrypt(previousCipher, decrypted, key, BF_DECRYPT);

			unsigned char *xorVal = (unsigned char *)malloc(BLOCKSIZE * sizeof(unsigned char));
			for(int j = 0; j < BLOCKSIZE; j++){
				xorVal[j] = decrypted[j] ^ currentCipher[j];
			}
			plainBlocks->push_back(xorVal);
		}
	}
	//Set resultlen to length of the plaintext
	int outputBytes = BLOCKSIZE * sizeof(unsigned char) * numBlocks;
	*resultlen = outputBytes;
	//Take plaintext vector and convert to char*
	int current = 0;
	unsigned char *output = (unsigned char *)malloc(outputBytes);
	for(int i = 0; i < numBlocks; i++){
		unsigned char *block = plainBlocks->at(i);
		for(int j = 0; j < BLOCKSIZE; j++){
			output[current] = block[j];
			current++;
		}
		/*unsigned char *ptext = plainBlocks->at(i);
		for(int j = 0; j < BLOCKSIZE; j++){
			output[current] = ptext[j];
			current++;
		}*/
	}

	int j = 0;
  	printf("decrypted plaintext = ");
  		for (j = 0; j < bufsize; j++)
      		printf("%c", output[j]);
  		printf("\n");
	//Remove the padding
	//Return output plaintext
  	return (void *)output;
}

int getNumBlocks(int bytes){
  	int blocks = bytes / BLOCKSIZE;
  	if(bytes % BLOCKSIZE != 0){
    	blocks++;
  	}
  	return blocks;
}

int getPadding(int bytes){
  	int padding = 0;
  	if(bytes % BLOCKSIZE != 0){
    	padding = bytes % BLOCKSIZE;
  	}
  	return padding;
}
