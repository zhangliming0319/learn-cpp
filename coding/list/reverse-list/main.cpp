#include <iostream>
struct Node {
  int   value;
  Node* next;
};
class Solution {
 private:
  /* data */
 public:
  Solution(/* args */);
  ~Solution();
  Node* ReverseList(Node* head) {
    if (head == nullptr) {
      return head;
    }

    Node* prev = nullptr;
    Node* next = nullptr;
    while (head != nullptr) {
      next       = head->next;
      head->next = prev;
      prev       = head;
      head       = next;
    }
    return prev;
  }
};

Solution::Solution(/* args */) {}

Solution::~Solution() {}
int main(int argc, char** argv) {
  Solution solution;
  Node     end{ 4, nullptr };
  Node     node2{ 2, &end };
  Node     node3{ 3, &node2 };
  Node     head{ 1, &node3 };
  std::cout << "solution:" << solution.ReverseList(&head)->value << std::endl;
}