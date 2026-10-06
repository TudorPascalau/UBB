package container;

import task.Task;

import java.util.Objects;

public class QueueContainer implements Container {
    private Task[] tasks;
    private int size;

    public QueueContainer() {
        this(100);
    }

    public QueueContainer(int capacity) {
        if (capacity < 0) {
            throw new IllegalArgumentException("Capacity must not be negative");
        }
        this.tasks = new Task[capacity];
        this.size = 0;
    }

    @Override
    public Task remove() {
        if (isEmpty()) {
            return null;
        }

        Task task = tasks[0];
        System.arraycopy(tasks, 1, tasks, 0, size - 1);
        tasks[--size] = null;
        return task;
    }

    @Override
    public void add(Task task) {
        Objects.requireNonNull(task, "Task must not be null");

        if (size == tasks.length) {
            Task[] newTasks = new Task[Math.max(1, 2 * tasks.length)];
            System.arraycopy(tasks, 0, newTasks, 0, size);
            tasks = newTasks;
        }

        tasks[size++] = task;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public Task get(int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Invalid index: " + index);
        }
        return tasks[index];
    }
}
