import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class Main {

    public static void main(String[] args) {

        try {
            // чтение путей файла чтения и файла записи в список
            List<String> paths = Files.readAllLines(Paths.get("src/files/paths.txt"));

            // чтение строк из файла "commits.txt" в список
            List<String> allCommits = Files.readAllLines(Paths.get(paths.getFirst()));

            // вызов статического метода класса Top3Contributors для нахождения наиболее активных участников
            // по количеству коммитов
            List<String> topContributors = Top3Contributors.findByCommitsCount(allCommits);

            BufferedWriter writer = new BufferedWriter(new FileWriter(paths.getLast()));
            for (String contributor: topContributors) {
                writer.write(contributor + "\n");
            }
            // закрытие потока записи
            writer.close();

        } catch (IOException e) {
            if (e.toString().contains("commits.txt"))
                System.out.println("Error reading commits.txt");
            else
                System.out.println("Error writing result.txt");
            e.getMessage();
        }
    }
}