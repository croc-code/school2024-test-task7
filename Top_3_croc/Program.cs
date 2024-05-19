using Top_3_croc;
using Microsoft.Extensions.Configuration;
using System.Collections.Generic;
using System.Text;

partial class Program
{
    static void Main()
    {

        var builder = new ConfigurationBuilder();
        // установка пути к текущему каталогу
        builder.SetBasePath(Directory.GetCurrentDirectory());
        builder.AddJsonFile("appsettings.json");
        // создаем конфигурацию
        var config = builder.Build();
        // получаем строки подключения
        var path = config.GetConnectionString("DefaultConnection");
        var path2 = config.GetConnectionString("OutputConnection");

        if (path == null) path = "commits.txt"; //на случай, если строки в json-е пустые
        if (path2 == null) path2 = "result.txt";

        string[] info = File.ReadAllLines(path);

        List<Employee> employees = new List<Employee>();

        foreach (string line in info) //обработка всех коммитов и заполнение коллекции сотрудниками
        {
            Employee employee = new Employee(GetName(line),
                new List<Tuple<string, DateTime>> { new Tuple<string, DateTime>(GetHash(line), GetTime(line)) });
            if (!employees.Contains(employee)) //проверяем есть ли сотрудник в листе, если да,
                                               //то просто добавляем ему его коммит, если нет,
                                               //то добавляем сотрудника в лист
            {
                employees.Add(employee);
            }
            else
            {
                var EmpIndex = employees.IndexOf(employee);
                employees[EmpIndex].AddCommit(GetHash(line), GetTime(line));
            }
        }

        employees.Sort(); //Сортируем сотрудников по их количеству коммитов

        using (StreamWriter writer = new StreamWriter(path2, false)) //заполняем выходной файл с провнркой на случай,
                                                                     //если сотрудников < 3
        {
            int k = 3;
            if (employees.Count < k)
            
                foreach (var employee in employees) writer.WriteLine(employee.Name);
            else 
                for (int i = 0; i < k; ++i) writer.WriteLine(employees[i].Name);
        }
    }
}