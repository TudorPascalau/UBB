import task.MessageTask;
import task.SortingTask;
import container.StackContainer;
import sorter.BubbleSort;
import sorter.QuickSort;

import java.time.LocalDateTime;

public class Main {
    public static void main(String[] args) {
        MessageTask[] tasks = {
                new MessageTask("1", "Feedback lab1", "Ai obtinut 9.60", "Gigi", "Ana",
                        LocalDateTime.of(2018, 9, 27, 9, 29)),
                new MessageTask("2", "Feedback lab2", "Ai obtinut 10", "Gigi", "Ana",
                        LocalDateTime.of(2018, 10, 4, 10, 30)),
                new MessageTask("3", "Anunt seminar", "Seminarul incepe la 10", "Maria", "Studenti",
                        LocalDateTime.of(2018, 10, 5, 8, 0)),
                new MessageTask("4", "Tema", "Rezolvati exercitiile 1-5", "Maria", "Ana",
                        LocalDateTime.of(2018, 10, 5, 9, 15)),
                new MessageTask("5", "Confirmare", "Am primit tema", "Ana", "Maria",
                        LocalDateTime.of(2018, 10, 5, 11, 45))
        };

        for (MessageTask task : tasks) {
            task.execute();
        }

        System.out.println("BubbleSort:");
        new SortingTask("6", "Sortare BubbleSort", new int[]{5, -2, 3, 3, 0}, new BubbleSort()).execute();
        System.out.println("QuickSort:");
        new SortingTask("7", "Sortare QuickSort", new int[]{5, -2, 3, 3, 0}, new QuickSort()).execute();

        System.out.println("StackContainer (LIFO):");
        StackContainer stack = new StackContainer(2);
        for (MessageTask task : tasks) {
            stack.add(task);
        }
        while (!stack.isEmpty()) {
            stack.remove().execute();
        }
    }
}
