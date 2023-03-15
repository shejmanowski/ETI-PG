import java.util.ArrayList;
import java.util.List;

public class ThreadManager {
    List<Thread> threads = new ArrayList<>();
    Resource resource;
    int threadsNumber;

    public ThreadManager(Resource resource, int threadsNumber){
        this.resource = resource;
        this.threadsNumber = threadsNumber;
    }

    public void StartThreads(){
        for(int i = 0; i < threadsNumber; i++){
            threads.add(new Thread(new PrimeChecker(resource)));
            threads.get(i).start();
        }
    }

    public void StopThreads(){
        for(int i = 0; i < threadsNumber; i++){
            threads.get(i).interrupt();
        }
    }
}
