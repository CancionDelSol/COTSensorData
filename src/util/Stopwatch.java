package util;

import java.util.*;
import java.time.Period;
import java.time.temporal.TemporalAmount;

/**
 * Stopwatch class used for timing
 *  function execution
 */
public class Stopwatch {

    //region Constants
    private static final String ALREADY_STARTED_ERR = "Should not call start on time that has already been started";
    private static final String NOT_STARTED_ERR = "Stopwatch has not been started";
    private static final String NO_FUNC_ERR = "No function to time available";
    private static final String CALL_FAILURE_ERR = "Failure received";
    //endregion

    //region Fields
    private Date _startTime;
    private Date _endTime;
    private ITimeableFunction _timedFunction;
    //endregion

    //region Properties
    /**
     * Return the timer's starting
     *  time
     * Throw exception if time
     *  is null.
     */
    public Date getStartTime() throws Exception {
        if (_startTime == null)
            throw new Exception("Null starting time");

        return _startTime;
    }

    /**
     * Return the timer's ending
     *  time
     * Throw exception if time
     *  is null.
     */
    public Date getEndTime() throws Exception {
        if (_endTime == null)
            throw new Exception("Null starting time");

        return _endTime;
    }
    //endregion

    //region Constructor
    /**
     * Keep open-ended
     */
    public Stopwatch() {

    }

    /**
     * Construct a Stopwatch which
     *  times the execution of a function
     * Does not start function call
     */
    public Stopwatch(ITimeableFunction funcToTime) {
        _timedFunction = funcToTime;
    }
    //endregion

    //region Methods
    /**
     * Call to start a timer for
     *  a method or procedure
     *  ran externally
     */
    public void Start() throws Exception {
        if (_startTime != null)
            throw new Exception(ALREADY_STARTED_ERR);

        _startTime = new Date();
    }

    /**
     * Get time since _startTime
     */
    public long GetTime() throws Exception {
        if (_startTime == null)
            throw new Exception(NOT_STARTED_ERR);
        
        Date currentTime = new Date();
        long period = currentTime.getTime() - _startTime.getTime();

        return period;
    }

    /**
     * Sets the start time to now
     */
    public void Reset() {
        _startTime = new Date();
    }

    /**
     * Only call if a function to time
     *  has been provided
     * Return time taken to run. Throw exception
     *  on failure from function
     */
    public long TimeFunction(Object param) throws Exception {

        // Throw Exception if no function
        //  is provided
        if (_timedFunction == null)
            throw new Exception(NO_FUNC_ERR);

        // Save the starting time
        Start();

        // Run function
        boolean res = false;
        try {
            res = _timedFunction.Run(param);
        } catch (Exception exc) {
            
        }
        

        // Throw exception on function failure
        if (!res)
            throw new Exception(CALL_FAILURE_ERR);
        
        // Call GetTime to return period
        return GetTime();
    }
    //endregion

    //region ITimeable Interface
    public interface ITimeableFunction {
        boolean Run(Object input);
    }
    //endregion

}