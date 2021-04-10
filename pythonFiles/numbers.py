
class numbers:

	def __init__(self):
		self.number = 0

	def getNumber(self):
		return self.number

	def addNumber(self, numberToAddBy):
		self.number += numberToAddBy

numbersInstance = numbers()

def addToInstance(numberToAddBy):
	numbersInstance.addNumber(numberToAddBy)
	return ""

def getInstanceValue():
	return str(numbersInstance.getNumber())
