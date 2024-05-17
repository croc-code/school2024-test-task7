package dataOperations.sorting;

import dataOperations.Commit;
import dataOperations.validation.Validator;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;


public class CommitSorter {
    private final static int number_of_winners = 3;
    private CommitSorter(){}
    //удаление невалидированных коммитов
    private static void validateCommits(ArrayList<Commit> commits){
        commits.removeIf(commit -> !Validator.validateCommit(commit));
    }
    //получение статистики по кол-ву коммитов (имя-колво)
    private static HashMap<String,Integer> mapCommits(ArrayList<Commit> commits){
        HashMap<String,Integer> out = new HashMap<>();
        for(Commit commit: commits){
            String name = commit.name();
            if(out.containsKey(name)){
                out.put(name, out.get(name) + 1);
            }
            else{
                out.put(name,1);
            }
        }
        return out;
    }
    private static ArrayList<String> sortContributors(HashMap<String,Integer> contributors){
        ArrayList<String> out = new ArrayList<>();
        contributors.entrySet().stream().sorted(Map.Entry.comparingByValue(Comparator.reverseOrder())).forEach(contributor -> out.add(contributor.getKey()));
        return out;
    }
    public static ArrayList<String> sort(ArrayList<Commit> commits){
        HashMap<String,Integer> contributors = mapCommits(commits);
        ArrayList<String> out = sortContributors(contributors);
        if (out.size() < number_of_winners){
            System.out.println("Only " + out.size() + " contributors!");
            System.exit(-1);
        }
        return new ArrayList<>(out.subList(0, number_of_winners));
    }
}
