package dataOperations.validation;

import dataOperations.Commit;

import java.time.DateTimeException;
import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.regex.Pattern;

public class Validator {
    private Validator(){}
    //регулярные выражения в соответствии требованиям
    private static final Pattern name_pattern = Pattern.compile("^[a-zA-Z_][a-zA-Z0-9_]*$");
    private static final Pattern hash_pattern = Pattern.compile("^[a-z0-9]{7}$");
    private static final Pattern dTime_pattern = Pattern.compile("\\\\d{4}-\\\\d{2}-\\\\d{2}T\\\\d{2}:\\\\d{2}:\\\\d{2}\\\\.\\\\d{0,9}");

    private static boolean validateName(String name){
        if(name.isEmpty()){
            return false;
        }
        return name_pattern.matcher(name).matches();
    }
    private static boolean validateHash(String hash){
        if(hash.isEmpty()){
            return false;
        }
        return hash_pattern.matcher(hash).matches();
    }
    //проверка соответствия логике времени и даты (не более 60 минут, и т.д)
    private static boolean checkDTime(String dTime){
        String[] split = dTime.split("[.\\-T:]");
        int[] dTimeNumbers = Arrays.stream(split).mapToInt(Integer::parseInt).toArray();
        try{
            LocalDateTime.of(dTimeNumbers[0],dTimeNumbers[1],dTimeNumbers[2],dTimeNumbers[3],dTimeNumbers[4],dTimeNumbers[5],dTimeNumbers[6]);
        } catch (DateTimeException e){
            return false;
        }
        return true;
    }
    private static boolean validateDTime(String dTime){
        if(dTime.isEmpty()){
            return false;
        }
        return dTime_pattern.matcher(dTime).matches() && checkDTime(dTime);
    }
    public static boolean validateCommit(Commit commit){
        return validateDTime(commit.dTime()) && validateHash(commit.hash()) && validateName(commit.name());
    }
}
