#include <iostream>
#include <memory>
#include <string>

class Prototype {
public:
	virtual ~Prototype() = default;
	virtual std::unique_ptr<Prototype> clone() const = 0;
	virtual void print() const = 0;
};

class ConcretePrototype : public Prototype {
public:
	ConcretePrototype(std::string d) : data(d)
	{
	}

	std::unique_ptr<Prototype> clone() const override {
		return std::make_unique<ConcretePrototype>(*this);
	}
	
	void print() const override {
		std::cout << "ConcretePrototype: " << data 
			<< std::endl;
	}

private:
	std::string data;
};

int main() {
	auto original = std::make_unique<ConcretePrototype>("Original");
	auto copy = original->clone();

	original->print();
	copy->print();

	return 0;
}
