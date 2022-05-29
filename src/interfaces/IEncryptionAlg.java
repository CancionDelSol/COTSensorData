package interfaces;
/**
 * Encryption Algorithm interface
 */
interface IEncryptionAlg {
    //region Methods
    /**
     *  Encrypt the input
     */
    String Encrypt(String input);

    /**
     * Decrypt the input
     */
    String Decrypt(String input);
    //endregion
}