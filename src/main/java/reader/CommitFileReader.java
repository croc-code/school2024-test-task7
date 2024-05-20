package reader;

import exception.FileReadingException;

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

    /**
     * Читает записи коммитов из файла commits.txt, валидирует записи и возвращает
     * список допустимых коммитов для возожности последующей обработки. Если запись
     * с коммитом не валидна, то выводится сообщение об этом.
     *
     * Реализовал сперва чтение всех записей, без одновременной обработки - для
     * большей гибкости и возожности применения различных алгоритмов к полученному списку коммитов
     * в дальнейшем. Также, учитываю, что по заданию дубликаты записей не присутсвуют.
     *
     * @return Список строк, содержащих допустимые коммиты из файла.
     * @throws FileReadingException если происходит ошибка при чтении файла.
     */
    public static List<String> getCommitsFromFile() {

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
        } catch (IOException e) {
            throw new FileReadingException("Commit file reading exception");
        }

        return commitsList;
    }

    private static void printValidationError(String commitLine) {

        System.out.println("Commit: [" + commitLine + "] doesn't valid. Check format or data correctness.");
    }

}

