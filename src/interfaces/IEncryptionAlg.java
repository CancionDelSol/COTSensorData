package interfaces;
/**
 * Encryption Algorithm interface
 */
public interface IEncryptionAlg {
    //region Methods
    /**
     *  Encrypt the input
     */
    String Encrypt(String input);

    /**
     * Decrypt the input
     */
    String Decrypt(String input);

    /**
     * Get the encryption
     *  easy name
     */
    String getName();

    /**
     * Get the index for
     *  this encryption algorithm
     *  for use with ESPModule
     */
    int getIndex();
    //endregion
}