import java.util.Date;

public class ProducerConsumer {
    static final int N = 100;
    static Producer p = new Producer();
    static Consumer c = new Consumer();
    static OurMonitor mon = new OurMonitor();

    public static void main(String args[]) {
        p.start();
        c.start();
    }

    static class Producer extends Thread {
        public void run() {
            long item;
            while (true) {
                item = produceItem();
                mon.insert(item);
            }
        }

        private long produceItem() {
            return new Date().getTime();
        }
    }

    static class Consumer extends Thread {
        public void run() {
            long item;
            while (true) {
                item = mon.remove();
                consumeItem(item);
            }
        }

        private void consumeItem(long item) {
            System.out.println("consumer: " + item);
        }
    }

    static class OurMonitor {
        private long buffer[] = new long[N];
        private int count = 0, lo = 0, hi = 0;

        public synchronized void insert(long item) {
            if (count == N)
                goToSleep();
            buffer[hi] = item;
            hi = (hi + 1) % N;
            if (++count == 1)
                notify();
        }

        public synchronized long remove() {
            long val;
            if (count == 0)
                goToSleep();
            val = buffer[lo];
            lo = (lo + 1) % N;
            count = count - 1;
            if (count == N - 1)
                notify();
            return val;
        }

        private void goToSleep() {
            try {
                wait();
            } catch (InterruptedException error) {
                System.out.println(error.getMessage());
            }
        }
    }
}