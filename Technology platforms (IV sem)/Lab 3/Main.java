import java.util.List;

public class Main {

    public static void main(String[] args) {

        Thread serverThread = new Thread(new IncomingSocketConnectionHandler(8080));
        serverThread.start();
    }
}
