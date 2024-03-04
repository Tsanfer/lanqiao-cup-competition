from selenium.webdriver.common.by import By
from time import sleep

"""
 * page2-【用户管理 】页面
 * 
 * 需实现该页面中如下 10 个元素的操作代码，以下元素位置可参照题目附图：
 *
 * 1. 点击【系统管理】菜单
 * 2. 点击【用户管理】菜单
 * 3. 点击【新增+】按钮
 * 4. 输入【登录名称】搜索框
 * 5. 点击【搜索】按钮
 * 6. 点击【重置】按钮
 * 7. 点击【删除】按钮
 * 8. 获取【分页显示信息】文本
 * 9. 获取【登录成功后的用户名】文本
 * 10. 用户【用户退出】的操作方法

 * 注意1：不要在 Page 类中填写 页面及 iframe 切换的代码
 * 注意2：不要改动已经写好的方法名。

"""
class UserManagePage:
    def __init__(self, driver):
        self.driver = driver
        
    
    def click_system_menu(self):
        # TODO 请实现点击【系统管理】菜单的操作方法
        self.driver.find_element(By.XPATH, "//*[@id='side-menu']/li[3]/a/span[1]").click()
    
    def click_user_menu(self):
        # TODO 请实现点击【用户管理】菜单的操作方法
        self.driver.find_element(By.XPATH, "//*[@id='side-menu']/li[3]/ul/li[1]/a").click()
    
    def click_add_user_button(self):    
        # TODO 请实现点击【新增+】按钮的操作方法
        
        self.driver.find_element(By.XPATH, "//*[@id='toolbar']/a[1]").click()
        sleep(1)

    
    def input_login_name(self, loginName):
        # TODO 请实现搜索框输入【登录名称】的操作方法
        # 清空密码输入框内容，防止脏数据
        self.driver.find_element(By.XPATH, '//*[@id="user-form"]/div/ul/li[1]/input').clear()

        # 输入新增时的登录用户名
        self.driver.find_element(By.XPATH, '//*[@id="user-form"]/div/ul/li[1]/input').send_keys(loginName)

    
    def click_search_button(self):
        # TODO 请实现点击【搜索】按钮的操作方法
        
        self.driver.find_element(By.XPATH, '//*[@id="user-form"]/div/ul/li[5]/a[1]').click()
        sleep(1)

    
    def click_reset_button(self):
        # TODO 请实现【重置】按钮的操作方法
        
        self.driver.find_element(By.XPATH, '//*[@id="user-form"]/div/ul/li[5]/a[2]').click()
        sleep(1)
        
    
    def delete_user(self):
        # TODO 请实现【删除】用户的操作方法
        self.driver.find_element(By.XPATH, '//*[@id="bootstrap-table"]/tbody/tr/td[9]/a[2]').click()
        sleep(1)

    
    def get_username_text(self):
        # TODO: 实现获取【登录成功后的用户名文本】的操作方法 
        getUserNameTextElement = self.driver.find_element(By.XPATH, '//*[@id="page-wrapper"]/div[1]/nav/ul/li[3]/a/span')
        
        getUsernameText = getUserNameTextElement.text
        
        return getUsernameText
    
    
    def get_page_number_text(self):
        # TODO: 实现获取【分页显示信息】的操作方法
        getPageNumberTextElement = self.driver.find_element(By.XPATH, '/html/body/div[2]/div/div/div[2]/div[1]/div[3]/div[1]/span')
        
        getPageNumberText = getPageNumberTextElement.text
        
        return getPageNumberText
    
    
    def click_login_out(self):
        # TODO 请实现 【用户退出】的操作方法
        # 点击蓝桥超管
        self.driver.find_element(By.XPATH, "//*[@id=\"page-wrapper\"]/div[1]/nav/ul/li[3]/a/span").click()
        sleep(1)
        # 点击退出登录按钮
        self.driver.find_element(By.XPATH, "//*[@id=\"page-wrapper\"]/div[1]/nav/ul/li[3]/ul/li[6]/a").click()
        
        
        
        
        