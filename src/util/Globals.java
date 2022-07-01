package util;

/**
 * Make some constants globally accessible
 */
public class Globals {
    //region Constants
    public static final String MAIN_CONFIG_FILE = "MainConfig.cfg";
    public static final String ESP_MODULE_CONFIG_FILE = "ESPConfig.cfg";
    public static final String ARDUINO_CONFIG_FILE = "ArdConfig.cfg";
    public static final String LOPAN_MODULE_CONFIG_FILE = "LoPanModule.cfg";
    public static final String SIX_LOWPAN_PROTO_CONFIG_FILE = "6LoWPANProtoConfig.cfg";
    public static final String WIFI_PROTO_CONFIG_FILE = "WifiProtoConfig.cfg";
    public static final String BLUETOOTH_PROTO_CONFIG_FILE = "BluetoothProtoConfig.cfg";
    //endregion

    //region Arrays
    public static final String PORT_NAMES[] = {
        "/dev/tty.usbserial-A9007UX1", // Mac OS X
        "/dev/ttyUSB0", // Linux
        "COM4", // Windows
    };
    //endregion
}
