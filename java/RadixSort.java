import java.util.LinkedList;
import java.util.List;

public class RadixSort {


    private static void radixMSD(int radix, int[] a, int[] b, int start, int end, int length, int mod) {

        int[] count = new int[length];
        //int[] index = new int[10];
        int[] temp = new int[a.length];

        for (int i = start; i < end; i++) {
            int test = (int) (a[i] / Math.pow(10, radix)) % mod; //radix
            count[test]++;
            b[test]++;
        }

        for (int k = 1; k < length; k++) {
            count[k] += count[k - 1];
            b[k] += b[k - 1];
        }

        for (int i = end - 1; i >= start; i--) {
            int test = (int) (a[i] / Math.pow(10, radix)) % mod; //radix
            temp[--count[test]] = a[i];
        }

        for (int i = start; i < end; i++) {
            a[i] = temp[i];
        }
    }

    public static void radixLSD(int radix, int[] a, int[] b, int start, int end) {
        if (end <= (start + 1)) {
            return;
        }

        int[] count = new int[10];

        for (int i = start; i < end; i++) {
            int test = (int) (a[i] / Math.pow(10, radix)) % 10; //radix
            count[test]++;
        }

        for (int k = 1; k < 10; k++) {
            count[k] += count[k - 1];
        }

        for (int i = end - 1; i >= start; i--) {
            int test = (int) (a[i] / Math.pow(10, radix)) % 10; //radix
            b[--count[test] + start] = a[i];
        }

        for (int i = start; i < end; i++) {
            a[i] = b[i];
        }
    }

    public static void sortParallel(int level, int[] a, int[] b, int[] c, int radix) {
        List<Thread> threadList = new LinkedList<>();
        if (level == 0) {
			for (int i = 0; i < radix; i++) {
				radixLSD(i, a, b, 0, a.length);
			}
		} else {
			threadList = createThreads(level, a, b, c, radix);
			threadList.forEach(Thread::start);

			threadList.forEach(thread -> {
				try {
					thread.join();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			});
		}
    }

    private static List<Thread> createThreads(int level, int[] a, int[] b, int[] c, int radix) {
		List<Thread> threadList = new LinkedList<>();
		int iterations = (int) Math.pow(2, level);
		int start = 0;
		int end = c.length / iterations;
		for (int i = 0; i < iterations; i++) {
			threadList.add(new Thread(new RadixSorter(a, b, c, radix, start, iterations)));
			start = end;
			end = end + (c.length / iterations);
		} 
		return threadList;
	}


    public static void sort(int[] a, int[] b, int maxValue, int level, int length, int mod) {    //max length
        int[] temp = new int[length];

        if (level != 0) {
            if (mod == 100) {
                radixMSD(maxValue - 2, a, temp, 0, a.length, length, mod);
            } else {
                radixMSD(maxValue - 1, a, temp, 0, a.length, length, mod);
            }
        }

        sortParallel(level, a, b, temp, maxValue);
    }
}
