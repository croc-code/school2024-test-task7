package fileOperations;

import dataOperations.Commit;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Properties;
import java.util.Scanner;

public class CommitReader extends FileOperator{
    private CommitReader(){}
    public static ArrayList<Commit> read(){
        ArrayList<Commit> out = new ArrayList<>();
        try(Scanner fstream = new Scanner(new File(readPathByKey("inputPath")))){
            while(fstream.hasNextLine()){
                String[] split = fstream.nextLine().split(" ");
                out.add(new Commit(split[0], split[1], split[2]));
            }
        }catch(IOException e){
            System.out.println("No such input file found");
            System.exit(-111);
        }
        return out;
    }

}
