package task;

import sorter.AbstractSorter;

import java.util.Arrays;
import java.util.Objects;

public class SortingTask extends Task {
    private final int[] numbers;
    private final AbstractSorter sorter;

    public SortingTask(String taskId, String description, int[] numbers, AbstractSorter sorter) {
        super(taskId, description);
        this.numbers = Objects.requireNonNull(numbers, "Numbers must not be null");
        this.sorter = Objects.requireNonNull(sorter, "Sorter must not be null");
    }

    @Override
    public void execute() {
        sorter.sort(numbers);
        System.out.println(Arrays.toString(numbers));
    }
}
