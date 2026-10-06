import factory.Strategy;
import runner.PrinterTaskRunner;
import runner.StrategyTaskRunner;
import task.MessageTask;

import java.time.LocalDateTime;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Introdu o strategie: FIFO sau LIFO.");
            return;
        }

        Strategy strategy;
        try {
            strategy = Strategy.valueOf(args[0]);
        } catch (IllegalArgumentException e) {
            System.out.println("Strategie invalida. Foloseste FIFO sau LIFO.");
            return;
        }

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

        System.out.println("Strategy task runner");
        StrategyTaskRunner taskRunner = new StrategyTaskRunner(strategy);
        taskRunner.addTask(tasks[0]);
        taskRunner.addTask(tasks[1]);
        taskRunner.addTask(tasks[2]);
        taskRunner.executeAllTasks();

        System.out.println("Printer task runner");
        PrinterTaskRunner printerTaskRunner = new PrinterTaskRunner(taskRunner);
        printerTaskRunner.addTask(tasks[0]);
        printerTaskRunner.addTask(tasks[1]);
        printerTaskRunner.addTask(tasks[2]);
        printerTaskRunner.executeAllTasks();

    }
}
