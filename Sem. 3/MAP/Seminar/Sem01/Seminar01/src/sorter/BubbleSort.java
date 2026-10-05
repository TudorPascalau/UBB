package sorter;

public class BubbleSort extends AbstractSorter {
    @Override
    public void sort(int[] numbers) {
        for (int end = numbers.length - 1; end > 0; end--) {
            boolean swapped = false;
            for (int i = 0; i < end; i++) {
                if (numbers[i] > numbers[i + 1]) {
                    int temporary = numbers[i];
                    numbers[i] = numbers[i + 1];
                    numbers[i + 1] = temporary;
                    swapped = true;
                }
            }
            if (!swapped) {
                return;
            }
        }
    }
}
