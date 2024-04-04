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

 * 注意1：不要在 Page 类中填写 iframe 切换的代码。
 * 注意2：不要改动已经写好的方法名。

"""
class UserManagePage:
    def __init__(self, driver):
        self.driver = driver

    def click_system_menu(self):
        # TODO 请实现点击【系统管理】菜单的操作方法
        e = self.driver.find_element(By.XPATH, '/html/body/div/nav/div[2]/div[1]/ul/li[3]/a/span[1]')
        e.click()
        
    
    def click_user_menu(self):
        # TODO 请实现点击【用户管理】菜单的操作方法
        e = self.driver.find_element(By.XPATH, '/html/body/div/nav/div[2]/div[1]/ul/li[3]/ul/li[1]/a')
        e.click()
        
          
    
    def click_add_user_button(self):    
        # TODO 请实现点击【新增+】按钮的操作方法
        e = self.driver.find_element(By.XPATH, '/html/body/div[2]/div/div/div[2]/div[1]/div[1]/div[1]/div/a[1]')
        e.click()
       
        
    
    def input_login_name(self, loginName):
        # TODO 请实现搜索框输入【登录名称】的操作方法
        e = self.driver.find_element(By.XPATH, '/html/body/div[2]/div/div/div[1]/form/div/ul/li[1]/input')
        e.clear()
        e.send_keys(loginName)
        

    
    def click_search_button(self):
        # TODO 请实现点击【搜索】按钮的操作方法
        e = self.driver.find_element(By.XPATH, '/html/body/div[2]/div/div/div[1]/form/div/ul/li[5]/a[1]')
        e.click()
        

    
    def click_reset_button(self):
        # TODO 请实现【重置】按钮的操作方法
        e = self.driver.find_element(By.XPATH, '/html/body/div[2]/div/div/div[1]/form/div/ul/li[5]/a[2]')
        e.click()
        

    
    def delete_user(self):
        # TODO 请实现【删除】用户的操作方法
        e = self.driver.find_element(By.XPATH, '/html/body/div[2]/div/div/div[2]/div[1]/div[2]/div[2]/table/tbody/tr/td[9]/a[2]')
        e.click()
        
    
    def get_username_text(self):
        # TODO: 实现获取【登录成功后的用户名文本】的操作方法 
        e = self.driver.find_element(By.XPATH, '/html/body/div/div/div[1]/nav/ul/li[3]/a/span')
        return e.text
        
    
    
    def get_page_number_text(self):
        # TODO: 实现获取【分页显示信息】的操作方法
        e = self.driver.find_element(By.XPATH, '/html/body/div[2]/div/div/div[2]/div[1]/div[3]/div[1]/span')
        return e.text
        
    
    def click_login_out(self):
        # TODO 请实现 【用户退出】的操作方法
        # 点击用户名
        e = self.driver.find_element(By.XPATH, '/html/body/div[1]/div/div[1]/nav/ul/li[3]/a')
        e.click()

        # 点击退出登陆
        e = self.driver.find_element(By.XPATH, '/html/body/div[1]/div/div[1]/nav/ul/li[3]/ul/li[6]/a')
        e.click()
        
        
        