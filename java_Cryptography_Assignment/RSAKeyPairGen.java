package server;

import java.io.*;
import java.security.*;
/*
 * Generates an RSA key pair. The public key is sent to the client. The private key is saved to the server.
 */

public class RSAKeyPairGen
{
  public static void main(String[] args) throws Exception
  {

      // Generate RSA key pair
      KeyPair keyPair = KeyPairGenerator.getInstance("RSA").generateKeyPair();

      // File for writing private key -Specifies path
      FileOutputStream privateKeyFOS = new FileOutputStream("src/server/RSAPrivateKeyFile");
      ObjectOutputStream privateKeyOOS = new ObjectOutputStream(privateKeyFOS);

      // File for writing publickey
      FileOutputStream publicKeyFOS = new FileOutputStream("src/client/RSAPublicKeyFile");
      ObjectOutputStream publicKeyOOS = new ObjectOutputStream(publicKeyFOS);

      // Write the keys to respective files
      privateKeyOOS.writeObject(keyPair.getPrivate());
      publicKeyOOS.writeObject(keyPair.getPublic());
      
      System.out.println("Key pair generated");
      
      privateKeyFOS.close();
      publicKeyFOS.close();
  }
}