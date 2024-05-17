package fileOperations;

import dataOperations.Commit;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class ContrubutorsWriter extends FileOperator {
    private ContrubutorsWriter(){}
    public static void write(ArrayList<String> contributors){
        String path = readPathByKey("outputPath");
        try(FileWriter wr = new FileWriter(path, false)){
            for(String contributor: contributors){
                wr.write(contributor+"\n");
            }
            wr.flush();
        } catch (IOException e){
            System.out.println("Output file IO error");
            System.exit(-112);
        }
    }
}
