using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Top_3_croc
{
    internal class Employee : IComparable<Employee>
    {
        public string Name { get; set; } // имя пользователя
        private List<Tuple<string, DateTime>> Commits; // список коммитов, их хэш и дата в кортежах

        public Employee() // конструктор без параметров
        {
            Name = "NoName";
            Commits = new List<Tuple<string, DateTime>>();
        }

        public Employee(string name, List<Tuple<string, DateTime>> commits)
        {
            Name = name;
            Commits = commits;
        }

        public Employee(string name)
        {
            Name = name;
            Commits = new List<Tuple<string, DateTime>>();
        }

        public DateTime GetTimeLastCommit() // получение времени последнего комммита пользователем
        {
            return (Commits[0].Item2);
        }

        public int GetCountCommit() // получение количества коммитов пользователя
        {
            return Commits.Count;
        }
        public int CompareTo(Employee? employee) // определение метода для возможности сортировки объектов класса
        {
            if (employee is null) throw new ArgumentException("Некорректное значение параметра");

            if (this.GetCountCommit().CompareTo(employee.GetCountCommit()) == 0)
                return this.GetTimeLastCommit().CompareTo(employee.GetTimeLastCommit());
            else
                return this.GetCountCommit().CompareTo(employee.GetCountCommit()) * -1;
        }
        public void AddCommit(string hash_, DateTime date_) // добавление коммита пользователю
        {
            CommitsComparer dc = new CommitsComparer();

            Commits.Add(new Tuple<string, DateTime>(hash_, date_));
            Commits.Sort(dc);//Выполнение сортировки на этапе добавления элемента обусловлено тем,
                             //чтобы не выполнять ее несколько раз при вызове GetTimeLastCommit
                             //При сортировке списка сотрудников
        }

        public override bool Equals(object? obj) // перегрузка Equals для проверки на равенство объектов класса
        {
            // возвращаем true, если имена совпадают
            if (obj is Employee employee) return Name == employee.Name;
            return false;
        }
        public override int GetHashCode() => Name.GetHashCode();
    }

    public class CommitsComparer : IComparer<Tuple<string, DateTime>> // класс для вызова функции в методе Sort()
                                                                      // для сортировки списка коммитов пользователя по времени
    {
        public int Compare(Tuple<string, DateTime>? x, Tuple<string, DateTime>? y)
        {
            if (x is null || y is null) throw new ArgumentException("Некорректное значение параметра");
            return x.Item2.CompareTo(y.Item2) * -1;
        }
    }
}