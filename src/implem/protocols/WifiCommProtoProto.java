package implem.protocols;

import java.util.Date;

import implem.ESPModule;
import interfaces.ICommProto;
import interfaces.IEncryptionAlg;
import telemetry.RoundTripResult;
import util.ConfigurableBase;
import util.Globals;
import util.Logger;

public class WifiCommProtoProto extends ConfigurableBase implements ICommProto {
    //region Fields
    private static ESPModule _espModule = ESPModule.getModule();
    //endregion

    //region Properties
    @Override
    public boolean getIsConnected() {
        return _espModule != null;
    }

    @Override
    public String getName() {
        return "WifiTranceiver";
    }
    //endregion

    //region Constructor
    public WifiCommProtoProto() {
        super(Globals.WIFI_PROTO_CONFIG_FILE);
    }
    //endregion

    //region Methods
    @Override
    public RoundTripResult RequestAndVerifySensorData(IEncryptionAlg encryptionAlg) {
        if (_espModule == null) {
            Logger.Error("No module available");
            return new RoundTripResult(this, encryptionAlg, "Failure, no active module");
        }

        long procStartTime = (new Date()).getTime();
        Logger.Debug("Procedure Start Time: " + procStartTime);

        RoundTripResult res = null;
        try {
            Logger.Debug("Sending request to ESP module");
            String resp = ESPModule.DataRequest(encryptionAlg);

            // Split response and return results
            String[] vals = resp.split(" ");
            for (int i = 0; i < vals.length; i++) {
                Logger.Debug("Vals[" + i + "] = " + vals[i]);
            }

            if (vals.length < 4)
                throw new Exception("Invalid response");

            // Request sent by transmitter (Client)
            long rsbt = Long.parseLong(vals[0]) - ESPModule.getESPClientOrigTime();

            // Request received by receiver (Server)
            long rrbrec = Long.parseLong(vals[1]) - ESPModule.getESPServerOrigTime();

            // Response sent by receiver (Server)
            long rsbr = Long.parseLong(vals[vals.length - 2]) - ESPModule.getESPServerOrigTime();

            // Response received by transmitter (Client)
            long rrbt = Long.parseLong(vals[vals.length - 1]) - ESPModule.getESPClientOrigTime();

            res = new RoundTripResult((new Date()).getTime() - procStartTime,
                procStartTime,
                rsbt,
                rrbrec,
                rsbr,
                rrbt,
                this,
                encryptionAlg,
                "Success");
            
        } catch (Exception exc) {
            Logger.Error("Error requesting data: " + exc.getMessage());
            res = new RoundTripResult(this, encryptionAlg, "Failure, no active module");

        }

        return res;
    }

    @Override
    public String ProcessIncomingMessage(String message, IEncryptionAlg encryptionAlg) {
        
        return message;
    }
    //endregion

    //region ConfigurableBase
    @Override
    protected void _setDefaults() {
        SetSetting("UseESP", "true");
        SetSetting("Timeout", "15000");
    }
    //endregion
}
