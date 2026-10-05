import container.StackContainer;
import sorter.AbstractSorter;
import sorter.BubbleSort;
import sorter.QuickSort;
import task.MessageTask;
import task.SortingTask;
import task.Task;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.Random;

public class Seminar01Test {
    public static void main(String[] args) {
        testTasks();
        testSorters();
        testStack();
        System.out.println("All Seminar01 tests passed.");
    }

    private static void testTasks() {
        MessageTask first = message("1");
        MessageTask second = message("1");
        check(first.equals(second) && second.equals(first), "Symmetric equality");
        check(first.hashCode() == second.hashCode(), "Equal tasks have equal hash codes");
        check(!first.equals(null) && !first.equals(message("2")), "Different tasks");
        check(!first.equals(new SortingTask("1", "Feedback lab1", new int[0], new QuickSort())),
                "Different task types are not equal");
        second.setTaskId("2");
        second.setDescription("Updated");
        check(second.getTaskId().equals("2") && second.getDescription().equals("Updated"), "Task setters");
        String expected = "id=1|description=Feedback lab1|message=Ai obtinut 9.60"
                + "|from=Gigi|to=Ana|date=2018-09-27 09:29";
        check(first.toString().equals(expected), "Required message format");
        check(outputOf(first).equals(expected + System.lineSeparator()), "MessageTask execution");
        int[] numbers = {3, -1, 2};
        check(outputOf(new SortingTask("3", "Sorting", numbers, new QuickSort()))
                .equals("[-1, 2, 3]" + System.lineSeparator()), "SortingTask execution");
        check(Arrays.equals(numbers, new int[]{-1, 2, 3}), "SortingTask sorts its array");
    }

    private static void testSorters() {
        for (AbstractSorter sorter : new AbstractSorter[]{new BubbleSort(), new QuickSort()}) {
            int[][] cases = {{}, {1}, {2, 1}, {1, 2, 3}, {3, 2, 1}, {4, 4, 4},
                    {Integer.MAX_VALUE, 0, Integer.MIN_VALUE, -1}};
            for (int[] numbers : cases) {
                checkSort(sorter, numbers.clone());
            }
            Random random = new Random(42);
            for (int length = 0; length < 100; length++) {
                int[] numbers = new int[length];
                for (int i = 0; i < length; i++) {
                    numbers[i] = random.nextInt(21) - 10;
                }
                checkSort(sorter, numbers);
            }
        }
    }

    private static void checkSort(AbstractSorter sorter, int[] numbers) {
        int[] expected = numbers.clone();
        Arrays.sort(expected);
        sorter.sort(numbers);
        check(Arrays.equals(numbers, expected), sorter.getClass().getSimpleName() + " sorted order");
    }

    private static void testStack() {
        for (int capacity : new int[]{0, 1, 2, 100}) {
            StackContainer stack = new StackContainer(capacity);
            check(stack.isEmpty() && stack.size() == 0 && stack.remove() == null, "Empty stack");
            Task[] tasks = new Task[205];
            for (int i = 0; i < tasks.length; i++) {
                tasks[i] = message(String.valueOf(i));
                stack.add(tasks[i]);
                check(stack.size() == i + 1 && stack.get(i) == tasks[i], "Growth preserves elements");
            }
            for (int i = tasks.length - 1; i >= 0; i--) {
                check(stack.remove() == tasks[i] && stack.size() == i, "LIFO removal");
            }
            check(stack.isEmpty() && stack.remove() == null, "Drained stack");
            stack.add(tasks[0]);
            check(stack.remove() == tasks[0] && stack.isEmpty(), "Reuse after draining");
            try {
                stack.get(0);
                throw new AssertionError("Invalid index accepted");
            } catch (IndexOutOfBoundsException expected) {
                // Only currently stored elements may be accessed.
            }
            try {
                stack.add(null);
                throw new AssertionError("Null task accepted");
            } catch (NullPointerException expected) {
                check(stack.isEmpty(), "Rejected task leaves stack unchanged");
            }
        }
        check(new StackContainer().isEmpty(), "Default constructor");
        try {
            new StackContainer(-1);
            throw new AssertionError("Negative capacity accepted");
        } catch (IllegalArgumentException expected) {
            // Negative capacities are invalid.
        }
    }

    private static MessageTask message(String id) {
        return new MessageTask(id, "Feedback lab1", "Ai obtinut 9.60", "Gigi", "Ana",
                LocalDateTime.of(2018, 9, 27, 9, 29));
    }

    private static String outputOf(Task task) {
        PrintStream original = System.out;
        ByteArrayOutputStream output = new ByteArrayOutputStream();
        try (PrintStream capture = new PrintStream(output)) {
            System.setOut(capture);
            task.execute();
        } finally {
            System.setOut(original);
        }
        return output.toString();
    }

    private static void check(boolean condition, String message) {
        if (!condition) {
            throw new AssertionError(message);
        }
    }
}
