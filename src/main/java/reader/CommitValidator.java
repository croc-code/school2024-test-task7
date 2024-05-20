package reader;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.time.temporal.ChronoUnit;
import java.util.regex.Pattern;

public class CommitValidator {

    private static final String usernamePattern = "^(?![0-9])[a-zA-Z0-9_]+$";
    private static final String hashPattern = "^[a-z0-9]{7}$";

    /**
     * Валидатор коммитов.
     *
     * Проверяет, что коммит имеет верный формат и содержит допустимые данные.
     * Формат коммита: "имя_пользователя хэш дата_время".
     *
     * @param commitLine строка с коммитом
     * @return true, если коммит валидный, иначе false
     */
    public static boolean isValidCommit(String commitLine) {
        var commit = commitLine.split(" ");

        if (commit.length != 3) {
            return false;
        }
        return isValidUsername(commit[0])
                && isValidHash(commit[1])
                && isValidDateTime(commit[2]);
    }

    /**
     * Проверяет, что имя пользователя валидно: соответствует шаблону - может содержать [A-z, 0-9 и _],
     * но не начинаться с 0-9.
     *
     * @param username имя пользователя
     * @return true, если имя пользователя валидно, иначе false
     */
    private static boolean isValidUsername(String username) {

        return Pattern.matches(usernamePattern, username);
    }

    /**
     * Проверяет, что хэш валиден: соответствует шаблону - должен состоять из 7 символов (a-z или 0-9).
     *
     * @param hash сокращенный хэш коммита
     * @return true, если хэш валиден, иначе false
     */
    private static boolean isValidHash(String hash) {

        return Pattern.matches(hashPattern, hash);
    }

    /**
     * Проверяет, что дата и время валидны (пример, "2024-04-25T13:45:30.492")
     * и находятся в пределах спринта, т.е в рамках последних 4 недель. Время
     * начала и конца спринта округляется до 00:00.
     *
     * Использовал ISO_LOCAL_DATE_TIME, так как по условию необходима поддержка
     * обоих форматов: 2024-04-24T13:56:39.492 и YYYY-MM-ddTHH:mm:ss (с и без ms).
     *
     * @param dateString строка с датой и временем
     * @return true, если дата и время валидны, иначе false
     */
    private static boolean isValidDateTime(String dateString) {
        try {
            DateTimeFormatter dateTimeFormatter = DateTimeFormatter.ISO_LOCAL_DATE_TIME;
            var commitDateTime = LocalDateTime.parse(dateString, dateTimeFormatter);

            var sprintEnd = LocalDateTime.now().truncatedTo(ChronoUnit.DAYS);
            var sprintStart = sprintEnd.minusWeeks(4);

            return commitDateTime.isAfter(sprintStart) && commitDateTime.isBefore(sprintEnd);

        } catch (DateTimeParseException e) {
            return false;
        }
    }

}
