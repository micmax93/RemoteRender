#ifndef UTILITIES_HPP_INCLUDED
#define UTILITIES_HPP_INCLUDED

class Semaphore
{
    int count;
    boost::mutex outer_mx;
    boost::mutex  inner_mx;

    public:

    Semaphore()
    {
        count=0;
        inner_mx.lock();
    }

    void get()
    {
        outer_mx.lock();
        if(count>0)
        {
            count--;

            if(count>0)
                {inner_mx.unlock();}

            outer_mx.unlock();
        }
        else
        {
            outer_mx.unlock();
            inner_mx.lock();
            get();
        }
    }

    void add(int n=1)
    {
        outer_mx.lock();
        count+=n;
        inner_mx.unlock();
        outer_mx.unlock();
    }
};

template <class X>
class TaskQueue
{
    queue <X> tasks;
    boost::mutex mx;

    public:

    void add(X task)
    {
        mx.lock();
        tasks.push(task);
        mx.unlock();
    }

    X get()
    {
        mx.lock();
        X task=tasks.pop();
        mx.unlock();
        return task;
    }

    int size()
    {
        mx.lock();
        int n=tasks.size();
        mx.unlock();
        return n;
    }
}

template <class X>
class ResultQueue
{
    queue <X> tasks;
    boost::mutex mx;
    Semaphore sem;

    public:

    void add(X task)
    {
        mx.lock();
        tasks.push(task);
        mx.unlock();
        sem.add();
    }

    X get()
    {
        sem.get();
        mx.lock();
        X task=tasks.pop();
        mx.unlock();
        return task;
    }
}

template <class X>
class RoundTasksQueue
{
    boost::mutex edit;
    vector< TaskQueue <X>* > tasksPointers;
    int curr;
    Semaphore tasksCount;

    public:

    RoundTasksQueue()
    {
        curr=0;
    }

    void newQueue(TaskQueue <X> *tasksPtr,int size)
    {
        edit.lock();
        tasksPointers.push_back(tasksPtr);
        edit.unlock();
        tasksCount.add(size);
    }

    X getTask()
    {
        tasksCount.get();
        edit.lock();
        curr=(curr+1)%(tasksPointers.size());
        X task=tasksPointers[curr]->get();
        edit.unlock();
        return task;
    }

    void addPriorityTask(X task)
    {

    }
};

template <class X>
class TaskContainer
{
	public:
	int owner;
	string hash;
	
	ResultQueue *models;
	X task;
};


#endif // UTILITIES_HPP_INCLUDED
