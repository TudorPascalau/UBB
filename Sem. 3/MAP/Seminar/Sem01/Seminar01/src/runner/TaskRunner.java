package runner;

import task.Task;

public interface TaskRunner {
    void executeOneTask();
    void executeAllTasks();
    void addTask(Task t);
    boolean hasTask();
}
