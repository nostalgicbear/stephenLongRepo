package server;

import java.io.*;
import java.security.*;
import javax.crypto.*;
import javax.crypto.spec.*;

public class RSADecrypt
{
  public static void main(String args[])
  {
    /*
     * Reads in the RSA private key and uses it to decrypt the encrypted AES key.
     */

    try
    {
      // File containing RSA private key
      FileInputStream keyFIS = new FileInputStream("src/server/RSAPrivateKeyFile");
      ObjectInputStream keyOIS = new ObjectInputStream(keyFIS);

      // Create RSA cipher instance
      Cipher rsaCipher = Cipher.getInstance("RSA/ECB/PKCS1Padding");

      // Initialize the cipher for encryption
      rsaCipher.init(Cipher.DECRYPT_MODE, (PrivateKey) keyOIS.readObject());

      keyOIS.close();
      keyFIS.close();

      // Read ciphertext from file and decrypt it
      FileInputStream fis = new FileInputStream("src/server/encryptedAESKey");
      BufferedInputStream bis = new BufferedInputStream(fis);
      CipherInputStream cis = new CipherInputStream(bis, rsaCipher);

      /*
       * The encrypted key is read into the buffer bit by bit until it reaches its end. It is then pieced together
       * and its toString is accessible.
       */
      StringBuffer decryptedAESKey= new StringBuffer();
      int c;
      while ((c = cis.read()) != -1){
        decryptedAESKey.append((char) c);
      }
      cis.close();
      bis.close();
      fis.close();

      
      //Specify destination to save
      FileOutputStream decryptedKeyFOS = new FileOutputStream("src/server/decryptedAESKey");
      ObjectOutputStream decryptedKeyOOS = new ObjectOutputStream(decryptedKeyFOS);
      
      
      String decryptedKey = decryptedAESKey.toString();
      byte [] decrypted = decryptedKey.getBytes();
      
      //create aes key and save out to file
      SecretKey decryptKey = new SecretKeySpec(decrypted, "AES");
      decryptedKeyOOS.writeObject(decryptKey);
      System.out.println("Decrypted AES key: " + decryptedAESKey.toString());
      decryptedKeyFOS.close();
      

    }
    catch (Exception e)
    {
      System.out.println(e);
    }
  }
}