import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;

public class Loader {
    public Loader(){}


    public World loadGameState(){
        try (InputStream is = new FileInputStream("savedGameState");
             ObjectInputStream ois = new ObjectInputStream(is)) {
            World world = (World) ois.readObject();
            return world;
        } catch (IOException | ClassNotFoundException ex) {
            System.out.println("Loading Exception" + ex);
        }
        return null;
    }
}
