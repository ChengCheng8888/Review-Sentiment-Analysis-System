#include <iostream>
#include <fstream>
#include <sstream>
#include "SearchHeader.h"

// 构造函数
Queue::Queue() : front(nullptr), rear(nullptr) {}

// 析构函数
Queue::~Queue() {
    while (!empty()) {
        pop();
    }
}

// 深拷贝构造函数
Queue::Queue(const Queue& other) : front(nullptr), rear(nullptr) {
    copyFrom(other);
}

// 深拷贝赋值操作符
Queue& Queue::operator=(const Queue& other) {
    if (this != &other) {
        while (!empty()) {
            pop();
        }
        copyFrom(other);
    }
    return *this;
}

// 复制其他队列中的所有节点
void Queue::copyFrom(const Queue& other) {
    Node* current = other.front;
    while (current != nullptr) {
        push(current->email);
        current = current->next;
    }
}

// 检查队列是否为空
bool Queue::empty() {
    return front == nullptr;
}

// 入队操作
void Queue::push(const Email& email) {
    Node* newNode = new Node{ email, nullptr };
    if (rear) {
        rear->next = newNode;
    }
    rear = newNode;
    if (!front) {
        front = newNode;
    }
}

// 出队操作
Email Queue::pop() {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    Node* temp = front;
    Email email = front->email;
    front = front->next;
    if (!front) {
        rear = nullptr;
    }
    delete temp;
    return email;
}

// 获取队列大小
int Queue::size() {
    int count = 0;
    Node* current = front;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// 获取队列头部节点指针
Queue::Node* Queue::getFront() {
    return front;
}

// 从CSV文件读取邮件数据
void readEmailsFromCSV(const std::string& filename, Queue& emailQueue) {
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);  // 跳过表头

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Email email;
        std::string priority;

        std::getline(ss, email.from, ',');
        std::getline(ss, email.to, ',');
        std::getline(ss, email.date, ',');
        std::getline(ss, email.time, ',');
        std::getline(ss, priority, ',');
        std::getline(ss, email.subject, ',');
        std::getline(ss, email.content, '\n');

        emailQueue.push(email);
    }

    file.close();
}

// 显示单封邮件
void displayEmail(const Email& email) {
    std::cout
        << "\nFrom: " << email.from << "\n"
        << "To: " << email.to << "\n"
        << "Date: " << email.date << "\n"
        << "Time: " << email.time << "\n"
        << "Subject: " << email.subject << "\n"
        << "Content: " << email.content << "\n"
        << "-----------------------------\n";
}

// 显示所有邮件
void displayAllEmails(Queue& emailQueue) {
    Queue tempQueue = emailQueue;
    if (tempQueue.empty()) {
        std::cout << "No emails to display.\n";
        return;
    }

    while (!tempQueue.empty()) {
        Email email = tempQueue.pop();
        displayEmail(email);
    }
}

// 搜索包含关键词的邮件
void searchEmail(Queue& emailQueue, const std::string& keyword) {
    Queue tempQueue = emailQueue;
    bool found = false;

    while (!tempQueue.empty()) {
        Email email = tempQueue.pop();
        if (email.from.find(keyword) != std::string::npos ||
            email.to.find(keyword) != std::string::npos ||
            email.subject.find(keyword) != std::string::npos ||
            email.content.find(keyword) != std::string::npos) {
            displayEmail(email);
            found = true;
        }
    }

    if (!found) {
        std::cout << "No emails found containing the keyword: " << keyword << "\n";
    }
}

// 根据月份搜索邮件
void searchByMonth(Queue& emailQueue, const std::string& month) {
    Queue tempQueue = emailQueue;
    bool found = false;

    while (!tempQueue.empty()) {
        Email email = tempQueue.pop();
        std::istringstream iss(email.date);
        std::string dayOfWeek, monthInDate;
        iss >> dayOfWeek >> monthInDate;

        if (monthInDate == month) {
            displayEmail(email);
            found = true;
        }
    }

    if (!found) {
        std::cout << "No emails found for month: " << month << "\n";
    }
}


