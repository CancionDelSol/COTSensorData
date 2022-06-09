package util;

import java.util.HashMap;

/**
 * Provides a simple way to
 *  provide a configuration
 */
public class Config {

    // Cache of settings
    private HashMap<String, Object> _settings = new HashMap<>();

    // Default Constructor
    public Config() {

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
}
