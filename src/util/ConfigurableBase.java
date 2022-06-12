package util;

import java.util.HashMap;

import interfaces.IConfigurable;

/**
 * Provides a simple way to
 *  provide a configuration
 */
public class ConfigurableBase implements IConfigurable {

    //region Fields
    // Cache of settings
    private HashMap<String, Object> _settings = new HashMap<>();
    //endregion
    
    //region Properties

    //endregion

    // Default Constructor
    public ConfigurableBase() {

    }

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
}
