import static java.lang.Integer.parseInt;

public class Main {

    public static void main(String[] args) {
        int threadsNumber = parseInt(args[0]);

        Resource resource = new Resource();
        ThreadManager threadManager = new ThreadManager(resource, threadsNumber);
        InputManager inputManager = new InputManager(resource);

        threadManager.StartThreads();
        inputManager.TakeInput(); //Type "End" to stop
        threadManager.StopThreads();

        System.out.println(resource.getResults());
    }
}
