import copy

class Prototype:
	def clone(self):
		return copy.deepcopy(self)

class ConcretePrototype(Prototype):
	def __init__(self, data):
		self.data = data

	def __str__(self):
		return f"ConcretePrototype: {self.data}"

original = ConcretePrototype("Original")
copy = original.clone()

print(original)
print(copy);
