import jata.util.*;

/**
 * Stopwatch class used for timing
 *  function execution
 */
class Stopwatch {

    //region Fields
    private Date _startTime;
    private Date _endTime;
    private ITimeableFunction _timedMethod;
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
        _funcToTime = funcToTime;
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
            throw new Exception("Should not call start on time that has already been started");

        _startTime = new Date();
    }

    /**
     * Get time since _startTime
     */
    public Period GetTime() throws Exception {
        if (_startTime == null)
            throw new Exception("Stopwatch has not been started");

        return new Period(_startTime, new Date());
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
    public Period TimeFunction(Object param) throws Exception {

        // Throw Exception if no function
        //  is provided
        if (_funcToTime == null)
            throw new Exception ("No function to time available");

        // Save the starting time
        Start();

        // Run function
        boolean res = _funcToTime.Run(param);

        // Throw exception on function failure
        if (!res)
            throw new Exception("Failure received");
        
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