package reader;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.regex.Pattern;

public class CommitValidator {

    private static final String usernamePattern = "^(?![0-9])[a-zA-Z0-9_]+$";
    private static final String hashPattern = "^[a-z0-9]{7}$";

    public static boolean isValidCommit(String commitLine) {
        var commit = commitLine.split(" ");

        if (commit.length != 3) {
            return false;
        }
        return isValidUsername(commit[0])
                && isValidHash(commit[1])
                && isValidDateTime(commit[2]);
    }

    private static boolean isValidUsername(String username) {

        return Pattern.matches(usernamePattern, username);
    }

    private static boolean isValidHash(String hash) {

        return Pattern.matches(hashPattern, hash);
    }

    private static boolean isValidDateTime(String dateString) {
        try {
            DateTimeFormatter dateTimeFormatter = DateTimeFormatter.ISO_LOCAL_DATE_TIME;
            var commitDateTime = LocalDateTime.parse(dateString, dateTimeFormatter);
            var currentDateTime = LocalDateTime.now();

            return currentDateTime.isAfter(commitDateTime);

        } catch (DateTimeParseException e) {
            return false;
        }
    }

}
