import org.junit.jupiter.api.Test;
import service.ReportService;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class ReportServiceTest {

    @Test
    public void testGetTopThreeContributors() {
        List<String> commits = List.of(
                "user1 abcdef0 2024-05-01T10:15:30.345",
                "user2 abcdef1 2024-05-01T11:15:30",
                "user3 abcdef2 2024-05-01T12:15:30",
                "user1 abcdef3 2024-05-02T10:15:30",
                "user2 abcdef4 2024-05-02T11:15:30",
                "user1 abcdef5 2024-05-03T10:15:30"
        );

        List<String> topContributors = ReportService.getTopThreeContributors(commits);

        assertEquals(List.of("user1", "user2", "user3"), topContributors);
    }
}
