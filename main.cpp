#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;

 class Node 
{   public:
    Node *prev;
    Node *next;
    string current;
    //auto timestamp; commented because auto cannot be used to declare class members 
    system_clock::time_point timestamp;
    Node()
    {  
        current = "";
        next = nullptr;
        prev = nullptr;
    }
    Node(string url, system_clock::time_point timestamp1)
    {   timestamp = timestamp1;
        current = url;
        next = nullptr;
        prev = nullptr;
    }
    Node(string url, Node *ptr1, Node *ptr2)
    {
        current = url;
        next = ptr1;
        prev = ptr2;
    }

};
class Browser 
{   Node *currentPage;
    Node *start;
    Browser(string &homepage)
    {   
        currentPage = new Node(homepage,system_clock::now());
        start = currentPage; // when a new browser object is created meaning new session so when it is created we assign start to homepage
    }
    string visit(string url)
    {   
        if(start==nullptr)
        {
            start = new Node(url,system_clock::now());
            currentPage = start;
            start->prev = nullptr;
        } 
        else 
        {
            Node *new_node;
            new_node = new Node(url,system_clock::now());
            currentPage->next = new_node; 
            new_node->prev = currentPage;
          //new_node->next = nullptr; (commented because when i initialized new node with only url the next pointer was intialized to nullptr due to constructor i built)
            currentPage = new_node; 
        }
        return currentPage->current;
    }
    string back(int steps)
    {
        for(int i=0;i<steps;i++)
        {
            if(currentPage->prev == nullptr)
                {   
                    return currentPage->current;
                    break;
                }
            else
                currentPage = currentPage->prev;
        }
        return currentPage->current;
    }
    string forward(int steps)
    {
        for(int i=0;i<steps;i++)
        {
            if(currentPage->next == nullptr)
               {
                return currentPage->current;
                 break;
               }
            else
                currentPage = currentPage->next;
        }
        
        return currentPage->current;
    }
    //reading a session into a file 
    void readSessionToFile(Node *head,const string& filename) //create and pass a binary file for storing binary representation of the object
    {   ofstream file(filename);
        if(file.is_open())
        {
            while(head->next!=nullptr)
            {
                file.write(reinterpret_cast<const char*>(&head), sizeof(Node));

            }

        }
        file.close(); 
    } 
    //reading session out from a file 
    void readSessionFromFile(const string& filename)
    {
        Node head;
        ifstream file(filename);
        if(file.is_open())
        {
            while(!file.eof())
            {
                file.read(reinterpret_cast<char*>(&head), sizeof(Node));

            }
        }
        file.close();
    } 
};