
# 自动化测试        
# 如果不会设置Chrome驱动，请把chromedriver.exe复制到C盘根目录下，参考代码如下：
# service = Service("C:\\chromedriver.exe")

# 如果遇到无法启动chrome，控制台显示500的error
# 可以尝试取消沙盒模式，增加--no-sandbox参数来解决。参考代码如下：
# opt = Options()
# opt.add_argument('--no-sandbox')
# self.driver = webdriver.Chrome(chrome_options = opt, service=service)

class GoodsEditTest(unittest.TestCase):

    @classmethod
    def setUpClass(cls) -> None:
        #请填写代码

    def test_login(self) -> None:
        #请填写代码

    def test_add(self) -> None:
        #请填写代码

    def test_del(self) -> None:
        #请填写代码

    @classmethod
    def tearDownClass(cls) -> None:
        #请填写代码


#请填写代码