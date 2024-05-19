package org.example;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Path;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.HashMap;
import java.util.Map;
import java.util.StringJoiner;

/**Менеджер рейтингов, подсчитывает количество коммитов по именам и выдает трех самых активных участников**/
public class RatingManager {
    private Path commitsPath;
    private HashMap<String, Integer> commitsCount;  //имя, количество коммитов
    /**Паттерны для даты и времени**/
    private static final String datePattern = "yyyy-MM-dd";
    private static final String timePattern = "HH:mm:ss";
    /**Форматер для даты**/
    private SimpleDateFormat format;

    /**Конструктор
     * @exception IllegalArgumentException если входной файл отсутствует**/
    public RatingManager(Path input) throws IllegalArgumentException {
        this.commitsPath = input;
        this.commitsCount = new HashMap<>();
        this.format = new SimpleDateFormat();
        if(!commitsPath.toFile().exists())
            throw new IllegalArgumentException("Файл не существует!");
    }

    /**Валидирует строку согласно ТЗ
     * @return null если строка неправильного формата (см ТЗ), иначе возвращает имя пользователя для дальнейшей обработки**/
    private String validator(String line) {
        if(line == null) return null;
        String[] lines = line.split(" ");
        //Неправильная строка
        if(lines.length != 3)
            return null;

        //Хеш длины 7 и в нижнем регистре
        String hash = lines[1];
        if(hash.length() != 7 || !hash.equals(hash.toLowerCase()))
            return null;

        //Формат даты YYYY-MM-ddTHH:mm:ss
        if(lines[2].charAt(10) != 'T') return null;
        try {
            //Игнорируем T
            String date = lines[2].substring(0, 10).intern();
            String time = lines[2].substring(11);
            //Парсим дату
            format.applyPattern(datePattern);
            format.parse(date);
            format.applyPattern(timePattern);
            format.parse(time);
        } catch (ParseException e) {
            return null;
        }

        //Имя не начинается с цифры
        if(Character.isDigit(lines[0].charAt(0))) {
            return null;
        }

        //Помещаем имя в пул строк, чтобы не было лишнего копирования
        return lines[0].intern();
    }

    /**Подсчет количества коммитов
     * @exception IllegalArgumentException если строка неправильного формата
     * @exception IOException ошибка чтения файла**/
    public void calculateCommits() throws IOException, IllegalArgumentException {
        BufferedReader reader = new BufferedReader(new FileReader(commitsPath.toFile()));
        String line;
        //Обходим строки файла
        while ((line = reader.readLine()) != null) {
            String name = validator(line);
            if(name == null) {
                throw new IllegalArgumentException("Неправильный формат строки");
            }
            //Если уже был, то обновляем счетчик, иначе - добавляем
            if(commitsCount.containsKey(name)) {
                commitsCount.replace(name, commitsCount.get(name) + 1);
            } else {
                commitsCount.put(name, 1);
            }
        }
        reader.close();
    }

    /**Подсчет результатов
     * @return имена трех самых активных разработчиков, по одному в каждой строке, null если произошла ошибка или файл пустой**/
    public String getResult()  {
        if(commitsCount == null || commitsCount.isEmpty()) return null;
        //Для поиска максимумов
        //Количество коммитов, c1 >= c2 >= c3
        int c1 = 0, c2 = 0, c3 = 0, temp;
        String name1 = "", name2 = "", name3 = "";
        for (Map.Entry<String, Integer> entry: commitsCount.entrySet()) {
            temp = entry.getValue();
            //temp > c1 >= c2 >= c3
            if(temp > c1) {
                c3 = c2;
                c2 = c1;
                c1 = temp;
                name3 = name2;
                name2 = name1;
                name1 = entry.getKey();
            } else if(temp > c2) {      // c1 >= temp > c2 >= c3
                c3 = c2;
                c2 = temp;
                name3 = name2;
                name2 = entry.getKey();
            } else if(temp > c3) {       //c1 >= c2 >= temp > c3
                c3 = temp;
                name3 = entry.getKey();
            }
        }
        StringJoiner joiner = new StringJoiner("\n");
        joiner.add(name1);
        joiner.add(name2);
        joiner.add(name3);
        return joiner.toString();
    }
}
