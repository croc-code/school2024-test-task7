using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

partial class Program
{
    public static DateTime GetTime(string dateTime) //получение даты в формате DateTime из строки списка коммитов
    {
        dateTime = dateTime.Split(' ')[2];

        char[] delimiterChars = { 'T', '.', '-', ':' }; // разделительные знаки

        string[] dateTime_ = dateTime.Split(delimiterChars);

        int[] dateTimeInt = new int[7];

        for (int i = 0; i < dateTime_.Length; ++i)
        {
            dateTimeInt[i] = Convert.ToInt32(dateTime_[i]);
        }

        return new DateTime(dateTimeInt[0], dateTimeInt[1], dateTimeInt[2],
            dateTimeInt[3], dateTimeInt[4], dateTimeInt[5], dateTimeInt[6]);
    }

    public static string GetHash(string hash) //получаем хэш коммита из строки
    {
        return hash.Split(' ')[1];
    }

    public static string GetName(string name) //получение имени пользователя
    {
        return name.Split(' ')[0];
    }
}
