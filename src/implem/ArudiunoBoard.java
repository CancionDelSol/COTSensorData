package implem;

import util.ConfigurableBase;
import util.Globals;

public class ArudiunoBoard extends ConfigurableBase {
    //region Fields

    //endregion

    //region Properties
    
    //endregion

    //region Constructor
    public ArudiunoBoard() {
        super(Globals.ARDUINO_CONFIG_FILE);
    }
    //endregion

    //region Methods

    //endregion

    //region ConfigurableBase
    @Override
    protected void _setDefaults() {
        SetSetting("BoardName", "UnoMini");
    }
    //endregion
}