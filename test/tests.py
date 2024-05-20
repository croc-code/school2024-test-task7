import unittest
from app.classes.commits import Commit
from app.classes.contributor import Contributor

class TestCommit(unittest.TestCase):
    def test_correct(self):
        commit = Commit("25ec001", "2024-04-24T13:56:39")
        self.assertTrue(commit.validate())
        commit = Commit("25ec001", "2024-04-24T13:56:39.123")
        self.assertTrue(commit.validate())

    def test_incorrect_args(self):
        with self.assertRaises(ValueError):
            Commit("2024-04-24T13:56:39.492")
        with self.assertRaises(ValueError):
            Commit()
        with self.assertRaises(ValueError):
            Commit("25ec0011", dt_str="2024-04-24T13:56:39.492")

    def test_incorrect_hash(self):
        with self.assertRaises(ValueError):
            Commit("failedhash", "2024-04-24T13:56:39.492")
        with self.assertRaises(ValueError):
            Commit("25ec00", "2024-04-24T13:56:39.492")
        with self.assertRaises(ValueError):
            Commit("25ec0011", "2024-04-24T13:56:39.492")

    def test_incorrect_time(self):
        with self.assertRaises(ValueError):
            Commit("25ec001", "2024-04-24 13:56:39.492")
        with self.assertRaises(ValueError):
            Commit("25ec001", "2024-04-24T13:56")
        with self.assertRaises(ValueError):
            Commit("25ec001", "13:56:39.492")


class TestContributor(unittest.TestCase):
    def setUp(self):
        self.commit = Commit("25ec001", "2024-04-24T13:56:39.492")
        self.commit1 = Commit("25ec002", "2024-04-24T13:57:39.492")
        self.commit2 = Commit("25ec003", "2024-04-24T13:59:39.492")
        self.commit3 = Commit("25ec004", "2024-04-24T13:58:39.492")

    def test_correct(self):
        contributor = Contributor("test")
        contributor.add_commit(self.commit)
        self.assertEqual(contributor.name, "test")
        self.assertEqual(contributor.commits_list, [self.commit])

    def test_incorrect_name(self):
        with self.assertRaises(ValueError):
            Contributor("123")
        with self.assertRaises(ValueError):
            Contributor("_sad1234")
        with self.assertRaises(ValueError):
            Contributor("a123^&!@")
        with self.assertRaises(ValueError):
            Contributor("qpwioe0-123")

    def test_incorrect_commit(self):
        contributor = Contributor("test")
        self.assertFalse(contributor.add_commit_raw("25ec0011", "2024-04-24T13:56:39.492")[0])
        self.assertFalse(contributor.add_commit_raw("25ec001", "2024-04-24T13:56")[0])
        self.assertEqual(contributor.commits_list, [])

    def test_commit_amount(self):
        contributor = Contributor("test")
        self.assertEqual(contributor.get_commits_amount(), 0)
        contributor.add_commit(self.commit)
        self.assertEqual(contributor.get_commits_amount(), 1)
        contributor.add_commit(self.commit1)
        self.assertEqual(contributor.get_commits_amount(), 2)
        contributor.add_commit(self.commit2)
        self.assertEqual(contributor.get_commits_amount(), 3)
        contributor.add_commit(self.commit3)
        self.assertEqual(contributor.get_commits_amount(), 4)



if __name__ == "__main__":
    unittest.main()