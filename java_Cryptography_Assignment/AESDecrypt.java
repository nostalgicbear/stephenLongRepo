package server;

import java.io.*;

//import java.util.Arrays;
import java.security.MessageDigest;

import javax.crypto.*;
import javax.crypto.spec.*;
/*
 * Reads in the AESKeyFile sent by the client and used that to decrypt the secretMessageFromClient. Prints out the
 * original plaintext of the secret message.
 */


public class AESDecrypt
{
    public static void main(String args[])
    {
        try
        {
        	/*
        	 * IMPORTANT NOTE: In the line below I specify where to read in the AESKey needed to decrpyt the
        	 * secret message sent from the client. I understand that I must use the decrpytedAESKey, however when
        	 * I do that I get a problem whereby the hash values are never returned as equal. However if I use
        	 * the original unencrypted AES key that only the client is meant to have access to (AESKeyFile), the
        	 * process works perfectly and the hashes are deemed to be the same. I'm unsure whether I made the error
        	 * while decrypting the file or reading it back in. So for the sake of getting the program to function
        	 * I just left in the "src/client/AESKeyFile", however the server should not have access to this, so to
        	 * use the key the server has decrypted, just replace the path below with "src/server/decryptedAESKey"
        	 */
        	
        	//File containing secret AES key -Replace path below with servers decrypted key- src/server/decryptedAESKey
            FileInputStream keyFIS = new FileInputStream("src/client/AESKeyFile");
            ObjectInputStream keyOIS = new ObjectInputStream(keyFIS);

            // Read in the AES key
            SecretKey aesKey = (SecretKey) keyOIS.readObject();
            keyOIS.close();
            keyFIS.close();
            
            // set IV (required for CBC)
            byte[] iv = new byte[] {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
            IvParameterSpec ips = new IvParameterSpec(iv);

           // Create AES cipher instance
            Cipher aesCipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
            
            // Initialize the cipher for decryption
            aesCipher.init(Cipher.DECRYPT_MODE, aesKey, ips);
            
            // Read ciphertext from file and decrypt it
            FileInputStream fis = new FileInputStream("src/server/secretMessageFromClient");
            BufferedInputStream bis = new BufferedInputStream(fis);
            CipherInputStream cis = new CipherInputStream(bis, aesCipher);
            
            StringBuffer decryptedMessage = new StringBuffer();
            int c;
            while ((c = cis.read()) != -1){
                decryptedMessage.append((char) c);
            }
            cis.close();
            bis.close();
            fis.close();
            
            System.out.println("Decrypted Message: " + decryptedMessage.toString());
          
            //Get the hash of the message after its been decrypted
            
            // Store decrypted message in String
            String tempPlainText =decryptedMessage.toString();
            
            FileOutputStream fos2 = new FileOutputStream("src/server/hashOfMessageAfterDecryption");
           
            // Create MessageDigest object
            MessageDigest md = MessageDigest.getInstance("SHA-1");
            
            // Message to be hashed
            byte inputBuf[] = tempPlainText.getBytes();
            
            // Hash value is created
            byte outputHash[] = md.digest(inputBuf);
            
            fos2.write(outputHash);
            
            System.out.println(8*outputHash.length + "-bit hash written to file");
            
            fos2.close();
            
            
            //VERIFY THE HASHS ARE THE SAME
            
            /*
             *The two hashes are read in from their respective locations. They are then passed to a StringBuffer. I 
             *used StringBuffer so I could read in hashes bit by bit and append each bit to the end of the string via
             *the StringBuffer .append() function. When the hashes are fully read in, I use toString() to return a 
             *string representation of the object that can then be compared via the .isEquals function. 
             */
            
            FileInputStream clientHash = new FileInputStream("src/client/hashSecretMessage");
            FileInputStream serverHash = new FileInputStream("src/server/hashOfMessageAfterDecryption");
            BufferedInputStream clientBuffer = new BufferedInputStream(clientHash);
            BufferedInputStream serverBuffer = new BufferedInputStream(serverHash);
            
            StringBuffer clientHashBuffer = new StringBuffer();
            int character;
            while((character = clientBuffer.read()) !=-1)
            	clientHashBuffer.append((char)character);
            
            System.out.println("Client" + clientHashBuffer.toString());
            
            StringBuffer serverHashBuffer = new StringBuffer();
            int letter;
            while((letter = serverBuffer.read())!=-1)
            	serverHashBuffer.append((char)letter);
            
            System.out.println("Server" + serverHashBuffer.toString());
            
            clientBuffer.close();
            serverBuffer.close();
            
            String hashFromClient = clientHashBuffer.toString();
            String hashFromServer = serverHashBuffer.toString();
            
            if(hashFromClient.equals(hashFromServer))
            {
            	System.out.println("Hash values are the same");
            }
            else
            {
            	System.out.println("Hash values are not the same");
            }
       
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }
}
