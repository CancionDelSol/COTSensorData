import java.util.HashMap;

import interfaces.ICommProto;
import util.Logger;

public class Program {

    //region Fields
    private static String[] _args;
    private static HashMap<String, ICommProto> _communicationProtocols = new HashMap<>();
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

                // Remove from hash map
                //  if needed
                if (!isConn)
                    _communicationProtocols.remove(proto.getName());

            }

        }

        // TODO : Time each protocol without encryption

        // TODO : Time each protocol with encryption

    }
    //endregion

    //region Private 
    /**
     * Get available protocols
     *  and encryption algs
     */
    private static void Discover() throws Exception {

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

    }
    //endregion



}
