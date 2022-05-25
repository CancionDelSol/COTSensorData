
interface ICommProto {

    //region Properties
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
    boolean EncryptedRoundTry()
    //endregion

}