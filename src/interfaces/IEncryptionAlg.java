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
    //endregion
}