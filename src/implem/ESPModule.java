package implem;

import util.ConfigurableBase;
import util.Globals;
import util.Logger;

import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import interfaces.IEncryptionAlg;

import java.io.FileDescriptor;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Date;

import javax.imageio.plugins.tiff.GeoTIFFTagSet;

/**
 * Interface for the Esp-Wroom-32 module
 * 
 * Accepted Messages:
 *  HANDSHAKE - Initialize Connection
 *  GETDATA   - Makes request for ESP module
 *              to get sensor data from a
 *              collector source over WiFi
 *  SYNC      - Used to synchonize loops
 */
public class ESPModule extends ConfigurableBase {
    //region Constants
    private static final String PORT_NAME = "PortName";
    private static final String BOARD_NAME = "BoardName";
    private static final String TIMEOUT = "Timeout";
    //endregion

    //region Fields
    private static ESPModule _singleton = new ESPModule();
    private static SerialReader _reader;
    private static SerialWriter _writer;
    private static boolean _isConnected = false;
    //endregion

    //region Properties

    //endregion

    //region Constructor
    /**
     * Private constructor
     */
    private ESPModule() {
        super(Globals.ESP_MODULE_CONFIG_FILE);

        try {
            // Get serial port name from settings
            String portName = GetSetting(PORT_NAME, null);
            Logger.Debug("Attempting to connect to port: " + portName);

            // Connect to serial port
            CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
            
            if (portIdentifier == null)
                Logger.Throw("Null port identifier");

            if ( portIdentifier.isCurrentlyOwned() )
            {
                Logger.Error("Error: Port is currently in use");
            }
            else
            {
                CommPort commPort = portIdentifier.open(this.getClass().getName(),2000);
                
                if ( commPort instanceof SerialPort )
                {
                    SerialPort serialPort = (SerialPort) commPort;
                    serialPort.setSerialPortParams(57600,SerialPort.DATABITS_8,SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);
                    
                    _reader = new SerialReader(serialPort.getInputStream());
                    _writer = new SerialWriter(serialPort.getOutputStream());

                    _isConnected = true;
                }
                else
                {
                    Logger.Error("Error: Only serial ports are handled by this example.");
                }
            }     
        } catch (Exception exc) {
            Logger.Error("Unable to connect to esp via serial: " + exc.getMessage());
        }
        
        _singleton = this;
    }
    
    /**
     * Factory
     */
    public static ESPModule getModule() { return _singleton; }
    //endregion

    //region Methods
    public static String DataRequest(IEncryptionAlg alg) throws Exception {
        // Construct the message to send via serial
        StringBuilder bldr = new StringBuilder();

        bldr.append((char)(3 + alg.getIndex()));

        return SendMessage(bldr.toString(), true);
    }

    /**
     * Sends a message via serial port
     *  to the connected ESP Module, returns
     *  the module's response
     */
    public static String SendMessage(String msg, boolean requiresResponse) throws Exception {
        if (_writer == null || _reader == null || !_isConnected) 
            Logger.Throw("No connection");

        _writer.WriteSerial(msg);

        if (!requiresResponse)
            return "NULL";

        return ReadBuffer();
    }

    /**
     * Read buffer into a string
     * @return
     * @throws Exception
     */
    public static String ReadBuffer() throws Exception {
        if (_writer == null || _reader == null || !_isConnected) 
            Logger.Throw("No connection");

        StringBuilder bldr = new StringBuilder();

        long timeout = Long.parseLong(_singleton.GetSetting(TIMEOUT, null)) + (new Date()).getTime();

        do {
            
            String response = _reader.ReadBuffer();

            bldr.append(response);

        } while ((new Date()).getTime() < timeout);
        
        return bldr.toString();
    }
    //endregion

    //region ConfigurableBase
    @Override
    protected void _setDefaults() {
        SetSetting(BOARD_NAME, "ESP-WROOM-32");
        SetSetting(PORT_NAME, "COM4");
        SetSetting(TIMEOUT, "2500");
    }
    //endregion

    //region Serial Reader
    /**
     * Read string from buffer
     */
    public static class SerialReader 
    {
        InputStream _inputStream;
        
        public SerialReader ( InputStream in )
        {
            _inputStream = in;
        }
        
        /**
         * Read the buffer and place into string
         */
        public String ReadBuffer()
        {
            byte[] buffer = new byte[1024];
            StringBuilder bldr = new StringBuilder();
            int len = -1;

            try
            {
                while ((len = _inputStream.read(buffer)) > -1)
                {
                    bldr.append(new String(buffer,0,len));
                }
            }
            catch ( IOException e )
            {
                e.printStackTrace();
            }

            return bldr.toString();
        }
    }
    //endregion

    //region Serial Writer
    /**
     * Write string to serial
     */
    public static class SerialWriter 
    {
        OutputStream _outputStream;
        
        public SerialWriter (OutputStream out)
        {
            _outputStream = out;
        }
        
        public void WriteSerial(String msg)
        {
            try
            {
                byte[] buffer = msg.getBytes();
                for (byte b : buffer) {
                    _outputStream.write(b);
                }
            }
            catch ( IOException e )
            {
                Logger.Error("Error writing serial: " + e.getMessage());
            }            
        }
    }
    //endregion
}
