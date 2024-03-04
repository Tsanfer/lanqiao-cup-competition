import time

from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
import unittest


class GoodsEditTest(unittest.TestCase):

    @classmethod
    def setUpClass(cls) -> None:
        opt = Options()
        opt.add_argument('--no-sandbox')
        service = Service("D:\\360MoveData\\Users\\Administrator\\Desktop\\考试软件工具包\\chrome\\chromedriver.exe")
        cls.driver = webdriver.Chrome(chrome_options=opt, service=service)
        cls.driver.get("http://localhost:8084/platform-framework/")

    def test_login(self) -> None:
        # 登录
        # 输入用户名
        self.driver.find_element(By.XPATH, '/html/body/div[1]/div[1]/div/div/div/div[1]/div/input').send_keys('ceshi')
        # 输入密码
        self.driver.find_element(By.XPATH, '/html/body/div[1]/div[1]/div/div/div/div[2]/div/input').send_keys('ceshi')
        # 点击登录按钮
        self.driver.find_element(By.XPATH, '/html/body/div[1]/div[1]/div/div/div/div[3]/button').click()
        time.sleep(3)

        frame_main = self.driver.find_element(By.XPATH, '/html/body/div[1]/div[1]/div[3]/iframe')
        self.driver.switch_to.frame(frame_main)
        # 获取欢迎text
        welcome_text = self.driver.find_element(By.XPATH, '/html/body/div[1]/div/div[1]/h1').text
        # 断言预期结果是否包含欢迎登录后台管理系统
        assert "欢迎登录后台管理系统" in welcome_text

    def test_add(self) -> None:
        self.driver.switch_to.default_content()
        # 点击编辑商品
        self.driver.find_element(By.XPATH, '/html/body/div/nav/div[2]/div[1]/ul/li[4]/a').click()
        time.sleep(2)
        # 点击所有商品
        self.driver.find_element(By.XPATH, '/html/body/div[1]/nav/div[2]/div[1]/ul/li[4]/ul/li[1]/a').click()
        frame_product_list = self.driver.find_element(By.XPATH, '/html/body/div[1]/div[1]/div[3]/iframe[2]')
        self.driver.switch_to.frame(frame_product_list)
        # 点击新增按钮
        self.driver.find_element(By.XPATH, '/html/body/div[1]/div[1]/div[1]/div[2]/button[1]').click()
        time.sleep(1)
        # 商品类型 选择
        self.driver.find_element(By.XPATH,
                                 '/html/body/div[1]/div[2]/div[2]/div[1]/div[2]/div[1]/form/div[1]/div/div[1]/i').click()
        self.driver.find_element(By.XPATH, '/html/body/div[2]/div[2]/div/ul/li/ul/li[9]/span').click()
        self.driver.find_element(By.XPATH, '/html/body/div[2]/div[2]/div/ul/li/ul/li[9]/ul/li[1]/a/span[2]').click()
        self.driver.find_element(By.XPATH, '/html/body/div[2]/div[3]/a[1]').click()
        # 商品序列号
        self.driver.find_element(By.XPATH,
                                 '/html/body/div[1]/div[2]/div[2]/div[1]/div[2]/div[1]/form/div[2]/div/div/input').send_keys(
            'BP2323232')
        # 名称
        self.driver.find_element(By.XPATH,
                                 '/html/body/div[1]/div[2]/div[2]/div[1]/div[2]/div[1]/form/div[3]/div/div/input').send_keys(
            'test_手机')
        # 品牌
        self.driver.find_element(By.XPATH,
                                 '/html/body/div[1]/div[2]/div[2]/div[1]/div[2]/div[1]/form/div[4]/div/div').click()
        self.driver.find_element(By.XPATH,
                                 '/html/body/div[1]/div[2]/div[2]/div[1]/div[2]/div[1]/form/div[4]/div/div/div[2]/ul[2]/li[1]').click()
        # 类别
        self.driver.find_element(By.XPATH,
                                 '/html/body/div[1]/div[2]/div[2]/div[1]/div[2]/div[1]/form/div[5]/div/div').click()
        self.driver.find_element(By.XPATH,
                                 '/html/body/div[1]/div[2]/div[2]/div[1]/div[2]/div[1]/form/div[5]/div/div/div[2]/ul[2]/li[1]').click()

        # 库存
        self.driver.find_element(By.XPATH,
                                 '/html/body/div[1]/div[2]/div[2]/div[1]/div[2]/div[1]/form/div[6]/div/div/input').send_keys(
            '99999')
        # 零售价格
        self.driver.find_element(By.XPATH,
                                 '/html/body/div[1]/div[2]/div[2]/div[1]/div[2]/div[1]/form/div[7]/div/div/input').send_keys(
            '234.9')
        # 市场价
        self.driver.find_element(By.XPATH,
                                 '/html/body/div[1]/div[2]/div[2]/div[1]/div[2]/div[1]/form/div[8]/div/div/input').send_keys(
            '431.9')
        # 主图
        self.driver.find_element(By.XPATH,
                                 '/html/body/div[1]/div[2]/div[2]/div[1]/div[2]/div[1]/form/div[9]/div[1]/div/div/div/input').send_keys(
            'http://img.laoyou17.com/softtest/20221225/153418252cd844.png')

        # 提交
        self.driver.find_element(By.XPATH, '/html/body/div[1]/div[2]/div[2]/div[2]/button[1]').click()
        time.sleep(1)
        # 操作成功确定框
        self.driver.find_element(By.XPATH, '/html/body/div[9]/div[3]/a').click()
        time.sleep(1)

        product_name = self.driver.find_element(By.XPATH,
                                                '/html/body/div[1]/div[1]/div[2]/div[3]/div[3]/div/table/tbody/tr[2]/td[5]').text
        # 断言预期结果是否包含test_手机
        assert "test_手机" in product_name

    def test_del(self) -> None:
        # 选中 删除
        self.driver.find_element(By.XPATH,
                                 '/html/body/div[1]/div[1]/div[2]/div[3]/div[3]/div/table/tbody/tr[2]/td[2]/input').click()
        self.driver.find_element(By.XPATH, '/html/body/div[1]/div[1]/div[1]/div[2]/button[3]').click()
        time.sleep(2)
        # 确认框
        self.driver.find_element(By.XPATH, '/html/body/div[9]/div[3]/a[1]').click()
        time.sleep(2)
        # 操作成功确定框
        self.driver.find_element(By.XPATH, '/html/body/div[9]/div[3]/a').click()

    @classmethod
    def tearDownClass(cls) -> None:
        cls.driver.quit()


if __name__ == "__main__":
    suite = unittest.TestSuite()
    suite.addTest(GoodsEditTest("test_login"))
    suite.addTest(GoodsEditTest("test_add"))
    suite.addTest(GoodsEditTest("test_del"))
    unittest.TextTestRunner().run(suite)
