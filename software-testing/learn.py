import unittest
from selenium import webdriver
from selenium.webdriver.firefox.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.common.keys import Keys


from time import sleep

class WebCaseTest(unittest.TestCase):
    def setUp(self):
        gecko_path = "C:\\LanQiaoTest\\project\\PythonLanqiaoTest\\driver\\geckodriver.exe"
        options = webdriver.FirefoxOptions()
        options.set_preference("security.fileuri.strict_origin_policy", False)
        options.set_preference("security.fileuri.origin_policy", "*")
        self.driver = webdriver.Firefox(service=Service(gecko_path),options=options)
        self.driver.implicitly_wait(5)
        self.driver.maximize_window()
        
        self.driver.get("https://661f3927c078967d2a8215eb.hz-iframe-svc.simplelab.cn/login")
          
    def test_browser(self):
        # 设置浏览器窗口大小
        self.driver.set_window_size(1280, 720)
        print(self.driver.get_window_size())
        #  执行js脚本
        #  新标签页打开网页（自动切换到新标签页）
        js = "window.open('https://tsanfer.com');"
        self.driver.execute_script(js)
        # 等待网页打开
        sleep(5)
        
        #  切换标签页
        self.driver.switch_to.window(self.driver.window_handles[0])
        #  关闭标签页
        self.driver.close()
        # 重置标签页位置（程序中）
        self.driver.switch_to.window(self.driver.window_handles[0])

        # 获取当前 URL
        print(self.driver.current_url)
        
        e = self.driver.find_element(By.LINK_TEXT, '升腾C92 刷 OpenWrt 作旁路由设置 DNS 服务、扩容分区、设置 swap')
        e.click()
        
        wait = WebDriverWait(self.driver, 5, 0.5)
        e = wait.until(EC.presence_of_element_located((By.LINK_TEXT, '升腾C92 刷 OpenWrt 作旁路由设置 DNS 服务、扩容分区、设置 swap')), "time out")
        # 前进和后退
        self.driver.back()
        self.driver.forward()
        
        # 刷新页面
        self.driver.refresh()
        sleep(1)
        
        e = self.driver.find_element(By.XPATH, '//*[@id="app"]/div[1]/div/div[2]/div[3]/div/main/section/div[1]/h1')
        self.assertEqual(e.text, '升腾C92 刷 OpenWrt 作旁路由设置 DNS 服务、扩容分区、设置 swap',"Page right")
#         self.assertNotEqual(e.text, '升腾C92 刷 OpenWrt 作旁路由设置 DNS 服务、扩容分区、设置 swap',"Page error")
        
        e = self.driver.find_element(By.XPATH, '//*[@id="app"]/div[1]/div/div[2]/div[3]/div/main/footer')
        self.driver.execute_script("arguments[0].scrollIntoView();", e)
        sleep(3)
        
        e = self.driver.find_element(By.XPATH, '//*[@id="app"]/div[1]/div/div[2]/header/div[2]/div[2]/input')
        actions = ActionChains(self.driver)
        actions.move_to_element(e)
        actions.click()
        actions.send_keys("WHOAMI")
        actions.perform()
        actions.key_down(Keys.CONTROL).send_keys("a").key_up(Keys.CONTROL).perform()
        actions.send_keys(Keys.BACKSPACE).perform()
        
        sleep(5)
        
        
    def tearDown(self):
        if self.driver:
            self.driver.quit()
            
if __name__ == "__main__":
    unittest.main()
