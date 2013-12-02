Cryptography Read Me
_______________________
Autoher : Stephen Long

This project must be run in Eclipse. The project has both a client and a server folder in order to simulate a client server relationship.

Create a src folder. In it create a client folder and a server folder. 
In the client folder, place the following java files: AESKeyGen and AESEncrypt.
In the server, place the following java files: RSAKeyPairGen, RSADecrypt, and AESDecrypt.

The client folder consists of 2 classes, AESKeyGen and AESEncrypt, whereas the server consists of 3 classes, RSAKeyPairGen, RSADecrypt, and AESDecrypt.

Instructions
__________

This project must be run via Eclipse. Open the project in Eclipse.

1. Run the RSAKeyPairGen class located in the server folder. 
	The RSA public and private keys have now been generated and saved to the server folder.

2. Run the AESKeyGen class located in the client folder. 
	AESKey is now generated in client folder and encryptedAESKey is sent to server where it can be later decrypted.

3. Run the AESEncrypt class located in the server folder.
	This allows the user to enter a message that is then encrypted and sent to the server. The hash of message is also saved to the client folder.

4. Run the RSADecrypt class located in the server folder.
	This decrypts the encryptedAES key that was sent to the server in step2, and saves it to a file called decryptedAESKey. The decrypted key is now ready to be
used to decrypt the secret message.

5. Run the AESDecrypt class located in the server folder.
	This uses the decrypted AES key (from step 4) to decrypt the secret message sent to the server from the client. 
