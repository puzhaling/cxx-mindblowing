import random
import string

def generate_license_plate():
	return "{}{}{}{}{}".format(random.choice(string.ascii_uppercase),
							   random.randint(0, 9), random.randint(0, 9), random.randint(0, 9),
							   random.choice(string.ascii_uppercase) + random.choice(string.ascii_uppercase))

def generate_car_model():
	brands = ["FordMustang", "ChevroletCamaro", "ToyotaCorolla", "HondaCivic", "BMWX5",
			  "MercedesBenz", "AudiA4", "VolkswagenJetta", "TeslaModelS", "JeepWrangler"]
	return random.choice(brands)

def generate_name():
	first_names = ["John", "Alice", "David", "Emily", "Michael", "Jessica", "Christopher", "Sarah", "Matthew", "Jennifer"]
	last_names = ["Smith", "Johnson", "Brown", "Davis", "Wilson", "Taylor", "Martinez", "Anderson", "Thomas", "Garcia"]
	return "{} {}".format(random.choice(first_names), random.choice(last_names))

def generate_file(file_name, num_lines=1000000):
	with open(file_name, 'w') as file:
		for _ in range(num_lines):
			line = "{} {} {}\n".format(generate_name(), generate_license_plate(), generate_car_model())
			file.write(line)

# Generate the file
generate_file("million_lines.txt")