using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace CROC_7
{
    public static class RatingContributors
    {
        /// <summary>
        /// Returns top of rating, default - returns top-3
        /// </summary>
        public static List<string> GetTop(IEnumerable<string> rating, int count = 3)
        {
            return rating.Take(count).ToList();
        }

        public static IEnumerable<string> GetRating(IEnumerable<string> commits)
        {
            return commits
                .Distinct()
                .Select(commit => commit.Split())
                .Where(IsCommit)
                .Select(commit => commit[0])
                .GroupBy(commit => commit)
                .OrderByDescending(commit => commit.Count())
                .Select(commit => commit.Key);
        }

        public static bool IsCommit(string[] commit)
        {
            return commit != null
                && commit.Length == 3
                && IsName(commit[0])
                && IsShortHash(commit[1])
                && IsDateTime(commit[2]);
        }

        private static bool IsDateTime(string data)
        {
            return DateTime.TryParse(data, out DateTime dateTime);
        }

        private static bool IsShortHash(string hash)
        {
            if(hash == null || hash.Length != 7)
                return false;
            foreach(var symbol in hash)
            {
                if(!char.IsLetterOrDigit(symbol))
                    return false;
            }
            return true;
        }

        private static bool IsName(string name)
        {
            if(name  == null || name.Length == 0) 
                return false;
            var isFirst = true;
            foreach(var symbol in name)
            {
                if(isFirst)
                {
                    isFirst = false;
                    if (!char.IsLetter(symbol) && symbol != '_')
                        return false;
                }
                else
                {
                    if (!char.IsLetterOrDigit(symbol) && symbol != '_')
                        return false;
                }  
            }
            return true;
        }
    }
}
