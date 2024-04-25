
#include <iostream>
#include <vector>
#include <string_view>

class IObserver {
public:
    virtual void handleEvent() = 0;
};

class IObservable {
public:
    virtual void addObserver(IObserver* obs) = 0;
    virtual void removeObserver(IObserver* obs) = 0;
    virtual void notify(IObserver* obs) = 0;
    virtual void notifyAll() = 0;

    virtual ~IObservable() {}
};

class EmailUser : public IObserver {
public:
    EmailUser(IObservable* emailCampaign) :
        m_emailCampaign{ emailCampaign }
    {}

    void handleEvent() {
        std::cout << "new incoming message\n";
    }

private:
    IObservable* m_emailCampaign;
};

class EmailCampaign : public IObservable {
public:
    EmailCampaign(std::string_view text) : 
        m_text{ text } 
    {} 
    
    void changeText(std::string_view text) {
        m_text = text;
        notifyAll();
    } 
    void addObserver(IObserver* obs) {
        m_observers.push_back(obs);
    }
    void removeObserver(IObserver* obs) {
        auto it = std::find(m_observers.begin(), m_observers.end(), obs);
        if (it != m_observers.end())
            m_observers.erase(it);
    }
    void notify(IObserver* obs) {
        obs->handleEvent(); 
    }
    void notifyAll() {
        for (auto obs : m_observers)
           obs->handleEvent(); 
    }

private:
    std::vector<IObserver*> m_observers;
    std::string m_text;
};

int main() {
    EmailCampaign* christmasSale = new EmailCampaign("hurry up and don't lose you chance!");
    EmailUser* Manny_Calavera = new EmailUser(christmasSale); 
    EmailUser* Glottis = new EmailUser(christmasSale);
    EmailUser* Olivia_Ofrenda = new EmailUser(christmasSale);

    christmasSale->addObserver(Manny_Calavera);
    christmasSale->addObserver(Glottis);
    christmasSale->addObserver(Olivia_Ofrenda);
   
    //christmasSale->notify(Manny_Calavera);
    christmasSale->notifyAll();
    christmasSale->changeText("discounts are over. see you next year!");
}
