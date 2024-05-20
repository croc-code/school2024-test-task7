package reader;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

import static reader.CommitValidator.isValidCommit;

public class CommitFileReader {

    private static final String COMMIT_FOLDER_PATH = "src/main/resources/";
    private static final String COMMIT_FILE_NAME = "commits.txt";

    public static List<String> getCommitsFromFile() throws IOException {

        List<String> commitsList = new ArrayList<>();

        String commitsFileName = COMMIT_FOLDER_PATH + COMMIT_FILE_NAME;
        var commitsFilePath = Paths.get(commitsFileName);

        try (Stream<String> commits = Files.lines(commitsFilePath)) {
            commits.forEach(commitLine -> {

                if (isValidCommit(commitLine)) {
                    commitsList.add(commitLine);

                } else {
                   printValidationError(commitLine);
                }

            });
        }

        return commitsList;
    }

    private static void printValidationError(String commitLine){

        System.err.println("Commit: [" + commitLine + "] doesn't valid. Check format.");
    }

}

