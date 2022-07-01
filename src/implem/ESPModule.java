package implem;

import util.ConfigurableBase;
import util.Globals;
import util.Logger;

import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.FileDescriptor;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * Interface for the Esp-Wroom-32 module
 */
public class ESPModule extends ConfigurableBase {
    //region Fields
    private static ESPModule _singleton;
    //endregion

    //region Properties

    //endregion

    //region Constructor
    public ESPModule() throws Exception {
        super(Globals.ESP_MODULE_CONFIG_FILE);

        if (_singleton != null)
            Logger.Throw("Module instance already exists");

        _singleton = this;
    }
    //endregion

    //region Methods
    /**
     * Sends a message via serial port
     *  to the connected ESP Module, returns
     *  the module's response
     */
    public static String SendMessage(String msg) throws Exception {

        CommPortIdentifier portIdentifier = CommPortIdentifier
            .getPortIdentifier(_singleton.GetSetting("PortName", null));

        if (portIdentifier.isCurrentlyOwned()) {
            Logger.Throw("Port is already open");
        }
        return "";
    }
    //endregion

    //region ConfigurableBase
    @Override
    protected void _setDefaults() {
        SetSetting("BoardName", "ESP-WROOM-32");
        SetSetting("PortName", "COM4");
    }
    //endregion
}
