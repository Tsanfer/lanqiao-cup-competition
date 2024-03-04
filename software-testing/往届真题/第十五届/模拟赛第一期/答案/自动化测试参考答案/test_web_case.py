import unittest
from selenium import webdriver
from selenium.webdriver.firefox.service import Service
from time import sleep

from cn.lanqiao.web.login_page import LoginPage
from cn.lanqiao.web.add_user_page import AddUserPage
from cn.lanqiao.web.user_manage_page import UserManagePage


"""
 * 请按照操作步骤编写测试用例
 * 
 * 用例要求：
 * 1.合理使用元素等待时间
 * 2.请调用 Page 类中的方法实现操作步骤
 * 3.页面及 iframe 切换的代码填写在此文件中
 * 4.不要改动已经写好的方法名。

"""

class TestWebCase(unittest.TestCase):
    
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
        self.driver.get("https://6514fa5a1d59731dbb1eb60f.hz-iframe-svc.simplelab.cn/login")


    # 浏览器退出
    def tearDown(self):
        if self.driver:
            self.driver.quit()

    # 测试用例
    def test_case(self,):
        # TODO 请参照题目中【用例步骤】补全此处代码
        
        # TODO 实例化登录 page ，完成测试步骤
        login_page = LoginPage(self.driver)
        
        user_manage_page = UserManagePage(self.driver)

        # 步骤1-点击登录账号输入框并输入账户-admin
        login_page.input_login_name("admin")

        # 步骤2-点击登录密码输入框并输入密码-admin123
        login_page.input_login_password("admin123")

        # 步骤3-点击登录按钮
        login_page.click_login_button()

        # 断言1-断言用户名是否为【蓝桥超管】，如果断言失败则扣 4 分
        self.assertEqual("蓝桥超管",user_manage_page.get_username_text())
        
        # 菜单路径操作用例：点击系统管理->点击用户管理
        # 步骤4-点击系统管理菜单
        user_manage_page.click_system_menu()

        # 步骤5-点击用户管理菜单
        user_manage_page.click_user_menu()

        sleep(1)
        
        # 实现窗口切换用例
        # Frame切换、多窗口切换至新增用户表单
        self.driver.switch_to.frame(1)

        # 实现新增用户用例
        # 创建AddUserPage对象
        add_user_page = AddUserPage(self.driver)

        # 步骤6-点击新增+按钮
        user_manage_page.click_add_user_button()

        # 实现窗口切换用例
        self.driver.switch_to.default_content()

        self.driver.switch_to.frame(2)

        # 步骤7-点击用户名输入框并输入-userName
        add_user_page.input_user_name("userName")

        # 步骤8-点击登录用户输入框并输入-loginName
        add_user_page.input_login_name("loginName")

        # 步骤9-点击登录密码输入框并输入-loginPassword
        add_user_page.input_login_password("loginPassword")

        # 步骤10-点击单选框-角色：选择【普通角色】
        add_user_page.click_role()

        # 步骤11-点击保存按钮
        add_user_page.click_save_button()

        # 多窗口切换
        self.driver.switch_to.default_content()
        self.driver.switch_to.frame(1)
        sleep(1)
        
        # 断言2-断言新增后分页展示：期望=显示第 1 到第 3 条记录，总共 3 条记录，实际值=text
        self.assertEqual("显示第 1 到第 3 条记录，总共 3 条记录",user_manage_page.get_page_number_text())
            
        # 搜索用户用例
        
        # 步骤12-输入已新增登录用户
        user_manage_page.input_login_name("loginName")
        
        # 步骤13-点击搜索按钮
        user_manage_page.click_search_button()
        
        sleep(1)
        
        # 断言3-断言搜素后分页展示：期望=显示第 1 到第 1 条记录，总共 1 条记录，实际值=text
        self.assertEqual("显示第 1 到第 1 条记录，总共 1 条记录", user_manage_page.get_page_number_text())
        
        # 步骤14-删除搜索用户
        user_manage_page.delete_user()
        sleep(1)
        
        # 步骤15-点击重置按钮
        user_manage_page.click_reset_button()
        
        # 断言4-断言删除后分页展示：期望=显示第 1 到第 2 条记录，总共 2 条记录，实际值=text
        self.assertEqual("显示第 1 到第 2 条记录，总共 2 条记录", user_manage_page.get_page_number_text())
        sleep(2)
         
        # TODO 请实现 【用户退出】的操作方法
        # 步骤16-窗口切回主页面
        self.driver.switch_to.default_content()
        user_manage_page.click_login_out()
        sleep(2)

if __name__ == "__main__":
    unittest.main()   
        
        
        
        
        
        
        