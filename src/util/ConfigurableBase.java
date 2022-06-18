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

    //region Fields
    private HashMap<String, Object> _settings = new HashMap<>();
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

        LoadConfiguration(_configPath);
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

            // Iterate through the nodes
            //  and save the 

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
