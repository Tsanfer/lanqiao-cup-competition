import datetime


# 日期处理
# 1.strftime 该方法根据给定的日期、日期时间或时间对象创建指定格式的时间字符串
# 2.python中时间戳是10位包括年月日时分秒, 例如2022年12月19日的时间戳是1671379200
# 3.fromtimestamp方法
#   1.该方法可以由一个10位的时间戳转成datetime
#   2. 参数t接收的时间戳非10位时, 返回从1970-01-01开始的错误日期

# 时间格式(yyyy-MM-dd)
DATE_PATTERN = "%Y-%m-%d"

class DateUtils:

    @classmethod
    def format_datetime(cls, dt: datetime.datetime, pattern: str = DATE_PATTERN):
        if not dt:
            return None
        if not pattern or len(pattern) == 0:
            pattern = DATE_PATTERN
        return dt.strftime(pattern)

    @classmethod
    def timestamp_to_str(cls, timestamp: int, pattern: str = DATE_PATTERN):
        if not pattern or len(pattern) == 0:
            pattern = DATE_PATTERN
        if timestamp < 0:
            return None
        date_time = datetime.datetime.fromtimestamp(timestamp)
        return date_time.strftime(pattern)
