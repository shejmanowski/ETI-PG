import java.util.Collections;
import java.util.List;
import java.util.ArrayList;

public class Resource {

    private final List<Integer> toCalculate = Collections.synchronizedList(new ArrayList<>());
    private final List<Integer> results = Collections.synchronizedList(new ArrayList<>());

    public List<Integer> getResults() {
        return results;
    }

    private final Object lock1 = new Object();
    private final Object lock2 = new Object();

    public int take() throws InterruptedException {
        synchronized(lock1) {
            while (toCalculate.isEmpty()) {
                System.out.println(Thread.currentThread().getName() + " waits");
                lock1.wait();
            }
            System.out.println(Thread.currentThread().getName() + " takes");
            int ret = toCalculate.get(0);
            toCalculate.remove(0);
            return ret;
        }
    }

    public void put(int number){
        synchronized (lock1) {
            toCalculate.add(number);
            lock1.notifyAll();
        }
    }

    public void saveResult(Integer result){
        synchronized (lock2){
            results.add(result);
        }
    }
}
