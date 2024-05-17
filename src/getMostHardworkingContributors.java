import dataOperations.Commit;
import dataOperations.sorting.CommitSorter;
import fileOperations.CommitReader;
import fileOperations.ContrubutorsWriter;

import java.util.ArrayList;

public class getMostHardworkingContributors {
    public static void main(String[] args) {
        //считываем информацию о коммитах по пути из settings.txt
        ArrayList<Commit> commits = CommitReader.read();
        //находим победителей
        ArrayList<String> sorted = CommitSorter.sort(commits);
        //записываем в файл по пути из settings.txt
        ContrubutorsWriter.write(sorted);
    }
}