package implem.protocols;

import interfaces.ICommProto;
import interfaces.IEncryptionAlg;

/**
 * Bluetooth tranceiver
 * 
 * Server-Side:
 *  - Uses on-board bluetooth transmission
 *     for laptop
 * 
 * Client-Side:
 *  - Uses ESP-WROOM-32 module
 */
public class BlueToothCommProto  implements ICommProto {
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
    public BlueToothCommProto() {
        
    }
    //endregion

    //region Methods
    @Override
    public boolean RoundTripMessage(String message, IEncryptionAlg encryptionAlg) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public boolean ProcessIncomingMessage(String message, IEncryptionAlg encryptionAlg) {
        // TODO 
        return false;
    }
    //endregion
}
