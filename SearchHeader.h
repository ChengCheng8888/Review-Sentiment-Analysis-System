#ifndef HEADER_H
#define HEADER_H

#include <string>

struct Email {
    std::string from;
    std::string to;
    std::string date;
    std::string time;
    std::string subject;
    std::string content;
};

class Queue {
public:  // 将 Node 结构移到 public 访问权限
    struct Node {
        Email email;
        Node* next;
    };

private:
    Node* front;
    Node* rear;

    // Helper function to copy nodes from another queue
    void copyFrom(const Queue& other);

public:
    Queue();
    ~Queue();
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);

    bool empty();
    void push(const Email& email);
    Email pop();
    int size();
    Node* getFront();
};

void readEmailsFromCSV(const std::string& filename, Queue& emailQueue);
void displayEmail(const Email& email);
void displayAllEmails(Queue& emailQueue);
void searchEmail(Queue& emailQueue, const std::string& keyword);
void searchByMonth(Queue& emailQueue, const std::string& month);

#endif  // HEADER_H
