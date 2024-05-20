package writer;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

public class CommitFileWriter {

    private static final String RESULT_FOLDER_PATH = "src/main/resources/";
    private static final String RESULT_FILE_NAME = "result.txt";

    public static void saveTopContributors(List<String> contributors) throws IOException {

        String resultFileName = RESULT_FOLDER_PATH + RESULT_FILE_NAME;

        try (PrintWriter writer = new PrintWriter(new FileWriter(resultFileName))) {

            for (String contributor : contributors) {
                writer.println(contributor);
            }
        }
    }
}
