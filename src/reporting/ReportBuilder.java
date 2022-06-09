package reporting;

/**
 * In the end, a report will need
 *  to be created containing all
 *  gathered telemetry
 */
public class ReportBuilder {
    private StringBuilder _bldr;
    public ReportBuilder() {
        _bldr = new StringBuilder();
    }
    public ReportBuilder(String content) {
        _bldr = new StringBuilder(content);
    }

    public ReportBuilder AddLine(String text) {
        _bldr.append(text + '\n');
        return this;
    }
    public ReportBuilder Add(String text) {
        _bldr.append(text);
        return this;
    }
    public String Build() {
        return _bldr.toString();
    }
}
