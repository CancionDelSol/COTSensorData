package implem.arduino;

import util.ConfigurableBase;
import util.Globals;

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
