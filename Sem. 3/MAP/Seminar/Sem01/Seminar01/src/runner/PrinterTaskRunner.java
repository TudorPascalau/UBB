package runner;

public class PrinterTaskRunner extends AbstractTaskRunner {

    public PrinterTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }

    @Override
    public void executeOneTask() {
        super.executeOneTask();
        System.out.println("Task executed at " + java.time.LocalDateTime.now());
    }
}
