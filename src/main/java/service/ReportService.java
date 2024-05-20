package service;

import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ReportService {

    public static List<String> getTopThreeContributors(List<String> commits) {

        Map<String, Integer> commitsAmountByUsername = getContributorsMap(commits);

        return commitsAmountByUsername.entrySet()
                .stream()
                .sorted(Map.Entry.comparingByValue(Comparator.reverseOrder()))
                .limit(3)
                .map(Map.Entry::getKey)
                .toList();
    }

    private static Map<String, Integer> getContributorsMap(List<String> commits) {

        Map<String, Integer> contributorsMap = new HashMap<>();

        for (String line : commits) {
            var commit = line.split(" ");
            String username = commit[0];

            contributorsMap.put(
                    username,
                    contributorsMap.getOrDefault(username, 0) + 1);
        }

        return contributorsMap;
    }
}
