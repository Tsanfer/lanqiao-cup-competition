import unittest
from cn.lanqiao.group_competition import GroupCompetition

#  单元测试
# 请使用 分支覆盖法 对被测源码 GroupCompetition 类中的 grouping 方法设计单元测试用例。
# 请在下方 GroupCompetitionTest 类中填写单元测试代码。
# 分支覆盖：又称判定覆盖，是指设计适当数量的测试用例运行被测程序，使得程序中每个判定语句的真、假分支至少被执行一次。

class GroupCompetitionTest(unittest.TestCase):
    def test_grouping_01(self):
        self.assertEqual("少儿A组", GroupCompetition.grouping(5, 87))

    def test_grouping_02(self):
        self.assertEqual("少儿B组", GroupCompetition.grouping(5, 79))
    
    def test_grouping_03(self):
        self.assertEqual("青少年A组", GroupCompetition.grouping(18, 87))

    def test_grouping_04(self):
        self.assertEqual("青少年B组", GroupCompetition.grouping(13, 79))
        
    def test_grouping_05(self):    
        self.assertEqual("无复赛资格", GroupCompetition.grouping(20, 85))


if __name__ == '__main__':
    unittest.main()