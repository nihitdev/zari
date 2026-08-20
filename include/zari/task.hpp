#pragma once
#include <atomic>
#include <functional>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
namespace zari {
struct TaskSnapshot { std::string label, error; int progress=0; bool finished=false; };
class TaskQueue { public: TaskQueue(); ~TaskQueue(); TaskQueue(const TaskQueue&)=delete; TaskQueue& operator=(const TaskQueue&)=delete; void start(std::string, std::function<void(std::atomic<int>&,std::atomic_bool&,std::string&)>); std::vector<TaskSnapshot> snapshots() const; bool active() const; void cancel_all(); private: struct Job; mutable std::mutex mutex_; std::vector<std::unique_ptr<Job>> jobs_; };
}
