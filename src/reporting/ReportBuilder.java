package reporting;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;

import util.Logger;

/**
 * In the end, a report will need
 *  to be created containing all
 *  gathered telemetry
 */
public class ReportBuilder {

    // Functions as the buffer
    private StringBuilder _bldr;

    // Create a clean report
    //  builder
    public ReportBuilder() {
        _bldr = new StringBuilder();
    }

    // Create a report builder
    //  with initial content
    public ReportBuilder(String content) {
        _bldr = new StringBuilder(content);
    }

    // Add a line to the report
    public ReportBuilder AddLine(String text) {
        _bldr.append(text + '\n');
        return this;
    }

    // Append text to the end of the report
    public ReportBuilder Add(String text) {
        _bldr.append(text);
        return this;
    }

    // Get the report content
    public String Build() {
        return _bldr.toString();
    }

    /**
     * Save current bldr to file
     *  Clear the buffer if clearBuffer
     *  is true
     */
    public boolean SaveToFile(String fileName, boolean clearBuffer) {

        try {

            // Create file object
            File targetFile = new File("src/test/resources/targetFile.tmp");

            // Open output stream to file
            //  object
            OutputStream outStream = new FileOutputStream(targetFile);

            // Get the content from the builder
            String content = _bldr.toString();

            // Write the stream to file
            outStream.write(content.getBytes());

            // Flush the bldr
            outStream.flush();

            // Clost the output stream
            outStream.close();

            // Clear buffer if requested
            if (clearBuffer)
                _bldr = new StringBuilder();

        } catch (Exception exc) {
            Logger.Error("Exception attempting to save report to file: " + exc.getMessage());
            return false;
        }

        return true;
    }
}
