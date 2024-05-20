package writer;

import exception.FileWritingException;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

public class CommitFileWriter {

    private static final String RESULT_FOLDER_PATH = "src/main/resources/";
    private static final String RESULT_FILE_NAME = "result.txt";

    /**
     * Сохраняет список лучших участников в файл.
     *
     * @param contributors список имен лучших участников.
     * @throws FileWritingException если происходит ошибка при записи в файл.
     */
    public static void saveTopContributors(List<String> contributors) {

        String resultFileName = RESULT_FOLDER_PATH + RESULT_FILE_NAME;

        try (PrintWriter writer = new PrintWriter(new FileWriter(resultFileName))) {

            for (String contributor : contributors) {
                writer.println(contributor);
            }
        } catch (IOException e) {
            throw new FileWritingException("Result file writing exception");
        }
    }
}
