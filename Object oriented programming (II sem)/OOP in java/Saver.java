import java.io.*;

public class Saver {
    public Saver(){
    }

    public void saveGameState(World world){
        try (OutputStream os = new FileOutputStream("savedGameState")) {
            try(ObjectOutputStream oos = new ObjectOutputStream(os)) {
                oos.writeObject(world);
            }
            catch (IOException ex){}
        } catch (IOException | SecurityException ex) {}
    }
}
