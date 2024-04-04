from selenium.webdriver.common.by import By

"""
 * Page3-【新增用户】页面 
 * 需实现该页面中如下 5 个元素的操作代码，以下元素位置可参照题目附图：
 *
 * 1. 表单框输入【用户名】
 * 2. 表单框输入【登录账号】
 * 3. 表单框输入【密码】
 * 4. 单选框选择【普通用户】
 * 5. 点击【保存】按钮
 
 *  注意1：不要在 Page 类中填写 iframe 切换的代码。
 *  注意2：不要改动已经写好的方法名。
"""
class AddUserPage:
    def __init__(self, driver):
        self.driver = driver

    
    
    def input_user_name(self, userName):
        # TODO 实现 表单【用户名】点击和输入 的方法
        e = self.driver.find_element(By.XPATH, '//*[@id="userName"]')
        e.clear()
        e.send_keys(userName)
        
        
    
    def input_login_name(self, loginName):
        # TODO 实现 表单【登录账号】点击和输入 的方法
        e = self.driver.find_element(By.XPATH, '//*[@id="loginName"]')
        e.clear()
        e.send_keys(loginName)


    
    def input_login_password(self, loginPassword):
        # TODO 实现 表单【密码】点击和输入 的方法
        e = self.driver.find_element(By.XPATH, '//*[@id="password"]')
        e.clear()
        e.send_keys(loginPassword)


    
    def click_role(self):
        # TODO 实现 表单【普通用户】单选 的方法
        e = self.driver.find_element(By.XPATH, '/html/body/div[1]/form/div[6]/div/div/div/label[2]')
        e.click()

    
    def click_save_button(self):
        # TODO 实现 表单【保存】按钮点击的方法
        e = self.driver.find_element(By.XPATH, '/html/body/div[2]/div/button[1]')
        e.click()
     
