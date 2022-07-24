package implem;

import util.ConfigurableBase;
import util.Globals;
import util.Logger;

import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.SerialPort;
import interfaces.IEncryptionAlg;

import java.io.FileDescriptor;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.Charset;
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
    private static long _espClientOrigTime = 0L;
    private static long _espServerOrigTime = 0L;
    //endregion

    //region Properties
    public static long getESPClientOrigTime() { return _espClientOrigTime; }
    public static long getESPServerOrigTime() { return _espServerOrigTime; }
    //endregion

    //region Constructor
    /**
     * Private constructor
     */
    private ESPModule() {
        super(Globals.ESP_MODULE_CONFIG_FILE);

        String portName = "";

        try {
            // Get serial port name from settings
            portName = GetSetting(PORT_NAME, null);
            Logger.Debug("Attempting to connect to port: " + portName);

            // Connect to serial port
            CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
            
            if (portIdentifier == null)
                Logger.Throw("Null port identifier");

            if (portIdentifier.isCurrentlyOwned() )
            {
                Logger.Error("Error: Port is currently in use");
            }
            else
            {
                CommPort commPort = portIdentifier.open(this.getClass().getName(), 2000);
                
                if (commPort instanceof SerialPort)
                {
                    SerialPort serialPort = (SerialPort) commPort;
                    serialPort.setSerialPortParams(115200,
                                                    SerialPort.DATABITS_8,
                                                    SerialPort.STOPBITS_1,
                                                    SerialPort.PARITY_NONE);
                    
                    Logger.Debug("Creating reader and writer");
                    _reader = new SerialReader(serialPort.getInputStream());
                    _writer = new SerialWriter(serialPort.getOutputStream());

                }
                else
                {
                    Logger.Error("Error: Only serial ports are handled by this example.");
                }
            }
        } catch (NoSuchPortException nspExc) {
            Logger.Error("Port " + portName + " does not exist");

            Logger.Error("Open serial ports (Include full name in cfg file): ");

            java.util.Enumeration<CommPortIdentifier> portEnum = CommPortIdentifier.getPortIdentifiers();
            while (portEnum.hasMoreElements())
            {
                CommPortIdentifier portIdentifier = portEnum.nextElement();
                Logger.Error(" " + portIdentifier.getName() + " | " +  getPortTypeName(portIdentifier.getPortType()));
            }    

        } catch (Exception exc) {
            Logger.Error("Unable to connect to esp via serial: " + exc.getMessage());
            exc.printStackTrace();
        }
        
        _singleton = this;
    }
    
    /**
     * Factory
     */
    public static ESPModule getModule() { return _singleton; }
    //endregion

    //region Methods
    private static void GetModuleTimes() {
        try {
            String res = SendMessage("CurrentTime", true);

            if (res != null && !res.equals("")) {
                String[] splits = res.split(" ");
                _espClientOrigTime = Long.parseLong(splits[0]);
                _espServerOrigTime = Long.parseLong(splits[1]); 
            }

        } catch (Exception exc) {
            Logger.Error("Exception during time acquisition: " + exc.getMessage());
        }
    }
    
    public static String DataRequest(IEncryptionAlg alg) throws Exception {
        // Get current times for adjustment later
        GetModuleTimes();

        // Construct the message to send via serial
        StringBuilder bldr = new StringBuilder();

        bldr.append(alg.getName());

        String req = bldr.toString();

        Logger.Debug("Request to module: " + req);
        return SendMessage(req, true);
    }

    /**
     * Sends a message via serial port
     *  to the connected ESP Module, returns
     *  the module's response
     */
    public static String SendMessage(String msg, boolean requiresResponse) throws Exception {
        
        if (_writer == null)
            Logger.Throw("No writer");

        if (_reader == null)
            Logger.Throw("No reader");

        // Builder for full message
        StringBuilder bldr = new StringBuilder();
        
        // Log
        Logger.Debug("Sending msg to board: " + msg);

        // Send message to board
        _writer.WriteSerial(msg);

        if (!requiresResponse)
            return bldr.toString();

        // Log
        Logger.Debug("Awaiting response");
        String resp = ReadBuffer();

        bldr.append(resp);

        return bldr.toString();
    }

    /**
     * Read buffer into a string
     * @return
     * @throws Exception
     */
    public static String ReadBuffer() throws Exception {
        if (_writer == null || _reader == null) 
            Logger.Throw("No connection");

        String response = _reader.ReadBuffer();

        Logger.Debug("Response: " + response);

        return response;
    }
    //endregion

    //region ConfigurableBase
    @Override
    protected void _setDefaults() {
        SetSetting(BOARD_NAME, "ESP-WROOM-32");
        SetSetting(PORT_NAME, "ttyUSB0");
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

            // Get the timeout
            long timeout = Long.parseLong(_singleton.GetSetting(TIMEOUT, null));
            try
            {
                // Wait for anvailable input
                long endTime = (new Date()).getTime() + timeout;
                Logger.Info("Waiting for serial input");

                boolean fullMsg = false;

                Logger.Debug("Reading from input stream on blocking thread");
                while (!fullMsg) {
                    
                    if ((new Date()).getTime() > endTime) {
                        Logger.Error("Timeout on ESP read from input stream");
                        return "";
                    }

                    if (_inputStream.available() == 0) 
                        continue;

                    len = _inputStream.read(buffer);

                    Logger.Debug("Length" + len);
                    String fromStream = new String(buffer, 0, len);

                    Logger.Debug("Read from buffer: " + fromStream);
                    bldr.append(fromStream);

                    fullMsg = CheckFullMsg(bldr.toString());
                }

                Logger.Debug("Finish reading from input stream");
            } catch (Exception exc) {
                exc.printStackTrace();
            }

            return bldr.toString().replace("<", "").replace(">", "");
        }
    }

    private static boolean CheckFullMsg(String msg) {
        char[] charArray = msg.toCharArray();

        if (charArray.length < 2)
            return false;
        
        if (charArray[0] != '<')
            return false;

        if (charArray[charArray.length - 1] != '>')
            return false;
        
        return true;
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
        
        public void WriteSerial(String msg) throws Exception {
            if (_outputStream == null)
                Logger.Throw("No open output stream");

            try
            {
                byte[] buffer = msg.getBytes(Charset.forName("UTF-8"));
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
    
    //region Testing
    public static String CleanMessage(String msg) throws Exception {
        
        if (_reader == null)
            Logger.Throw("Reader is null");
        
        if (_writer == null)
            Logger.Throw("Writer is null");

        try {
            _writer.WriteSerial(msg);

            return _reader.ReadBuffer();
            
        } catch (Exception exc) {
            Logger.Error("Failed to send and recieve: " + exc.getMessage());
            exc.printStackTrace();
        }
        return "Failed";
    }
    //endregion

    //region Private
    static String getPortTypeName ( int portType )
    {
        switch ( portType )
        {
            case CommPortIdentifier.PORT_I2C:
                return "I2C";
            case CommPortIdentifier.PORT_PARALLEL:
                return "Parallel";
            case CommPortIdentifier.PORT_RAW:
                return "Raw";
            case CommPortIdentifier.PORT_RS485:
                return "RS485";
            case CommPortIdentifier.PORT_SERIAL:
                return "Serial";
            default:
                return "unknown type";
        }
    }
    //endregion
}
