package util;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.HashMap;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
import org.w3c.dom.Element;

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
    private static final String SETTING_XML_NAME = "setting";
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
            NodeList nodeList = doc.getElementsByTagName(SETTING_XML_NAME);

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
        Document doc;
        Element e = null;

        // Factory
        DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
        try {
            // Document builder
            DocumentBuilder db = dbf.newDocumentBuilder();

            // Document
            doc = db.newDocument();

            // Root element
            Element rootEle = doc.createElement("roles");

            // Loop over settings
            for (String key : _settings.keySet()) {
                // New Element
                e = doc.createElement(SETTING_XML_NAME);

                // Set the key and value attributes
                e.setAttribute(KEY_XML_NAME, key);
                e.setAttribute(VALUE_XML_NAME, _settings.get(key));

                // Append to root
                rootEle.appendChild(e);
            }

            // Append root to document
            doc.appendChild(rootEle);

            try {
                // Transformer
                Transformer tr = TransformerFactory.newInstance().newTransformer();

                // Set properties
                tr.setOutputProperty(OutputKeys.INDENT, "yes");
                tr.setOutputProperty(OutputKeys.METHOD, "xml");
                tr.setOutputProperty(OutputKeys.ENCODING, "UTF-8");
                tr.setOutputProperty(OutputKeys.DOCTYPE_SYSTEM, "roles.dtd");
                tr.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");

                // Send DOM to file
                tr.transform(new DOMSource(doc), 
                                    new StreamResult(
                                        new FileOutputStream(configPath)
                                        )
                                        );

            } catch (Exception exc) {
                // Throw to outer exception
               throw exc;
            }

        } catch (Exception exc) {
            // Log exception
            Logger.Error("Error saving config file: " + exc.getMessage());

            // Return failure
            return false;
        }

        // Return success
        return true;
    }
    //endregion
}
