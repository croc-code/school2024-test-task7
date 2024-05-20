import org.junit.jupiter.api.Test;
import reader.CommitValidator;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import static org.junit.jupiter.api.Assertions.*;

class CommitValidatorTest {

    @Test
    void testValidUsername() throws NoSuchMethodException, InvocationTargetException, IllegalAccessException {

        Method isValidUsername = CommitValidator.class.getDeclaredMethod("isValidUsername", String.class);
        isValidUsername.setAccessible(true);

        // Валидные имена пользователей
        assertTrue((boolean) isValidUsername.invoke(null, "user_name"));
        assertTrue((boolean) isValidUsername.invoke(null, "UserName123"));
        assertTrue((boolean) isValidUsername.invoke(null, "username"));
        assertTrue((boolean) isValidUsername.invoke(null, "_User_Name"));

        // Невалидные имена пользователей
        assertFalse((boolean) isValidUsername.invoke(null, "123username")); // начинается с цифры
        assertFalse((boolean) isValidUsername.invoke(null, "user@name")); // содержит недопустимый символ
        assertFalse((boolean) isValidUsername.invoke(null, "")); // пустая строка
    }

    @Test
    void testValidHash() throws NoSuchMethodException, InvocationTargetException, IllegalAccessException {

        Method isValidHash = CommitValidator.class.getDeclaredMethod("isValidHash", String.class);
        isValidHash.setAccessible(true);

        // Валидные хэши
        assertTrue((boolean) isValidHash.invoke(null,"abcdefg"));
        assertTrue((boolean) isValidHash.invoke(null,"1234567"));
        assertTrue((boolean) isValidHash.invoke(null,"a1b2c3d"));

        // Невалидные хэши
        assertFalse((boolean) isValidHash.invoke(null,"1234")); // слишком короткий
        assertFalse((boolean) isValidHash.invoke(null,"abcdefg123")); // слишком длинный
        assertFalse((boolean) isValidHash.invoke(null,"abc!@#")); // содержит недопустимые символы
        assertFalse((boolean) isValidHash.invoke(null,"ABCDEF1")); // содержит заглавные буквы
        assertFalse((boolean) isValidHash.invoke(null,"")); // пустая строка
    }

    @Test
    void testValidDateTime() throws NoSuchMethodException, InvocationTargetException, IllegalAccessException {

        Method isValidDateTime = CommitValidator.class.getDeclaredMethod("isValidDateTime", String.class);
        isValidDateTime.setAccessible(true);

        DateTimeFormatter formatter = DateTimeFormatter.ISO_LOCAL_DATE_TIME;
        LocalDateTime now = LocalDateTime.now();

        // Валидные даты
        String validDateTime1 = now.minusWeeks(2).format(formatter);
        String validDateTime2 = now.minusDays(10).format(formatter);
        String validDateTime3 = "2024-04-25T13:45:30"; // формат без миллисекунд
        String validDateTime4 = "2024-04-25T13:45:30.495"; // формат c миллисекундами)

        // Невалидные даты
        String invalidDateTime1 = now.minusWeeks(5).format(formatter); // более 4 недель назад
        String invalidDateTime2 = now.plusDays(1).format(formatter); // в будущем
        String invalidDateTime3 = "invalid-date"; // неверный формат строки

        assertTrue((boolean) isValidDateTime.invoke(null,validDateTime1));
        assertTrue((boolean) isValidDateTime.invoke(null,validDateTime2));
        assertTrue((boolean) isValidDateTime.invoke(null, validDateTime3));
        assertTrue((boolean) isValidDateTime.invoke(null, validDateTime4));

        assertFalse((boolean) isValidDateTime.invoke(null,invalidDateTime1));
        assertFalse((boolean) isValidDateTime.invoke(null,invalidDateTime2));
        assertFalse((boolean) isValidDateTime.invoke(null, invalidDateTime3));
    }

    @Test
    void testIsValidCommit() {
        String validCommit = "username abcdefg " + LocalDateTime.now().minusDays(2).format(DateTimeFormatter.ISO_LOCAL_DATE_TIME);
        String invalidCommit1 = "username abcdefg123 2024-04-25T13:45:30"; // Неверный хэш
        String invalidCommit2 = "123username abcdefg 2024-04-25T13:45:30"; // Неверное имя пользователя
        String invalidCommit3 = "username abcdefg 2023-01-01T13:45:30"; // Неверная дата
        String invalidCommit4 = "username abcdefg"; // Недостаточно частей

        assertTrue(CommitValidator.isValidCommit(validCommit));
        assertFalse(CommitValidator.isValidCommit(invalidCommit1));
        assertFalse(CommitValidator.isValidCommit(invalidCommit2));
        assertFalse(CommitValidator.isValidCommit(invalidCommit3));
        assertFalse(CommitValidator.isValidCommit(invalidCommit4));
    }
}

