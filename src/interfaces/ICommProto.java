package interfaces;
/**
 * Communication Protocol interface
 */
interface ICommProto {

    //region Properties
    /**
     * Get successfully connected flag
     */
    boolean getIsConnected();
    //endregion

    //region Methods
    /**
     * Round trip a message
     *  Return false if message
     *  is incorrect
     */
    boolean RoundTripMessage(String message);

    /**
     * Do an encrypted round
     *  trip
     * Return false if message
     *  is incorrect
     */
    boolean EncryptedRoundTrip(String message, IEncryptionAlg encryptionAlg);
    //endregion

}