#pragma once
#include <functional>
#include <exception>

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *prev;
};

template <typename T>
class dLinkList
{
public:
    dLinkList() : m_Start(nullptr), m_End(nullptr), m_Size(0) {}
    ~dLinkList();
    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    void display() const;
    void insert(const int _position,const T& value);
    void remove(const int _position);
    size_t size() const {return m_Size;}
    // Node<T> *begin() const { return m_Start; }
    // Node<T> *end() const { return m_End; }

    std::function<Node<T> *()> getIterator(bool reverse = false);
    friend class Display;

private:
    void handleError(const std::string& errorMessage)
    {
        throw std::runtime_error("[ERROR]: " + errorMessage + '\n');
    }
    Node<T> *m_Start, *m_End;
    int m_Size;
};

class Display
{
public:
    template <typename T>
    static void print(const dLinkList<T> &object, std::function<Node<T> *()> iteratorfunction)
    {
        Node<T> *temp;
        std::cout << "List: ";
        while ((temp = iteratorfunction()) != nullptr)
        std::cout << temp->data << " ";
        std::cout << std::endl;
    }
};

template <typename T>
inline dLinkList<T>::~dLinkList()
{
    Node<T>* current = m_Start;
    Node<T>* temp;
    while ( current != nullptr )
    {
        temp = current;
        current = current->next;
        delete temp;
    }
}

template <typename T>
void dLinkList<T>::push_back(const T &value)
{
    Node<T> *temp = new Node<T>{};
    
    temp->data = value;
    
    if (!m_Start)
    m_Start = temp;
    if (!m_End)
    m_End = temp;
    else
    {
        m_End->next = temp;
        temp->prev = m_End;
        m_End = temp;
    }
    m_Size++;
}

template <typename T>
inline void dLinkList<T>::push_front(const T& value)
{
    Node<T> *temp = new Node<T>{};
    
    temp->data = value;
    temp->next = m_Start;
    
    if (!m_Start) // check this because if the first element can't set nullptr previous value to something
    m_Start = temp;
    else 
    m_Start->prev = temp;
    
    m_Start = temp;
    
    if (!m_End) 
        m_End = temp;
    
    m_Size++;
}

template <typename T>
inline void dLinkList<T>::pop_back()
{
    Node<T>* n = m_End;
    m_End = m_End->prev;
    m_End->next = nullptr;
    delete n;
    m_Size--;
}

template <typename T>
inline void dLinkList<T>::pop_front()
{
    Node<T>* n = m_Start;
    m_Start = m_Start->next;
    m_Start->prev = nullptr;
    delete n;
    m_Size--;
}

template <typename T>
void dLinkList<T>::display() const
{
    Node<T> *ptr = m_Start;
    std::cout << "List: ";
    while (ptr)
    {
        std::cout << ptr->data << " ";
        ptr = ptr->next;
    }
    std::cout << "\n";
}

template <typename T>
inline void dLinkList<T>::insert(const int _position,const T& value)
{
    bool isFound = false;
    Node<T>* temp = m_Start;
    int count = 0;
    for (temp = m_Start; temp != nullptr; temp = temp->next)
    {
        if (count == _position)
        {
            isFound = true;
            break;
        }
        count++;
        
    }
    if (isFound)
    {
        Node<T>* newNode = new Node<T>{};
        newNode->data = value; 
        newNode->prev = temp->prev;
        temp->prev->next = newNode;
        temp->prev = newNode;
        newNode->next = temp;
        m_Size++;
    }
    else
    {
        this->handleError("Invaild position of insert!!");
    }
}

template <typename T>
inline void dLinkList<T>::remove(const int _position)
{
    bool isFound = false;
    Node<T>* temp = m_Start;
    int count = 0;
    for (temp = m_Start; temp != nullptr; temp = temp->next)
    {
        if (count == _position)
        {
            isFound = true;
            break;
        }
        count++;
        
    }
    if (isFound)
    {
        Node<T>* node = temp;
        node->prev->next = temp->next;
        node->next->prev = node->prev;
        // temp->prev = node;
        // node->next = temp;
        delete node;
        m_Size--;
    }
    else
    {
        this->handleError("Invaild position to remove!!");
    }
}

template <typename T>
inline std::function<Node<T> *()> dLinkList<T>::getIterator(bool reverse)
{
    Node<T> *current = reverse ? m_Start : m_End;
    return [current, reverse]() mutable -> Node<T> *
    {
        if (!current)
            return nullptr;
        Node<T> *temp = current;
        current = reverse ? current->next : current->prev;
        return temp;
    };
}


