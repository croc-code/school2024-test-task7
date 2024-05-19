package org.example;
import java.io.File;
import java.io.FileWriter;

public class Main {
    public static void main(String[] args) {
        try(FileWriter writer = new FileWriter("result.txt")) {
            RatingManager manager = new RatingManager(new File("commits.txt").toPath());
            manager.calculateCommits();
            //Записываем результат в файл
            String res = manager.getResult();
            if(res != null)
                writer.write(res);
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}