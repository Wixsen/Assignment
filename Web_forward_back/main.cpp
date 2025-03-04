#include <iostream>
#include <string>
#include "dList.hpp"

class Browser
{
public:
    enum ERROR
    {
        FAILD_FORWARD = 1,
        FAILED_BACKWARD = 2
    };
    Browser(const std::string &homepage);
    Browser() : m_BackwardCount(0){}
    void addSite(const std::string& homepage);
    void forward();
    void backward();
    std::string now();
    void printUrls();

private:
    int m_BackwardCount;
    dLinkList<std::string> m_Websites;
};
Browser::Browser(const std::string &homepage)
    : m_BackwardCount(0)
{
    m_Websites.push_back(homepage);
}

void Browser::addSite(const std::string& url)
{
    while (m_BackwardCount > 0)
    {
        m_Websites.pop_back();
        m_BackwardCount--;
    }

    m_Websites.push_back(url);
}

void Browser::forward()
{
    if (m_BackwardCount > 0)
        m_BackwardCount--;
    else
        throw ERROR::FAILD_FORWARD;
    // m_Websites.insert(m_Websites.size() - 1 - m_BackwardCount);
}

void Browser::backward()
{
    if (m_BackwardCount  < m_Websites.size() - 1)
        m_BackwardCount++;
    else
        throw ERROR::FAILED_BACKWARD;
}

std::string Browser::now() 
{
    int index = m_BackwardCount;
    std::function<Node<std::string>* ()> reverse_iter = m_Websites.getIterator(false);

    while (index--)
    {
        reverse_iter();
    }
    return reverse_iter()->data;
}

void Browser::printUrls()
{
    std::function<Node<std::string> *()> _forward = m_Websites.getIterator(true);
    int _upto = m_Websites.size() - m_BackwardCount - 1;
    int _count = 0;
    std::cout << "Website Routing: \n";
    for (Node<std::string> *_site = _forward(); _site != nullptr; _site = _forward())
    {
        if (_count >= _upto)
        {
            std::cout << _site->data << std::endl;
            break;
        }
        else
        {
            std::cout << _site->data << " - >";
        }
        _count++;
    }
}



int main()
{
    const char *introScreen{
        "-------------------[Mika Browser]----------------\n"
        "| 1. Add Link                                   |\n"
        "| 2. Forward                                    |\n"
        "| 3. Backward                                   |\n"
        "| 4. Print                                      |\n"
        "|                                               |\n"
        "-------------------------------------------------\n"};
    enum OPTIONS
    {
        NONE = 0,
        ADD,
        FORWARD,
        BACKWARD,
        PRINT
    };
    int option = OPTIONS::NONE;
    
    const unsigned int MAX_OPTION = 4;
    std::string urlStr;
    Browser mika;

    do
    {
        // #ifdef _WIN32
        //     system("cls");
        // #else 
        //     system("clear");
        // #endif
        printf("%s\n", introScreen);
        std::cin >> option;
        
        try
        {
            switch (option)
            {
            case OPTIONS::ADD:
                std::cout << "Open link: ";
                std::cin >> urlStr;
                mika.addSite(urlStr);
                break;
            case OPTIONS::FORWARD:
                mika.forward();
                std::cout<<"The Website is forward: "<<mika.now() <<std::endl;
                std::cin.get();
            break;
            case OPTIONS::BACKWARD:
                mika.backward();
                std::cout<<"The Website is backward: "<<mika.now() <<std::endl;
                std::cin.get();
                break;
            case OPTIONS::PRINT:
                mika.printUrls();
                std::cin.get();
                break;
            };
        }
        catch (const Browser::ERROR &e)
        {
            std::cout << "[ERROR]: ";
            switch(e)
            {
                case Browser::ERROR::FAILD_FORWARD:
                    std::cout << "Unable to perform forward operation !!\n";
                    break;
                case Browser::ERROR::FAILED_BACKWARD:
                    std::cout << "Unable to perform backward operation!!\n";
                    break;
                default:
                    std::cout <<"Error!!\n";

            };
            std::cin.get();
        }
        std::cin.get();

    } while (option > 0 && option <= MAX_OPTION);

    return 0;
}
