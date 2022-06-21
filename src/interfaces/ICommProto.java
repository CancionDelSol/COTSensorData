package interfaces;
/**
 * Communication Protocol interface
 */
public interface ICommProto {

    //region Properties
    /**
     * Get successfully connected flag
     */
    boolean getIsConnected();
    //endregion

    //region Methods
    /**
     * Do an encrypted round
     *  trip. Null encAlg
     *  for no encryption
     * Return false if message
     *  is incorrect
     * Called server-side
     */
    boolean RoundTripMessage(String message, IEncryptionAlg encryptionAlg);

    /**
     * Client-side receive message
     *  and respond
     */
    String ProcessIncomingMessage(String message, IEncryptionAlg encryptionAlg);

    /**
     * Get the protocol's easy
     *  to read name
     */
    String getName();
    //endregion

}