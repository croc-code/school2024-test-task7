
namespace CROC_7;
internal class Program
{
    public static void Main()
    {
        DoTask();
        Console.WriteLine(
            "Файл с результатом находится в папке проекта :\n" +
            $"{FileWorker.projectPath}\n\n" +
            $"Для выхода нажмите любую клавишу");
        Console.ReadKey();
    }

    public static void DoTask()
    {
        var input = FileWorker.ReadFile("commits.txt");
        var rating = CommitsRating.ParseFile(input);
        var top = CommitsRating.GetTop(rating);
        FileWorker.SaveFile("result.txt", top);
    }
}
