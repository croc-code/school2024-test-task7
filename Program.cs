namespace CROC_7;
internal class Program
{
    public static void Main()
    {
        DoTask("commits.txt", "result.txt");
        Console.WriteLine(
            "Файл с результатом находится в папке проекта :\n" +
            $"{FileWorker.projectPath}\n\n" +
            $"Для выхода нажмите любую клавишу");
        Console.ReadKey();
    }

    public static void DoTask(string inputFile, string outputFile)
    {
        var input = FileWorker.ReadFile(inputFile);
        var rating = RatingContributors.GetRating(input);
        var top = RatingContributors.GetTop(rating);
        FileWorker.SaveFile(outputFile, top);
    }
}
