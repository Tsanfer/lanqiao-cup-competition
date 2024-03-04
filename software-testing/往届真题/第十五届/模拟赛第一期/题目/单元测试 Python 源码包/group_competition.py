# 根据年龄和初赛成绩进行复赛分组： 
# 1. 年龄大于 18 岁或初赛成绩小于 60 分，无复赛资格；
# 2. 年龄小于等于 12 岁，初赛成绩大于等于 80 分，复赛分组为“少儿 A 组”；初赛成绩小于 80 分，复赛分组为“少儿 B 组”； 
# 3. 年龄大于 12 岁，初赛成绩大于等于 80 分，复赛分组为“青年年 A 组”；初赛成绩小于 80 分，复赛分组为“青少年 B 组”。

class GroupCompetition:
    # 根据年龄和初赛成绩进行复赛分组
    @classmethod
    def grouping(cls, age, score):
        if age <= 18 and score >= 60:
            if age <= 12:
                if score >= 80:
                    return "少儿A组"
                else:
                    return "少儿B组"
            else:
                if score  >= 80:
                    return "青少年A组"
                else:
                    return "青少年B组"
        else:
            return "无复赛资格"