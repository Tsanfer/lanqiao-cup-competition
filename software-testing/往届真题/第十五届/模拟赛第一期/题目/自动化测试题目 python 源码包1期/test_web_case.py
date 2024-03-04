import unittest
from selenium import webdriver
from selenium.webdriver.firefox.service import Service

from cn.lanqiao.web.login_page import LoginPage
from cn.lanqiao.web.add_user_page import AddUserPage
from cn.lanqiao.web.user_manage_page import UserManagePage


"""
 * 请按照操作步骤编写测试用例
 * 
 * 用例要求：
 * 1.合理使用元素等待时间。
 * 2.请调用 Page 类中的方法实现操作步骤。
 * 3.合理使用 iframe 切换，iframe 切换的代码填写在此文件中。
 * 4.不要改动已经写好的方法名。

"""

class TestWebCase(unittest.TestCase):
    
    # 浏览器初始化
    def setUp(self):
        # 不要改动此处 driver 位置
        gecko_path = "C:\\LanQiaoTest\\project\\PythonLanqiaoTest\\driver\\geckodriver.exe"
        
        options = webdriver.FirefoxOptions()
        
        options.set_preference('security.fileuri.strict_origin_policy', False)
        
        options.set_preference('security.fileuri.origin_policy', '*')
        
        self.driver = webdriver.Firefox(service=Service(gecko_path),options=options)
      
        self.driver.implicitly_wait(10)
        
        self.driver.maximize_window()
        
        # TODO 打开被测系统的网址
        self.driver.get("")


    # 请在此方法中续写测试用例
    def test_case(self,):
        # 创建 LoginPage 对象
        login_page = LoginPage(self.driver)
        
        # 创建 UserManagePage 对象
        user_manage_page = UserManagePage(self.driver)
        
        # 创建 AddUserPage 对象
        add_user_page = AddUserPage(self.driver)
        
        
        # TODO 请调用以上3个实例化对象中的方法完成测试用例代码（具体请参照题目中的用例步骤描述和截图）
        
        
        
        
        
    # 浏览器退出
    def tearDown(self):
        if self.driver:
            self.driver.quit()
            
        
if __name__ == "__main__":
    unittest.main()       
        
        
        
        