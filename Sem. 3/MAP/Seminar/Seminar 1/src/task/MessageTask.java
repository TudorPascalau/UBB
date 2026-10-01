package task;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MessageTask extends Task {

    public static final DateTimeFormatter DATE_TIME_FORMATTER =
            DateTimeFormatter.ofPattern("yyyy-MM-dd hh:mm");

    private String message;
    private String from;
    private String to;
    private LocalDateTime date;

    public MessageTask(String taskId, String description, String message, String from, String to, LocalDateTime date) {
        super(taskId, description);
        this.message = message;
        this.from = from;
        this.to = to;
        this.date = date;
    }

    @Override
    public String toString() {
        return "Message Task{" +
                "message " + this.message +
                ", from " + this.from +
                ", to " + this.to +
                " at time" + date.format(DATE_TIME_FORMATTER);
    }

    @Override
    public void execute() {
        System.out.println(this);
    }
}
