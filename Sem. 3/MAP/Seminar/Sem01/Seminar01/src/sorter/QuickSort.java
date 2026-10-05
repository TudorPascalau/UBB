package sorter;

public class QuickSort extends AbstractSorter {
    @Override
    public void sort(int[] numbers) {
        sort(numbers, 0, numbers.length - 1);
    }

    private void sort(int[] numbers, int left, int right) {
        if (left >= right) {
            return;
        }
        int pivot = numbers[left + (right - left) / 2];
        int i = left;
        int j = right;
        while (i <= j) {
            while (numbers[i] < pivot) {
                i++;
            }
            while (numbers[j] > pivot) {
                j--;
            }
            if (i <= j) {
                int temporary = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temporary;
                i++;
                j--;
            }
        }
        sort(numbers, left, j);
        sort(numbers, i, right);
    }
}
