import java.text.ParseException;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.text.SimpleDateFormat;

public class Top3Contributors {

    private static final int kolElem = 3;
    private static final int hashLength = 7;
    private static final String dateFormat = "yyyy-MM-dd";
    private static final String timeFormat = "HH:mm:ss";

    public static List<String> findByCommitsCount(List<String> allCommits) {

        // Получаем мапу с валидными коммитами с ключами из имен пользователей
        // и значениями - количеством их коммитов
        Map<String, Long> commitCounts = allCommits.stream()
                .filter(Top3Contributors::validation)
                .map((e) -> e.split(" ")[0])
                .collect(Collectors.groupingBy(String::valueOf, Collectors.counting()));

        // сортируем по убыванию количества коммитов и возвращаем 3 самых первых
        return commitCounts.entrySet().stream()
                .sorted((e1, e2) -> e2.getValue().compareTo(e1.getValue()))
                .limit(3)
                .map(Map.Entry::getKey)
                .collect(Collectors.toList());
    }

    // метод для проверки коммитов на правильность формата данных
    private static boolean validation(String commit) throws IllegalArgumentException {

        boolean ind = true;

        String[] splitCommit = commit.split(" ");

        // Проверка, состоит ли строка коммита из 3 элементов
        if (splitCommit.length != kolElem) {
            return false;
        }

        // Проверка, начинается ли имя пользователя с цифр
        if (Character.isDigit(splitCommit[0].charAt(0))) {
            return false;
        }

        // Проверка, состоит ли сокращенный хэш коммита из 7 символов в нижнем регистре
        if (splitCommit[1].length() != hashLength || !splitCommit[1].equals(splitCommit[1].toLowerCase())) {
            return false;
        }

        // Проверка, соответсвует ли формат даты и времени требуемым
        if (splitCommit[2].length() > 10 && splitCommit[2].charAt(10) != 'T')
            return false;
        try {
            SimpleDateFormat format = new SimpleDateFormat();
            format.applyPattern(dateFormat);
            format.parse(splitCommit[2].substring(0, 10));
            format.applyPattern(timeFormat);
            format.parse(splitCommit[2].substring(11));
        } catch (ParseException e) {
            return false;
        }

        return ind;
    }
}
