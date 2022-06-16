package implem;

import interfaces.ICommProto;
import interfaces.IEncryptionAlg;

public class BTTranceiver  implements ICommProto {

    //region Fields

    //endregion

    //region Properties
    @Override
    public boolean getIsConnected() {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public String getName() {
        return "BlueToothTranceiver";
    }
    //endregion

    //region Constructor
    
    //endregion

    //region Methods
    @Override
    public boolean RoundTripMessage(String message) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public boolean EncryptedRoundTrip(String message, IEncryptionAlg encryptionAlg) {
        // TODO Auto-generated method stub
        return false;
    }
    //endregion
}
