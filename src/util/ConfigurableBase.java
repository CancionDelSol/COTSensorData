package util;

import java.util.HashMap;

import interfaces.IConfigurable;

/**
 * The base class for a configurable
 *  object. It loads, saves, and
 *  provides access to settings
 */
public class ConfigurableBase implements IConfigurable {

    //region Fields
    private HashMap<String, Object> _settings = new HashMap<>();
    private boolean _isConfigured = false;
    //endregion

    //region Properties
    public boolean getIsConfigured() {
        return _isConfigured;
    }
    //endregion

    //region Constructor
    public ConfigurableBase() {

    }
    //endregion

    //region Methods
    // Set a setting
    public void SetSetting(String name, Object value) {
        _settings.put(name, value);
    }

    // Get a setting
    public Object GetSetting(String name) {

        // Return the setting if present
        if (_settings.containsKey(name))
            return _settings.get(name);

        // Return null otherwise
        return null;
    }

    // Load Configuration from file
    public void LoadConfiguration(String configPath) {

    }

    // Save Configuration to file
    public void SaveConfiguration(String configPath) {

    }
    //endregion
}
