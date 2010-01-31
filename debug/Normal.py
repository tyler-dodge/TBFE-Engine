import sys
sys.path.append("TbfePy/")
import Tbfe
test=Tbfe.TBFE()
print("test")
for i in range(0,5000):
    test.runEngine()

