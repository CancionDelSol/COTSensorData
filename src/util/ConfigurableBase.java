package util;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import java.io.File;

import interfaces.IConfigurable;
import interfaces.callbacks.IErrorCallback;

/**
 * The base class for a configurable
 *  object. It loads, saves, and
 *  provides access to settings
 */
public class ConfigurableBase implements IConfigurable {

    //region Constants
    private static final String KEY_XML_NAME = "key";
    private static final String VALUE_XML_NAME = "value";
    //endregion

    //region Fields
    private HashMap<String, String> _settings = new HashMap<>();
    private boolean _isConfigured = false;
    private String _configPath = "";
    //endregion

    //region Properties
    public boolean getIsConfigured() {
        return _isConfigured;
    }
    //endregion

    //region Constructor
    public ConfigurableBase(String configPath) {
        _configPath = configPath;

        LoadConfiguration(_configPath, null);
    }
    //endregion

    //region Methods
    // Set a setting
    public void SetSetting(String name, String value, IErrorCallback onError) {
        _settings.put(name, value);
    }

    // Get a setting
    public String GetSetting(String name, IErrorCallback onError) {

        // Return the setting if present
        if (_settings.containsKey(name))
            return _settings.get(name);

        // Return null otherwise
        return null;
    }

    // Load Configuration from file
    public boolean LoadConfiguration(String configPath, IErrorCallback onError) {
        // Use the configPath as filename
        File fXmlFile = new File(configPath);

        // Document builder factory
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();

        try {
            // Document builder to parse
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();

            // Parse XML document
            Document doc = dBuilder.parse(fXmlFile);

            // Normalize head element
            doc.getDocumentElement().normalize();
            
            // Get the setting elements
            NodeList nodeList = doc.getElementsByTagName("setting");

            // Loop through elements and save the values
            for (int i = 0; i < nodeList.getLength(); i++) {
                // Element
                Element ele = (Element)nodeList.item(i);

                // Save value and key into settings dictionary
                String key = ele.getAttribute(KEY_XML_NAME);
                String val = ele.getAttribute(VALUE_XML_NAME);

                // Place into settings
                if (!_settings.containsKey(key))
                    _settings.put(key, val);
                else
                    Logger.Warn("Duplicate value for key: " + key);
            }

        } catch (ParserConfigurationException | SAXException | IOException exc) {
            // Log exception
            Logger.Error("Parsing error: " + exc.getMessage());

            // Callback
            try {
                if (onError != null) 
                    onError.onError();
            } catch (Exception onErrorException) {
                Logger.Error("Error occurred in callback: " + onErrorException.getMessage());
            }

            // Return failure
            return false;
        }
        
        return true;
    }

    // Save Configuration to file
    public boolean SaveConfiguration(String configPath, IErrorCallback onError) {
        
    }
    //endregion
}
