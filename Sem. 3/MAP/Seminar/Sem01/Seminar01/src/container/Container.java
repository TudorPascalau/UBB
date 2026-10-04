package container;

import task.Task;

public interface Container {
    Task remove();
    void add(Task task);
    int size();
    Task get(int index);
}
