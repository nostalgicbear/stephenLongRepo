package client;

import java.io.*;
import java.security.PublicKey;
//import java.security.PublicKey;

import javax.crypto.*;

/*
 * In this class an AES key is generated and saved to file called "AESKeyFile". The RSA public key
 * generated in the RSAKeyPairGen class is read in via a file input stream (simulates server sending to client) and
 * it is used to encrypt the AES key. The encrypted AES key is then saved to a file called "encryptedAESKey" (this 
 * simulates the key being sent to the server as the server can read the file in via a file input stream from the 
 * saved location)
 */

public class AESKeyGen
{
    public static void main(String args[])
    {
        try
        {
            // File for writing output
            FileOutputStream keyFOS = new FileOutputStream("src/client/AESKeyFile");
            ObjectOutputStream keyOOS = new ObjectOutputStream(keyFOS);
            
            // Generate random AES key
            KeyGenerator keygen = KeyGenerator.getInstance("AES");
            SecretKey aesKey = keygen.generateKey();
            keyOOS.writeObject(aesKey);
            
            //Message to verify AES key is generated
            System.out.println("AES key generated and written to file: AESKeyFile");
             
            keyOOS.close();
            keyFOS.close();
            
         // File containing RSA public key - Reading in
            FileInputStream keyFIS = new FileInputStream("src/client/RSAPublicKeyFile");
            ObjectInputStream keyOIS = new ObjectInputStream(keyFIS);

            // Create RSA cipher instance
            Cipher rsaCipher = Cipher.getInstance("RSA/ECB/PKCS1Padding");

            // Initialize the cipher for encryption
            rsaCipher.init(Cipher.ENCRYPT_MODE, (PublicKey) keyOIS.readObject());
            
            keyOIS.close();
            keyFIS.close();

            // File for writing output
            FileOutputStream fos = new FileOutputStream("src/server/encryptedAESKey");

            //Here .getEncoded returns a representation of the aesKey in byte format
            byte[] unencrypted = aesKey.getEncoded();

            // Encrypt the plaintext using the rsaCipher instance
            byte[] encrypted = rsaCipher.doFinal(unencrypted);

            // Write ciphertext to file specified above
            fos.write(encrypted);
            fos.close();
            
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }
}
