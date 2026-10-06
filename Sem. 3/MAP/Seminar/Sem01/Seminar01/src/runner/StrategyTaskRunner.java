package runner;

import container.Container;
import factory.Strategy;
import factory.TaskContainerFactory;
import task.Task;

public class StrategyTaskRunner implements TaskRunner {

    private Container container;
    public StrategyTaskRunner(Strategy strategy) {
        container = TaskContainerFactory.getInstance().createContainer(strategy);
    }

    @Override
    public void executeOneTask() {
        container.remove().execute();
    }

    @Override
    public void executeAllTasks() {
        while (!container.isEmpty()) {
            container.remove().execute();
        }
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
