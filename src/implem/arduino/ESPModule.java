package implem.arduino;

import util.ConfigurableBase;
import util.Globals;

import com.pi4j.Pi4J;
import com.pi4j.io.gpio.digital.DigitalInput;
import com.pi4j.io.gpio.digital.DigitalOutput;
import com.pi4j.io.gpio.digital.DigitalState;
import com.pi4j.io.gpio.digital.PullResistance;
import com.pi4j.util.Console;

/**
 * Interface for the Esp-Wroom-32 module
 */
public class ESPModule extends ConfigurableBase {
    //region Fields

    //endregion

    //region Properties

    //endregion

    //region Constructor
    public ESPModule() {
        super(Globals.ESP_MODULE_CONFIG_FILE);
    }
    //endregion

    //region Methods

    //endregion

    //region ConfigurableBase
    @Override
    protected void _setDefaults() {
        SetSetting("BoardName", "ESP-WROOM-32");
    }
    //endregion
}
