package client;
import java.security.*;
import java.io.*;
import javax.crypto.*;
import javax.crypto.spec.*;
import java.util.Scanner;

public class AESEncrypt
{
    /*
     * The client uses the already generated AES key to encrypt whatever message the user enters when they are
     * prompted. This secret message is then saved to a file called "secretMessageFromClient". The hash of the 
     * secret message is taken via the sha-1 hash function and saved to a file called "hashSecretMessage".
     */
    public static void main(String args[])
    {
        try
        { 
            // File containing secret AES key
            FileInputStream keyFIS = new FileInputStream("src/client/AESKeyFile");
            ObjectInputStream keyOIS = new ObjectInputStream(keyFIS);
            
            // Read in the AES key
            SecretKey aesKey = (SecretKey) keyOIS.readObject();
            keyOIS.close();
            keyFIS.close();
            
            // set IV (required for CBC)
            
            byte[] iv ={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
            IvParameterSpec ips = new IvParameterSpec(iv);
            
            // Create AES cipher instance
            Cipher aesCipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
            
            // Initialize the cipher for encryption
            aesCipher.init(Cipher.ENCRYPT_MODE, aesKey, ips);
            
            // File for writing output
            FileOutputStream fos = new FileOutputStream("src/server/secretMessageFromClient");
            
           
            // This is the messge to be encrypted. Entered by user in console
            System.out.println("Enter message :");
            Scanner scan = new Scanner(System.in);
            String secretMessage = scan.nextLine();
            byte plaintext[] = secretMessage.getBytes();
         
            
            // Encrypt the plaintext
            byte[] ciphertext = aesCipher.doFinal(plaintext);
            // Write ciphertext to file
            fos.write(ciphertext);
            fos.close();
            scan.close();          
            
            // File for writing output
            FileOutputStream fos2 = new FileOutputStream("src/client/hashSecretMessage");

            // Create MessageDigest object
            MessageDigest md = MessageDigest.getInstance("SHA-1");
       
            // This is the message to be hashed
            byte inputBuf[] = secretMessage.getBytes();

            // Create the hash value 
            byte outputHash[] = md.digest(inputBuf);

            // Write hash value to file
            fos2.write(outputHash);
            System.out.println(8*outputHash.length + "-bit hash written to file");

            fos2.close();
  
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }
}
