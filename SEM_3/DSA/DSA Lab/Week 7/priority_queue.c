// The task scheduler must handle the following complexities:
// Task Preemption: A lower priority task can be interrupted and paused if a higher priority task arrives.
// Dynamic Priority Changes: The priority of certain tasks can dynamically change based on system requirements.
// Task Dependencies: Some tasks can only be executed after a specific set of tasks are completed.
// Your task is to simulate this multi-core task scheduler using a priority queue. 
// Tasks must be managed efficiently to minimize idle time across cores while respecting all constraints.
// The following operations must be performed by the scheduler:
// Task Insertion: Add a new task to the scheduler, specifying the task ID, priority, and execution time.
// Execute Task: Execute the highest priority task available. 
// The task should run on the available core with the lowest ID. 
// If multiple cores are available, the one with the lowest ID should be selected. Print the core ID and the TID of the executed task.
// Change Task Priority: If a task's priority changes dynamically due to system requirements, the new priority must be updated in the scheduler.
// Task Dependency: Some tasks can only be executed after certain other tasks are completed. 
// If a dependent task is added to the queue, it should not be executed until its dependency is fulfilled.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Task {
    int tid;
    int priority;
    int executionTime;
    struct Task* next;
} Task;

typedef struct Core {
    int coreId;
    Task* currentTask;
    bool isFree;
} Core;

typedef struct TaskQueue {
    Task* head;
} TaskQueue;

// Function to create a new task queue
TaskQueue* createTaskQueue() {
    TaskQueue* q = (TaskQueue*)malloc(sizeof(TaskQueue));
    q->head = NULL;
    return q;
}

// Function to create a new task
Task* createTask(int tid, int priority, int executionTime) {
    Task* temp = (Task*)malloc(sizeof(Task));
    temp->tid = tid;
    temp->priority = priority;
    temp->executionTime = executionTime;
    temp->next = NULL; 
    return temp;
}

// Function to create a new core
Core* createCore(int coreId) {
    Core* temp = (Core*)malloc(sizeof(Core));
    temp->coreId = coreId;
    temp->currentTask = NULL;
    temp->isFree = true; 
    return temp;
}

// Function to insert a task into the priority queue based on priority
void insertTask(TaskQueue* queue, Task* newTask) {
   if (queue->head == NULL || queue->head->priority < newTask->priority) {
        newTask->next = queue->head; 
        queue->head = newTask;
        return;
   }
   
   Task* p = queue->head;
   while (p->next != NULL && p->next->priority >= newTask->priority) {
       p = p->next; 
   }
   newTask->next = p->next; 
   p->next = newTask;
}

// Function to execute the highest priority task
Task* executeTask(TaskQueue* queue) {
    if (queue->head == NULL)
        return NULL; 

    Task* executing = queue->head; 
    queue->head = queue->head->next;
    return executing; 
}

// Function to update task priority
void changeTaskPriority(TaskQueue* queue, int tid, int newPriority) {
    Task *prev = NULL, *current = queue->head;

    while (current != NULL && current->tid != tid) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    if (prev != NULL) {
        prev->next = current->next; 
    } else {
        queue->head = current->next; 
    }

    current->priority = newPriority;

    insertTask(queue, current); 
}

// Function to simulate task scheduling
void simulateTaskScheduler(TaskQueue* queue, Core** cores, int numCores) {
        for (int i = 0; i < numCores; i++) {
            if (cores[i]->isFree) { 
                Task* nextTask = executeTask(queue); 
                
                if (nextTask != NULL) {
                    printf("Core %d: Executing Task %d\n", 
                           cores[i]->coreId, 
                           nextTask->tid);
                    
                    cores[i]->currentTask = nextTask;
                    cores[i]->isFree = false; 
                    
                    }
                }
            }
}

int main() {
    int numCores;

    scanf("%d", &numCores);
    
    Core** cores = (Core**)malloc(numCores * sizeof(Core*));
    
    for (int i = 0; i < numCores; i++) {
        cores[i] = createCore(i + 1);
    }
    
    TaskQueue* queue = createTaskQueue();
    
    int numTasks;

    scanf("%d", &numTasks);
    
    for (int i = 0; i < numTasks; i++) {
        int tid, priority, executionTime;
        scanf("%d %d %d", &tid, &priority, &executionTime);
        Task* newTask = createTask(tid, priority, executionTime);
        insertTask(queue, newTask);
    }
    
    simulateTaskScheduler(queue, cores, numCores);
    
    free(queue);  // Freeing memory for the task queue
    
    for (int i = 0; i < numCores; i++) {
        free(cores[i]);  // Freeing memory for each core
    }
    
    free(cores);  // Freeing memory for core array
    
    return 0;
}