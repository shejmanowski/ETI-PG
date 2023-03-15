import java.io.*;
import java.net.Socket;
import java.util.Arrays;

public class SocketConnectionHandler implements Runnable {

    private final Socket socket;


    public SocketConnectionHandler(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run(){
        try (ObjectOutputStream output =  new ObjectOutputStream(socket.getOutputStream());
             ObjectInputStream input = new ObjectInputStream(socket.getInputStream());) {

            output.writeObject("ready");
            Integer n = (Integer) input.readObject();
            output.writeObject("ready for an array");
            Integer[] arr = (Integer[]) input.readObject();
            System.out.println(Arrays.toString(arr));
            output.writeObject("ready for messages");
            for(int i = 0; i < n; i++){
                System.out.println(input.readObject().toString());
            }
            output.writeObject("finished");


        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
