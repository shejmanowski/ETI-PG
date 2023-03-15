import java.util.Scanner;

public class InputManager{
    Scanner scan = new Scanner(System.in);
    private final Resource resource;

    public InputManager(Resource resource){
        this.resource = resource;
    }

    public void TakeInput(){
        String line = scan.nextLine();
        while(!line.equals("End")){
            int number = Integer.parseInt(line);
            resource.put(number);
            line = scan.nextLine();
        }
    }

}
