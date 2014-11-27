#!/usr/bin/python

class Employee:
	employee_total = 0
	def __init__(self,employee_name,employee_id):
		self.employee_name = employee_name
		self.employee_id = employee_id
		Employee.employee_total += 1
	def total(self):
		print "Total employee %d" % Employee.employee_total
	def getName(self):
		print "Name: ", self.employee_name

class Jijia(Employee):
	def __init__(self,employee_name,employee_id):
		self.position = "Jijia"
	def getPos(self):
		print "Jijia"
emp1 = Employee("Zara","asdf")
emp2 = Jijia("Hou","123")
emp1.getName()
print hasattr(emp1,'employee_name')
print Employee.__dict__
print Employee.__module__
emp2.total()
emp2.getPos()
emp2.getName()
