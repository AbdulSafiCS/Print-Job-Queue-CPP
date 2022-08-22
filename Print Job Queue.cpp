#include <iostream>
#include <string>
using namespace std;

class printJob {
  string name;
  string status;
  int trackingNumber;
//getters
  public:
    string getName() const {
    return name;
}
    string getStatus() const {
    return status;
}

    int getTrackingNumber(){
    return trackingNumber;
}
//setters
    void setTrackingNumber(int track) {
      trackingNumber = track;
    }
    void setName(string name) {
      this->name = name;
    }
    void setStatus(string status) {
      this->status = status;
    }
    
};
class Node {
  private: 
    printJob data;
    Node* next;
  public:
    Node(printJob data){
    this->data = data;
    next = nullptr;
  }
  //setters
  void setData(printJob data) {
    this->data = data;
  }
  void setNext(Node* n) {
    this->next = n;
  }
  //getters
  printJob getData(){
    return data;
  }
  Node* getNext(){
    return next;
  }
};
class Queue {
  private:
    Node* head;
    Node* tail;
    int queueSize;
    int numDenied;
    int numAccepted;
    int numExecuted;
    int numRequestPlaced;
  public:
    Queue() {
      head = nullptr;
      tail = nullptr;
      queueSize = 0;
      numDenied = 0;
      numAccepted = 0;
      numExecuted = 0;
      numRequestPlaced = 0;
    }
    //setters
    void setQueueSize(int size){
      queueSize = size;
    }
    void setNumDenied(int denied) {
      numDenied = denied;
    }
    void setNumAccepted(int accepted) {
      numAccepted = accepted;
    }
    void setNumExecuted(int executed) {
      numExecuted = executed;
    }
    void setNumRequestPlaced(int placed) {
      numRequestPlaced = placed;
    }
    //getters
    int getNumDenied() const {
      return numDenied;
    }
    int getNumAccepted() const {
      return numAccepted;
    }
    int getNumExecuted() const {
      return numExecuted;
    }
    int getNumRequestPlaced() const {
      return numRequestPlaced;
    }
    int  getSize() const {
      return queueSize;
    }
  
    bool isEmpty();
    void Enqueue(printJob job);
    printJob Dequeue();
    printJob peek();
  


};

  bool isValid(string name);
  void getData(Queue& q);
  enum choice{Enter = 1, Execute, Statuses, Exit};

int main() {
  Queue q;
  
  int choices;
  while(choices != Exit) {

    cout << "\n\nMenu: \n";
    cout << "1. Enter a Print Job.\n"
            "2. Execute a Print Job\n"
            "3. Get Statuses of Print Jobs\n"
            "4. Exit Program\n";
   
    cin >> choices;

  switch(choices) {
    case Enter :
    getData(q);
    break;

    case Execute : 
    cout << q.Dequeue().getName() << " has been executed. there are currently " << q.getSize() << " print jobs in the Queue\n"; 
    break;

    case Statuses :
    cout << "1. Jobs Accepted: " << q.getNumAccepted() << endl;
    cout << "2. Jobs Denied: " << q.getNumDenied() << endl;
    cout << "3. Jobs in the Queue: " << q.getSize() << endl;
    cout << "4. Jobs Executed: " << q.getNumExecuted() << endl;
    cout << "5. Jobs Requests Placed: " << q.getNumRequestPlaced() << endl;
    break;

    case Exit :
    cout << "Program is exiting...";
    break;

    default :
       cout << "You entered an invalid choice. Try again." << endl;
       cin.clear();
       cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  /*
  Menu: 
1. Enter a Print Job.
2. Execute a Print Job
3. Get Statuses of Print Jobs
4. Exit Program
1
Job name please: Abdul
Your Job Abdul was Accepted at position 0 with tracking number 1001

Menu: 
1. Enter a Print Job.
2. Execute a Print Job
3. Get Statuses of Print Jobs
4. Exit Program
2
Abdul has been executed. there are currently 0 print jobs in the Queue


Menu: 
1. Enter a Print Job.
2. Execute a Print Job
3. Get Statuses of Print Jobs
4. Exit Program
3
1. Jobs Accepted: 1
2. Jobs Denied: 0
3. Jobs in the Queue: 0
4. Jobs Executed: 1
5. Jobs Requests Placed: 1


Menu: 
1. Enter a Print Job.
2. Execute a Print Job
3. Get Statuses of Print Jobs
4. Exit Program
4
Program is exiting... 
  */
} 
//determines wether the first char of job string is Alphabetical.
//Precondition: string name is initialized.
//returns true or false based on the first letter of the name string.
bool isValid(string name){
  bool isValid = true;
  for(int i = 0; i < name.size(); i++) {
    if(!isalpha(name[0])) {
      isValid = false;
    }
  }
  return isValid;
}
//get a string from the user and validates it. if valid it will enqueue and incremeent numAccepted else increments numDenied and NumRequestPlaced.
//Precondition: Queue is instantiated and passed by reference
//Postcondition: Gets a job from user, validates it, and Enqueues it based on the validation. adjust stats for the job.
void getData(Queue& q){
  string userJobName;
  cout << "Job name please: ";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, userJobName);
  q.setNumRequestPlaced(q.getNumRequestPlaced() + 1);
  printJob job1;
  job1.setTrackingNumber(q.getNumRequestPlaced() + 1000);
  
  job1.setName(userJobName);
  if(isValid(userJobName)) {
    job1.setStatus("Accepted");
    q.setNumAccepted(q.getNumAccepted() + 1);
  }
  else {
    job1.setStatus("DENIED");
    q.setNumDenied(q.getNumDenied() + 1);
  }

  if(job1.getStatus() == "Accepted") {
  cout<< "Your Job " << job1.getName() << " was " << job1.getStatus() << " at position " << q.getSize() << " with tracking number " << job1.getTrackingNumber();
  q.Enqueue(job1);
  }
  else {
    cout << "Your Job " << job1.getName() << " was " << job1.getStatus() << " because of invalid name\n";
  }
}

//determines wether the queue is empty.
//precondition: queue has been initialized.
//postcondition: function value = (queue is empty)
bool Queue::isEmpty() {
  return head == nullptr;
}
//adds a new job at the end of the queue
//precondition: queue has been initialized
//postcondition: item is added at the end of the queue
void Queue::Enqueue(printJob job) {
  Node* n = new Node(job);
  if(head == nullptr) {
    head = n;
    tail = n;
  }
  else {
    tail->setNext(n);
    tail = n;
  }
  queueSize++;
}
//removes item from the front of the queue
//precondition: queue has been initialized and not empty.
//postcondition: item is removed from the front of the queue.
printJob Queue::Dequeue() {
  Node* temp = head;
  if(isEmpty()) {
    cout << "Queue is empty\n";
    exit(EXIT_FAILURE);
  }
  else{
  head = head->getNext();
  queueSize--;
  numExecuted++;
  } 
  return temp->getData();
}
//returns a copy of an item from the front of the queue.
//precondition: queue has been initialized and not empty.
//postcondition: a copy of the item at the front of the queue is returned.
printJob Queue::peek() {
  if(isEmpty()){
   cout << "Queue is empty\n";
   exit(EXIT_FAILURE);
  }
  return head->getData();
}
