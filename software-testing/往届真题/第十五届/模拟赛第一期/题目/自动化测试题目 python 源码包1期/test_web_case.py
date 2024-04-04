import unittest
from selenium import webdriver
from selenium.webdriver.firefox.service import Service

from cn.lanqiao.web.login_page import LoginPage
from cn.lanqiao.web.user_manage_page import UserManagePage
from cn.lanqiao.web.add_user_page import AddUserPage

from time import sleep
from selenium.webdriver.common.by import By

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
        self.driver.get("https://660e94508755772af51d62b7.hz-iframe-svc.simplelab.cn/login")


    # 请在此方法中续写测试用例
    def test_case(self,):
        # 创建 LoginPage 对象
        login_page = LoginPage(self.driver)
        
        # 创建 UserManagePage 对象
        user_manage_page = UserManagePage(self.driver)
        
        # 创建 AddUserPage 对象
        add_user_page = AddUserPage(self.driver)
        
        
        # TODO 请调用以上3个实例化对象中的方法完成测试用例代码（具体请参照题目中的用例步骤描述和截图）
        login_page.input_login_name("admin")
        login_page.input_login_password("admin123")
        login_page.click_login_button()
        
        # 等待进入【用户管理】界面
        sleep(1)
        
        self.assertEqual(user_manage_page.get_username_text(), "蓝桥超管")
        
        user_manage_page.click_system_menu()
        user_manage_page.click_user_menu()
        
        #  切换到【用户管理】界面内部
        self.driver.switch_to.default_content()
        self.driver.switch_to.frame(1)
        # /html/body/div[1]/div/div[3]/iframe[2]
        sleep(1)
        
        user_manage_page.click_add_user_button()
        
        #  等待进入【添加用户】界面
        sleep(1)
        
        #  切换到【添加用户】界面内部
        self.driver.switch_to.default_content()
        self.driver.switch_to.frame(2)
        sleep(1)
        
        add_user_page.input_user_name("whoami")
        add_user_page.input_login_name("whoami_account")
        add_user_page.input_login_password("123456")
        add_user_page.click_role()
        add_user_page.click_save_button()
        
        #  切换到【用户管理】界面内部
        sleep(1)
        self.driver.switch_to.default_content()
        self.driver.switch_to.frame(1)
        sleep(1)
        
        self.assertEqual(user_manage_page.get_page_number_text(), "显示第 1 到第 3 条记录，总共 3 条记录")
        
        user_manage_page.input_login_name("whoami_account")
        user_manage_page.click_search_button()
        
        #  等待搜索成功
        sleep(1)
        
        self.assertEqual(user_manage_page.get_page_number_text(), "显示第 1 到第 1 条记录，总共 1 条记录")
        
        user_manage_page.delete_user()
        sleep(1)
        user_manage_page.click_reset_button()
        self.assertEqual(user_manage_page.get_page_number_text(), "显示第 1 到第 2 条记录，总共 2 条记录")
        
        self.driver.switch_to.default_content()
        sleep(1)
        user_manage_page.click_login_out()
        
        
        
        sleep(3)
        
    # 浏览器退出
    def tearDown(self):
        if self.driver:
            self.driver.quit()
            
        
if __name__ == "__main__":
    unittest.main()       
        
        
        
        