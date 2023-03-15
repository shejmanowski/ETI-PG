import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.util.List;
import java.util.logging.Level;

public class IncomingSocketConnectionHandler implements Runnable{

    private final ServerSocket server;

    public IncomingSocketConnectionHandler(int port) {
        try {
            server = new ServerSocket(port);
            server.setSoTimeout(1000);
        } catch (IOException ex) {
            throw new IllegalStateException(ex);
        }
    }

    @Override
    public void run(){
        System.out.println("Staring listener.");
        while (!Thread.interrupted()) {
            try {
                Socket socket = server.accept();
                new Thread(new SocketConnectionHandler(socket)).start();
            } catch (SocketTimeoutException ex) {
                //System.out.println(Level.FINEST, ex.getMessage(), ex);
            } catch (IOException ex) {
                //log.log(Level.WARNING, ex.getMessage(), ex);
            }
        }
        System.out.println("Stopping listener.");
    }
}
