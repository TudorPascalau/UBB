package container;

import task.Task;

public class StackContainer implements Container {
    private Task[] tasks;
    private int size;

    public StackContainer(int size) {
        this.tasks = new Task[100];
        this.size = 0;
    }

    @Override
    public Task remove() {

    }

    @Override
    public void add(Task task) {
        if(size == Tasks.length) {
            // redimensionare
            Task[] newTasks = new Task[2*size];
            System.arraycopy(Tasks, 0, newTasks, 0, Tasks.length);
            tasks = newTasks;
        }

        T
    }
}
