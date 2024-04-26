//реализовать утилиту для генерации команды компиляции другой программы

#include <string_view>
#include <string>
#include <iostream>
#include <vector>

static constexpr char gCompany[] = "dreamcomp";
static constexpr char gEncryptedMark[] = "Encrypted";
static constexpr char gSign[] = "signsignsign";

class IAttachable {
public:
    virtual std::string& getInfo() = 0;
    virtual void setInfo(std::string& info) = 0;
};

class TextDocument : IAttachable {
public:
    virtual std::string& getInfo() { return m_info; }
    virtual void setInfo(std::string& info) { m_info = info; }

private:
    std::string m_info;
};

class Letter {
public:
    void setSender(std::string_view sender) { m_sender = sender; }
    void setReciever(std::string_view reciever) { m_reciever = reciever; }
    void setSubject(std::string_view subject) { m_subject = subject; }
    void setCopy(std::string_view copy) { m_copy = copy; }
    void setBody(std::string_view body) { m_body = body; }
    void setAttachment(IAttachable* attachment) { m_attachments.push_back(attachment); }
    void setSign(std::string_view sign) { m_sign = sign; }

private:
    std::string m_sender;
    std::string m_reciever;
    std::string m_subject;
    std::string m_copy;
    std::string m_body;
    std::vector<IAttachable*> m_attachments;
    std::string m_sign;
};

class ILetterBuilder {
public:
    virtual void setSender(std::string_view sender) = 0;
    virtual void setReciever(std::string_view reciever) = 0;
    virtual void setSubject(std::string_view subject) = 0;
    virtual void setCopy(std::string_view copy) = 0;
    virtual void setBody(std::string_view body) = 0;
    virtual void setAttachment(IAttachable* attachment) = 0;
    virtual void setSign(std::string_view sign) = 0;
    virtual void createLetter() = 0;
    virtual Letter getLetter() = 0;
};

class SimpleLetterBuilder : public ILetterBuilder {
public:
    // change getters to newly added setters, GETTERS AREN'T NEEDED
    virtual void setSender(std::string_view sender) {
        m_letter.getSender() = sender; 
    }
    virtual void setReciever(std::string_view reciever) {
        m_letter.getReciever() = reciever;
    }
    virtual void setSubject(std::string_view subject) {
        m_letter.getSubject() = subject;  
    }
    virtual void setCopy(std::string_view copy) {
        m_letter.getCopy() = copy;
    }
    virtual void setBody(std::string_view body) {
        m_letter.getBody() = body;
    }
    virtual void setAttachment(IAttachable* attachment) {
        m_letter.getAttachments().push_back(attachment);
    }
    virtual void setSign(std::string_view sign) {
        m_letter.getSign() = sign;
    }
    virtual void createLetter() {
        m_letter = Letter{}; 
        m_letter.getSender() = gCompany; 
    }
    virtual Letter getLetter() {
        return m_letter;
    }

private:
    Letter m_letter;
};

class ProtectedLetterBuilder : public ILetterBuilder {
public:
    virtual void setSender(std::string_view sender) {
        m_letter.getSender() = sender; 
    }
    virtual void setReciever(std::string_view reciever) {
        m_letter.getReciever() = reciever;
    }
    virtual void setSubject(std::string_view subject) {
        m_letter.getSubject() = subject;  
    }
    virtual void setCopy(std::string_view copy) {
        m_letter.getCopy() = copy;
    }
    virtual void setBody(std::string_view body) {
        m_letter.getBody() = body;
    }
    virtual void setAttachment(IAttachable* attachment) {
        m_letter.getAttachments().push_back(attachment);
    }
    virtual void setSign(std::string_view sign) {
        m_letter.getSign() = sign;
    }
    virtual void createLetter() {
        m_letter = Letter{}; 
        m_letter.getSender() = gCompany; 
    }
    virtual Letter getLetter() {
        using str = std::string;

        m_letter.getSender().append(str{" " + str{gSign} + " " + str{gEncryptedMark}});
        m_letter.getReciever().append(str{" " + str{gSign} + " " + str{gEncryptedMark}});
        m_letter.getSubject().append(str{" " + str{gSign} + " " + str{gEncryptedMark}});
        m_letter.getCopy().append(str{" " + str{gSign} + " " + str{gEncryptedMark}});
        m_letter.getBody().append(str{" " + str{gSign} + " " + str{gEncryptedMark}});

        auto& attachments{ m_letter.getAttachments() };
        for (auto* attachment : attachments) {
            attachment->getInfo().append(str{" " + str{gSign} + " " + str{gEncryptedMark}});
        }
        
        m_letter.getSign().append(str{" " + str{gSign} + " " + str{gEncryptedMark}});
        return m_letter;
    }

private:
    Letter m_letter;
};

int main() {
    ILetterBuilder* b = new SimpleLetterBuilder();
    b->createLetter();
    b->setReciever("sdfsdfsf");
    b->setBody("sfdsdfsdfsdfsdfsdfsfsdfsdfsd"); 

    std::cout << b->getLetter().getBody();

    SimpleLetterBuilder builder;
    builder.createLetter();
    Letter letter{ builder.getLetter() }; 
    delete b;
    b = new ProtectedLetterBuilder();
    b->setReciever("pppp");
    b->setBody("qqqqqqqqqqqq");

    std::cout << b->getLetter().getBody();
    delete b;
    return 0;
}
