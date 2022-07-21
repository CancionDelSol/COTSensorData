import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.List;

import javax.imageio.plugins.tiff.GeoTIFFTagSet;

import enums.ProgramType;
import implem.protocols.BlueToothCommProto;
import implem.protocols.DummyCommProto;
import implem.protocols.LoPanCommProto;
import implem.protocols.WifiCommProtoProto;
import implem.ESPModule;
import implem.encryptionAlgorithms.DummyEncAlg;
import interfaces.ICommProto;
import interfaces.IEncryptionAlg;
import reporting.ReportBuilder;
import telemetry.RoundTripResult;
import util.ConfigurableBase;
import util.Globals;
import util.Logger;
import util.Stopwatch;
import util.Logger.LogLevel;

/**
 * Main program class
 * Functions as the experiment controller
 *  by centralizing all experimental logic
 *  into one executable
 * 
 * Flow:
 * 
 *  - Load main program configuration from disk
 *    This is done upon static field initialization
 *    (i.e Program constructor calls ConfigurableBase.ctor())
 * 
 *  - Discover all available encryption algorithms
 *     and communication protocols 
 * 
 *  - Process Command Line Arguments
 *    - Program Type
 *       Test
 *       Local (Server)
 *       Remote (Client)
 *    
 *
 *  - Perform necessary initialization
 *    - Remote (Client):
 *       Read sensor data from file
 *    - Local (Server):
 *       Confirm all protocols can connect 
 * 
 *  - Test each protocol's round trip communication
 *    time with each encryption algorithm
 * 
 *  - Save experimental results to disk
 * 
 * The following 3rd party libraries are used:
 * 
 *   - Pi4J : https://pi4j.com/
 *      Used to access GPIO on the RaspberryPi through
 *      the JVM. It does this through native libraries and JNI
 * 
 *   - JArduino : https://github.com/SINTEF-9012/JArduino
 *      Used to access serial communications with an arduino
 * 
 */
public class Program extends ConfigurableBase {
    //region Constants
    private static final String TEST_PRGM_TYPE_FLAG = "-test";
    private static final String REMOTE_PRGM_TYPE_FLAG = "-rem";
    private static final String LOCAL_PRGM_TYPE_FLAG = "-loc";

    private static final String LOG_LEVEL = "LogLevel";
    //endregion

    //region Fields
    private static String[] _args;
    private static HashMap<String, ICommProto> _communicationProtocols = new HashMap<>();
    private static HashMap<String, IEncryptionAlg> _encryptionAlgs = new HashMap<>();

    private static boolean _throwOnWarn = false;
    private static String _message = "TestMessage";

    private static String _configFilePath = Globals.MAIN_CONFIG_FILE;
    private static Program _program = new Program();

    private static ProgramType _programType = ProgramType.TEST;
    //endregion

    //region Properties
    public static ConfigurableBase getConfiguration() { return _program; }
    //endregion

    //region Constructor
    // Ensures configuration is loaded
    public Program() {
        super(_configFilePath);
    }
    //endregion
    
    //region Main
    /**
     * Main entry point
     */
    public static void main(String[] args) {
        Logger.Debug("Start of program");

        // Load settings from configuration
        try {
            LoadConfig();
        } catch (Exception e) {
            Logger.Error("Error loading config");
            return;
        }

        // Save reference to arguments
        //  for potential future use
        _args = args;

        // Process args for flags
        try {
            ProcessCLIArgs();
        } catch (Exception exc) {
            Logger.Error("Exception processing args: " + exc.getMessage());
            return;
        }

        // Use reflection
        //  to get available
        //  encryption algs and
        //  communication protos
        try {
            Discover();
        } catch (Exception exc) {
            Logger.Error("Exception during discovery: " + exc.getMessage());
            return;
        }

        try {
            switch (_programType) {
                case LOCAL:
                    RunLocalLogic();
                    break;
                case REMOTE:
    
                    break;
                case TEST:
                    RunTests();

                    // Add any unit tests here
                    //  Then run regular local
                    //  logic
                    //RunLocalLogic();
                    break;
                default:
                    Logger.Error("Unknown program type");
            }
        } catch (Exception exc) {
            Logger.Error("Exception running program-type logic");
            exc.printStackTrace();
            return;
        }
        

        // Check for invalid configurations
        try {
            if (Logger.getLevel() != LogLevel.DEBUG)
                CheckSetup();

        } catch (Exception exc) {
            Logger.Error("Invalid configuration: " + exc.getMessage());
            return;
        }

        
    }
    //endregion

    //region Private 
    /**
     * Get available protocols
     *  and encryption algs
     */
    private static void Discover() throws Exception {

        ICommProto[] commProtos;
        IEncryptionAlg[] encAlgs;

        // Unit Tests
        if (_programType == ProgramType.TEST) {

            // Communication protocols
            commProtos = new ICommProto[] {
                new DummyCommProto("CommProtoOne"),
                new DummyCommProto("CommProtoTwo"),
            };

            // Encryption algorithms
            encAlgs = new IEncryptionAlg[] {
                new DummyEncAlg("AlgStubOne"),
                new DummyEncAlg("AlgStubTwo")
            };

        // Production
        } else {
            // Communication protocols
            commProtos = new ICommProto[] {
                //new BlueToothCommProto(),
                //new LoPanCommProto(),
                new WifiCommProtoProto()
            };

            // Encryption algorithms
            encAlgs = new IEncryptionAlg[] {
            };
        }

        for (ICommProto cP : commProtos) {
            _communicationProtocols.put(cP.getName(), cP);
        }

        for (IEncryptionAlg eA : encAlgs) {
            _encryptionAlgs.put(eA.getName(), eA);
        }
        IEncryptionAlg nullAlg = new DummyEncAlg("None");
        _encryptionAlgs.put(nullAlg.getName(), nullAlg);
    }

    /**
     * Process the command line args
     *  for configurations and run
     *  types
     */
    private static void ProcessCLIArgs() throws Exception {
        try {

            // Loop through arguments
            for (int i = 0; i < _args.length;) {
                String curArg = _args[i];
                switch (curArg) {
                    case (REMOTE_PRGM_TYPE_FLAG):
                        _programType = ProgramType.REMOTE;
                        i++;
                        break;
                    case (LOCAL_PRGM_TYPE_FLAG):
                        _programType = ProgramType.LOCAL;
                        i++;
                        break;
                    case (TEST_PRGM_TYPE_FLAG):
                        _programType = ProgramType.TEST;
                        i++;
                        break;
                    default:
                        i++;
                        break;
                }
            }

        } catch (Exception exc) {
            // Log error
            Logger.Error("Error processing args: " + exc.getLocalizedMessage());
            
            // Throw exception
            throw exc;
        }
    }

    /**
     * Check the application setup
     *  for any invalid configuration
     *  setups or paramaters
     */
    private static void CheckSetup() throws Exception {

        // Check each connection
        Collection<ICommProto> protocols = _communicationProtocols.values();
        for (ICommProto proto : protocols) {

            // Check IsConnected
            //  Remove from hash
            //  map if it fails
            //  to connect
            if (proto != null) {
                // Check connection
                boolean isConn = proto.getIsConnected();

                // Throw if requested
                //  Otherwise remove
                if (!isConn && _throwOnWarn) 
                    throw new Exception("Unable to connect with " + proto.getName());
                else 
                    _communicationProtocols.remove(proto.getName());
                
            }

        }

    }
    
    /**
     * Run logic for a "local" machine (Server)
     */
    private static void RunLocalLogic() throws Exception {
        // Time each protocol against each encryption
        //  algorithm, including no encryption
        List<RoundTripResult> results = new ArrayList<>();
        Collection<ICommProto> commProtos =  _communicationProtocols.values();
        Collection<IEncryptionAlg> encAlgs =  _encryptionAlgs.values();

        // Loop over protocols
        for (ICommProto proto : commProtos) {
            Logger.Debug("Loop iter start for proto: " + proto.getName());

            // Loop over encryptions
            for (IEncryptionAlg encAlg : encAlgs) {
                Logger.Debug("Process Encryption Algorithm: " + encAlg.getName());

                try {
                    Logger.Debug("Creating stopwatch");
                    Stopwatch newWatch = new Stopwatch(param -> proto.RequestAndVerifySensorData(encAlg));

                    Logger.Debug("Time execution and grab results");
                    RoundTripResult res = newWatch.TimeFunction(null);
                    
                    Logger.Debug("Adding to list");
                    results.add(res);

                } catch (Exception exc) {
                    Logger.Error("Exception during experiment: " + exc.getMessage());
                    RoundTripResult res = new RoundTripResult(proto,
                                                              encAlg,
                                                              "Failure: " + exc.getMessage());
                    results.add(res);
                }
            }
        }

        Logger.Debug("Creating report");
        ReportBuilder repBldr = new ReportBuilder();
        repBldr.AddLine("Roger Johnson: " + (new Date()));

        // Build report,
        Logger.Debug("Looping through results and adding to report");
        for (RoundTripResult res : results) {
            repBldr.AddLine("Result from: " + res.getCommProtoName());
            repBldr.AddLine(res.toString());
            repBldr.AddLine("----------------------------------------");
        }

        String report = repBldr.Build();

        System.out.println(report);
    }

    private static void LoadConfig() throws Exception {
        if (_program == null)
            Logger.Throw("Program is null");

        String logLevel = _program.GetSetting(LOG_LEVEL, () -> _program.SetSetting(LOG_LEVEL, "GUI"));
        if (logLevel != null && logLevel.length() > 0)
            Logger.setLevel(LogLevel.valueOf(logLevel));

    }
    //endregion

    //region Tests
    private static void RunTests() throws Exception {
        String responseNoneEncReq = ESPModule.CleanMessage("None");
        Thread.sleep(1000);

        String responseAESEncReq = ESPModule.CleanMessage("ESP");
        Thread.sleep(1000);
        
        String responseDESEncReq = ESPModule.CleanMessage("DES");
        Thread.sleep(1000);
        
        String responseECCEncReq = ESPModule.CleanMessage("ECC");
        
        Logger.Info("Response None Type Encryption Request: " + responseNoneEncReq);
        Logger.Info("Response AES Type Encryption Request: " + responseAESEncReq);
        Logger.Info("Response DES Type Encryption Request: " + responseDESEncReq);
        Logger.Info("Response ECC Type Encryption Request: " + responseECCEncReq);
    }
    //endregion

    //region ConfigurableBase
    @Override
    protected void _setDefaults() {
        SetSetting("LogLevel", "DEBUG");
    }
    //endregion

}
