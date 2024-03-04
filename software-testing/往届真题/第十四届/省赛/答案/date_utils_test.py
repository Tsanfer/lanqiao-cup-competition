import datetime
import unittest

from com.lanqiao.date_utils import DateUtils, DATE_PATTERN


class DateUtilsTest(unittest.TestCase):
    def test_format_datetime(self):
        self.assertEqual(None, DateUtils.format_datetime(None, None))
        self.assertEqual("2022-12-19", DateUtils.format_datetime(datetime.datetime.fromtimestamp(1671379200), None))
        self.assertEqual("2022-12-19", DateUtils.format_datetime(datetime.datetime.fromtimestamp(1671379200), ""))
        self.assertEqual("2022-12/19",
                         DateUtils.format_datetime(datetime.datetime.fromtimestamp(1671379200), "%Y-%m/%d"))

    def test_timestamp_to_str(self):
        self.assertEqual("1970-01-01", DateUtils.timestamp_to_str(0, None))
        self.assertEqual(None, DateUtils.timestamp_to_str(-1, None))
        self.assertEqual("2022-12-19", DateUtils.timestamp_to_str(1671379200, None))
        self.assertEqual("2022-12-19", DateUtils.timestamp_to_str(1671379200, DATE_PATTERN))


if __name__ == '__main__':
    unittest.main()
