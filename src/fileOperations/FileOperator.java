package fileOperations;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

public abstract class FileOperator {
    protected static final String settings_path = "src/resources/settings.txt";
    protected static String readPathByKey(String key){
        Properties settings = new Properties();
        try(FileInputStream fstream = new FileInputStream(settings_path)){
            settings.load(fstream);
        } catch (IOException e){
            System.out.println("Settings file not found");
            System.exit(-110);
        }
        return settings.getProperty(key);
    }
}
