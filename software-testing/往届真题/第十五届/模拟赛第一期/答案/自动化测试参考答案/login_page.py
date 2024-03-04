from selenium.webdriver.common.by import By
from time import sleep
"""
 * Page1-【登录】页面
 * 
 * 实现该页面中如下 3 个元素的操作代码（以下元素位置可参照题目附图）。
 * 
 * 1. 输入【登录名称】
 * 2. 输入【登录密码】
 * 3. 点击【登录】按钮

 * 注意1：不要在 Page 类中填写 页面及 iframe 切换的代码
 * 注意2：不要改动已经写好的方法名。

"""
class LoginPage:
    def __init__(self, driver):
        self.driver = driver

    
    def input_login_name(self, loginName):
        # TODO 实现 【登录名称】输入的方法
        # 清空用户名输入框内容，防止脏数据
        self.driver.find_element(By.XPATH, '//*[@id="signupForm"]/input[1]').clear()

        # 输入传入的loginName参数
        self.driver.find_element(By.XPATH, '//*[@id="signupForm"]/input[1]').send_keys(loginName)

    
    def input_login_password(self, password):
        # TODO 实现【密码】输入的 方法
        
        # 清空密码输入框内容，防止脏数据
        self.driver.find_element(By.XPATH, '//*[@id="signupForm"]/input[2]').clear()

        # 输入传入的password参数
        self.driver.find_element(By.XPATH, '//*[@id="signupForm"]/input[2]').send_keys(password)


    
    def click_login_button(self):
        # 实现 【登录】按钮的点击方法
        
        # 点击登录按钮
        self.driver.find_element(By.XPATH, '//*[@id="btnSubmit"]').click()

        # 等待2秒，模拟操作延迟
        sleep(2)
