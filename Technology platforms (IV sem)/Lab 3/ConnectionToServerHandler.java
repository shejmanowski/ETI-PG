import java.io.*;
import java.net.Socket;
import java.util.Random;
import java.util.Scanner;

public class ConnectionToServerHandler {

    Message msg = new Message(3, "Hejka");
    Message msg2 = new Message(6, "Narka");

    public void makeConnection() {
        Random rand = new Random();
        Scanner scan = new Scanner(System.in);
        try (Socket client = new Socket("localhost", 8080)) {
            System.out.println("Connection made");
            try (ObjectInputStream is = new ObjectInputStream(client.getInputStream());
                 ObjectOutputStream oos = new ObjectOutputStream(client.getOutputStream())) {

                System.out.println("Server is " + (String) is.readObject() + ".");
                System.out.println("Type n:");
                Integer n = scan.nextInt();
                scan.nextLine();
                oos.writeObject(n);

                System.out.println("Server is " + (String) is.readObject() + ".");
                Integer[] arr = new Integer[10];
                for (int i = 0; i < 10; i++) {
                    arr[i] = rand.nextInt(n);
                }
                oos.writeObject(arr);
                System.out.println("Server is " + (String) is.readObject() + ".");
                for (int i = 0; i < n; i++) {
                    int nr = i + 1;
                    System.out.println("--Message number " + nr + ":");
                    Message msg = new Message(rand.nextInt(10), scan.nextLine());
                    oos.writeObject(msg);
                }
                System.out.println("Messages sent to the server");
            }
        } catch (IOException | ClassNotFoundException ex) {
            System.err.println(ex);
        }
    }
}
