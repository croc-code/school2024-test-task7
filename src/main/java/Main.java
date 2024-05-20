import static reader.CommitFileReader.getCommitsFromFile;
import static service.ReportService.getTopThreeContributors;
import static writer.CommitFileWriter.saveTopContributors;


public class Main {

    public static void main(String[] args) {

        try {
            var commits = getCommitsFromFile();
            var topThreeContributors = getTopThreeContributors(commits);

            saveTopContributors(topThreeContributors);

        } catch (Exception e) {
            System.err.println(e.getMessage());
        }

    }
}
