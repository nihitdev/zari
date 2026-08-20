#include "zari/task.hpp"
namespace zari {
struct TaskQueue::Job {
  std::string label, error;
  std::atomic<int> progress{0};
  std::atomic_bool cancel{false}, finished{false};
  std::thread thread;
};
TaskQueue::TaskQueue() = default;
TaskQueue::~TaskQueue() {
  cancel_all();
  std::lock_guard lock(mutex_);
  for (auto& job : jobs_) if (job->thread.joinable()) job->thread.join();
}
void TaskQueue::start(std::string label, std::function<void(std::atomic<int>&,std::atomic_bool&,std::string&)> fn) {
  auto job=std::make_unique<Job>(); job->label=std::move(label); auto* ptr=job.get();
  ptr->thread=std::thread([ptr,fn=std::move(fn)] { fn(ptr->progress,ptr->cancel,ptr->error); ptr->finished=true; });
  std::lock_guard lock(mutex_); jobs_.push_back(std::move(job));
}
std::vector<TaskSnapshot> TaskQueue::snapshots() const { std::lock_guard lock(mutex_); std::vector<TaskSnapshot> out; for(auto& j:jobs_)out.push_back({j->label,j->error,j->progress,j->finished}); return out; }
bool TaskQueue::active() const { std::lock_guard lock(mutex_); for(auto& j:jobs_)if(!j->finished)return true; return false; }
void TaskQueue::cancel_all() { std::lock_guard lock(mutex_); for(auto& j:jobs_)j->cancel=true; }
}
