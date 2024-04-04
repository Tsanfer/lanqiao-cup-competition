from selenium.webdriver.common.by import By

"""
 * Page1-【登录】页面
 * 
 * 实现该页面中如下 3 个元素的操作代码（以下元素位置可参照题目附图）。
 * 
 * 1. 输入【登录名称】
 * 2. 输入【登录密码】
 * 3. 点击【登录】按钮
 
 * 注意1：不要在 Page 类中填写 iframe 切换的代码。
 * 注意2：不要改动已经写好的方法名。
"""
class LoginPage:
    def __init__(self, driver):
        self.driver = driver
    
    def input_login_name(self, loginName):
        # TODO 实现 【登录名称】输入的方法
        e_user_name = self.driver.find_element(By.XPATH, '/html/body/div/div[1]/div[2]/form/input[1]')
        e_user_name.clear()
        e_user_name.send_keys(loginName)
        #         e_auth_code = self.driver.find_element(By.XPATH, "/html/body/div/div[1]/div[2]/form/div[1]/div[1]/input")
        #         e_auto_login = self.driver.find_element(By.XPATH, '//*[@id="rememberme"]')

       

    def input_login_password(self, password):
        # TODO 实现【密码】输入的 方法
        e_passwd = self.driver.find_element(By.XPATH, '/html/body/div/div[1]/div[2]/form/input[2]')
        e_passwd.clear()
        e_passwd.send_keys(password)


    
    def click_login_button(self):
        # TODO 实现 【登录】按钮的点击方法
        e_login = self.driver.find_element(By.XPATH, '//*[@id="btnSubmit"]')
        e_login.click()
