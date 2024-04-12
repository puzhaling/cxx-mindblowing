import random

# Списки для генерации осмысленных слов
names = ["James", "John", "Robert", "Michael", "William", "David", "Richard", "Joseph", "Charles", "Thomas"]
surnames = ["Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor"]
car_brands_and_models = {
"Toyota": ["Camry", "Corolla", "Rav4", "Prius", "Highlander"],
"Honda": ["Accord", "Civic", "CR-V", "Pilot", "Odyssey"],
"Ford": ["Fusion", "Focus", "Escape", "Explorer", "Mustang"],
"Chevrolet": ["Impala", "Camaro", "Malibu", "Cruze", "Equinox"],
"Nissan": ["Altima", "Sentra", "Maxima", "Rogue", "Murano"],
# Дополните список другими марками и моделями по вашему выбору
}

def generate_car_brand_and_model():
	brand, models = random.choice(list(car_brands_and_models.items()))
	model = random.choice(models)
	# Используем метод capitalize для обеспечения правильного формата
	return brand.capitalize() + model.capitalize()

def generate_car_number():
	# Генерация автомобильного номера
	return random.choice("ABCDEFGHIJKLMNOPQRSTUVWXYZ") + \
		''.join(random.choice("0123456789") for _ in range(3)) + \
		''.join(random.choice("ABCDEFGHIJKLMNOPQRSTUVWXYZ") for _ in range(2))

def generate_unique_numbers(n):
	# Генерация списка уникальных чисел
	return random.sample(range(1, 10*n), n)

def create_file(filename, num_lines=1000000):
	unique_numbers = generate_unique_numbers(num_lines)
	with open(filename, 'w', encoding='utf-8') as file:
		for i in range(num_lines):
			name = random.choice(names)
			surname = random.choice(surnames)
			car_number = generate_car_number()
			car_brand_and_model = generate_car_brand_and_model()
			unique_number = unique_numbers[i]
			file.write(f"{name} {surname} {car_number} {car_brand_and_model} {unique_number}\n")

if __name__ == "__main__":
	create_file("million_lines_file.txt")
