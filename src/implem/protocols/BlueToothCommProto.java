package implem.protocols;

import interfaces.ICommProto;
import interfaces.IEncryptionAlg;
import telemetry.RoundTripResult;
import util.ConfigurableBase;
import util.Globals;

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
public class BlueToothCommProto extends ConfigurableBase implements ICommProto {
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
        return "BlueToothCommProto";
    }
    //endregion

    //region Constructor
    public BlueToothCommProto() {
        super(Globals.BLUETOOTH_PROTO_CONFIG_FILE);
    }
    //endregion

    //region Methods
    @Override
    public RoundTripResult RequestAndVerifySensorData(IEncryptionAlg encryptionAlg) {
        return new RoundTripResult(this, encryptionAlg, "Not Implemented");
    }

    @Override
    public String ProcessIncomingMessage(String message, IEncryptionAlg encryptionAlg) {
        // TODO 
        return message;
    }
    //endregion

    //region ConfigurableBase
    @Override
    protected void _setDefaults() {
        SetSetting("UseESP", "false");
        SetSetting("Timeout", "15000");
    }
    //endregion
}
