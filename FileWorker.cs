using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CROC_7
{
    internal static class FileWorker
    {
        public static readonly string projectPath;

        static FileWorker()
        {
                projectPath = Directory.GetParent(Directory.GetCurrentDirectory())
                .Parent.Parent.FullName;
        }

        public static IEnumerable<string> ReadFile(string fileName)
        {
            var path = Path.Combine(projectPath, fileName);
            foreach (var line in  File.ReadLines(path))
            {
                yield return line;
            }
        }

        public static void SaveFile(string fileName, List<string> input)
        {
            var path = Path.Combine(projectPath , fileName);
            File.WriteAllLines(path, input);
        }
    }
}
