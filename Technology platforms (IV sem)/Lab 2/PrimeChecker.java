public class PrimeChecker implements Runnable{

    private final Resource resource;

    public PrimeChecker(Resource resource){
        this.resource = resource;
    }

    @Override
    public void run() {

        while(!Thread.interrupted()) {
            try {
                int number = resource.take();

                System.out.println(Thread.currentThread().getName() + " starts counting");
                Thread.sleep(1000 * 5); //time-consuming calculations

                boolean prime = true;
                for (int i = 2; i < number - 1; i++) {
                    if (number % i == 0) {
                        prime = false;
                        break;
                    }
                }
                System.out.println(Thread.currentThread().getName() + " done counting");
                if (prime) {
                    resource.saveResult(number);
                }
            } catch (InterruptedException e) {
                break;
            }
        }
        System.out.println(Thread.currentThread().getName() + " died");
    }
}
