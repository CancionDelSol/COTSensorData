import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import implem.DummyCommProto;
import implem.DummyEncAlg;
import interfaces.ICommProto;
import interfaces.IEncryptionAlg;
import telemetry.RoundTripResult;
import util.Logger;

public class Program {

    //region Fields
    private static String[] _args;
    private static HashMap<String, ICommProto> _communicationProtocols = new HashMap<>();
    private static HashMap<String, IEncryptionAlg> _encryptionAlgs = new HashMap<>();

    private static boolean _throwOnWarn = false;
    //endregion
    
    //region Main
    /**
     * Main entry point
     */
    public static void Main(String[] args) {

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

        // Check for invalid configurations
        try {
            CheckSetup();
        } catch (Exception exc) {
            Logger.Error ("Invalid configuration: " + exc.getMessage());
            return;
        }

        // Time each protocol against each encryption
        //  algorithm, including no encryption
        List<RoundTripResult> results = new ArrayList<>();
        ICommProto[] commProtos = (ICommProto[]) _communicationProtocols.values().toArray();
        IEncryptionAlg[] encAlgs = (IEncryptionAlg[]) _encryptionAlgs.values().toArray();
        for (ICommProto proto : commProtos) {
            for (IEncryptionAlg encAlg : encAlgs) {
                
                try {

                    Stopwatch newWatch = new Stopwatch(param -> proto.EncryptedRoundTrip("", encAlg));

                    long duration = newWatch.TimeFunction(null);

                } catch (Exception exc) {

                }
            }
        }

    }
    //endregion

    //region Private 
    /**
     * Get available protocols
     *  and encryption algs
     * TODO : Do this via reflection
     */
    private static void Discover() throws Exception {

        // Construct the communication protocols
        ICommProto dummyProto1 = new DummyCommProto("CommProtoOne");
        ICommProto dummyProto2 = new DummyCommProto("CommProtoTwo");

        // Encryption algorithm
        IEncryptionAlg dummyEncAlg1 = new DummyEncAlg("AlgStubOne");
        IEncryptionAlg dummyEncAlg2 = new DummyEncAlg("AlgStubTwo");

        // Add all communication protocols
        _communicationProtocols.put(dummyProto1.getName(), dummyProto1);
        _communicationProtocols.put(dummyProto1.getName(), dummyProto2);

        // Add all encryption algorithms
        _encryptionAlgs.put(dummyProto1.getName(), dummyEncAlg1);
        _encryptionAlgs.put(dummyProto1.getName(), dummyEncAlg2);
        _encryptionAlgs.put("None", null);

    }

    /**
     * Process the command line args
     *  for configurations and run
     *  types
     */
    private static void ProcessCLIArgs() throws Exception {

    }

    /**
     * Check the application setup
     *  for any invalid configuration
     *  setups or paramaters
     */
    private static void CheckSetup() throws Exception {

        // Check each connection
        ICommProto[] protocols = (ICommProto[])_communicationProtocols.values().toArray();
        for (int i = 0; i < _communicationProtocols.size(); i++) {

            // Check IsConnected
            //  Remove from hash
            //  map if it fails
            //  to connect
            ICommProto proto = protocols[i];
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
    //endregion



}
